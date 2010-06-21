#ifndef ARMES_H
#define ARMES_H

// Cr�ation de toutes les armes
void jeuInitArmes();

// Mise � jour des tirs
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
	
	MAX_ARMES	// Repr�sente le nombre d'armes
};

// Les modes de tir
enum
{
	MODE_SEMI = 0,
	MODE_AUTO
};

// La structure des donn�es d'une arme
typedef struct {
	char* name;		// Le nom de l'arme
	int degats;		// Les d�gats que font l'arme lors d'une seule touche
	int cadence;	// La cadence de tirs (d�lai entre deux tirs)
	int mode;		// Le mode de tir (auto, semi)
	int vitesse;	// Vitesse de d�placement des tirs
	int ammo1;		// Nombre de balles dans l'arme
	int ammo1_total;// Nombre de balles totales dans l'arme
	int ammo2;		// Nombre de balles suppl�mentaires
	int ammo2_total;// Nombre de balles totales suppl�mentaires
} Arme;
extern Arme armes[MAX_ARMES];

#endif // ARMES_H
