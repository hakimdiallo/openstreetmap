#include "graphic.h"


void dessiner_trait_noeuds(node n1, node n2, SDL_Renderer *renderer){
  int x1 = calcul_coor_x(n1.lon);
  int y1 = calcul_coor_y(n1.lat);
  int x2 = calcul_coor_x(n2.lon);
  int y2 = calcul_coor_y(n2.lat);
  if(DEBUG)
    printf("x1 %d y1 %d x2 %d y2 %d\n", x1, y1, x2, y2);
  SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
	SDL_RenderPresent(renderer);
}

void afficher(xmlNodePtr noeud) {
        if (noeud->type == XML_ELEMENT_NODE ) {
    	    xmlChar *id=xmlGetProp(noeud,(const xmlChar *)"id");//retourne valeur de l'attribut id du noeud
    	    xmlChar *visible=xmlGetProp(noeud,(const xmlChar *)"visible");
    	    xmlChar *k=xmlGetProp(noeud,(const xmlChar *)"k");
    	    xmlChar *v=xmlGetProp(noeud,(const xmlChar *)"v");
          if(DEBUG){
      	    printf("noeud:%s , ",noeud->name);
      	    if(id!=NULL)
      	      printf("id:%s , ",id);
      	    if(visible!=NULL)
      	      printf("visible:%s , ",visible);
      	    if(k!=NULL)
      	      printf("k:%s , ",k);
      	    if(v!=NULL)
      	      printf("v:%s , ",v);
      	    printf("\n");
          }
    	    xmlFree(id);
    	    xmlFree(visible);
    	    xmlFree(k);
    	    xmlFree(v);
        }
}

/*
void draw_fenetre(SDL_Surface **ecran,int x,int y,char title[] ){
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
      fprintf(stderr, "Erreur d'initialisation de la SDL");
      exit(EXIT_FAILURE);
    }
    //Termine le programme en appelant la fonction SDL_Quit
    atexit(SDL_Quit);
    *ecran=SDL_SetVideoMode(x, y, 32, SDL_HWSURFACE); // Ouverture de la fenêtre
    if(ecran==NULL){// Initialisation de la SDL
      fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
      exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption(title, NULL);
}

//Attend que l'utilisateur appuie sur une touche ou la croix rouge
void attendreTouche(void)
{
  SDL_Event event;

  do
    SDL_WaitEvent(&event);
  while (event.type != SDL_QUIT && event.type != SDL_KEYDOWN);
}

//Remplit entièrement l'écran de la couleur choisit
void effacerEcran(SDL_Surface *ecran,Uint32 coul)
{
  //La valeur NULL permet de remplir tout l'écran
  SDL_FillRect(ecran, NULL, coul);
}

//mise à jour de l'écran entier
void actualiser(SDL_Surface *ecran)
{
  SDL_UpdateRect(ecran, 0, 0, 0, 0);
}

//déssine un pixel sur le point de coordonnées x,y sur la fenêtre
void setPixel(SDL_Surface *ecran,int x, int y, Uint32 coul)
{
  *((Uint32*)(ecran->pixels) + x + y * ecran->w) = coul;
}

//déssine un pixel sur le point de coordonnées x,y sur la fenêtre et ne fait rien
// si les coordonnées dépasse les limites de la fenêtre
void setPixelVerif(SDL_Surface *ecran,int x, int y, Uint32 coul)
{
  if (x >= 0 && x < ecran->w &&
      y >= 0 && y < ecran->h)
    setPixel(ecran,x, y, coul);
}


//Déssine un rectangle plein
//les paramètres sont les coordonnées du point supérieur gauche(x,y), la largeur w, la hauteur h et le code couleur.
void barre(SDL_Surface *ecran,int x, int y, int w, int h, Uint32 coul)
{
  SDL_Rect r;

  r.x = x;
  r.y = y;
  r.w = w;
  r.h = h;

  SDL_FillRect(ecran, &r, coul);
}



//Déssine une ligne horizontale
//les paramètres sont les coordonnées du point supérieur gauche(x,y), la largeur w et le code couleur.
void ligneHorizontale(SDL_Surface *ecran,int x, int y, int w, Uint32 coul)
{
  SDL_Rect r;

  r.x = x;
  r.y = y;
  r.w = w;
  r.h = 1;

  SDL_FillRect(ecran, &r, coul);
}


//Déssine une ligne verticale
//les paramètres sont les coordonnées du point supérieur gauche(x,y), la hauteur h et le code couleur.
void ligneVerticale(SDL_Surface *ecran,int x, int y, int h, Uint32 coul)
{
  SDL_Rect r;

  r.x = x;
  r.y = y;
  r.w = 1;
  r.h = h;

  SDL_FillRect(ecran, &r, coul);
}


//Déssine un rectangle vide
void rectangle(SDL_Surface *ecran,int x, int y, int w, int h, Uint32 coul)
{
  ligneHorizontale(ecran,x, y, w, coul);
  ligneHorizontale(ecran,x, y + h - 1, w, coul);
  ligneVerticale(ecran,x, y + 1, h - 2, coul);
  ligneVerticale(ecran,x + w - 1, y + 1, h - 2, coul);
}
//Dessine une ligne quelconques
//(x1,y1) le point de départ et (x2,y2) le point d'arrivée
void echangerEntiers(int* x, int* y)
{
  int t = *x;
  *x = *y;
  *y = t;
}

void ligne(SDL_Surface *ecran,int x1, int y1, int x2, int y2, Uint32 coul)
{
  int d, dx, dy, aincr, bincr, xincr, yincr, x, y;

  if (abs(x2 - x1) < abs(y2 - y1)) {
    // parcours par l'axe vertical

    if (y1 > y2) {
      echangerEntiers(&x1, &x2);
      echangerEntiers(&y1, &y2);
    }

    xincr = x2 > x1 ? 1 : -1;
    dy = y2 - y1;
    dx = abs(x2 - x1);
    d = 2 * dx - dy;
    aincr = 2 * (dx - dy);
    bincr = 2 * dx;
    x = x1;
    y = y1;

    setPixelVerif(ecran,x, y, coul);

    for (y = y1+1; y <= y2; ++y) {
      if (d >= 0) {
	x += xincr;
	d += aincr;
      } else
	d += bincr;

      setPixelVerif(ecran,x, y, coul);
    }

  } else {
    // parcours par l'axe horizontal

    if (x1 > x2) {
      echangerEntiers(&x1, &x2);
      echangerEntiers(&y1, &y2);
    }

    yincr = y2 > y1 ? 1 : -1;
    dx = x2 - x1;
    dy = abs(y2 - y1);
    d = 2 * dy - dx;
    aincr = 2 * (dy - dx);
    bincr = 2 * dy;
    x = x1;
    y = y1;

    setPixelVerif(ecran,x, y, coul);

    for (x = x1+1; x <= x2; ++x) {
      if (d >= 0) {
	y += yincr;
	d += aincr;
      } else
	d += bincr;

      setPixelVerif(ecran,x, y, coul);
    }
  }
}

//Déssine un cercle vide avec comme centre (cx,cy) et un rayon de  (rayon)
void cercle(SDL_Surface *ecran,int cx, int cy, int rayon, Uint32 coul)
{
  int d, y, x;

  d = 3 - (2 * rayon);
  x = 0;
  y = rayon;

  while (y >= x) {
    setPixelVerif(ecran,cx + x, cy + y, coul);
    setPixelVerif(ecran,cx + y, cy + x, coul);
    setPixelVerif(ecran,cx - x, cy + y, coul);
    setPixelVerif(ecran,cx - y, cy + x, coul);
    setPixelVerif(ecran,cx + x, cy - y, coul);
    setPixelVerif(ecran,cx + y, cy - x, coul);
    setPixelVerif(ecran,cx - x, cy - y, coul);
    setPixelVerif(ecran,cx - y, cy - x, coul);

    if (d < 0)
      d = d + (4 * x) + 6;
    else {
      d = d + 4 * (x - y) + 10;
      y--;
    }

    x++;
  }
}

//Déssine un cercle plein de couleur (coul) avec pour centre cx,cy et pour rayon (rayon)
void disque(SDL_Surface *ecran,int cx, int cy, int rayon, Uint32 coul)
{
  int d, y, x;

  d = 3 - (2 * rayon);
  x = 0;
  y = rayon;

  while (y >= x) {
    ligneHorizontale(ecran,cx - x, cy - y, 2 * x + 1, coul);
    ligneHorizontale(ecran,cx - x, cy + y, 2 * x + 1, coul);
    ligneHorizontale(ecran,cx - y, cy - x, 2 * y + 1, coul);
    ligneHorizontale(ecran,cx - y, cy + x, 2 * y + 1, coul);

    if (d < 0)
      d = d + (4 * x) + 6;
    else {
      d = d + 4 * (x - y) + 10;
      y--;
    }

    x++;
  }
}
*/
