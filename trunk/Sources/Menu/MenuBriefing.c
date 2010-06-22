////////////////
// Inclusions //
////////////////
#include "Menu.h"
#include "../Common/Common.h"

//////////////////
// menuBriefing //
//////////////////
void menuBriefing()
{
	REG_DISPCNT = MODE_4 | BG2_ENABLE;
	
	// Selection de l'image de fond
	u8** menu_briefing_bitmap8 = 0;
	u16* menu_briefing_palette = 0;
	if(sauvegardes[currentSave].niveau == 0)
	{
		menu_briefing_bitmap8 = menu_briefing_01_bitmap8;
		menu_briefing_palette = menu_briefing_01_palette;
	}
	
	// Fondu vers l'image
	commonFadeIn((void*)menu_briefing_bitmap8, (void*)menu_briefing_palette);
	
	// Affichage de l'image de fond
	commonDisplayPicture((u16*) menu_briefing_bitmap8, menu_briefing_palette);
	
	// Remise à zéro des sprites
	commonResetSprites();
	
	// Affiche des textes
	u16 nextSprite = commonWriteString(0, 0, 0, "B: BACK");
	nextSprite = commonWriteString(nextSprite, 240 - (5 * 8), 0, "OK: A");
	nextSprite = commonWriteString(nextSprite, (240 - 16 * 8) / 2, 8, "L&R&START: ERASE");
	
	char save[2];
	commonIntToString(currentSave + 1, save);
	nextSprite = commonWriteString(nextSprite, 240 - (2 * 8), 150, save);
	
	// Activation de l'affichage des sprites
	REG_DISPCNT |= OBJ_ENABLE | OBJ_MAP_1D;
	
	while(scene == MENU_BRIEFING)
	{
		// Si la touche A est appuyée
		if(!(REG_KEYS & KEY_A))
			scene = JEU_CHARGEMENT;
		// Si la touche START est appuyée
		else if(!(REG_KEYS & KEY_B))
			scene = MENU_PRINCIPAL;
		
		// La combinaison de touches pour supprimer
		if(!(REG_KEYS & KEY_L) && !(REG_KEYS & KEY_R) && !(REG_KEYS & KEY_START))
		{
			sauvegardes[currentSave].niveau = 0;
			mainSaveAll();
			
			scene = MENU_PRINCIPAL;
		}
		
		// Attente de la fin du dessin à l'écran
		commonWaitVSync();
		
		// Copie des sprites dans la mémoire OAM
		commonCopyOAMBuffer();
	}
	
	// Désactivation de l'affichage des sprites
	REG_DISPCNT &= ~OBJ_ENABLE & ~OBJ_MAP_1D;
	
	// Remise à zéro des sprites
	commonResetSprites();
	
	// Fondu vers le noir
	commonFadeOut();
	
	REG_DISPCNT = 0;
}
