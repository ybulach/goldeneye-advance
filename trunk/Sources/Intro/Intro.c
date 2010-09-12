////////////////
// Inclusions //
////////////////
#include "../Common/Common.h"

///////////
// intro //
///////////
void intro()
{
	REG_DISPCNT = MODE_4 | BG2_ENABLE;
	REG_BG2CNT = BG_MOSAIC_ENABLE;
	
	///////////////////////////
	// Message d'information //
	///////////////////////////
	// Fondu vers l'image
	commonFadeIn((void*)info_bitmap8, (void*)info_palette);
	
	// Affichage de l'image
	commonDisplayPicture((u16*)info_bitmap8, info_palette);
	
	// Affichage de l'image pendant 3 seconde
	commonWaitTime(3, 0);
	
	// Fondu vers le noir
	commonFadeOut();
	
	////////////////////
	// Player-Advance //
	////////////////////
	// Fondu vers l'image
	commonFadeIn((void*)player_advance_bitmap8, (void*)player_advance_palette);
	
	// Affichage de l'image
	commonDisplayPicture((u16*)player_advance_bitmap8, player_advance_palette);
	
	// Affichage de l'image pendant 1 seconde
	commonWaitTime(1, 0);
	
	// Fondu vers le noir
	commonFadeOut();
	
	///////////////////////
	// Apex Audio System //
	///////////////////////
	//AAS_ShowLogo();
	
	// Remise à zéro des sprites
	commonResetSprites();
	
	////////////////////////////////////
	// Logo avec un texte PRESS START //
	////////////////////////////////////
	// Fondu vers l'image
	commonFadeIn((void*)logo_bitmap8, (void*)logo_palette);
	
	// Affichage de l'image
	commonDisplayPicture((u16*)logo_bitmap8, logo_palette);
	
	// Affiche du texte PRESS START
	commonWriteString(0, (240 - 11 * 8) / 2, 130, "PRESS START");
	
	// Activation de l'affichage des sprites
	REG_DISPCNT |= OBJ_ENABLE | OBJ_MAP_1D;
	
	// Attente de l'appuie sur start pour continuer
	while(REG_KEYS & KEY_START)
	{
		// Attente de la fin du dessin à l'écran
		commonWaitVSync();
		
		// Copie des sprites dans la mémoire OAM
		commonCopyOAMBuffer();
	}
	
	// Désactivation de l'affichage des sprites
	REG_DISPCNT &= ~OBJ_ENABLE & ~OBJ_MAP_1D;
	
	// Remise à zéro des sprites
	commonResetSprites();
	
	// Effet de mosaic "Out"
	commonMosaicOut();
	
	REG_DISPCNT = 0;
	REG_BG2CNT = 0;
}
