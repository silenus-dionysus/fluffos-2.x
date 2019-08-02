/*
 * console.h -- definitions and prototypes for console.c
 *
 */

#ifndef CONSOLE_H
#define CONSOLE_H

#include "options_incl.h"

#ifdef HAS_CONSOLE

class Console {
public:
  void console_command(char *);
};

extern Console globalConsole;
#endif

#endif

