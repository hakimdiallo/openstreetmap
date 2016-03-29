#include "osm.h"
#include "string.h"
#include "graphic.h"
#include <SDL.h>
#include <stdlib.h>



int main(int argc, char *argv[]){
	//if(DEBUG)
		//printf("Parsing file xml...\n");
	if(argc < 2 || argc > 2){
		printf("1 argument manquand: le nom du fichier xml/osm a parser.\n");
		return -1;
	}
	my_bounds *bound;
	GHashTable *ways;
	GHashTable *nodes;
	nodes = g_hash_table_new_full( g_str_hash, g_str_equal, NULL, g_free);//initialisation de l'hashtable des nodes
	ways = g_hash_table_new_full( g_str_hash, g_str_equal, NULL, g_free);;//initialisation de l'hashtable des ways
	bound = init_my_bounds();
	parse_file_v(ways, nodes, bound, argv[1]);
	SDL_Window *win = NULL;
  SDL_Renderer *renderer = NULL;
  //SDL_Texture *bitmapTex = NULL;
  //SDL_Surface *bitmapSurface = NULL;
  int posX = 100, posY = 100, width = WIDTH, height = HEIGHT;
	/*GHashTableIter iter;
	gpointer key;
	gpointer val;
	int i=0;
	g_hash_table_iter_init(&iter, ways);
	 while(g_hash_table_iter_next(&iter, &key, &val)) {
			 g_print("key\t: %s\t value: %d\n", (char *) key, ((my_way *)val)->count_nodes);
			 i++;
			 printf("%d\n", i);
	 }
	 */
  SDL_Init(SDL_INIT_VIDEO);

  win = SDL_CreateWindow("MY OSM RENDERER", posX, posY, width, height, 0);

  renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	// clear screen with red color
  SDL_SetRenderDrawColor(renderer, 239, 239, 239, 255);
  SDL_RenderClear(renderer);
  //bitmapSurface = SDL_LoadBMP("img/hello.bmp");
  //bitmapTex = SDL_CreateTextureFromSurface(renderer, bitmapSurface);
  //SDL_FreeSurface(bitmapSurface);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
  //SDL_RenderDrawLine(renderer, 0, 0, 200, 500);
	//short s[5] = { 400, 450, 450, 425, 300 };
  //short t[5] = { 400, 410, 450, 425, 500};
  //filledPolygonRGBA(renderer, s, t, 5, 255, 0, 255, 155);
	//SDL_RenderPresent(renderer);
	printf("draw ...\n");
	dessiner_ways(renderer, ways, nodes );
  while (1) {
      SDL_Event e;
      if (SDL_PollEvent(&e)) {
          if (e.type == SDL_QUIT) {
              break;
          }
      }

      //SDL_RenderClear(renderer);
      //SDL_RenderCopy(renderer, bitmapTex, NULL, NULL);
  }
	//free_my_ways(ways);
	//my_hashmap_node* nodes=stockage_nodes(context);
	//int i=0;
	//printf(" valeur %s\n", get_hashmap_node(nodes, 1321042431) );
  //SDL_DestroyTexture(bitmapTex);
	//free_my_ways(ways);
	//free_my_nodes(nodes);
	//free_my_bound(bound);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
  SDL_Quit();
	return 0;
}
