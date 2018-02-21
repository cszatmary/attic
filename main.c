#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include "utils.h"
#include "config.h"
#include "install.h"

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
            {0, 0, 0, 0}
    };

    // Check options
    while ((opt = getopt_long(argc, argv, "v", long_options, NULL)) != -1) {
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
            case '?':
            default:
                fprintf(stderr, "Unknown option %c\n", opt);
                return EXIT_FAILURE;
        }
    }

    if (optind >= argc) {
        print_usage();
        return EXIT_FAILURE;
    }

    char *command_name = argv[optind++];
    char *file_name = argv[optind];

    if (file_name == NULL) {
        print_usage();
        return EXIT_FAILURE;
    }

    command_func command;

    if (strcmp(command_name, "install") == 0) {
        command = install;
    } else {
        fprintf(stderr, "ERROR: Unrecognized command '%s'\nTry 'attic --help' for more information.\n", command_name);
        return EXIT_FAILURE;
    }

    load_config();
    command(file_name);

    // Cleanup
    free_config();

    return EXIT_SUCCESS;
}