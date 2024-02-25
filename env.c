#include "main.h"
#include <unistd.h>
#include <stdlib.h> 

extern char **environ; 

/**
 * print_environment - Prints the environment variables
 * Return: On success, Always 0.
 * -1 is returned on error
 */
int print_environment(void)
{
    char **env_ptr = environ;

    while (*env_ptr)
    {
        size_t len = 0;

        while ((*env_ptr)[len])
            len++;

        if (write(STDOUT_FILENO, *env_ptr, len) == -1 ||
            write(STDOUT_FILENO, "\n", 1) == -1)
        {
            return -1; // Return -1 on write error
        }

        env_ptr++;
    }

    return (0);
}
