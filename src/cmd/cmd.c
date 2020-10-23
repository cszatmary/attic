#include "cmd.h"

#include <getopt.h>
#include <sds/sds.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "verbose.h"
#include "version.h"

struct Cmd root_cmd = {
    .name = "attic",
    .desc = "attic is a small program to easily install executables globally.",
    .arg_desc = "[command]",
};

enum ErrorCode cmd_init(void) {
    // Add children to root command
    // This needs to be updated if more sub commands are added
    size_t root_children_len = 5;
    struct Cmd **root_children =
        malloc(root_children_len * sizeof(struct Cmd *));
    if (root_children == NULL) {
        return ErrAllocFailed;
    }

    root_children[0] = &install_cmd;
    root_children[1] = &reinstall_cmd;
    root_children[2] = &uninstall_cmd;
    root_children[3] = &list_cmd;
    root_children[4] = &config_cmd;

    root_cmd.children = root_children;
    root_cmd.len_children = root_children_len;

    // Add parent to children
    install_cmd.parent = &root_cmd;
    reinstall_cmd.parent = &root_cmd;
    uninstall_cmd.parent = &root_cmd;
    list_cmd.parent = &root_cmd;
    config_cmd.parent = &root_cmd;

    return ErrNoErr;
}

enum ErrorCode cmd_parse(int argc, char **argv, struct Cmd **cmd) {
    // Extremely brutalist, this requires subcommands, then flags, then args
    // Start at 1 since 0 is always the name of the program
    int argi = 1;

    // Set return cmd to NULL in case we need to exit early
    *cmd = NULL;

    if (argc == 1) {
        // If no args, print root help
        cmd_help(&root_cmd);
        return ErrArgsValidate;
    }

    // Parse subcommands
    struct Cmd *curr_cmd = &root_cmd;
    while (argi < argc) {
        const char *arg = argv[argi];
        // If arg starts with a dash we have hit an option and are done
        // subcommands
        if (arg[0] == '-') {
            break;
        }

        // Seach each child command of the current command to see if we get a
        // match
        bool found = false;
        for (int i = 0; i < curr_cmd->len_children; i++) {
            struct Cmd *c = curr_cmd->children[i];
            if (strcmp(arg, c->name) == 0) {
                // We found the sub command
                found = true;
                curr_cmd = c;
                break;
            }
        }

        if (!found) {
            // If command has no run fn, then a subcommand is required
            if (curr_cmd->run == NULL) {
                eprintf("Unknown command: %s\n\n", arg);
                cmd_help(curr_cmd);
                return ErrArgsValidate;
            }

            // Otherwise break because any additional args are for the command
            break;
        }

        argi++;
    }

    // Parse flags
    int opt;
    // Option flags
    int show_version;

    struct option long_options[] = {{"verbose", no_argument, NULL, 'v'},
                                    {"version", no_argument, &show_version, 1},
                                    {"help", no_argument, NULL, 'h'},
                                    {0, 0, 0, 0}};

    // Tell getopt to start after the subcommands
    optind = argi;
    while ((opt = getopt_long(argc, argv, "vh", long_options, NULL)) != -1) {
        switch (opt) {
            case 0:
                if (show_version) {
                    printf("%s version %s\n", root_cmd.name, PROJECT_VERSION);
                    return ErrNoErr;
                }
                break;
            case 'v':
                set_verbose(true);
                break;
            case 'h':
                cmd_help(curr_cmd);
                return ErrNoErr;
            case '?':
            default:
                eprintf("\n");
                cmd_usage(curr_cmd);
                return ErrArgsValidate;
        }
    }

    // Pass remaining args to command
    if (optind < argc) {
        curr_cmd->argc = argc - optind;
        curr_cmd->argv = argv + optind;
    }

    *cmd = curr_cmd;
    return ErrNoErr;
}

sds cmd_path(struct Cmd *cmd) {
    if (cmd->parent == NULL) {
        return sdsnew(cmd->name);
    }

    sds p = cmd_path(cmd->parent);
    p = sdscat(p, " ");
    return sdscat(p, cmd->name);
}

void cmd_usage(struct Cmd *cmd) {
    sds path = cmd_path(cmd);
    if (cmd->arg_desc != NULL) {
        eprintf("Usage:\n  %s %s\n\n", path, cmd->arg_desc);
    } else if (cmd->len_children > 0) {
        eprintf("Usage:\n  %s [command]\n\n", path);
    } else {
        eprintf("Usage:\n  %s\n\n", path);
    }

    // Print sub commands
    if (cmd->len_children > 0) {
        eprintf("Available Commands:\n");
        for (int i = 0; i < cmd->len_children; i++) {
            struct Cmd *c = cmd->children[i];
            eprintf("  %-11s %s\n", c->name, c->desc);
        }
        eprintf("\n");
    }

    eprintf("Flags:\n");
    eprintf("  %-15s Display help for %s\n", "-h, --help", cmd->name);
    eprintf("  %-15s Enable verbose logging\n", "-v, --verbose");

    // If root, print global flags
    // TODO figure out a better way to handle flags
    if (cmd->parent == NULL) {
        eprintf("  %-15s Print the version of %s\n", "--version", cmd->name);
    }

    if (cmd->len_children > 0) {
        eprintf("\n");
        eprintf(
            "Use \"%s [command] --help\" for more information about a "
            "command.\n",
            path);
    }

    sdsfree(path);
}

void cmd_help(struct Cmd *cmd) {
    // Help is the same as usage except it also prints the description
    eprintf("%s\n\n", cmd->desc);
    cmd_usage(cmd);
}
