#include "args.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define OPT_SHORT       1
#define OPT_LONG        2
#define OPT_NON_OPTION  3


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

static int priv_get_opt_type(const char* opt) {
    if (strlen(opt) < 2 || opt[0] != '-') {
        return OPT_NON_OPTION;
    } else if (opt[1] != '-') {
        return OPT_SHORT;
    } else {
        return OPT_LONG;
    }
}

static void priv_get_value(args_t* args, args_option_type_t* option) {

}

static void priv_short_opt(args_t* args, const char* opt) {
    printf("%s\n", args->argv[0]);
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
    args->argc--;
    args->argv++;

    while (args->argc) {
        const char* opt = args->argv[0];

        switch (priv_get_opt_type(opt)) {
            case OPT_NON_OPTION:
                continue;
            case OPT_SHORT:
                priv_short_opt(args, opt);
                break;
            case OPT_LONG:
                break;
            default:
                break;
        }

        args->argc--;
        args->argv++;
    }
}
