#include <stdio.h>

#include <global.h>
#include <init.h>
#include <dllist.h>

#define clrscr() printf("\e[1;1H\e[2J")

void print_init_message(void)
{
    for (size_t idx = 0; settings.init->message[idx]; idx++) {
        if (settings.init->message[idx] != '\\') {
            putchar(settings.init->message[idx]);
            continue;
        }

        if (!settings.init->message[++idx]) // Exits if '\0' is reached
            return;

        if (settings.init->message[idx] == 'n')
            putchar('\n');
    }
}

void init_shell(void)
{
    // Gets the settings from the configuration file
    get_settings();

    // Clear the screen and print initial message
    clrscr();
    print_init_message();

    // Free data that is no longer needed
    clean_junk_after_init();
}