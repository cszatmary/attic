#ifndef ATTIC_CMD_H
#define ATTIC_CMD_H

#include <sds/sds.h>
#include <stddef.h>

#include "error.h"

struct Cmd {
    const char *name;
    const char *desc;
    const char *arg_desc;
    struct Cmd *parent;
    struct Cmd **children;
    int len_children;
    char **argv;
    int argc;
    enum ErrorCode (*run)(struct Cmd *cmd);
};

// cmd_init initializes the commands and creates the command tree.
enum ErrorCode cmd_init(void);

// cmd_parse sets cmd to the appropriate command based on the given arguments.
// If cmd is NULL than no action should be taken.
enum ErrorCode cmd_parse(int argc, char **argv, struct Cmd **cmd);

// cmd_path returns the full path of this command (i.e. its parents).
// The caller is responsible for freeing the string.
sds cmd_path(struct Cmd *cmd);

// cmd_usage prints the usage message for the given command.
void cmd_usage(struct Cmd *cmd);

// cmd_help prints the help message for the given command.
// It is similar to cmd_usage, but it also prints the command
// description.
void cmd_help(struct Cmd *cmd);

enum ErrorCode run_config(struct Cmd *cmd);
enum ErrorCode run_install(struct Cmd *cmd);
enum ErrorCode run_list(struct Cmd *cmd);
enum ErrorCode run_reinstall(struct Cmd *cmd);
enum ErrorCode run_uninstall(struct Cmd *cmd);

extern struct Cmd root_cmd;
extern struct Cmd config_cmd;
extern struct Cmd install_cmd;
extern struct Cmd list_cmd;
extern struct Cmd reinstall_cmd;
extern struct Cmd uninstall_cmd;

#endif  // ATTIC_CMD_H
