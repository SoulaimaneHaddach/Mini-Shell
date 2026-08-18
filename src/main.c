#include "shell.h"

int	main(void)
{
	char	input[1024];
	char	*args[64];
	char	*command;
	char	*token;
	pid_t	pid;
	int		i;
	int		j;
	int		builtin;

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

		j = 0;
		while (args[j] != NULL)
		{
			args[j] = expand_variable(args[j]);
			j++;
		}

		builtin = handle_builtin(args);

		if (builtin == 2)
			break;

		if (builtin == 1)
			continue;

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
			waitpid(pid, NULL, 0);
		else
			perror("fork");

		free(command);
	}

	return (0);
}