//
// Created by Christopher Szatmary on 2018-02-18.
//

#ifndef ATTIC_CONFIG_H
#define ATTIC_CONFIG_H

typedef struct {
    const char *install_location;
    const char *link_path;
} attic_config;

extern const attic_config *config_data;

int init_config();
void free_config();

#endif //ATTIC_CONFIG_H
