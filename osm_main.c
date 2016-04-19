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
	GHashTable *ways_water;
	GHashTable *hash_ways;
	GHashTable *hash_nodes;
	GHashTable *hash_relations;
	hash_relations = g_hash_table_new_full( g_str_hash, g_str_equal, NULL, g_free);
	hash_nodes = g_hash_table_new_full( g_str_hash, g_str_equal, NULL, g_free);//initialisation de l'hashtable des nodes
	hash_ways = g_hash_table_new_full( g_str_hash, g_str_equal, NULL, g_free);//initialisation de l'hashtable des ways
	ways_water = g_hash_table_new_full( g_str_hash, g_str_equal, NULL, g_free);
	bound = init_my_bounds();
	parse_file_v(hash_relations, ways_water, hash_ways, hash_nodes, bound, argv[1]);

	rendererMap(ways_water, hash_ways, hash_nodes, hash_relations);
	//g_hash_table_destroy(hash_ways);
	//g_hash_table_destroy(hash_nodes);
	//g_hash_table_destroy(hash_relations);
	//free_my_bound(bound);

	return 0;
}
