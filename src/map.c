#ifndef __C_JSON_MAP

#define __C_JSON_MAP

#include "json.h"

typedef struct {
    char *key;
    json_object value;
} map_element;

static void map_element_free(void *e) {
    map_element pair = *(map_element*) e;
    free(pair.key);
    json_free(pair.value);
}

Map *map_create() {
    Map *map = (Map*) malloc(sizeof(Map));

    map->data = (Vector*) malloc(sizeof(Vector));
    map->data->data = calloc(10, sizeof(map_element));
    map->data->element_size = sizeof(map_element);
    map->data->capacity = 10;
    map->data->length = 0;

    map->data->free_strategy = map_element_free;

    return map;
}

void map_free(Map *map) {
    vector_free(map->data);
    free(map);
}

void map_put(Map *map, char *key, json_object value) {
    int i = map_contains(map, key);

    if (i) {
        map_element *e = vector_get(map->data, i - 1);
        e->value = value;
    } else {
        map_element e;
        e.key = malloc(strlen(key));
        strcpy(e.key, key);
        e.value = value;

        vector_add(map->data, &e);
    }
}

/*
 * Returns whether or not the given key is present in the given map instance.
 * If the key is not present, 0 is returned. If it is present, the index + 1 is
 * returned. In the case that this is updated to not secretly be a vector, the
 * return value will at least be true.
 */
int map_contains(Map *map, char *key) {
    for (int i = 0; i < map->data->length; i++) {
        map_element *e = vector_get(map->data, i);

        if (strcmp(e->key, key) == 0) {
            return i + 1;
        }
    }

    return 0;
}

json_object *map_get(Map *map, char *key) {
    int i = map_contains(map, key);
    return i ? vector_get(map->data, i - 1) : NULL;
}

void map_remove(Map *map, char *key) {
    int i = map_contains(map, key);

    if (i) {
        map_element *e = vector_get(map->data, i - 1);
        free(e->key);

        vector_remove(map->data, i - 1);
    }
}

map_iter map_iter_init(Map *map) {
    return (map_iter) {
        map,
        0,
        NULL,
        (json_object) { 0, 0 }
    };
}

int map_next(map_iter *iter) {
    if (iter->__i < iter->__map->data->length) {
        map_element *e = vector_get(iter->__map->data, iter->__i);

        iter->key = e->key;
        iter->value = e->value;

        iter->__i++;
        return 1;
    } else {
        return 0;
    }
}

#endif
