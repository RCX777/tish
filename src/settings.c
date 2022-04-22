#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>

#include "../include/settings.h"
#include "../include/colors.h"

#define HOSTNAMESIZE      256
#define PATHSIZE          512

#define BUFSIZE           2048
#define SAFE_STR_FORMAT "%2047s"

#define CONFIG_PATH "/home/rcx/Projects/tish/tish.config"

#define DEFAULT_PROMPT "^BLUE-*user-@-^BLUE-*host-:-^CYAN-*path-^BLUE-_>>_"

#define DEFAULT_HISTSIZE 32

#define DEFAULT_CONFIG \
"\n\
# Default config for tish. Items must be encased in square brackets, followed\n\
# by a whitespace and the setting.\n\
\n\
# Prompt syntax: separate each token with dashes, set text color with '^WHITE',\n\
# '^BLUE', etc for the next token. You can also print the current user, hostname\n\
# or directory path with '*user', '*host' or '*path'. Use underscores instead of spaces\n\n\
[Prompt] "DEFAULT_PROMPT"\n\
\n\
# InitMessage: Changes the text displayed on shell initialization. If you want to\n\
# remove this, you can set the value to NoDisplay. You can also set colors!\n\n\
[InitMessage] Welcome to ^BLUE tish, The Tiny Shell for Linux!\n\
\n\
# CommandHistorySize: Sets a limit for the number of commands to be stored in the history.\n\n\
[CommandHistorySize] 64\n\
"

enum enumsettings {
    prompt,
    histsize,
    init_message,
};

static const char* setting_list[] = {
    [prompt]       = "[Prompt]",
    [histsize]     = "[CommandHistorySize]",
    [init_message] = "[InitMessage]"
};

static size_t num_of_settings = sizeof(setting_list) / sizeof(char*);


/* Creates a default configuration file */
static void create_default_cfg(void)
{
    printf("Cannot find configuration file! Creating default at %s ...\n", CONFIG_PATH);

    FILE* fp = fopen(CONFIG_PATH, "w");

    if (!fp) {
        SET_RED();
        perror("fopen() failed!");
        fprintf(stderr, "Failure! Could not create a default configuration! Terminating shell...\n");
        RESET_COLOR();
        exit(errno);
    }

    fprintf(fp, "%s", DEFAULT_CONFIG);

    fclose(fp);

    printf("Done!\n");
}

/* Handles errors while interpreting the configuration file */
static void config_error(FILE* fp, settings_t* settings, char* buffer)
{
    SET_RED();
    printf("Terminating shell...\n");
    RESET_COLOR();
    free(settings);
    free(buffer);
    fclose(fp);
    exit(EXIT_FAILURE);
}

/* Converts a prompt format from config into the actual prompt to be printed */
static void set_prompt(settings_t* settings, char* format)
{
    settings->prompt    = malloc(sizeof(char) * BUFSIZE);
    settings->prompt[0] = '\0';

    char* saveptr = format;
    char* token;

    bool set_color_flag = false;

    while ((token = strtok_r(saveptr, "-", &saveptr))) {
        // Convert underscores to whitespaces
        for (size_t index = 0; index < strlen(token); index++)
            if (token[index] == '_')
                token[index]  = ' ';

        switch (token[0]) {
        // Colors
        case '^':
            if (set_color_flag) // Don't do anything if color is already set
                continue;

            set_str_color(settings->prompt, token + sizeof((char) '^'));
            set_color_flag = true;
            continue;
        // Special tokens
        case '*':
            if (!strcmp(token + sizeof((char) '*'), "user")) {
                strcat(settings->prompt, getenv("USER"));

            } else if (!strcmp(token + sizeof((char) '*'), "host")) {
                gethostname(settings->prompt + strlen(settings->prompt), HOSTNAMESIZE);

            } else if (!strcmp(token + sizeof((char) '*'), "path")) {
                char* path = getcwd(NULL, PATHSIZE);
                strcat(settings->prompt, path);
                free(path);

            } else {
                strcat(settings->prompt, token);
            }
            break;
        // Ordinary characters
        default:
            strcat(settings->prompt, token);
        }

        if (set_color_flag) {
            RESET_STR_COLOR(settings->prompt);
            set_color_flag = false;
        }
    }
}

void set_init_message(settings_t* settings, char* message)
{
    settings->init->message    = malloc(sizeof(char) * BUFSIZE);
    settings->init->message[0] = '\0';

    char* saveptr = message;
    char* token;

    bool set_color_flag = false;

    while ((token = strtok_r(saveptr, " ", &saveptr))) {
        if (token[0] == '^') {
            set_str_color(settings->init->message, token + sizeof((char) '^'));
            set_color_flag = true;
            continue;
        }

        strcat(settings->init->message, token);
        strcat(settings->init->message, " ");

        if (set_color_flag) {
            RESET_STR_COLOR(settings->init->message);
            set_color_flag = false;
        }
    }

    strcat(settings->init->message, "\n\n");
}

/* Reads the configuration file and populates a settings_t structure. If no configuration
 * file is present, then it is created with default settings, or if the configuration is
 * not correct, then the shell is terminated.*/
settings_t* get_settings(void)
{
    // Test if config file exists, if not then create a default configuration
    if (access(CONFIG_PATH, F_OK))
        create_default_cfg();
    
    FILE* fp = fopen(CONFIG_PATH, "r");

    if (!fp) {
        perror("fopen() failed!");
        fprintf(stderr, "Failure! Could not open the configuration file! Terminating shell...\n");
        exit(errno);
    }

    settings_t* settings = malloc(sizeof(settings_t));
    char*       buffer   = malloc(BUFSIZE * sizeof(char));

    settings->init       = malloc(sizeof(init_fields));
    settings->histsize   = DEFAULT_HISTSIZE;

    // Read config file
    while (fscanf(fp, SAFE_STR_FORMAT, buffer) != EOF) {
        // Skip comment
        if (buffer[0] == '#') {
            fscanf(fp, "%*[^\n]\n");
            continue;
        }

        size_t switch_arg = -1;

        for (size_t index = 0; index < num_of_settings; index++) {
            if (!strcmp(buffer, setting_list[index]))
                switch_arg = index;
        }

        switch (switch_arg) {
        case prompt:
            fscanf(fp, SAFE_STR_FORMAT, buffer);
            set_prompt(settings, buffer);
            break;
        case init_message:
            fscanf(fp, "%[^\n]\n", buffer);
            set_init_message(settings, buffer);
            break;
        case histsize:
            fscanf(fp, "%zu", &(settings->histsize));
            break;
        default:
            if (buffer[0] == '[')
                printf("Unknown setting: '%s'\n", buffer);
        }
    }

    free(buffer);
    fclose(fp);

    return settings;
}

void clean_junk_after_init(settings_t* settings)
{
    free(settings->init->message);
    free(settings->init);

    settings->prompt = realloc(settings->prompt, strlen(settings->prompt) + sizeof((char) '\0'));
}

void clean_settings(settings_t* settings)
{
    free(settings->prompt);
    free(settings);
}