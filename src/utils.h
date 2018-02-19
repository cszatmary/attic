//
// Created by Christopher Szatmary on 2018-02-18.
//

#ifndef ATTIC_UTILS_H
#define ATTIC_UTILS_H

#define ALL_RW_PERM 0666
#define ALL_RX_PERM 0555
#define MAX_RW_PERM 0766
#define MAX_RX_PERM 0755

#define BUFFER_SIZE 8192

#define STATUS_OK 0
#define ERROR_READ -1
#define ERROR_WRITE -2
#define ERROR_CREATE -3

int copy_file(const char *file_name, const char *destination, mode_t permissions);

#endif //ATTIC_UTILS_H
