#ifndef __C_JSON_VECTOR

#define __C_JSON_VECTOR

#include "json.h"

static char *to_string_num(json_object json) {
    (void) json;
    return "";
}

static char *to_string_string(json_object json) {
    (void) json;
    return "";
}

static char *to_string_vector(json_object json) {
    (void) json;
    return "";
}

static char *to_string_map(json_object json) {
    (void) json;
    return "";
}

int json_dump(char *filename, json_object json) {
    char *buffer = json_dumps(json);
    FILE *f = fopen(filename, "w");

    if (!f) {
        return 0;
    }

    int r = fputs(buffer, f);
    r |= fclose(f);

    return r == EOF ? 0 : 1;
}

char *json_dumps(json_object json) {
    switch (json.type) {
        case NUL:       return "null";
        case NUM:       return to_string_num(json);
        case BOOL:      return json.value ? "true" : "false";
        case STRING:    return to_string_string(json);
        case VECTOR:    return to_string_vector(json);
        case MAP:       return to_string_map(json);
    }

    return "";
}

#endif
