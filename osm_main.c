#include "osm.h"
#include "string.h"
#include "graphic.h"
#include<SDL.h>

my_bounds bn;

int main(int argc, char *argv[]){
	xmlDocPtr doc;
	if(DEBUG)
		printf("Parsing file xml...\n");
	if(argc < 2 || argc > 2){
		printf("1 argument manquand: le nom du fichier xml/osm a parser.\n");
		return -1;
	}
	doc = parse_file(argv[1]);
	if( doc == NULL ){
		if(DEBUG)
			printf("Something went wrong...\n");
		free_file(doc);
		return -1;
	}

	xmlXPathContextPtr context = get_xpath_contexte(doc);
	// Evaluation de l'expression XPath
	bn = getBoundInformations(context);
	char *path = "/osm/way";
	xmlXPathObjectPtr obj = getNode_by_xpathExpression(path,context);
	// Manipulation du résultat

	SDL_Window *win = NULL;
  SDL_Renderer *renderer = NULL;
  //SDL_Texture *bitmapTex = NULL;
  //SDL_Surface *bitmapSurface = NULL;
  int posX = 100, posY = 100, width = WIDTH, height = HEIGHT;

  SDL_Init(SDL_INIT_VIDEO);

  win = SDL_CreateWindow("MY OSM RENDERER", posX, posY, width, height, 0);

  renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	// clear screen with red color
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
  //bitmapSurface = SDL_LoadBMP("img/hello.bmp");
  //bitmapTex = SDL_CreateTextureFromSurface(renderer, bitmapSurface);
  //SDL_FreeSurface(bitmapSurface);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
  //SDL_RenderDrawLine(renderer, 0, 0, 200, 500);
	//SDL_RenderPresent(renderer);
	xpath_parcours(obj,context,renderer);
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

  //SDL_DestroyTexture(bitmapTex);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(win);

  SDL_Quit();
	xmlXPathFreeObject(obj);
	return 0;
}
