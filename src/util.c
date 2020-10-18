#include "util.h"

#include <errno.h>
#include <fcntl.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define READ_CHUNK 1024
#define COPY_CHUNK 8192

bool file_exists(const char *name) {
    struct stat s;

    if (stat(name, &s) != 0) {
        return false;
    }

    return true;
}

const char *home_dir(void) {
    char *hd = getenv("HOME");

    if (hd == NULL) {
        hd = getpwuid(getuid())->pw_dir;
    }

    return hd;
}

enum ErrorCode read_file(const char *name, sds *data) {
    FILE *f = fopen(name, "r");
    if (f == NULL) {
        return ErrFileOpen;
    }

    char buf[READ_CHUNK];
    size_t nread;

    if (*data == NULL) {
        *data = sdsempty();
    }

    while ((nread = fread(buf, sizeof(char), sizeof(buf), f)) > 0) {
        if (ferror(f)) {
            return ErrFileRead;
        }

        *data = sdscatlen(*data, buf, nread);
    }

    if (fclose(f) != 0) {
        return ErrFileClose;
    }

    return ErrNoErr;
}

enum ErrorCode copy_file(const char *src_path, const char *dest_path) {
    int src_fd;
    int dest_fd;
    char buf[COPY_CHUNK];

    struct stat s;
    int r = stat(src_path, &s);
    if (r != 0) {
        if (r == ENOENT) {
            return ErrFileNotExist;
        }

        return ErrFileStat;
    }

    if (!S_ISREG(s.st_mode)) {
        return ErrFileNotRegular;
    }

    src_fd = open(src_path, O_RDONLY);
    dest_fd = open(dest_path, O_WRONLY | O_CREAT | O_TRUNC, s.st_mode);

    if (dest_fd == -1) {
        return ErrFileCreate;
    }

    enum ErrorCode code = ErrNoErr;
    ssize_t nread;
    while ((nread = read(src_fd, buf, sizeof buf)) > 0) {
        ssize_t nwritten = write(dest_fd, buf, (size_t)nread);
        if (nwritten == -1) {
            code = ErrFileWrite;
            break;
        }
    }

    if (nread == -1) {
        code = ErrFileRead;
    }

    close(src_fd);
    close(dest_fd);

    return code;
}
