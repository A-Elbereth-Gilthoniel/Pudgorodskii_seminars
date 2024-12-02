#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "fcntl.h"

#define BUF_SIZE 1024

void print_file(char* file_name);
void print_stdin();

int main(int argc, char * argv[])
{
    if (argc == 1)
    {
        print_stdin();
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            print_file(argv[i]);
        }
    }

    return 0;
}

//=====================================================

void print_file(char* file_name)
{
    int fp = open(file_name, O_RDONLY);
    if (fp < 0)
    {
        perror("file");
        return;
    }

    char buffer[BUF_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(fp, buffer, BUF_SIZE)) > 0)
    {
        write(STDOUT_FILENO, buffer, bytes_read);
    }

    close(fp);
}

//=====================================================

void print_stdin()
{
    char buffer[BUF_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(STDIN_FILENO, buffer, BUF_SIZE)) > 0)
    {
        write(STDOUT_FILENO, buffer, bytes_read);
    }
}
