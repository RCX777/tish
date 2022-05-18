// Responsible for getting the inputs and storing the command history

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "utils.h"
#include "prompt.h"
#include "input.h"


bool get_input(char* input)
{
    char* buffer = readline(get_prompt());

    char* line   = skip_trailing_delims(buffer, ' ');

    if (line && strlen(line)) {
        add_history(line);
        strcpy(input, line);

        free(buffer);

        return EXIT_SUCCESS;
    }

    // Should only be reached in case of an empty line
    free(buffer);
    return EXIT_FAILURE;
}
