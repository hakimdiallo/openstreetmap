#include "osm.h"
#include "mercator.h"

double calcul_coor_x(double d, my_bounds *bn);
double calcul_coor_y(double d, my_bounds *bn);


void parcours_largeur(GHashTable *relations, GHashTable *ways, GHashTable *nodes, my_bounds *bound, xmlNodePtr noeud, fct_parcours_t f){
    xmlNodePtr n;
    for (n = noeud; n != NULL; n = n->next) {
      f(relations, ways, nodes, bound, n);
    }
}

void stockageNoeudsOSM(GHashTable *relations, GHashTable *ways, GHashTable *nodes, my_bounds *bound, xmlNodePtr noeud){
  if (noeud->type == XML_ELEMENT_NODE) {
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

void parse_file(GHashTable *relations, GHashTable *ways, GHashTable *nodes, my_bounds *bound, char *name){
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
    my_way *way = init_my_way();
    char *id = (char *)xmlGetProp(noeud, BAD_CAST "id");
    char *visible = (char *)xmlGetProp(noeud, BAD_CAST "visible");
    strcpy(way->at.id,id);
    strcpy(way->at.visible,visible);
    xmlNodePtr child = noeud->children;
    //xmlChar *ref = NULL;
    while( child != NULL){
      if(xmlStrEqual(child->name, BAD_CAST "nd")){
        xmlChar *ref = xmlGetProp(child, BAD_CAST "ref");
        char *reff = (char *)malloc(20*sizeof(char));
        strcpy(reff,(char *)ref);
        //(char *)malloc(20*sizeof(char));
        add_node_my_way(way,reff);
        //free(reff);
        free(ref);
      }
      else {
        my_tag *tag = getTagInformations(child);
        add_tag_my_way(way,tag);
        free(tag);
      }
      child = child->next;
    }
    g_hash_table_insert(ways, &(way->at.id), way);
    free(id);
    free(visible);
}

void setNodeInformations(GHashTable *nodes, xmlNodePtr noeud, my_bounds *bound){
  my_node *n = init_my_node();
  char *id = (char *) xmlGetProp(noeud,BAD_CAST "id");
  char *visible = (char *)xmlGetProp(noeud,BAD_CAST "visible");
  strcpy(n->at.id, (const char *)id);
  strcpy(n->at.visible, (const char *)visible);
  xmlChar *lat = xmlGetProp(noeud,(const xmlChar *)"lat");
  xmlChar *lon = xmlGetProp(noeud,(const xmlChar *)"lon");
  double cor = fmax( ((bound->maxlat - bound->minlat) / HEIGHT), ((bound->maxlon - bound->minlon) / WIDTH) );
  n->lat = calcul_coor_y( merc_y(strtod((const char *)lat,NULL)), bound ) / cor;
  n->lon = calcul_coor_x( merc_x(strtod((const char *)lon,NULL)), bound ) / cor;
  xmlNodePtr child = noeud->children;
  while ( child != NULL ) {
    my_tag *tag = getTagInformations(child);
    add_tag_my_node(n,tag);
    free(tag);
    child = child->next;
  }
  g_hash_table_insert(nodes, n->at.id, n);//ajoute le noeud crée à la liste des noeuds
  free(lat);
  free(lon);
  free(id);
  free(visible);
}

my_tag *getTagInformations(xmlNodePtr node){
  my_tag *tag = (my_tag *)malloc(sizeof(my_tag));
  tag->key = NULL;
  tag->value = NULL;
  tag->key  = (char *)xmlGetProp(node,(const xmlChar *)"k");
  tag->value = (char *)xmlGetProp(node,(const xmlChar *)"v");
  return tag;
}

void setBoundInformations(my_bounds *bound, xmlNodePtr noeud){
  xmlChar *minlat = xmlGetProp(noeud,(const xmlChar *)"minlat");
  xmlChar *minlon = xmlGetProp(noeud,(const xmlChar *)"minlon");
  xmlChar *maxlat = xmlGetProp(noeud,(const xmlChar *)"maxlat");
  xmlChar *maxlon = xmlGetProp(noeud,(const xmlChar *)"maxlon");
  bound->maxlat = merc_y(strtod((const char *)maxlat,NULL));
  bound->minlat = merc_y(strtod((const char *)minlat,NULL));
  bound->maxlon = merc_x(strtod((const char *)maxlon,NULL));
  bound->minlon = merc_x(strtod((const char *)minlon,NULL));
  free(minlon);
  free(maxlon);
  free(minlat);
  free(maxlat);
}

void setRelationInformations(GHashTable *relations, xmlNodePtr noeud){
  my_relation *rel = init_my_relation();
  char *id = (char *)xmlGetProp(noeud, BAD_CAST "id");
  char *visible = (char *)xmlGetProp(noeud, BAD_CAST "visible");
  strcpy(rel->at.id,id);
  strcpy(rel->at.visible,visible);
  xmlNodePtr child = noeud->children;
  while ( child != NULL ) {
    xmlChar *ref = NULL;
    if( xmlStrEqual(child->name, BAD_CAST "member") ){
      xmlChar *member = xmlGetProp(child, BAD_CAST "type");
      xmlChar *role = xmlGetProp(child, BAD_CAST "role");
      ref = xmlGetProp(child, BAD_CAST "ref");
      if( xmlStrEqual(member, BAD_CAST "way") ) {
        add_way_to_relation(rel,(char *)ref,role);
      }
      else if( xmlStrEqual(member, BAD_CAST "node") ) {
        add_node_to_relation(rel,(char *)ref);
      }
      else if( xmlStrEqual(member, BAD_CAST "relation") ) {
        add_relation_to_relation(rel,(char *)ref);
      }
      free(member);
      free(role);
    }
    else{
      my_tag *tag = getTagInformations(child);
      add_tag_to_relation(rel,tag);
      free(tag);
    }
    child = child->next;
    free(ref);
  //  free(rel);
  }
  g_hash_table_insert(relations, &(rel->at.id), rel);
  free(id);
  free(visible);
}

//Calcule les coordonnées y sur la fenêtre
double calcul_coor_y(double d, my_bounds *bn){
  double height = bn->maxlat - bn->minlat ;
  return (-height/2) + (height * (d - bn->minlat)/(bn->maxlat - bn->minlat));
}

//Calcule les coordonnées x sur la fenêtre
double calcul_coor_x(double d, my_bounds *bn){
  double width = bn->maxlon - bn->minlon ;
  return -(width/2) + (width * ((d - bn->minlon)/(bn->maxlon - bn->minlon)));
}
