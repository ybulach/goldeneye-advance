#ifndef MAP_H
#define MAP_H

// Chargement d'un niveau
void jeuLoadLevel(int level);

// Récupération d'un tile
u16 jeuGetTile(int x, int y);

// Affichage de la map
void jeuUpdateBackground();

// Centre la caméra sur le joueur en tenant compte de la map
void jeuFocusCam(int s);

#define CharBaseBlock(n)	(0x6000000 | ((n)*0x4000))
#define ScreenBaseBlock(n)	(0x6000000 | ((n)*0x800))
//#define CharBaseBlock(n)		(((n) * 0x4000) + 0x6000000)
//#define ScreenBaseBlock(n)		(((n) * 0x800)  + 0x6000000)

// Les dimensions de la map
extern int MAP_WIDTH;
extern int MAP_HEIGHT;

// Variables qui contiennent les anciennes positions traitées
int backgroundX;
int backgroundY;

// Les pointeurs vers les maps en cours
u16* map_fond;
u16* map_plan;
u16* map_col;

// Les différents blocs de colision
#define COL_NONE	0x0000
#define COL_ALL		0x0001
#define COL_TIR		0x0002
#define COL_DEAD	0x0003

// exemple
extern const unsigned short exemple_palette[];
extern const unsigned char* exemple_tiles[];
extern const unsigned short* exemple_fond_map[];
extern const unsigned short* exemple_plan_map[];
extern const unsigned short* exemple_col_map[];

// dam
extern const unsigned short dam_palette[];
extern const unsigned char* dam_tiles[];
extern const unsigned short* dam_fond_map[];
extern const unsigned short* dam_plan_map[];
extern const unsigned short* dam_col_map[];

#endif // MAP_H
