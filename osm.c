#include "osm.h"

xmlDocPtr parse_file(char *name){
	// Ouverture du document
  xmlKeepBlanksDefault(0); // Ignore les noeuds texte composant la mise en forme
  xmlDocPtr doc = xmlParseFile(name);
  return doc;
}

xmlNodePtr get_root(xmlDocPtr doc){
	if (doc == NULL) {
    fprintf(stderr, "Document OSM invalide\n");
    return NULL;
  }
	xmlNodePtr racine = xmlDocGetRootElement(doc);
	return racine;
}

void free_file(xmlDocPtr doc){
	if (doc != NULL) {
    xmlFreeDoc(doc);// Libération de la mémoire
  }
}

void parcours_prefixe(xmlNodePtr noeud, fct_parcours_t f) {
    xmlNodePtr n;
    
    for (n = noeud; n != NULL; n = n->next) {
      f(n);
      if ((n->type == XML_ELEMENT_NODE) && (n->children != NULL)) {
          parcours_prefixe(n->children, f);
      }
    }
}

void afficher(xmlNodePtr noeud) {
        if (noeud->type == XML_ELEMENT_NODE ) {
	    xmlChar *id=xmlGetProp(noeud,(const xmlChar *)"id");//retourne valeur de l'attribut id du noeud
	    xmlChar *visible=xmlGetProp(noeud,(const xmlChar *)"visible");
	    xmlChar *k=xmlGetProp(noeud,(const xmlChar *)"k");
	    xmlChar *v=xmlGetProp(noeud,(const xmlChar *)"v");
	    printf("noeud:%s , ",noeud->name);
	    if(id!=NULL)
	      printf("id:%s , ",id);
	    if(visible!=NULL)
	      printf("visible:%s , ",visible);
	    if(k!=NULL)
	      printf("k:%s , ",k);
	    if(v!=NULL)
	      printf("v:%s , ",v);
	    printf("\n");
	    xmlFree(id);
	    xmlFree(visible);
	    xmlFree(k);
	    xmlFree(v);
    }
}

