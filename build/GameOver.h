
//{{BLOCK(GameOver)

//======================================================================
//
//	GameOver, 256x192@8, 
//	+ palette 256 entries, not compressed
//	+ 149 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x24 
//	Total size: 512 + 9536 + 1536 = 11584
//
//	Time-stamp: 2025-01-12, 12:05:54
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_GAMEOVER_H
#define GRIT_GAMEOVER_H

#define GameOverTilesLen 9536
extern const unsigned int GameOverTiles[2384];

#define GameOverMapLen 1536
extern const unsigned short GameOverMap[768];

#define GameOverPalLen 512
extern const unsigned short GameOverPal[256];

#endif // GRIT_GAMEOVER_H

//}}BLOCK(GameOver)
