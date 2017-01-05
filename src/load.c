#ifndef __C_JSON_VECTOR

#define __C_JSON_VECTOR

#include "json.h"

static json_object _json_loads(char *string, char *end);

static json_object loads_num(char *string, char *end) {
    double value = 0;
    int d = 0;

    while (string <= end) {
        char c = *string++;

        if (c >= '0' && c <= '9') {
            value *= 10;
            d *= 10;
            value += c - '0';
        } else if (c == '.') {
            d = 1;
        }
    }

    if (d) {
        value /= d;
    }

    return num_to_json(value);
}

static json_object loads_string(char *string, char *end) {
    (void) string;
    (void) end;
    return (json_object) { NUL, 1 };
}

static json_object loads_vector(char *string, char *end) {
    (void) string;
    (void) end;
    return (json_object) { NUL, 1 };
}

static json_object loads_map(char *string, char *end) {
    (void) string;
    (void) end;
    return (json_object) { NUL, 1 };
}

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

    json_object json = _json_loads(buffer, buffer + length - 1);
    free(buffer);

    return json;
}

json_object json_loads(char *string) {
    return _json_loads(string, string + strlen(string) - 1);
}

static json_object _json_loads(char *string, char *end) {
    if ((*string >= '0' && *string <= '9') || *string == '.') {
        return loads_num(string, end);
    }
    if (*string == '"' && *end == '"') {
        return loads_string(string, end);
    }
    if (*string == '[' && *end == ']') {
        return loads_vector(string, end);
    }
    if (*string == '{' && *end == '}') {
        return loads_map(string, end);
    }

    return (json_object) { NUL, 0 };
}

#endif
