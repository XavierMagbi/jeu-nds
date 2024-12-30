/*
// Include necessary headers
#include <nds.h>
#include <stdio.h>
#include <nds/arm9/background.h>
#include "graphics.h"
#include "ball.h"

// Constants of the game 
#define GAME_STATE_WAITING 0
#define GAME_STATE_PLAYING 1

// Global variables 
int gameState = GAME_STATE_WAITING; // État initial du jeu
int score = 0;                      // Score initial
int blinkCounter = 0;    // Compteur pour gérer le clignotement
bool showMessage = true; // Indique si le message est affiché

// Bird's variable
const int gravity = 1;       // Gravity value (increase for faster falling)
const int jumpForce = -10;   // Jump force (negative value for upward movement)
const int groundLevel = SCREEN_HEIGHT - BIRD_HEIGHT; // Ground position
int birdX = SCREEN_WIDTH / 2; // Center of the screen horizontally
int birdY = SCREEN_HEIGHT / 2;      // Starts at the ground
int birdVelocity = 0;         // Initial velocity (stationary)
bool isJumping = false;       // Tracks whether the bird is mid-jump


 

 u16 *gfx;


//Functions 

//void initBird();
void initGame();
void resetGame();
void handleInput();
void updateGameLogic();
void displayStartScreen();
void configureBird();


int keys; 

int main(){

	initBackground();
	configureBird();

	while(1){

		updateBackground();

		scanKeys();
		keys =  keysDown();

		if(birdY < (groundLevel)){birdY+=1;}
		
		else if((keys & KEY_A) && (birdY < (groundLevel))) birdY-=jumpForce;
		//if((keys & KEY_B) && (birdY  > 0)) birdY-=2;

		 oamSet(&oamMain, 0, birdX, birdY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, gfx, -1, false, false, false, false, false);
		
	
		
		swiWaitForVBlank();
		
		
		
		//handleInput();
		//updateGameLogic();
		oamUpdate(&oamMain);

	}

	return 0;
  
}




// Fonction pour initialiser l'oiseau

/*
void initBird(){
    birdX = 0;            // Position X fixe de l'oiseau
    birdY = 0;            // Position Y initiale
    //birdVelocity = 0;      // Vitesse initiale

    setBirdPosition(birdX, birdY); // Met le sprite de l'oiseau à jour
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
    //initBird();                    // Réinitialise l'oiseau

    consoleClear();                // Efface l'écran de la console
    iprintf("Appuyez sur A pour rejouer\n");
}

void handleInput() {
    
return ; 	
}

void updateGameLogic() {
    birdVelocity += gravity;
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

void configureBird() {
    VRAM_B_CR = VRAM_ENABLE | VRAM_B_MAIN_SPRITE_0x06400000 ;

    oamInit(&oamMain, SpriteMapping_1D_32, false);

    //Allocate space for the graphic to show in the sprite
	gfx = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);

    // Load bird sprite
    swiCopy(ballPal, SPRITE_PALETTE, ballPalLen/2);
    swiCopy(ballTiles, gfx, ballTilesLen/2);

    // Load pipe sprite
    //swiCopy(pipesTiles, SPRITE_GFX + birdTilesLen, pipesTilesLen);
    //swiCopy(pipesPal, SPRITE_PALETTE + birdPalLen, pipesPalLen);

}
*/




// Include necessary headers
#include <nds.h>
#include <stdio.h>
#include <nds/arm9/background.h>
#include "graphics.h"
#include "ball.h"
#include "pipess.h"

// Constants of the game 
#define GAME_STATE_WAITING 0
#define GAME_STATE_PLAYING 1

// Global variables 
int gameState = GAME_STATE_WAITING; // État initial du jeu
int score = 0;                      // Score initial
int blinkCounter = 0;    // Compteur pour gérer le clignotement
bool showMessage = true; // Indique si le message est affiché

// Bird's variable
const int gravity = 1;       // Gravity value (increase for faster falling)
const int jumpForce = -10;   // Jump force (negative value for upward movement)
const int groundLevel = SCREEN_HEIGHT - BIRD_HEIGHT; // Ground position
int birdX = SCREEN_WIDTH / 2; // Center of the screen horizontally
float birdY = SCREEN_HEIGHT / 2;      // Starts at the ground
float birdX_init = SCREEN_WIDTH / 2;
float birdY_init = SCREEN_HEIGHT / 2;
int birdVelocity = 0;         // Initial velocity (stationary)
bool isJumping = false;       // Tracks whether the bird is mid-jump


 

u16 *gfx;
u16 *Pipegfx;


//Functions 

//void initBird();
void initGame();
void resetGame();
void handleInput();
void updateGameLogic();
void displayStartScreen();
void configureBird();


int keys; 

int main() {
   
    initBackground();
    configureBird();
    //configurePipe();
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

        
        //updateBackground();

        
        if (gameState == GAME_STATE_WAITING) {
            oamSet(&oamMain, 0, birdX_init, birdY_init, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, gfx, -1, false, false, false, false, false);
        }

       
        if (gameState == GAME_STATE_PLAYING) {
            updateBackground();
            if (birdY < groundLevel) {
                birdY += 0.5;
            } 
            else {
                birdY = groundLevel; 
            }

            
            if ((keys & KEY_B) && birdY > 0) {
                birdY += jumpForce; 
            }
            
            if (birdY >= groundLevel) {
                resetGame();
            } 

            
            oamSet(&oamMain, 0, birdX, birdY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, gfx, -1, false, false, false, false, false);
            //oamSet(&oamMain, 1, 120, 120, 0, 1, SpriteSize_32x32, SpriteColorFormat_256Color, Pipegfx, -1, false, false, false, false, false);
        }

        
        swiWaitForVBlank();

        oamUpdate(&oamMain);
    }

    return 0;
}



// Fonction pour initialiser l'oiseau


void initBird(){
    birdX = birdX_init;            // Position X fixe de l'oiseau
    birdY = birdY_init;            // Position Y initiale
    //birdVelocity = 0;      // Vitesse initiale

    //setBirdPosition(birdX, birdY); // Met le sprite de l'oiseau à jour
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
    initBird();                    // Réinitialise l'oiseau

    consoleClear();                // Efface l'écran de la console
    iprintf("Appuyez sur A pour rejouer\n");
}

void handleInput() {
    
return ; 	
}

void updateGameLogic() {
    birdVelocity += gravity;
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

void configureBird() {
    // Map VRAM_B for the bird sprite
    VRAM_B_CR = VRAM_ENABLE | VRAM_B_MAIN_SPRITE_0x06400000;

    // Allocate space for the bird graphic
    gfx = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);

    // Load bird sprite palette and tiles
    swiCopy(ballPal, SPRITE_PALETTE + 0, ballPalLen / 2); // Load bird palette at index 0
    swiCopy(ballTiles, gfx, ballTilesLen / 2);            // Load bird tiles
}

void configurePipe() {
    // Map VRAM_C for the pipe sprite
    VRAM_C_CR = VRAM_ENABLE | VRAM_C_MAIN_BG_0x06040000;

    // Allocate space for the pipe graphic
    Pipegfx = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);

    // Load pipe sprite palette and tiles
    swiCopy(pipessPal, SPRITE_PALETTE + 32, pipessPalLen / 2); // Load pipe palette at index 1
    swiCopy(pipessTiles, Pipegfx, pipessTilesLen / 2);         // Load pipe tiles
}
