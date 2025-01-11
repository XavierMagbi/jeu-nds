// Include necessary headers
#include <nds.h>
#include <stdio.h>
#include <nds/arm9/background.h>
#include "graphics.h"
#include "timer.h"
#include "bird.h"
#include "pipe1.h"
#include "pipe2.h"


#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"






int keys; 

int score = 0;    // Score initial
int distance = 0;


int birdX = BIRDX_INIT; // Center of the screen horizontally
float birdY = BIRDY_INIT ;      // Starts at the ground
int birdVelocity = 0;         // Initial velocity (stationary)
bool isJumping = false;       // Tracks whether the bird is mid-jump

int gameState = GAME_STATE_INIT;



void printPipes() {
    iprintf("----- Pipes List -----\n");
    
    for(int i = 0; i < NUM_PIPES; i++) {
        iprintf("Pipe %d: x = %d, y = %d\n", 
            i, 
            pipes[i].x, 
            pipes[i].y);
                
    }
    

}


int main(){

    consoleDemoInit();

    // Init Backgrounds 
    initMainScreenBackground();
    initSubScreen();


    // Initialization of  sprites 

    configureSprites();
    oamInit(&oamMain, SpriteMapping_1D_32, false);
    gameState = GAME_STATE_WAITING;


    // SOUND 
    //Init the sound library 
    mmInitDefaultMem((mm_addr)soundbank_bin);
    //Load Effect 
    mmLoadEffect(SFX_JUMP);
    mmLoadEffect(SFX_START);
    mmLoadEffect(SFX_GAMEOVER);

    while (1) {
        
        scanKeys();
        keys = keysDown();
        //displayScoreAndDistance(score,distance);

       
        if (gameState == GAME_STATE_WAITING) {
             initSubScreen();
            if (keys & KEY_START) {
                gameState = GAME_STATE_PLAYING;
            }
        }

        if (gameState == GAME_STATE_WAITING) {
            setBirdPosition(SPRITE_BIRD,BIRDX_INIT,BIRDY_INIT);
            initPipes();
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
                birdY += JUMPFORCE ;
                mmEffect(SFX_JUMP); 
            }
            checkCollisions(); // Check for collisions
            setBirdPosition(SPRITE_BIRD,birdX,birdY);

            updatePipes();
            updateScore_and_Distance();
            
            
           
        }
            
        

        if(gameState == GAME_STATE_GAME_OVER){
            mmEffect(SFX_GAMEOVER);

             if (keys & KEY_START){

                resetGame();
             }

        }

    
        swiWaitForVBlank();

        oamUpdate(&oamMain);
    }

    return 0;

}

    


