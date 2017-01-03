#ifndef __C_JSON_VECTOR

#define __C_JSON_VECTOR

#include "json.h"

static json_object _json_loads(char *string, int length);

json_object json_load(char *filename) {
    FILE *f = fopen(filename, "r");

    if (!f) {
        return (json_object) { NUL, 0 };
    }

    int length;
    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *buffer = malloc(length);
    length = fread(buffer, 1, length, f);
    fclose(f);

    json_object json = _json_loads(buffer, length);
    free(buffer);

    return json;
}

json_object json_loads(char *string) {
    return _json_loads(string, strlen(string));
}

static json_object _json_loads(char *string, int length) {
    (void) string;
    (void) length;
    return (json_object) { NUL, 0 };
}

#endif
