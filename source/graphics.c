
#include "graphics.h"
#include <nds/arm9/background.h>
#include <stdio.h>
#include"bird.h"
#include "pipe1.h"
#include "pipe2.h"
#include "background2.h" // GRIT file for background tiles
#include "Subbg.h"
#include "GameOver.h"


// Global variables 

int scrollX = 0;
u16 *gfx;
u16 *Pipegfx;
u16 *Pipegfx2;

Pipe pipes[NUM_PIPES];


extern int speedMultiplier; 


// Main engine configuration 

void initMainScreenBackground() {


    // Configure sub-screen with BG0 for text
    REG_DISPCNT = MODE_0_2D | DISPLAY_BG0_ACTIVE;

    // Use VRAM C for sub-screen
    VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;

    // Configure BG0 on the sub-screen
    BGCTRL[0] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(2);



    dmaCopy(background2Tiles, BG_TILE_RAM(2), background2TilesLen);
    dmaCopy(background2Map, BG_MAP_RAM(0), background2MapLen);
    dmaCopy(background2Pal, BG_PALETTE, background2PalLen);
}

void resetPipe() {
    for(int i = 0; i < NUM_PIPES; i++) {
    
        pipes[i].x = PIPE_INIT_X;
        pipes[i].y = PIPE_INIT_Y*i;
        //setPipePosition(SPRITE_PIPE, PIPE_INIT_X , pipes[i].y);
      
    }
    
}

void updateBackground() {
    speedTimerISR();
    scrollX = (scrollX + 1) % 256; // Accelerated scrolling
    REG_BG0HOFS = scrollX; 
}

void setBirdPosition(int index, int x, int y) {
    oamSet(&oamMain, index, x, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, gfx, -1, false, false, false, false, false);
}

void setPipePosition(int index, int x, int y) {
    oamSet(&oamMain, index, x, y, 0, 0, SpriteSize_64x64, SpriteColorFormat_256Color, Pipegfx, -1, false, false, false, false, false);
    oamSet(&oamMain, index+1, x, 0, 0, 0, SpriteSize_64x64, SpriteColorFormat_256Color, Pipegfx, -1, false, false, false, true, false);
}
void setPipePositiondouble(int index, int x, int y, int z ) {
    oamSet(&oamMain, index, x, y, 0, 0, SpriteSize_64x64, SpriteColorFormat_256Color, Pipegfx, -1, false, false, false, false, false);  //DOWN
    oamSet(&oamMain, index+1, x, z, 0, 0, SpriteSize_64x64, SpriteColorFormat_256Color, Pipegfx, -1, false, false, false, true, false); //UP
}



// Fonction pour réinitialiser le jeu en cas de Game Over
void resetGame() {                    // Score réinitialisé
    gameState = GAME_STATE_WAITING; // Retour à l'état d'attente
    birdX = BIRDX_INIT;
    birdY = BIRDY_INIT;

    //resetPipe();
    consoleClear();                // Efface l'écran de la console
    
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
    //Pipegfx2 = oamAllocateGfx(&oamMain, SpriteSize_64x64, SpriteColorFormat_256Color);

    // Load bird sprite palette and tiles
    dmaCopy(birdPal, SPRITE_PALETTE , birdPalLen); // Load bird palette at index 0
    dmaCopy(pipe1Pal, &SPRITE_PALETTE[birdPalLen/2], pipe1PalLen);
    //dmaCopy(pipe1Pal, &SPRITE_PALETTE[pipe1PalLen/2], pipe1PalLen);
    dmaCopy(birdTiles, gfx, birdTilesLen); // Load bird tiles
    dmaCopy(pipe1Tiles , Pipegfx, pipe1TilesLen);   // Load pipe tiles
    //dmaCopy(pipe1Tiles , Pipegfx2, pipe1TilesLen);              // Load bird tiles

}


void initPipes() {
    for (int i = 0; i < NUM_PIPES; i++) {
        int pair_number = i / 2;
        pipes[i].x = PIPE_INIT_X + (pair_number * 140);
        if (i % 2 == 0) {
            // Upper pipe
            pipes[i].y = 0; // Fixed at the top of the screen
        } else {
            // Lower pipe
            pipes[i].y = 150; // Fixed at the predefined bottom Y-coordinate
        }
    }
}


void updatePipes() {
    int spriteIndex = 1;
    for (int i = 0; i < NUM_PIPES; i++) {
        pipes[i].x -= 1;

        if (i % 2 == 0) {
            // Set position for upper and lower pipes
            setPipePositiondouble(spriteIndex, pipes[spriteIndex-1].x, pipes[spriteIndex].y, pipes[spriteIndex-1].y);
            spriteIndex += 2;
        }
        
        // Reset pipe if it moves off-screen
        if (pipes[i].x + PIPE_WIDTH < 0) {
            pipes[i].x = SCREEN_WIDTH;

            
           if (i % 2 == 0) {
                
                int maxUpperY = 150 - PIPE_HEIGHT - PIPE_GAP;
                pipes[i].y = rand() % (maxUpperY > 0 ? maxUpperY : 1); 
                } else {
                    
                    pipes[i].y = pipes[i - 1].y + PIPE_HEIGHT + PIPE_GAP;

                    if (pipes[i].y > 150) {
                        pipes[i].y = 150;
                    }
                }

            
        }
    }
}

void updateScore(int score) {
    
    for (int i = 0; i < NUM_PIPES; i++){
        iprintf("\x1b[10;cela marche");

        if (birdX > pipes[i].x + PIPE_WIDTH) { // Passed the pipe
            //pipes[i].x = -1; // Mark pipe as counted
            score++;
            iprintf("Score: %d\n", score);
        }
        
    }
 }

void initSubScreen(){

    REG_DISPCNT_SUB = MODE_0_2D | DISPLAY_BG0_ACTIVE;

    VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;

    BGCTRL_SUB[0] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(2);


    dmaCopy(SubbgTiles, BG_TILE_RAM_SUB(2), SubbgTilesLen);
    dmaCopy(SubbgMap, BG_MAP_RAM_SUB(0), SubbgMapLen);
    dmaCopy(SubbgPal, BG_PALETTE_SUB, SubbgPalLen);

}


void displayGameOverScreen() {

    gameState = GAME_STATE_GAME_OVER;


    REG_DISPCNT_SUB = MODE_0_2D | DISPLAY_BG0_ACTIVE;

    VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;

    BGCTRL_SUB[0] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(1) | BG_TILE_BASE(3);

    dmaCopy(GameOverTiles, BG_TILE_RAM_SUB(3), GameOverTilesLen);
    dmaCopy(GameOverMap, BG_MAP_RAM_SUB(1), GameOverMapLen);
    dmaCopy(GameOverPal, BG_PALETTE_SUB, GameOverPalLen);

    
}

void checkCollisions() {
    // Check ground and ceiling collision
    if (birdY >= GROUNDLEVEL || birdY <= 0) {
        // Collision with ground or ceiling
        displayGameOverScreen();
        return;
    }
    
    // Check pipe collisions
    for (int i = 0; i < NUM_PIPES; i++) {
            // Horizontal collision check
            if (birdX + BIRD_WIDTH  > pipes[i].x && birdX < pipes[i].x + PIPE_WIDTH) {
                if (i % 2 == 0) {
                    if (birdY < (pipes[i].y+60)) {
                        displayGameOverScreen();
                        return;
                    }
                } 
                else {
                    if (birdY + BIRD_HEIGHT-10 > pipes[i].y) {
                    displayGameOverScreen();
                    return;
                    }
                
                    }
            }
        }
        
        
 }

 void displayScoreAndDistance(int score, int distance) {
    // Print the score and distance at the top-left corner
    iprintf("\x1b[1;1HScore: %d", score);
    iprintf("\x1b[2;1HDistance: %d m", distance);
}



//****************************************NEW CODE

