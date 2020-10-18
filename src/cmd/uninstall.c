#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "cmd.h"
#include "color.h"
#include "config.h"
#include "util.h"
#include "verbose.h"

struct Cmd uninstall_cmd = {
    .name = "uninstall",
    .desc = "Removes a previously installed program.",
    .arg_desc = "[file]",
    .run = run_uninstall,
};

enum ErrorCode run_uninstall(struct Cmd *cmd) {
    if (cmd->argc < 1) {
        return ErrArgsNone;
    }

    const char *filename = cmd->argv[0];
    sds path =
        sdscatfmt(sdsempty(), "%s/%s", config_install_location(), filename);

    // Make sure file actually exists before attempted removal
    verbose_printf("Checking if %s exists\n", filename);
    if (!file_exists(path)) {
        exitf("Error: %s does not exist\n", filename);
    }

    printf("Uninstalling %s ...\n", filename);
    verbose_printf("Removing %s from %s\n", filename,
                   config_install_location());

    if (unlink(path) != 0) {
        eprintf("Failed to uninstall %s:\n%s\n", filename, strerror(errno));
    }

    printf(GREEN("Successfully uninstalled %s!\n"), filename);

    sdsfree(path);
    return ErrNoErr;
}
