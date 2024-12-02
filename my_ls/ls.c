#include "stdio.h"
#include "unistd.h"
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stat.h>

void list_directory(char *path, int show_details, int show_all, int recursive);

int main(int argc, char *argv[])
{
    int opt;
    int show_details = 0;
    int show_all = 0;
    int recursive = 0;
    char *path = ".";

    while ((opt = getopt(argc, argv, "liRad")) != -1)
    {
        switch (opt)
        {
            case 'l':
                show_details = 1;
                break;
            case 'i':
                printf("i flag selected\n");
                break;
            case 'R':
                recursive = 1;
                break;
            case 'a':
                show_all = 1;
                break;
            case 'd':
                printf("d flag selected\n");
                break;
        }
    }

    if (optind < argc)
    {
        path = argv[optind];
    }

    list_directory(path, show_details, show_all, recursive);

    return 0;
}

//======================================================================

void list_directory(char *path, int show_details, int show_all, int recursive)
{
    struct dirent *entry;
    DIR *dir = opendir(path);

    if (dir == NULL)
    {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (!show_all && entry->d_name[0] == '.')
        {
            continue;
        }

        if (show_details)
        {
            struct stat file_stat;
            char full_path[1024];
            snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
            if (stat(full_path, &file_stat) == -1)
            {
                perror("stat");
                continue;
            }

            printf("File: %s\n", entry->d_name);
            printf("Size: %ld bytes\n", file_stat.st_size);
            printf("Permissions: %o\n", file_stat.st_mode);
            printf("Last modified: %ld\n\n", file_stat.st_mtime);
        }
        else
        {
            printf("%s  ", entry->d_name);
        }

        if (recursive && entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            char full_path[1024];
            snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
            printf("\nEntering directory: %s\n", full_path);
            list_directory(full_path, show_details, show_all, recursive);
        }
    }
    printf("\n");
    closedir(dir);
}
