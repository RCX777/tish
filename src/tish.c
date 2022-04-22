#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/settings.h"
#include "../include/init.h"

int main(int argc __attribute__((unused)), char** argv)
{
   // Initialize shell
   settings_t* settings;
   char command[1000];

   init_shell(&settings);

   // for debugging some stuff
   printf("HISTSIZE = %zu\n\n", settings->histsize);
   size_t promptsize = strlen(settings->prompt) + 1;
   size_t sett_size = sizeof(settings_t) + promptsize;
   printf("Size of prompt = %zu\n", promptsize);
   printf("Total memory occupied by settings: %zu bytes.\n\n", sett_size);

   // TODO (run command loop) 
   for (;;) {
      printf("%s", settings->prompt);

      // TODO
      fgets(command, 999, stdin);

      if (strstr(command, "exit")) {
         clean_settings(settings);
         return EXIT_SUCCESS;
      }

      // TODO
      system(command);
   }
}
