#ifndef __C_JSON_DUMP

#define __C_JSON_DUMP

#include "json.h"

static void buffer_json(Strbuf *buf, json_object json);

static void buffer_int(Strbuf *buf, uint_fast64_t i) {
    char str[80];
    sprintf(str, "%ld", i);
    strbuf_adds(buf, str);
}

static void buffer_double(Strbuf *buf, double d) {
    char str[80];
    sprintf(str, "%f", d);
    strbuf_adds(buf, str);
}

static void buffer_string(Strbuf *buf, char *str) {
    strbuf_addc(buf, '"');
    while (*str) {
        // TODO: expand this to actually deal with UTF8 and escaped chars
        if (*str == '"') {
            strbuf_addc(buf, '\\');
        }
        strbuf_addc(buf, *str++);
    }
    strbuf_addc(buf, '"');
}

static void buffer_vector(Strbuf *buf, Vector *v) {
    strbuf_addc(buf, '[');

    for (int i = 0; i < v->length; i++) {
        json_object e = *(json_object*) vector_get(v, i);
        buffer_json(buf, e);

        if (i != v->length - 1) {
            strbuf_addc(buf, ',');
        }
    }

    strbuf_addc(buf, ']');
}

static void buffer_map(Strbuf *buf, Map *map) {
    strbuf_addc(buf, '{');

    map_iter iter = map_iter_init(map);

    int comma = 0;

    while (map_next(&iter)) {
        if (comma) {
            strbuf_addc(buf, ',');
        } else {
            comma = 1;
        }

        buffer_string(buf, iter.key);
        strbuf_addc(buf, ':');
        buffer_json(buf, iter.value);
    }

    strbuf_addc(buf, '}');
    (void) map;
}

static void buffer_json(Strbuf *buf, json_object json) {
    switch (json.type) {
        case NUL:
            strbuf_adds(buf, "null");
            break;
        case INT:
            buffer_int(buf, unpack_int(json));
            break;
        case DOUBLE:
            buffer_double(buf, unpack_double(json));
            break;
        case BOOL:
            strbuf_adds(buf, json.value ? "true" : "false");
            break;
        case STRING:
            buffer_string(buf, unpack_str(json));
            break;
        case VECTOR:
            buffer_vector(buf, unpack_vec(json));
            break;
        case MAP:
            buffer_map(buf, unpack_map(json));
            break;
    }
}

int json_dump(char *filename, json_object json) {
    char *buffer = json_dumps(json);
    FILE *f = fopen(filename, "w");

    if (!f) {
        return 0;
    }

    int r = fputs(buffer, f);
    r |= fclose(f);
    free(buffer);

    return r == EOF ? 0 : 1;
}

char *json_dumps(json_object json) {
    Strbuf *buf = strbuf_create();
    buffer_json(buf, json);
    return strbuf_to_str(buf);
}

#endif
