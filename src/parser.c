#include "shell.h"

char	*expand_variable(char *arg)
{
	char	*value;

	if (arg[0] != '$')
		return (arg);

	value = getenv(arg + 1);
	if (value == NULL)
		return ("");

	return (value);
}