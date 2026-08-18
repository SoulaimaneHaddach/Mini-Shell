#ifndef SHELL_H
# define SHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

char	*find_command(char *command);
char	*expand_variable(char *arg);

int		handle_builtin(char **args);

#endif