#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <SDL.h>
#include "SDL_mixer.h"
#include "SDL_image.h"

#include "game.h"
#include "gui.h"
#include "fonctions.h"
#include "load.h"
#include "menu.h"
#include "serveur.h"
#include "client.h"
#include "player.h"
#include "partie.h"


/*

  __  __      _      ___   _   _ 
 |  \/  |    / \    |_ _| | \ | |
 | |\/| |   / _ \    | |  |  \| |
 | |  | |  / ___ \   | |  | |\  |
 |_|  |_| /_/   \_\ |___| |_| \_|


*/

int main(int argc, char **argv){

    game.ecran.camera.h = 768; // hauteur ecran
    game.ecran.camera.w = 1024; // largeur ecran

    // ===================================== gestion SDL =====================================

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) // initialise la SDL
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Écriture de l'erreur
        return -1;
    }
    if(TTF_Init() == -1){ // initialise TTF pour les textes
        printf("SDL_ttf could not initialize! SDL_ttf Error:%s\n",TTF_GetError());
        return -1;
    }
    /*if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1){ //Initialisation de l'API Mixer pour les sons
        printf("%s", Mix_GetError());
    }*/

    // création de la fenetre
    game.ecran.windows = SDL_CreateWindow("Poketudiant Online",      // nom de la fenètre
                                            SDL_WINDOWPOS_UNDEFINED, // x
                                            SDL_WINDOWPOS_UNDEFINED, // y
                                            game.ecran.camera.w, // largeur
                                            game.ecran.camera.h, // hauteur
                                            SDL_WINDOW_SHOWN); // visible

    if (game.ecran.windows == NULL)
    {
        SDL_Log("Could not create a window: %s", SDL_GetError());
        return -1;
    }

    game.ecran.renderer = SDL_CreateRenderer( game.ecran.windows, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // SDL_RENDERER_ACCELERATED qui permet au renderer de travailler avec l'acceleration materielle
    if (game.ecran.renderer == NULL)
    {
        SDL_Log("Could not create a renderer: %s", SDL_GetError());
        return -1;
    }
    else
    {
        int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
        if (!(IMG_Init(imgFlags) & imgFlags))
        {
            printf("SDL_image could not initialize! SDL_image error: %s\n", IMG_GetError());
            return -1;
        }
    }

    SDL_SetRenderDrawBlendMode(game.ecran.renderer, SDL_BLENDMODE_BLEND); // activer la transparence
    

    if(load() == -1){ // chargement du jeu
        running = false; 
    }

    while (running){
        // =========== delta time ===============
        game.fps.last_tick_time = game.fps.tick_time;        
        game.fps.tick_time = SDL_GetTicks(); 
        game.fps.delta = game.fps.tick_time - game.fps.last_tick_time; // delta entre les 2 derniers affichage
        game.fps.delta = game.fps.delta/1000; // tranforme en seconde
        game.fps.compteur += game.fps.delta;
        game.fps.nb_fps++;
        
        if(game.fps.compteur >= 1){ // si 1 seconde écoulée
            game.fps.compteur = 0;
            //SDL_Log("======================== fps : %d ==========================", game.fps.nb_fps);
            game.fps.nb_fps = 0;
        }   

        eventClavier(); // gere les events clavier/souris

        if(strcmp(game.affichage, "GAME") == 0){ // si on est en jeu
            if(update() == -1 || draw() == -1){
                running = false;      
                break;      
            }
        }
        else if(strcmp(game.affichage, "MENU") == 0){ // si on est dans le menu
            if(updateMenu() == -1 || drawMenu() == -1){
                running = false;      
                break;      
            }
        }    
        else if(strcmp(game.affichage, "SERVEUR") == 0){ // si on est dans l'affichage des serveurs
            if(updateServeur() == -1 || drawServeur() == -1){     
                running = false;      
                break;      
            }
        } 
        else if(strcmp(game.affichage, "PARTIE") == 0){ // si on est dans l'affichage des parties
            if(updatePartie() == -1 || drawPartie() == -1){     
                running = false;      
                break;      
            }
        }       
        
        // =================== bride les fps du programme ===================
        /*
        delay = 1.0/60.0;
       // printf("delta : %lf\n", game.fps.delta);
       // printf("delay : %lf\n", delay);
        if(game.fps.delta < delay){ // si on est plus rapide que 60 fps
            SDL_Delay((delay - game.fps.delta)*1000); // on attend
        }
        */
    }

    // ============= quitte la SDL =============
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
    //Mix_CloseAudio();

    // ============= client =============
    client_close_and_free(clientTCP);

    player = destroyPoketudiant(player);

    // ============= font ==============
    TTF_CloseFont(police);
    police = NULL;
    TTF_CloseFont(policeTitre);
    policeTitre = NULL;

    // ============= GUI =============
    freeListeGroupe(listeGroupes);
    listeGroupes = NULL;

    SDL_DestroyTexture(imgFleche);  
    imgFleche = NULL;

    SDL_DestroyTexture(herbeImg);  
    imgFleche = NULL;
    SDL_DestroyTexture(soinImg);  
    imgFleche = NULL;
    SDL_DestroyTexture(buissonImg);  
    imgFleche = NULL;

    SDL_DestroyTexture(player1Img);  
    imgFleche = NULL;
    SDL_DestroyTexture(player2Img);  
    imgFleche = NULL;
    SDL_DestroyTexture(player3Img);  
    imgFleche = NULL;
    SDL_DestroyTexture(player4Img);  
    imgFleche = NULL;

    libereMenu();
    libereServeur();
    liberePartie();

    return 0;
}