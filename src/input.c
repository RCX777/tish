#include <stdio.h>

#include <input.h>
#include <dllist.h>

void trim_leading_space(dll_t* line)
{
    if (!line || !(line->size))
        return;
    
    while ((line->head->item) == ' ' && (line->size))
        dll_delete_first(line);
}

void getinput(settings_t* settings, cqu_t* history)
{
    // Display the prompt
    char*  prompt = update_prompt(settings);
    printf("%s", prompt);

    ssize_t linecursor = 0;
    dll_t*  line = dll_create();
    int     ch   = 0;

    // Disables echoing done by the OS
    // set_io_echo_mode(settings, false);

    while ((ch = getchar()) != EOF && ch != '\n') {
        // Handle special characters
        // BIG TODO

        dll_insert_last(line, ch);
    }

    trim_leading_space(line);

    if (line->size != 0)
        cqu_enqueue(history, line);
    else
        dll_destroy(line);
    
    // reset_io_settings(settings);
}