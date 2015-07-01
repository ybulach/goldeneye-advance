#ifndef PERSONNAGES_H
#define PERSONNAGES_H

#include <Armes.h>

// Mise à zéro des sprites
void jeuResetSprites();

// Création d'un sprite
void jeuCreateSprite(int s, int size, int gfx);

// Mise à jour d'un sprite
void jeuUpdateSpriteGfx(int s);

// Mise à jour des ennemis
void jeuUpdateEnnemis();

// Colisions d'un personnages avec la map
int jeuPersonnageColUp(int s);
int jeuPersonnageColDown(int s);
int jeuPersonnageColLeft(int s);
int jeuPersonnageColRight(int s);

/////////////
// Sprites //
/////////////
// La structure des données d'un sprite
typedef struct {
    int x;			// Position en x du sprite
    int y;			// Position en y du sprite
	int move;		// Il est en mouvement (on doit faire l'animation) ou pas
    int anim;		// Animation courrante
    int anim_cnt;	// Compteur (timer) pour l'animation
    int gfx;		// Le sprite
    int size;		// La taille du sprite (en pixels)
	int direction;	// Le sens du sprite (0 = droite, 1 = gauche)
	int vies;		// Le nombre de vies du sprite
	int armure;		// Le nombre de points d'armure du sprite
	
	int armes[MAX_ARMES];	// Les armes en possession ou non
	int current_arme;		// L'arme en cours d'utilisation (-1 pour aucune)
	int arme_cnt;			// Le compteur (timer) pour les tirs
	int recharge;			// Rechargement de l'arme en cours ou non
} Sprite;
extern Sprite sprite[128];

// L'identifiant du sprite de James Bond
#define JAMES_BOND	0

// Les différentes animations des sprites
#define ANIM(s)	SPRITE_CALC_BLOC(sprite[s].anim * ((sprite[s].size >> 3) * (sprite[s].size >> 3)))
enum
{
	ANIM_RIEN = 0,
	ANIM_MARCHE1,
	ANIM_MARCHE2,
	ANIM_MARCHE3,
	ANIM_MORT
};

#endif // PERSONNAGES_H
