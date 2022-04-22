#include <stdio.h>

#include "../include/init.h"
#include "../include/settings.h"

#define clrscr() printf("\e[1;1H\e[2J")

void init_shell(settings_t** settings)
{
    // Gets the settings from the configuration file
    *settings = get_settings();

    // Clear the screen and print initial message
    clrscr();

    printf("%s", (*settings)->init->message);

    // Free data that is no longer needed
    clean_junk_after_init(*settings);
}