#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>

#include <colors.h>
#include <global.h>
#include <prompt.h>

#define COLOR_CODE_BUFSIZ 64

static void print_user(void)
{
    printf("%s", getenv("USER"));
}

static void print_hostname(void)
{
    char hostname[HOST_NAME_MAX + sizeof((char) '\0')];

    if (gethostname(hostname, HOST_NAME_MAX + sizeof((char) '\0')) == -1)
        return;

    printf("%s", hostname);
}

static void print_cwd(void)
{
    char* cwd;

    if ((cwd = getcwd(NULL, 0))) {
        printf("%s", cwd);
        free(cwd);
    }
}

static void print_privilege(void)
{
    if (getuid())
        putchar('$');
    else
        putchar('#');
}

static void handle_color_codes(size_t* idx)
{
    char color[COLOR_CODE_BUFSIZ]; // Buffer for ANSI color code

    color[0] = '\033';

    size_t color_idx = 1;
    (*idx)++;
        
    while (settings.prompt[*idx] != 'm') {
        if (!settings.prompt[*idx])
            return;

        color[color_idx++] = settings.prompt[(*idx)++];
    }

    color[color_idx++] = 'm';
    color[color_idx]   = '\0';

    printf("%s", color);
}

void print_prompt(void)
{
    for (size_t idx = 0; settings.prompt[idx]; idx++) {
        if (settings.prompt[idx] != '\\') {
            putchar(settings.prompt[idx]);
            continue;
        }

        idx++; // Skips the '\'

        if (!settings.prompt[idx]) // Exits if '\0' is reached
            return;

        switch (settings.prompt[idx]) {
        case 'u':
            print_user();
            break;
        case 'h':
            print_hostname();
            break;
        case 'w':
            print_cwd();
            break;
        case '$':
            print_privilege();
            break;
        case '\\':
            putchar('\\');
            break;
        case 'e':
            handle_color_codes(&idx);
            break;
        }
    }
}