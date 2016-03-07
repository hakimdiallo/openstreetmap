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

#define DEBUG 0
#define WIDTH 500
#define HEIGHT 600
#define CIRC_TERRE 40075.00


typedef void (*fct_parcours_t)(xmlNodePtr);//pointeur sur une fonction qui retourne un type int


extern my_bounds bn;

xmlDocPtr parse_file(char *name); // Parse un document xml et retourne un pointeur sur le document xml
xmlNodePtr get_root(xmlDocPtr doc); // retourne le noeud racine s'il existe ou null sinon
void free_file(xmlDocPtr doc); // Libere le fichier xml (Libère la mémoire)
void parcours_prefixe(xmlNodePtr noeud, fct_parcours_t f); // Parcours en profondeur des noeuds du fichier xml
xmlXPathContextPtr get_xpath_contexte(xmlDocPtr doc);
xmlXPathObjectPtr getNode_by_xpathExpression(char *nodePath, xmlXPathContextPtr ctxt);
my_way **xpath_parcours(xmlXPathObjectPtr xpathRes, xmlXPathContextPtr ctxt); // parcours un document xml par xpath
void parcours_des_noeuds_fils(xmlNodePtr n, xmlXPathContextPtr ctxt, my_way **ways, int count);
xmlNodePtr getNode_by_id(xmlChar *ref, xmlXPathContextPtr ctxt);
my_node *getNodeInformations(xmlNodePtr noeud);
my_bounds getBoundInformations(xmlXPathContextPtr ctxt); //
void parcours_attributs(xmlNodePtr noeud);
int calcul_coor_y(double d);
int calcul_coor_x(double d);
my_tag getTagInformations(xmlNodePtr node);
my_hashmap_node* stockage_nodes(xmlXPathContextPtr ctxt);
#endif
