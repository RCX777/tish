#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <signal.h>

#include <input.h>
#include <init.h>

int main(int argc __attribute__((unused)), char** argv)
{
   // Initialize shell
   init_shell();

   // TODO (run command loop) 
   while (1) {
      getinput();
   }

   // TODO (free remaining used memory)
}
