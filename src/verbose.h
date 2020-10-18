#ifndef ATTIC_VERBOSE_H
#define ATTIC_VERBOSE_H

#include <stdbool.h>
#include <stdio.h>

// set_verbose toggles verbose mode on or off.
void set_verbose(bool value);

// fverbose_printf is like fprintf but only prints if verbose mode is on.
int fverbose_printf(FILE *stream, const char *restrict format, ...);

// verbose_printf is like printf but only prints if verbose mode is on.
int verbose_printf(const char *restrict format, ...);

#endif  // ATTIC_VERBOSE_H
