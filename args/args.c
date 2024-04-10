#include "args.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/******************************************************
 *                 Private functions                  *
 ******************************************************/

static void priv_check_options(args_t* args) {
    const args_option_t* options = args->options;

    for (int i = 0; i < args->nb_options; i++) {
        switch (options[i].type) {
            case OPT_BOOL:
            case OPT_INT:
            case OPT_STRING:
            case OPT_HELP:
                continue;
            default:
                fprintf(stderr, "\033[31merror:\033[0m wrong option type: %d\n", options[i].type);
                printf("Try '%s --help' for more information.\n", args->name);
                exit(EXIT_FAILURE);
        }
    }
}


/******************************************************
 *                 Public functions                   *
 ******************************************************/

void args_init(args_t* args, const args_option_t* options, const int nb_options, const int argc, const char** argv, const char* help) {
    memset(args, 0, sizeof(args_t));

    args->options = options;
    args->nb_options = nb_options;
    args->argc = argc;
    args->argv = argv;
    args->help = help != NULL ? help : "No help message";
    args->name = argv[0];

    priv_check_options(args);
}

void args_parse(args_t* args) {
    int i = 0;
    while (args->argc) {
        printf("%s\n", args->argv[i]);

        args->argc--;
        i++;
    }
}
