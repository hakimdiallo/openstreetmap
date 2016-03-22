#include "graphic.h"

SDL_Point *get_tab_point_nodes(my_way *way){
  SDL_Point *points = NULL;
  points = malloc(way->count_nodes * sizeof(SDL_Point));
  int i;
  for (i = 0;i < way->count_nodes;i++) {
    points[i].x = calcul_coor_x(way->nodes[i].lon);
    points[i].y = calcul_coor_y(way->nodes[i].lat);
  }
  return points;
}

short *get_tab_x(my_way *way){
  int i;
  short *tab = malloc(sizeof(short)* way->count_nodes);
  for (i = 0;i < way->count_nodes;i++) {
    tab[i] = (short)calcul_coor_x(way->nodes[i].lon);
  }
  return tab;
}

short *get_tab_y(my_way *way){
  int i;
  short *tab = malloc(sizeof(short)* way->count_nodes);
  for (i = 0;i < way->count_nodes;i++) {
    tab[i] = (short)calcul_coor_y(way->nodes[i].lat);
  }
  return tab;
}

void dessiner_trait_noeuds(my_node n1, my_node n2, SDL_Renderer *renderer){
  int x1 = calcul_coor_x(n1.lon);
  int y1 = calcul_coor_y(n1.lat);
  int x2 = calcul_coor_x(n2.lon);
  int y2 = calcul_coor_y(n2.lat);
  //if(DEBUG)
    //printf("x1 %d y1 %d x2 %d y2 %d\n", x1, y1, x2, y2);
  SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
	SDL_RenderPresent(renderer);
}

void afficher(xmlNodePtr noeud) {
        if (noeud->type == XML_ELEMENT_NODE ) {
    	    xmlChar *id=xmlGetProp(noeud,(const xmlChar *)"id");//retourne valeur de l'attribut id du noeud
    	    xmlChar *visible=xmlGetProp(noeud,(const xmlChar *)"visible");
    	    xmlChar *k=xmlGetProp(noeud,(const xmlChar *)"k");
    	    xmlChar *v=xmlGetProp(noeud,(const xmlChar *)"v");
          if(DEBUG){
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
          }
    	    xmlFree(id);
    	    xmlFree(visible);
    	    xmlFree(k);
    	    xmlFree(v);
        }
}
void dessiner_way(my_way way, SDL_Renderer *renderer){
  int i;
  for (i = 0; i < way.count_nodes-1; i++) {
    dessiner_trait_noeuds(way.nodes[i],way.nodes[i+1],renderer);
  }
}
/*
void dessiner_way_bis(my_way way, SDL_Renderer *renderer){
  SDL_Point *pts = get_tab_point_nodes(way);
  SDL_RenderDrawLines(renderer,pts,way.count_nodes);
	SDL_RenderPresent(renderer);
}
*/
void dessiner_ways(my_way **ways, int count, SDL_Renderer *renderer){
  int i;
  //if( DEBUG )
    //printf("nb %d\n",count );
  for (i = 0; i < count; i++) {
    SDL_Point *pts = get_tab_point_nodes(ways[i]);
    SDL_RenderDrawLines(renderer,pts,ways[i]->count_nodes);
    SDL_RenderPresent(renderer);
  }
}

void draw_line_with_width(SDL_Renderer *renderer, my_way *way, uint8_t w, uint8_t r, uint8_t g, uint8_t b){
  int i;
  for (i = 0; i < way->count_nodes-1; i++) {
    short x1 = (short)calcul_coor_x(way->nodes[i].lon);
    short y1 = (short)calcul_coor_y(way->nodes[i].lat);
    short x2 = (short)calcul_coor_x(way->nodes[i+1].lon);
    short y2 = (short)calcul_coor_y(way->nodes[i+1].lat);
    thickLineRGBA(renderer,x1,y1,x2,y2,w,r,g,b,255);
  }
}

void draw_line_points(SDL_Renderer *renderer, my_way *way, uint8_t r, uint8_t g, uint8_t b){
  SDL_Point *pts = get_tab_point_nodes(way);
  SDL_SetRenderDrawColor(renderer,r,g,b,255);
  SDL_RenderDrawPoints(renderer,pts,way->count_nodes);
}

void dessiner_ways_bis(my_way **ways, int count, SDL_Renderer *renderer){
  int i;
  //if( DEBUG )
    //printf("nb %d\n",count );
  for (i = 0; i < count; i++) {
    //char *v = parcours_tag(ways[i]->tag, ways[i]->count_tag);
    if(ways[i]->count_tag > 0){
      int j;
      for (j = 0; j < ways[i]->count_tag; j++) {
        char *v = NULL;
        if(!strcmp(ways[i]->tag[j].key,"highway")){
          v = strdup(ways[i]->tag[j].value);
          if(!strcmp(v,"motorway")){
            draw_line_with_width(renderer,ways[i],18,233,144,160);
          }
          else if(!strcmp(v,"trunk")){
            draw_line_with_width(renderer,ways[i],18,251,178,154);
          }
          else if(!strcmp(v,"primary") || !strcmp(v,"primary_link")){
            draw_line_with_width(renderer,ways[i],15,236,152,154);
          }
          else if(!strcmp(v,"secondary") || !strcmp(v,"secondary_link")){
            draw_line_with_width(renderer,ways[i],15,254,215,165);
          }
          else if(!strcmp(v,"tertiary") || !strcmp(v,"tertiary_link")){
            draw_line_with_width(renderer,ways[i],15,255,255,179);
            //draw_line_with_width(renderer,ways[i],15,0,254,254);
          }
          else if(!strcmp(v,"unclassified")){
            draw_line_with_width(renderer,ways[i],10,254,254,254);
          }
          else if(!strcmp(v,"residential")){
            draw_line_with_width(renderer,ways[i],10,254,254,254);
          }
          else if(!strcmp(v,"service")){
            draw_line_with_width(renderer,ways[i],7,254,254,254);
          }
          else if(!strcmp(v,"pedestrian")){
            draw_line_with_width(renderer,ways[i],5,237,237,237);
          }
          else if(!strcmp(v,"footway") || !strcmp(v,"path")){
            draw_line_with_width(renderer,ways[i],2,248,147,136);
          }
          else if(!strcmp(v,"motorway_link")){
            draw_line_with_width(renderer,ways[i],10,233,144,160);
          }
          else if(!strcmp(v,"trunk_link")){
            draw_line_with_width(renderer,ways[i],15,251,178,154);
          }
          else if(!strcmp(v,"living_street")){
            draw_line_with_width(renderer,ways[i],15,237,237,237);
          }
          else if(!strcmp(v,"track")){
            draw_line_with_width(renderer,ways[i],2,172,131,39);
          }
          else if(!strcmp(v,"bus_guideway")){
            draw_line_with_width(renderer,ways[i],4,100,100,255);
          }
          else if(!strcmp(v,"raceway")){
            draw_line_with_width(renderer,ways[i],7,255,192,202);
          }
          else if(!strcmp(v,"road")){
            draw_line_with_width(renderer,ways[i],2,221,221,221);
          }
          else if(!strcmp(v,"bridleway")){
            draw_line_with_width(renderer,ways[i],2,73,161,72);
          }
          else if(!strcmp(v,"steps")){
            draw_line_with_width(renderer,ways[i],5,252,119,102);
          }
          else if(!strcmp(v,"cycleway")){
            draw_line_with_width(renderer,ways[i],2,155,154,245);
          }
          else{
            printf("highway: %s\n",v );
          }
        }
        else if(!strcmp(ways[i]->tag[j].key,"building")){
          v = strdup(ways[i]->tag[j].key);
          if(!strcmp(v,"building")){
            short *tab_x = get_tab_x(ways[i]);
            short *tab_y = get_tab_y(ways[i]);
            filledPolygonRGBA(renderer, tab_x, tab_y, ways[i]->count_nodes, 191, 174, 174, 255);
            //polygonRGBA(renderer, tab_x, tab_y, ways[i]->count_nodes, 168, 146, 162, 255);
          }
        }
        else if(!strcmp(ways[i]->tag[j].key,"waterway")){
          v = strdup(ways[i]->tag[j].value);
          if(!strcmp(v,"river")){
            draw_line_with_width(renderer,ways[i],10,180,190,209);
          }
          else if(!strcmp(v,"riverbank")){
            short *tab_x = get_tab_x(ways[i]);
            short *tab_y = get_tab_y(ways[i]);
            //filledPolygonRGBA(renderer, tab_x, tab_y, ways[i]->count_nodes, 181,208,208, 255);
            //draw_line_with_width(renderer,ways[i],50,180,208,209);
          }
          else if(!strcmp(v,"stream")){
            draw_line_with_width(renderer,ways[i],2,180,208,209);
          }
        }
        else if(!strcmp(ways[i]->tag[j].key,"natural")){
          v = strdup(ways[i]->tag[j].value);
          if(!strcmp(v,"water")){
            short *tab_x = get_tab_x(ways[i]);
            short *tab_y = get_tab_y(ways[i]);
            filledPolygonRGBA(renderer, tab_x, tab_y, ways[i]->count_nodes, 180, 208, 209, 255);
          }
          else if(!strcmp(v,"coastline")){
            //short *tab_x = get_tab_x(ways[i]);
            //short *tab_y = get_tab_y(ways[i]);
            //filledPolygonRGBA(renderer, tab_x, tab_y, ways[i]->count_nodes, 180, 208, 209, 255);
          }
        }
        else if(!strcmp(ways[i]->tag[j].key,"landuse") || !strcmp(ways[i]->tag[j].key,"leisure")){
          v = strdup(ways[i]->tag[j].value);
          if(!strcmp(v,"grass")){
            short *tab_x = get_tab_x(ways[i]);
            short *tab_y = get_tab_y(ways[i]);
            filledPolygonRGBA(renderer, tab_x, tab_y, ways[i]->count_nodes, 207, 237, 165, 255);
          }
          else if(!strcmp(v,"forest")){
            short *tab_x = get_tab_x(ways[i]);
            short *tab_y = get_tab_y(ways[i]);
            filledPolygonRGBA(renderer, tab_x, tab_y, ways[i]->count_nodes, 157, 202, 138, 255);
          }
          else if(!strcmp(v,"park")){
            short *tab_x = get_tab_x(ways[i]);
            short *tab_y = get_tab_y(ways[i]);
            filledPolygonRGBA(renderer, tab_x, tab_y, ways[i]->count_nodes, 205, 247, 201, 255);
          }
          else if(!strcmp(v,"garden")){
            short *tab_x = get_tab_x(ways[i]);
            short *tab_y = get_tab_y(ways[i]);
            filledPolygonRGBA(renderer, tab_x, tab_y, ways[i]->count_nodes, 207, 236, 168, 255);
          }
          else if(!strcmp(v,"pitch")){
            short *tab_x = get_tab_x(ways[i]);
            short *tab_y = get_tab_y(ways[i]);
            filledPolygonRGBA(renderer, tab_x, tab_y, ways[i]->count_nodes, 138, 211, 175, 255);
          }
        }
        else if(!strcmp(ways[i]->tag[j].key,"area")){
          v = strdup(ways[i]->tag[j].value);
          if(!strcmp(v,"yes")){
            short *tab_x = get_tab_x(ways[i]);
            short *tab_y = get_tab_y(ways[i]);
            filledPolygonRGBA(renderer, tab_x, tab_y, ways[i]->count_nodes, 237, 237, 237, 255);
          }else{
            printf("%s\n",ways[i]->tag[j].value);
          }
        }
        else if(!strcmp(ways[i]->tag[j].key,"barrier")){
          v = strdup(ways[i]->tag[j].value);
          if(!strcmp(v,"fence")){
            //short *tab_x = get_tab_x(ways[i]);
            //short *tab_y = get_tab_y(ways[i]);
            //polygonRGBA(renderer, tab_x, tab_y, ways[i]->count_nodes, 173,171,168, 255);
            draw_line_with_width(renderer,ways[i],1,173,171,168);
          }
        }
        else if(!strcmp(ways[i]->tag[j].key,"source")){
          //v = strdup(ways[i]->tag[j].value);
            if (ways[i]->count_tag == 1) {
              short *tab_x = get_tab_x(ways[i]);
              short *tab_y = get_tab_y(ways[i]);
              filledPolygonRGBA(renderer, tab_x, tab_y, ways[i]->count_nodes, 221, 221, 221, 255);
            }
            draw_line_with_width(renderer,ways[i],1,168, 146, 162);
        }

        else{
          //printf("%s - %s\n",ways[i]->tag[j].key,ways[i]->tag[j].value);
        }
      }
    }
    else{
      short *tab_x = get_tab_x(ways[i]);
      short *tab_y = get_tab_y(ways[i]);
      //filledPolygonRGBA(renderer, tab_x, tab_y, ways[i]->count_nodes, 191, 174, 174, 255);
      filledPolygonRGBA(renderer, tab_x, tab_y, ways[i]->count_nodes, 221, 221, 221, 255);
    }

  }
  SDL_RenderPresent(renderer);
}

char *parcours_tag(my_tag *tag, int size){
  int i;
  char *val = NULL;
  for (i = 0; i < size; i++) {
    if(!strcmp(tag[i].key,"highway")){
      val = strdup(tag[i].value);
      return val;
    }
    else if(!strcmp(tag[i].key,"building")){
      val = strdup(tag[i].key);
      return val;
    }
    else if(!strcmp(tag[i].key,"waterway")){
      val = strdup(tag[i].value);
      return val;
    }
    else if(!strcmp(tag[i].key,"natural")){
      val = strdup(tag[i].value);
      return val;
    }
    else if(!strcmp(tag[i].key,"landuse") || !strcmp(tag[i].key,"leisure")){
      val = strdup(tag[i].value);
      return val;
    }
    else if(!strcmp(tag[i].key,"area")){
      val = strdup(tag[i].value);
      return val;
    }
    else{
      //printf("%s - %s\n", tag[i].key, tag[i].value);
    }
  }
  return val;
}
