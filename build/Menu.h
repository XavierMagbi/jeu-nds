
//{{BLOCK(Menu)

//======================================================================
//
//	Menu, 256x192@8, 
//	+ palette 256 entries, not compressed
//	+ 237 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x24 
//	Total size: 512 + 15168 + 1536 = 17216
//
//	Time-stamp: 2025-01-12, 12:05:54
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_MENU_H
#define GRIT_MENU_H

#define MenuTilesLen 15168
extern const unsigned int MenuTiles[3792];

#define MenuMapLen 1536
extern const unsigned short MenuMap[768];

#define MenuPalLen 512
extern const unsigned short MenuPal[256];

#endif // GRIT_MENU_H

//}}BLOCK(Menu)
