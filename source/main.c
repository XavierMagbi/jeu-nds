// Include necessary headers
#include <nds.h>
#include <stdio.h>
#include <nds/arm9/background.h>
#include "graphics.h"
#include "bird.h"
#include "pipe1.h"
#include "pipe2.h"


int keys; 

int score = 0;    // Score initial
int blinkCounter = 0;    // Compteur pour gérer le clignotement
bool showMessage = true; // Indique si le message est affiché

int birdX = SCREEN_WIDTH / 2; // Center of the screen horizontally
float birdY = SCREEN_HEIGHT / 2;      // Starts at the ground
float birdX_init = SCREEN_WIDTH / 2;
float birdY_init = SCREEN_HEIGHT / 2;
int birdVelocity = 0;         // Initial velocity (stationary)
bool isJumping = false;       // Tracks whether the bird is mid-jump

int gameState = GAME_STATE_WAITING;


int main(){

    initBackground();
    configureSprites();
    oamInit(&oamMain, SpriteMapping_1D_32, false);
    gameState = GAME_STATE_WAITING;

    while (1) {
        
        scanKeys();
        keys = keysDown();

       
        if (gameState == GAME_STATE_WAITING) {
            
            if (keys & KEY_START) {
                gameState = GAME_STATE_PLAYING;
            }
        }

        if (gameState == GAME_STATE_WAITING) {
            setBirdPosition(SPRITE_BIRD,birdX_init,birdY_init);
            setPipePosition(SPRITE_PIPE ,PIPE_INIT_X,PIPE_INIT_Y);
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
            
            if (birdY >= GROUNDLEVEL) {
                resetGame();
            } 

            
            setBirdPosition(SPRITE_BIRD,birdX,birdY);
            updatePipes();
        }

    
        swiWaitForVBlank();

        oamUpdate(&oamMain);
    }

    return 0;
}


