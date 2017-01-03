#ifndef __CJSON_H

#define __CJSON_H

#include <stdlib.h>
#include <string.h>

/*
 * JSON types
 */

enum JSON_TYPE {
    INT = 0,
    FLOAT,
    STRING,
    VECTOR,
    MAP,
    NUM_TYPES
};

typedef int JSON_TYPE;

typedef struct {
    JSON_TYPE type;
    void *value;
} json_object;

/*
 * vector.c
 */

typedef struct {
    json_object *data;
    int capacity;
    int length;
} Vector;

Vector *vector_create();

void vector_free(Vector *vector);

void vector_clear(Vector *vector);

int vector_add(Vector *vector, json_object *e);

void vector_add_all(Vector *vector, Vector *toAdd);

void vector_insert(Vector *vector, json_object *e, int i);

void vector_remove(Vector *vector, int i);

void vector_set(Vector *vector, json_object *e, int i);

json_object *vector_get(Vector *vector, int i);

#endif
