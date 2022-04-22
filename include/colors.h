#pragma once

#define SET_BLACK()   printf("\033[0;30m")
#define SET_RED()     printf("\033[0;31m")
#define SET_GREEN()   printf("\033[0;32m")
#define SET_YELLOW()  printf("\033[0;33m")
#define SET_BLUE()    printf("\033[0;34m")
#define SET_PURPLE()  printf("\033[0;35m")
#define SET_CYAN()    printf("\033[0;36m")
#define SET_WHITE()   printf("\033[0;37m")

#define RESET_COLOR() printf("\033[0m")

#define SET_STR_BLACK(str)   strcat(str, "\033[0;30m")
#define SET_STR_RED(str)     strcat(str, "\033[0;31m")
#define SET_STR_GREEN(str)   strcat(str, "\033[0;32m")
#define SET_STR_YELLOW(str)  strcat(str, "\033[0;33m")
#define SET_STR_BLUE(str)    strcat(str, "\033[0;34m")
#define SET_STR_PURPLE(str)  strcat(str, "\033[0;35m")
#define SET_STR_CYAN(str)    strcat(str, "\033[0;36m")
#define SET_STR_WHITE(str)   strcat(str, "\033[0;37m")

#define RESET_STR_COLOR(str) strcat(str, "\033[0m")

void set_color(const char* color);

void set_str_color(char* str, const char* color);
