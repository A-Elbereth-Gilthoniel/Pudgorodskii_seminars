#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <limits.h>
#include <signal.h>
#include <sys/wait.h>

#define _GNU_SOURCE

void exiting(int signum);
void args_handle(char **buf, const char *line);
void parsing(char *line);

//===================================================

int main() {
    signal(SIGINT, exiting);

    while (1) {
        char *ptr = NULL;
        size_t n = 0;

        printf("> ");
        ssize_t len = getline(&ptr, &n, stdin);
        if (len == -1) {
            free(ptr);
            perror("getline");
            exit(1);
        }

        parsing(ptr);
        free(ptr);
    }

    return 0;
}


//==================================================================

void exiting(int signum)
{
    exit(0);
}

//==================================================================

void args_handle(char **buf, const char *line)
{
    int sz = 0;
    size_t len = strlen(line);
    size_t start = 0;

    for (size_t i = 0; i <= len; ++i) {
        if (isspace(line[i]) || line[i] == '\0') {
            if (i > start) {
                buf[sz] = (char *)(line + start);
                sz++;
            }
            start = i + 1;
        }
    }

    buf[sz] = NULL;
}

//=========================================================

void parsing(char *line) {
    int children = 0;
    int fd_to_read = -1;

    if (strncmp(line, "exit\n", 5) == 0) {
        exit(0);
    }

    char *command = strtok(line, "|\n");
    while (command) {
        char *args[32768 / 4 - 1];
        args_handle(args, command);

        int fds[2];

        if ((command = strtok(NULL, "|\n")) != NULL) {
            if (pipe(fds) == -1) {
                perror("pipe");
                exit(1);
            }
        }

        pid_t pid = fork();

        if (pid == 0)
        {
            if (fd_to_read >= 0)
            {
                dup2(fd_to_read, 0);
                close(fd_to_read);
            }
            if (command)
            {
                close(fds[0]);
                dup2(fds[1], 1);
                close(fds[1]);
            }

            if (execvp(args[0], args) == -1)
            {
                perror("execvp");
                exit(1);
            }
        }
        else
        {
            if (fd_to_read >= 0)
            {
                close(fd_to_read);
            }
            children++;
            if (command)
            {
                close(fds[1]);
                fd_to_read = fds[0];
            }
        }
        command = strtok(NULL, "|\n");
    }

    for (int i = 0; i < children; ++i)
    {
        wait(NULL);
    }
}
