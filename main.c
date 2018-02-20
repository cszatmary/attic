#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>
#include "utils.h"
#include "config.h"
#include "install.h"

int main(int argc, char **argv) {

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

    printf("User: %s\n", getpwuid(getuid())->pw_name);
    printf("Home dir: %s\n", get_home_dir());
    size_t size = strlen(get_home_dir()) + strlen(".attic") + 2;
    printf("Size: %lu\n", size);
    char path[size];
    int status = join_path(get_home_dir(), ".attic", path, size);
    printf("Joined path: %s\n", path);
    printf("Status: %d\n", status);

    set_verbose(true);
//    generate_new_config();
    load_config();
    printf("Install location is: %s\n", config_data->install_location);

    install(argv[1]);

    // Cleanup
    free_config();

    return 0;
}