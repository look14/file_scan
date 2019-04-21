#include "file_scan.h"
#include "common_queue.h"

int main(int argc, char* argv[])
{
    char path[MAX_FILE_PATH_SIZE];

    char* base_path = ".";
    file_scan_t* file_scan = file_scan_create(base_path);

    printf("%d %d\n", file_scan->file_count, file_scan->all_count);

    for(int i = 0; i < file_scan->all_count; i++)
    {
        if(0 == file_scan_get_path(file_scan, i, path, MAX_FILE_PATH_SIZE))
            printf("%-2d %s\n", i, path);
    }

    file_scan_destroy(&file_scan);

    return 0;
}
