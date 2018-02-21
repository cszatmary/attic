//
// Created by Christopher Szatmary on 2018-02-18.
//

#ifndef ATTIC_CONFIG_H
#define ATTIC_CONFIG_H

#include <stdio.h>
#include <libconfig.h>
#include "utils.h"

typedef struct {
    const char *install_location;
} attic_config;

extern const attic_config *config_data;
extern const char *link_path;

int generate_new_config();
int load_config();
int read_config_values(config_t *cfg, attic_config *config_struct);
void free_config();
int print_config_error(print_func print, FILE *stream, config_t *cfg);

#endif //ATTIC_CONFIG_H
