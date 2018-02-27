#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include "utils.h"
#include "config.h"
#include "install.h"
#include "uninstall.h"
#include "setup.h"
#include "help.h"

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

    if (optind >= argc) {
        print_usage();
        return EXIT_FAILURE;
    }

    char *command_name = argv[optind++];
    char *file_name = argv[optind];

    if (strcmp(command_name, "setup") == 0) {
        return setup();
    }

    if (file_name == NULL) {
        print_usage();
        return EXIT_FAILURE;
    }

    command_func command;

    if (strcmp(command_name, "install") == 0) {
        command = install;
    } else if (strcmp(command_name, "uninstall") == 0) {
        command = uninstall;
    } else if (strcmp(command_name, "link") == 0) {
        command = link_command;
    } else if (strcmp(command_name, "unlink") == 0) {
        command = unlink_command;
    } else {
        fprintf(stderr, "ERROR: Unrecognized command '%s'\nTry 'attic --help' for more information.\n", command_name);
        return EXIT_FAILURE;
    }

//    load_config();
    // Use a static config for now, will add proper config later
    static_default_config();
    command(file_name);

    // Cleanup
    free_config();

    return EXIT_SUCCESS;
}