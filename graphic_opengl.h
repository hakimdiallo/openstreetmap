#ifndef _GRAPHIC_OPENGL_H_
  #define _GRAPHIC_OPENGL_H_
#include <SDL_opengl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include "osm.h"
#include "osm_structure.h"

#define ZOOM 0.009f
#define MAX_ZOOM 3.0
#define MIN_ZOOM 0.25


#define WATER_DEPTH 0.1
#define BULDING_DEPTH 0.3
#define AREA_DEPTH 0.25
#define BULDING_COUNTOUR_DEPTH 0.4
#define LANDUSE_DEPTH 0.7
#define INNER_DEPTH 0.5
#define PEDEST_DEPTH 0.2
#define HIGHWAY_DEPTH 0.8
#define HIGHWAY_DEPTH_SND 0.9

#define CONTOUR_WIDTH 1
#define HIGHWAY_WIDTH 5.0f
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

void draw_relations(GHashTable *relations, GHashTable *ways, GHashTable *nodes);
void draw_one_relation(my_relation *rel, GHashTable *relations, GHashTable *ways, GHashTable *nodes);

#endif
