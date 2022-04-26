#pragma once

#include <stdio.h>
#include <termios.h>

typedef struct termios termios_t;
typedef struct init_fields {
    char*        message;
    size_t       histsize;
}   init_fields;

typedef struct settings {
    init_fields* init;
    termios_t*   _os_new;
    termios_t*   _os_old;
    char*        prompt;
}   settings_t;

void get_settings(void);

void set_io_echo_mode(int echo);

void reset_io_settings(void);

void clean_settings(void);

void clean_junk_after_init(void);