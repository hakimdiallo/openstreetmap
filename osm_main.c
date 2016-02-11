#include "osm.h"

int main(int argc, char *argv[]){
	xmlDocPtr doc;
	printf("Parsing file xml...\n");
	if(argc < 2 || argc > 2){
		printf("1 argument manquand: le nom du fichier xml/osm a parser.\n");
		return -1;
	}
	doc = parse_file(argv[1]);
	if( doc == NULL ){
		printf("Something went wrong...\n");
		free_file(doc);
		return -1;
	}
	xmlNodePtr racine = get_root(doc);
	if( racine == NULL ){
		printf("Structure du fichier bizarre...\n");
		free_file(doc);
	}
	parcours_prefixe(racine,afficher);
	printf("Hey! look at u!...\n");
	return 0;
}
