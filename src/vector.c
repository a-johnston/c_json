#ifndef __C_JSON_VECTOR

#define __C_JSON_VECTOR

#include "json.h"

static void _ensure_capacity(Vector *vector, int capacity) {
    if (capacity > vector->capacity) {
        void *temp = realloc(
            vector->data,
            sizeof(json_object) * vector->capacity * 2
        );

        if (temp) {
            vector->data = temp;
            vector->capacity = capacity;
        }
    }
}

Vector *vector_create() {
    Vector *vector = (Vector*) malloc(sizeof(Vector));
    vector->data = calloc(10, sizeof(json_object));
    vector->capacity = 10;
    vector->length = 0;

    return vector;
}

void vector_free(Vector *vector) {
    free(vector->data);
    free(vector);
}

void vector_clear(Vector *vector) {
    vector->length = 0;
}

int vector_add(Vector *vector, json_object *e) {
    _ensure_capacity(vector, vector->length + 1);
    vector_set(vector, e, vector->length);
    return vector->length++;
}

void vector_add_all(Vector *vector, Vector *toAdd) {
    _ensure_capacity(vector, vector->length + toAdd->length);
    memcpy(
        vector->data + vector->length * sizeof(json_object),
        toAdd->data,
        toAdd->length * sizeof(json_object)
    );
}

void vector_insert(Vector *vector, json_object *e, int i) {
    _ensure_capacity(vector, vector->length + 1);
    void *p = vector_get(vector, i);
    memmove(
        p + sizeof(json_object),
        p,
        sizeof(json_object) * (vector->length - i - 1)
    );
    vector_set(vector, e, i);
    vector->length++;
}

void vector_remove(Vector *vector, int i) {
    void *p = vector_get(vector, i);
    memmove(
        p,
        p + sizeof(json_object),
        sizeof(json_object) * (vector->length - i - 1)
    );
    vector->length--;
}

void vector_set(Vector *vector, json_object *e, int i) {
    vector->data[i] = *e;
}

json_object *vector_get(Vector *vector, int i) {
    return &vector->data[i];
}

#endif
