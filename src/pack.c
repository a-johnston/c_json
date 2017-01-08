#ifndef __C_JSON_VECTOR

#define __C_JSON_VECTOR

#include "json.h"

void json_free(json_object json) {
    if (json.type == STRING) {
        free((void*) json.value);
    }

    if (json.type == VECTOR) {
        vector_free((Vector*) json.value);
    }

    if (json.type == MAP) {
        map_free((Map*) json.value);
    }
}

// Packing

json_object pack_num(double d) {
    return (json_object) { NUM, *(uint_fast64_t*) &d };
}

json_object pack_str(char *str) {
    return (json_object) { STRING, (uint_fast64_t) str };
}

json_object pack_vec(Vector *vec) {
    return (json_object) { VECTOR, (uint_fast64_t) vec };
}

// Unpacking

double unpack_num(json_object json) {
    return *(double*)&json.value;
}

char *unpack_str(json_object json) {
    return (char*) json.value;
}

Vector *unpack_vec(json_object json) {
    return (Vector*) json.value;
}

#endif
