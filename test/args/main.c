#include <stdio.h>

#include "../../args/args.h"


int main(int argc, const char** argv) {
    int a = 0, b = 0;

    const args_option_t options [] = {
        OPTION_BOOL('a', "aa", &a),
        OPTION_BOOL('b', "bb", &b),
        OPTION_HELP(),
        OPTION_END(),
    };

    args_t args;
    args_init(&args, options, argc, argv, NULL);
    args_parse(&args);

    if (a) printf("option a selected\n");
    if (b) printf("option b selected\n");

    return 0;
}
