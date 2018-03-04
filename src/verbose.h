//
// Created by Christopher Szatmary on 2018-03-03.
//

#ifndef ATTIC_VERBOSE_H
#define ATTIC_VERBOSE_H

#include <stdio.h>
#include <stdbool.h>

void set_verbose(bool value);
int fverbose_print(FILE *stream, const char *restrict format, ...);
int verbose_print(const char *restrict format, ...);

#endif //ATTIC_VERBOSE_H
