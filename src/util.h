#ifndef ATTIC_UTIL_H
#define ATTIC_UTIL_H

#include <sds/sds.h>
#include <stdbool.h>

#include "error.h"

// file_exists checks whether or not a file exists.
// If an error occurs, false will be returned.
bool file_exists(const char *name);

// home_dir returns the absolute path to the user's home directory.
// This will first check the $HOME environment variable.
// If that is empty, then getpwuid will be used to retrive it from
// /etc/passwd.
const char *home_dir(void);

// read_file reads the entire file into the dynamic string
// pointed to by data. If data points to NULL it will be initialized.
// If an error occurs the appropriate ErrorCode will be returned.
// It is the caller's responsibility to free data, whether or not an error
// occurred.
enum ErrorCode read_file(const char *name, sds *data);

// copy_file copies the file at src_path to dest_path.
// If a file already exists at dest_path it will be overwritten.
enum ErrorCode copy_file(const char *src_path, const char *dest_path);

#endif  // ATTIC_UTIL_H
