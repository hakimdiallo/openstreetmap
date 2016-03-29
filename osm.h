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
#include "hashmap.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>
#include <SDL.h>
#include <math.h>
#include "osm_structure.h"


#define DEBUG 0
#define WIDTH 900
#define HEIGHT 650
#define CIRC_TERRE 40075.00
#define RAYON_TERRE 6371.00



typedef void (*fct_parcours_t)(GHashTable *ways, GHashTable *nodes, my_bounds *bound, xmlNodePtr noeud);

//parcours en largeur des noeuds fils du noeud <osm>(document osm) et applique une fonction sur chaque noeud
void parcours_largeur(GHashTable *ways, GHashTable *nodes, my_bounds *bound, xmlNodePtr noeud, fct_parcours_t f);

xmlDocPtr parse_file(char *name); // Parse un document xml et retourne un pointeur sur le document xml

//Stocke un noeud osm dans une hashtable de way (noeud way), de node(noeud node) ou bound (noeud bound)
void stockageNoeudsOSM(GHashTable *ways, GHashTable *nodes, my_bounds *bound, xmlNodePtr noeud);

//Rempli l'hashtable de way, de nodes et le bound en fonction du document xml entré en paramètre
void parse_file_v(GHashTable *ways, GHashTable *nodes, my_bounds *bound, char *name);

//Rempli l'hashtable de ways avec les informations du noeud en paramètre
void setWayInformation(GHashTable *ways, xmlNodePtr noeud);

//Rempli l'hashtable de node avec les informations du noeud
void setNodeInformations(GHashTable *nodes, xmlNodePtr noeud, my_bounds *bound);

//retourne une structure my_tag : la clé k et la valeur v d'un noeud
my_tag *getTagInformations(xmlNodePtr node);

//Rempli la variable bound en fonction du fichier entré en paramètre
void setBoundInformations(my_bounds *bound, xmlNodePtr noeud);

#endif
