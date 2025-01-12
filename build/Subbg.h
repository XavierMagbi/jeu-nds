
//{{BLOCK(Subbg)

//======================================================================
//
//	Subbg, 256x192@8, 
//	+ palette 256 entries, not compressed
//	+ 444 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x24 
//	Total size: 512 + 28416 + 1536 = 30464
//
//	Time-stamp: 2025-01-12, 12:05:54
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_SUBBG_H
#define GRIT_SUBBG_H

#define SubbgTilesLen 28416
extern const unsigned int SubbgTiles[7104];

#define SubbgMapLen 1536
extern const unsigned short SubbgMap[768];

#define SubbgPalLen 512
extern const unsigned short SubbgPal[256];

#endif // GRIT_SUBBG_H

//}}BLOCK(Subbg)
