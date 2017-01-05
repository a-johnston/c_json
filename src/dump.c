#ifndef __C_JSON_VECTOR

#define __C_JSON_VECTOR

#include "json.h"

static void buffer_json(Strbuf *buf, json_object json);

static void buffer_num(Strbuf *buf, json_object json) {
    double d = *(double*)(&json.value);
    (void) buf;
    (void) d;
}

static void buffer_string(Strbuf *buf, json_object json) {
    char *str = (char*) json.value;

    strbuf_addc(buf, '"');
    while (str) {
        // TODO: expand this to actually deal with UTF8
        if (*str == '"') {
            strbuf_addc(buf, '\\');
        }
        strbuf_addc(buf, *str++);
    }
    strbuf_addc(buf, '"');
}

static void buffer_vector(Strbuf *buf, json_object json) {
    strbuf_addc(buf, '[');

    Vector *v = (Vector*) json.value;

    for (int i = 0; i < v->length; i++) {
        json_object e = *(json_object*) vector_get(v, i);
        buffer_json(buf, e);

        if (i != v->length - 1) {
            strbuf_addc(buf, ',');
        }
    }

    strbuf_addc(buf, ']');
}

static void buffer_map(Strbuf *buf, json_object json) {
    (void) buf;
    (void) json;
}

static void buffer_json(Strbuf *buf, json_object json) {
    switch (json.type) {
        case NUL:
            strbuf_adds(buf, "null");
            break;
        case NUM:
            buffer_num(buf, json);
            break;
        case BOOL:
            strbuf_adds(buf, json.value ? "true" : "false");
            break;
        case STRING:
            buffer_string(buf, json);
            break;
        case VECTOR:
            buffer_vector(buf, json);
            break;
        case MAP:
            buffer_map(buf, json);
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

    char *str = buf->str;
    free(buf);

    return str;
}

#endif
