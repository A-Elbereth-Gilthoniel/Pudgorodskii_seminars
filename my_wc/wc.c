#include <stdio.h>
#include <ctype.h>

void count_wc(FILE *file, int *lines, int *words, int *chars);

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            perror(argv[i]);
            continue;
    }

    int lines = 0, words = 0, chars = 0;
    count_wc(file, &lines, &words, &chars);

    printf("%d %d %d %s\n", lines, words, chars, argv[i]);
    fclose(file);
    }

    return 0;
}

//======================================================================

void count_wc(FILE *file, int *lines, int *words, int *chars) {
    int c, prev_c = '\0';
    if (lines) *lines = 0;
    if (words) *words = 0;
    if (chars) *chars = 0;

    while ((c = fgetc(file)) != EOF) {
        if (chars)
            (*chars)++;

        if (c == '\n' && lines)
            (*lines)++;

        if (isspace(c))
        {
            if (!isspace(prev_c) && words)
                (*words)++;
        }

        prev_c = c;
    }
    if (!isspace(prev_c) && words) (*words)++;
}
