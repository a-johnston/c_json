#ifndef __CJSON_H

#define __CJSON_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * JSON types
 */

enum JSON_TYPE {
    NUL = 0,
    NUM,
    BOOL,
    STRING,
    VECTOR,
    MAP,
    NUM_TYPES,
};

typedef int JSON_TYPE;

typedef struct {
    JSON_TYPE type;
    uint_fast64_t value;
} json_object;

/*
 * vector.c
 */

typedef struct {
    json_object *data;
    int element_size;
    int capacity;
    int length;
} Vector;

Vector *vector_create();

void vector_free(Vector *vector);

void vector_clear(Vector *vector);

int vector_add(Vector *vector, void *e);

void vector_add_all(Vector *vector, Vector *toAdd);

void vector_insert(Vector *vector, void *e, int i);

void vector_remove(Vector *vector, int i);

void *vector_get(Vector *vector, int i);

void vector_set(Vector *vector, void *e, int i);

/*
 * map.c
 */

typedef struct {
    Vector *data;
} Map;

Map *map_create();

void map_free(Map *map);

void map_clear(Map *map);

void map_put(Map *map, char *key, json_object value);

int map_contains(Map *map, char *key);

json_object *map_get(Map *map, char *key);

void map_remove(Map *map, char *key);

/*
 * load.c
 */

json_object json_load(char *filename);

json_object json_loads(char *string);

/*
 * dump.c
 */

int json_dump(char *filename, json_object json);

char *json_dumps(json_object json);

#endif
