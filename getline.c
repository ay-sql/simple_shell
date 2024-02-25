#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
    size_t bufsize = INITIAL_BUFFER_SIZE;
    ssize_t chars_read = 0;
    int c;

    if (lineptr == NULL || n == NULL || stream == NULL)
        return (-1);

    if (*lineptr == NULL || *n == 0) {
        *lineptr = malloc(bufsize);
        if (*lineptr == NULL) {
            perror("Failed to allocate memory");
            exit(EXIT_FAILURE);
        }
        *n = bufsize;
    }

    while ((c = fgetc(stream)) != EOF) {
        (*lineptr)[chars_read++] = (char)c;

        if (chars_read >= (ssize_t)(*n - 1)) {
            char *temp = realloc(*lineptr, *n + INITIAL_BUFFER_SIZE);
            if (temp == NULL) {
                perror("Failed to reallocate memory");
                exit(EXIT_FAILURE);
            }
            *lineptr = temp;
            *n += INITIAL_BUFFER_SIZE;
        }

        if (c == '\n')
            break;
    }

    if (chars_read == 0)
        return (0);

    (*lineptr)[chars_read] = '\0';
    return (chars_read);
}
