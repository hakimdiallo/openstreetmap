#include "graphic.h"


void pause()
{
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}

void draw_fenetre(SDL_Surface *ecran,int x,int y ){
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
      fprintf(stderr, "Erreur d'initialisation de la SDL");
      exit(EXIT_FAILURE);
    }
  ecran=SDL_SetVideoMode(x, y, 32, SDL_HWSURFACE); // Ouverture de la fenêtre
  if(ecran==NULL){// Initialisation de la SDL
    fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  SDL_WM_SetCaption("Carte", NULL);
  pause(); // Mise en pause du programme
  SDL_Quit(); // Arrêt de la SDL
}
