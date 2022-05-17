// Prompt is provided by the Starship Cross-Shell Prompt

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "colors.h"


#define MAX_PROMPT_SIZE 256


char* get_prompt(void)
{
    // Get the prompt from starship
    FILE* fp = popen("starship prompt", "r");

    if (!fp) {
        printf(RED"Failed to get prompt from starship!\n"RES);
        exit(errno);
    }

    static char prompt[MAX_PROMPT_SIZE];
    size_t      idx = 0;
    int         ch;

    // Store the prompt in a static variable
    while (((ch = fgetc(fp)) != EOF) && idx < MAX_PROMPT_SIZE - 1)
        prompt[idx++] = (char) ch;
    
    prompt[idx] = '\0';

    // Close the file pointer associated with the starship process
    pclose(fp);

    return prompt;
}