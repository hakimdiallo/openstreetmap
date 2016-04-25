CC = gcc
CFLAGS = -g -lm -lSDL2_gfx -W -Wall -lglut -lGLU -lGL
LDFLAGS = `xml2-config --cflags --libs` `sdl2-config --cflags --libs` `pkg-config --cflags --libs glib-2.0`
EXEC = osm_main
#HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS) $(CFLAGS)

%.o: %.c #$(HEADERS)
	$(CC) $(CFLAGS) -c $< $(LDFLAGS)

mrproper: clean
	rm -f $(EXEC)

osm_main.o: graphic_opengl.h osm_structure.h osm.h
osm_structure.o: osm_structure.h
osm.o: osm_structure.h osm.h mercator.h
graphic_opengl.o: graphic_opengl.h osm_structure.h
mercator.o: mercator.h 

clean:
	rm -f $(OBJECTS)
	rm -f *~
