#include <stdio.h>

#include <init.h>
#include <dllist.h>

#define clrscr() printf("\e[1;1H\e[2J")

void init_shell(settings_t** settings, cqu_t** history)
{
    // Gets the settings from the configuration file
    *settings = get_settings();

    // Initializes the command history queue
    *history  = cqu_create((*settings)->histsize, &dll_destroy);

    // Clear the screen and print initial message
    clrscr();
    printf("%s", (*settings)->init->message);

    // Free data that is no longer needed
    clean_junk_after_init(*settings);
}