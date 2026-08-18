#include "shell.h"

char	*find_command(char *command)
{
	char	*path;
	char	*dir;
	char	*full_path;

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