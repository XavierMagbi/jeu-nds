
#include <nds.h>
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
u16 *birdgfx;
u16 *Pipegfx;
u16 *Tubegfx;
u16 *Pipegfx1;
u16 *Pipegfx2;
u16 *Pipegfx3;


Pipe pipes[NUM_PIPES];


extern int speedMultiplier; 
bool printpipe;


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

    if scrollX == 0 {
        printpipe = true;
    }

    
}

void setBirdPosition(int index, int x, int y) {
    oamSet(&oamMain, index, x, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, birdgfx, -1, false, false, false, false, false);
}

void setPipePosition(int index, int x, int y) {
    oamSet(&oamMain, index, x, y, 0, 0, SpriteSize_64x64, SpriteColorFormat_256Color, Pipegfx, -1, false, false, false, false, false);
    oamSet(&oamMain, index+1, x, 0, 0, 0, SpriteSize_64x64, SpriteColorFormat_256Color, Pipegfx, -1, false, false, false, true, false);
}

void setPipePositiondouble(int index, int x, int y, int z ) {
    oamSet(&oamMain, index, x, y, 0, 0, SpriteSize_64x64, SpriteColorFormat_256Color, Pipegfx, -1, false, false, false, false, false);  //DOWN
    oamSet(&oamMain, index+1, x, z, 0, 0, SpriteSize_64x64, SpriteColorFormat_256Color, Pipegfx, -1, false, false, false, true, false); //UP
}

void setTubePosition(int index , int x , int y){
     oamSet(&oamMain, index, x, y, 0, 0, SpriteSize_64x64, SpriteColorFormat_256Color, Pipegfx2, -1, false, false, false, true, false);//UP 
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
    birdgfx = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
    Pipegfx = oamAllocateGfx(&oamMain, SpriteSize_64x64, SpriteColorFormat_256Color);
    Tubegfx = oamAllocateGfx(&oamMain, SpriteSize_64x64, SpriteColorFormat_256Color);

    // Load bird sprite palette and tiles
    dmaCopy(birdPal, SPRITE_PALETTE , birdPalLen); // Load bird palette at index 0
    dmaCopy(pipe1Pal, &SPRITE_PALETTE[birdPalLen/2], pipe1PalLen);
    dmaCopy(pipe2Pal, &SPRITE_PALETTE[pipe1PalLen/2], pipe2PalLen);
    dmaCopy(birdTiles, birdgfx, birdTilesLen); // Load bird tiles
    dmaCopy(pipe1Tiles , Pipegfx, pipe1TilesLen);   // Load pipe tiles
    dmaCopy(pipe2Tiles , Tubegfx, pipe2TilesLen);        // Load tube tiles

}

void initPipes() {

    if (printpipe){

        for (int i = 0; i < NUM_PIPES; i += 2) {
        pipes[i].x = SCREEN_WIDTH + (i / 2) * 40;      // Apply 40px horizontal spacing
        pipes[i + 1].x = pipes[i].x;                   // Sync lower pipe with upper pipe

        int pattern = (i / 2) % 3;  // Cycle through 3 patterns

        if (pattern == 0) {
            // Pattern 1: Upper at 0, lower at 150
            pipes[i].y = 0;
            pipes[i + 1].y = 150;
        } else if (pattern == 1) {
            // Pattern 2: Upper at 20, lower at 180
            pipes[i].y = 20;
            pipes[i + 1].y = 180;
        } else {
            // Pattern 3: Upper at 10, lower at 170
            pipes[i].y = 10;
            pipes[i + 1].y = 170;
        }
    }


    }
    
}

void initGamePipes() {
    initPipes();  // Initialize pipe positions

    // Initialize all 3 pipe pairs (6 pipes total)
    for (int i = 0; i < NUM_PIPES; i += 2) {
        setPipePositiondouble(i, pipes[i].x, pipes[i].y, pipes[i + 1].y);
    }
}




void updatePipes() {
    for (int i = 0; i < NUM_PIPES; i += 2) {
        pipes[i].x -= 1 * speedMultiplier;    // Move upper pipe
        pipes[i + 1].x = pipes[i].x;         // Sync lower pipe

        // Reset pipes when off-screen
        if (pipes[i].x + PIPE_WIDTH < 0) {
            pipes[i].x = SCREEN_WIDTH + 40;  // Reset with 40px spacing
            pipes[i + 1].x = pipes[i].x;

            int pattern = ((i / 2) + 1) % 3;  // Cycle to next pattern

            if (pattern == 0) {
                // Pattern 1: Upper at 0, lower at 150
                pipes[i].y = 0;
                pipes[i + 1].y = 150;
            } else if (pattern == 1) {
                // Pattern 2: Upper at 20, lower at 180
                pipes[i].y = 20;
                pipes[i + 1].y = 180;
            } else {
                // Pattern 3: Upper at 10, lower at 170
                pipes[i].y = 10;
                pipes[i + 1].y = 170;
            }
        }

        // Update the sprite positions
        setPipePosition(i, pipes[i].x, pipes[i].y);           // Upper pipe
        setPipePosition(i + 1, pipes[i + 1].x, pipes[i + 1].y); // Lower pipe
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

