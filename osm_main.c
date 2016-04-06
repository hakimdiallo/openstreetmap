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
	my_bounds *hash_bound;
	GHashTable *hash_ways;
	GHashTable *hash_nodes;
	GHashTable *hash_relations;
	hash_relations = g_hash_table_new_full( g_str_hash, g_str_equal, NULL, g_free);
	hash_nodes = g_hash_table_new_full( g_str_hash, g_str_equal, NULL, g_free);//initialisation de l'hashtable des nodes
	hash_ways = g_hash_table_new_full( g_str_hash, g_str_equal, NULL, g_free);//initialisation de l'hashtable des ways
	hash_bound = init_my_bounds();
	parse_file_v(hash_relations, hash_ways, hash_nodes, hash_bound, argv[1]);
	SDL_Window *win = NULL;
  SDL_Renderer *renderer = NULL;

  SDL_Init(SDL_INIT_VIDEO);

  win = SDL_CreateWindow("MY OSM RENDERER", SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED, WIDTH+100, HEIGHT+100, SDL_WINDOW_RESIZABLE);

  renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,WIDTH,HEIGHT);
	//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // permet d'obtenir les redimensionnements plus doux.
	SDL_SetRenderTarget(renderer, texture); //on modifie la texture
	SDL_SetRenderDrawColor(renderer, 239, 239, 239, 255);
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
      }
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer,texture,NULL,&position);
			SDL_RenderPresent(renderer);
  }
/*
	free_my_ways(ways);
	free_my_nodes(nodes);
	free_my_bound(bound);*/
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
  SDL_Quit();
	return 0;
}
