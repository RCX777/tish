#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

#include <input.h>
#include <init.h>

typedef cqu_t history_t;

static volatile sig_atomic_t keep_running = true;

static void sig_interrupt_handler(int _)
{
   (void)_;
   keep_running = false;
}

int main(int argc __attribute__((unused)), char** argv)
{
   // Handle interrupt
   signal(SIGINT, sig_interrupt_handler);

   // Initialize shell
   settings_t* settings = NULL;
   history_t*  history  = NULL;

   init_shell(&settings, &history);

   // for debugging some stuff
   // printf("HISTSIZE = %zu\n\n", settings->histsize);
   // size_t promptsize = strlen(settings->prompt) + 1;
   // size_t sett_size = sizeof(settings_t) + promptsize;
   // printf("Size of prompt = %zu\n", promptsize);
   // printf("Total memory occupied by settings: %zu bytes.\n\n", sett_size);

   // TODO (run command loop) 
   while (keep_running) {
      getinput(settings, history);
   }

   // TODO (free remaining used memory)
}
