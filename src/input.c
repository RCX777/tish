#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../include/settings.h"
#include "../include/dllist.h"
#include "../include/input.h"

#define BUFSIZE 1024

char* getinput(settings_t* settings)
{
    char* prompt = update_prompt(settings);
    printf("%s", prompt);

    dll_t* dll = dll_create();

    // set_io_echo_mode(settings, false);

    int ch = 0;

    while (ch != '\n')
    {
        ch = getchar();
        dll_insert_last(dll, ch);
    }

    char* str = dll_to_str(dll);

    // reset_io_settings(settings);

    free(prompt);

    return str;
}