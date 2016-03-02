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

#define DEBUG 1
#define WIDTH 500
#define HEIGHT 600
#define CIRC_TERRE 40075.00


typedef void (*fct_parcours_t)(xmlNodePtr);//pointeur sur une fonction qui retourne un type int

typedef struct tag {
	char *key;
	char *value;
} tag;

typedef struct attributs {
	int id;
	char *visible;
	/*
		char *user;
		int uid;
		char *timestamp;
		char *version;
	*/
} attributs;

typedef struct node {
	double lon;
	double lat;
	//attributs at;
	//tag t[];
} node;

typedef struct way {
	attributs at;
	//node refs[];
	tag t[];
} way;

typedef struct area {
	way w;
}area;

typedef struct bounds{
	double maxlat;
	double minlat;
	double maxlon;
	double minlon;
}bounds;

extern bounds bn;

xmlDocPtr parse_file(char *name); // Parse un document xml et retourne un pointeur sur le document xml
xmlNodePtr get_root(xmlDocPtr doc); // retourne le noeud racine s'il existe ou null sinon
void free_file(xmlDocPtr doc); // Libere le fichier xml (Libère la mémoire)
void parcours_prefixe(xmlNodePtr noeud, fct_parcours_t f); // Parcours en profondeur des noeuds du fichier xml
void afficher(xmlNodePtr noeud);
xmlXPathContextPtr get_xpath_contexte(xmlDocPtr doc);
xmlXPathObjectPtr getNode_by_xpathExpression(char *nodePath, xmlXPathContextPtr ctxt);
void xpath_parcours(xmlXPathObjectPtr xpathRes, xmlXPathContextPtr ctxt, SDL_Renderer *renderer); // parcours un document xml par xpath
void parcours_des_noeuds_fils(xmlNodePtr n, xmlXPathContextPtr ctxt, SDL_Renderer *renderer);
xmlNodePtr getNode_by_id(xmlChar *ref, xmlXPathContextPtr ctxt);
node getNodeInformations(xmlNodePtr noeud);
bounds getBoundInformations(xmlXPathContextPtr ctxt); //
void parcours_attributs(xmlNodePtr noeud);
void dessiner_trait_noeuds(node n1, node n2, SDL_Renderer *renderer);
int calcul_coor_y(double d);
int calcul_coor_x(double d);
#endif
