//
// Created by Christopher Szatmary on 2019-07-15.
//

#include "utils.h"
#include "config.h"
#include "verbose.h"
#include "reinstall.h"

int reinstall(const char *file_name) {
    struct stat sb;

    // Get install path
    char path[PATH_SIZE];
    join_path(config_data->install_location, file_name, path, PATH_SIZE);

    // Check if file doesn't exist
    verbose_print("Checking that %s is installed\n", file_name);
    if (!check_file_exists(path)) {
        
    }
}