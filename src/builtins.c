#include "shell.h"

int	handle_builtin(char **args)
{
	char	cwd[1024];

	if (strcmp(args[0], "cd") == 0)
	{
		if (args[1] == NULL)
			printf("cd: missing argument\n");
		else if (chdir(args[1]) != 0)
			perror("cd");
		return (1);
	}

	if (strcmp(args[0], "pwd") == 0)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			printf("%s\n", cwd);
		else
			perror("getcwd");
		return (1);
	}

	if (strcmp(args[0], "exit") == 0)
		return (2);

	return (0);
}