CC = gcc
CFLAGS = -g -Wall
CPPFLAGS = `xml2-config --cflags`
LDFLAGS = `xml2-config --libs`
SRC = $(wildcard *.c)
EXE = $(SRC:.c=.exe)

all: $(EXE)

%.exe: %.c
<tabulation>$(CC) $(CFLAGS) $< -o $@ $(CPPFLAGS) $(LDFLAGS)
