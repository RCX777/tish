// Parses input into arguments and executes built-in commands

#pragma once


#define   MAX_ARGS         64

#define   ERRPIPE          -1
#define   NULLCMD           0
#define   BUILTIN           0
#define   NOT_PIPED         1
#define   PIPED             2


int process_input(char* input, char** args, char** args_piped);