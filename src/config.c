//
// Created by Christopher Szatmary on 2018-02-18.
//

#include <string.h>
#include <stdlib.h>
#include "config.h"

#define DEFAULT_LOCATION "/usr/local/attic"
#define ATTIC_CONFIG_NAME "attic_config.cfg"
#define ATTIC_VERSION_NUMBER "0.1.0"

#define ATTIC_INSTALL_LOCATION "install_location"

const attic_config *config_data = NULL;
attic_config *config = NULL;

int generate_new_config() {
    verbose_print("Generating config file.\n");

    if (check_file_exists(ATTIC_CONFIG_NAME)) {
        printf("A config file already exists.\nAre you sure you want to recreate it? [y/n] ");
        char choice[3];
        scanf("%s", choice);

        // If user does not respond yes abort the process
        if (strcasecmp(choice, "y") != 0 && strcasecmp(choice, "yes") != 0) {
            verbose_print("Aborting create config.\n");
            return ACTION_ABORTED;
        }
    }

    // Setup config file and pointers to all entries
    config_t cfg;
    config_setting_t *root, *path_config;

    config_init(&cfg);
    root = config_root_setting(&cfg);

    // Add install location path to config
    verbose_print("Adding install location to config.\n");
    path_config = config_setting_add(root, ATTIC_INSTALL_LOCATION, CONFIG_TYPE_STRING);
    config_setting_set_string(path_config, DEFAULT_LOCATION);

    // Write everything to the config file
    verbose_print("Writing to file ...\n");
    if (!config_write_file(&cfg, ATTIC_CONFIG_NAME)) {

        // Handle any errors
        fprintf(stderr, "Error while writing file.\n");
        print_config_error(fverbose_print, stderr, &cfg);
        config_destroy(&cfg);
        return ERROR_WRITE;
    }

    printf("New configuration successfully written to: %s\n", ATTIC_CONFIG_NAME);

    config_destroy(&cfg);

    return EXIT_SUCCESS;
}

int load_config() {
    config_t cfg;

    config_init(&cfg);

    verbose_print("Reading from config file ...\n");
    // Try reading from the config file
    if (!config_read_file(&cfg, ATTIC_CONFIG_NAME)) {

        // Handle errors
        fprintf(stderr, "Error reading the config file.\n");
        print_config_error(fverbose_print, stderr, &cfg);
        config_destroy(&cfg);
        return ERROR_READ;
    }

    verbose_print("Creating config struct\n");
    config = malloc(sizeof(attic_config));

    if (read_config_values(&cfg, config) != EXIT_SUCCESS) {
        verbose_print("Unable to successfully read the config, aborting\n");
        verbose_print("Freeing config struct\n");
        free(config);
        config_destroy(&cfg);
        return ERROR_READ;
    }

    // Assign config to global constant pointer so that it can be read from anywhere but not modified
    config_data = config;

    return EXIT_SUCCESS;
}

int read_config_values(config_t *cfg, attic_config *config_struct) {
    verbose_print("Reading config values\n");

    // Try reading each value from the config file
    // If any of them fail at any point exit the function
    verbose_print("Reading install_location\n");
    if (!config_lookup_string(cfg, ATTIC_INSTALL_LOCATION, &config_struct->install_location)) {
        fprintf(stderr, "Error reading the install_location field from the config.\n");
        return ERROR_READ;
    }

    verbose_print("Finished reading config values successfully\n");
    return EXIT_SUCCESS;
}

void free_config() {
    verbose_print("Freeing config struct\n");
    free(config);
}

int print_config_error(print_func print, FILE *stream, config_t *cfg) {
    return print(stream, "%s:%d - %s\n", config_error_file(cfg), config_error_line(cfg),
          config_error_text(cfg));
}

char* get_version_number() {
    return ATTIC_VERSION_NUMBER;
}
