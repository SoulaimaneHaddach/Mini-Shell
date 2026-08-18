#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

char *find_command(char *command)
{
    char *path;
    char *dir;
    char *full_path;

    path = getenv("PATH");

    if (path == NULL)
        return (NULL);

    path = strdup(path);
    if (path == NULL)
        return (NULL);

    dir = strtok(path, ":");

    while (dir != NULL)
    {
        full_path = malloc(strlen(dir) + strlen(command) + 2);

        if (full_path == NULL)
        {
            free(path);
            return (NULL);
        }

        sprintf(full_path, "%s/%s", dir, command);

        if (access(full_path, X_OK) == 0)
        {
            free(path);
            return (full_path);
        }

        free(full_path);
        dir = strtok(NULL, ":");
    }

    free(path);
    return (NULL);
}

int main(void)
{
    char input[1024];
    char *args[64];
    char *command;
    char *token;
    pid_t pid;
    int i;

    while (1)
    {
        printf("mini-shell > ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        input[strcspn(input, "\n")] = '\0';

        if (input[0] == '\0')
            continue;

        i = 0;
        token = strtok(input, " ");

        while (token != NULL && i < 63)
        {
            args[i] = token;
            i++;
            token = strtok(NULL, " ");
        }

        args[i] = NULL;
        
        command = find_command(args[0]);

        if (command == NULL)
        {
            printf("%s: command not found\n", args[0]);
            continue;
        }
        pid = fork();

        if (pid == 0)
        {
            execve(command, args, NULL);
            perror("execve");
            free(command);
            return (1);
        }
        else if (pid > 0)
        {
            waitpid(pid, NULL, 0);
        }
        else
        {
            perror("fork");
        }

        free(command);
    }

    return (0);
}