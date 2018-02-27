//
// Created by Christopher Szatmary on 2018-02-21.
//

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "config.h"
#include "setup.h"

int setup() {
//    generate_new_config();
    const char *install_location =  default_install_location;

    printf("Setting up attic\nCreating install directory at %s\n", install_location);
    if (mkdir(install_location, MAX_RX_PERM) == -1) {
        // Handle mkdir errors
        if (errno == EEXIST) {
            printf("%s exists.\nattic has already been set up.\n", install_location);
            return EXIT_SUCCESS;
        } else if (errno == EACCES) {
            fprintf(stderr, "ERROR: You do not have the correct permissions to setup attic.\n"
                           "Please run 'sudo attic setup' to ensure everything can be setup properly\n");
            return EXIT_FAILURE;
        } else {
            fprintf(stderr, "ERROR: %s\n", strerror(errno));
            return EXIT_FAILURE;
        }
    }

    // If sudo attic setup was run change install directory owner to user that made the call
    if (strcmp(getenv("USER"), "root") == 0) {
        printf("Changing owner of %s\n", install_location);
        uid_t uid = (uid_t)strtol(getenv("SUDO_UID"), NULL, 10);
        gid_t gid = (gid_t)strtol(getenv("SUDO_GID"), NULL, 10);
        if (chown(install_location, uid, gid) == -1) {
            fprintf(stderr, "Error changing owner of %s\nError message: %s\n",
                    install_location, strerror(errno));
        }
    }

    printf("Finished setting up attic!\n");
    return EXIT_SUCCESS;
}
