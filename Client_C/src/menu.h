#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include "gui.h"




SDL_Texture *menuImg;// img fond du menu
SDL_Texture *textTitre; // texture pour le titre du menu


void libereMenu();
int loadMenu();

int drawMenu();
int updateMenu();

#endif