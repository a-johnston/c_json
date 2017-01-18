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
    INT,
    DOUBLE,
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

typedef void (*_vec_free_element_impl)(void *e);

typedef struct {
    json_object *data;
    int element_size;
    int capacity;
    int length;
    _vec_free_element_impl free_strategy;
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

typedef struct {
    Map *__map;
    int __i;

    char *key;
    json_object value;
} map_iter;

Map *map_create();

void map_free(Map *map);

void map_put(Map *map, char *key, json_object value);

int map_contains(Map *map, char *key);

json_object *map_get(Map *map, char *key);

void map_remove(Map *map, char *key);

map_iter map_iter_init(Map *map);

int map_next(map_iter *iter);

/*
 * strbuf.c
 */

typedef struct {
    char *str;
    int capacity;
    int length;
} Strbuf;

Strbuf *strbuf_create();

void strbuf_free(Strbuf *buf);

char *strbuf_to_str(Strbuf *buf);

int strbuf_adds(Strbuf *buf, char *str);

int strbuf_addsb(Strbuf *buf, Strbuf *toAdd);

int strbuf_addsn(Strbuf *buf, char *str, int n);

int strbuf_addc(Strbuf *buf, char c);

void strbuf_reverse(Strbuf *buf);

/*
 * pack.c
 */

void json_free(json_object json);

json_object pack_int(uint_fast64_t i);

json_object pack_double(double d);

json_object pack_str(char *str);

json_object pack_vec(Vector *vec);

json_object pack_map(Map *map);

uint_fast64_t unpack_int(json_object json);

double unpack_double(json_object json);

char *unpack_str(json_object json);

Vector *unpack_vec(json_object json);

Map *unpack_map(json_object json);

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
