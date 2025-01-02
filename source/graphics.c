
#include "graphics.h"
#include <nds/arm9/background.h>
#include"bird.h"
#include "pipe1.h"
#include "pipe2.h"
#include "start_button.h"
#include "Menu.h"
#include "background2.h" // GRIT file for background tiles
#include <stdio.h>

// Global variables 

int scrollX = 0;
u16 *gfx;
u16 *Pipegfx;
u16 *Pipegfx2;

Pipe pipes[NUM_PIPES];


// Main engine configuration 

void initBackground() {

    REG_DISPCNT = MODE_0_2D | DISPLAY_BG0_ACTIVE;

    VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;

    BGCTRL[0] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(2);

    dmaCopy(background2Tiles, BG_TILE_RAM(2), background2TilesLen);
    dmaCopy(background2Map, BG_MAP_RAM(0), background2MapLen);
    dmaCopy(background2Pal, BG_PALETTE, background2PalLen);
}


void updateBackground() {
    scrollX = (scrollX + 1) % 256; // Wrap around when reaching the end
    REG_BG0HOFS = scrollX; 
    }        // Update horizontal offset

void setBirdPosition(int index, int x, int y) {
    oamSet(&oamMain, index, x, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, gfx, -1, false, false, false, false, false);
}

void setPipePosition(int index, int x, int y) {
    oamSet(&oamMain, index, x, y, 0, 0, SpriteSize_64x64, SpriteColorFormat_256Color, Pipegfx, -1, false, false, false, false, false);
}

void drawPipes() {
    for (int i = 0; i < NUM_PIPES; i++) {
        if (pipes[i].active) {
            // Top pipe
            setPipePosition(i * 2, pipes[i].x, pipes[i].y - PIPE_HEIGHT);

            // Bottom pipe
            setPipePosition(i * 2 + 1, pipes[i].x, pipes[i].y + PIPE_GAP);
        }
    }
}




// Fonction pour initialiser le jeu
void initGame() {
    //gameState = GAME_STATE_WAITING; // État initial du jeu
    score = 0;                     // Score réinitialisé
    
    initBackground();                // Initialise les graphismes
    //initBird();                    // Initialise l'oiseau

}

// Fonction pour réinitialiser le jeu en cas de Game Over
void resetGame() {
    score = 0;                     // Score réinitialisé
    gameState = GAME_STATE_WAITING; // Retour à l'état d'attente

    consoleClear();                // Efface l'écran de la console
    iprintf("Appuyez sur A pour rejouer\n");
}

void handleInput() {
    
return ; 	
}

void updateGameLogic() {
    birdVelocity += GRAVITY;
    birdY += birdVelocity;
    //setBirdPosition(32, birdY);

    // Check collisions (ground, pipes, etc.)
    if (birdY > 192 || birdY < 0) {
        //playCollisionSound();
        while (1); // Game Over
    }
}

void displayStartScreen() {
    blinkCounter++;

    // Alterne tous les 30 frames (environ 0.5 secondes si 60 FPS)
    if (blinkCounter >= 30) {
        showMessage = !showMessage; // Alterne entre afficher et cacher
        blinkCounter = 0;          // Réinitialise le compteur
    }

    // Efface la ligne du message
    iprintf("\x1b[10;0H                              "); // Remplit l’espace avec des espaces

    // Affiche le message uniquement si showMessage est vrai
    if (showMessage) {
        iprintf("\x1b[10;5HAppuyez sur A pour jouer");
    }
}

void configureSprites(){
     // Map VRAM_B for the bird sprite
    VRAM_B_CR = VRAM_ENABLE | VRAM_B_MAIN_SPRITE_0x06400000;



    oamInit(&oamMain, SpriteMapping_1D_32, false);
    gfx = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
    Pipegfx = oamAllocateGfx(&oamMain, SpriteSize_64x64, SpriteColorFormat_256Color);
    Pipegfx2 = oamAllocateGfx(&oamMain, SpriteSize_64x64, SpriteColorFormat_256Color);

    // Load bird sprite palette and tiles
    dmaCopy(birdPal, SPRITE_PALETTE , birdPalLen); // Load bird palette at index 0
    dmaCopy(pipe1Pal, &SPRITE_PALETTE[birdPalLen/2], pipe1PalLen);
    dmaCopy(pipe1Pal, &SPRITE_PALETTE[pipe1PalLen/2], pipe1PalLen);
    dmaCopy(birdTiles, gfx, birdTilesLen); // Load bird tiles
    dmaCopy(pipe1Tiles , Pipegfx, pipe1TilesLen);   // Load pipe tiles
    dmaCopy(pipe2Tiles , Pipegfx2, pipe2TilesLen);              // Load bird tiles

}

void initPipes() {
    for (int i = 0; i < NUM_PIPES; i++) {
        pipes[i].x = SCREEN_WIDTH + i * 100; // Offset pipes
        pipes[i].y = rand() % (SCREEN_HEIGHT - PIPE_GAP); // Random height
        pipes[i].active = true;
    }
}

void updatePipes() {

    int pipe_x = PIPE_INIT_X;
    int pipe_y = PIPE_INIT_Y ;
    for (int i = 0; i < NUM_PIPES; i++) {
        // Les pipes bougent à la même vitesse que le background
        pipe_x -= (1 + scrollX % 256); // Ajustez la vitesse relative si nécessaire
        setPipePosition(SPRITE_PIPE,pipe_x,pipe_y);
        /*
        // Réinitialiser le pipe lorsqu'il sort de l'écran
        if (pipes[i].x + PIPE_WIDTH < 0) {
            pipes[i].x = SCREEN_WIDTH;
            pipes[i].y = rand() % (SCREEN_HEIGHT - PIPE_GAP); // Nouvelle hauteur aléatoire
            pipes[i].active = true;
        }
        */
    }
}



void checkCollisions() {
    for (int i = 0; i < NUM_PIPES; i++) {
        if (pipes[i].active) {
            if (birdX + BIRD_WIDTH > pipes[i].x && birdX < pipes[i].x + PIPE_WIDTH) {
                if (birdY < pipes[i].y || birdY + BIRD_HEIGHT > pipes[i].y + PIPE_GAP) {
                    gameState = GAME_STATE_WAITING; // Game over
                }
            }
        }
    }
}


// Sub engine configuration 

void SubMenu(){

    // Sub background intialisation 
    REG_DISPCNT_SUB = MODE_0_2D | DISPLAY_BG0_ACTIVE;
    VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;

    // SuB Background configuration 
    BGCTRL_SUB[0] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(2);
    
    // Load the tiles and map into VRAM
    dmaCopy(MenuTiles, BG_TILE_RAM_SUB(0), MenuTilesLen); // Replace `menuTiles` with your tile data
    dmaCopy(MenuMap, BG_MAP_RAM_SUB(1), MenuMapLen);     // Replace `menuMap` with your map data
    dmaCopy(MenuPal, BG_PALETTE_SUB, MenuPalLen); // Replace `menuPalette` with your palette
}

void initSubMenuSprites() {
    // Configure VRAM pour les sprites sur le sous-écran
    REG_DISPCNT_SUB = MODE_0_2D | DISPLAY_BG0_ACTIVE;
    VRAM_D_CR = VRAM_ENABLE | VRAM_D_SUB_SPRITE;

    oamInit(&oamSub, SpriteMapping_1D_32, false);

    // Alloue de la mémoire pour les sprites
    u16* startButtonSubGfx = oamAllocateGfx(&oamSub, SpriteSize_64x32, SpriteColorFormat_256Color);

    // Charge les graphismes des boutons
    dmaCopy(start_buttonTiles, startButtonSubGfx, start_buttonTilesLen);

    // Charge la palette des sprites
    dmaCopy(start_buttonPal, SPRITE_PALETTE_SUB, start_buttonPalLen);
}


