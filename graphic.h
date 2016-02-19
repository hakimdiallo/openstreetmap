#ifndef _GRAPHIC_H_
  #define _GRAPHIC_H_
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

void pause();//Maintiens la fenêtre sur la machine jusqu'à ce que l'utilsateur la ferme
void draw_fenetre(SDL_Surface *ecran,int x,int y );//Dessine une fénêtre graphique

#endif
