////////////////
// Inclusions //
////////////////
#include <Common.h>
#include <Armes.h>
#include <Map.h>
#include <Personnages.h>

///////////
// AUTRE //
///////////
// Si les touches ont déjà été pressées
int keyPressedA;
int keyPressedB;

/////////
// jeu //
/////////
void jeu()
{
	REG_DISPCNT = MODE_0;
	
	// On remet à zéro les sprites
	jeuResetSprites();
	
	// On initialise les données des armes
	jeuInitArmes();
	
	// Un sprite
	jeuCreateSprite(JAMES_BOND, 16, SPRITE_JAMES_BOND);
	sprite[JAMES_BOND].x = 0 << 3;
	sprite[JAMES_BOND].y = 9 << 3;
	
	sprite[JAMES_BOND].armes[0] = 1;
	sprite[JAMES_BOND].armes[1] = 1;
	
	sprite[JAMES_BOND].current_arme = 0;
	
	jeuCreateSprite(1, 16, SPRITE_SCIENTIFIQUE);
	sprite[1].x = 45 << 3;
	sprite[1].y = 13 << 3;
	
	// On initialise les maps
	jeuLoadLevel(sauvegardes[currentSave].niveau);
	
	jeuUpdateBackground();
	
	// On affiche deux backgrounds et les sprites
	REG_DISPCNT |= BG1_ENABLE | BG2_ENABLE | OBJ_ENABLE | OBJ_MAP_1D;
	
	keyPressedA = 0;
	keyPressedB = 0;
	
	// Le nombre de balles dans l'arme
	char nb_balles[2];
	
	while(scene >= JEU)
	{
		// Retour au menu de briefing
		if(commonCheckKey(KEY_START))
			scene = MENU_BRIEFING;
		
		sprite[JAMES_BOND].move = 0;
		
		// Si une touche est appuyée et qu'il n'y a pas d'obstacle
		if(commonCheckKey(KEY_RIGHT) && !jeuPersonnageColRight(JAMES_BOND))
		{
			sprite[JAMES_BOND].x++;
			
			sprite[JAMES_BOND].direction = 0;
			
			sprite[JAMES_BOND].move = 1;
		}
		else if(commonCheckKey(KEY_LEFT) && !jeuPersonnageColLeft(JAMES_BOND))
		{
			sprite[JAMES_BOND].x--;
			
			sprite[JAMES_BOND].direction = 1;
			
			sprite[JAMES_BOND].move = 1;
		}
		
		if(commonCheckKey(KEY_UP) && !jeuPersonnageColUp(JAMES_BOND))
		{
			sprite[JAMES_BOND].y--;
			
			sprite[JAMES_BOND].move = 1;
		}
		else if(commonCheckKey(KEY_DOWN) && !jeuPersonnageColDown(JAMES_BOND))
		{
			sprite[JAMES_BOND].y++;
			
			sprite[JAMES_BOND].move = 1;
		}
		
		// On change l'animation si il bouge
		if(sprite[JAMES_BOND].move)
		{
			// Si le compteur est assez élevé pour changer l'animation
			if(sprite[JAMES_BOND].anim_cnt > 5)
			{
				// Changement de l'animation
				if(sprite[JAMES_BOND].anim >= ANIM_MARCHE3)
					sprite[JAMES_BOND].anim = ANIM_RIEN;
				else
					sprite[JAMES_BOND].anim++;
				
				sprite[JAMES_BOND].anim_cnt = 0;
			}
			else
				sprite[JAMES_BOND].anim_cnt++;
		}
		// Si on ne fait rien
		else
		{
			sprite[JAMES_BOND].anim_cnt = 0;
			sprite[JAMES_BOND].anim = ANIM_RIEN;
		}
		
		// Un appui sur A
		if(commonCheckKey(KEY_A))
		{
			if(!keyPressedA)
			{
				// On change d'arme
				jeuChangeArme();
				
				keyPressedA = 1;
			}
		}
		else
			keyPressedA = 0;
		
		// Un appui sur B
		if(commonCheckKey(KEY_B))
		{
			// Si l'arme est en mode semi
			if(armes[sprite[JAMES_BOND].current_arme].mode == MODE_SEMI)
			{
				if(!keyPressedB)
				{
					// On tire
					jeuTir(JAMES_BOND);
					
					keyPressedB = 1;
				}
			}
			else
				jeuTir(JAMES_BOND);
		}
		else
			keyPressedB = 0;
		
		if(sprite[JAMES_BOND].current_arme != -1)
		{
			// On affiche le nom de l'arme
			commonWriteString(101, 0, 152, armes[sprite[JAMES_BOND].current_arme].name);
			
			// On affiche le mode de tir de l'arme
			if(armes[sprite[JAMES_BOND].current_arme].mode == MODE_SEMI)
				commonWriteString(116, 0, 144, "SEMI");
			else if(armes[sprite[JAMES_BOND].current_arme].mode == MODE_AUTO)
				commonWriteString(116, 0, 144, "AUTO");
			
			// On affiche le nombre de balles
			commonIntToString(armes[sprite[JAMES_BOND].current_arme].ammo1, nb_balles);
			commonWriteString(120, 200, 152, nb_balles);
			
			commonWriteString(122, 216, 152, ":");
			
			commonIntToString(armes[sprite[JAMES_BOND].current_arme].ammo2, nb_balles);
			commonWriteString(123, 224, 152, nb_balles);
		}
		
		// Centre l'écran sur le joueur
		jeuFocusCam(JAMES_BOND);
		
		// Mise à jour du joueur
		commonSpriteFlip(JAMES_BOND, sprite[JAMES_BOND].direction, 0);
		jeuUpdateSpriteGfx(JAMES_BOND);
		
		// Mise à jour des ennemis
		jeuUpdateEnnemis();
		
		// Mise à jour des tirs
		jeuUpdateTirs();
		
		// Mise à jour des coordonnées du background
		jeuUpdateBackground();
		
		// Attente de la fin du dessin à l'écran
		commonWaitVSync();
		
		// Copie des sprites dans la mémoire OAM
		commonCopyOAMBuffer();
	}
}
