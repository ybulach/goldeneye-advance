////////////////
// Inclusions //
////////////////
#include <Menu.h>
#include <Common.h>

///////////////////
// menuPrincipal //
///////////////////
void menuPrincipal()
{
	REG_DISPCNT = MODE_4 | BG2_ENABLE;
	REG_MOSAIC = SetMosaic(0, 0, 0, 0);
	
	// Fondu vers l'image
	commonFadeIn((void*)menu_principal_bitmap8, (void*)menu_principal_palette);
	
	// Affichage de l'image de fond
	commonDisplayPicture((u16*) menu_principal_bitmap8, menu_principal_palette);
	
	// Remise à zéro des sprites
	commonResetSprites();
	
	// Affichage du curseur
	int curseurX = 112, curseurY = 72;
	OAMBuffer[0].attribute0 = COLOR_256 | SQUARE | curseurY;
	OAMBuffer[0].attribute1 = SIZE_16 | curseurX;
	OAMBuffer[0].attribute2 = SPRITE_CURSEUR;
	
	// On affiche les derniers niveaux finis sur chaque sauvegarde
	char niveau[2];
	u16 nextSprite = 1;
	
	if(sauvegardes[0].niveau != 0)
	{
		nextSprite = commonWriteString(nextSprite, 19, 121, "LEVEL");
		commonIntToString(sauvegardes[0].niveau, niveau);
		nextSprite = commonWriteString(nextSprite, 39 - (strlen(niveau) / 2 * 8), 131, niveau);
	}
	else
		nextSprite = commonWriteString(nextSprite, 19, 121, "EMPTY");
	
	if(sauvegardes[1].niveau != 0)
	{
		nextSprite = commonWriteString(nextSprite, 59, 76, "LEVEL");
		commonIntToString(sauvegardes[1].niveau, niveau);
		nextSprite = commonWriteString(nextSprite, 79 - (strlen(niveau) / 2 * 8), 86, niveau);
	}
	else
		nextSprite = commonWriteString(nextSprite, 59, 76, "EMPTY");
	
	if(sauvegardes[2].niveau != 0)
	{
		nextSprite = commonWriteString(nextSprite, 140, 121, "LEVEL");
		commonIntToString(sauvegardes[2].niveau, niveau);
		nextSprite = commonWriteString(nextSprite, 160 - (strlen(niveau) / 2 * 8), 131, niveau);
	}
	else
		nextSprite = commonWriteString(nextSprite, 140, 121, "EMPTY");
	
	if(sauvegardes[3].niveau != 0)
	{
		nextSprite = commonWriteString(nextSprite, 181, 76, "LEVEL");
		commonIntToString(sauvegardes[3].niveau, niveau);
		nextSprite = commonWriteString(nextSprite, 201 - (strlen(niveau) / 2 * 8), 86, niveau);
	}
	else
		nextSprite = commonWriteString(nextSprite, 181, 76, "EMPTY");
	
	nextSprite = commonWriteString(nextSprite, (240 - 9 * 8), 150, "SELECT: A");
	
	// Activation de l'affichage des sprites
	REG_DISPCNT |= OBJ_ENABLE | OBJ_MAP_1D;
	
	while(scene == MENU_PRINCIPAL)
	{
		if(!(REG_KEYS & KEY_UP))
		{
			if(curseurY > 8)
				curseurY -= 2;
		}
		else if(!(REG_KEYS & KEY_DOWN))
		{
			if(curseurY < 152)
				curseurY += 2;
		}
		if(!(REG_KEYS & KEY_LEFT))
		{
			if(curseurX > 8)
				curseurX -= 2;
		}
		else if(!(REG_KEYS & KEY_RIGHT))
		{
			if(curseurX < 232)
				curseurX += 2;
		}
		
		// Changement de la position du curseur
		commonSpriteChangePos(0, curseurX - 8, curseurY - 8);
		
		// Si la touche A est appuyée (ou la touche START)
		if(!(REG_KEYS & KEY_A) || !(REG_KEYS & KEY_START))
		{
			// Sauvegarde 2
			if((curseurX  < 117) && (curseurX > 43) && (curseurY < 102) && (curseurY > 14))
			{
				currentSave = 1;
				scene = MENU_BRIEFING;
			}
			// Sauvegarde 1
			else if((curseurX  < 77) && (curseurX > 2) && (curseurY < 148) && (curseurY > 61))
			{
				currentSave = 0;
				scene = MENU_BRIEFING;
			}
			// Sauvegarde 4
			else if((curseurX  < 238) && (curseurX > 163) && (curseurY < 102) && (curseurY  > 14))
			{
				currentSave = 3;
				scene = MENU_BRIEFING;
			}
			// Sauvegarde 3
			else if((curseurX  < 197) && (curseurX  > 123) && (curseurY  < 148) && (curseurY  > 61))
			{
				currentSave = 2;
				scene = MENU_BRIEFING;
			}
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
