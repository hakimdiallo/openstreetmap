#ifndef _OSM_STRUCTURE_H_
	#define _OSM_STRUCTURE_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>


#define MY_TAG_SIZE 20
#define MY_NODE_SIZE 100
#define ACTIVE 1


typedef struct my_tag {
	char key[200];
	char value[200];
} my_tag;

typedef struct my_attributs {
	char id[20];
	char visible[10];
	/*
		char *user;
		int uid;
		char *timestamp;
		char *version;
	*/
} my_attributs;

typedef struct my_node {
	double lon;
	double lat;
	my_attributs at;
	GHashTable *tag;
} my_node;

typedef struct my_way {
	my_attributs at;
	GSList *nodes;
	GHashTable *tag;
} my_way;

typedef struct my_relation{
	my_attributs at;
	GSList *ways;
	GSList *nodes;
	GSList *relation;
}my_relation;

typedef struct my_area {
	my_way w;
}area;

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

//ajoute un tag dans un way
void add_tag_my_way(my_way *way,my_tag *tag);

//ajoute un noeud dans un way
void add_node_my_way(my_way *way, char *idNode);

//ajoute un tag dans un node
void add_tag_my_node(my_node *node, my_tag *tag);

//détruit la structure my_way
void free_my_way(my_way *way);

//Libère un tableau de ways
void free_my_ways(GHashTable *ways);

//Libère la structure my_node
void free_my_node(my_node *node);

//Libère l'hashmap de noeuds
void free_my_nodes(GHashTable *nodes);

//Libère la structure my_bounds
void free_my_bound(my_bounds *bound);
#endif
