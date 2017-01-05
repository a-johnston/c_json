#ifndef __C_JSON_VECTOR

#define __C_JSON_VECTOR

#include "json.h"

json_object num_to_json(double d) {
    return (json_object) { NUM, *(uint_fast64_t*) &d };
}

double json_to_num(json_object json) {
    return *(double*)&json.value;
}

#endif
