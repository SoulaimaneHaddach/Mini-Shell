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
char *expand_variable(char *arg)
{
    char *value;

    if (arg[0] != '$')
        return (arg);

    value = getenv(arg + 1);

    if (value == NULL)
        return ("");

    return (value);
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
        int j;

        j = 0;
        while (args[j] != NULL)
        {
            args[j] = expand_variable(args[j]);
            j++;
        }   
        if (strcmp(args[0], "cd") == 0)
        {
            if (args[1] == NULL)
            {
                printf("cd: missing argument\n");
            }
            else if (chdir(args[1]) != 0)
            {
                perror("cd");
            }

             continue;
        }
        if (strcmp(args[0], "pwd") == 0)
        {
            char cwd[1024];

            if (getcwd(cwd, sizeof(cwd)) != NULL)
                printf("%s\n", cwd);
            else
                perror("getcwd");
            continue;
        }
        if (strcmp(args[0], "exit") == 0)
            break;
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