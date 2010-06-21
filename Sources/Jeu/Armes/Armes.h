#ifndef ARMES_H
#define ARMES_H

// Création de toutes les armes
void jeuInitArmes();

// Mise à jour des tirs
void jeuUpdateTirs();

// Colisions d'un tir avec la map
int jeuTirColLeft(int s);
int jeuTirColRight(int s);

// Change l'arme et prend la suivante
void jeuChangeArme();

// Effectue un tir avec l'arme en cours
void jeuTir(u8 s);

// Les identifiants des armes
enum
{
	ARME_PP7 = 0,
	ARME_KF7_SOVIET,
	
	MAX_ARMES	// Représente le nombre d'armes
};

// Les modes de tir
enum
{
	MODE_SEMI = 0,
	MODE_AUTO
};

// La structure des données d'une arme
typedef struct {
	char* name;		// Le nom de l'arme
	int degats;		// Les dégats que font l'arme lors d'une seule touche
	int cadence;	// La cadence de tirs (délai entre deux tirs)
	int mode;		// Le mode de tir (auto, semi)
	int vitesse;	// Vitesse de déplacement des tirs
	int ammo1;		// Nombre de balles dans l'arme
	int ammo1_total;// Nombre de balles totales dans l'arme
	int ammo2;		// Nombre de balles supplémentaires
	int ammo2_total;// Nombre de balles totales supplémentaires
} Arme;
extern Arme armes[MAX_ARMES];

#endif // ARMES_H
