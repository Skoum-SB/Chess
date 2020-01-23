#include <stdio.h>
#include <stdlib.h>

#define couleur(param) printf("\033[%sm",param) //Changer la couleur des pièces

typedef struct plateau{
	int grille[8][8];
	int Nbp[12];
}plateau;

struct noeud {
	int coord;	//Coordonnée de départ
	int coup;	//Coordonnée d'arrivée
	struct noeud * suiv[];
};
typedef struct noeud  noeud;
typedef struct noeud * arbre;

typedef struct solution{
	int sol;
	arbre hist;
}solution;

void initp (plateau *p); //initialiser le plateau avec les pièces

void newp(plateau *p); //Créer un nouveau problème

void affp (plateau p); //Afficher le plateau de jeu

void affc (int c); //Afficher une case du plateau

int convert(char * nom); //Convertir le nom de la pièce en entier

void viderBuffer(); //Vider stdin

void deplp(plateau *p, int dep, int arr);

void decomptepieces(plateau *p);

int tropdepieces(plateau p, int t);

void coupslegaux(plateau p, int coord, int lscoup[27], int mode);

void ajoutercoup(int lscoup[27], int coord);

void initlscoup(int lscoup[27]);

int coordvalide(int coord);

char itoc(int n);

int echec(plateau p, int c);

int mat(plateau p, int couleur);

void selecp(plateau p);

solution resop(plateau p, int coup, int nbc, int c);

char converttype(int type);

void inserefeuille (arbre a,int coord, int c);

arbre initarbre();

void inserearbre (arbre a, arbre b, int coord, int c);

void afficherarbre(arbre a, int nbc);