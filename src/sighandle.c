// Handles signals received during input

#include <stdio.h>
#include <stdbool.h>
#include <signal.h>

#include <readline/readline.h>

#include "utils.h"
#include "sighandle.h"


static void sigint_handler(int UNUSED signum)
{
    // Clear old line and variables changed by the sig
    rl_free_line_state();
    rl_cleanup_after_signal();

    // Interrupt readline processes
    RL_UNSETSTATE(RL_STATE_ISEARCH    |
                  RL_STATE_NSEARCH    |
                  RL_STATE_VIMOTION   |
                  RL_STATE_NUMERICARG |
                  RL_STATE_MULTIKEY);

    // Set the first char of the buffer to '\0'
    rl_line_buffer[rl_point = rl_end = rl_mark = 0] = 0;

    // Correctly re-print the prompt as readline does
    printf("\n%s ", rl_prompt);

    // Current situation must be signaled back to readline
    rl_on_new_line_with_prompt();
}

void sig_handler(void)
{
    signal(SIGINT, sigint_handler);
}