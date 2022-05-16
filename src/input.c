// Responsible for getting the inputs and storing the command history

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "input.h"
#include "prompt.h"

bool get_input(char* input)
{
    char* buffer = readline(get_prompt());

    if (strlen(buffer)) {
        add_history(buffer);
        strcpy(input, buffer);

        free(buffer);

        return EXIT_SUCCESS;
    }

    free(buffer);

    return EXIT_FAILURE;
}
