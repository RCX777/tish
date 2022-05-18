// Some functions and random stuff I'll use

#include <string.h>


#include "utils.h"


/* Similar to strtok(), but it ignore delims inside blocks. For example, with
 * delim = " "; and block = ", here is how the following string is tokenized
 *
 * Input:
 * 
 * tish -c "ls -alh"
 * 
 * Output:
 * 
 * tish
 * -c
 * ls -alh
 */
char *strmbtok (char *input, char *delim, char *openblock, char *closeblock)
{
    static char *token = NULL;

    char *lead  = NULL;
    char *block = NULL;

    int  i_block = 0;
    int  i_block_index = 0;

    if (input) {
        token = input;
        lead  = input;
    } else {
        lead = token;
        if (*token == '\0')
            lead = NULL;

    }

    while (*token != '\0') {
        if (i_block) {
            if (closeblock[i_block_index] == *token) {
                i_block = 0;
            }
            token++;
            continue;
        }

        if ((block = strchr(openblock, *token)) != NULL) {
            i_block = 1;
            i_block_index = block - openblock;
            token++;
            continue;
        }

        if (strchr(delim, *token) != NULL) {
            *token = '\0';
            token++;
            break;
        }

        token++;
    }

    return lead;
}

/* Returns the number of occurences of 'ch' in 'str'. If this number is greater
 * than 'max_occ', then the counting stops and -1 is returned. To ignore the
 * rule of 'max_occ', you can pass '0' instead.
 */
int strcount_s(char* str, char ch, size_t max_occ)
{
    size_t occ = 0;
    size_t idx;

    for (idx = 0; str[idx]; idx++) {
        if (str[idx] == ch)
            occ++;
        
        if (max_occ && occ > max_occ)
            return -1;
    }

    return occ;
}

/* Returns the address at which the first character different from a delim is
 * found. 
 */
char* skip_trailing_delims(char* str, char delim)
{
    while (str && *str == delim)
        str++;

    return str;
}
