//
// Created by Christopher Szatmary on 2018-02-26.
//

#include <stdio.h>
#include "help.h"

static const char *attic_help = "Example usage:\n"
        "\tattic install [FILE]\t-- Installs a program globally.\n"
        "\tattic uninstall [NAME]\t-- Removes a program installed with attic.\n"
        "\tattic link [NAME]\t-- Symlink a program installed with attic to '/usr/local/bin'.\n"
        "\tattic unlink [NAME]\t-- Remove symlink from '/usr/local/bin'.\n"
        "\tattic list\t\t-- Lists all programs installed with attic.\n"
        "\n"
        "Options:\n"
        "\t-v, --verbose\tVerbose Mode.\n"
        "\t--version\tDisplay attic version.\n"
        "\t-h, --help\tDisplays this help message.\n";

void help() {
    printf("%s", attic_help);
}