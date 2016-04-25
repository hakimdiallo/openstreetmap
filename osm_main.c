#include "osm.h"
#include "osm_structure.h"
#include "graphic_opengl.h"
#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>



int main(int argc, char *argv[]){
	if(argc < 2 || argc > 2){
		printf("1 argument manquand: le nom du fichier xml/osm a parser.\n");
		return -1;
	}
	glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	my_bounds *bound;
	GHashTable *hash_ways;
	GHashTable *hash_nodes;
	GHashTable *hash_relations;
	/*hash_relations = g_hash_table_new_full( g_str_hash, g_str_equal, NULL, g_free);
	hash_nodes = g_hash_table_new_full( g_str_hash, g_str_equal, NULL, g_free);//initialisation de l'hashtable des nodes
	hash_ways = g_hash_table_new_full( g_str_hash, g_str_equal, NULL, NULL);//initialisation de l'hashtable des ways*/
	hash_relations = g_hash_table_new( g_str_hash, g_str_equal);
	hash_nodes = g_hash_table_new( g_str_hash, g_str_equal);//initialisation de l'hashtable des nodes
	hash_ways = g_hash_table_new( g_str_hash, g_str_equal);//initialisation de l'hashtable des ways
	bound = init_my_bounds();
	parse_file(hash_relations, hash_ways, hash_nodes, bound, argv[1]);
	rendererMap_opengl(hash_ways, hash_nodes, hash_relations);
	free_my_ways(hash_ways);
	free_my_nodes(hash_nodes);
	free_my_relations(hash_relations);
	free_my_bound(bound);
	return 0;
}
