// Include necessary headers
#include <nds.h>
#include <stdio.h>
#include <nds/arm9/background.h>
#include "graphics.h"
#include "timer.h"


// Library for Sounds
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"


int keys; 

// Variables for Game
int score = 0;    
int distance = 0;
static bool gameover = false;
static bool music_start = false;

// Variables of the bird 
int birdX = BIRDX_INIT; // Center of the screen horizontally
float birdY = BIRDY_INIT ;      // Starts at the ground
int birdVelocity = 0;         // Initial velocity (stationary)
bool isJumping = false;       // Tracks whether the bird is mid-jump



int gameState = GAME_STATE_INIT; // Game's State



void checkTouchInput(mm_sound_effect jumpSound) {
    touchPosition touch;

    if (keys & KEY_TOUCH) {
        touchRead(&touch);

        // Check if Flappy on the sub-screen is touched
        if (touch.px >= 70 && touch.px <= 170 && touch.py >= 60 && touch.py <= 120) {
            // Trigger jump in the main game
            birdY += JUMPFORCE;
            mmEffectEx(&jumpSound);   // Play jump sound effect
        }
        
    }
}

int main(){

    consoleDemoInit();

   
   

    // SOUND 

    //Init the sound library 
    mmInitDefaultMem((mm_addr)soundbank_bin);
    //Load Effect 
    mmLoadEffect(SFX_JUMP);
    mmLoadEffect(SFX_START);
    mmLoadEffect(SFX_GAMEOVER);
    mmLoad(MOD_MUSIC);

    mm_sound_effect jumpSound = {
    { SFX_JUMP }, // Sound ID
    (int)(1.0f * (1 << 10)), 
    0, // Handle
    50, // Volume 
    128 // Panning 
};

    gameState = GAME_STATE_MENU;
    

    while (1) {
        
        scanKeys();
        keys = keysDown();
       
        
    if (gameState == GAME_STATE_MENU) {
        
        displayMenuScreen();
        
        if (keys & KEY_START) {
            consoleClear();
           
            irqEnable(IRQ_TIMER0);
            gameState = GAME_STATE_INIT;
            
        }
    }

    if(gameState == GAME_STATE_INIT){


             // Init Backgrounds
             initMainScreenBackground();
             

             // Configuration of  sprites 
             configureSprites();
             oamInit(&oamMain, SpriteMapping_1D_32, false);

             initSubScreen(); // Init the Subbackground

             //Initialization of pipes
             setBirdPosition(SPRITE_BIRD,BIRDX_INIT,BIRDY_INIT);
             initPipes();
             setPipePosition(SPRITE_PIPE ,PIPE_INIT_X,PIPE_INIT_Y);

             gameState = GAME_STATE_WAITING;
    }
    
    if (gameState == GAME_STATE_WAITING) {
            if (!music_start) {
            mmStart(MOD_MUSIC,MM_PLAY_LOOP);
            mmSetModuleVolume(100);
            music_start = true;
            }



            if ((keys & KEY_B) || (keys & KEY_TOUCH)) {
                gameState = GAME_STATE_PLAYING;
                irqEnable(IRQ_TIMER0);
                initScrollTimer();
                
            }
        }
        if (gameState == GAME_STATE_PLAYING) {

            updateBackground();
            UpdateSubScreen(); 
                   



            if (birdY < GROUNDLEVEL) {
                birdY += 0.5;
            } 
            else {
                birdY = GROUNDLEVEL; 
            }

            checkTouchInput(jumpSound);

            
            if ((keys & KEY_B) && birdY > 0) {
                
                mmEffectEx(&jumpSound); 
                birdY += JUMPFORCE ;
            }

            checkCollisions(); // Check for collisions
            setBirdPosition(SPRITE_BIRD,birdX,birdY);

            updatePipes(&distance);
            updateScore(); 
        }

        if(gameState == GAME_STATE_GAME_OVER){
            
            displayGameOverPanel();
            if (!gameover) {
            mmEffect(SFX_GAMEOVER);
            gameover = true;
        }


             if (keys & KEY_START){
                music_start = false;
                gameover = false;
                distance = 0;
                resetGame();
             }

        }
        swiWaitForVBlank();

        oamUpdate(&oamMain);
    }

    return 0;

}

    


