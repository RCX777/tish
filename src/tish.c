#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/settings.h"
#include "../include/init.h"
#include "../include/input.h"

int main(int argc __attribute__((unused)), char** argv)
{
   // Initialize shell
   settings_t* settings;
   char*       command;

   init_shell(&settings);

   // for debugging some stuff
   // printf("HISTSIZE = %zu\n\n", settings->histsize);
   // size_t promptsize = strlen(settings->prompt) + 1;
   // size_t sett_size = sizeof(settings_t) + promptsize;
   // printf("Size of prompt = %zu\n", promptsize);
   // printf("Total memory occupied by settings: %zu bytes.\n\n", sett_size);

   // TODO (run command loop) 
   for (;;) {
      command = getinput(settings);

      system(command); // TODO: replace this

      free(command);
   }
}
