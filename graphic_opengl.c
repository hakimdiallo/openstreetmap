#include "graphic_opengl.h"

void draw_line(my_way *way, GHashTable *nodes, GLfloat width, GLdouble depth, GLubyte r, GLubyte g, GLubyte b){
  glColor3ub(r,g,b); //Couleur de la ligne
  glLineWidth( width );//Change la largeur d'une ligne
  glBegin(GL_LINE_STRIP);//option pour relier les sommets du premier au dernier
    int size = g_slist_length(way->nodes);
    int i;
    for (i = 0; i < size - 1; i++){
      my_node *node1 = g_hash_table_lookup(nodes, g_slist_nth_data(way->nodes, i));
      glVertex3d((GLdouble)(node1->lon),(GLdouble)(node1->lat),depth);
    }
  glEnd();
}

void draw_way(my_way *w, GHashTable *ways, GHashTable *nodes){
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
            draw_line(w,nodes,10,1,254,254,254);
          }
          else if(!strcmp(tag_value,"residential")){
            draw_line(w,nodes,10,1,254,254,254);
          }
          else if(!strcmp(tag_value,"service")){
            draw_line(w,nodes,5,1,254,254,254);
          }
          else if(!strcmp(tag_value,"pedestrian")){
            draw_line(w,nodes,5,1,237,237,237);
          }
          else if(!strcmp(tag_value,"footway") || !strcmp(tag_value,"path")){
            draw_line(w,nodes,2,1,248,147,136);
          }
          else if(!strcmp(tag_value,"motorway_link")){
            draw_line(w,nodes,10,1,233,144,160);
          }
          else if(!strcmp(tag_value,"trunk_link")){
            draw_line(w,nodes,13,1,251,178,154);
          }
          else if(!strcmp(tag_value,"living_street")){
            draw_line(w,nodes,13,1,237,237,237);
          }
          else if(!strcmp(tag_value,"track")){
            draw_line(w,nodes,2,1,172,131,39);
          }
          else if(!strcmp(tag_value,"bus_guideway")){
            draw_line(w,nodes,4,1,100,100,255);
          }
          else if(!strcmp(tag_value,"raceway")){
            draw_line(w,nodes,7,1,255,192,202);
          }
          else if(!strcmp(tag_value,"road")){
            draw_line(w,nodes,2,1,221,221,221);
          }
          else if(!strcmp(tag_value,"bridleway")){
            draw_line(w,nodes,2,1,73,161,72);
          }
          else if(!strcmp(tag_value,"steps")){
            draw_line(w,nodes,5,1,252,119,102);
          }
          else if(!strcmp(tag_value,"cycleway")){
            draw_line(w,nodes,2,1,155,154,245);
          }
        }
    }
}

void draw_ways(GHashTable *hash_ways, GHashTable *hash_nodes){
  GHashTableIter iter;
	gpointer val;
	g_hash_table_iter_init(&iter, hash_ways);
	 while(g_hash_table_iter_next(&iter, NULL, &val)){
		 my_way *way = (my_way *)val;
     draw_way(way,hash_ways,hash_nodes);
    }
}

void rendererMap_opengl(GHashTable *hash_ways, GHashTable *hash_nodes, GHashTable *hash_relations){
  SDL_Window *win = NULL;
  SDL_GLContext contextOpenGL = NULL;
  

  SDL_Init(SDL_INIT_VIDEO);

  // Version d'OpenGL

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	// Double Buffer

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

  win = SDL_CreateWindow("MY OSM RENDERER", SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
  if (win == 0) {
			printf("Erreur lors de la création de la fenêtre %s\n", SDL_GetError());
			SDL_DestroyWindow(win);
      SDL_Quit();
		}

		// Création du contexte OpenGL
	 	contextOpenGL = SDL_GL_CreateContext(win);

		if(contextOpenGL == 0){
			printf("%s\n", SDL_GetError());
			SDL_DestroyWindow(win);
      SDL_Quit();
		}

    //Repère en bas à gauche et mesure de dessin en pixel
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity( );
    gluOrtho2D(0,WIDTH,0,HEIGHT);
    //activation de la profndeur des dessins
    glEnable(GL_DEPTH_TEST);

	printf("draw ...\n");
	int continuer = 1;
  while (continuer) {
      SDL_Event event;
      SDL_WaitEvent(&event);
      switch (event.type) {
      	case SDL_QUIT:
					continuer = 0;
					break;
      }
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    	draw_ways(hash_ways,hash_nodes);

      glFlush();
		 	SDL_GL_SwapWindow(win);
  }
  SDL_GL_DeleteContext(contextOpenGL);
	SDL_DestroyWindow(win);
	SDL_Quit();
}
