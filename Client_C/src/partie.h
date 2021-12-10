#ifndef PARTIE_H
#define PARTIE_H


typedef struct _partie{
    char nom[30];
    char map[150][150];
    int nbJoueur;
    int maxJoueur;
    int nbLigne;
    int nbColonne;
    struct _partie *suiv;
}Partie, *Parties;


// =========== variables ===========


int nbPartie;
Parties maPartie;

SDL_Texture *textPartie; // texture pour le titre du menu

// =========== fonctions ===========


int refreshGame();
int newPartie(char text[50]);
int joinPartie(char text[50]);


Parties createPartie(char name[50]);
Parties ajouterTetePartie(Parties liste, Parties p);
void destroyParties(Parties p);


int loadPartie();
int updatePartie();
int drawPartie();

void liberePartie();

#endif