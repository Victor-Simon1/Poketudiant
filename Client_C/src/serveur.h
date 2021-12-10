#ifndef SERVEUR_H
#define SERVEUR_H

#include "partie.h"

typedef struct _serveur{
    char ip[20];
    Parties listePartie;
    int nbClient;
    int maxClient;
    struct _serveur *suiv;
}Serveur, *Serveurs;

typedef struct _texte{
    SDL_Texture *texte;
    struct _texte *suiv;
    int x;
    int y;
}Texte, *Textes;

// =========== variables ===========

Serveurs listeServeur; // liste des serveurs disponible
Textes listeTexte; // liste des serveurs disponible


int nbServeur;


// =========== fonctions ===========

int refresh(char texte[20]);
int joinServeur();

Serveurs createServeur(char _ip[20]);
Serveurs ajouterTeteServeur(Serveurs liste, Serveurs s);
void destroyServeurs(Serveurs s);

Textes createTexte(char text[50], int p_x, int p_y);
Textes ajouterTeteTexte(Textes liste, Textes t);
Textes destroyTextes(Textes text);

int loadServeur();
int updateServeur();
int drawServeur();

void libereServeur();

#endif