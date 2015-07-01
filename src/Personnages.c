////////////////
// Inclusions //
////////////////
#include <Common.h>
#include <Map.h>
#include <Personnages.h>

//////////////////////////////////////////////////
// Il y a 128 sprites au total:					//
// 		0		joueur							//
// 		1-75	ennemis							//
// 		76-100	tirs							//
//		101-127	interface (vies, arme, etc...)	//
//////////////////////////////////////////////////
Sprite sprite[128];

/////////////////////
// jeuResetSprites //
/////////////////////
void jeuResetSprites()
{
	int i;
	
	// Pour chaque sprite du tableau
	for(i = 0; i < 128; i++)
	{
		// On met le sprite en dehors de la map
		sprite[i].x = -240;
		sprite[i].y = -160;
		
		sprite[i].anim = ANIM_MORT;
	}
	
	commonResetSprites();
	
	// Copie des sprites dans la mémoire OAM
	commonCopyOAMBuffer();
}

/////////////////////
// jeuCreateSprite //
/////////////////////
void jeuCreateSprite(int s, int size, int gfx)
{
    sprite[s].x = 0;
    sprite[s].y = 0;
	sprite[s].move = 0;
    sprite[s].anim = ANIM_RIEN;
    sprite[s].anim_cnt = 0;
	sprite[s].gfx = gfx;
	sprite[s].size = size;
	sprite[s].direction = 0;
	sprite[s].vies = 100;
	sprite[s].armure = 0;
	
	int i;
	for(i = 0; i < MAX_ARMES; i++)
		sprite[s].armes[i] = 0;
	sprite[s].current_arme = -1;
	sprite[s].arme_cnt = 100;
	sprite[s].recharge = 0;
	
	OAMBuffer[s].attribute0 = COLOR_256 | SQUARE | sprite[s].y;
	OAMBuffer[s].attribute2 = (sprite[s].gfx + ANIM(s));
	
	if(size == 8)
		OAMBuffer[s].attribute1 = SIZE_8 | sprite[s].x;
	else if(size == 16)
		OAMBuffer[s].attribute1 = SIZE_16 | sprite[s].x;
	else if(size == 32)
		OAMBuffer[s].attribute1 = SIZE_32 | sprite[s].x;
	else if(size == 64)
		OAMBuffer[s].attribute1 = SIZE_64 | sprite[s].x;
}

////////////////////////
// jeuUpdateSpriteGfx //
////////////////////////
void jeuUpdateSpriteGfx(int s)
{
	commonSpriteChangeGfx(s, sprite[s].gfx + ANIM(s), 1);
}

//////////////////////
// jeuUpdateEnnemis //
//////////////////////
void jeuUpdateEnnemis()
{
	int i, x, y;
	
	// Pour chaque ennemi du tableau
	for(i = 1; i < 76; i++)
	{
		// Si le personnage est vivant
		if(sprite[i].anim != ANIM_MORT)
		{
			x = sprite[i].x - backgroundX;
			y = sprite[i].y - backgroundY;
			
			// Si il est sur l'écran seulement
			if((x < 240) && (x > 0) && (y < 160) && (y > 0))
			{
				commonSpriteChangePos(i, x, y);
				
				///////////////////////////////////
				// Intelligence Artificielle ICI //
				///////////////////////////////////
			}
			else
				commonSpriteChangePos(i, 240, 160);
		}
		// Sinon on le met en dehors de l'écran
		else
			commonSpriteChangePos(i, 240, 160);
	}
}

////////////////////////
// jeuPersonnageColUp //
////////////////////////
int jeuPersonnageColUp(int s)
{
	if(	(jeuGetTile(sprite[s].x + 2, sprite[s].y + (sprite[s].size >> 1)) != COL_ALL) && (jeuGetTile(sprite[s].x + 2, sprite[s].y + (sprite[s].size >> 1)) != COL_TIR)
			&& (jeuGetTile(sprite[s].x + (sprite[s].size >> 1), sprite[s].y + (sprite[s].size >> 1)) != COL_ALL) && (jeuGetTile(sprite[s].x + (sprite[s].size >> 1), sprite[s].y + (sprite[s].size >> 1)) != COL_TIR)
			&& (jeuGetTile(sprite[s].x + sprite[s].size - 2, sprite[s].y + (sprite[s].size >> 1)) != COL_ALL) && (jeuGetTile(sprite[s].x + sprite[s].size - 2, sprite[s].y + (sprite[s].size >> 1)) != COL_TIR)	)
		return 0;
	return 1;
}

//////////////////////////
// jeuPersonnageColDown //
//////////////////////////
int jeuPersonnageColDown(int s)
{
	if(	(jeuGetTile(sprite[s].x + 2, sprite[s].y + sprite[s].size) != COL_ALL) && (jeuGetTile(sprite[s].x + 2, sprite[s].y + sprite[s].size) != COL_TIR)
			&& (jeuGetTile(sprite[s].x + (sprite[s].size >> 1), sprite[s].y + sprite[s].size) != COL_ALL) && (jeuGetTile(sprite[s].x + (sprite[s].size >> 1), sprite[s].y + sprite[s].size) != COL_TIR)
			&& (jeuGetTile(sprite[s].x + sprite[s].size - 2, sprite[s].y + sprite[s].size) != COL_ALL) && (jeuGetTile(sprite[s].x + sprite[s].size - 2, sprite[s].y + sprite[s].size) != COL_TIR)	)
		return 0;
	return 1;
}

//////////////////////////
// jeuPersonnageColLeft //
//////////////////////////
int jeuPersonnageColLeft(int s)
{
	if(		(jeuGetTile(sprite[s].x, sprite[s].y + (sprite[s].size >> 1) + 2) != COL_ALL) && (jeuGetTile(sprite[s].x, sprite[s].y + (sprite[s].size >> 1) + 2) != COL_TIR)
			&& (jeuGetTile(sprite[s].x, sprite[s].y + sprite[s].size - 2) != COL_ALL) && (jeuGetTile(sprite[s].x, sprite[s].y + sprite[s].size - 2) != COL_TIR)	)
		return 0;
	return 1;
}

///////////////////////////
// jeuPersonnageColRight //
///////////////////////////
int jeuPersonnageColRight(int s)
{
	if(		(jeuGetTile(sprite[s].x + sprite[s].size, sprite[s].y + (sprite[s].size >> 1) + 2) != COL_ALL) && (jeuGetTile(sprite[s].x + sprite[s].size, sprite[s].y + (sprite[s].size >> 1) + 2) != COL_TIR)
			&& (jeuGetTile(sprite[s].x + sprite[s].size, sprite[s].y + sprite[s].size - 2) != COL_ALL) && (jeuGetTile(sprite[s].x + sprite[s].size, sprite[s].y + sprite[s].size - 2) != COL_TIR)	)
		return 0;
	return 1;
}
