//
// Created by Christopher Szatmary on 2018-02-21.
//

#include <stdlib.h>
#include "config.h"
#include "setup.h"

int setup(const char *install_dir) {
    const char *install_location = install_dir == NULL ? install_dir : default_install_location;

    verbose_print("Checking if install location already exists\n");
    if (check_file_exists(install_location)) {
        printf("%s exists.\nattic has already been set up.\n", install_location);
        return EXIT_SUCCESS;
    }


}

//    char *src = argv[1];
//    char *dest = argv[2];
//
//    int status = copy_file(src, dest, MAX_RX_PERM);
//
//    if (status == -1) {
//        printf("Error copying. Process unsuccessful.\n");
//        exit(1);
//    } else {
//        printf("Successfully copied file.\n");
//    }
//    printf("Status: %d", status);
//    verbose_print("Install directory does not exist, creating it ...\n");
//    mkdir(config_data->install_location, MAX_RX_PERM);
//    perror("mkdir");
//    verbose_print("Successfully created install directory at %s\n", config_data->install_location);

//    generate_new_config();
