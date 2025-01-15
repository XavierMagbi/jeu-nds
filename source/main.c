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

// Variables of the bird 
int birdX = BIRDX_INIT; // Center of the screen horizontally
float birdY = BIRDY_INIT ;      // Starts at the ground
int birdVelocity = 0;         // Initial velocity (stationary)
bool isJumping = false;       // Tracks whether the bird is mid-jump



int gameState = GAME_STATE_INIT; // Game's State



void checkTouchInput() {
    touchPosition touch;
    scanKeys();
    int keys = keysDown();
    
    if (keys & KEY_TOUCH) {
        touchRead(&touch);

        // Check if Flappy on the sub-screen is touched
        if (touch.px >= 112 && touch.px <= 144 && touch.py >= 96 && touch.py <= 128) {
            // Trigger jump in the main game
            birdY += JUMPFORCE;
            mmEffect(SFX_JUMP);  // Play jump sound effect
        }
    }
}

int main(){

    consoleDemoInit();

    //Init the Timer to increase the speed of the game 
    //initSpeedTimer(); *****YOUR TIMER
    //////MY TIMER BEGIN
    irqInit();               // Initialize the interrupt system
    irqEnable(IRQ_VBLANK);   // Enable V-Blank interrupt (commonly used)
    irqEnable(IRQ_KEYS);     // Enable keypad interrupt
    REG_IME = 1; 
    //////END

    // SOUND 

    //Init the sound library 
    mmInitDefaultMem((mm_addr)soundbank_bin);
    //Load Effect 
    mmLoadEffect(SFX_JUMP);
    mmLoadEffect(SFX_START);
    mmLoadEffect(SFX_GAMEOVER);
    mmLoadEffect(SFX_INTRO);

    gameState = GAME_STATE_MENU;
    initScrollTimer();



    while (1) {
        
        scanKeys();
        keys = keysDown();
        
    if (gameState == GAME_STATE_MENU) {
        
        static bool introPlayed = false;
        
        if (!introPlayed) {
            mmEffect(SFX_INTRO);
            introPlayed = true;
        }
        
        displayMenuScreen();
        
        if (keys & KEY_START) {
            consoleClear();
            mmEffect(SFX_START);
            irqEnable(IRQ_TIMER0);
            gameState = GAME_STATE_INIT;
        }
    }

    if(gameState == GAME_STATE_INIT){
        
             

             // Init Backgrounds
             initMainScreenBackground();
             //initSubScreen();

           
             // Configuration of  sprites 
             configureSprites();
             oamInit(&oamMain, SpriteMapping_1D_32, false);

             //Initialization of pipes
             setBirdPosition(SPRITE_BIRD,BIRDX_INIT,BIRDY_INIT);
             initPipes();
             setPipePosition(SPRITE_PIPE ,PIPE_INIT_X,PIPE_INIT_Y);

             gameState = GAME_STATE_WAITING;
    }
    
    if (gameState == GAME_STATE_WAITING) {

            if (keys & KEY_A) {
                gameState = GAME_STATE_PLAYING;
                irqEnable(IRQ_TIMER0);
            }
        }
        if (gameState == GAME_STATE_PLAYING) {

            //speedTimerISR();
            updateBackground();
            //UpdateSubScreen(); 
    
            if (birdY < GROUNDLEVEL) {
                birdY += 0.5;
            } 
            else {
                birdY = GROUNDLEVEL; 
            }

            checkTouchInput();

            
            if ((keys & KEY_B) && birdY > 0) {
                birdY += JUMPFORCE ;
                mmEffect(SFX_JUMP); 
            }
            checkCollisions(); // Check for collisions
            setBirdPosition(SPRITE_BIRD,birdX,birdY);

            updatePipes(&distance);
            updateScore();
            
            
           
        }
            
        

        if(gameState == GAME_STATE_GAME_OVER){
            displayGameOverPanel();
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

    


