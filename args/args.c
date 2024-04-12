#include "args.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define OPT_SHORT                 1
#define OPT_LONG                  2
#define OPT_NON_OPTION            3
#define OPT_NON_OPTION_SEPARATOR  4


/******************************************************
 *                 Private functions                  *
 ******************************************************/

static void priv_check_options(args_t* args) {
    const args_option_t* options = args->options;

    for (;options->type != OPT_END; options++) {
        switch (options->type) {
            case OPT_BOOL:
            case OPT_INT:
            case OPT_STRING:
            case OPT_HELP:
                continue;
            default:
                fprintf(stderr, "\033[31merror:\033[0m wrong option type: %d\n", options->type);
                printf("Try '%s --help' for more information.\n", args->name);
                exit(EXIT_FAILURE);
        }
    }
}

static int priv_get_opt_type(const char* opt) {
    if (strlen(opt) < 2 || opt[0] != '-') {
        return OPT_NON_OPTION;
    } else if (strlen(opt) == 2 && opt[1] == '-') {
        return OPT_NON_OPTION_SEPARATOR;
    } else if (opt[1] != '-') {
        return OPT_SHORT;
    } else {
        return OPT_LONG;
    }
}

static void priv_get_value(args_t* args, const args_option_t* option) {
    switch (option->type) {
        case OPT_BOOL:
            *(int*)option->val = 1;
            break;
        case OPT_INT:
            break;
        case OPT_STRING:
            break;
        case OPT_HELP:
            break;
        default:
            break;
    }
}

static void priv_short_opt(args_t* args, const char opt) {
    const args_option_t* options = args->options;

    for (;options->type != OPT_END; options++) {
        if (options->short_name == opt) {
            priv_get_value(args, options);
        }
    }
}


/******************************************************
 *                 Public functions                   *
 ******************************************************/

void args_init(args_t* args, const args_option_t* options, const int argc, const char** argv, const char* help) {
    memset(args, 0, sizeof(args_t));

    args->options = options;
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
                break;
            case OPT_SHORT:
                opt++;
                while (*opt) {
                    priv_short_opt(args, *opt);
                    opt++;
                }
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
