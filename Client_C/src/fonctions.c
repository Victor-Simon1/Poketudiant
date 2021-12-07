
#include <stdio.h>
#include <string.h>

#include <SDL.h>
#include "SDL_mixer.h"
#include "SDL_image.h"

#include "game.h"
#include "gui.h"






// recupere et gere les evenements clavier
int eventClavier(){ 

    while(SDL_PollEvent(&event)){
       if(strcmp(game.affichage,"GAME") == 0){
            switch(event.type){
                case SDL_KEYDOWN:                            
                // ============================= apppuie sur une touche =============================
                    switch(event.key.keysym.sym){
                        case SDLK_m: // affiche ou non la minimap
                            
                        break;           
                    }
                    continue;
                // ============================= clique de la souirs =============================
                case SDL_MOUSEBUTTONDOWN:                            
                    if(event.button.button == SDL_BUTTON_LEFT){

                    }
                break;
                // ============================= relachement de la souris =============================
                case SDL_MOUSEBUTTONUP: 
                    if(event.button.button == SDL_BUTTON_LEFT){

                    }      
                break;
                // ============================= relachement d'une touche =============================
                case SDL_KEYUP:  
                    switch(event.key.keysym.sym){
                        
                    }
                    continue;
                // ============================= si on bouge la souris =============================
                case SDL_MOUSEMOTION: 

                break;
                case SDL_QUIT: // si on ferme la fenetre
                    running = false;
                    break;
                default:
                    break;
            }
        }
        else if(strcmp(game.affichage, "MENU") == 0){
            switch(event.type){
                case SDL_QUIT: // si on ferme la fenetre
                    running = false;
                    break;
                default:
                    break;
            }
        }
        else if(strcmp(game.affichage, "SERVEUR") == 0){
            switch(event.type){
                case SDL_QUIT: // si on ferme la fenetre
                    running = false;
                    break;
                default:
                    break;
            }
        }

    }
    return 1;
}



/*
  _   _   ____    ____       _      _____   _____  
 | | | | |  _ \  |  _ \     / \    |_   _| | ____| 
 | | | | | |_) | | | | |   / _ \     | |   |  _|   
 | |_| | |  __/  | |_| |  / ___ \    | |   | |___  
  \___/  |_|     |____/  /_/   \_\   |_|   |_____| 
                                                  
*/

int update(){
    

    // =========================== Gestion des events (clavier) ===============================


    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]) // HAUT
    {
       
    }
    if (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S]) // BAS
    {
   
    }
    if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D]) /// DROITE
    {
   
    }
    if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A]) // GAUCHE 
    {
 
    }
    
    
  

    
    
    // mise a jour de l'interface graphique
    updateGui();
    
    return 1;
    
}

/*
  ____    ____       _     __        __
 |  _ \  |  _ \     / \    \ \      / /
 | | | | | |_) |   / _ \    \ \ /\ / / 
 | |_| | |  _ <   / ___ \    \ V  V /  
 |____/  |_| \_\ /_/   \_\    \_/\_/   
                                     
*/

int draw(){ // affichage du jeu
    SDL_RenderClear(game.ecran.renderer); // Efface l'écran
   
    

    // =================================== affichage le player ==============================

    

        

    
    
   
        drawGui();

    SDL_RenderPresent(game.ecran.renderer); // Présente l'écran
    return 1;
}