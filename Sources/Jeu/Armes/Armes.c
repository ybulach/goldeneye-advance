////////////////
// Inclusions //
////////////////
#include "../../Common/Common.h"
#include "Armes.h"
#include "../Map/Map.h"
#include "../Personnages/Personnages.h"

Arme armes[MAX_ARMES];

///////////////////
// jeuTirColLeft //
///////////////////
int jeuTirColLeft(int s)
{
	if(		(jeuGetTile(sprite[s].x, sprite[s].y + 2) != COL_ALL)
			&& (jeuGetTile(sprite[s].x, sprite[s].y + sprite[s].size - 2) != COL_ALL)	)
		return 0;
	return 1;
}

////////////////////
// jeuTirColRight //
////////////////////
int jeuTirColRight(int s)
{
	if(		(jeuGetTile(sprite[s].x + sprite[s].size, sprite[s].y + 2) != COL_ALL)
			&& (jeuGetTile(sprite[s].x + sprite[s].size, sprite[s].y + sprite[s].size - 2) != COL_ALL)	)
		return 0;
	return 1;
}

/////////////////////
// jeuChangeArme() //
/////////////////////
void jeuChangeArme()
{
	// On change d'arme
	int i = sprite[JAMES_BOND].current_arme + 1;
	while(i > -1)
	{
		if(i < MAX_ARMES)
		{
			// Si l'arme est dans l'inventaire
			if(sprite[JAMES_BOND].armes[i])
			{
				sprite[JAMES_BOND].current_arme = i;
				i = -1;
			}
			// On va à l'arme suivante
			else
				i++;
		}
		// On revient à la première arme
		else
			i = 0;
	}
	
	// On enlève le nom de l'arme précédente
	for(i = 101; i < 116; i++)
		commonResetSprite(i);
}

//////////////////
// jeuInitArmes //
//////////////////
void jeuInitArmes()
{
	// Création des données statiques sur les armes
	armes[0].name = "PP7";
	armes[0].degats = 20;
	armes[0].cadence = 20;
	armes[0].mode = MODE_SEMI;
	armes[0].vitesse = 2;
	armes[0].ammo1 = armes[0].ammo1_total = 7;
	armes[0].ammo2 = armes[0].ammo2_total = 93;
	
	armes[1].name = "KF7 SOVIET";
	armes[1].degats = 35;
	armes[1].cadence = 10;
	armes[1].mode = MODE_AUTO;
	armes[1].vitesse = 3;
	armes[1].ammo1 = armes[1].ammo1_total = 30;
	armes[1].ammo2 = armes[1].ammo2_total = 2;
	
	// Chargements des sprites des tirs
	int i;
	for(i = 76; i < 101; i++)
	{
		jeuCreateSprite(i, 8, SPRITE_TIR);
		
		// Avec les tirs, on l'utilise pour savoir si on doit afficher ou non le tir
		sprite[i].anim = ANIM_MORT;
		
		commonSpriteChangePos(i, 240, 160);
		commonSpriteChangeGfx(i, sprite[i].gfx + sprite[i].anim, 1);
	}
}

///////////////////
// jeuUpdateTirs //
///////////////////
void jeuUpdateTirs()
{
	int i, j, x, y, size, arme;
	
	// On met à jour le délai entre les tirs
	for(i = 0; i < 76; i++)
	{
		sprite[i].arme_cnt++;
		
		// Si la recharge est finie
		if((sprite[i].recharge == 1) && (sprite[i].arme_cnt > 100))
		{
			sprite[i].recharge = 0;
			sprite[i].arme_cnt = 0;
		}
		
		// Si l'arme est vide
		if(armes[sprite[i].current_arme].ammo1 == 0)
		{
			// Si il y a des balles de rechange
			if(armes[sprite[i].current_arme].ammo2 != 0)
			{
				// On transfert les balles dans l'arme
				if(armes[sprite[i].current_arme].ammo2 < armes[sprite[i].current_arme].ammo1_total)
				{
					armes[sprite[i].current_arme].ammo1 = armes[sprite[i].current_arme].ammo2;
					armes[sprite[i].current_arme].ammo2 = 0;
				}
				else
				{
					armes[sprite[i].current_arme].ammo1 = armes[sprite[i].current_arme].ammo1_total;
					armes[sprite[i].current_arme].ammo2 -= armes[sprite[i].current_arme].ammo1_total;
				}
				
				sprite[i].recharge = 1;
				sprite[i].arme_cnt = 0;
			}
		}
	}
	
	for(i = 76; i < 101; i++)
	{
		// Si le tir doit être affiché
		if(sprite[i].anim != ANIM_MORT)
		{
			// On regarde si ce tir touche un obstacle
			if(jeuTirColLeft(i) || jeuTirColRight(i))
				sprite[i].anim = ANIM_MORT;
			// On regarde si le tir est dans la zone où les tirs sont effectifs
			else if((sprite[i].x > (backgroundX + SCREEN_WIDTH + (SCREEN_WIDTH >> 1))) || (sprite[i].x < (backgroundX - (SCREEN_WIDTH >> 1))))
				sprite[i].anim = ANIM_MORT;
			else
			{
				x = sprite[i].x;
				y = sprite[i].y;
				size = sprite[i].size;
				arme = sprite[i].current_arme;
				
				// On regarde si ce tir touche un sprite
				for(j = 0; j < 75; j++)
				{
					// Si le sprite est vivant uniquement
					if(sprite[j].anim != ANIM_MORT)
					{
						// Si il est en contact avec le sprite
						if(	(x > sprite[j].x) && (x < (sprite[j].x + sprite[j].size))
								&& ((x + size) > sprite[j].x) && ((x + size) < (sprite[j].x + sprite[j].size))
								&& (y > sprite[j].y) && (y < (sprite[j].y + sprite[j].size))
								&& ((y + size) > sprite[j].y) && ((y + size) < (sprite[j].y + sprite[j].size))	)
						{
							// Si il a une armure
							if(sprite[j].armure > 0)
							{
								// Si il y a plus de points d'armure que de dégats du tir
								if(sprite[j].armure >= armes[arme].degats)
									sprite[j].armure -= armes[arme].degats;
								// Sinon, on enlève aussi des points de vie
								else
								{
									sprite[j].vies -= (armes[arme].degats - sprite[j].armure);
									sprite[j].armure = 0;
								}
							}
							// Sinon, on enlève les points de vie
							else
							{
								sprite[j].vies -= armes[arme].degats;
							}
							
							// Si il n'a plus de points de vie
							if(sprite[j].vies <= 0)
							{
								sprite[j].vies = 0;
								sprite[j].anim = ANIM_MORT;
							}
							
							// On détruit le tir
							sprite[i].anim = ANIM_MORT;
						}
					}
				}
			}
			
			// Si il n'a touché personne, il continue son chemin
			if(sprite[i].anim != ANIM_MORT)
			{
				sprite[i].x = (sprite[i].direction) ? (sprite[i].x - armes[arme].vitesse) : (sprite[i].x + armes[arme].vitesse);
				
				x = sprite[i].x - backgroundX;
				y = sprite[i].y - backgroundY;
				
				// On ne l'affiche que si il est dans l'écran
				if((x > 0) && (x < SCREEN_WIDTH) && (y > 0) && (y < SCREEN_HEIGHT))
					commonSpriteChangePos(i, x, y);
				else
					commonSpriteChangePos(i, 240, 160);
			}
			// Sinon, on n'affiche pas le tir
			else
				commonSpriteChangePos(i, 240, 160);
		}
		// Sinon, on n'affiche pas le tir
		else
			commonSpriteChangePos(i, 240, 160);
	}
}

////////////
// jeuTir //
////////////
void jeuTir(u8 s)
{
	// Si le délai est dépassé et qu'il y a des balles dans l'arme
	if((sprite[s].arme_cnt > armes[sprite[s].current_arme].cadence) && (armes[sprite[s].current_arme].ammo1 > 0) && (sprite[s].recharge == 0))
	{
		// On crée un tir dans un emplacement vide
		int i, j = 0;
		for(i = 76; i < 101; i++)
			if(sprite[i].anim == ANIM_MORT)
				j = i;
		
		// On paramètre le tir
		if(j > 0)
		{
			sprite[j].anim = ANIM_RIEN;
			commonSpriteChangeGfx(j, sprite[j].gfx + sprite[j].anim, 1);
			
			sprite[j].direction = sprite[s].direction;
			
			if(sprite[j].direction)
				sprite[j].x = sprite[s].x - sprite[j].size - 2;
			else
				sprite[j].x = sprite[s].x + sprite[s].size + 2;
			
			sprite[j].y = sprite[s].y + (sprite[s].size >> 1) - (sprite[j].size >> 1);
			
			sprite[j].current_arme = sprite[s].current_arme;
			
			// On enlève la balle de l'arme
			armes[sprite[s].current_arme].ammo1--;
		}
		
		sprite[s].arme_cnt = 0;
	}
}
