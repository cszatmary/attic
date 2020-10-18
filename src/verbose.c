#include "verbose.h"

#include <stdarg.h>

bool verbose = false;

void set_verbose(bool value) { verbose = value; }

int fverbose_printf(FILE *stream, const char *restrict format, ...) {
    if (!verbose) {
        return 0;
    }

    va_list args;
    va_start(args, format);
    int status = vfprintf(stream, format, args);
    va_end(args);

    return status;
}

int verbose_printf(const char *restrict format, ...) {
    if (!verbose) {
        return 0;
    }

    va_list args;
    va_start(args, format);
    int status = vprintf(format, args);
    va_end(args);

    return status;
}
