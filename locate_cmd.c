#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// Function to locate a command in the system's PATH directories
char *locate_cmd(char *cmd) {
    // Get the PATH environment variable
    char *path = getenv("PATH");
    if (!path) {
        // If PATH is not found, print an error message and return NULL
        perror("PATH environment variable not found");
        return NULL;
    }

    // Duplicate the PATH string to prevent modification of the original string
    char *path_cpy = strdup(path);
    if (!path_cpy) {
        // If memory allocation for path copy fails, print an error message and return NULL
        perror("Failed to duplicate PATH");
        return NULL;
    }

    // Length of the command
    int command_len = strlen(cmd);

    // Tokenize the PATH string by colon delimiter
    char *path_token = strtok(path_cpy, ":");
    while (path_token != NULL) {
        // Length of the current directory in PATH
        int directory_len = strlen(path_token);

        // Allocate memory for the file path
        char *file_path = malloc(command_len + directory_len + 2); // +1 for '/' and +1 for '\0'
        if (!file_path) {
            // If memory allocation for file path fails, print an error message, free memory, and return NULL
            perror("Failed to allocate memory for file path");
            free(path_cpy);
            return NULL;
        }

        // Construct the full file path
        strcpy(file_path, path_token);
        strcat(file_path, "/");
        strcat(file_path, cmd);

        // Check if the constructed file path is a valid executable
        struct stat buffer;
        if (stat(file_path, &buffer) == 0) {
            // Free the duplicated PATH string and return the file path if the command is found
            free(path_cpy);
            return file_path;
        }

        // Free the file path if the command is not found in the current directory
        free(file_path);

        // Move to the next directory in PATH
        path_token = strtok(NULL, ":");
    }

    // Check if the command itself is a valid path to an executable
    struct stat buffer;
    if (stat(cmd, &buffer) == 0) {
        // Duplicate the command and return it
        char *cmd_path = strdup(cmd);
        free(path_cpy);
        return cmd_path;
    }

    // Free the duplicated PATH string and return NULL if the command is not found
    free(path_cpy);
    return NULL;
}
