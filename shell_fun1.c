#include "shell.h"


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
		arguments[i] = token;
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
	char *path_str = strdup(path_env);

	char **paths = NULL;
	char *token = strtok(path_str, ":");

	int count = 0;

	while (token != NULL)
	{
		paths = realloc(paths, sizeof(char *) * (count + 2));
		paths[count] = strdup(token);
		token = strtok(NULL, ":");
		count++;
	}
	paths[count] = NULL;

	free(path_str);
	return (paths);
}
