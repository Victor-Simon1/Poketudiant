#ifndef GAME_H
#define GAME_H

#include "stdbool.h"

#include <SDL.h>
#include "SDL_ttf.h"

typedef struct{
    SDL_Color noire;
    SDL_Color rouge;
}Couleur;

typedef struct {
    int x;
    int y;
    int w;
    int h;
}Camera;

typedef struct {
    SDL_Window *windows;
    SDL_Renderer *renderer;
    Camera camera;
}Ecran;

typedef struct {
    float delta; // temps passé entre chaque frame en seconde
    uint32_t last_tick_time;
    uint32_t tick_time;
    int nb_fps; // nombre de frame par seconde
    float compteur;
}Fps;

typedef struct{
    SDL_Color noir;
    SDL_Color rouge;
    SDL_Color jaune;
}Coulor;

typedef struct {
    Ecran ecran;
    Fps fps;
    Coulor couleur;
    char affichage[20];
}Game;


// =========== variables ==============
SDL_Event event; 
bool running;
Game game;

int choix;

SDL_Texture *imgFleche;// img fleche de selection

TTF_Font *police;
TTF_Font *policeTitre;

#endif