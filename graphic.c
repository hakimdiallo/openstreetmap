#include "graphic.h"

#define HIGHWAY "highway"

void draw_line_with_width(SDL_Renderer *renderer, my_way *way, GHashTable *nodes, uint8_t w, uint8_t r, uint8_t g, uint8_t b){
  int i;
  //my_node *node = init_my_node();
  int size = g_slist_length(way->nodes);
  for (i = 0; i < size - 1; i++)
  {
    my_node *node = g_hash_table_lookup(nodes, g_slist_nth_data (way->nodes, i));
    short x1 = (short)(node->lon);
    short y1 = (short)(node->lat);
    node = g_hash_table_lookup(nodes, g_slist_nth_data (way->nodes, i+1));
    short x2 = (short)(node->lon);
    short y2 = (short)(node->lat);
    /*short x1 = (short)((my_node *)(g_hash_table_lookup(nodes, g_list_nth_data (way->nodes, i)))->lon);
    short y1 = (short)((my_node *)(g_hash_table_lookup(nodes, g_list_nth_data (way->nodes, i)))->lat);
    short x2 = (short)((my_node *)(g_hash_table_lookup(nodes, g_list_nth_data (way->nodes, i)))->lon);
    short y2 = (short)((my_node *)(g_hash_table_lookup(nodes, g_list_nth_data (way->nodes, i)))->lon);*/
    thickLineRGBA(renderer,x1,y1,x2,y2,w,r,g,b,255);
  }
  //free_my_node(node);
}


short *get_tab_x(my_way *way, GHashTable *nodes){
  int i;
  short *tab = malloc(sizeof(short)* g_slist_length(way->nodes));
  //my_node *node = init_my_node();
  for (i = 0; i < g_slist_length(way->nodes) - 1; i++)
  {
    my_node *node = g_hash_table_lookup(nodes, g_slist_nth_data (way->nodes, i));
    tab[i] = (short)(node->lon);;
  }
  //free_my_node(node);
  return tab;
}

short *get_tab_y(my_way *way, GHashTable *nodes){
  int i;
  short *tab = malloc(sizeof(short)* g_slist_length(way->nodes));
  //my_node *node = init_my_node();
  for (i = 0; i < g_slist_length(way->nodes) - 1; i++)
  {
    my_node *node = g_hash_table_lookup(nodes, g_slist_nth_data (way->nodes, i));
    tab[i] = (short)(node->lat);
  }
  //free_my_node(node);
  return tab;
}

void dessiner_ways(SDL_Renderer *renderer, GHashTable *ways, GHashTable *nodes){
  GHashTableIter iter;
  gpointer way;
  g_hash_table_iter_init(&iter, ways);
  char *tagValue = NULL ;
  while(g_hash_table_iter_next(&iter, NULL, &way)) {
    //tagValue = malloc(sizeof(char) * 200);
    //my_way *w = (my_way *)
    if(g_hash_table_lookup ( ((my_way *)way)->tag, HIGHWAY) != NULL)
      tagValue = strdup(g_hash_table_lookup ( ((my_way *)way)->tag, HIGHWAY));
    //printf("%s\n", tagValue);
    if( tagValue != NULL){//existance d'un highway
      if (!strcmp(tagValue, "motorway")) {
        draw_line_with_width(renderer,(my_way *)way,nodes,18,233,144,160);
      }
      else if(!strcmp(tagValue,"trunk")){
        draw_line_with_width(renderer,(my_way *)way,nodes,18,251,178,154);
      }
      else if(!strcmp(tagValue,"primary") || !strcmp(tagValue,"primary_link")){
        draw_line_with_width(renderer,(my_way *)way,nodes,15,236,152,154);
      }
      else if(!strcmp(tagValue,"secondary") || !strcmp(tagValue,"secondary_link")){
        draw_line_with_width(renderer,(my_way *)way,nodes,15,254,215,165);
      }
      else if(!strcmp(tagValue,"tertiary") || !strcmp(tagValue,"tertiary_link")){
        draw_line_with_width(renderer,(my_way *)way,nodes,15,255,255,179);
        //draw_line_with_width(renderer,(my_way *)way,nodes,15,0,254,254);
      }
      else if(!strcmp(tagValue,"unclassified")){
        draw_line_with_width(renderer,(my_way *)way,nodes,10,254,254,254);
      }
      else if(!strcmp(tagValue,"residential")){
        draw_line_with_width(renderer,(my_way *)way,nodes,10,254,254,254);
      }
      else if(!strcmp(tagValue,"service")){
        draw_line_with_width(renderer,(my_way *)way,nodes,7,254,254,254);
      }
      else if(!strcmp(tagValue,"pedestrian")){
        draw_line_with_width(renderer,(my_way *)way,nodes,5,237,237,237);
      }
      else if(!strcmp(tagValue,"footway") || !strcmp(tagValue,"path")){
        draw_line_with_width(renderer,(my_way *)way,nodes,2,248,147,136);
      }
      else if(!strcmp(tagValue,"motorway_link")){
        draw_line_with_width(renderer,(my_way *)way,nodes,10,233,144,160);
      }
      else if(!strcmp(tagValue,"trunk_link")){
        draw_line_with_width(renderer,(my_way *)way,nodes,15,251,178,154);
      }
      else if(!strcmp(tagValue,"living_street")){
        draw_line_with_width(renderer,(my_way *)way,nodes,15,237,237,237);
      }
      else if(!strcmp(tagValue,"track")){
        draw_line_with_width(renderer,(my_way *)way,nodes,2,172,131,39);
      }
      else if(!strcmp(tagValue,"bus_guideway")){
        draw_line_with_width(renderer,(my_way *)way,nodes,4,100,100,255);
      }
      else if(!strcmp(tagValue,"raceway")){
        draw_line_with_width(renderer,(my_way *)way,nodes,7,255,192,202);
      }
      else if(!strcmp(tagValue,"road")){
        draw_line_with_width(renderer,(my_way *)way,nodes,2,221,221,221);
      }
      else if(!strcmp(tagValue,"bridleway")){
        draw_line_with_width(renderer,(my_way *)way,nodes,2,73,161,72);
      }
      else if(!strcmp(tagValue,"steps")){
        draw_line_with_width(renderer,(my_way *)way,nodes,5,252,119,102);
      }
      else if(!strcmp(tagValue,"cycleway")){
        draw_line_with_width(renderer,(my_way *)way,nodes,2,155,154,245);
      }
      else{
        printf("highway: %s\n",tagValue );
      }
    }
    /*else{
      short *tab_x = get_tab_x((my_way *)way,nodes);
      short *tab_y = get_tab_y((my_way *)way,nodes);
      //filledPolygonRGBA(renderer, tab_x, tab_y, (my_way *)way,nodes->count_nodes, 191, 174, 174, 255);
      filledPolygonRGBA(renderer, tab_x, tab_y, ((my_way *)way)->count_nodes, 221, 221, 221, 255);
    }*/
  }
  SDL_RenderPresent(renderer);
  free(tagValue);
}
