#include <stdio.h>

#include "../../args/args.h"


int main(int argc, const char** argv) {
    char* s = NULL;
    int a = 0, b = 0, i = 0;

    const char* help =
        "Test [options]\n"
        "\n"
        "Options:\n"
        "   -a --aa         Bool\n"
        "   -b --bb         Bool\n"
        "   -s --string     String\n"
        "   -i --int        Int\n";

    const args_option_t options [] = {
        OPTION_BOOL('a', "aa", &a),
        OPTION_BOOL('b', "bb", &b),
        OPTION_STRING('s', "string", &s),
        OPTION_INT('i', "int", &i),
        OPTION_HELP(&help),
        OPTION_END(),
    };

    args_t args;
    args_init(&args, options, argc, argv, NULL);
    args_parse(&args);

    if (a) printf("option a\n");
    if (b) printf("option b\n");
    if (s != NULL) printf("option s: %s\n", s);
    if (i != 0) printf("option i: %d\n", i);

    return 0;
}
