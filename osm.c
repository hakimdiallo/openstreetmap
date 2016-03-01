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

xmlXPathContextPtr get_xpath_contexte(xmlDocPtr doc){
  // Initialisation de l'environnement XPath
	xmlXPathInit();
	// Création du contexte
	xmlXPathContextPtr ctxt = xmlXPathNewContext(doc); // doc est un xmlDocPtr représentant notre fichier osm
	if (ctxt == NULL) {
	    fprintf(stderr, "Erreur lors de la création du contexte XPath\n");
	    exit(-1);
	}
  return ctxt;
}

xmlXPathObjectPtr getNode_by_xpathExpression(char *nodePath, xmlXPathContextPtr ctxt){
  printf("Evaluation d'une expression...\n");
  // Evaluation de l'expression XPath
  xmlXPathObjectPtr pathObj = xmlXPathEvalExpression(BAD_CAST nodePath, ctxt);
	if (pathObj == NULL) {
	    fprintf(stderr, "Erreur sur l'expression XPath\n");
	    exit(-1);
	}
  return pathObj;
}

void xpath_parcours(xmlXPathObjectPtr xpathRes, xmlXPathContextPtr ctxt, SDL_Renderer *renderer){
  printf("Parcours des noeuds par xpath...\n");
  // Manipulation du résultat de l'evaluation d'une expression xpath
  //printf("%s\n",xpathRes->type );
  if (xpathRes->type == XPATH_NODESET) {
    printf("Starting...\n");
    int i;
    for (i = 0; i < xpathRes->nodesetval->nodeNr; i++) {
      xmlNodePtr n = xpathRes->nodesetval->nodeTab[i];
      xmlChar *visible = xmlGetProp(n,(const xmlChar *)"visible");
      printf("%s\n", visible );
      if( n->type == XML_ELEMENT_NODE && xmlStrEqual(visible,(const xmlChar *)"true") ){
        parcours_des_noeuds_fils(n,ctxt,renderer);
      }
    }
  }
  // Libération de la mémoire
  //xmlXPathFreeObject(xpathRes);
  xmlXPathFreeContext(ctxt);
}

void parcours_des_noeuds_fils(xmlNodePtr n, xmlXPathContextPtr ctxt, SDL_Renderer *renderer){
  printf("Parcours des noeuds fils\n");
  xmlNodePtr child = n->children;
  while( child != NULL ){
    if(xmlStrEqual(child->name,(const xmlChar *)"nd")){
      if(child->prev != NULL){
        xmlChar *ref = xmlGetProp(child,(const xmlChar *)"ref");
        xmlChar *ref2 = xmlGetProp(child->prev,(const xmlChar *)"ref");
        //commencer a construire un way
        xmlNodePtr noeud = getNode_by_id(ref,ctxt);
        xmlNodePtr noeud2 = getNode_by_id(ref2,ctxt);
        node nd1 = getNodeInformations(noeud);
        node nd2 = getNodeInformations(noeud2);
        // Dessiner
        dessiner_trait_noeuds(nd1,nd2,renderer);
      }
    }
    else {
      xmlChar *k = xmlGetProp(child,(const xmlChar *)"k");
      xmlChar *v = xmlGetProp(child,(const xmlChar *)"v");
      printf("tag - k: %s v: %s\n", k, v);

    }
    child = child->next;
  }
}

xmlNodePtr getNode_by_id(xmlChar *ref, xmlXPathContextPtr ctxt){
  xmlChar *expr;
  xmlChar *expression = "/osm/node[@id=";
  expr = xmlStrncatNew(expression,ref,xmlStrlen(ref));

  xmlChar *fin = "]";
  xmlChar *ex = xmlStrncatNew(expr,fin,xmlStrlen(fin));
  printf("1 %s\n",ex );
  //break;
  xmlXPathObjectPtr node = getNode_by_xpathExpression((char *)ex, ctxt);
  if(node == NULL){
    exit(-1);
  }
  xmlNodePtr noeud = node->nodesetval->nodeTab[0];
  printf("%s\n",noeud->name );

  xmlXPathFreeObject(node);
  return noeud;
}

node getNodeInformations(xmlNodePtr noeud){
  node n;
  xmlChar *lat = xmlGetProp(noeud,(const xmlChar *)"lat");
  xmlChar *lon = xmlGetProp(noeud,(const xmlChar *)"lon");
  printf("Lon: %s\n", lon);
  printf("Lat: %s\n", lat);
  n.lat = strtod((const char *)lat,NULL);
  n.lon = strtod((const char *)lon,NULL);
  printf("ffff %f\n",n.lat );
  //xmlChar *visible = xmlGetProp(noeud,(const xmlChar *)"visible");
  //xmlNodePtr child = noeud->children;
  printf("Done...\n");
  //while( child != NULL ){

  //}
  //xmlFree(lat);
  //xmlFree(lon);
  return n;
}

bounds getBoundInformations(xmlXPathContextPtr ctxt){
  bounds b;
  xmlChar *expression = "/osm/bounds";
  //printf("1 %s\n",ex );
  //break;
  xmlXPathObjectPtr node = getNode_by_xpathExpression((char *)expression, ctxt);
  if(node == NULL){
    exit(-1);
  }
  xmlNodePtr noeud = node->nodesetval->nodeTab[0];
  xmlChar *minlat = xmlGetProp(noeud,(const xmlChar *)"minlat");
  xmlChar *minlon = xmlGetProp(noeud,(const xmlChar *)"minlon");
  xmlChar *maxlat = xmlGetProp(noeud,(const xmlChar *)"maxlat");
  xmlChar *maxlon = xmlGetProp(noeud,(const xmlChar *)"maxlon");
  b.maxlat = CIRC_TERRE*cos(strtod((const char *)maxlat,NULL));
  b.minlat = CIRC_TERRE*cos(strtod((const char *)minlat,NULL));
  b.maxlon = CIRC_TERRE*cos(strtod((const char *)maxlon,NULL));
  b.minlon = CIRC_TERRE*cos(strtod((const char *)minlon,NULL));

  xmlXPathFreeObject(node);
  return b;
}

void parcours_attributs(xmlNodePtr noeud){
  xmlAttrPtr at = noeud->properties;

  while ( at != NULL) {
    xmlChar *val = xmlGetProp(noeud,at->name);
    printf("%s - ",val );
    at =  at->next;
  }
}

void dessiner_trait_noeuds(node n1, node n2, SDL_Renderer *renderer){
  int x1 = calcul_coor_x(n1.lon);
  int y1 = calcul_coor_y(n1.lat);
  int x2 = calcul_coor_x(n2.lon);
  int y2 = calcul_coor_y(n2.lat);
  printf("x1 %d y1 %d x2 %d y2 %d\n", x1, y1, x2, y2);
  SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
	SDL_RenderPresent(renderer);
}

int calcul_coor_y(double d){
  double r = CIRC_TERRE*cos(d);
  printf("min lat %f\n",bn.minlat );
  printf("x - %f\n", r);
  printf("max lat %f\n", bn.maxlat);
  return HEIGHT - (int)( HEIGHT * ((r - bn.minlat)/(bn.maxlat - bn.minlat)) );
}

int calcul_coor_x(double d){
  double r = CIRC_TERRE*cos(d);
  printf("min lon %f\n",bn.minlon);
  printf("y - %f\n", r);
  printf("max lon %f\n", bn.maxlon);
  return (int)( WIDTH * ((r - bn.minlon)/(bn.maxlon - bn.minlon)) );
}
