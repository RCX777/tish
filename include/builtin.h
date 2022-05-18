// Handling of built-in commands

#pragma once


#include <stdbool.h>


bool builtin_handler(char** args);

void builtin_cmd_exit(char** args);

void builtin_cmd_cd(char** args);

void builtin_cmd_help(char** args);

void builtin_cmd_clear(char** args);
