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

#ifndef _OSM_STRUCTURE_H_
	#define _OSM_STRUCTURE_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <libxml/tree.h>


#define MY_TAG_SIZE 20
#define MY_NODE_SIZE 100
#define ACTIVE 1

//Structure de tag du document osm
typedef struct my_tag {
	char *key;
	char *value;
} my_tag;

//structure qui contient l'attribut en commun de chaque noeud du document osm
typedef struct my_attributs {
	char id[20];
	char visible[10];
} my_attributs;

//structure du noeud  "node"
typedef struct my_node {
	double lon;
	double lat;
	my_attributs at;
	GHashTable *tag;
} my_node;

//structure du noeud "way"
typedef struct my_way {
	my_attributs at;
	GSList *nodes;
	GHashTable *tag;
	int drawn;
} my_way;

//structure du noeud "relation"
typedef struct my_relation{
	my_attributs at;
	GSList *ways_inner;
	GSList *ways_outer;
	GSList *ways;
	GSList *nodes;
	GSList *relations;
	GHashTable *tags;
}my_relation;

//structure du noeud "area"
typedef struct my_area {
	my_way w;
}area;

//structure du noeud bounds
typedef struct my_bounds{
	double maxlat;
	double minlat;
	double maxlon;
	double minlon;
}my_bounds;

//Innitialise la structure my_way
my_way* init_my_way();

//Initialise un noeud
my_node* init_my_node();

//Initialise un bound
my_bounds* init_my_bounds();

my_relation* init_my_relation();

//ajoute un tag dans un way
void add_tag_my_way(my_way *way,my_tag *tag);

//ajoute un noeud dans un way
void add_node_my_way(my_way *way, char *idNode);

//ajoute un tag dans un node
void add_tag_my_node(my_node *node, my_tag *tag);

//ajoute l'id d'un way dans une rélation
void add_way_to_relation(my_relation *rel, char *idWay, xmlChar *role);

//ajoute l'id d'un node dans une rélation
void add_node_to_relation(my_relation *rel, char *idNode);

//ajoute un tag dans une rélation
void add_tag_to_relation(my_relation *rel, my_tag *tag);

//ajoute l'id d'une rélation dans une rélation
void add_relation_to_relation(my_relation *rel, char *idRel);

//libère une structure my_tag
void free_my_tag(my_tag *tag);

//libère la structure my_way
void free_my_way(my_way *way);

//Libère un tableau de ways
void free_my_ways(GHashTable *ways);

//Libère la structure my_node
void free_my_node(my_node *node);

//Libère l'hashmap de noeuds
void free_my_nodes(GHashTable *nodes);

//Libère la structure my_bounds
void free_my_bound(my_bounds *bound);

//Libère la structure de donnée rélation
void free_my_relation(my_relation *rel);

//Libère l'hashtable des rélations
void free_my_relations(GHashTable *rel);

#endif
