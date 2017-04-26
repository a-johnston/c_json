#include <json.h>

int main() {
    json_object json = json_loads("12.345,987");
    double d = unpack_double(json);
    printf("%f\n", d);

    char *dump = json_dumps(json);
    printf("%s\n", dump);
    free(dump);

    json = json_loads("123");
    int i = unpack_int(json);
    printf("%d\n", i);

    dump = json_dumps(json);
    printf("%s\n", dump);
    free(dump);

    json = json_loads("\"test string \\\" lol\":123");
    char *str = unpack_str(json);
    printf("%s\n", str);

    json = json_loads("[1,2,3,\"test str\"]");
    Vector *v = unpack_vec(json);
    printf("%d\n", v->length);

    dump = json_dumps(json);
    printf("%s\n", dump);
    free(dump);

    free(str);
    vector_free(v);

    json = json_loads("{\"test\": 123, \"ids\": [1, 2, 3, 4]}");
    Map *m = unpack_map(json);
    dump = json_dumps(json);
    printf("%s\n", dump);

    free(dump);
    map_free(m);
}
