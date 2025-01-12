
//{{BLOCK(background)

//======================================================================
//
//	background, 256x192@8, 
//	+ palette 256 entries, not compressed
//	+ 453 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x24 
//	Total size: 512 + 28992 + 1536 = 31040
//
//	Time-stamp: 2025-01-12, 12:05:54
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BACKGROUND_H
#define GRIT_BACKGROUND_H

#define backgroundTilesLen 28992
extern const unsigned int backgroundTiles[7248];

#define backgroundMapLen 1536
extern const unsigned short backgroundMap[768];

#define backgroundPalLen 512
extern const unsigned short backgroundPal[256];

#endif // GRIT_BACKGROUND_H

//}}BLOCK(background)
