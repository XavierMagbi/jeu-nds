
#include <nds/arm9/background.h>
#include <nds.h>
#include "graphics.h"
#include <stdio.h>

// GRIT file for Sprites 
#include"bird.h"
#include "pipe1.h"
#include "pipe2.h"

// GRIT file for background tiles
#include "background.h" 
#include "background2.h" 
#include "Subbg.h"
#include "SubGameBg.h"
#include "GameOver.h"
#include "Menu.h"


// Global variables 

int scrollX = 0;
u16 *birdgfx;
u16 *Pipegfx;
u16 *Pipegfx2;


Pipe pipes[NUM_PIPES];


extern int speedMultiplier; 
bool background = true; // To switch with the two backgrounds 


// Main engine configuration 

void initMainScreenBackground() {


    // Configure sub-screen with BG0 for text
    REG_DISPCNT = MODE_0_2D | DISPLAY_BG0_ACTIVE;

    // Use VRAM C for sub-screen
    VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;

    // Configure BG0 on the sub-screen
    BGCTRL[0] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(2);


    if (background){
    dmaCopy(background2Tiles, BG_TILE_RAM(2), background2TilesLen);
    dmaCopy(background2Map, BG_MAP_RAM(0), background2MapLen);
    dmaCopy(background2Pal, BG_PALETTE, background2PalLen);

    }

    else{

    dmaCopy(backgroundTiles, BG_TILE_RAM(2), backgroundTilesLen);
    dmaCopy(backgroundMap, BG_MAP_RAM(0), backgroundMapLen);
    dmaCopy(backgroundPal, BG_PALETTE, backgroundPalLen);

    }


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
    oamSet(&oamMain, index, x, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, birdgfx, -1, false, false, false, false, false);
}

void setPipePosition(int index, int x, int y) {
    oamSet(&oamMain, index, x, y, 0, 0, SpriteSize_64x64, SpriteColorFormat_256Color, Pipegfx, -1, false, false, false, false, false);
    oamSet(&oamMain, index+1, x, 0, 0, 0, SpriteSize_64x64, SpriteColorFormat_256Color, Pipegfx, -1, false, false, false, true, false);
}

void setPipePositiondouble(int index, int x, int y, int z ) {
    oamSet(&oamMain, index, x, y, 0, 0, SpriteSize_64x64, SpriteColorFormat_256Color, Pipegfx, -1, false, false, false, false, false);  //DOWN CORRECT


    oamSet(&oamMain, index+1, x, z, 0, 0, SpriteSize_64x64, SpriteColorFormat_256Color, Pipegfx, -1, false, false, false, true, false); //UP CORRECT

    oamSet(&oamMain, index+5, x, -22, 0, 0, SpriteSize_64x64, SpriteColorFormat_256Color, Pipegfx, -1, false, false, false, false, false); //UP CORRECT
    
}




// Fonction pour réinitialiser le jeu en cas de Game Over
void resetGame() {                    // Score réinitialisé
    gameState = GAME_STATE_WAITING; // Retour à l'état d'attente
    birdX = BIRDX_INIT;
    birdY = BIRDY_INIT;

    //resetPipe();
    background = !background;
    consoleClear();                // Efface l'écran de la console
    
}


void displayMenuScreen() {

    // Configure sub-screen with BG0 for text
    REG_DISPCNT = MODE_0_2D | DISPLAY_BG0_ACTIVE;

    // Use VRAM C for sub-screen
    VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;

    // Configure BG0 on the sub-screen
    BGCTRL[0] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(2);

    dmaCopy(MenuTiles, BG_TILE_RAM(2), MenuTilesLen);
    dmaCopy(MenuMap, BG_MAP_RAM(0), MenuMapLen);
    dmaCopy(MenuPal, BG_PALETTE, MenuPalLen);
    

    static bool showMessage = true;
    static int blinkCounter = 0;


    blinkCounter++;
    if (blinkCounter >= 30) {  // Blink every half second
        showMessage = !showMessage;
        blinkCounter = 0;
    }


    if (showMessage) {
        iprintf("\x1b[10;5HPRESS START TO PLAY");
    } else {
        iprintf("\x1b[10;5H                     ");  // Clear text
    }

    
}


void configureSprites(){
     // Map VRAM_B for the bird sprite
    VRAM_B_CR = VRAM_ENABLE | VRAM_B_MAIN_SPRITE_0x06400000;



    oamInit(&oamMain, SpriteMapping_1D_32, false);
    birdgfx = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
    Pipegfx = oamAllocateGfx(&oamMain, SpriteSize_64x64, SpriteColorFormat_256Color);
    //Pipegfx2 = oamAllocateGfx(&oamMain, SpriteSize_64x64, SpriteColorFormat_256Color);

    // Load bird sprite palette and tiles
    dmaCopy(birdPal, SPRITE_PALETTE , birdPalLen); // Load bird palette at index 0
    //dmaCopy(pipe1Pal, &SPRITE_PALETTE[birdPalLen/2], pipe1PalLen);
    dmaCopy(pipe2Pal, &SPRITE_PALETTE[birdPalLen/2], pipe2PalLen);
    //dmaCopy(pipe1Pal, &SPRITE_PALETTE[pipe1PalLen/2], pipe1PalLen);
    dmaCopy(birdTiles, birdgfx, birdTilesLen); // Load bird tiles
    //dmaCopy(pipe1Tiles , Pipegfx, pipe1TilesLen);   // Load pipe tiles
    dmaCopy(pipe2Tiles , Pipegfx, pipe2TilesLen);   // Load pipe tiles
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
        if (pipes[i].x + 90 < 0) {
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

void updateScore_and_Distance() {

    distance = birdX + distance;
    
    for (int i = 0; i < NUM_PIPES; i++){

        if (birdX == pipes[i].x + PIPE_WIDTH && (i % 2 == 0)  ) { // Passed the pipe
            
            score++;
            //iprintf("Score: %d\n", score);
        }
        
    }
 }


void initSubScreen() {

    // Set display control for sub-screen
    REG_DISPCNT_SUB = MODE_0_2D | DISPLAY_BG0_ACTIVE;

    // Enable VRAM for the sub-screen
    VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;

    // Configure BG0 on the sub-screen
    BGCTRL_SUB[0] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(1) | BG_TILE_BASE(1);

    // Load the background graphics
    dmaCopy(SubbgTiles, BG_TILE_RAM_SUB(1), SubbgTilesLen);
    dmaCopy(SubbgMap, BG_MAP_RAM_SUB(1), SubbgMapLen);
    dmaCopy(SubbgPal, BG_PALETTE_SUB, SubbgPalLen);
}

void UpdateSubScreen(){

    // Enable VRAM for the sub-screen background
    VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;

    // Configure BG0 on the sub-screen
    BGCTRL_SUB[0] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(1) | BG_TILE_BASE(2);


    // Load the background for the sub-screen
    dmaCopy(SubGameBgTiles, BG_TILE_RAM_SUB(2), SubGameBgTilesLen);
    dmaCopy(SubGameBgMap, BG_MAP_RAM_SUB(1), SubGameBgMapLen);
    dmaCopy(SubGameBgPal, BG_PALETTE_SUB, SubGameBgPalLen);
}


void displayGameOverScreen() {

    gameState = GAME_STATE_GAME_OVER;


   // Displaying Sub_Game_Over Scren 
    REG_DISPCNT_SUB = MODE_0_2D | DISPLAY_BG0_ACTIVE;

    VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;

    BGCTRL_SUB[0] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(1) | BG_TILE_BASE(3);

    dmaCopy(GameOverTiles, BG_TILE_RAM_SUB(3), GameOverTilesLen);
    dmaCopy(GameOverMap, BG_MAP_RAM_SUB(1), GameOverMapLen);
    dmaCopy(GameOverPal, BG_PALETTE_SUB, GameOverPalLen);

    
}

void displayGameOverPanel(int score, int bestScore, int distance) {
    // Draw the Game Over text
    iprintf("\x1b[5;8H GAME OVER");

    // Draw the box for score and distance
    iprintf("\x1b[7;6H+------------------+");
    iprintf("\x1b[8;6H|   SCORE: %d      |", score);
    iprintf("\x1b[9;6H|   BEST:  %d      |", bestScore);
    iprintf("\x1b[10;6H| DISTANCE: %d m  |", distance);
    iprintf("\x1b[11;6H+------------------+");

    // Instruction to restart
    iprintf("\x1b[13;5HPRESS START TO RESTART");
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
            if (birdX + BIRD_WIDTH > pipes[i].x && birdX < pipes[i].x + PIPE_WIDTH) {
                if (i % 2 == 0) {
                    if (birdY < (pipes[i].y+60)) {
                        displayGameOverScreen();
                        return;
                    }
                } 
                else {
                    if (birdY + BIRD_HEIGHT > pipes[i].y+5) {
                    displayGameOverScreen();
                    return;
                    }
                
                    }
            }
        }
        
        
 }
