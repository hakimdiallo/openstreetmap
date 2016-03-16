#include "osm.h"
#include "string.h"
#include "graphic.h"
#include<SDL.h>
#include <stdlib.h>

my_bounds bn;

int main(int argc, char *argv[]){
	xmlDocPtr doc;
	//if(DEBUG)
		//printf("Parsing file xml...\n");
	if(argc < 2 || argc > 2){
		printf("1 argument manquand: le nom du fichier xml/osm a parser.\n");
		return -1;
	}
	doc = parse_file(argv[1]);
	if( doc == NULL ){
			printf("Something went wrong...\n");
		free_file(doc);
		return -1;
	}

	xmlXPathContextPtr context = get_xpath_contexte(doc);
	// Evaluation de l'expression XPath
	bn = getBoundInformations(context);
	//if( DEBUG )
		//printf("%f %f %f %f\n",bn.minlon,bn.minlat,bn.maxlon,bn.maxlat);
	char *path = "/osm/way";
	xmlXPathObjectPtr obj = getNode_by_xpathExpression(path,context);
	// Manipulation du résultat
	my_way **ways = xpath_parcours(obj,context);
	SDL_Window *win = NULL;
  SDL_Renderer *renderer = NULL;
  //SDL_Texture *bitmapTex = NULL;
  //SDL_Surface *bitmapSurface = NULL;
  int posX = 100, posY = 100, width = WIDTH, height = HEIGHT;

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
	dessiner_ways_bis(ways,obj->nodesetval->nodeNr,renderer);
  while (1) {
      SDL_Event e;
      if (SDL_PollEvent(&e)) {
          if (e.type == SDL_QUIT) {
              break;
          }
      }

      //SDL_RenderClear(renderer);
      //SDL_RenderCopy(renderer, bitmapTex, NULL, NULL);
      //SDL_RenderPresent(renderer);
  }
	free_my_ways(ways,  obj->nodesetval->nodeNr);
	//my_hashmap_node* nodes=stockage_nodes(context);
	//int i=0;
	//printf(" valeur %s\n", get_hashmap_node(nodes, 1321042431) );
  //SDL_DestroyTexture(bitmapTex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
  SDL_Quit();
	xmlXPathFreeObject(obj);
	xmlXPathFreeContext(context);
	xmlFreeDoc(doc);
	return 0;
}
