//
// Created by Christopher Szatmary on 2018-02-20.
//

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "config.h"
#include "uninstall.h"
#include "verbose.h"

/* Steps taken by uninstall function
 * Check if symlink exists in /usr/local/bin
 * Remove the symlink
 * Check if it exists in the install directory
 * Remove it from the install directory
 */

int uninstall(const char *file_name) {
    printf("Uninstalling %s ...\n", file_name);

    // Get file path in install directory
    char path[PATH_SIZE];
    join_path(config_data->install_location, file_name, path, PATH_SIZE);

    // Make sure file actually exists before attempted removal
    verbose_print("Checking if %s exists\n", file_name);
    if (!check_file_exists(path)) {
        fprintf(stderr, "ERROR: %s is not installed!\n", file_name);
        return EXIT_FAILURE;
    }

    // Remove the symlink from /usr/local/bin first
    remove_symlink(file_name);

    // Remove file from install directory
    verbose_print("Removing %s from %s\n", file_name, config_data->install_location);
    int status = unlink(path);

    // Check if unlink had an error
    if (status == -1) {
        fprintf(stderr, "Error occurred while removing %s:\n%s\n", file_name, strerror(errno));
    } else {
        verbose_print("Successfully removed %s\n", path);
        printf("Successfully uninstalled %s!\n", file_name);
    }

    return status;
}

int unlink_command(const char *file_name) {
    return remove_symlink(file_name) == -1 ? EXIT_FAILURE : EXIT_SUCCESS;
}

int remove_symlink(const char *file_name) {
    printf("Removing symlink from %s\n", config_data->link_path);

    // Get symlink path
    char symlink_path[PATH_SIZE];
    join_path(config_data->link_path, file_name, symlink_path, PATH_SIZE);

    // Remove symlink
    int status = unlink(symlink_path);

    // Check if unlink had an error
    if (status == -1) {
        fprintf(stderr, "Error occurred while deleting symlink:\n%s\n", strerror(errno));
    } else {
        printf("Successfully removed %s\n", symlink_path);
    }

    return status;
}