#include "osm_structure.h"
#include <stdlib.h>
#include <stdio.h>

my_way* init_my_way(){
  my_way *way = NULL;
  way  = malloc(sizeof(my_way));
  way->nodes = malloc(MY_NODE_SIZE * sizeof(my_node));
  way->tag = malloc(MY_TAG_SIZE * sizeof(my_tag));
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
  if( (way->size_nodes) == (way->count_nodes) ){
    way->size_nodes += MY_NODE_SIZE;
    way->nodes = realloc(way->nodes,way->size_nodes*sizeof(my_node));
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
  node->count_tag = 0;
  node->size_tag = MY_TAG_SIZE;
  return node;
}

void add_tag_my_node(my_node *node, my_tag tag){
  if( (node->size_tag) == (node->count_tag) ){
    node->size_tag += MY_TAG_SIZE;
    node->tag = realloc(node->tag,node->size_tag * sizeof(my_tag));
  }
  node->tag[node->count_tag] = tag;
  (node->count_tag)++;
}

void free_my_node(my_node *node){
  free(node->tag);
  free(node);
}

my_hashmap_node* init_hashmap(int startsize){
  my_hashmap_node* hm = (my_hashmap_node*)malloc(sizeof(my_hashmap_node));
  hm->table = (hashmap_entry*)calloc(sizeof(hashmap_entry), startsize);
  hm->size = startsize;
  hm->count = 0;
  return hm;
}

void add_node_hashmap(my_hashmap_node* hash, my_node *node, unsigned long id){
  int index, i, step;
  printf("boucle ajout\n");
  do
  {
    index = id % hash->size;
    step = (id % (hash->size-2)) + 1;

    for (i = 0; i < hash->size; i++){
      if (hash->table[index].flags & ACTIVE)
      {
        if (hash->table[index].id == id)
        {
          hash->table[index].node = node;
          return;
        }
      }
      else
      {
        hash->table[index].flags |= ACTIVE;
        hash->table[index].node = node;
        hash->table[index].id = id;
        ++hash->count;
        return;
      }
      index = (index + step) % hash->size;
    }
  }
  while (1);
}

my_node* get_hashmap_node(my_hashmap_node* hash, unsigned long id)
{
  //Si l'hashmap contient un élément
  if (hash->count)
  {
    int index, i, step;
    index = id % hash->size;
    step = (id % (hash->size-2)) + 1;

    for (i = 0; i < hash->size; i++)
    {
      if (hash->table[index].id == id)
      {
        if (hash->table[index].flags & ACTIVE)
          return hash->table[index].node;
        break;
      }
      else
        if (!hash->table[index].node)
          break;

      index = (index + step) % hash->size;
    }
  }

  return 0;
}

void free_hashmap_node(my_hashmap_node* hash)
{
  free(hash->table);
  free(hash);
}
