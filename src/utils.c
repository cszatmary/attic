//
// Created by Christopher Szatmary on 2018-02-18.
//

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include "utils.h"

bool verbose = false;

/// Creates a copy of a file at the given destination.
int copy_file(const char *file_name, const char *destination, mode_t permissions) {
    int src_file_descriptor, dest_file_descriptor;
    ssize_t num_bytes_read;
    unsigned char buffer[BUFFER_SIZE];
    int status = EXIT_SUCCESS;

    // Open source file and create copy file
    src_file_descriptor = open(file_name, O_RDONLY);
    dest_file_descriptor = open(destination, O_WRONLY | O_CREAT | O_EXCL, permissions);

    // Check if there was an error creating the file
    if (dest_file_descriptor == -1) {
        status = ERROR_CREATE;
    }

    // While bytes are successfully being read into buffer
    while (num_bytes_read = read(src_file_descriptor, buffer, sizeof buffer), num_bytes_read > 0 && status == EXIT_SUCCESS) {

        // Try writing to the file
        ssize_t num_bytes_written = write(dest_file_descriptor, buffer, (size_t) num_bytes_read);

        // Handle write error
        if (num_bytes_written == -1) {
            status = ERROR_WRITE;
            break;
        }
    }

    // Check if there was a read error
    if (num_bytes_read == -1) {
        status = ERROR_READ;
    }

    int error = errno;

    close(src_file_descriptor);
    close(dest_file_descriptor);

    // Set errno to any previously saved error
    // This way any errors from close are ignored as they generally are of no consequence
    // any previous errors are of greater concern
    errno = error;

    return status;
}

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

/// Returns the absolute path to the user's home directory
char* get_home_dir() {
    char *home_dir = getenv("HOME");

    if (home_dir == NULL) {
        home_dir = getpwuid(getuid())->pw_dir;
    }

    return home_dir;
}

/// Checks whether or not a file exists.
bool check_file_exists(const char *file_name) {
    struct stat config_stats;

    if (stat(file_name, &config_stats) == -1) {
        return false;
    } else {
        return true;
    }
}

int join_path(const char *path, const char *sub_path, char *full_path, size_t buffer_size) {
    int len = snprintf(full_path, buffer_size, "%s/%s", path, sub_path);
    return len <= buffer_size ? EXIT_SUCCESS : EXIT_FAILURE;
}
