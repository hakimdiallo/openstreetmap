#include "osm_structure.h"
#include<stdlib.h>

my_way* init_my_way(){
  my_way *way = NULL;
  way  = malloc(sizeof(my_way));
  way->nodes = malloc(MY_NODE_SIZE*sizeof(my_node));
  way->tag = malloc(MY_TAG_SIZE*sizeof(my_tag));
  way->count_nodes = 0;
  way->count_tag = 0;
  way->size_tag = MY_TAG_SIZE;
  way->size_nodes = MY_NODE_SIZE;
  return way;
}

void add_tag_my_way(my_way *way,my_tag tag){
  if( (way->size_tag) <= (way->count_tag) ){
    way->size_tag += MY_TAG_SIZE;
    way->tag = realloc(way,way->size_tag * sizeof(my_tag));
  }
  way->tag[way->count_tag]=tag;
  (way->count_tag)++;
}

void add_node_my_way(my_way *way,my_node node){
  if( (way->size_nodes) <= (way->count_nodes) ){
    way->size_nodes += MY_NODE_SIZE;
    way->nodes = realloc(way,way->size_nodes*sizeof(my_node));
  }
  way->nodes[way->count_nodes] = node;
  (way->count_nodes)++;
}

void free_my_way(my_way *way){
  free(way->nodes);
  free(way->tag);
  free(way);
}

my_node* init_my_node(){
  my_node *node = NULL;
  node = malloc(sizeof(my_node));
  node->tag=malloc(MY_TAG_SIZE*sizeof(my_tag));
  node->count_tag=0;
  node->size_tag=MY_TAG_SIZE;
  return node;
}

void add_tag_my_node(my_node *node, my_tag tag){
  if( (node->size_tag) <= (node->count_tag) ){
    node->size_tag += MY_TAG_SIZE;
    node->tag = realloc(node,node->size_tag * sizeof(my_node));
  }
  node->tag[node->count_tag] = tag;
  (node->count_tag)++;
}

void free_my_node(my_node *node){
  free(node->tag);
  free(node);
}

hashmap_node* init_hashmap(int startsize){
  hashmap_node* hm = (hashmap_node*)malloc(sizeof(hashmap_node));
  hm->map = (hashmap_entry*)calloc(sizeof(hashmap_entry), startsize);
  hm->size = startsize;
  hm->count = 0;

  return hm;
}

void add_node_hashmap(hashmap* hash, my_node *node, int id){
  int index, i, step;

  do
  {
    index = key % hash->size;
    step = (key % (hash->size-2)) + 1;

    for (i = 0; i < hash->size; i++){
        hash->table[index].flags |= ACTIVE;
        hash->table[index].data = (void*)data;
        hash->table[index].key = key;
        ++hash->count;
        return;

      index = (index + step) % hash->size;
    }
  }
  while (1);
}
