#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "cmd.h"
#include "config.h"
#include "verbose.h"

struct Cmd list_cmd = {
    .name = "list",
    .desc = "Lists all installed programs.",
    .arg_desc = NULL,
    .run = run_list,
};

enum ErrorCode run_list(struct Cmd *cmd) {
    if (cmd->argc > 0) {
        return ErrArgsSome;
    }

    const char *install_path = config_install_location();
    DIR *dir = opendir(install_path);

    verbose_printf("Opening directory %s\n", install_path);
    if (dir == NULL) {
        verbose_printf("Error opening %s\n%s", install_path, strerror(errno));
        return ErrDirOpen;
    }

    verbose_printf("Reading directory contents\n");
    printf("Installed Programs:\n");
    struct dirent *de;
    while ((de = readdir(dir)) != NULL) {
        // There shouldn't be any dirs but if there are ignore them
        if (de->d_type == DT_DIR) {
            continue;
        }

        printf("  - %s\n", de->d_name);
    }

    closedir(dir);
    return ErrNoErr;
}
