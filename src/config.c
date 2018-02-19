//
// Created by Christopher Szatmary on 2018-02-18.
//

#include <libconfig.h>
#include <sys/stat.h>
#include <string.h>
#include "utils.h"
#include "config.h"

#define DEFAULT_LOCATION "/usr/local/attic"
#define ATTIC_CONFIG_NAME "attic_config.cfg"

int generate_new_config() {
    verbose_print("Generating config file.\n");

    struct stat config_stats = {};

    // Check if a config file already exists
    if (stat(ATTIC_CONFIG_NAME, &config_stats) != -1) {
        printf("A config file already exists.\nAre you sure you want to recreate it? [y/n] ");
        char choice[3];
        scanf("%s", choice);

        // If user does not respond yes abort the process
        if (strcasecmp(choice, "y") != 0 && strcasecmp(choice, "yes") != 0) {
            verbose_print("Aborting create config.\n");
            return -1;
        }
    }

    // Setup config file and pointers to all entries
    config_t cfg;
    config_setting_t *root, *path_config;

    config_init(&cfg);
    root = config_root_setting(&cfg);

    // Add install location path to config
    verbose_print("Adding intall location to config.\n");
    path_config = config_setting_add(root, "install_location", CONFIG_TYPE_STRING);
    config_setting_set_string(path_config, DEFAULT_LOCATION);

    // Write everything to the config file
    if (!config_write_file(&cfg, ATTIC_CONFIG_NAME)) {

        // Handle any errors
        fprintf(stderr, "Error while writing file.\n");
        config_destroy(&cfg);
        return -1;
    }

    printf("New configuration successfully written to: %s\n", ATTIC_CONFIG_NAME);

    config_destroy(&cfg);

    return 0;
}
