// Parses input into arguments and feeds data to the built-in handler

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "utils.h"
#include "builtin.h"
#include "colors.h"
#include "parse.h"


/* Function that parses command 'words' from an input, may it be piped or
 * not piped. Words encased inside quotation marks are considered
 * arguments, even though they contain spaces.
 */
static void parse_delims(char* input, char** args)
{
    size_t idx = 0;

    args[0] = strmbtok(input, " ", "\"", "\"");

    while (args[idx]) {
        args[++idx] = strmbtok(NULL, " ", "\"", "\"");

        // Do not store empty tokens into @args
        if (args[idx] && !*args[idx])
            idx--;
    }
}

/* Function that searches for the pipe symcol '|' and returns:
 * 1  -> pipe is found
 * 0  -> no pipe
 * -1 -> Too many pipes
 * 
 * The functions also stores a pointer to each command.
 */
static int parse_pipe(char* input, char** cmdpiped)
{
    if (strcount_s(input, '|', 1) == -1) {
        fprintf(stderr,
                RED"Too many pipe symbols! Allowed maximum is 2!\n"RES);
        return -1;
    }

    char* rest = input;

    cmdpiped[0] = strtok_r(rest, "|", &rest);
    cmdpiped[1] = strtok_r(rest, "|", &rest);

    if (cmdpiped[1])
        return 1;
    else
        return 0;
}

static void clear_args(char** args)
{
    size_t idx;

    for (idx = 0; idx < MAX_ARGS && args[idx]; idx++)
        args[idx] = NULL;
}

int process_input(char* input, char** args, char** args_piped)
{
    clear_args(args);
    clear_args(args_piped);

    char* cmdpiped[2];

    int   piped = parse_pipe(input, cmdpiped);

    switch (piped) {
    case -1:
        return ERRPIPE;  // Too many pipes!
    case  0:
        parse_delims(input, args);
        break;
    case  1:
        parse_delims(cmdpiped[0], args);
        parse_delims(cmdpiped[1], args_piped);
    }

    if (builtin_handler(args))
        return BUILTIN;
    else
        return NOT_PIPED + piped; // Returns either PIPED or NOT_PIPED
}