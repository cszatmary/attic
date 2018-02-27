//
// Created by Christopher Szatmary on 2018-02-26.
//

#include <stdio.h>
#include "help.h"

static const char *attic_help = "Example usage:\n"
        "\tattic install [FILE]\n"
        "\tattic uninstall [NAME]\n"
        "\tattic link [NAME]\n"
        "\tattic unlink [NAME]\n"
        "\n"
        "Options:\n"
        "\t-v, --verbose\tVerbose Mode\n"
        "\t--version\tDisplay attic version\n";

void help() {
    printf("%s", attic_help);
}