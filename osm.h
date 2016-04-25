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

#ifndef _OSM_H_
	#define _OSM_H_
#include <stdio.h>
#include <stdlib.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>
#include<SDL.h>
#include <math.h>
#include "osm_structure.h"

#define opengl 1
#define DEBUG 0
#define WIDTH 1000
#define HEIGHT 700




typedef void (*fct_parcours_t)(GHashTable *relations, GHashTable *ways, GHashTable *nodes, my_bounds *bound, xmlNodePtr noeud);

//parcours en largeur des noeuds fils du noeud <osm>(document osm) et applique une fonction sur chaque noeud
void parcours_largeur(GHashTable *relations, GHashTable *ways, GHashTable *nodes, my_bounds *bound, xmlNodePtr noeud, fct_parcours_t f);

//Stocke un noeud osm dans une hashtable de way (noeud way), de node(noeud node) ou bound (noeud bound)
void stockageNoeudsOSM(GHashTable *relations, GHashTable *ways, GHashTable *nodes, my_bounds *bound, xmlNodePtr noeud);

//Rempli l'hashtable de way, de nodes et le bound en fonction du document xml entré en paramètre
void parse_file(GHashTable *relations, GHashTable *ways, GHashTable *nodes, my_bounds *bound, char *name);

//Rempli l'hashtable de ways avec les informations du noeud en paramètre
void setWayInformation(GHashTable *ways, xmlNodePtr noeud);

//Rempli l'hashtable de node avec les informations du noeud
void setNodeInformations(GHashTable *nodes, xmlNodePtr noeud, my_bounds *bound);

//retourne une structure my_tag : la clé k et la valeur v d'un noeud
my_tag *getTagInformations(xmlNodePtr node);

//Rempli la variable bound en fonction du fichier entré en paramètre
void setBoundInformations(my_bounds *bound, xmlNodePtr noeud);

//rempli la structure rélation en fonction du fichier osm
void setRelationInformations(GHashTable *relations, xmlNodePtr noeud);

#endif
