#pragma once

#include <termios.h>

typedef struct termios termios_t;
typedef struct init_fields {
    char*        message;
}   init_fields;

typedef struct settings {
    init_fields* init;
    termios_t*   _os_new;
    termios_t*   _os_old;
    char*        prompt;
    size_t       histsize;
}   settings_t;

settings_t* get_settings(void);

char* update_prompt(settings_t* settings);

void set_io_echo_mode(settings_t* settings, int echo);

void reset_io_settings(settings_t* settings);

void clean_settings(settings_t* settings);

void clean_junk_after_init(settings_t* settings);