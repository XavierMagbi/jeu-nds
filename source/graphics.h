#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <nds.h>

// Sprite indices
#define SPRITE_BIRD 0
#define SPRITE_PIPE 1

//Screen dimensions
#define SCREEN_WIDTH	256
#define	SCREEN_HEIGHT	192

//Bird dimensions 
#define	BIRD_WIDTH	32
#define	BIRD_HEIGHT	32



// Graphics Initialization
//void configureBird();

// Sprite Functions
void setBirdPosition(int x, int y);
void setPipePosition(int index, int x, int y);

// Background Initialization
void initBackground();

void updateBackground();

#endif
