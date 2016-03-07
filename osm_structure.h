#ifndef _OSM_STRUCTURE_H_
	#define _OSM_STRUCTURE_H_

#define MY_TAG_SIZE 20
#define MY_NODE_SIZE 100
#define ACTIVE 1

typedef struct my_tag {
	char key[1024];
	char value[1024];
} my_tag;

typedef struct my_attributs {
	int id;
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
	my_tag *tag;
	int size_tag;
	int count_tag;
} my_node;

typedef struct my_way {
	//attributs at;
	my_node *nodes;
	my_tag *tag;
	int size_tag;
	int size_nodes;
	int count_nodes;
	int count_tag;
} my_way;

typedef struct my_area {
	my_way w;
}area;

typedef struct my_bounds{
	double maxlat;
	double minlat;
	double maxlon;
	double minlon;
}my_bounds;

// l'entree de l'hashmap
typedef struct hashmap_entry{
	unsigned long id;
	my_node *node;
	int flags;
} hashmap_entry;


typedef struct my_hashmap_node{
	hashmap_entry *table;
	int size, count;
} my_hashmap_node;

//Innitialise la structure my_way
my_way* init_my_way();

//ajoute un tag dans un way
void add_tag_my_way(my_way *way,my_tag tag);

//ajoute un noeud dans un way
void add_node_my_way(my_way *way,my_node node);

//détruit la structure my_way
void free_my_way(my_way *way);

//Initialise un noeud
my_node* init_my_node();

//Libère la structure my_node
void free_my_node(my_node *node);

//ajoute un tag dans un node
void add_tag_my_node(my_node *node, my_tag tag);

// initialise un hashmap avec une taille donnée
my_hashmap_node* init_hashmap(int startsize);

//Ajoute un noeud dans l'hashmap
void add_node_hashmap (my_hashmap_node* hash, my_node *node, unsigned long id);

//Recupère le my_node qui a l'id entrée en paramètre
my_node* get_hashmap_node(my_hashmap_node* hash, unsigned long id);

//Libère la structure hashmap
void free_hashmap_node(my_hashmap_node* hash);

#endif
