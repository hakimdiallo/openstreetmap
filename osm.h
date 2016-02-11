#include <stdio.h>
#include <stdlib.h>
#include <libxml/tree.h>
#include <libxml/parser.h>

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
	int lon;
	int lat;
	attributs at;
	tag t[];
} node;

typedef struct way {
	attributs at;
	int *refs;
	tag t[];
} way;

typedef struct area {
	way w;
}area;

xmlDocPtr parse_file(char *name); // Parse un document xml et retourne un pointeur sur le document xml
xmlNodePtr get_root(xmlDocPtr doc); // retourne le noeud racine s'il existe ou null sinon
void free_file(xmlDocPtr doc); // Libere le fichier xml (Libère la mémoire)
void parcours_prefixe(xmlNodePtr noeud, fct_parcours_t f); // Parcours en profondeur des noeuds du fichier xml
void afficher(xmlNodePtr noeud);



