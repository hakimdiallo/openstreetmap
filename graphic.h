#ifndef _GRAPHIC_H_
  #define _GRAPHIC_H_
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include "osm.h"
#include "osm_structure.h"

void afficher(xmlNodePtr noeud);
void dessiner_trait_noeuds(my_node n1, my_node n2, SDL_Renderer *renderer);
void dessiner_way(my_way way, SDL_Renderer *renderer);
void dessiner_way_bis(my_way way, SDL_Renderer *renderer);

#endif
/*
void attendreTouche();//Attend que l'utilisateur appuie sur une touche ou la croix rouge
void draw_fenetre(SDL_Surface **ecran,int x,int y,char title[] );//Crée une fenêtre de taille x*y avec un titre
void effacerEcran(SDL_Surface *ecran,Uint32 coul);//Remplit entièrement l'écran de la couleur choisit
void actualiser(SDL_Surface *ecran);//mise à jour de l'écran entier
void setPixel(SDL_Surface *ecran,int x, int y, Uint32 coul);//déssine un pixel sur le point de coordonnées x,y sur la fenêtre
//déssine un pixel sur le point de coordonnées x,y sur la fenêtre et ne fait rien
// si les coordonnées dépasse les limites de la fenêtre
void setPixelVerif(SDL_Surface *ecran,int x, int y, Uint32 coul);
//Déssine un rectangle plein
//les paramètres sont les coordonnées du point supérieur gauche(x,y), la largeur w, la hauteur h et le code couleur.
void barre(SDL_Surface *ecran,int x, int y, int w, int h, Uint32 coul);

//Déssine une ligne horizontale
//les paramètres sont les coordonnées du point supérieur gauche(x,y), la largeur w et le code couleur.
void ligneHorizontale(SDL_Surface *ecran,int x, int y, int w, Uint32 coul);

//Déssine une ligne verticale
//les paramètres sont les coordonnées du point supérieur gauche(x,y), la hauteur h et le code couleur.
void ligneVerticale(SDL_Surface *ecran,int x, int y, int h, Uint32 coul);
void rectangle(SDL_Surface *ecran,int x, int y, int w, int h, Uint32 coul);//Déssine un rectangle vide
//Dessine une ligne quelconques
//(x1,y1) le point de départ et (x2,y2) le point d'arrivée
void ligne(SDL_Surface *ecran,int x1, int y1, int x2, int y2, Uint32 coul);
//Déssine un cercle vide avec comme centre (cx,cy) et un rayon de  (rayon)
void cercle(SDL_Surface *ecran,int cx, int cy, int rayon, Uint32 coul);
//Déssine un cercle plein de couleur (coul) avec pour centre cx,cy et pour rayon (rayon)
void disque(SDL_Surface *ecran,int cx, int cy, int rayon, Uint32 coul);
*/
