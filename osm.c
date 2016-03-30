#include "osm.h"

int calcul_coor_x(double d, my_bounds *bn);
int calcul_coor_y(double d, my_bounds *bn);

void parcours_largeur(GHashTable *relations, GHashTable *ways, GHashTable *nodes, my_bounds *bound, xmlNodePtr noeud, fct_parcours_t f){
    xmlNodePtr n;
    for (n = noeud; n != NULL; n = n->next) {
      f(relations, ways, nodes, bound, n);
    }
}

void stockageNoeudsOSM(GHashTable *relations, GHashTable *ways, GHashTable *nodes, my_bounds *bound, xmlNodePtr noeud){
  if (noeud->type == XML_ELEMENT_NODE) {
    //xmlChar *chemin = xmlGetNodePath(noeud);
    if(xmlStrEqual(noeud->name, BAD_CAST "way")){
      setWayInformation(ways,  noeud);
    }
    else if (xmlStrEqual(noeud->name, BAD_CAST "node")){
      setNodeInformations(nodes,noeud, bound);
    }
    else if (xmlStrEqual(noeud->name, BAD_CAST "bounds")){
      setBoundInformations(bound, noeud);
    }
    else if (xmlStrEqual(noeud->name, BAD_CAST "relation")){
      setRelationInformations(relations, noeud);
    }
  }
}

void parse_file_v(GHashTable *relations, GHashTable *ways, GHashTable *nodes, my_bounds *bound, char *name){
  xmlDocPtr doc;
  xmlNodePtr noeud;

  // Ouverture du document
  xmlKeepBlanksDefault(0); // Ignore les noeuds texte composant la mise en forme
  doc = xmlParseFile(name);
  if (doc == NULL) {
      fprintf(stderr, "Document XML invalide\n");
      return ;
  }
  // Récupération de la racine
  noeud = xmlDocGetRootElement(doc);
  if (noeud == NULL) {
      fprintf(stderr, "Document XML vierge\n");
      xmlFreeDoc(doc);
      return ;
  }
  if ( noeud -> children == NULL ){
    fprintf(stderr, " Rien a affiché \n");
    xmlFreeDoc(doc);
    return ;
  }
  //parcour du fichier
  parcours_largeur(relations, ways, nodes, bound, noeud->children, stockageNoeudsOSM);
  xmlFreeDoc(doc);
}

void setWayInformation(GHashTable *ways, xmlNodePtr noeud){
    xmlNodePtr child = noeud->children;
    my_way *way = init_my_way();
    strcpy(way->at.id, (const char *) xmlGetProp(noeud, BAD_CAST "id"));
    while( child != NULL){
      if(xmlStrEqual(child->name, BAD_CAST "nd")){
        xmlChar *ref = xmlGetProp(child, BAD_CAST "ref");
        //my_node *nd1 = (my_node *)g_hash_table_lookup(nodes, (char *)ref) ;
        //if(nd1 != NULL)
          //add_node_my_way(way,nd1);
        add_node_my_way(way, (char *)ref);
      }
      else {
        my_tag *tag = getTagInformations(child);
        add_tag_my_way(way,tag);
      }
      child = child->next;
    }
    g_hash_table_insert(ways, way->at.id, way);
}

void setNodeInformations(GHashTable *nodes, xmlNodePtr noeud, my_bounds *bound){
  my_node *n = init_my_node();
  strcpy(n->at.id, (const char *) xmlGetProp(noeud,BAD_CAST "id"));
  strcpy(n->at.visible, (const char *)xmlGetProp(noeud,BAD_CAST "visible"));
  xmlChar *lat = xmlGetProp(noeud,(const xmlChar *)"lat");
  xmlChar *lon = xmlGetProp(noeud,(const xmlChar *)"lon");
  n->lat = calcul_coor_y( (RAYON_TERRE*sin(strtod((const char *)lat,NULL)) * sqrt(2)), bound );
  n->lon = calcul_coor_x( ((RAYON_TERRE*M_PI*strtod((const char *)lon,NULL))/(180 * sqrt(2))), bound );
  xmlNodePtr child = noeud->children;
  while ( child != NULL ) {
    my_tag *tag = getTagInformations(child);
    add_tag_my_node(n,tag);
    child = child->next;
  }
  g_hash_table_insert(nodes, n->at.id, n);//ajoute le noeud crée à la liste des noeuds
}

my_tag *getTagInformations(xmlNodePtr node){
  my_tag *tag = (my_tag *)malloc(sizeof(my_tag));
  xmlChar *k = xmlGetProp(node,(const xmlChar *)"k");
  xmlChar *v = xmlGetProp(node,(const xmlChar *)"v");
  strcpy(tag->key,(char *)k);
  strcpy(tag->value,(char *)v);
  return tag;
}

void setBoundInformations(my_bounds *bound, xmlNodePtr noeud){
  xmlChar *minlat = xmlGetProp(noeud,(const xmlChar *)"minlat");
  xmlChar *minlon = xmlGetProp(noeud,(const xmlChar *)"minlon");
  xmlChar *maxlat = xmlGetProp(noeud,(const xmlChar *)"maxlat");
  xmlChar *maxlon = xmlGetProp(noeud,(const xmlChar *)"maxlon");
  bound->maxlat = RAYON_TERRE*sin(strtod((const char *)maxlat,NULL)) * sqrt(2);
  bound->minlat = RAYON_TERRE*sin(strtod((const char *)minlat,NULL)) * sqrt(2);
  bound->maxlon = (RAYON_TERRE*M_PI*strtod((const char *)maxlon,NULL))/(180 * sqrt(2));
  bound->minlon = (RAYON_TERRE*M_PI*strtod((const char *)minlon,NULL))/(180 * sqrt(2));
}

void setRelationInformations(GHashTable *relations, xmlNodePtr noeud){
  my_relation *rel = init_my_relation();
  char *id = (char *)xmlGetProp(noeud, BAD_CAST "id");
  xmlNodePtr child = noeud->children;
  while ( child != NULL ) {
    if( xmlStrEqual(child->name, BAD_CAST "member") ){
      xmlChar *member = xmlGetProp(child, BAD_CAST "type");
      xmlChar *ref = xmlGetProp(child, BAD_CAST "ref");
      if( xmlStrEqual(member, BAD_CAST "way") ) {
        add_way_to_relation(rel,(char *)ref);
      }
      else if( xmlStrEqual(member, BAD_CAST "node") ) {
        add_node_to_relation(rel,(char *)ref);
      }
      else if( xmlStrEqual(member, BAD_CAST "relation") ) {
        add_relation_to_relation(rel,(char *)ref);
      }
    }
    else{
      my_tag *tag = getTagInformations(child);
      add_tag_to_relation(rel,tag);
    }
    child = child->next;
  }
  g_hash_table_insert(relations, &id, rel);
}

//Calcule les coordonnées y sur la fenêtre
int calcul_coor_y(double d, my_bounds *bn){
  return HEIGHT - (int)( HEIGHT * ((d - bn->minlat)/(bn->maxlat - bn->minlat)) );
}

//Calcule les coordonnées x sur la fenêtre
int calcul_coor_x(double d, my_bounds *bn){
  return (int)( WIDTH * ((d - bn->minlon)/(bn->maxlon - bn->minlon)) );
}
