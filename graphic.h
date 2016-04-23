#ifndef _GRAPHIC_H_
  #define _GRAPHIC_H_
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <GL/glut.h>
#include <SDL_opengl.h>
#include <SDL2_gfxPrimitives.h>
#include "osm.h"
#include "osm_structure.h"

void draw_line_with_width(SDL_Renderer *renderer, my_way *way, GHashTable *nodes, uint8_t w, uint8_t r, uint8_t g, uint8_t b);
void dessiner_ways(SDL_Renderer *renderer, GHashTable *ways, GHashTable *nodes);
void rendererMap(GHashTable *hash_ways, GHashTable *hash_nodes, GHashTable *hash_relations);
void dessiner_hash_ways(SDL_Renderer *renderer, GHashTable *ways, GHashTable *nodes);
void dessiner_relations(SDL_Renderer *renderer, GHashTable *relations, GHashTable *ways, GHashTable *nodes);
void dessiner_une_relation(SDL_Renderer *renderer, my_relation *rel, GHashTable *relations, GHashTable *ways, GHashTable *nodes);
void dessiner_way(SDL_Renderer *renderer, my_way *w, GHashTable *ways, GHashTable *nodes);
#endif
