#include "cmd/cmd.h"
#include "color.h"
#include "config.h"
#include "error.h"

int main(int argc, char **argv) {
    color_init();

    enum ErrorCode code = cmd_init();
    if (code != ErrNoErr) {
        exiterrf(code, "Failed to initialize attic\n");
    }

    struct Cmd *cmd;
    code = cmd_parse(argc, argv, &cmd);
    if (code != ErrNoErr) {
        return 1;
    }

    // If cmd is NULL then we do nothing as it means help or version was run
    if (cmd == NULL) {
        return 0;
    }

    code = config_init();
    if (code != ErrNoErr) {
        exiterrf(code, "Failed to load config\n");
    }

    code = cmd->run(cmd);
    if (code != ErrNoErr) {
        if (code == ErrArgsNone || code == ErrArgsSome) {
            // Improper usage of command, display usage
            printf("Error: %s\n", error_title(code));
            cmd_usage(cmd);
            return 1;
        }

        exiterrf(code, "Failed to run command %s\n", cmd_path(cmd));
    }

    return 0;
}
