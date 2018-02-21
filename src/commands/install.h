//
// Created by Christopher Szatmary on 2018-02-19.
//

#ifndef ATTIC_INSTALL_H
#define ATTIC_INSTALL_H

#include <stdbool.h>

int install(const char *file_name);
int link_command(const char *file_name);
int symlink_file(const char *file_name, const char *full_path);
#endif //ATTIC_INSTALL_H
