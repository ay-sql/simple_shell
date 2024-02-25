#include "main.h"
#include <unistd.h>
#include <stdlib.h>

extern char **environ;

void execute(char **argv)
{
    char *cmd = NULL, *actual_cmd = NULL;

    if (argv && argv[0])
    {
        cmd = argv[0];
        actual_cmd = locate_cmd(cmd);

        if (actual_cmd == NULL)
        {
            perror("command path not found");
            return;
        }

        if (execve(actual_cmd, argv, environ) == -1) // or NULL if environment inheritance is not desired
        {
            perror("Error executing command");
            free(actual_cmd);
            return;
        }
    }
}
