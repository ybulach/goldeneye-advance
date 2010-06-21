////////////////
// Inclusions //
////////////////
#include "../../Common/Common.h"
#include "Map.h"
#include "../Personnages/Personnages.h"

int MAP_WIDTH;
int MAP_HEIGHT;

// Variables qui contiennent les anciennes positions traitées
int backgroundX = 0, backgroundY = 0;

// Les pointeurs vers les maps en cours
u16* map_fond;
u16* map_plan;
u16* map_col;

//////////////////
// jeuLoadLevel //
//////////////////
void jeuLoadLevel(int level)
{
	REG_BG2CNT = 2 | BG_COLORS_256 | TXTBG_SIZE_256x256 | (0 << 2) | (30 << 8);
	REG_BG1CNT = 0 | BG_COLORS_256 | TXTBG_SIZE_256x256 | (0 << 2) | (31 << 8);
	
	switch(level)
	{
		// DAM
		case 0:
			MAP_WIDTH = 325;
			MAP_HEIGHT = 20;
			
			// La palette des maps
			commonDMACopy((void*)dam_palette, (void*)palette, 256, DMA_16NOW);
			// Les tiles des maps
			commonDMACopy((void*)dam_tiles, (void*)CharBaseBlock(0), 1024 << 5, DMA_16NOW);
			
			// Chargement de la map
			map_fond = dam_fond_map;
			map_plan = dam_plan_map;
			
			map_col = dam_col_map;
			
			// On joue la musique du niveau
			AdpcmStart(&ADPCM_dam, -1, 0);
			break;
		case 1:
			MAP_WIDTH = 256;
			MAP_HEIGHT = 64;
			
			// La palette des maps
			commonDMACopy((void*)exemple_palette, (void*)palette, 256, DMA_16NOW);
			// Les tiles des maps
			commonDMACopy((void*)exemple_tiles, (void*)CharBaseBlock(0), 1024 << 3, DMA_16NOW);
			
			// Chargement de la map
			map_fond = exemple_fond_map;
			map_plan = exemple_plan_map;
			
			map_col = exemple_col_map;
			break;
		default:
			scene = MENU_BRIEFING;
			break;
	}
}

////////////////
// jeuGetTile //
////////////////
u16 jeuGetTile(int x, int y)
{
	return map_col[(x >> 3) + ((y >> 3) * MAP_WIDTH)];
}

/////////////////////////
// jeuUpdateBackground //
/////////////////////////
void jeuUpdateBackground()
{
	// On calcul les dimensions à copier
	int copyWidth = (backgroundX + 32 > MAP_WIDTH) ? (MAP_WIDTH - (backgroundX >> 3)) : (32);
	int copyHeight = (backgroundY + 32 > MAP_HEIGHT) ? (MAP_HEIGHT - (backgroundY >> 3)) : (32);
	
	// On traite chaque ligne
	int i;
	for(i = 0; i < copyHeight; i++)
	{
		commonDMACopy((void*)map_fond + (((backgroundX >> 3) + ((backgroundY >> 3) * MAP_WIDTH) + (i * MAP_WIDTH)) << 1), (void*)ScreenBaseBlock(30) + (i << 6), copyWidth, DMA_16NOW);
		commonDMACopy((void*)map_plan + (((backgroundX >> 3) + ((backgroundY >> 3) * MAP_WIDTH) + (i * MAP_WIDTH)) << 1), (void*)ScreenBaseBlock(31) + (i << 6), copyWidth, DMA_16NOW);
	}
	
	REG_BG1HOFS = backgroundX & 7;
	REG_BG1VOFS = backgroundY & 7;
	
	REG_BG2HOFS = backgroundX & 7;
	REG_BG2VOFS = backgroundY & 7;
}

/////////////////
// jeuFocusCam //
/////////////////
void jeuFocusCam(int s)
{
	int posX, posY;
	
	////////////////
	// Position X //
	////////////////
	// Si on a atteint la gauche de la map
	if(sprite[s].x < 112)
	{
		// On ne défile plus le background et on déplace le sprite
		backgroundX = 0;
		
		if(sprite[s].x < 0)
			sprite[s].x = 0;
	}
	// Si on a atteint la droite de la map
	else if(sprite[s].x > ((MAP_WIDTH * 8) - SCREEN_WIDTH + 112))
	{
		backgroundX = (MAP_WIDTH * 8) - SCREEN_WIDTH;
		
		if(sprite[s].x > ((MAP_WIDTH * 8) - sprite[s].size))
			sprite[s].x = (MAP_WIDTH * 8) - sprite[s].size;
	}
	// Sinon
	else
		backgroundX = sprite[s].x - 112;
	
	posX = sprite[s].x - backgroundX;
	
	////////////////
	// Position Y //
	////////////////
	// Si on a atteint le haut de la map
	if(sprite[s].y < 72)
	{
		// On ne défile plus le background et on déplace le sprite
		backgroundY = 0;
		
		if(sprite[s].y < backgroundY)
			sprite[s].y = 0;
	}
	// Si on a atteint le bas de la map
	else if(sprite[s].y > (MAP_HEIGHT * 8) - SCREEN_HEIGHT + 72)
	{
		backgroundY = (MAP_HEIGHT * 8) - SCREEN_HEIGHT;
		
		if(sprite[s].y > ((MAP_HEIGHT * 8) - sprite[s].size))
			sprite[s].y = (MAP_HEIGHT * 8) - sprite[s].size;
	}
	// Sinon
	else
		backgroundY = sprite[s].y - 72;
	posY = sprite[s].y - backgroundY;
	
	commonSpriteChangePos(s, posX, posY);
}
