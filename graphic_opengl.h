/*
    Copyright (C) 2016

    Authors:
      - Souleymane DIALLO diallosouleymane.07@gmail.com
      - Jules Camille ZIRIGA julesziriga@gmail.com
      - Leila NAIT HAMOUD houacineleila@outlook.fr

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef _GRAPHIC_OPENGL_H_
  #define _GRAPHIC_OPENGL_H_
#include <SDL_opengl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include "osm_structure.h"

#define ZOOM 0.009f
#define MAX_ZOOM 3.0
#define MIN_ZOOM 0.25

#define WIDTH 1000
#define HEIGHT 700

#define WATER_DEPTH 0.1
#define BULDING_DEPTH 0.3
#define AREA_DEPTH 0.25
#define BULDING_COUNTOUR_DEPTH 0.4
#define LANDUSE_DEPTH 0.7
#define LAND_DEPTH 0.73
#define INNER_DEPTH 0.5
#define PEDEST_DEPTH 0.2
#define STEP_WAY_DEPTH 0.75
#define RAILWAY_DEPTH 0.74
#define HIGHWAY_DEPTH 0.8
#define HIGHWAY_DEPTH_SND 0.9

#define CONTOUR_WIDTH 1
#define HIGHWAY_WIDTH 5.0f
#define SERVICE_WIDTH 3
#define PEDEST_WIDTH 5
#define FOOTWAY_WIDTH 2
#define TRACK_WIDTH 2
#define BUS_G_WIDTH 4
#define ROAD_WIDTH 2
#define BRIDLEWAY_WIDTH 2
#define CYCLEWAY_WIDTH 2

#define SHOW_TEXT 0

//Dessine une ligne avec une couleur , une largeur et une profondeur à l'aide d'un way
void draw_line( my_way *way, GHashTable *nodes, GLfloat width, GLdouble depth, GLubyte r, GLubyte g, GLubyte b);

//Dessine une ligne en pointillé  à l'aide d'un way
void draw_line_stipple(my_way *way, GHashTable *nodes, GLfloat width, GLdouble depth, GLubyte r, GLubyte g, GLubyte b);

//Déssine un polygone concave  à l'aide d'un way
void draw_polygon(my_way *way, GHashTable *nodes, GLdouble depth, GLubyte r, GLubyte g, GLubyte b);

//Dessine un way
void draw_way(my_way *w, GHashTable *ways, GHashTable *nodes);

//parcour une hashtable de way et dessine un way
void draw_ways(GHashTable *hash_ways, GHashTable *hash_nodes);

//Déssine la fenêtre graphique avec les éléments du fichier osm
void rendererMap_opengl(GHashTable *hash_ways, GHashTable *hash_nodes, GHashTable *hash_relations);

//Déssine les rélations du document osm
void draw_relations(GHashTable *relations, GHashTable *ways, GHashTable *nodes);

//déssine une rélation
void draw_one_relation(my_relation *rel, GHashTable *relations, GHashTable *ways, GHashTable *nodes);

//Déssine les rélations et les ways sur une fenêtre
void draw_relations_and_ways(SDL_Window *win, GHashTable *hash_relations, GHashTable *hash_ways, GHashTable *hash_nodes);

#endif
