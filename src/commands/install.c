//
// Created by Christopher Szatmary on 2018-02-19.
//

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "install.h"
#include "config.h"
#include "verbose.h"

/* Steps taken by install function
 * Check if file is already installed
 * Check if file exists
 * Check that it's an executable
 * Check that the install directory exists
 * Copy executable to install directory
 * symlink executable to /usr/local/bin
 */

int install(const char *file_name) {
    struct stat sb;

    char path[PATH_SIZE];
    join_path(config_data->install_location, file_name, path, PATH_SIZE);

    verbose_print("Checking if %s is already installed\n", file_name);
    if (check_file_exists(path)) {
        printf("%s is already installed!\nTo install a new version use 'attic update'\n", file_name);
        return EXIT_SUCCESS;
    }

    printf("Installing %s ...\n", file_name);
    verbose_print("Checking %s\n", file_name);

    // Check if file exists
    if (stat(file_name, &sb) == -1) {
        fprintf(stderr, "ERROR: %s does not exist!\n", file_name);
        return EXIT_FAILURE;
    }

    // Check if user has execute permissions
    verbose_print("Checking if file is executable\n");
    if(!(sb.st_mode & S_IXUSR)) {
        fprintf(stderr, "ERROR: Not a valid executable. Cannot install.\n");
        return EXIT_FAILURE;
    }

    // Check if the install directory exists
    verbose_print("Checking if install directory exists\n");
    if (!check_file_exists(config_data->install_location)) {
        fprintf(stderr, "ERROR: %s does not exist!\nRun 'attic setup' to set it up\n", config_data->install_location);
        return EXIT_FAILURE;
    }

    verbose_print("Install directory exists\n");

    printf("Moving %s to %s\n", file_name, config_data->install_location);

    copy_file(file_name, path, MAX_RX_PERM);

    if (symlink_file(file_name, path) == -1) {
        printf("Resolve any issues and try again using 'attic link'\n");
        return EXIT_FAILURE;
    }

    printf("Successfully installed %s!\n", file_name);
    return EXIT_SUCCESS;
}

int link_command(const char *file_name) {
    verbose_print("Finding %s\n", file_name);

    char path[PATH_SIZE];
    join_path(config_data->install_location, file_name, path, PATH_SIZE);

    // Check if file exists
    if (!check_file_exists(path)) {
        fprintf(stderr, "ERROR: %s does not exist!\nRun 'attic install [FILE]' to install it\n", file_name);
        return EXIT_FAILURE;
    }

    return symlink_file(file_name, path) == -1 ? EXIT_FAILURE : EXIT_SUCCESS;
}

int symlink_file(const char *file_name, const char *full_path) {
    printf("Symlinking %s to %s\n", file_name, link_path);

    char symlink_path[PATH_SIZE];
    join_path(link_path, file_name, symlink_path, PATH_SIZE);

    if (check_file_exists(symlink_path)) {
        printf("%s is already symlinked to %s!\n", file_name, link_path);
        return EXIT_SUCCESS;
    }

    int status = symlink(full_path, symlink_path);

    if (status == -1) {
        fprintf(stderr, "Error occurred while symlinking:\n%s\n", strerror(errno));
    } else {
        printf("Successfully symlinked %s to %s\n", file_name, symlink_path);
    }

    return status;
}
