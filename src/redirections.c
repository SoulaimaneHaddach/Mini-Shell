#include "shell.h"

int	handle_redirection(char **args)
{
	int	i;
	int	fd;

	i = 0;
	while (args[i] != NULL)
	{
		if (strcmp(args[i], ">") == 0)
		{
			if (args[i + 1] == NULL)
			{
				printf("mini-shell: expected file after '>'\n");
				return (1);
			}

			fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror("open");
				return (1);
			}

			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				perror("dup2");
				close(fd);
				return (1);
			}

			close(fd);

			args[i] = NULL;
			return (0);
		}

		i++;
	}

	return (0);
}