#include "graphic.h"

#define HIGHWAY "highway"

int coastline = 0;
void draw_line_with_width(SDL_Renderer *renderer, my_way *way, GHashTable *nodes, uint8_t width, uint8_t r, uint8_t g, uint8_t b){
  int i;
  //my_node *node = init_my_node();
  int size = g_slist_length(way->nodes);
  for (i = 0; i < size - 1; i++){
    my_node *node1 = (my_node *)malloc(sizeof(my_node));
    node1 = g_hash_table_lookup(nodes, g_slist_nth_data(way->nodes, i));
    short x1 = (short)(node1->lon);
    //printf("%d\n", x1);
    short y1 = (short)(node1->lat);
    //printf("%d\n", y1);
    my_node *node2 = (my_node *)malloc(sizeof(my_node));
    node2 = g_hash_table_lookup(nodes, g_slist_nth_data (way->nodes, i+1));
    short x2 = (short)(node2->lon);
    //printf("%d\n", x2);
    short y2 = (short)(node2->lat);
    //printf("%d\n", y2);
    thickLineRGBA(renderer,x1,y1,x2,y2,width,r,g,b,255);
  }
}


short *get_tab_x(my_way *way, GHashTable *hash_nodes){
  int i;
  short *tab = malloc(sizeof(short)* g_slist_length(way->nodes));
  int count = g_slist_length(way->nodes);
  for (i = 0; i < count; i++){
    my_node *node = (my_node *)malloc(sizeof(my_node));
    node = (my_node *)g_hash_table_lookup(hash_nodes, g_slist_nth_data (way->nodes, i));
    tab[i] = (short)(node->lon);
  }
  //free_my_node(node);
  return tab;
}

short *get_tab_y(my_way *way, GHashTable *hash_nodes){
  int i;
  short *tab = malloc(sizeof(short)* g_slist_length(way->nodes));
  int count = g_slist_length(way->nodes);
  for (i = 0; i < count; i++)
  {
    my_node *node = (my_node *)malloc(sizeof(my_node));
    node = (my_node *)g_hash_table_lookup(hash_nodes, g_slist_nth_data (way->nodes, i));
    tab[i] = (short)(node->lat);
  }
  //free_my_node(node);
  return tab;
}

void dessiner_ways(SDL_Renderer *renderer, GHashTable *ways, GHashTable *nodes){
  GHashTableIter iter;
  gpointer way;
  g_hash_table_iter_init(&iter, ways);
  //char *tagValue = NULL ;
  while(g_hash_table_iter_next(&iter, NULL, &way)) {
    GHashTableIter iter2;
    gpointer key;
    gpointer value;
    my_way *w = (my_way *)way;
    g_hash_table_iter_init(&iter2, w->tag);
    while (g_hash_table_iter_next(&iter2, &key, &value)) {
      char *tag_key = (char *)key;
      char *tag_value = (char *)value;
      if(!strcmp(tag_key,"highway")){
          //v = strdup(ways[i]->tag[j].value);
          if(!strcmp(tag_value,"motorway")){
            //fait
            draw_line_with_width(renderer,w,nodes,18,243,132,154);
          }
          else if(!strcmp(tag_value,"trunk")){
            //fait
            draw_line_with_width(renderer,w,nodes,18,255,176,147);
          }
          else if(!strcmp(tag_value,"primary") || !strcmp(tag_value,"primary_link")){
            //fait
            draw_line_with_width(renderer,w,nodes,15,254,221,155);
          }
          else if(!strcmp(tag_value,"secondary") || !strcmp(tag_value,"secondary_link")){
            //fait
            draw_line_with_width(renderer,w,nodes,15,239,255,183);
          }
          else if(!strcmp(tag_value,"tertiary") || !strcmp(tag_value,"tertiary_link")){
            //fait
            draw_line_with_width(renderer,w,nodes,15,245,245,245);
            //draw_line_with_width(renderer,ways[i],15,0,254,254);
          }
          else if(!strcmp(tag_value,"unclassified")){
            //fait
            draw_line_with_width(renderer,w,nodes,10,240,239,231);
          }
          else if(!strcmp(tag_value,"residential")){
            //fait
            draw_line_with_width(renderer,w,nodes,10,240,239,231);
          }
          else if(!strcmp(tag_value,"service")){
            //fait
            draw_line_with_width(renderer,w,nodes,7,240,239,231);
          }
          else if(!strcmp(tag_value,"pedestrian")){
            //fait
            draw_line_with_width(renderer,w,nodes,5,222,217,232);
          }
          else if(!strcmp(tag_value,"footway") || !strcmp(tag_value,"path")){
            //fait
            draw_line_with_width(renderer,w,nodes,2,250,135,122);
          }
          else if(!strcmp(tag_value,"motorway_link")){
            //fait
            draw_line_with_width(renderer,w,nodes,10,243,132,155);
          }
          else if(!strcmp(tag_value,"trunk_link")){
            //fait
            draw_line_with_width(renderer,w,nodes,15,255,176,147);
          }
          else if(!strcmp(tag_value,"living_street")){
            //fait
            draw_line_with_width(renderer,w,nodes,15,236,237,236);
          }
          else if(!strcmp(tag_value,"track")){
            //fait
            draw_line_with_width(renderer,w,nodes,2,171,139,24);
          }
          else if(!strcmp(tag_value,"bus_guideway")){
            //fait
            draw_line_with_width(renderer,w,nodes,4,102,102,255);
          }
          else if(!strcmp(tag_value,"raceway")){
            //fait
            draw_line_with_width(renderer,w,nodes,7,255,184,198);
          }
          else if(!strcmp(tag_value,"road")){
            //fait
            draw_line_with_width(renderer,w,nodes,2,220,220,220);
          }
          else if(!strcmp(tag_value,"bridleway")){
            //fait
            draw_line_with_width(renderer,w,nodes,2,105,177,103);
          }
          else if(!strcmp(tag_value,"steps")){
            //fait
            draw_line_with_width(renderer,w,nodes,5,251,152,136);
          }
          else if(!strcmp(tag_value,"cycleway")){
            //fait
            draw_line_with_width(renderer,w,nodes,2,113,11,249);
          }
          else{
            printf("highway: %s\n",tag_value);
          }
        }
        else if(!strcmp(tag_key,"building")){
          if(!strcmp(tag_key,"building")){
            short *tab_x = get_tab_x(w,nodes);
            short *tab_y = get_tab_y(w,nodes);
            filledPolygonRGBA(renderer, tab_x, tab_y, g_slist_length(w->nodes), 191, 174, 174, 255);
            polygonRGBA(renderer, tab_x, tab_y, g_slist_length(w->nodes), 168, 146, 162, 255);
          }
        }
        else if(!strcmp(tag_key,"waterway")){
          //v = strdup(ways[i]->tag[j].value);
          if(!strcmp(tag_value,"river")){
            //fait
            draw_line_with_width(renderer,w,nodes,10,174,208,208);
          }
          else if(!strcmp(tag_value,"riverbank")){
            short *tab_x = get_tab_x(w,nodes);
            short *tab_y = get_tab_y(w,nodes);
            filledPolygonRGBA(renderer, tab_x, tab_y, g_slist_length(w->nodes), 181,208,208, 255);
          }
          else if(!strcmp(tag_value,"stream")){
            //fait
            draw_line_with_width(renderer,w,nodes,2,179,210,211);
          }
        }

        else if(!strcmp(tag_key,"landuse") || !strcmp(tag_key,"leisure")){
          //v = strdup(ways[i]->tag[j].value);
          if(!strcmp(tag_value,"grass")){
            short *tab_x = get_tab_x(w,nodes);
            short *tab_y = get_tab_y(w,nodes);
            //fait
            filledPolygonRGBA(renderer, tab_x, tab_y, g_slist_length(w->nodes), 207,249, 249, 249);
          }
          else if(!strcmp(tag_value,"forest")){
            short *tab_x = get_tab_x(w,nodes);
            short *tab_y = get_tab_y(w,nodes);
            //fait
            filledPolygonRGBA(renderer, tab_x, tab_y, g_slist_length(w->nodes), 157,139,214,137);
          }
          else if(!strcmp(tag_value,"park")){
            short *tab_x = get_tab_x(w,nodes);
            short *tab_y = get_tab_y(w,nodes);
            //fait
            filledPolygonRGBA(renderer, tab_x, tab_y, g_slist_length(w->nodes), 205, 205,247,201);
          }
          else if(!strcmp(tag_value,"garden")){
            short *tab_x = get_tab_x(w,nodes);
            short *tab_y = get_tab_y(w,nodes);
            //fait
            filledPolygonRGBA(renderer, tab_x, tab_y, g_slist_length(w->nodes), 207, 207,236,168);
          }
          else if(!strcmp(tag_value,"pitch")){
            short *tab_x = get_tab_x(w,nodes);
            short *tab_y = get_tab_y(w,nodes);
            //fait
            filledPolygonRGBA(renderer, tab_x, tab_y, g_slist_length(w->nodes), 138, 138,211,175);
          }
        }
        else if(!strcmp(tag_key,"area")){
          //v = strdup(ways[i]->tag[j].value);
          if(!strcmp(tag_value,"yes")){
            short *tab_x = get_tab_x(w,nodes);
            short *tab_y = get_tab_y(w,nodes);
            filledPolygonRGBA(renderer, tab_x, tab_y, g_slist_length(w->nodes), 237, 237, 237, 255);
          }else{
            printf("%s\n",tag_value);
          }
        }
        else if(!strcmp(tag_key,"barrier")){
          //v = strdup(ways[i]->tag[j].value);
          if(!strcmp(tag_value,"fence")){
            //short *tab_x = get_tab_x(ways[i]);
            //short *tab_y = get_tab_y(ways[i]);
            //polygonRGBA(renderer, tab_x, tab_y, ways[i]->count_nodes, 173,171,168, 255);
            draw_line_with_width(renderer,w,nodes,1,171,170,166);
          }
        }
        else if(!strcmp(tag_key,"source")){
          //v = strdup(ways[i]->tag[j].value);
            if (g_hash_table_size(w->tag) == 1) {
              short *tab_x = get_tab_x(w,nodes);
              short *tab_y = get_tab_y(w,nodes);
              filledPolygonRGBA(renderer, tab_x, tab_y, g_slist_length(w->nodes), 221, 221, 221, 255);
            }
            //draw_line_with_width(renderer,w,nodes,1,168, 146, 162);
        }
        else{
          //printf("%s - %s\n",ways[i]->tag[j].key,ways[i]->tag[j].value);
        }
    }
  }
  SDL_RenderPresent(renderer);
  //free(tagValue);
}

<<<<<<< HEAD
void dessiner_way_water(SDL_Renderer *renderer, my_way *w, GHashTable *ways, GHashTable *nodes){
    if ( w == NULL ) {
      return;
    }
    if ( (w->tag) == NULL) {
      return;
    }
    GHashTableIter iter2;
    gpointer key;
    gpointer value;
    g_hash_table_iter_init(&iter2, w->tag);
    while (g_hash_table_iter_next(&iter2, &key, &value)) {
      char *tag_key = (char *)key;
      char *tag_value = (char *)value;
      if(!strcmp(tag_key,"waterway")){
          if(!strcmp(tag_value,"river")){
            draw_line_with_width(renderer,w,nodes,10,174,208,208);
          }
          else if(!strcmp(tag_value,"riverbank")){
            short *tab_x = get_tab_x(w,nodes);
            short *tab_y = get_tab_y(w,nodes);
            filledPolygonRGBA(renderer, tab_x, tab_y,g_slist_length(w->nodes), 181,174,208,208);
          }
          else if(!strcmp(tag_value,"stream")){
            //fait
            draw_line_with_width(renderer,w,nodes,2,180,208,209);
          }
      }
      else if(!strcmp(tag_key,"natural")){
        /*if(!strcmp(tag_value,"water")){
          short *tab_x = get_tab_x(w,nodes);
          short *tab_y = get_tab_y(w,nodes);
          filledPolygonRGBA(renderer, tab_x, tab_y, g_slist_length(w->nodes), 180, 208, 209, 255);
          polygonRGBA(renderer, tab_x, tab_y, g_slist_length(w->nodes), 175, 175, 175, 255);
        }*/
        if(!strcmp(tag_value,"coastline")){
          if ( !coastline) {
            //fait
            SDL_SetRenderDrawColor(renderer, 180, 174, 208, 208);
            SDL_RenderClear(renderer);
            coastline = 1;
          }
          short *tab_x = get_tab_x(w,nodes);
          short *tab_y = get_tab_y(w,nodes);
          filledPolygonRGBA(renderer, tab_x, tab_y, g_slist_length(w->nodes), 221, 221, 221, 255);
          //SDL_RenderPresent(renderer);
        }
      }
    }
}

void dessiner_way_building(SDL_Renderer *renderer, my_way *w, GHashTable *ways, GHashTable *nodes){
    if ( w == NULL ) {
      return;
    }
    if ( (w->tag) == NULL) {
      return;
    }
    GHashTableIter iter2;
    gpointer key;
    gpointer value;
    g_hash_table_iter_init(&iter2, w->tag);
    while (g_hash_table_iter_next(&iter2, &key, &value)) {
      char *tag_key = (char *)key;
      char *tag_value = (char *)value;
      if(!strcmp(tag_key,"building")){
          if(!strcmp(tag_key,"building")){
            short *tab_x = get_tab_x(w,nodes);
            short *tab_y = get_tab_y(w,nodes);
            filledPolygonRGBA(renderer, tab_x, tab_y, g_slist_length(w->nodes), 191, 174, 174, 255);
            polygonRGBA(renderer, tab_x, tab_y, g_slist_length(w->nodes), 168, 146, 162, 255);
          }
      }
      else if(!strcmp(tag_key,"area")){
        if(!strcmp(tag_value,"yes")){
          short *tab_x = get_tab_x(w,nodes);
          short *tab_y = get_tab_y(w,nodes);
          filledPolygonRGBA(renderer, tab_x, tab_y, g_slist_length(w->nodes), 237, 237, 237, 255);
          polygonRGBA(renderer, tab_x, tab_y, g_slist_length(w->nodes), 175, 175, 175, 255);;
        }else{
          printf("area: %s\n",tag_value);
        }
      }
    }
}

void dessiner_way_highway(SDL_Renderer *renderer, my_way *w, GHashTable *ways, GHashTable *nodes){
    if ( w == NULL ) {
      return;
    }
    if ( (w->tag) == NULL) {
      return;
    }
    GHashTableIter iter2;
    gpointer key;
    gpointer value;
    g_hash_table_iter_init(&iter2, w->tag);
    while (g_hash_table_iter_next(&iter2, &key, &value)) {
      char *tag_key = (char *)key;
      char *tag_value = (char *)value;
      if(!strcmp(tag_key,"highway")){
          if(!strcmp(tag_value,"unclassified")){
            draw_line_with_width(renderer,w,nodes,10,254,254,254);
          }
          else if(!strcmp(tag_value,"residential")){
            draw_line_with_width(renderer,w,nodes,10,254,254,254);
          }
          else if(!strcmp(tag_value,"service")){
            draw_line_with_width(renderer,w,nodes,5,254,254,254);
          }
          else if(!strcmp(tag_value,"pedestrian")){
            //fait
            draw_line_with_width(renderer,w,nodes,5,222,217,223);
          }
          else if(!strcmp(tag_value,"footway") || !strcmp(tag_value,"path")){
            //fait
            draw_line_with_width(renderer,w,nodes,2,250,135,122);
          }
          else if(!strcmp(tag_value,"motorway_link")){
            //fait
            draw_line_with_width(renderer,w,nodes,10,243,132,155);
          }
          else if(!strcmp(tag_value,"trunk_link")){
            //fait
            draw_line_with_width(renderer,w,nodes,13,255,176,147);
          }
          else if(!strcmp(tag_value,"living_street")){
            //fait
            draw_line_with_width(renderer,w,nodes,13,236,237,236);
          }
          else if(!strcmp(tag_value,"track")){
            //fait
            draw_line_with_width(renderer,w,nodes,2,171,139,25);
          }
          else if(!strcmp(tag_value,"bus_guideway")){
            //fait
            draw_line_with_width(renderer,w,nodes,4,142,142,249);
          }
          else if(!strcmp(tag_value,"raceway")){
            //fait
            draw_line_with_width(renderer,w,nodes,7,255,184,198);
          }
          else if(!strcmp(tag_value,"road")){
            //fait
            draw_line_with_width(renderer,w,nodes,2,220,220,220);
          }
          else if(!strcmp(tag_value,"bridleway")){
            //fait
            draw_line_with_width(renderer,w,nodes,2,137,192,133);
          }
          else if(!strcmp(tag_value,"steps")){
            //fait
            draw_line_with_width(renderer,w,nodes,5,251,152,136);
          }
          else if(!strcmp(tag_value,"cycleway")){
            //fait
            draw_line_with_width(renderer,w,nodes,2,113,113,249);
          }
        }
    }
}

void dessiner_way_highway_second(SDL_Renderer *renderer, my_way *w, GHashTable *ways, GHashTable *nodes){
    if ( w == NULL ) {
      return;
    }
    if ( (w->tag) == NULL) {
      return;
    }
    GHashTableIter iter2;
    gpointer key;
    gpointer value;
    g_hash_table_iter_init(&iter2, w->tag);
    while (g_hash_table_iter_next(&iter2, &key, &value)) {
      char *tag_key = (char *)key;
      char *tag_value = (char *)value;
      if(!strcmp(tag_key,"highway")){
          if(!strcmp(tag_value,"motorway")){
            //fait
            draw_line_with_width(renderer,w,nodes,10,243,132,154);
          }
          else if(!strcmp(tag_value,"trunk")){
            //fait
            draw_line_with_width(renderer,w,nodes,10,255,176,147);
          }
          if(!strcmp(tag_value,"primary") || !strcmp(tag_value,"primary_link")){
            //fait
            draw_line_with_width(renderer,w,nodes,10,254,221,155);
          }
          else if(!strcmp(tag_value,"secondary") || !strcmp(tag_value,"secondary_link")){
            draw_line_with_width(renderer,w,nodes,10,239,255,183);
          }
          else if(!strcmp(tag_value,"tertiary") || !strcmp(tag_value,"tertiary_link")){
            //fait
            draw_line_with_width(renderer,w,nodes,10,245,245,245);
            //draw_line_with_width(renderer,ways[i],15,0,254,254);
          }
        }
    }
}

=======
>>>>>>> 18bd2b290a2dfbe1101149cd65dc91a9f3728dcb
void dessiner_way(SDL_Renderer *renderer, my_way *w, GHashTable *ways, GHashTable *nodes){
    if ( w == NULL ) {
      return;
    }
    if( w->tag == NULL || g_hash_table_size(w->tag) == 0 ||
        (g_hash_table_size(w->tag) == 1 && g_hash_table_lookup(w->tag,(const char *)"source") != NULL) ) {
      short *tab_x = get_tab_x(w,nodes);
      short *tab_y = get_tab_y(w,nodes);
      filledPolygonRGBA(renderer, tab_x, tab_y, g_slist_length(w->nodes), 221, 221, 221, 255);
      polygonRGBA(renderer, tab_x, tab_y, g_slist_length(w->nodes), 168, 146, 162, 255);
      w->drawn = 1;
      g_hash_table_insert(ways,&(w->at.id),w);
      return;
    }
    GHashTableIter iter2;
    gpointer key;
    gpointer value;
    g_hash_table_iter_init(&iter2, w->tag);
    while (g_hash_table_iter_next(&iter2, &key, &value)) {
      char *tag_key = (char *)key;
      char *tag_value = (char *)value;
<<<<<<< HEAD
      //if(!strcmp(tag_key,"highway")){
          /*if(!strcmp(tag_value,"motorway")){
            draw_line_with_width(renderer,w,nodes,18,243,132,154);
          }
          else if(!strcmp(tag_value,"trunk")){
            draw_line_with_width(renderer,w,nodes,18,255,176,147);
          }
          if(!strcmp(tag_value,"primary") || !strcmp(tag_value,"primary_link")){
            draw_line_with_width(renderer,w,nodes,15,254,221,155);
          }
          else if(!strcmp(tag_value,"secondary") || !strcmp(tag_value,"secondary_link")){
            draw_line_with_width(renderer,w,nodes,15,239,255,183);
          }
          else if(!strcmp(tag_value,"tertiary") || !strcmp(tag_value,"tertiary_link")){
            draw_line_with_width(renderer,w,nodes,15,245,245,245);
=======
      if(!strcmp(tag_key,"highway")){
          if(!strcmp(tag_value,"motorway")){
            draw_line_with_width(renderer,w,nodes,9,233,144,160);
          }
          else if(!strcmp(tag_value,"trunk")){
            draw_line_with_width(renderer,w,nodes,9,251,178,154);
          }
          else if(!strcmp(tag_value,"primary") || !strcmp(tag_value,"primary_link")){
            draw_line_with_width(renderer,w,nodes,9,236,152,154);
          }
          else if(!strcmp(tag_value,"secondary") || !strcmp(tag_value,"secondary_link")){
            draw_line_with_width(renderer,w,nodes,9,254,215,165);
          }
          else if(!strcmp(tag_value,"tertiary") || !strcmp(tag_value,"tertiary_link")){
            draw_line_with_width(renderer,w,nodes,9,255,255,179);
>>>>>>> 18bd2b290a2dfbe1101149cd65dc91a9f3728dcb
            //draw_line_with_width(renderer,ways[i],15,0,254,254);
          }
          else if(!strcmp(tag_value,"unclassified")){
            draw_line_with_width(renderer,w,nodes,9,254,254,254);
          }
          else if(!strcmp(tag_value,"residential")){
            draw_line_with_width(renderer,w,nodes,9,254,254,254);
          }
          else if(!strcmp(tag_value,"service")){
            draw_line_with_width(renderer,w,nodes,5,254,254,254);
          }
          else if(!strcmp(tag_value,"pedestrian")){
            draw_line_with_width(renderer,w,nodes,5,237,237,237);
          }
          else if(!strcmp(tag_value,"footway") || !strcmp(tag_value,"path")){
            draw_line_with_width(renderer,w,nodes,2,248,147,136);
          }
          else if(!strcmp(tag_value,"motorway_link")){
<<<<<<< HEAD
            draw_line_with_width(renderer,w,nodes,10,243,132,154);
          }
          else if(!strcmp(tag_value,"trunk_link")){
            draw_line_with_width(renderer,w,nodes,15,255,176,147);
=======
            draw_line_with_width(renderer,w,nodes,9,233,144,160);
          }
          else if(!strcmp(tag_value,"trunk_link")){
            draw_line_with_width(renderer,w,nodes,9,251,178,154);
>>>>>>> 18bd2b290a2dfbe1101149cd65dc91a9f3728dcb
          }
          else if(!strcmp(tag_value,"living_street")){
            draw_line_with_width(renderer,w,nodes,9,237,237,237);
          }
          else if(!strcmp(tag_value,"track")){
            draw_line_with_width(renderer,w,nodes,2,172,131,39);
          }
          else if(!strcmp(tag_value,"bus_guideway")){
            draw_line_with_width(renderer,w,nodes,4,100,100,255);
          }
          else if(!strcmp(tag_value,"raceway")){
            draw_line_with_width(renderer,w,nodes,7,255,192,202);
          }
          else if(!strcmp(tag_value,"road")){
            draw_line_with_width(renderer,w,nodes,2,221,221,221);
          }
          else if(!strcmp(tag_value,"bridleway")){
            draw_line_with_width(renderer,w,nodes,2,73,161,72);
          }
          else if(!strcmp(tag_value,"steps")){
            draw_line_with_width(renderer,w,nodes,5,252,119,102);
          }
          else if(!strcmp(tag_value,"cycleway")){
            draw_line_with_width(renderer,w,nodes,2,155,154,245);
          }
          else{
            printf("highway: %s\n",tag_value);
          }
        }
        else if(!strcmp(tag_key,"building")){
          if(!strcmp(tag_key,"building")){
            //printf("role %d\n",role );
            short *tab_x = get_tab_x(w,nodes);
            short *tab_y = get_tab_y(w,nodes);
            filledPolygonRGBA(renderer, tab_x, tab_y, g_slist_length(w->nodes), 191, 174, 174, 255);
            polygonRGBA(renderer, tab_x, tab_y, g_slist_length(w->nodes), 168, 146, 162, 255);
          }
        }
        else if(!strcmp(tag_key,"waterway")){
          if(!strcmp(tag_value,"river")){
            draw_line_with_width(renderer,w,nodes,10,180,190,209);
          }
          else if(!strcmp(tag_value,"riverbank")){
            short *tab_x = get_tab_x(w,nodes);
            short *tab_y = get_tab_y(w,nodes);
            filledPolygonRGBA(renderer, tab_x, tab_y,g_slist_length(w->nodes), 181,208,208, 255);
            //draw_line_with_width(renderer,ways[i],50,180,208,209);
          }
          else if(!strcmp(tag_value,"stream")){
            draw_line_with_width(renderer,w,nodes,2,180,208,209);
          }
        }
        else if(!strcmp(tag_key,"natural")){
          if(!strcmp(tag_value,"water")){
            short *tab_x = get_tab_x(w,nodes);
            short *tab_y = get_tab_y(w,nodes);
            filledPolygonRGBA(renderer, tab_x, tab_y, g_slist_length(w->nodes), 180,174,208,208);
            polygonRGBA(renderer, tab_x, tab_y, g_slist_length(w->nodes), 175, 175, 175, 255);
          }
          else if(!strcmp(tag_value,"coastline")){
            if ( !coastline) {
              SDL_SetRenderDrawColor(renderer, 180, 208, 209, 255);
              SDL_RenderClear(renderer);
              coastline = 1;
            }
            short *tab_x = get_tab_x(w,nodes);
            short *tab_y = get_tab_y(w,nodes);
            filledPolygonRGBA(renderer, tab_x, tab_y, g_slist_length(w->nodes), 221, 221, 221, 255);
          }
        }
        //*******************************************************************
      //  **********************************************************************
        //**********************************************************************
      //  ************************************************************************
      //*******************************************************************************

        else if(!strcmp(tag_key,"landuse") || !strcmp(tag_key,"leisure")){
          if(!strcmp(tag_value,"grass")){
            short *tab_x = get_tab_x(w,nodes);
            short *tab_y = get_tab_y(w,nodes);
            filledPolygonRGBA(renderer, tab_x, tab_y, g_slist_length(w->nodes), 207, 237, 165, 255);
            polygonRGBA(renderer, tab_x, tab_y, g_slist_length(w->nodes), 175, 175, 175, 255);
          }
          else if(!strcmp(tag_value,"forest")){
            short *tab_x = get_tab_x(w,nodes);
            short *tab_y = get_tab_y(w,nodes);
            filledPolygonRGBA(renderer, tab_x, tab_y, g_slist_length(w->nodes), 157, 202, 138, 255);
            polygonRGBA(renderer, tab_x, tab_y, g_slist_length(w->nodes), 175, 175, 175, 255);
          }
          else if(!strcmp(tag_value,"park")){
            short *tab_x = get_tab_x(w,nodes);
            short *tab_y = get_tab_y(w,nodes);
            filledPolygonRGBA(renderer, tab_x, tab_y, g_slist_length(w->nodes), 205, 247, 201, 255);
            polygonRGBA(renderer, tab_x, tab_y, g_slist_length(w->nodes), 175, 175, 175, 255);
          }
          else if(!strcmp(tag_value,"garden")){
            short *tab_x = get_tab_x(w,nodes);
            short *tab_y = get_tab_y(w,nodes);
            filledPolygonRGBA(renderer, tab_x, tab_y, g_slist_length(w->nodes), 207, 236, 168, 255);
            polygonRGBA(renderer, tab_x, tab_y, g_slist_length(w->nodes), 175, 175, 175, 255);
          }
          else if(!strcmp(tag_value,"pitch")){
            short *tab_x = get_tab_x(w,nodes);
            short *tab_y = get_tab_y(w,nodes);
            filledPolygonRGBA(renderer, tab_x, tab_y, g_slist_length(w->nodes), 138, 211, 175, 255);
          }
        }
        else if(!strcmp(tag_key,"area")){
          if(!strcmp(tag_value,"yes")){
            short *tab_x = get_tab_x(w,nodes);
            short *tab_y = get_tab_y(w,nodes);
            filledPolygonRGBA(renderer, tab_x, tab_y, g_slist_length(w->nodes), 237, 237, 237, 255);
            polygonRGBA(renderer, tab_x, tab_y, g_slist_length(w->nodes), 175, 175, 175, 255);;
          }else{
            printf("area: %s\n",tag_value);
          }
        }
    }
    w->drawn = 1;
    g_hash_table_insert(ways,&(w->at.id),w);
}

void draw_way_of_relation(SDL_Renderer *renderer, GSList *list, GHashTable *hash_ways, GHashTable *hash_nodes){
  int i;
  int count = g_slist_length(list);
  for (i = 0; i < count; i++) {
    char *data = g_slist_nth_data(list, i);
    my_way *way = (my_way *)malloc(sizeof(my_way));
    way = (my_way *)g_hash_table_lookup(hash_ways,data);
    if ( way == NULL ) {
      //printf("way null...\n");
    }
    else
      dessiner_way(renderer,way,hash_ways,hash_nodes);

    way = NULL;
  }
}

void dessiner_une_relation(SDL_Renderer *renderer, my_relation *rel, GHashTable *hash_relations, GHashTable *hash_ways, GHashTable *hash_nodes){
  //if ( !(rel->drawn) ) {
    if ( (rel->relations) != NULL ){
      if (g_slist_length(rel->relations) > 0) {
        int i;
        int size = g_slist_length(rel->relations);
        for (i = 0; i < size; i++) {
          char *data = g_slist_nth_data (rel->relations, i);
          //printf("rel n: %s\n",data);

          my_relation *re = (my_relation *)malloc(sizeof(my_relation));
          re = (my_relation *)g_hash_table_lookup(hash_relations,data);
          if(re == NULL){
            //printf("relation null...\n");
          }
          else
            dessiner_une_relation(renderer,re,hash_relations,hash_ways,hash_nodes);
        }
      }
    }
    if ( rel->ways_outer != NULL && g_slist_length(rel->ways_outer) > 0 ){
      draw_way_of_relation(renderer,rel->ways_outer,hash_ways, hash_nodes);
    }
    if ( rel->ways_inner != NULL && g_slist_length(rel->ways_inner) > 0 ){
      draw_way_of_relation(renderer,rel->ways_inner,hash_ways,hash_nodes);
    }
    if ( rel->ways != NULL && g_slist_length(rel->ways) > 0 ){
    //  draw_way_of_relation(renderer,rel->ways,hash_ways,hash_nodes);
    }
    if ( rel->nodes != NULL && g_slist_length(rel->nodes) > 0 ){
      /* code */
    }
  //}
}

void dessiner_relations(SDL_Renderer *renderer, GHashTable *relations, GHashTable *ways, GHashTable *nodes){
  GHashTableIter iter5;
  gpointer relat5;
  g_hash_table_iter_init(&iter5, relations);
  while(g_hash_table_iter_next(&iter5, NULL, &relat5)){
    my_relation *rel = (my_relation *)malloc(sizeof(my_relation));
    rel = (my_relation *)relat5;
    dessiner_une_relation(renderer,rel,relations,ways,nodes);
  }
  printf("done relations...\n");
}

void dessiner_hash_ways(SDL_Renderer *renderer, GHashTable *hash_ways, GHashTable *hash_nodes){
   GHashTableIter iter5;
   gpointer val5;
   g_hash_table_iter_init(&iter5, hash_ways);
 	 while(g_hash_table_iter_next(&iter5, NULL, &val5)){
 		 my_way *way = (my_way *)malloc(sizeof(my_way));
     way = (my_way *)val5;
      if((way->drawn) == 0){
        dessiner_way(renderer,way,hash_ways,hash_nodes);
      }
      way = NULL;
 	 }
   printf("done ways...\n");
}

void rendererMap(GHashTable *hash_ways, GHashTable *hash_nodes, GHashTable *hash_relations){
  SDL_Window *win = NULL;
  SDL_Renderer *renderer = NULL;

  SDL_Init(SDL_INIT_VIDEO);

  win = SDL_CreateWindow("MY OSM RENDERER", SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED, WIDTH+100, HEIGHT+100, SDL_WINDOW_RESIZABLE);

  renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,WIDTH,HEIGHT);
	//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // permet d'obtenir les redimensionnements plus doux.
	SDL_SetRenderTarget(renderer, texture); //on modifie la texture
	SDL_SetRenderDrawColor(renderer, 221, 221, 221, 255);
	SDL_RenderClear(renderer);
	//dessiner_ways(renderer, ways, nodes );
	dessiner_relations(renderer,hash_relations,hash_ways,hash_nodes);
	dessiner_hash_ways(renderer,hash_ways,hash_nodes);
	SDL_SetRenderTarget(renderer, NULL);// Dorénavent, on modifie à nouveau le renderer
	SDL_Rect position;
	SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
	int ecranw,  ecranh;
	SDL_GetWindowSize(win, &ecranw, &ecranh); //on recupère la largeur et la hauteur de la fenêtre
	position.x = ecranw/2 - position.w/2;
	position.y = ecranh/2 - position.h/2;

	SDL_RenderCopy(renderer,texture,NULL,&position);
	SDL_RenderPresent(renderer);
	printf("draw ...\n");
	int continuer = 1;
  while (continuer) {
      SDL_Event event;
      SDL_WaitEvent(&event);
      switch (event.type) {
      	case SDL_QUIT:
					continuer = 0;
					break;
				case SDL_WINDOWEVENT:
	        switch ( event.window.event ) {
						case SDL_WINDOWEVENT_SIZE_CHANGED:
							position.x = event.window.data1/2 - position.w/2;
							position.y = event.window.data2/2 - position.h/2;
            break;

	        }
          case SDL_MOUSEBUTTONDOWN:
  						switch (event.button.button) {
  							case SDL_BUTTON_LEFT:
  								printf("%d\n", event.button.x);
  								printf("%d\n", event.button.y);
  								break;
  						}
  						switch (event.button.state){
  							case SDL_PRESSED:
  								printf("enfoncé\n");
  								break;
  						}
      }
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			SDL_RenderPresent(renderer);
  }
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
  SDL_Quit();
}
