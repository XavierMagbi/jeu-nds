#include <nds.h>

#ifndef GRAPHICS_H
#define GRAPHICS_H


// Sprite indices
#define SPRITE_BIRD 0
#define SPRITE_PIPE 1

//Screen dimensions
#define SCREEN_WIDTH	256
#define	SCREEN_HEIGHT	192

//Bird dimensions 
#define	BIRD_WIDTH	32
#define	BIRD_HEIGHT	32

#define PIPE_WIDTH 32
#define PIPE_HEIGHT 192
#define PIPE_GAP 60
#define NUM_PIPES 4

// Constants of the game 
#define GAME_STATE_WAITING 0
#define GAME_STATE_PLAYING 1
#define GROUNDLEVEL 128
#define JUMPFORCE -10 
#define GRAVITY 1


typedef struct {
    int x;     // Position horizontale
    int y;     // Position du haut du gap
    bool active;
} Pipe;

extern Pipe pipes[NUM_PIPES];

extern int score ;    // Score initial
extern int blinkCounter ;    // Compteur pour gérer le clignotement
extern bool showMessage ; // Indique si le message est affiché

// Bird's variable
extern int birdX; // Center of the screen horizontally
extern float birdY ;      // Starts at the ground
extern float birdX_init ;
extern float birdY_init ;
extern int birdVelocity ;         // Initial velocity (stationary)
extern bool isJumping ;       // Tracks whether the bird is mid-jump

// Global variables 
extern int gameState; // État initial du jeu



// Sprite Functions
void configureBird();
void setBirdPosition(int index,int x, int y);
void setPipePosition(int index, int x, int y);


// Pipes initialization 
void drawPipes();

void initBackground(); // Background Initialization
void updateBackground(); // Scrolling the background 

// Fonctions qui étaient dans le main 

//void initBird();
void initGame();
void setPipePosition(int index, int x, int y);
void resetGame();
void handleInput();
void updateGameLogic();
void displayStartScreen();
void configureBird();
void configurePipe();
void initPipes();
void updatePipes();
void drawPipes();
void checkCollisions();


void SubMenu(); //initialisation SubMenu pour le menu du jeu 
void initSubMenuSprites(); //Initialisation Sprite pour les boutons du menu du bas 



#endif
