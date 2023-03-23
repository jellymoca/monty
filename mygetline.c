#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

ssize_t my_getline(char **lineptr, size_t *n, FILE *stream)
{
    size_t num_read = 0;
    size_t pos = 0;
    int c;
    char *new_lineptr = realloc(*lineptr, *n);

    if (!lineptr || !n || !stream)
    {
        /* check for invalid arguments */
        return -1;
    }
    while ((c = fgetc(stream)) != EOF) {
        if (pos >= *n) {
            /* resize buffer if necessary */
            *n *= 2;
            if (!new_lineptr) {
                return -1;
            }
            *lineptr = new_lineptr;
        }

        (*lineptr)[pos++] = c;
        num_read++;

        if (c == '\n') {
            /* stop reading after newline */
            break;
        }
    }

    if (num_read == 0) {
        /* nothing was read */
        return -1;
    }

    (*lineptr)[pos] = '\0'; /* add null terminator */

    return num_read;
}
