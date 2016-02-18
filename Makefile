CC = gcc
CFLAGS = -g -Wall
CPPFLAGS = `xml2-config --cflags`
LDFLAGS = `xml2-config --libs`
EXEC = osm_main
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS) $(CPPFLAGS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< $(LDFLAGS) $(CPPFLAGS)


mrproper: clean
	rm -f $(EXEC)

clean:
	rm -f $(OBJECTS)
	rm -f *~
