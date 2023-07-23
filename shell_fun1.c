#include "simple_shell.h"


/**
 * display_prompt - shows prompt
 *
 * Return: void
 */

void display_prompt(void)
{
	printf(" $ ");
	fflush(stdout);
}


/**
 * parse_command - parses command
 * @command: command to parse
 * @arguments: arguments to parse
 *
 * Return: void
 */

void parse_command(char *command, char **arguments)
{
	int i = 0;
	char *token = strtok(command, " ");

	while (token != NULL)
	{
		arguments[i] = tokens;
		token = strtok(NULL, " ");
		i++;
	}
	arguments[i] = NULL;
}



/**
 * get_paths - gets path
 * Return: paths
 */

char **get_paths()
{
	char *path_env = getenv("PATH");
	char *path = strtok(path_env, ":");
	char **paths = malloc((MAX_ARGUMENTS + 1) * sizeof(char *));
	int i = 0;

	while (path != NULL)
	{
		paths[i] = path;
		path = strtok(NULL, ":");
		i++;
	}
	paths[i] = NULL;
	return (paths);
}
