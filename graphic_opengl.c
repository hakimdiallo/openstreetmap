#include "graphic_opengl.h"

int coast_line = 0;
int cameraX = 0;
int cameraY = 0;
float zoom = 1.0;

void draw_line(my_way *way, GHashTable *nodes, GLfloat width, GLdouble depth, GLubyte r, GLubyte g, GLubyte b){
  glColor3ub(r,g,b); //Couleur de la ligne
  glLineWidth( width );//Change la largeur d'une ligne
  glBegin(GL_LINE_STRIP);//option pour relier les sommets du premier au dernier
    int size = g_slist_length(way->nodes);
    int i;
    for (i = 0; i < size; i++){
      my_node *node1 = g_hash_table_lookup(nodes, g_slist_nth_data(way->nodes, i));
      glVertex3d((GLdouble)(node1->lon),(GLdouble)(node1->lat),depth);
    }
  glEnd();
}

void draw_line_stipple(my_way *way, GHashTable *nodes, GLfloat width, GLdouble depth, GLubyte r, GLubyte g, GLubyte b){
  glColor3ub(r,g,b); //Couleur de la ligne
  glLineWidth( width );//Change la largeur d'une ligne
  glLineStipple(1,1);
  glBegin(GL_LINE_STRIP);//option pour relier les sommets du premier au dernier
    int size = g_slist_length(way->nodes);
    int i;
    for (i = 0; i < size; i++){
      my_node *node1 = g_hash_table_lookup(nodes, g_slist_nth_data(way->nodes, i));
      glVertex3d((GLdouble)(node1->lon),(GLdouble)(node1->lat),depth);
    }
  glEnd();
}


void draw_polygon(my_way *way, GHashTable *nodes, GLdouble depth, GLubyte r, GLubyte g, GLubyte b){
  glColor3ub(r,g,b); //Couleur de la ligne
  glBegin(GL_POLYGON);
    int size = g_slist_length(way->nodes);
    int i;
    for (i = 0; i < size; i++){
      my_node *node1 = g_hash_table_lookup(nodes, g_slist_nth_data(way->nodes, i));
      glVertex3d((GLdouble)(node1->lon),(GLdouble)(node1->lat),depth);
    }
  glEnd();
}



void draw_way(my_way *w, GHashTable *ways, GHashTable *nodes){
    if ( w == NULL ) {
      return;
    }
    if( w->tag == NULL || g_hash_table_size(w->tag) == 0 ||
        (g_hash_table_size(w->tag) == 1 && g_hash_table_lookup(w->tag,(const char *)"source") != NULL) ) {
      draw_polygon(w,nodes,INNER_DEPTH,221, 221, 221);
      draw_line(w,nodes,2,INNER_DEPTH,168, 146, 162);
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
            draw_line(w,nodes,9,HIGHWAY_DEPTH,233,144,160);
          }
          else if(!strcmp(tag_value,"trunk")){
            draw_line(w,nodes,9,HIGHWAY_DEPTH,251,178,154);
          }
          else if(!strcmp(tag_value,"primary") || !strcmp(tag_value,"primary_link")){
            draw_line(w,nodes,9,HIGHWAY_DEPTH,236,152,154);
          }
          else if(!strcmp(tag_value,"secondary") || !strcmp(tag_value,"secondary_link")){
            draw_line(w,nodes,9,HIGHWAY_DEPTH,254,215,165);
          }
          else if(!strcmp(tag_value,"tertiary") || !strcmp(tag_value,"tertiary_link")){
            draw_line(w,nodes,9,HIGHWAY_DEPTH,255,255,179);
            //draw_line(ways[i],15,0,254,254);
          }
          else if(!strcmp(tag_value,"unclassified")){
            draw_line(w,nodes,9,HIGHWAY_DEPTH,254,254,254);
          }
          else if(!strcmp(tag_value,"residential")){
            draw_line(w,nodes,9,HIGHWAY_DEPTH,254,254,254);
          }
          else if(!strcmp(tag_value,"service")){
            draw_line(w,nodes,5,HIGHWAY_DEPTH,254,254,254);
          }
          else if(!strcmp(tag_value,"pedestrian")){
            draw_line(w,nodes,5,HIGHWAY_DEPTH,237,237,237);
          }
          else if(!strcmp(tag_value,"footway") || !strcmp(tag_value,"path")){
            draw_line(w,nodes,2,HIGHWAY_DEPTH,248,147,136);
          }
          else if(!strcmp(tag_value,"motorway_link")){
            draw_line(w,nodes,9,HIGHWAY_DEPTH,233,144,160);
          }
          else if(!strcmp(tag_value,"trunk_link")){
            draw_line(w,nodes,9,HIGHWAY_DEPTH,251,178,154);
          }
          else if(!strcmp(tag_value,"living_street")){
            draw_line(w,nodes,9,HIGHWAY_DEPTH,237,237,237);
          }
          else if(!strcmp(tag_value,"track")){
            draw_line(w,nodes,2,HIGHWAY_DEPTH,172,131,39);
          }
          else if(!strcmp(tag_value,"bus_guideway")){
            draw_line(w,nodes,4,HIGHWAY_DEPTH,100,100,255);
          }
          else if(!strcmp(tag_value,"raceway")){
            draw_line(w,nodes,7,HIGHWAY_DEPTH,255,192,202);
          }
          else if(!strcmp(tag_value,"road")){
            draw_line(w,nodes,2,HIGHWAY_DEPTH,221,221,221);
          }
          else if(!strcmp(tag_value,"bridleway")){
            draw_line(w,nodes,2,HIGHWAY_DEPTH,73,161,72);
          }
          else if(!strcmp(tag_value,"steps")){
            draw_line(w,nodes,5,HIGHWAY_DEPTH,252,119,102);
          }
          else if(!strcmp(tag_value,"cycleway")){
            draw_line(w,nodes,2,HIGHWAY_DEPTH,155,154,245);
          }
          else{
            printf("highway: %s\n",tag_value);
          }
        }
        else if(!strcmp(tag_key,"building")){
          if(!strcmp(tag_key,"building")){
            draw_polygon(w,nodes,BULDING_DEPTH, 191, 174, 174);
            draw_line(w,nodes,2,BULDING_DEPTH,168, 146, 162);
            //polygonRGBA( tab_x, tab_y, g_slist_length(w->nodes), 168, 146, 162, 255);
          }
        }
        else if(!strcmp(tag_key,"waterway")){
          if(!strcmp(tag_value,"river")){
            draw_line(w,nodes,10,WATER_DEPTH,180,190,209);
          }
          else if(!strcmp(tag_value,"riverbank")){
            draw_polygon(w,nodes,WATER_DEPTH,181,208,208);
            //draw_line(ways[i],50,180,208,209);
          }
          else if(!strcmp(tag_value,"stream")){
            draw_line(w,nodes,2,WATER_DEPTH,180,208,209);
          }
        }
        else if(!strcmp(tag_key,"natural")){
          if(!strcmp(tag_value,"water")){
            draw_polygon(w,nodes,HIGHWAY_DEPTH,180, 208, 209);
            draw_line(w,nodes,2,HIGHWAY_DEPTH,175, 175, 175);
            //polygonRGBA( tab_x, tab_y, g_slist_length(w->nodes), 175, 175, 175, 255);
          }
          else if(!strcmp(tag_value,"coastline")){
            if ( !coast_line) {
              //SDL_SetRenderDrawColor( 180, 208, 209, 255);
              //SDL_RenderClear(renderer);
              coast_line = 1;
            }
            draw_polygon(w,nodes,WATER_DEPTH, 221, 221, 221);
          }
        }
        else if(!strcmp(tag_key,"landuse") || !strcmp(tag_key,"leisure")){
          if(!strcmp(tag_value,"grass")){
            //draw_polygon( tab_x, tab_y, g_slist_length(w->nodes), 207, 237, 165, 255);
            //polygonRGBA( tab_x, tab_y, g_slist_length(w->nodes), 175, 175, 175, 255);
          }
          else if(!strcmp(tag_value,"forest")){
            //draw_polygon( tab_x, tab_y, g_slist_length(w->nodes), 157, 202, 138, 255);
            //polygonRGBA( tab_x, tab_y, g_slist_length(w->nodes), 175, 175, 175, 255);
          }
          else if(!strcmp(tag_value,"park")){
            //draw_polygon( tab_x, tab_y, g_slist_length(w->nodes), 205, 247, 201, 255);
            //polygonRGBA( tab_x, tab_y, g_slist_length(w->nodes), 175, 175, 175, 255);
          }
          else if(!strcmp(tag_value,"garden")){
            //draw_polygon( tab_x, tab_y, g_slist_length(w->nodes), 207, 236, 168, 255);
            //polygonRGBA( tab_x, tab_y, g_slist_length(w->nodes), 175, 175, 175, 255);
          }
          else if(!strcmp(tag_value,"pitch")){
            //draw_polygon( tab_x, tab_y, g_slist_length(w->nodes), 138, 211, 175, 255);
          }
        }
        else if(!strcmp(tag_key,"area")){
          if(!strcmp(tag_value,"yes")){
            //draw_polygon( tab_x, tab_y, g_slist_length(w->nodes), 237, 237, 237, 255);
            //polygonRGBA( tab_x, tab_y, g_slist_length(w->nodes), 175, 175, 175, 255);;
          }else{
            printf("area: %s\n",tag_value);
          }
        }
    }
    //w->drawn = 1;
    //g_hash_table_insert(ways,&(w->at.id),w);
}

void draw_ways(GHashTable *hash_ways, GHashTable *hash_nodes){
  GHashTableIter iter;
	gpointer val;
	g_hash_table_iter_init(&iter, hash_ways);
	 while(g_hash_table_iter_next(&iter, NULL, &val)){
     draw_way((my_way *)val,hash_ways,hash_nodes);
  }
}

void init_opengl(){
  // Version d'OpenGL
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	// Double Buffer rt profondeur
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

  //Repère en bas au centre et mesure de dessin en pixel
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
  glPushMatrix();
  gluOrtho2D(-WIDTH/2,WIDTH/2,-HEIGHT/2,HEIGHT/2);

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  //activation de la profondeur des dessins
  glEnable(GL_DEPTH_TEST);
  //activation des pointillés
  glEnable(GL_LINE_STIPPLE );
  glClearColor(221%255,221%255,221%255,0.0);
}


void rendererMap_opengl(GHashTable *hash_ways, GHashTable *hash_nodes, GHashTable *hash_relations){
  SDL_Window *win = NULL;
  SDL_GLContext contextOpenGL = NULL;
  SDL_Init(SDL_INIT_VIDEO);

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


  int x=0, y=0;
  int oldEcranW ,  oldEcranH, ecranW, ecranH;
  SDL_GetWindowSize(win, &oldEcranW, &oldEcranH);

  init_opengl();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  draw_ways(hash_ways,hash_nodes);
  glFlush();
  SDL_GL_SwapWindow(win);

  int continuer = 1;
  while (continuer) {
  	SDL_GetWindowSize(win, &ecranW, &ecranH); //on recupère la largeur et la hauteur de la fenêtre
    if((ecranW != oldEcranW) || (ecranH != oldEcranH) ){
      glMatrixMode( GL_PROJECTION );
      glPopMatrix();
      glLoadIdentity( );
      gluOrtho2D(-ecranW/2,ecranW/2,-ecranH/2,ecranH/2);
      glViewport( 0.f, 0.f, ecranW, ecranH );
      glPushMatrix();
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    	draw_ways(hash_ways,hash_nodes);
      glFlush();
      SDL_GL_SwapWindow(win);
      oldEcranW  = ecranW;  oldEcranH = ecranH;
    }
      //Evenement sdl
      if(SDL_QuitRequested()){
        continuer = 0;
        break;
      }

      SDL_PumpEvents();
      //Scrooling avec un clic et un déplacement de la souris
      if(SDL_GetRelativeMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT) & ((x != 0) || (y != 0))){
        //Initialize Modelview Matrix
        cameraX += x;
        cameraY -= y;
        glMatrixMode( GL_MODELVIEW );
        glPopMatrix();
        glLoadIdentity();
        glScalef( zoom, zoom, 0 );
        glTranslatef( cameraX , cameraY, 0.f );
        glPushMatrix();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      	draw_ways(hash_ways,hash_nodes);
        glFlush();
  		 	SDL_GL_SwapWindow(win);
        printf("Le bouton gauche est appuyé\n");
        printf("camerax :%d cameray: %d\n", cameraX, cameraY);
      }

      //zoom / dezoom avec le clavier
      const Uint8 *state = SDL_GetKeyboardState(NULL);
      //dezoom avec touche -
      if (state[SDL_SCANCODE_KP_PLUS] ) {
        zoom += ZOOM;
        if (zoom > MAX_ZOOM) {
          zoom = MAX_ZOOM;
        }
        printf("%f\n", zoom);
        glMatrixMode( GL_MODELVIEW );
        glPopMatrix();
        glLoadIdentity();
        glTranslatef( cameraX*zoom, cameraY*zoom, 0.f );
        glScalef( zoom, zoom, 0 );
        glPushMatrix();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      	draw_ways(hash_ways,hash_nodes);
        glFlush();
  		 	SDL_GL_SwapWindow(win);
      }
      //zoom avec touche +
      if (state[SDL_SCANCODE_KP_MINUS] ) {
        zoom -= ZOOM;
        if(zoom < 0)
          zoom = -zoom;
        if(zoom < MIN_ZOOM)
          zoom = MIN_ZOOM;
        printf("%f\n", zoom);
        glMatrixMode( GL_MODELVIEW );
        glPopMatrix();
        glLoadIdentity();
        glTranslatef( cameraX*zoom, cameraY*zoom, 0.f );
        glScalef( zoom, zoom, 0 );
        glPushMatrix();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      	draw_ways( hash_ways,hash_nodes);
        glFlush();
  		 	SDL_GL_SwapWindow(win);
      }
      //LAa touche home poutr revenir à la position initiale
      if (state[SDL_SCANCODE_HOME] ) {
        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();
        glPushMatrix();
        zoom = 1;
        cameraX = 0;
        cameraY = 0;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      	draw_ways( hash_ways,hash_nodes);
        glFlush();
  		 	SDL_GL_SwapWindow(win);
      }

  }
  glDisable(GL_LINE_STIPPLE);
	glDisable(GL_DEPTH_TEST);
  SDL_GL_DeleteContext(contextOpenGL);
	SDL_DestroyWindow(win);
	SDL_Quit();
}
