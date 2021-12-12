
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "menu.h"
#include "fonctions.h"
#include "serveur.h"
#include "player.h"
#include "partie.h"

/*
  _        ___       _      ____  
 | |      / _ \     / \    |  _ \ 
 | |     | | | |   / _ \   | | | |
 | |___  | |_| |  / ___ \  | |_| |
 |_____|  \___/  /_/   \_\ |____/ 
                                
*/


int load(){


    // ============== font ==============
    police = LoadFont("src/font/arial.ttf",20);
    if(police == NULL)
        return -1;

    policeTitre = LoadFont("src/font/blocked.ttf", 50);
    if(police == NULL)
        return -1;


   
   // ==================================== INITIALISATION VARIABLES ====================================
    imgFondCombat = LoadTexture2(game.ecran.renderer,"src/gfx/battle_background.png");

    herbeImg = LoadTexture2(game.ecran.renderer,"src/gfx/herbe.png");
    soinImg = LoadTexture2(game.ecran.renderer,"src/gfx/soin.png");
    buissonImg = LoadTexture2(game.ecran.renderer,"src/gfx/buisson.png");

    player1Img = LoadTexture2(game.ecran.renderer,"src/gfx/player1.png");
    player2Img = LoadTexture2(game.ecran.renderer,"src/gfx/player2.png");
    player3Img = LoadTexture2(game.ecran.renderer,"src/gfx/player3.png");
    player4Img = LoadTexture2(game.ecran.renderer,"src/gfx/player4.png");

    running = true;
    choose = true;
    player = createPoketudiant();

    game.ecran.camera.x = 0;
    game.ecran.camera.y = 0;

    // Couleur de la police
    game.couleur.noir.r = 0;
    game.couleur.noir.g = 0;
    game.couleur.noir.b = 0;

    game.couleur.rouge.r = 255;
    game.couleur.rouge.g = 0;
    game.couleur.rouge.b = 0;

    game.couleur.jaune.r = 255;
    game.couleur.jaune.g = 255;
    game.couleur.jaune.b = 0;
   
    strcpy(game.affichage,"MENU");

    // initialisation des stats de tous les poketudiants
    tabAtk[parlfor] = 60;
    tabDef[parlfor] = 40;
    tabPvMax[parlfor] = 60;

    tabAtk[ismar] = 50;
    tabDef[ismar] = 30;
    tabPvMax[ismar] = 40;

    tabAtk[rigolamor] = 85;
    tabDef[rigolamor] = 55;
    tabPvMax[rigolamor] = 70;

    tabAtk[procrastino] = 40;
    tabDef[procrastino] = 60;
    tabPvMax[procrastino] = 60;

    tabAtk[couchtar] = 30;
    tabDef[couchtar] = 50;
    tabPvMax[couchtar] = 40;

    tabAtk[nuidebou] = 55;
    tabDef[nuidebou] = 85;
    tabPvMax[nuidebou] = 70;

    tabAtk[alabourre] = 75;
    tabDef[alabourre] = 95;
    tabPvMax[alabourre] = 65;

    tabAtk[buchafon] = 50;
    tabDef[buchafon] = 50;
    tabPvMax[buchafon] = 60;

    tabAtk[belmention] = 30;
    tabDef[belmention] = 50;
    tabPvMax[belmention] =40 ;

    tabAtk[promomajor] = 70;
    tabDef[promomajor] = 70;
    tabPvMax[promomajor] = 70;

    tabAtk[enseignant_dresseur] = 100;
    tabDef[enseignant_dresseur] = 100;
    tabPvMax[enseignant_dresseur] = 100;

    //chargement des puissance celon l'attaque
    tabPuissance[bavardage] = 10;
    tabPuissance[groboucan] = 15;
    tabPuissance[megaphone_vocal] = 20;
    tabPuissance[batillement] = 10;
    tabPuissance[ptisomme] = 15;
    tabPuissance[superdodo] = 20;
    tabPuissance[rateletrin] = 15;
    tabPuissance[oboulo] = 10;
    tabPuissance[exo_maison] = 15;
    tabPuissance[max_reviz] = 20;
    tabPuissance[titquestion] = 10;
    tabPuissance[poser_colle] = 15;
    tabPuissance[fatal_interro] = 20;

    //chargement des types
    tabEfficace[noisy] = lazy;
    tabEfficace[lazy] = motivated;
    tabEfficace[motivated] = noisy;
    //tabEfficace[teacher] = ;

    imgFleche = LoadTexture2(game.ecran.renderer,"src/gfx/fleche.png");

    // ==================================== GUI ====================================

    loadMenu();

    loadServeur();

    loadPartie();
   
    return 1;
}

