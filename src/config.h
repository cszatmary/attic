#ifndef ATTIC_CONFIG_H
#define ATTIC_CONFIG_H

#include "error.h"

// config_init loads and initializes the global user configuration.
// This function is idempotent, calling it multiple times will no-op.
enum ErrorCode config_init(void);

// config_install_location returns the path where attic should install programs.
const char *config_install_location(void);

#endif  // ATTIC_CONFIG_H
