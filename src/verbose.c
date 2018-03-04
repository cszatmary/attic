//
// Created by Christopher Szatmary on 2018-03-03.
//

#include <stdarg.h>
#include "verbose.h"

bool verbose = false;

/// Toggles verbose mode on or off
void set_verbose(bool value) {
    verbose = value;
}

/// Writes output of a given format to the given file if verbose mode is on
int fverbose_print(FILE *stream, const char *restrict format, ...) {
    if (!verbose) {
        return 0;
    }

    va_list args;
    va_start(args, format);
    int status = vfprintf(stream, format, args);
    va_end(args);

    return status;
}

/// Writes output of a given format to stdout if verbose mode is on
int verbose_print(const char *restrict format, ...) {
    if (!verbose) {
        return 0;
    }

    va_list args;
    va_start(args, format);
    int status = vprintf(format, args);
    va_end(args);

    return status;
}