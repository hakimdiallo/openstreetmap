#ifndef _GRAPHIC_OPENGL_H_
  #define _GRAPHIC_OPENGL_H_
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "osm.h"
#include "osm_structure.h"
#include <SDL_opengl.h>
#include <GL/glut.h>

#define ZOOM 0.2f
#define MAX_ZOOM 30
#define MIN_ZOOM 0.25


#define HIGHWAY_WIDTH 5.0f
#define WATER_DEPTH 0.0
#define BULDING_DEPTH 0.1
#define INNER_DEPTH 0.9
#define HIGHWAY_DEPTH 1.0

//Dessine une ligne avec une couleur , une largeur et une profondeur
void draw_line( my_way *way, GHashTable *nodes, GLfloat width, GLdouble depth, GLubyte r, GLubyte g, GLubyte b);
//Dessine une ligne en pointillé
void draw_line_stipple(my_way *way, GHashTable *nodes, GLfloat width, GLdouble depth, GLubyte r, GLubyte g, GLubyte b);

void draw_polygon(my_way *way, GHashTable *nodes, GLdouble depth, GLubyte r, GLubyte g, GLubyte b);

//Dessine un way
void draw_way(my_way *w, GHashTable *ways, GHashTable *nodes);
//parcour une hashtable de way et dessine un way
void draw_ways(GHashTable *hash_ways, GHashTable *hash_nodes);

void rendererMap_opengl(GHashTable *hash_ways, GHashTable *hash_nodes, GHashTable *hash_relations);

#endif
