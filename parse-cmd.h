#ifndef PARSE_CMD_H
#define PARSE_CMD_H

enum OPTION_ARUGMENTS {
    OPTIONAL_VALUE,
    MANDATORY_VALUE,
    NO_VALUE
};

typedef struct cmd_option {
    char*       short_opt;
    char*       long_opt;
    int         has_value;
    int         value_specified;
    char[1024]  option_argument;
}cmd_option;

typedef struct cmd_argument {
    char*       argument;
    int         nposition;
};

int parse_options(int arc, char** argv, cmd_option*, int nargs);


#endif // !PARSE_CMD_H

