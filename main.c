#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include "utils.h"
#include "config.h"
#include "verbose.h"
#include "commands.h"

typedef int (*command_func)(const char*);

const char *attic_version = "attic -- version 0.1.0";

void print_usage() {
    fprintf(stderr, "Usage: attic [OPTION] [COMMAND] [FILE]\nTry 'attic --help' for more information.\n");
}

int main(int argc, char **argv) {

    int opt;
    int show_version; // Option flags

    struct option long_options[] = {
            {"verbose", no_argument, NULL, 'v'},
            {"version", no_argument, &show_version, 1},
            {"help", no_argument, NULL, 'h'},
            {0, 0, 0, 0}
    };

    // Check options
    while ((opt = getopt_long(argc, argv, "vh", long_options, NULL)) != -1) {
        switch (opt) {
            case 0:
                if (show_version) {
                    printf("%s\n", attic_version);
                    return EXIT_SUCCESS;
                }
                break;
            case 'v':
                set_verbose(true);
                break;
            case 'h':
                help();
                return EXIT_SUCCESS;
            case '?':
            default:
                return EXIT_FAILURE;
        }
    }

    // Check that other arguments were passed
    if (optind >= argc) {
        print_usage();
        return EXIT_FAILURE;
    }

    // Get command and file name
    // If no file name is given then the value will be NULL since the last argument is always NULL
    const char *command_name = argv[optind++];
    const char *file_name = argv[optind];
    command_func command;
    bool file_required = true;

    init_config();

    // Check which command was given and set the appropriate function to execute
    if (strcmp(command_name, "install") == 0) {
        command = install;
    } else if (strcmp(command_name, "uninstall") == 0) {
        command = uninstall;
    } else if (strcmp(command_name, "link") == 0) {
        command = link_command;
    } else if (strcmp(command_name, "unlink") == 0) {
        command = unlink_command;
    } else if (strcmp(command_name, "setup") == 0) {
        command = setup;
        file_required = false;
    } else if (strcmp(command_name, "list") == 0) {
        command = list_dir_contents;
        file_required = false;
    } else {
        fprintf(stderr, "ERROR: Unrecognized command '%s'\nTry 'attic --help' for more information.\n", command_name);
        return EXIT_FAILURE;
    }

    if (file_required && file_name == NULL) {
        print_usage();
        return EXIT_FAILURE;
    } else if (!file_required && file_name != NULL) {
        fprintf(stderr, "Error: %s does not required additional arguments.\n", command_name);
        return EXIT_FAILURE;
    } else if (file_name == NULL) {
        file_name = config_data->install_location;
    }

    command(file_name);

    // Cleanup
    free_config();

    return EXIT_SUCCESS;
}
