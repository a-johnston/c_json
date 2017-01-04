#ifndef __C_JSON_VECTOR

#define __C_JSON_VECTOR

#include "json.h"

Strbuf *strbuf_create() {
    Strbuf *buf = malloc(sizeof(Strbuf));

    buf->str = calloc(20, sizeof(char));
    buf->capacity = 20;
    buf->length = 0;

    buf->str[0] = '\0';

    return buf;
}

void strbuf_free(Strbuf *buf) {
    free(buf->str);
    free(buf);
}

static int ensure_capacity(Strbuf *buf, int length) {
    if (buf->capacity < length) {
        // TODO: consider alt allocation strategies
        char *temp = realloc(buf->str, (length + 1) * sizeof(char));
        
        if (temp) {
            buf->str = temp;
            buf->capacity = length + 1;
        } else {
            return 0;
        }
    }

    return 1;
}

int strbuf_add(Strbuf *buf, char *str) {
    int length = strlen(str);

    if (!ensure_capacity(buf, buf->length + length + 1)) {
        return -1;
    }

    strncpy(buf->str + buf->length, str, length);
    buf->length += length;
    buf->str[buf->length + 1] = '\0';

    return buf->length;
}

int strbuf_addc(Strbuf *buf, char c) {
    if (!ensure_capacity(buf, buf->length + 2)) {
        return -1;
    }

    buf->str[buf->length++] = c;
    buf->str[buf->length] = '\0';

    return buf->length;
}

#endif
