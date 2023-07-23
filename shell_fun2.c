#include "simple_shell.h"

/*********** find ********/

/**
 * find_command - find commands
 * @command: command to find
 * @paths: paths to find
 * @full_path: full path of command
 *
 * Return: 1 if found, otherwise 0
 */

int find_command(char *command, char **paths, char *full_path)
{
	int i = 0;

	while (path[i] != NULL)
	{
		sprintf(full_path, "%s/%s", paths[i], command);
		if (access(full_path, X_OK) == 0)
			return (1);
		i++;
	}
	return (0);
}

/******* execute *********/

/**
 * execute_command - executes command
 * @command: command to execute
 * @arguments: arg to execute
 *
 * Return: status
 */

int execute_command(char *command, char **arguments)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		execvp(command, arguments);
		exit(1);
	}
	else if (pid > 0)
	{
		int status;

		waitpid(pid, &status, 0);
		return (status);
	}
	else
	{
		perror("Fork error")
			exit(1);
	}
}

/********** execute_builtin ********/


/**
 * execute_builtin - executes builtin
 * @arguments: arguments to execute
 *
 * Return: 1 if executed, otherwise 0
 */

int execute_builtin(char **arguments)
{
	if (strcmp(arguments[0], "exit") == 0)
	{
		exit(0);
	}
	else if (strcmp(arguments[0], "env") == 0)
	{
		char **env = environ;

		while (*env != NUll)
		{
			printf("%s\n", *env);
		}
		return (1);
	}
	return (0);
}
