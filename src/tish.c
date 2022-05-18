//
// The main loop of the tish program.
/*
Copyright (C) 2021-2022 Robert-Ioan Constantinescu

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License version 2 as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "utils.h"
#include "input.h"
#include "parse.h"
#include "exec.h"

#define   INPUT_MAX_SIZE 1024

int main (int UNUSED argc, char** UNUSED argv)
{
    char  input[INPUT_MAX_SIZE];
    char* args_piped[MAX_ARGS];
    char* args[MAX_ARGS];

    int   exec_flag;

    // Execute program argument if given
    if (argc > 1 && !strcmp(argv[1], "-c")) {
        char command[INPUT_MAX_SIZE];
        *command = 0;

        int  idx;

        for (idx = 2; idx < argc; idx++) {
            strcat(command, argv[idx]);
            strcat(command, " ");
        }

        exec_flag = process_input(command, args, args_piped);

        if (exec_flag == NOT_PIPED)
            exec_args(args);
        
        if (exec_flag == PIPED)
            exec_args_piped(args, args_piped);

        return EXIT_SUCCESS;
    }

    // Main command loop
    for (;;) {
        if (get_input(input))
            continue;

        /* exec_flag takes the following values:
         *  -> -1 for a command with too many pipes
         *  ->  0 for an empty or builtin command
         *  ->  1 for a command without pipes
         *  ->  2 for a command with pipes
         */
        exec_flag = process_input(input, args, args_piped);

        if (exec_flag == NOT_PIPED)
            exec_args(args);

        if (exec_flag == PIPED)
            exec_args_piped(args, args_piped);
    }

    // This point should never be reached
    return EXIT_FAILURE;
}