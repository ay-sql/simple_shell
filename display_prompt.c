#include "main.h"
#include <unistd.h>

/**
 * display_prompt - a function that prompts the user
 */
void display_prompt(void)
{
    if (write(STDOUT_FILENO, "$ ", 2) == -1) {
        // Handle error, for example, print an error message to standard error
        write(STDERR_FILENO, "Error writing prompt\n", 21);
    }
}
