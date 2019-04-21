#include "file_scan.h"
#include "common_queue.h"

file_scan_t* file_scan_create(const char* base_path)
{
    file_scan_t* file_scan = NULL;
    DIR* dir = NULL;
    struct dirent* ptr = NULL;
    com_queue_t* com_queue = NULL;
    char *str;
    int count;

    file_scan = (file_scan_t*)calloc(sizeof(file_scan_t), 1);
    if(NULL == file_scan)
        goto END;

    strncpy(file_scan->path, base_path, MAX_FILE_PATH_SIZE);

    dir = opendir(base_path);
    if(NULL == dir)
        goto END;

    com_queue = com_queue_create();
    if(NULL == com_queue)
        goto END;

    while(NULL != (ptr = readdir(dir)))
    {
        if(DT_DIR & ptr->d_type)
        {
            if(!strcmp(".", ptr->d_name) || !strcmp("..", ptr->d_name))
                continue;

            str = (char*)calloc(MAX_FILE_PATH_SIZE, 1);
            if(NULL != str)
            {
                snprintf(str, MAX_FILE_PATH_SIZE, "%s/%s", base_path, ptr->d_name);
                com_queue_push(com_queue, str);

                file_scan->dir_count++;
            }
        }
        else
        {
            file_scan->file_count++;
            file_scan->all_count++;
        }
    }

    file_scan->dirs = (file_scan_t**)calloc(sizeof(file_scan_t*), file_scan->dir_count);

    count = 0;
    while(false == com_queue_empty(com_queue))
    {
        if(NULL == (str = com_queue_pop(com_queue)))
            continue;

        file_scan->dirs[count] = file_scan_create(str);

        if(NULL != file_scan->dirs[count]) {
            file_scan->all_count += file_scan->dirs[count]->all_count;
            count++;
        }

        free(str);
    }

END:
    if(NULL != com_queue)
    {
        while(false == com_queue_empty(com_queue))
            com_queue_pop(com_queue);
        com_queue_destroy(&com_queue);
    }
    if(NULL != dir)
        closedir(dir);

    return file_scan;
}

void file_scan_destroy(file_scan_t** pp_file_scan)
{
    int i;
    file_scan_t* file_scan = (pp_file_scan) ?(*pp_file_scan) :NULL;

    if(NULL == file_scan)
        return;

    for(i = 0; i < file_scan->dir_count; i++)
        file_scan_destroy(&file_scan->dirs[i]);

    if(NULL != file_scan->dirs)
        free(file_scan->dirs);

    free(file_scan);
    *pp_file_scan = NULL;
}

int file_scan_get_path(file_scan_t* file_scan, int pos, char path[], int size)
{
    int i, ret = -1;
    DIR* dir = NULL;
    struct dirent* ptr = NULL;

    if(NULL == file_scan || pos >= file_scan->all_count)
        return ret;

    if(pos >= file_scan->all_count - file_scan->file_count)
    {
        pos -= file_scan->all_count - file_scan->file_count;

        if(NULL != (dir = opendir(file_scan->path)))
        {
            while(NULL != (ptr = readdir(dir)))
            {
                if(0 == (DT_DIR & ptr->d_type))
                {
                    if(0 == pos) {
                        snprintf(path, size, "%s/%s", file_scan->path, ptr->d_name);
                        ret = 0;
                        break;
                    }
                    pos--;
                }
            }

            closedir(dir);
        }

    }
    else
    {
        for(i = 0; i < file_scan->dir_count; i++)
        {
            ret = file_scan_get_path(file_scan->dirs[i], pos, path, size);

            if(0 == ret)
                break;

            pos -= file_scan->dirs[i]->all_count;
        }
    }

    return ret;
}

