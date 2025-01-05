// Include necessary headers
#include <nds.h>
#include <stdio.h>
#include <nds/arm9/background.h>
#include "graphics.h"
#include "timer.h"
#include "bird.h"
#include "pipe1.h"
#include "pipe2.h"


int keys; 

int score = 0;    // Score initial
bool showMessage = false ; 
int blinkCounter = 0 ; 

int birdX = BIRDX_INIT; // Center of the screen horizontally
float birdY = BIRDY_INIT ;      // Starts at the ground
int birdVelocity = 0;         // Initial velocity (stationary)
bool isJumping = false;       // Tracks whether the bird is mid-jump

int gameState = GAME_STATE_INIT;



void printPipes() {
    iprintf("----- Pipes List -----\n");
    
    for(int i = 0; i < NUM_PIPES; i++) {
        iprintf("Pipe %d: x = %d, y = %d\n", 
            i+1, 
            pipes[i].x, 
            pipes[i].y);
                
    }
    
    //iprintf("BIRD: x = %d, y = %d\n", birdX, (int)birdY);
    
/*
    int index = 0; // Initialize an index variable

for (int i = 0; i < NUM_PIPES; i++) {
    int sprite_index = 1 + (i * 2); // Calculate the sprite index
    
    // Print pipe details
    iprintf("Pipe %d: sprite_index = %d, x = %d, y = %d\n", 
            index + 1,         // Use the local index
            sprite_index,      // Sprite index
            pipes[i].x,        // Pipe x-coordinate
            pipes[i].y);       // Pipe y-coordinate
    
    index++; // Increment index
}
*/



    iprintf("----------------------\n");
}




int main(){
    consoleDemoInit();
    initBackground();
    initSpeedTimer();
    initTimer();
    configureSprites();
    oamInit(&oamMain, SpriteMapping_1D_32, false);
    gameState = GAME_STATE_WAITING;

    while (1) {
        
        scanKeys();
        keys = keysDown();

       
        if (gameState == GAME_STATE_WAITING) {
            //setBirdPosition(SPRITE_BIRD,BIRDX_INIT,BIRDY_INIT);
            //setPipePosition(SPRITE_PIPE ,PIPE_INIT_X,PIPE_INIT_Y);
            if (keys & KEY_START) {
                gameState = GAME_STATE_PLAYING;
            }
        }

        if (gameState == GAME_STATE_WAITING) {
            setBirdPosition(SPRITE_BIRD,BIRDX_INIT,BIRDY_INIT);
            initPipes();
            setPipePosition(SPRITE_PIPE ,PIPE_INIT_X,PIPE_INIT_Y);
            //resetPipe();
            //printPipes();
            
        }

       
        if (gameState == GAME_STATE_PLAYING) {
            updateBackground();  
            if (birdY < GROUNDLEVEL) {
                birdY += 0.5;
            } 
            else {
                birdY = GROUNDLEVEL; 
            }

            
            if ((keys & KEY_B) && birdY > 0) {
                birdY += JUMPFORCE; 
            }

            checkCollisions(); // Check for collisions
            setBirdPosition(SPRITE_BIRD,birdX,birdY);

            updatePipes();
            //updateScore();
            printPipes(); 
        }

        if(gameState == GAME_STATE_GAME_OVER){

             if (keys & KEY_START){

                resetGame();
             }

        }

    
        swiWaitForVBlank();

        oamUpdate(&oamMain);
    }

    return 0;
}

