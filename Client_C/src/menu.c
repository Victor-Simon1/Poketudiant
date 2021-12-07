
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "gui.h"
#include "game.h"
#include "menu.h"
#include "fonctions.h"

/*

    ================================================ GESTION DE L ECRAN DU MENU ================================================

*/

int updateMenu(){ // mise a jour du menu

    updateGui();
    

    return 1;

}  

int loadMenu(){ // charge le menu

    // Titre
    textTitre = CreateFont(game.ecran.renderer, policeTitre, "Poketudiant", game.couleur.jaune);    
   
    //img fond
    menuImg = LoadTexture2(game.ecran.renderer,"src/gfx/ImgFond.png");
   
    groupeMenu = creerGroupe();
    groupeMenu->actif = true;

    Buttons ButtonServeur = creerBouton("src/gfx/boutonServeurs.png", "src/gfx/boutonServeurHover.png", "src/gfx/boutonServeurHover.png", 
                                                                                                game.ecran.camera.w/2 , 
                                                                                                game.ecran.camera.h/2 , 
                                                                                                150, 50, 
                                                                                                &changeAffichage,
                                                                                                "SERVEUR");
    
   ButtonServeur->box.x -= ButtonServeur->box.w/2;
   ButtonServeur->box.y -= ButtonServeur->box.h/2;

    groupeMenu->listeButtons =ajouter_teteButton(groupeMenu->listeButtons , ButtonServeur);// ajoute le bouton serveur au groupe
    

    Buttons quitButton = creerBouton("src/gfx/boutonQuitter.png", "src/gfx/boutonQuitterHover.png", "src/gfx/boutonQuitterHover.png", 
                                                                                                ButtonServeur->box.x , 
                                                                                                ButtonServeur->box.y+160 , 
                                                                                                150, 50, 
                                                                                                &changeAffichage,
                                                                                                "QUIT");

    
    groupeMenu->listeButtons = ajouter_teteButton(groupeMenu->listeButtons , quitButton);

    listeGroupes = ajouter_teteGroupes(listeGroupes, groupeMenu);// ajout le groupe menu



    return 1;
}

void libereMenu(){

    SDL_DestroyTexture(menuImg);  
    menuImg = NULL;

    SDL_DestroyTexture(textTitre);
    textTitre = NULL;

}


int drawMenu(){

    SDL_RenderClear(game.ecran.renderer); // Efface l'écran 

    SDL_Rect Rect = {0, 0, game.ecran.camera.w, game.ecran.camera.h};// fond
    SDL_RenderCopy(game.ecran.renderer,menuImg,NULL,&Rect);

    SDL_Rect rect2 = {game.ecran.camera.w/2 - 150, 2, 300, 40};// titre
    SDL_RenderCopy(game.ecran.renderer,textTitre,NULL,&rect2); 

    drawGui();

    SDL_RenderPresent(game.ecran.renderer); // Présente l'écran
    return 1;   
}
