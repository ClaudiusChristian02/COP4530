/* 
     ansicodes.h
     http://en.wikipedia.org/wiki/ANSI_escape_code#Colors

     see ansicodes.cpp for demo program

*/

#ifndef _ANSI_CODES_H
#define _ANSI_CODES_H

/* notes:

   "\x" signals beginning of a hexadecimal value
   "\x1b" is ascii character 1b(hex) = 27(dec) - this is ESC, the "escape" character
   "\e"   is an alias for "\x1b"

   http://en.cppreference.com/w/cpp/language/ascii

#define ANSI_RED     "\x1b[31m" // alternative 1
#define ANSI_RED     "\e[31m"   // alternative 2
*/

// foreground colors
#define ANSI_RED     "\e[31m"
#define ANSI_GREEN   "\e[32m"
#define ANSI_YELLOW  "\e[33m"
#define ANSI_BLUE    "\e[34m"
#define ANSI_MAGENTA "\e[35m"
#define ANSI_CYAN    "\e[36m"

// background colors
#define ANSI_BGBLACK   "\e[40m"
#define ANSI_BGRED     "\e[41m"
#define ANSI_BGGREEN   "\e[42m"
#define ANSI_BGYELLOW  "\e[43m"
#define ANSI_BGBLUE    "\e[44m"
#define ANSI_BGMAGENTA "\e[45m"
#define ANSI_BGCYAN    "\e[46m"

// attributes
#define ANSI_BOLD            "\e[1m"
#define ANSI_DIM             "\e[2m"
#define ANSI_UNDERLINE       "\e[4m"
#define ANSI_BLINK           "\e[5m"
#define ANSI_REVERSE         "\e[7m"
#define ANSI_HIDDEN          "\e[8m"

// reset
#define ANSI_RESET_ALL        "\e[0m"
#define ANSI_RESET_BOLD       "\e[21m"
#define ANSI_RESET_DIM        "\e[22m"
#define ANSI_RESET_UNDERLINE  "\e[24m"
#define ANSI_RESET_BLINK      "\e[25m"
#define ANSI_RESET_REVERSE    "\e[27m"
#define ANSI_RESET_HIDDEN     "\e[28m"

#define ANSI_BOLD_BLACK   "\e[1m\e[30m"
#define ANSI_BOLD_RED     "\e[1m\e[31m"
#define ANSI_BOLD_GREEN   "\e[1m\e[32m"
#define ANSI_BOLD_YELLOW  "\e[1m\e[33m"
#define ANSI_BOLD_BLUE    "\e[1m\e[34m"
#define ANSI_BOLD_MAGENTA "\e[1m\e[35m"
#define ANSI_BOLD_CYAN    "\e[1m\e[36m"

#define ANSI_BOLD_BLUE_SHADED "\e[1m\e[34m\e[43m"
#define ANSI_BOLD_RED_SHADED  "\e[1m\e[31m\e[43m"

#endif
