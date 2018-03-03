//
// Created by Christopher Szatmary on 2018-03-03.
//

#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "list.h"

int list_dir_contents(const char *dir_name) {
    DIR *dir = opendir(dir_name);
    struct dirent *dir_entry;

    verbose_print("Opening directory %s\n", dir_name);
    if (dir == NULL) {
        fprintf(stderr, "Error opening %s\n%s", dir_name, strerror(errno));
        return EXIT_FAILURE;
    }

    verbose_print("Reading directory contents\n");
    while ((dir_entry = readdir(dir)) != NULL) {
        printf("%s\n", dir_entry->d_name);
    }

    closedir(dir);

    return EXIT_SUCCESS;
}