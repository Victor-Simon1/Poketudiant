#include <stdlib.h>

#include "player.h"

Poketudiants createPoketudiant(){
    Poketudiants poke = (Poketudiants)malloc(sizeof(Poketudiant));
    int i=0;

    poke->maxVie;
    poke->vie = 100;
    
    poke->xp;
    poke->lvl;
    poke->nbPoke = 0;

    for(i=0; i < MAX_TEAM; i++){
        poke->team[i] = NULL;
    }



    return poke;
}