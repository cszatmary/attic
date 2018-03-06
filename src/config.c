//
// Created by Christopher Szatmary on 2018-02-18.
//

#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "config.h"
#include "verbose.h"

#define INSTALL_LOCATION "/usr/local/attic"
#define LINK_PATH "/usr/local/bin"

const attic_config *config_data = NULL;
attic_config *config = NULL;

int init_config() {
    verbose_print("Initializing config struct\n");

    // Check if config already exists
    if (config != NULL) {
        fprintf(stderr, "ERROR: config struct has already been initialized!\n");
        return EEXIST;
    }

    config = malloc(sizeof(attic_config));

    // Make sure malloc was successful
    if (config == NULL) {
        fprintf(stderr, "Error occurred while generating config.\n%s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    // Initialize config
    config->install_location = INSTALL_LOCATION;
    config->link_path = LINK_PATH;

    config_data = config;

    return EXIT_SUCCESS;
}

void free_config() {
    verbose_print("Freeing config struct\n");
    free(config);
}
