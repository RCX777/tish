// Handling of built-in commands

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "colors.h"
#include "builtin.h"


enum builtin_idx {
    _exit_,
    cd,
    help
};

static char* builtin_fname[] = {
    [_exit_] = "exit",
    [cd]     = "cd",
    [help]   = "help"
};

static void (*builtin_func[])(char**) = {
    [_exit_] = cmd_exit,
    [cd]     = cmd_cd,
    [help]   = cmd_help
};

static size_t builtin_nmemb = sizeof(builtin_fname) / sizeof(char*);

/* Built-in command handler. Should be self-explanatory. It also
 * returns 1 if input was a built-in, or 0 otherwise. */
bool builtin_handler(char** args)
{
    size_t idx;

    for (idx = 0; idx < builtin_nmemb; idx++) {
        if (!strcmp(args[0], builtin_fname[idx])) {
            builtin_func[idx](args);
            return true;
        }
    }

    return false;
}


void cmd_exit(char** args)
{
    if (args[1]) {
        fprintf(stderr, RED"exit: Too many arguments!\n"RES);
        printf("\n"YEL"(Type 'help exit' for related documentation)\n"RES);
        return;
    }

    exit(EXIT_SUCCESS);
}

void cmd_cd(char** args)
{
    if (args[2]) {
        fprintf(stderr, RED"cd: Too many arguments!\n"RES);
        printf("\n"YEL"(Type 'help cd' for related documentation)\n"RES);
        return;
    }

    if (!strcmp(args[1], "~")) {
        chdir(getenv("HOME"));
        return;
    }

    if (chdir(args[1]) == -1)
        fprintf(stderr, RED"cd: The directory %s does not exist!\n"RES,
                args[1]);
}

void cmd_help(char** args)
{

}