#ifndef PARTIE_H
#define PARTIE_H


typedef struct _partie{
    char nom[30];
    int **map;
    int nbJoueur;
    int maxJoueur;
    int nbLigne;
    int nbColonne;
    struct _partie *suiv;
}Partie, *Parties;


// =========== variables ===========


int nbPartie;


SDL_Texture *textPartie; // texture pour le titre du menu

// =========== fonctions ===========


void refreshGame();
void newPartie(char text[50]);
void joinPartie(char[50]);


Parties createPartie();
Parties ajouterTeteTexte(Parties liste, Parties p);
void destroyParties(Parties p);


int loadPartie();
int updatePartie();
int drawPartie();

void liberePartie();

#endif