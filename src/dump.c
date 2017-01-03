#ifndef __C_JSON_VECTOR

#define __C_JSON_VECTOR

#include "json.h"

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
    (void) json;
    return "IMPLEMENT ME PLS";
}

#endif
