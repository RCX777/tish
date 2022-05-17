// Handling of built-in commands

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "colors.h"
#include "utils.h"
#include "builtin.h"

#define  MAX_DIR_LEN 512


enum builtin_idx {
    _exit_,
    cd,
    help,
    clear
};

static char* builtin_fname[] = {
    [_exit_] = "exit",
    [cd]     = "cd",
    [help]   = "help",
    [clear]  = "clear"
};

static void (*builtin_func[])(char**) = {
    [_exit_] = builtin_cmd_exit,
    [cd]     = builtin_cmd_cd,
    [help]   = builtin_cmd_help,
    [clear]  = builtin_cmd_clear
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


void builtin_cmd_exit(char** args)
{
    if (args[1]) {
        fprintf(stderr, RED"exit: Too many arguments!\n"RES);
        printf("\n"YEL"(Type 'help exit' for related documentation)\n"RES);
        return;
    }

    exit(EXIT_SUCCESS);
}

void builtin_cmd_cd(char** args)
{
    if (args[2]) {
        fprintf(stderr, RED"cd: Too many arguments!\n"RES);
        printf("\n"YEL"(Type 'help cd' for related documentation)\n"RES);
        return;
    }

    if (!args[1]) {
        chdir(getenv("HOME"));
        return;
    }

    char directory[MAX_DIR_LEN];

    *directory = 0;

    if (strchr(args[1], '~') == args[1]) {
        strcpy(directory, getenv("HOME"));
        args[1]++;
    }

    strcat(directory, args[1]);

    if (chdir(directory) == -1)
        fprintf(stderr, RED"cd: The directory %s does not exist!\n"RES,
                directory);
}

void builtin_cmd_clear(char** args)
{
    if (args[2]) {
        fprintf(stderr, RED"clear: Too many arguments!\n"RES);
        printf("\n"YEL"(Type 'help clear' for related documentation)"RES"\n");
        return;
    }

    // Clears screen while preserving the scrollback buffer 
    if (args[1]) {
        if (!strcmp(args[1], "-x")) {
            printf("\e[1;1H\e[2J");
            return;
        } else {
            fprintf(stderr, RED"clear: Invalid flag!\n\n"RES);
            printf(YEL"(Type 'help clear' for related documentation)"RES"\n");
            return;
        }
    }

    // Clears screen without preserving the scrollback buffer
    printf("\033c");


}

void builtin_cmd_help(char** UNUSED args)
{
    // TODO
}
