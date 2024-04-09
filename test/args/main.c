#include <stdio.h>

#include "../../args/args.h"


int main(int argc, const char** argv) {
    int a = 0, b = 0;

    const args_option_t options [] = {
        OPTION_BOOL('a', "aa", &a),
        OPTION_BOOL('b', "bb", &b),
        OPTION_HELP(),
    };

    args_t args;
    args_init(&args, options, GET_NB_OPTIONS(options), argc, argv, NULL);
    args_parse(&args);

    if (a) printf("aaaaa\n");
    if (b) printf("bbbbb\n");

    return 0;
}
