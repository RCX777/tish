#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>

#include <settings.h>
#include <colors.h>
#include "../include/error.h"

#define CONFIG_PATH "/home/rcx/Projects/tish/tish.config"

#define DEFAULT_PROMPT       ANSI_BLUE"\\u"ANSI_RESCLR"@"ANSI_BLUE"\\h"ANSI_RESCLR":"ANSI_YELLOW"\\w"ANSI_RESCLR"\\$ "
#define DEFAULT_INIT_MESSAGE "Welcome to "ANSI_BLUE"tish"ANSI_RESCLR", The Tiny Shell for Linux!\\n\\n"
#define DEFAULT_HISTSIZE     64

#define DEFAULT_PROMPTSIZE   512

#define DEFAULT_CONFIG \
"\n\
# Config file for tish. Correct syntax for setting options is:\n\
# option = value\n\
\n\
# Prompt option: Sets the prompt, displaying things such as the current user,\n\
# the hostname of the machine, the current path, etc. Syntax is identical to the\n\
# PS1 environment variable used by GNU bash\n\n\
Prompt = "DEFAULT_PROMPT"\n\
\n\
# InitMessage: Changes the text displayed on shell initialization.\n\
# You can also set colors, with ANSI escape sequences. For newlines use \\n.\n\n\
InitMessage = Welcome to "ANSI_BLUE"tish"ANSI_RESCLR", The Tiny Shell for Linux!\\n\\n\n\
\n\
# CommandHistorySize: Sets a limit for the number of commands to be stored in the history.\n\n\
CommandHistorySize = 64\n\
"

settings_t settings;

enum options {
    prompt,
    histsize,
    init_message,
};

static const char* option_list[] = {
    [prompt]       = "Prompt",
    [histsize]     = "CommandHistorySize",
    [init_message] = "InitMessage"
};

static size_t num_of_options = sizeof(option_list) / sizeof(char*);

/* Creates a default configuration file */
static void create_default_cfg(void)
{
    FILE* fp = fopen(CONFIG_PATH, "w");

    ERR_FOPEN(fp, ERR_CONFIG_CREATE);

    fprintf(fp, "%s", DEFAULT_CONFIG);

    fclose(fp);
}

/* Sets the echoing feature of UNIX I/O using termios */
void set_io_echo_mode(int echo)
{
    tcgetattr(STDIN_FILENO, settings._os_old);
    settings._os_new = settings._os_old;

    // Disable buffered I/O and set ECHO mode
    settings._os_new->c_lflag &= ~ICANON;
    settings._os_new->c_lflag &= echo ? ECHO : ~ECHO;

    tcsetattr(STDIN_FILENO, TCSANOW, settings._os_new);
}

/* Resets I/O settings to old value */
void reset_io_settings()
{
    tcsetattr(STDIN_FILENO, TCSANOW, settings._os_old);
}

static bool is_comment(const char* __restrict__ line)
{
    for (size_t idx = 0; line[idx]; idx++) {
        if (line[idx] == '#')
            return true;
        
        if (line[idx] != '#' && line[idx] != ' ' && line[idx] != '\n')
            return false;
    }
}

static char* trim_leading_spaces(char* buffer)
{
    size_t idx = 0;

    for (idx = 0; buffer[idx] == ' ' || buffer[idx] == '\n'; idx++)
        if (!buffer[idx])
            return NULL;
    
    return (buffer + idx);
}

/* Reads the configuration file and populates a settings_t structure. If no configuration
 * file is present, then it is created with default settings, or if the configuration is
 * not correct, then the shell is terminated.*/
void get_settings(void)
{
    // Test if config file exists, if not then create a default configuration
    if (access(CONFIG_PATH, F_OK))
        create_default_cfg();
    
    FILE* fp = fopen(CONFIG_PATH, "r");

    ERR_FOPEN(fp, ERR_CONFIG_OPEN);

    settings._os_old = malloc(sizeof(termios_t));
    settings._os_new = malloc(sizeof(termios_t));
    settings.init    = calloc(1, sizeof(init_fields));
    settings.prompt  = malloc(DEFAULT_PROMPTSIZE * sizeof(char));
    settings.init->histsize = DEFAULT_HISTSIZE;

    char*  buffer = NULL;
    size_t bufsiz = 0;

    while (!feof(fp)) {
        if (!getline(&buffer, &bufsiz, fp))
            continue;
        
        char* line = trim_leading_spaces(buffer);

        if (!line || !*line || is_comment(line))
            continue;


        size_t switch_arg = -1;

        for (size_t idx = 0; idx < num_of_options; idx++)
            if (strstr(line, option_list[idx]) == line) {
                switch_arg = idx;
                line += strlen(option_list[idx]);
                break;
            }
        
        line = trim_leading_spaces(line);

        if (!(line = strchr(line, '='))) {
            printf(ANSI_RED"Syntax error! No equal sign found!\n");
            printf("Terminating shell...\n"ANSI_RESCLR);
            exit(EXIT_FAILURE);
        }

        line = trim_leading_spaces(++line);

        line[strcspn(line, "\n")] = 0;

        if (!*line)
            continue;

        // printf("%s", line);
        
        switch (switch_arg) {
        case prompt:
            strcpy(settings.prompt, line);
            break;
        case histsize:
            // TODO
            break;
        case init_message:
            settings.init->message = malloc(sizeof(char) * BUFSIZ);
            strcpy(settings.init->message, line);
            break;
        default:
            printf(ANSI_RED"Unknown option!\n");
            printf("Terminating shell...\n"ANSI_RESCLR);
            exit(EXIT_FAILURE);
        }
    }

    free(buffer);
}

void clean_junk_after_init(void)
{
    free(settings.init->message);
    free(settings.init);

    if (!settings.prompt)
        return;

    settings.prompt = realloc(settings.prompt, strlen(settings.prompt) + 1);
}

void clean_settings(void)
{
    free(settings.prompt);
    free(settings._os_old);
    free(settings._os_new);
}