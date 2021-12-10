#include <stdlib.h>

#include "player.h"

Poketudiants createPoketudiant(){
    Poketudiants poke = (Poketudiants)malloc(sizeof(Poketudiant));
    int i=0;

    poke->maxVie = 100;
    poke->vie = 100;
    poke->x = 0;
    poke->y = 0;
    poke->xp = 0;
    poke->lvl = 0;
    poke->nbPoke = 0;
    poke->timer = 0.5;
    poke->suiv = NULL;

    //Variete variete;
    //Attaque listAtk[5];
    //Type type;

 //   for(i=0; i < MAX_TEAM; i++){
    //    poke->team[i] = NULL;
   // }



    return poke;
}


Poketudiants ajouterTetePoketudiant(Poketudiants liste, Poketudiants t){  // ajoute un texte a une liste de texte

    t->suiv = liste;
    liste = t;

    return t;
}

Poketudiants destroyPoketudiant(Poketudiants t){
    Poketudiants temp = t, suivant = NULL;

    while(temp){
        suivant = temp->suiv;
        //SDL_DestroyTexture(temp->texte);
        free(temp);
        temp = temp->suiv;
    }
    return temp;
}