#include "osm_structure.h"


#define SIZE_NODES 20

my_way* init_my_way(){
  my_way *way  = malloc(sizeof(my_way));
  way->nodes = NULL;
  way->tag = g_hash_table_new( g_str_hash, g_str_equal);
  way->drawn = 0;
  return way;
}

my_node* init_my_node(){
  my_node *node = malloc(sizeof(my_node));
  node->tag = g_hash_table_new( g_str_hash, g_str_equal);
  return node;
}

my_bounds* init_my_bounds(){
  my_bounds* bound = malloc(sizeof(my_bounds));
  return bound;
}

my_relation* init_my_relation(){
  my_relation *rel = malloc(sizeof(my_relation));
  rel->ways_inner = NULL;
  rel->ways_outer = NULL;
  rel->ways = NULL;
  rel->nodes = NULL;
  rel->relations = NULL;
  rel->tags = g_hash_table_new( g_str_hash, g_str_equal);
  return rel;
}

void add_tag_my_way(my_way *way, my_tag *tag){
  g_hash_table_insert(way->tag, tag->key, tag->value);
}

void add_node_my_way(my_way *way, char *idNode){
  way->nodes = g_slist_append (g_slist_copy(way->nodes), idNode);
}

void add_tag_my_node(my_node *node, my_tag *tag){
  g_hash_table_insert(node->tag, tag->key, tag->value);
}

void add_way_to_relation(my_relation *rel, char *idWay, xmlChar *role){
  if ( xmlStrEqual(role, BAD_CAST "inner") ) {
    rel->ways_inner = g_slist_append(g_slist_copy(rel->ways_inner), idWay);
  }
  else if ( xmlStrEqual(role, BAD_CAST "outer") ) {
    rel->ways_outer = g_slist_append(g_slist_copy(rel->ways_outer), idWay);
  }
  else
    rel->ways = g_slist_append(g_slist_copy(rel->ways), idWay);
}

void add_node_to_relation(my_relation *rel, char *idNode){
  rel->nodes = g_slist_append(g_slist_copy(rel->nodes), idNode);
}

void add_relation_to_relation(my_relation *rel, char *idRel){
  rel->relations = g_slist_append(g_slist_copy(rel->relations), idRel);
}

void add_tag_to_relation(my_relation *rel, my_tag *tag){
  g_hash_table_insert(rel->tags, tag->key, tag->value);
}

void free_my_way(my_way *way){
  g_slist_free(way->nodes);
  g_hash_table_destroy(way->tag);
  free(way);
}

void free_my_ways(GHashTable *ways){
  GHashTableIter iter;
  gpointer value;
  g_hash_table_iter_init(&iter, ways);
  while(g_hash_table_iter_next(&iter, NULL, &value)) {
       free_my_way(value);
  }
  g_hash_table_destroy(ways);
}


void free_my_nodes(GHashTable *nodes){
  GHashTableIter iter;
  gpointer value;
  g_hash_table_iter_init(&iter, nodes);
  while(g_hash_table_iter_next(&iter, NULL, &value)) {
       free_my_way(value);
  }
  g_hash_table_destroy(nodes);
}

void free_my_node(my_node *node){
  g_hash_table_destroy(node->tag);
  free(node);
}

void free_my_bound(my_bounds *bound){
  free(bound);
}
