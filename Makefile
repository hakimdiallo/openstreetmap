CC = gcc
CFLAGS = -g -lm -lSDL2_gfx -Wall
CPPFLAGS = `xml2-config --cflags --libs` `sdl2-config --cflags --libs` `pkg-config --cflags --libs glib-2.0`
EXEC = osm_main
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^ $(CPPFLAGS) $(CFLAGS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< $(CPPFLAGS)

#gcc -Wall -o hello_glib hello_glib.c $(pkg-config --cflags --libs glib-2.0)
mrproper: clean
	rm -f $(EXEC)

clean:
	rm -f $(OBJECTS)
	rm -f *~
