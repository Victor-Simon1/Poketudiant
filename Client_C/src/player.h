#ifndef PLAYER_H
#define PLAYER_H

#define MAX_TEAM 3
#define NB_VARIETE 11
#define NB_ATTAQUE 13
#define NB_TYPE 4

#include <stdbool.h>

typedef enum _Variete{
    parlfor, ismar, rigolamor, procrastino, couchtar, nuidebou, alabourre, buchafon, belmention, promomajor, enseignant_dresseur
}Variete;

typedef enum _Attaque{
    bavardage, groboucan, megaphone_vocal, batillement, ptisomme, superdodo, rateletrin, oboulo, exo_maison, max_reviz, titquestion, poser_colle, fatal_interro
}Attaque;

typedef enum _Type{
    noisy, lazy, motivated, teacher
}Type;

typedef struct _poke{
    double vie;
    int maxVie;
    int x;
    int y;
    int atk; 
    int def;
    double xp;
    double xpManquant;
    int lvl;
    double timer;
    bool enCbt;
    struct _poke *team[MAX_TEAM];
    struct _poke *suiv;
    int nbPoke;
    char *variete;
    char *atk1;
    char *atk2;
    char *atk1Type;
    char *atk2Type;
    char *type;
}Poketudiant, *Poketudiants;



Poketudiants player;
Poketudiants listeRival;


int tabAtk[NB_VARIETE];
int tabDef[NB_VARIETE];
int tabPvMax[NB_VARIETE];

int tabPuissance[NB_ATTAQUE];

Type tabEfficace[NB_TYPE];



Poketudiants createPoketudiant();
Poketudiants ajouterTetePoketudiant(Poketudiants liste, Poketudiants t);
Poketudiants destroyPoketudiant(Poketudiants t);


#endif