#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <global.h>
#include <input.h>
#include <dllist.h>
#include <prompt.h>

#define HTAB         9
#define ESC         27
#define BACKSPACE  127

#define ARROW_UP    65
#define ARROW_DOWN  66
#define ARROW_RIGHT 67
#define ARROW_LEFT  68

void trim_leading_space(dll_t* line)
{
    if (!line || !(line->size))
        return;
    
    while ((line->head->item) == ' ' && (line->size))
        dll_delete_first(line);
}

void tab_completion(dll_t* line, ssize_t* linecursor)
{
    // TODO
}

void handle_escaped_inputs(dll_t* line, size_t* linecursor)
{
    getchar(); // Skip '[' character

    switch (getchar()) {
    case ARROW_UP:
        // TODO
        break;
    case ARROW_DOWN:
        // TODO
        break;
    case ARROW_LEFT:
        if (*linecursor == 1)
            return;
        printf("\033[1D");
        (*linecursor)--;
        break;
    case ARROW_RIGHT:
        if (*linecursor == line->size + 1)
            return;
        printf("\033[1C");
        (*linecursor)++;
        break;
    default:
        // TODO (other inputs)
    }
}

void save_character(dll_t* line, size_t* linecursor, int ch)
{
    if (*linecursor == line->size + 1) { // cursor at end of line
        dll_insert_last(line, ch);
        putchar(ch);
        (*linecursor)++;
    } else {
        dll_insert_nth_item(line, *linecursor, ch);
        printf("\033[1C");    // increment cursor pos
        printf("\033[s");     // save cursor pos
        printf("\033[0G");    // moves cursor pos to beginning of line
        print_prompt();
        dll_print(line);      // prints the modified list
        printf("\033[u");     // moves the cursor to previous pos
        (*linecursor)++;
    }
}

void remove_character(dll_t* line, size_t* linecursor)
{
    if (*linecursor == 1)
        return;

    if (*linecursor == line->size + 1) { // cursor at end of line
        dll_delete_last(line);
        printf("\033[1D");
        putchar(' ');
        printf("\033[1D");
        (*linecursor)--;
    } else {
        printf("\033[%zuC ", line->size - *linecursor);
        printf("\033[%zuD ", line->size - *linecursor + 2);
        dll_delete_nth_item(line, *linecursor - 1);
        printf("\033[1D\033[s");
        printf("\033[0G");
        print_prompt();
        dll_print(line);
        printf("\033[u");
        (*linecursor)--;
        if (*linecursor == line->size)
            printf("\033[1D");
    }
}

bool is_printable(int ch)
{
    return ((ch >= ' ') && (ch <= '~'));
}

void getinput(void)
{
    print_prompt();

    size_t  linecursor = 1;
    dll_t*  line = dll_create();
    int     ch   = 0;

    // Disables echoing done by the OS
    set_io_echo_mode(false);

    while ((ch = getchar()) != EOF && ch != '\n') {
        if (is_printable(ch)) {
            save_character(line, &linecursor, ch);
            continue;
        }

        switch (ch) {
        case HTAB:
            tab_completion(line, &linecursor); // TODO
            break;
        case ESC:
            handle_escaped_inputs(line, &linecursor);
            break;
        case BACKSPACE:
            remove_character(line, &linecursor);
            break;
        default:
            break; // To add stuff in the future
        }
    }
    putchar('\n');

    trim_leading_space(line);
    
    // dll_print_ascii(line); // DEBUG
    // dll_print(line); printf("\n");

    // Resets IO settings
    reset_io_settings();
}