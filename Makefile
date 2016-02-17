CC = gcc
CFLAGS = -g -Wall
CPPFLAGS = `xml2-config --cflags --libs` `sdl-config --cflags --libs`
EXEC = osm_main
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^ $(CPPFLAGS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< $(CPPFLAGS)


mrproper: clean
	rm -f $(EXEC)

clean:
	rm -f $(OBJECTS)
	rm -f *~
