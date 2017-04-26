#ifndef __C_JSON_STRBUF

#define __C_JSON_STRBUF

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

char *strbuf_to_str(Strbuf *buf) {
    char *str = buf->str;

    if (buf->capacity > buf->length + 1) {
        str = realloc(buf->str, (buf->length + 1) * sizeof(char));
        str[buf->length] = '\0';
    }

    free(buf);
    return str;
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

int strbuf_adds(Strbuf *buf, char *str) {
    return strbuf_addsn(buf, str, strlen(str));
}

int strbuf_addsb(Strbuf *buf, Strbuf *toAdd) {
    return strbuf_addsn(buf, toAdd->str, toAdd->length);
}

int strbuf_addsn(Strbuf *buf, char *str, int n) {
    if (!ensure_capacity(buf, buf->length + n + 1)) {
        return -1;
    }

    strncpy(buf->str + buf->length, str, n);
    buf->length += n;
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

void strbuf_reverse(Strbuf *buf) {
    int upper = buf->length / 2;

    for (int i = 0; i < upper; i++) {
        char a = buf->str[i];
        char b = buf->str[buf->length - i - 1];
        
        buf->str[buf->length - i -1] = a;
        buf->str[i] = b;
    }
}

#endif
