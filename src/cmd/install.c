#include <libgen.h>
#include <sds/sds.h>
#include <sys/stat.h>
#include <unistd.h>

#include "cmd.h"
#include "config.h"
#include "util.h"
#include "verbose.h"
#include "color.h"

struct Cmd install_cmd = {
    .name = "install",
    .desc = "Installs a program globally.",
    .arg_desc = "[file]",
    .run = run_install,
};

// Steps taken by install:
// - Check if already installed
// - Check if source exists
// - Check that it's an executable
// - Copy to install dir

enum ErrorCode run_install(struct Cmd *cmd) {
    if (cmd->argc < 1) {
        return ErrArgsNone;
    }

    const char *filepath = cmd->argv[0];
    // Extract file name in case it is in a different directory
    // Make a copy of the path because basename may modify the value
    sds path_copy = sdsnew(filepath);
    const char *filename = basename(path_copy);
    sds install_path =
        sdscatfmt(sdsempty(), "%s/%s", config_install_location(), filename);

    // Check if file is already installed
    verbose_printf("Checking if %s is already installed\n", filename);
    if (file_exists(install_path)) {
        printf(
            "%s is already installed!\nTo install a new version use 'attic "
            "reinstall'\n",
            filename);

        sdsfree(path_copy);
        sdsfree(install_path);
        return ErrNoErr;
    }

    printf("Installing %s ...\n", filename);
    verbose_printf("Checking %s\n", filename);

    // Check if file exists
    // Do this manually instead of using file_exists since we need to check
    // the perms after, so we need the actual stat object
    struct stat sb;
    if (stat(filepath, &sb) == -1) {
        exitf("Error: %s does not exist\n", filepath);
    }

    // Check if user has execute permissions
    verbose_printf("Checking if file is executable\n");
    if (!(sb.st_mode & S_IXUSR)) {
        exitf("Error: %s is not executable. Cannot install.\n", filepath);
    }

    verbose_printf("Copying %s to %s\n", filepath, config_install_location());
    enum ErrorCode code = copy_file(filepath, install_path);
    if (code != ErrNoErr) {
        exiterrf(code, "Failed to copy %s to %s\n", filepath,
                 config_install_location());
    }

    printf(GREEN("Successfully installed %s!\n"), filename);

    sdsfree(path_copy);
    sdsfree(install_path);
    return ErrNoErr;
}
