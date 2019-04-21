#ifndef __FILE_SCAN_H
#define __FILE_SCAN_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define MAX_FILE_PATH_SIZE  256

typedef struct file_scan_s {
    int all_count;
    int file_count;
    int dir_count;
    struct file_scan_s** dirs;
    char path[MAX_FILE_PATH_SIZE];

} file_scan_t;

file_scan_t* file_scan_create(const char* base_path);
void file_scan_destroy(file_scan_t** pp_file_scan);
int file_scan_get_path(file_scan_t* file_scan, int pos, char path[], int size);

#endif
