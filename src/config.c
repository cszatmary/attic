#include "config.h"

#include <cJSON/cJSON.h>
#include <errno.h>
#include <sds/sds.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "util.h"
#include "verbose.h"

#define ATTIC_DIR ".attic"
#define ATTIC_RC ".atticrc.json"

// Empty config, all defaults used
#define DEFAULT_ATTIC_RC_JSON "{}\n"

struct Config {
    sds install_path;
};

// The global config. Since this is static it will be initialized to zero.
struct Config config;

bool initialized = false;

enum ErrorCode config_init(void) {
    verbose_printf("Initializing config\n");

    // If already initialized just no-op
    if (initialized) {
        return ErrNoErr;
    }

    const char *hd = home_dir();

    // Handle the rc file

    sds rc_path = sdscatfmt(sdsempty(), "%s/%s", hd, ATTIC_RC);
    FILE *f;

    if (file_exists(rc_path)) {
        // rc file exists, read it and set config values
        sds data = NULL;
        enum ErrorCode code = read_file(rc_path, &data);
        if (code != ErrNoErr) {
            sdsfree(data);
            verbose_printf("failed to read config file %s\n", rc_path);
            return code;
        }

        cJSON *config_json = cJSON_Parse(data);
        if (config_json == NULL) {
            verbose_printf("failed to parse config file");

            const char *err = cJSON_GetErrorPtr();
            if (err != NULL) {
                verbose_printf(": %s", err);
            }

            verbose_printf("\n");
            return ErrConfigParse;
        }

        const cJSON *install_path = cJSON_GetObjectItem(config_json, "installPath");
        if (cJSON_IsString(install_path) && strlen(install_path->valuestring) > 0) {
            // Expand ~ if it is the first char
            if (install_path->valuestring[0] == '~') {
                config.install_path = sdscatfmt(sdsempty(), "%s%s", hd, install_path->valuestring[1]);
            } else {
                config.install_path = sdsnew(install_path->valuestring);
            }
        }

        cJSON_Delete(config_json);
        sdsfree(data);

        verbose_printf("loaded config\n");
    } else {
        verbose_printf("%s does not exist, creating a default one\n", rc_path);
        f = fopen(rc_path, "w");
        if (f == NULL) {
            verbose_printf("failed to create %s: %s\n", rc_path,
                           strerror(errno));
            return ErrFileCreate;
        }

        if (fputs(DEFAULT_ATTIC_RC_JSON, f) == EOF) {
            verbose_printf("failed to write to %s\n", rc_path);
            return ErrFileWrite;
        }

        if (fclose(f) != 0) {
            verbose_printf("failed to close file %s: %s\n", rc_path,
                           strerror(errno));
            return ErrFileClose;
        }
    }

    // Set default config values for ones that are missing
    if (config.install_path == NULL) {
        config.install_path = sdscatfmt(sdsempty(), "%s/%s", hd, ATTIC_DIR);
    }

    // Create the install directory if it doesn't exist
    if (!file_exists(config.install_path)) {
        verbose_printf("%s does not exist, creating\n", config.install_path);

        if (mkdir(config.install_path, 0755) != 0) {
            verbose_printf("failed to create %s: %s\n", config.install_path,
                           strerror(errno));
            return ErrDirCreate;
        }

        verbose_printf("created %s\n", config.install_path);
    }

    initialized = true;
    return ErrNoErr;
}

const char *config_install_location(void) {
    if (!initialized) {
        exitf("config accessed before it was initialized\n");
    }

    return config.install_path;
}
