#pragma once

typedef struct init_fields {
    char*        message;
}   init_fields;

typedef struct settings {
    init_fields* init;
    char*        prompt;
    size_t       histsize;
}   settings_t;

settings_t* get_settings(void);

void clean_settings(settings_t* settings);

void clean_junk_after_init(settings_t* settings);