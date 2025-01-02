#include <nds.h>

#ifndef GRAPHICS_H
#define GRAPHICS_H

// Constants of the game 
#define GAME_STATE_WAITING 0
#define GAME_STATE_PLAYING 1
#define GROUNDLEVEL 128
#define JUMPFORCE -10 
#define GRAVITY 1

// Sprite indices
#define SPRITE_BIRD 0
#define SPRITE_PIPE 1

//Screen dimensions
#define SCREEN_WIDTH	256
#define	SCREEN_HEIGHT	192

//Bird dimensions 
#define	BIRD_WIDTH	32
#define	BIRD_HEIGHT	32

// Bird's coordinates 
#define BIRDX_INIT 0
#define BIRDY_INIT SCREEN_HEIGHT / 2


// Pipes Dimensions & Variables 
#define PIPE_WIDTH 52
#define PIPE_HEIGHT 64
#define PIPE_GAP 60
#define NUM_PIPES 2
#define PIPE_INIT_X 140
#define PIPE_INIT_Y GROUNDLEVEL- 32



typedef struct {
    int x;            // Position horizontale du pipe
    int y;            // Position verticale du haut du gap
    int width;        // Largeur du pipe
    int height;       // Hauteur du pipe (si nécessaire)
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
void configureSprites();
void initPipes();
void updatePipes();
void checkCollisions();


void SubMenu(); //initialisation SubMenu pour le menu du jeu 
void initSubMenuSprites(); //Initialisation Sprite pour les boutons du menu du bas 



#endif
