#pragma once

#include <colors.h>
#include <stdbool.h>
#include <errno.h>

#define ERR_CONFIG_CREATE "Failure! Could not create a default configuration! Terminating shell..."
#define ERR_CONFIG_OPEN   "Failure! Could not open the configuration file! Terminating shell..."

#define ERR_FOPEN(fp, description)                                                 \
            do {                                                                    \
                if (!fp) {                                                          \
                    fprintf(stderr, "(%s, %d): ", __FILE__, __LINE__);              \
                    perror("fopen");                                                \
                    fprintf(stderr, "\n"ANSI_RED"%s"ANSI_RESCLR"\n", description);  \
                    exit(errno);                                                    \
                }                                                                   \
            } while(false)


