#include <stdio.h>
#include <string.h>

#include <colors.h>

enum enumcolors {
    reset,
    black,
    red,
    green,
    yellow,
    blue,
    purple,
    cyan,
    white
};

static const char* colors[] = {
    [reset]  = "RESET",
    [black]  = "BLACK",
    [red]    = "RED",
    [green]  = "GREEN",
    [yellow] = "YELLOW",
    [blue]   = "BLUE",
    [purple] = "PURPLE",
    [cyan]   = "CYAN",
    [white]  = "WHITE"
};

static size_t num_of_colors = sizeof(colors) / sizeof(char*);

void set_color(const char* color)
{
    size_t switch_arg = -1;

    for (size_t index = 0; index < num_of_colors; index++) {
        if (!strcmp(color, colors[index]))
            switch_arg = index;
    }

    switch (switch_arg) {
    case reset:
        RESET_COLOR();
        return;
    case black:
        SET_BLACK();
        return;
    case red:
        SET_RED();
        return;
    case green:
        SET_GREEN();
        return;
    case yellow:
        SET_YELLOW();
        return;
    case blue:
        SET_BLUE();
        return;
    case purple:
        SET_PURPLE();
        return;
    case cyan:
        SET_CYAN();
        return;
    case white:
        SET_WHITE();
        return;
    }
}

void set_str_color(char* str, const char* color)
{
    size_t switch_arg = -1;

    for (size_t index = 0; index < num_of_colors; index++) {
        if (!strcmp(color, colors[index]))
            switch_arg = index;
    }

    switch (switch_arg) {
    case reset:
        RESET_STR_COLOR(str);
        return;
    case black:
        SET_STR_BLACK(str);
        return;
    case red:
        SET_STR_RED(str);
        return;
    case green:
        SET_STR_GREEN(str);
        return;
    case yellow:
        SET_STR_YELLOW(str);
        return;
    case blue:
        SET_STR_BLUE(str);
        return;
    case purple:
        SET_STR_PURPLE(str);
        return;
    case cyan:
        SET_STR_CYAN(str);
        return;
    case white:
        SET_STR_WHITE(str);
        return;
    }
}