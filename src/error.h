#ifndef ATTIC_ERROR_H
#define ATTIC_ERROR_H

#include <stdio.h>
#include <stdlib.h>

// ErrorCode identifies the type of error.
enum ErrorCode {
    // ErrNoErr represents no error, i.e. success.
    // This is ugly but necessary.
    ErrNoErr,
    ErrAllocFailed,
    ErrFileCreate,
    ErrFileOpen,
    ErrFileRead,
    ErrFileWrite,
    ErrFileClose,
    ErrFileNotExist,
    ErrFileStat,
    ErrFileNotRegular,
    ErrDirCreate,
    ErrDirOpen,
    ErrConfigParse,
    ErrArgsValidate,
    ErrArgsSome,
    ErrArgsNone,
    ErrArgsInvalid,
};

// error_title returns a human readable description of an ErrorCode.
static inline const char *error_title(enum ErrorCode code) {
    static const char *titles[] = {
        "No error occurred",
        "Memory Allocation Failed",
        "Failed to create file",
        "Failed to open file",
        "Failed to read file",
        "Failed to write to file",
        "Failed to close file",
        "File does not exist",
        "Failed to get information about file",
        "File is not a regular file",
        "Failed to create directory",
        "Failed to open directory",
        "Failed to parse config file",
        "Arguments failed validation",
        "Expected no arguments",
        "Expected arguments",
        "Invalid argument value(s)",
    };
    return titles[code];
}

// eprintf is like printf but prints to stderr.
#define eprintf(...) fprintf(stderr, __VA_ARGS__)

// exitf prints the message to stderr then exits the program with status 1.
#define exitf(...)                \
    fprintf(stderr, __VA_ARGS__); \
    exit(1)

// exitf prints the error and message to stderr then exits the program with
// status 1.
#define exiterrf(code, ...)                            \
    fprintf(stderr, "Error: %s\n", error_title(code)); \
    fprintf(stderr, __VA_ARGS__);                      \
    exit(1)

#endif  // ATTIC_ERROR_H
