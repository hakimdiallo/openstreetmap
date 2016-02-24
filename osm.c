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

void get_xpath_contexte(xmlDocPtr doc, xmlXPathContextPtr ctxt){
  // Initialisation de l'environnement XPath
	xmlXPathInit();
	// Création du contexte
	ctxt = xmlXPathNewContext(doc); // doc est un xmlDocPtr représentant notre fichier osm
	if (ctxt == NULL) {
	    fprintf(stderr, "Erreur lors de la création du contexte XPath\n");
	    exit(-1);
	}
}

void getNode_by_xpathExpression(xmlChar *nodePath, xmlXPathContextPtr ctxt, xmlXPathObjectPtr pathObj){
  printf("Evaluation d'une expression...\n");
  // Evaluation de l'expression XPath
  pathObj = xmlXPathEvalExpression(BAD_CAST nodePath, ctxt);
	if (pathObj == NULL) {
	    fprintf(stderr, "Erreur sur l'expression XPath\n");
	    exit(-1);
	}
}

void xpath_parcours(xmlXPathObjectPtr xpathRes){
  printf("Parcours des noeuds par xpath...\n", );
  // Manipulation du résultat de l'evaluation d'une expression xpath
  if (xpathRes->type == XPATH_NODESET) {
    int i;
    for (i = 0; i < xpathRes->nodesetval->nodeNr; i++) {
      xmlNodePtr n = xpathRes->nodesetval->nodeTab[i];
      xmlChar *visible = xmlGetProp(n,(const xmlChar *)"visible");
      if( n->type == XML_ELEMENT_NODE && xmlStrEqual(visible,(const xmlChar *)"true") ){
        parcours_des_noeuds_fils(n);
      }
    }
  }
  // Libération de la mémoire
  xmlXPathFreeObject(xpathRes);
  xmlXPathFreeContext(ctxt);
}

void parcours_des_noeuds_fils(xmlNodePtr n){
  xmlNodePtr child = n->children;
  while( child != NULL ){
    if(xmlStrEqual(child->name,(const xmlChar *)"nd")){
      xmlChar *ref = xmlGetProp(child,(const xmlChar *)"ref");
      //printf("nd: %s\n", ref);
      //commencer a construire un way
      xmlNodePtr noeud;
      getNode_by_id(ref,ctxt,noeud);
      node nd;
      getNodeInformations(noeud,nd);
    }
    else {
      xmlChar *k = xmlGetProp(child,(const xmlChar *)"k");
      xmlChar *v = xmlGetProp(child,(const xmlChar *)"v");
      printf("tag - k: %s v: %s\n", k, v);

      xmlFree(k);
      xmlFree(v);
    }
    child = child->next;
  }
}

void getNode_by_id(xmlChar *ref, xmlXPathContextPtr ctxt, xmlNodePtr noeud){
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
  noeud = node->nodesetval->nodeTab[0];

  xmlFree(expr);
  xmlFree(expression);
  xmlFree(ex);
  xmlXPathFreeObject(node);
}

void getNodeInformations(xmlNodePtr noeud, node n){
  xmlChar *lat = xmlGetProp(noeud,(const xmlChar *)"lat");
  xmlChar *lon = xmlGetProp(noeud,(const xmlChar *)"lon");
  n.lon = atoi((char *)lon);
  n.lat = atoi((char *)lat);
  n.at.visible = (char *) xmlGetProp(noeud,(const xmlChar *)"visible");
  xmlNodePtr child = noeud->child;
  while( child != NULL ){

  }
  xmlFree(lat);
  xmlFree(lon);
}
