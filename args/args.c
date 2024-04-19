#include "args.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


#define OPT_SHORT                 1
#define OPT_LONG                  2
#define OPT_NON_OPTION            3
#define OPT_NON_OPTION_SEPARATOR  4


enum error_type {
    ERROR_NULL_POINTER,
    ERROR_WRONG_OPTION_TYPE,
    ERROR_OPT_SHORT,
    ERROR_OPT_LONG,
    ERROR_OPT_UNKNOWN,
};


/******************************************************
 *                 Private functions                  *
 ******************************************************/

static int priv_to_int(const char* str, int* out) {
    char* end;
    long res;

    res = strtol(str, &end, 10);

    if (str[0] == '\0' || str[0] == ' '
        || res > INT_MAX || res < INT_MIN
        || *end != '\0') {
        return -1;
    }

    *out = (int)res;

    return 0;
}

static void priv_error(args_t* args, const args_option_t* option, const char* reason, enum error_type cause) {
    switch (cause) {
        case ERROR_NULL_POINTER:
            fprintf(stderr, "\033[31merror:\033[0m option value is a NULL pointer\n"); break;
        case ERROR_WRONG_OPTION_TYPE:
            fprintf(stderr, "\033[31merror:\033[0m wrong option type: %d\n", option->type); break;
        case ERROR_OPT_SHORT:
            fprintf(stderr, "\033[31merror:\033[0m option `-%c` %s\n", option->short_name, reason); break;
        case ERROR_OPT_LONG:
            fprintf(stderr, "\033[31merror:\033[0m option `--%s` %s\n", option->long_name, reason); break;
        case ERROR_OPT_UNKNOWN:
            fprintf(stderr, "\033[31merror:\033[0m unknown option `%s`\n", *args->argv); break;
        default:
            break;
    }
    printf("Try '%s --help' for more information.\n", args->name);
    exit(EXIT_FAILURE);
}

static void priv_check_options(args_t* args) {
    const args_option_t* options = args->options;

    for (;options->type != OPT_END; options++) {
        if (options->short_name != 'h' && options->val == NULL) {
            priv_error(args, options, NULL, ERROR_NULL_POINTER);
        }
        switch (options->type) {
            case OPT_BOOL:
            case OPT_INT:
            case OPT_STRING:
            case OPT_HELP:
                continue;
            default:
                priv_error(args, options, NULL, ERROR_WRONG_OPTION_TYPE);
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
    enum error_type error = priv_get_opt_type(args->argv[0]) == OPT_SHORT ? ERROR_OPT_SHORT : ERROR_OPT_LONG;

    switch (option->type) {
        case OPT_BOOL:
            *(int*)option->val = 1;
            break;
        case OPT_INT:
            if (args->argc < 2) {
                priv_error(args, option, "requires a value", error);
            }
            args->argv++;
            args->argc--;
            if (priv_to_int(args->argv[0], (int*)option->val) != 0) {
                priv_error(args, option, "not a valid int", error);
            }
            break;
        case OPT_STRING:
            if (args->argc < 2) {
                priv_error(args, option, "requires a value", error);
            }
            args->argv++;
            args->argc--;
            *(const char**)option->val = args->argv[0];
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
            return;
        }
    }

    priv_error(args, options, NULL, ERROR_OPT_UNKNOWN);
}

static void priv_long_opt(args_t* args, const char* opt) {
    const args_option_t* options = args->options;

    for (;options->type != OPT_END; options++) {
        if (strcmp(options->long_name, opt) == 0) {
            priv_get_value(args, options);
            return;
        }
    }

    priv_error(args, options, NULL, ERROR_OPT_UNKNOWN);
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
            case OPT_SHORT:
                opt++;
                while (*opt) {
                    priv_short_opt(args, *opt);
                    opt++;
                }
                break;
            case OPT_LONG:
                opt += 2;
                priv_long_opt(args, opt);
                break;
            case OPT_NON_OPTION:
                break;
            case OPT_NON_OPTION_SEPARATOR:
                break;
            default:
                break;
        }

        args->argc--;
        args->argv++;
    }
}
