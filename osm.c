#include "osm.h"

xmlDocPtr parse_file(char *name){
	// Ouverture du document
  xmlKeepBlanksDefault(0); // Ignore les noeuds texte composant la mise en forme
  xmlDocPtr doc = xmlParseFile(name);
  return doc;
}

xmlNodePtr get_root(xmlDocPtr doc){
	if (doc == NULL) {
    if(DEBUG)
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


xmlXPathContextPtr get_xpath_contexte(xmlDocPtr doc){
  // Initialisation de l'environnement XPath
	xmlXPathInit();
	// Création du contexte
	xmlXPathContextPtr ctxt = xmlXPathNewContext(doc); // doc est un xmlDocPtr représentant notre fichier osm
	if (ctxt == NULL) {
      if(DEBUG)
	     fprintf(stderr, "Erreur lors de la création du contexte XPath\n");
	    exit(-1);
	}
  return ctxt;
}

xmlXPathObjectPtr getNode_by_xpathExpression(char *nodePath, xmlXPathContextPtr ctxt){
  if(DEBUG)
    printf("Evaluation d'une expression...\n");
  // Evaluation de l'expression XPath
  xmlXPathObjectPtr pathObj = xmlXPathEvalExpression(BAD_CAST nodePath, ctxt);
	if (pathObj == NULL) {
    //if(DEBUG)
    fprintf(stderr, "Erreur sur l'expression XPath\n");
	  exit(-1);
	}
  return pathObj;
}

void xpath_parcours(xmlXPathObjectPtr xpathRes, xmlXPathContextPtr ctxt, SDL_Renderer *renderer){
  if(DEBUG)
    printf("Parcours des noeuds par xpath...\n");
  // Manipulation du résultat de l'evaluation d'une expression xpath
  //printf("%s\n",xpathRes->type );
  if (xpathRes->type == XPATH_NODESET) {
    if(DEBUG)
      printf("Starting...\n");
    int i;
    for (i = 0; i < xpathRes->nodesetval->nodeNr; i++) {
      xmlNodePtr n = xpathRes->nodesetval->nodeTab[i];
      xmlChar *visible = xmlGetProp(n,(const xmlChar *)"visible");
      if(DEBUG)
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
  if(DEBUG)
    printf("Parcours des noeuds fils\n");
  my_way *way = init_my_way();
  if(way == NULL){
    fprintf(stderr, "Erreur sur l'expression XPath\n");
	  exit(-1);
  }
  xmlNodePtr child = n->children;
  while( child != NULL ){
    if(xmlStrEqual(child->name,(const xmlChar *)"nd")){
        xmlChar *ref = xmlGetProp(child,(const xmlChar *)"ref");
        xmlNodePtr noeud = getNode_by_id(ref,ctxt);
        xmlChar *visible = xmlGetProp(noeud,(const xmlChar *)"visible");
        if( xmlStrEqual(visible,(const xmlChar *)"true") ){
          my_node *nd1 = getNodeInformations(noeud);
          add_node_my_way(way,*nd1);
        }
    }
    else {
      my_tag tag = getTagInformations(child);
      add_tag_my_way(way,tag);
    }
    child = child->next;
  }
  // Dessiner un my_way
  dessiner_way_bis(*way,renderer);
  free_my_way(way);
}

xmlNodePtr getNode_by_id(xmlChar *ref, xmlXPathContextPtr ctxt){
  xmlChar *expr;
  xmlChar *expression = "/osm/node[@id=";
  expr = xmlStrncatNew(expression,ref,xmlStrlen(ref));

  xmlChar *fin = "]";
  xmlChar *ex = xmlStrncatNew(expr,fin,xmlStrlen(fin));
  if(DEBUG)
    printf("1 %s\n",ex );
  //break;
  xmlXPathObjectPtr no = getNode_by_xpathExpression((char *)ex, ctxt);
  if(no == NULL){
    exit(-1);
  }
  xmlNodePtr noeud = no->nodesetval->nodeTab[0];
  if(DEBUG)
    printf("%s\n",noeud->name );

  xmlXPathFreeObject(no);
  return noeud;
}

my_node *getNodeInformations(xmlNodePtr noeud){
  my_node *n = init_my_node();

  xmlChar *lat = xmlGetProp(noeud,(const xmlChar *)"lat");
  xmlChar *lon = xmlGetProp(noeud,(const xmlChar *)"lon");
  if(DEBUG){
    printf("Lon: %s\n", lon);
    printf("Lat: %s\n", lat);
  }
  n->lat = CIRC_TERRE*cos(strtod((const char *)lat,NULL));
  n->lon = CIRC_TERRE*cos(strtod((const char *)lon,NULL));
  if(DEBUG){
    printf("ffff %f\n",n->lat );
    printf("Done...\n");
  }
  xmlNodePtr child = noeud->children;
  while ( child != NULL ) {
    my_tag tag = getTagInformations(child);
    add_tag_my_node(n,tag);
    child = child->next;
  }
  return n;
}

my_bounds getBoundInformations(xmlXPathContextPtr ctxt){
  my_bounds b;
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

my_tag getTagInformations(xmlNodePtr node){
  my_tag tag;
  xmlChar *k = xmlGetProp(node,(const xmlChar *)"k");
  xmlChar *v = xmlGetProp(node,(const xmlChar *)"v");
  if(DEBUG)
    printf("tag - k: %s v: %s\n", k, v);
  strcpy(tag.key,(char *)k);
  strcpy(tag.value,(char *)v);
  return tag;
}

void parcours_attributs(xmlNodePtr noeud){
  xmlAttrPtr at = noeud->properties;

  while ( at != NULL) {
    xmlChar *val = xmlGetProp(noeud,at->name);
    if(DEBUG)
      printf("%s - ",val );
    at =  at->next;
  }
}

int calcul_coor_y(double d){
  if(DEBUG){
    printf("min lat %f\n",bn.minlat );
    printf("x - %f\n", d);
    printf("max lat %f\n", bn.maxlat);
  }
  return HEIGHT - (int)( HEIGHT * ((d - bn.minlat)/(bn.maxlat - bn.minlat)) );
}

int calcul_coor_x(double d){
  if(DEBUG){
    printf("min lon %f\n",bn.minlon);
    printf("y - %f\n", d);
    printf("max lon %f\n", bn.maxlon);
  }
  return (int)( WIDTH * ((d - bn.minlon)/(bn.maxlon - bn.minlon)) );
}
