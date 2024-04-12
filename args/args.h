#if !defined(ARGS_H)
#define ARGS_H


#define OPTION_END() {OPT_END, 0, 0, NULL}
#define OPTION_HELP()            {OPT_HELP, 'h', "help", NULL}
#define OPTION_BOOL(S, L, VAL)   {OPT_BOOL,   S, L, VAL}
#define OPTION_INT(S, L, VAL)    {OPT_INT,    S, L, VAL}
#define OPTION_STRING(S, L, VAL) {OPT_STRING, S, L, VAL}


typedef enum args_option_type {
    OPT_BOOL,
    OPT_INT,
    OPT_STRING,
    OPT_HELP,
    OPT_END,
} args_option_type_t;

typedef struct args_option {
    const args_option_type_t type;

    const char short_name;
    const char* long_name;

    void* val;
} args_option_t;

typedef struct args {
    const args_option_t* options;

    int argc;
    const char** argv;

    const char* help;
    const char* name;
} args_t;


void args_init(args_t* args, const args_option_t* options, const int argc, const char** argv, const char* help);
void args_parse(args_t* args);


#endif /* ARGS_H */
