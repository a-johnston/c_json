#ifndef __C_JSON_LOAD

#define __C_JSON_LOAD

#include "json.h"

static json_object _json_loads(char **string);

static void consume_whitespace(char **s) {
    while (**s == ' ' || **s == '\t' || **s == '\n') {
        (*s)++;
    }
}

static json_object loads_num(char **string) {
    double value = 0;
    int d = 0;
    int r = 1;

    while (r) {
        char c = *(*string)++;

        if (c >= '0' && c <= '9') {
            value *= 10;
            d *= 10;
            value += c - '0';
        } else if (c == '.') {
            d = 1;
        } else {
            r = 0;
            (*string)--;
        }
    }

    if (d) {
        value /= d;
        return pack_double(value);
    }

    return pack_int(value);
}

static json_object loads_string(char **string) {
    Strbuf *buf = strbuf_create();

    int needs = 2;
    int escape = 0;

    while (needs) {
        char c = *(*string)++;

        if (escape) {
            strbuf_addc(buf, c);
            escape = 0;
        } else {
            if (c == '\\') {
                escape = 1;
            } else if (c == '"') {
                needs--;
            } else if (c == '\0') {
                // panic - bad json
                return (json_object) { NUL, 0 };
            } else {
                strbuf_addc(buf, c);
            }
        }
    }

    char *str = strbuf_to_str(buf);

    return pack_str(str);
}

static json_object loads_vector(char **string) {
    if (**string != '[') {
        // sanity check
        (*string)++;
        return (json_object) { NUL, 1 };
    }

    Vector *v = vector_create();

    while (*(*string)++ != ']') { // note this consumes opening bracket and commas
        consume_whitespace(string);
        json_object json = _json_loads(string);
        vector_add(v, &json);
        consume_whitespace(string);
    }

    return pack_vec(v);
}

static json_object loads_map(char **string) {
    if (**string != '{') {
        // sanity check
        (*string)++;
        return (json_object) { NUL, 1 };
    }

    Map *m = map_create();

    while (*(*string)++ != '}') {
        consume_whitespace(string);
        char *key = unpack_str(loads_string(string));
        consume_whitespace(string);
        if (*(*string)++ != ':') {
            break;
        }
        consume_whitespace(string);
        json_object val = _json_loads(string);
        consume_whitespace(string);

        map_put(m, key, val);
    }

    return pack_map(m);
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

    json_object json = _json_loads(&buffer);
    free(buffer);

    return json;
}

json_object json_loads(char *string) {
    return _json_loads(&string);
}

static json_object _json_loads(char **string) {
    consume_whitespace(string);

    if ((**string >= '0' && **string <= '9') || **string == '.') {
        return loads_num(string);
    }
    if (**string == '"') {
        return loads_string(string);
    }
    if (**string == '[') {
        return loads_vector(string);
    }
    if (**string == '{') {
        return loads_map(string);
    }

    return (json_object) { NUL, 0 };
}

#endif
