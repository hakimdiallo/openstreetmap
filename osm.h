#include <stdio.h>
#include <stdlib.h>

typedef struct tag {
	char *key;
	char *value;
} tag;

typedef struct attributs {
	int id;
	char *visible;
	/*
		char *user;
		int uid;
		char *timestamp;
		char *version;
	*/
} attributs;

typedef struct node {
	int lon;
	int lat;
	attributs at;
	tag t;
} node;

typedef struct way {
	attributs at;
	int *refs;
	tag *t;
} way;

typedef struct area {
	way w;
}
