
//{{BLOCK(SubGameBg)

//======================================================================
//
//	SubGameBg, 256x192@8, 
//	+ palette 256 entries, not compressed
//	+ 681 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x24 
//	Total size: 512 + 43584 + 1536 = 45632
//
//	Time-stamp: 2025-01-12, 12:05:54
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_SUBGAMEBG_H
#define GRIT_SUBGAMEBG_H

#define SubGameBgTilesLen 43584
extern const unsigned int SubGameBgTiles[10896];

#define SubGameBgMapLen 1536
extern const unsigned short SubGameBgMap[768];

#define SubGameBgPalLen 512
extern const unsigned short SubGameBgPal[256];

#endif // GRIT_SUBGAMEBG_H

//}}BLOCK(SubGameBg)
