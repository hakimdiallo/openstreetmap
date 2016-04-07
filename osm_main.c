#include "osm.h"
#include "string.h"
#include "graphic.h"
#include <SDL.h>
#include <stdlib.h>



int main(int argc, char *argv[]){
	//if(DEBUG)
		//printf("Parsing file xml...\n");
	if(argc < 2 || argc > 2){
		printf("1 argument manquand: le nom du fichier xml/osm a parser.\n");
		return -1;
	}
	my_bounds *bound;
	GHashTable *ways;
	GHashTable *nodes;
	GHashTable *relations;
	relations = g_hash_table_new_full( g_str_hash, g_str_equal, NULL, g_free);
	nodes = g_hash_table_new_full( g_str_hash, g_str_equal, NULL, g_free);//initialisation de l'hashtable des nodes
	ways = g_hash_table_new_full( g_str_hash, g_str_equal, NULL, g_free);//initialisation de l'hashtable des ways
	bound = init_my_bounds();
	parse_file_v(relations, ways, nodes, bound, argv[1]);
	rendererMap(ways, nodes);
	g_hash_table_destroy(ways);
	g_hash_table_destroy(nodes);
	g_hash_table_destroy(relations);
	free_my_bound(bound);
	return 0;
}
