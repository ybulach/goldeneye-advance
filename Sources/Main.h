#ifndef MAIN_H
#define MAIN_H

// Les différentes scènes disponibles
typedef enum
{
	MENU_PRINCIPAL = 0,	// Choix du menu suivant, liste des modes de jeu
	MENU_BRIEFING,		// Infos du niveau dans la sauvegarde selectionnée (currentSave)
	MENU_CREDITS,		// Affichage des personnes ayant contribuées au jeu
	
	JEU,				// Le jeu en lui même
	JEU_CHARGEMENT,		// Chargement des données du jeu (niveau, etc...)
	JEU_PAUSE			// Affichage du menu de pause
} Scenes;
extern Scenes scene;

/////////////////
// Sauvegardes //
/////////////////
// Une sauvegarde
typedef struct
{
	// L'identifiant du dernier niveau fini
	int niveau;
} Save;
extern Save sauvegardes[];
extern int currentSave;

#define SAVE_MAGIC	"goldeneye"

#define SAVE_1	9
#define SAVE_2	SAVE_1 + sizeof(int)
#define SAVE_3	SAVE_2 + sizeof(int)
#define SAVE_4	SAVE_3 + sizeof(int)

// Tout sauvegarder
extern void mainSaveAll();

//////////
// Sons //
//////////
//#include "../Sounds/AAS_Data.h"

////////////////
// Graphismes //
////////////////
// Info
extern const unsigned char info_bitmap8[];
extern const unsigned short info_palette[];
// Player-Advance
extern const unsigned char player_advance_bitmap8[][];
extern const unsigned short player_advance_palette[];
// Logo
extern const unsigned char logo_bitmap8[];
extern const unsigned short logo_palette[];
// Menu principal
extern const unsigned char menu_principal_bitmap8[][];
extern const unsigned short menu_principal_palette[];
// Menu Briefing
extern const unsigned char menu_briefing_01_bitmap8[][];
extern const unsigned short menu_briefing_01_palette[];

// sprites
extern const unsigned char tir_tiles[][];
extern const unsigned char curseur_tiles[][];
extern const unsigned char font_tiles[][];
extern const unsigned short interface_palette[];
extern const unsigned char james_bond_tiles[][];
extern const unsigned char scientifique_tiles[][];

/////////////
// Sprites //
/////////////
#define SPRITE_CALC_SIZE(nb)	(nb * 64)	// Taille des sprites en mémoire:	((nombre de blocs de 8x8 pixels) * 64)
#define SPRITE_CALC_BLOC(nb)	(nb * 2)	// Bloc à utiliser:	(numéro du bloc * 2) => +512
#define SPRITE_CALC_OFFSET(nb)	((512 * 16) + ((nb - 512) * 16))	// Le décalage depuis le début des données OAM (OAMData)

#define SPRITE_TIR				512 + SPRITE_CALC_BLOC(0)
#define SPRITE_CURSEUR			512 + SPRITE_CALC_BLOC(1)
#define SPRITE_FONT				512 + SPRITE_CALC_BLOC(5)
#define SPRITE_VIDE				512 + SPRITE_CALC_BLOC(53)
#define SPRITE_JAMES_BOND		512 + SPRITE_CALC_BLOC(54)
#define SPRITE_SCIENTIFIQUE		512 + SPRITE_CALC_BLOC(82)

#endif // MAIN_H
