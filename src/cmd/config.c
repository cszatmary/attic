#include "cmd.h"

#include "config.h"
#include <string.h>

struct Cmd config_cmd = {
    .name = "config",
    .desc = "List configuration values.",
    .arg_desc = "[name]",
    .run = run_config,
};

enum ErrorCode run_config(struct Cmd *cmd) {
    if (cmd->argc < 1) {
        return ErrArgsNone;
    }

    const char *name = cmd->argv[0];
    if (strcmp(name, "INSTALL_PATH") == 0) {
        printf("%s\n", config_install_location());
        return ErrNoErr;
    }

    eprintf("Unknown config name %s\n", name);
    return ErrArgsInvalid;
}
