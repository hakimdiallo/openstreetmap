/*
    Copyright (C) 2016

    Authors:
      - Souleymane DIALLO diallosouleymane.07@gmail.com
      - Jules Camille ZIRIGA julesziriga@gmail.com
      - Leila NAIT HAMOUD houacineleila@outlook.fr

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "osm_structure.h"


#define SIZE_NODES 20

my_way* init_my_way(){
  my_way *way  = malloc(sizeof(my_way));
  way->nodes = NULL;
  way->tag = NULL;
  way->tag = g_hash_table_new( g_str_hash, g_str_equal);
  way->drawn = 0;
  return way;
}

my_node* init_my_node(){
  my_node *node = malloc(sizeof(my_node));
  node->tag = g_hash_table_new ( g_str_hash, g_str_equal);
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
  way->nodes = g_slist_append (way->nodes, idNode);
}

void add_tag_my_node(my_node *node, my_tag *tag){
  g_hash_table_insert(node->tag, tag->key, tag->value);
}

void add_way_to_relation(my_relation *rel, char *idWay, xmlChar *role){
  if ( xmlStrEqual(role, BAD_CAST "inner") ) {
    rel->ways_inner = g_slist_append(rel->ways_inner, idWay);
  }
  else if ( xmlStrEqual(role, BAD_CAST "outer") ) {
    rel->ways_outer = g_slist_append(rel->ways_outer, idWay);
  }
  else
    rel->ways = g_slist_append(rel->ways, idWay);
}

void add_node_to_relation(my_relation *rel, char *idNode){
  rel->nodes = g_slist_append(rel->nodes, idNode);
}

void add_relation_to_relation(my_relation *rel, char *idRel){
  rel->relations = g_slist_append(rel->relations, idRel);
}

void add_tag_to_relation(my_relation *rel, my_tag *tag){
  g_hash_table_insert(rel->tags, tag->key, tag->value);
}

//flibère une structure my_tag
void free_my_tag(my_tag *tag){
  free(tag->key);
  free(tag->value);
  free(tag);
}

void free_my_way(my_way *way){
  g_slist_free(way->nodes);
  g_hash_table_destroy(way->tag);
  free(way);
}

void free_my_ways(GHashTable *ways){
  GHashTableIter iter;
  gpointer key;
  gpointer value;
  g_hash_table_iter_init(&iter, ways);
  while(g_hash_table_iter_next(&iter, &key, &value)) {
    free_my_way(value);
  }
  g_hash_table_destroy(ways);
}


void free_my_nodes(GHashTable *nodes){
  GHashTableIter iter;
  gpointer value;
  g_hash_table_iter_init(&iter, nodes);
  while(g_hash_table_iter_next(&iter, NULL, &value)) {
    free_my_node(value);
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

void free_my_relation(my_relation *rel){
  g_slist_free(rel->ways_inner);
  g_slist_free(rel->ways_outer),
  g_slist_free(rel->ways);
  g_slist_free(rel->nodes);
  g_slist_free(rel->relations);
  g_hash_table_destroy(rel->tags);
  free(rel);
}

void free_my_relations(GHashTable *rel){
  GHashTableIter iter;
  gpointer key;
  gpointer value;
  g_hash_table_iter_init(&iter, rel);
  while(g_hash_table_iter_next(&iter, &key, &value)) {
    free_my_relation(value);
  }
  g_hash_table_destroy(rel);
}
