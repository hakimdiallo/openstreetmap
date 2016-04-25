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
  glEnable(GL_LINE_STIPPLE);
  glColor3ub(r,g,b); //Couleur de la ligne
  glLineWidth( width );//Change la largeur d'une ligne
  glLineStipple(1,0x5555);
  glBegin(GL_LINE_STRIP);//option pour relier les sommets du premier au dernier
    int size = g_slist_length(way->nodes);
    int i;
    for (i = 0; i < size; i++){
      my_node *node1 = g_hash_table_lookup(nodes, g_slist_nth_data(way->nodes, i));
      glVertex3d((GLdouble)(node1->lon),(GLdouble)(node1->lat),depth);
    }
  glEnd();
  glDisable(GL_LINE_STIPPLE);
}

void draw_polygon(my_way *way, GHashTable *nodes, GLdouble depth, GLubyte r, GLubyte g, GLubyte b){
  int size = g_slist_length(way->nodes);
  GLdouble **data1 = malloc(sizeof(GLdouble *)*size);
  int i;
  // Création du tesselator
	GLUtesselator * tobj1 = gluNewTess();
	// Définition des fcts callback
  gluTessCallback(tobj1, GLU_TESS_BEGIN, (_GLUfuncptr)glBegin);
  gluTessCallback(tobj1, GLU_TESS_VERTEX,  (_GLUfuncptr)glVertex3dv);
  gluTessCallback(tobj1, GLU_TESS_END, (_GLUfuncptr)glEnd);
  glColor3ub(r,g,b); //Couleur du polygone
  gluTessBeginPolygon(tobj1, NULL);
		gluTessBeginContour(tobj1);
      for (i = 0; i < size; i++){
        my_node *node1 = g_hash_table_lookup(nodes, g_slist_nth_data(way->nodes, i));
        data1[i] = malloc(sizeof(GLdouble)*3);
        data1[i][0] = (GLdouble)(node1->lon);
        data1[i][1] = (GLdouble)(node1->lat);
        data1[i][2] = depth;
        gluTessVertex(tobj1, data1[i], data1[i]);
      }
		gluTessEndContour(tobj1);
  gluTessEndPolygon(tobj1);
  gluDeleteTess(tobj1);
  for (i = 0; i < size; i++){
    free(data1[i]);
  }
  free(data1);
}

void write_name(my_way *way, GHashTable *nodes, char *name){
  glColor3ub(255,0,0);
  int count = g_slist_length(way->nodes);
  int i;
  for (i = 0; i < count; i+=2){
    my_node *node = g_hash_table_lookup(nodes,g_slist_nth_data(way->nodes,i));
    glRasterPos3d(node->lon,node->lat,1.0f);
    glutBitmapString(GLUT_BITMAP_8_BY_13, name);
  }
}

void draw_way(my_way *w, GHashTable *ways, GHashTable *nodes){
    if ( w == NULL ) {
      return;
    }
    if( w->tag == NULL || g_hash_table_size(w->tag) == 0 ||
        (g_hash_table_size(w->tag) == 1 && g_hash_table_lookup(w->tag,(const char *)"source") != NULL) ) {
      if (!coast_line) {
        draw_polygon(w,nodes,INNER_DEPTH,221, 221, 221);
        draw_line(w,nodes,CONTOUR_WIDTH,INNER_DEPTH,168, 146, 162);
        w->drawn = 1;
        g_hash_table_insert(ways,&(w->at.id),w);
        return;
      }
    }
    GHashTableIter iter2;
    gpointer key;
    gpointer value;
    g_hash_table_iter_init(&iter2, w->tag);
    while (g_hash_table_iter_next(&iter2, &key, &value)) {
      char *tag_key = (char *)key;
      char *tag_value = (char *)value;
      if(!strcmp(tag_key,"highway")){
          if(!strcmp(tag_value,"motorway") || !strcmp(tag_value,"motorway_link")){
            draw_line(w,nodes,HIGHWAY_WIDTH,HIGHWAY_DEPTH_SND,233,144,160);
          }
          else if(!strcmp(tag_value,"trunk")){
            draw_line(w,nodes,HIGHWAY_WIDTH,HIGHWAY_DEPTH_SND,251,178,154);
          }
          else if(!strcmp(tag_value,"primary") || !strcmp(tag_value,"primary_link")){
            draw_line(w,nodes,HIGHWAY_WIDTH,HIGHWAY_DEPTH_SND,253,215,161);
          }
          else if(!strcmp(tag_value,"secondary") || !strcmp(tag_value,"secondary_link")){
            draw_line(w,nodes,HIGHWAY_WIDTH,HIGHWAY_DEPTH_SND,246,250,187);
          }
          else if(!strcmp(tag_value,"tertiary") || !strcmp(tag_value,"tertiary_link")){
            draw_line(w,nodes,HIGHWAY_WIDTH,HIGHWAY_DEPTH_SND,255,255,179);
            //draw_line(ways[i],15,0,254,254);
          }
          else if(!strcmp(tag_value,"unclassified")){
            draw_line(w,nodes,HIGHWAY_WIDTH,HIGHWAY_DEPTH,254,254,254);
          }
          else if(!strcmp(tag_value,"residential")){
            draw_line(w,nodes,HIGHWAY_WIDTH,HIGHWAY_DEPTH,254,254,254);
          }
          else if(!strcmp(tag_value,"service")){
            draw_line(w,nodes,SERVICE_WIDTH,HIGHWAY_DEPTH,254,254,254);
          }
          else if(!strcmp(tag_value,"pedestrian")){
            draw_line(w,nodes,PEDEST_WIDTH,PEDEST_DEPTH,237,237,237);
          }
          else if(!strcmp(tag_value,"footway") || !strcmp(tag_value,"path")){
            draw_line_stipple(w,nodes,FOOTWAY_WIDTH,STEP_WAY_DEPTH,248,155,144);
          }
          else if(!strcmp(tag_value,"trunk_link")){
            draw_line(w,nodes,HIGHWAY_WIDTH,HIGHWAY_DEPTH_SND,251,178,154);
          }
          else if(!strcmp(tag_value,"living_street")){
            draw_line(w,nodes,HIGHWAY_WIDTH,HIGHWAY_DEPTH,237,237,237);
          }
          else if(!strcmp(tag_value,"track")){
            draw_line_stipple(w,nodes,TRACK_WIDTH,HIGHWAY_DEPTH,172,131,39);
          }
          else if(!strcmp(tag_value,"bus_guideway")){
            draw_line(w,nodes,BUS_G_WIDTH,HIGHWAY_DEPTH,100,100,255);
          }
          else if(!strcmp(tag_value,"raceway")){
            draw_line(w,nodes,HIGHWAY_WIDTH,HIGHWAY_DEPTH,255,192,202);
          }
          else if(!strcmp(tag_value,"road")){
            draw_line(w,nodes,ROAD_WIDTH,HIGHWAY_DEPTH,237,237,237);
          }
          else if(!strcmp(tag_value,"bridleway")){
            draw_line(w,nodes,BRIDLEWAY_WIDTH,HIGHWAY_DEPTH,94,171,92);
          }
          else if(!strcmp(tag_value,"steps")){
            draw_line_stipple(w,nodes,HIGHWAY_WIDTH,STEP_WAY_DEPTH,252,119,102);
          }
          else if(!strcmp(tag_value,"cycleway")){
            draw_line_stipple(w,nodes,CYCLEWAY_WIDTH,STEP_WAY_DEPTH,119,117,248);
          }
          else{
            printf("highway: %s\n",tag_value);
          }
        }
        else if(!strcmp(tag_key,"building")){
          if(!strcmp(tag_value,"yes")){
            draw_polygon(w,nodes,BULDING_DEPTH, 205, 199, 188);
            //draw_line(w,nodes,CONTOUR_WIDTH,BULDING_COUNTOUR_DEPTH,168, 146, 162);
            //polygonRGBA( tab_x, tab_y, g_slist_length(w->nodes), 168, 146, 162, 255);
          }
          else if(!strcmp(tag_value,"church")){
            draw_polygon(w,nodes,BULDING_DEPTH, 177, 173, 176);
            //draw_line(w,nodes,CONTOUR_WIDTH,BULDING_COUNTOUR_DEPTH,168, 146, 162);
            //polygonRGBA( tab_x, tab_y, g_slist_length(w->nodes), 168, 146, 162, 255);
          }
          else
            draw_polygon(w,nodes,BULDING_DEPTH, 205, 199, 188);
          draw_line(w,nodes,CONTOUR_WIDTH,BULDING_COUNTOUR_DEPTH,168, 146, 162);
        }
        else if(!strcmp(tag_key,"waterway")){
          if(!strcmp(tag_value,"river")){
            draw_line(w,nodes,HIGHWAY_WIDTH,WATER_DEPTH,180,190,209);
          }
          else if(!strcmp(tag_value,"riverbank")){
            draw_polygon(w,nodes,WATER_DEPTH,181,208,208);
          }
          else if(!strcmp(tag_value,"stream")){
            draw_line(w,nodes,HIGHWAY_WIDTH,WATER_DEPTH,180,208,209);
          }
        }
        else if(!strcmp(tag_key,"natural")){
          if(!strcmp(tag_value,"water")){
            draw_polygon(w,nodes,HIGHWAY_DEPTH,180, 208, 209);
            draw_line(w,nodes,CONTOUR_WIDTH,HIGHWAY_DEPTH,175, 175, 175);
          }
          else if(!strcmp(tag_value,"coastline")){
            if ( !coast_line) {
            //  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
              glClearColor(174/255.0,208/255.0,208/255.0,0.0);
              coast_line = 1;
            }
            draw_polygon(w,nodes,WATER_DEPTH, 221, 221, 221);
          }
          else if(!strcmp(tag_value,"land")){
            draw_polygon(w,nodes,LAND_DEPTH,242, 239, 233);
          }
        }
        else if(!strcmp(tag_key,"landuse") || !strcmp(tag_key,"leisure")){
          if(!strcmp(tag_value,"grass")){
            draw_polygon(w,nodes,LANDUSE_DEPTH, 207, 237, 165);
            draw_line(w,nodes,2,LANDUSE_DEPTH, 175, 175, 175);
          }
          else if(!strcmp(tag_value,"forest")){
            draw_polygon(w,nodes,LANDUSE_DEPTH, 157, 202, 138);
            draw_line(w,nodes,2,LANDUSE_DEPTH, 175, 175, 175);
          }
          else if(!strcmp(tag_value,"park")){
            draw_polygon(w,nodes,LANDUSE_DEPTH, 205, 247, 201);
            draw_line(w,nodes,2,LANDUSE_DEPTH, 175, 175, 175);
          }
          else if(!strcmp(tag_value,"garden")){
            draw_polygon(w,nodes,LANDUSE_DEPTH, 207, 236, 168);
            draw_line(w,nodes,2,LANDUSE_DEPTH, 175, 175, 175);
          }
          else if(!strcmp(tag_value,"pitch")){
            draw_polygon(w,nodes,LANDUSE_DEPTH, 138, 211, 175);
            draw_line(w,nodes,2,LANDUSE_DEPTH, 175, 175, 175);
          }
          else if(!strcmp(tag_value,"residential")){
            //draw_line_stipple(w,nodes,2,0.9, 190, 146, 190);
          }
        }
        else if(!strcmp(tag_key,"area")){
          if(!strcmp(tag_value,"yes")){
            draw_polygon(w,nodes,AREA_DEPTH, 237, 237, 237);
          }else{
            printf("area: %s\n",tag_value);
          }
        }
        else if(!strcmp(tag_key,"name")){
          if ( SHOW_TEXT ){
            write_name(w,nodes,tag_value);
          }
        }
        else if(!strcmp(tag_key,"network")){
          if(!strcmp(tag_value,"RATP")){
            draw_line_stipple(w,nodes,1,0.4, 255, 0, 0);
          }
        }
        else if(!strcmp(tag_key,"route")){
          if(!strcmp(tag_value,"ferry")){
            draw_line_stipple(w,nodes,1,0.4, 25, 29, 138);
          }
        }
    }
    if ( strcmp(w->at.id,"") ){
      w->drawn = 1;
      g_hash_table_insert(ways,&(w->at.id),w);
    }
}

void draw_way_relation(GSList *list, GHashTable *hash_ways, GHashTable *hash_nodes){
  int i;
  int count = g_slist_length(list);
  my_way *way = NULL;
  for (i = 0; i < count; i++) {
    char *data = g_slist_nth_data(list, i);
    way = (my_way *)g_hash_table_lookup(hash_ways,data);
    if ( way == NULL ) {
      //printf("way null...\n");
    }
    else
      draw_way(way,hash_ways,hash_nodes);

    way = NULL;
  }
  free(way);
}

my_way *set_way_outer(my_relation *rel, GHashTable *hash_ways){
  my_way *way = init_my_way();
  int i;
  int count = g_slist_length(rel->ways_outer);
  for (i = 0; i < count; i++) {
    my_way *w = (my_way *)g_hash_table_lookup(hash_ways,g_slist_nth_data(rel->ways_outer,i));
    if ( w != NULL ) {
      int j;
      int size = g_slist_length(w->nodes);
      for (j = 0; j < size; j++) {
        add_node_my_way(way,g_slist_nth_data(w->nodes,j));
      }
    }
  }
  strcpy(way->at.id,"");
  way->tag = rel->tags;
  return way;
}

my_way *set_way_node(my_relation *rel, GHashTable *hash_ways, GHashTable *hash_nodes){
  my_way *way = init_my_way();
  int i;
  int count = g_slist_length(rel->nodes);
  for (i = 0; i < count; i++) {
    char *idnode = g_slist_nth_data(rel->nodes,i);
    my_node *node = g_hash_table_lookup(hash_nodes,idnode);
    if( node != NULL )
      add_node_my_way(way,idnode);
  }
  strcpy(way->at.id,"");
  way->tag = rel->tags;
  return way;
}

void draw_one_relation(my_relation *rel, GHashTable *hash_relations, GHashTable *hash_ways, GHashTable *hash_nodes){
  //if ( !(rel->drawn) ) {
    if ( (rel->relations) != NULL ){
      if (g_slist_length(rel->relations) > 0) {
        int i;
        int size = g_slist_length(rel->relations);
        my_relation *re = NULL;//(my_relation *)malloc(sizeof(my_relation));
        for (i = 0; i < size; i++) {
          char *data = g_slist_nth_data (rel->relations, i);
          //printf("rel n: %s\n",data);
          re = (my_relation *)g_hash_table_lookup(hash_relations,data);
          if(re == NULL){
            //printf("relation null...\n");
          }
          else
            draw_one_relation(re,hash_relations,hash_ways,hash_nodes);
        }
      }
    }
    if ( rel->ways_outer != NULL && g_slist_length(rel->ways_outer) > 0 ){
      /*if ( rel->ways_inner == NULL || g_slist_length(rel->ways_inner) == 0 ){
        my_way *way = set_way_outer(rel,hash_ways);
        draw_way(way,hash_ways,hash_nodes);
      }else {*/
        draw_way_relation(rel->ways_outer,hash_ways, hash_nodes);
      //}
    }
    if ( rel->ways_inner != NULL && g_slist_length(rel->ways_inner) > 0 ){
      draw_way_relation(rel->ways_inner,hash_ways,hash_nodes);
    }
    if ( rel->ways != NULL && g_slist_length(rel->ways) > 0 ){
      //draw_way_relation(rel->ways,hash_ways,hash_nodes);
    }
    if ( rel->nodes != NULL && g_slist_length(rel->nodes) > 0 ){
      my_way *way = set_way_node(rel,hash_ways,hash_nodes);
      draw_way(way,hash_ways,hash_nodes);
      //free(way);
      //g_slist_free(way->nodes);
    }
}

void draw_relations(GHashTable *relations, GHashTable *ways, GHashTable *nodes){
  GHashTableIter iter5;
  gpointer relat5;
  g_hash_table_iter_init(&iter5, relations);
  while(g_hash_table_iter_next(&iter5, NULL, &relat5)){
    my_relation *rel = (my_relation *)malloc(sizeof(my_relation));
    rel = (my_relation *)relat5;
    if ( !strcmp(rel->at.visible,"true")) {
      draw_one_relation(rel,relations,ways,nodes);
    }
  }
  printf("done relations...\n");
}

void draw_ways(GHashTable *hash_ways, GHashTable *hash_nodes){
  GHashTableIter iter;
	gpointer val;
	g_hash_table_iter_init(&iter, hash_ways);
	 while(g_hash_table_iter_next(&iter, NULL, &val)){
     my_way *way = (my_way *)val;
     if ( !strcmp(way->at.visible,"true")) {
       if(way->drawn == 0)
        draw_way(way,hash_ways,hash_nodes);
       way->drawn = 0;
       g_hash_table_insert(hash_ways,&(way->at.id),way);
    }
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
  glEnable( GL_LINE_SMOOTH );
  glClearColor(221/255.0,221/255.0,221/255.0,0.0);
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
  draw_relations(hash_relations,hash_ways,hash_nodes);
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
      draw_relations(hash_relations,hash_ways,hash_nodes);
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
        glScalef( zoom, zoom, 1 );
        glTranslatef( cameraX , cameraY, 0.f );
        glPushMatrix();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        draw_relations(hash_relations,hash_ways,hash_nodes);
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
        glScalef( zoom, zoom, 1 );
        glPushMatrix();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        draw_relations(hash_relations,hash_ways,hash_nodes);
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
        glScalef( zoom, zoom, 1 );
        glPushMatrix();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        draw_relations(hash_relations,hash_ways,hash_nodes);
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
        draw_relations(hash_relations,hash_ways,hash_nodes);
      	draw_ways( hash_ways,hash_nodes);
        glFlush();
  		 	SDL_GL_SwapWindow(win);
      }

  }
  //glDisable(GL_LINE_STIPPLE);
	glDisable(GL_DEPTH_TEST);
  SDL_GL_DeleteContext(contextOpenGL);
	SDL_DestroyWindow(win);
	SDL_Quit();
}
