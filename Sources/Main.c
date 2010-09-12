////////////////
// Inclusions //
////////////////
#include "Common/Common.h"

Scenes scene = MENU_PRINCIPAL;
Save sauvegardes[4];
int currentSave = 0;

/////////////////
// mainSaveAll //
/////////////////
void mainSaveAll()
{
	commonSRAMSaveString(0, SAVE_MAGIC);
	
	commonSRAMSaveInt(SAVE_1, sauvegardes[0].niveau);
	commonSRAMSaveInt(SAVE_2, sauvegardes[1].niveau);
	commonSRAMSaveInt(SAVE_3, sauvegardes[2].niveau);
	commonSRAMSaveInt(SAVE_4, sauvegardes[3].niveau);
}

//////////
// main //
//////////
int main()
{
	// On charge les sauvegardes
	char* verifSave = commonSRAMLoadString(0, 9);
	if(strcmp(verifSave, SAVE_MAGIC) == 0)
	{
		// On charge les sauvegardes
		sauvegardes[0].niveau = commonSRAMLoadInt(SAVE_1);
		sauvegardes[1].niveau = commonSRAMLoadInt(SAVE_2);
		sauvegardes[2].niveau = commonSRAMLoadInt(SAVE_3);
		sauvegardes[3].niveau = commonSRAMLoadInt(SAVE_4);
	}
	else
	{
		// On met des valeurs par défaut dans les sauvegardes
		int i;
		for(i = 0; i < 4; i++)
			sauvegardes[i].niveau = 0;
		
		mainSaveAll();
	}
	
	// Initialisation des sprites
	commonInitSprites();
	
	// Chargement de la palette de 256 couleurs des sprites de l'interface
	commonDMACopy((void*)interface_palette, (void*)spritePalette, 256, DMA_16NOW);
	
	// Chargement des sprites de l'interface
	commonDMACopy((void*)tir_tiles, (void*)(&OAMData[SPRITE_CALC_OFFSET(SPRITE_TIR)]), SPRITE_CALC_SIZE(1), DMA_16NOW);
	commonDMACopy((void*)curseur_tiles, (void*)(&OAMData[SPRITE_CALC_OFFSET(SPRITE_CURSEUR)]), SPRITE_CALC_SIZE(4), DMA_16NOW);
	commonDMACopy((void*)font_tiles, (void*)(&OAMData[SPRITE_CALC_OFFSET(SPRITE_FONT)]), SPRITE_CALC_SIZE(48), DMA_16NOW);
	commonDMACopy((void*)james_bond_tiles, (void*)(&OAMData[SPRITE_CALC_OFFSET(SPRITE_JAMES_BOND)]), SPRITE_CALC_SIZE(28), DMA_16NOW);
	commonDMACopy((void*)scientifique_tiles, (void*)(&OAMData[SPRITE_CALC_OFFSET(SPRITE_SCIENTIFIQUE)]), SPRITE_CALC_SIZE(28), DMA_16NOW);
	
	// Lancement de l'interruption d'AAS
	//commonSetInterrupt(IT_TIMER1, (IntrFunction*) &AAS_Timer1InterruptHandler);
	
	// Configuration d'AAS
	//AAS_SetConfig(AAS_CONFIG_MIX_24KHZ, AAS_CONFIG_CHANS_4, AAS_CONFIG_SPATIAL_MONO, AAS_CONFIG_DYNAMIC_OFF);
	//AAS_SetConfig(AAS_CONFIG_MIX_8KHZ, AAS_CONFIG_CHANS_4, AAS_CONFIG_SPATIAL_MONO, AAS_CONFIG_DYNAMIC_OFF);
	
	// Mise en place l'interruption sur le retour de balayage (VBL)
	commonSetInterrupt(IT_VBLANK, (IntrFunction*) &commonBasicVblInterrupt);
	
	// Lancement de l'intro
	intro();
	
	while(1)
	{
		if(scene >= JEU)
		{
			// Lancement du jeu
			jeu();
		}
		else
		{
			// Lancement du menu
			menu();
		}
	}
	
	return 0;
}
