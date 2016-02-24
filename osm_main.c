#include "osm.h"
#include "string.h"
#include "graphic.h"

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
	// Initialisation de l'environnement XPath
	xmlXPathInit();
	// Création du contexte
	xmlXPathContextPtr ctxt = xmlXPathNewContext(doc); // doc est un xmlDocPtr représentant notre catalogue
	if (ctxt == NULL) {
	    fprintf(stderr, "Erreur lors de la création du contexte XPath\n");
	    exit(-1);
	}
	// Evaluation de l'expression XPath
	xmlXPathObjectPtr xpathRes = xmlXPathEvalExpression(BAD_CAST "/osm/way", ctxt);
	if (xpathRes == NULL) {
	    fprintf(stderr, "Erreur sur l'expression XPath\n");
	    exit(-1);
	}
	// Manipulation du résultat
	if (xpathRes->type == XPATH_NODESET) {
	    int i;
	    printf("Ways :\n");
	    for (i = 0; i < xpathRes->nodesetval->nodeNr; i++) {
					printf("wa---------------------------------------------------\n");
	        xmlNodePtr n = xpathRes->nodesetval->nodeTab[i];
	        if (n->type == XML_ELEMENT_NODE){ //|| n->type == XML_CDATA_SECTION_NODE) {
							//xmlChar *id = xmlGetProp(n,(const xmlChar *)"id");
							xmlNodePtr child = n->children;
							while( child != NULL ){
								if(xmlStrEqual(child->name,(const xmlChar *)"nd")){
									xmlChar *ref = xmlGetProp(child,(const xmlChar *)"ref");
									printf("nd: %s\n", ref);
									xmlChar *expr;
									xmlChar *expression = "/osm/node[@id=";
									expr = xmlStrncatNew(expression,ref,xmlStrlen(ref));

									xmlChar *fin = "]";
									xmlChar *ex = xmlStrncatNew(expr,fin,xmlStrlen(fin));
									printf("1 %s\n",ex );
									//break;
									xmlXPathObjectPtr node = xmlXPathEvalExpression(BAD_CAST ex, ctxt);
									if(node == NULL){
										return -1;
									}
									xmlNodePtr noeud = node->nodesetval->nodeTab[0];

									xmlFree(expr);
									xmlFree(expression);
									xmlFree(ex);
									xmlXPathFreeObject(node);
								}
								else {
									xmlChar *k = xmlGetProp(child,(const xmlChar *)"k");
									xmlChar *v = xmlGetProp(child,(const xmlChar *)"v");
									printf("tag - k: %s v: %s\n", k, v);
								}
								child = child->next;
							}
	        }
	    }
	}

	// Libération de la mémoire
	xmlXPathFreeObject(xpathRes);
	xmlXPathFreeContext(ctxt);
	/*xmlNodePtr racine = get_root(doc);
	if( racine == NULL ){
		printf("Structure du fichier bizarre...\n");
		free_file(doc);
	}
	parcours_prefixe(racine,afficher);
	printf("Hey! look at u!...\n");*/
	SDL_Surface *ecran=NULL;
	draw_fenetre(ecran,500,500);
	return 0;
}
