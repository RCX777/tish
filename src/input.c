#include <stdio.h>

#include <input.h>
#include <dllist.h>

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

void handle_escaped_inputs(dll_t* line, cqu_t* history, size_t* linecursor)
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

void save_character(dll_t* line, size_t* linecursor, const char* prompt, int ch)
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
        printf("%s", prompt); // re-prints the prompt
        dll_print(line);      // prints the modified list
        printf("\033[u");     // moves the cursor to previous pos
        (*linecursor)++;
    }
}

void getinput(settings_t* settings, cqu_t* history)
{
    // Display the prompt
    char*  prompt = update_prompt(settings);
    printf("%s", prompt);

    size_t  linecursor = 1;
    dll_t*  line = dll_create();
    int     ch   = 0;

    // Disables echoing done by the OS
    set_io_echo_mode(settings, false);

    while ((ch = getchar()) != EOF && ch != '\n') {
        switch (ch) {
        case HTAB:
            tab_completion(line, &linecursor);
            break;
        case ESC:
            handle_escaped_inputs(line, history, &linecursor);
            break;
        case BACKSPACE:
            break;
        default:
            save_character(line, &linecursor, prompt, ch);
        }
    }
    putchar('\n');

    trim_leading_space(line);

    if (line->size != 0)
        cqu_enqueue(history, line);
    else
        dll_destroy(line);
    
    dll_print_ascii(line); // DEBUG
    // dll_print(line); printf("\n");

    // Resets IO settings
    reset_io_settings(settings);
}