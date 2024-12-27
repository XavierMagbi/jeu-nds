#include "graphics.h"
#include <nds/arm9/background.h>
#include "ball.h"
#include "background2.h" // GRIT file for background tiles


// Global variables 

int scrollX = 0;
 

void initBackground() {

    REG_DISPCNT = MODE_0_2D | DISPLAY_BG0_ACTIVE;

    VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;

    BGCTRL[0] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(2);

    dmaCopy(background2Tiles, BG_TILE_RAM(2), background2TilesLen);
    dmaCopy(background2Map, BG_MAP_RAM(0), background2MapLen);
    dmaCopy(background2Pal, BG_PALETTE, background2PalLen);
}


void updateBackground() {
    scrollX = (scrollX + 1) % 256; // Wrap around when reaching the end
    REG_BG0HOFS = scrollX;         // Update horizontal offset
}


/*
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


void setBirdPosition(int x, int y) {
    oamSet(&oamMain, 0, x, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, gfx, -1, false, false, false, false, false);
}

void setPipePosition(int index, int x, int y) {
    oamSet(&oamMain, SPRITE_PIPE + index, x, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, SPRITE_GFX + birdTilesLen, -1, false, false, false, false, false);
}
*/




