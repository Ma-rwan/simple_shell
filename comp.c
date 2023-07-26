#include "shell.h"
/**
 * main - merge func
 * Return: 0
 */
int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	char *arguments[MAX_ARGUMENTS];
	char *paths[MAX_ARGUMENTS];
	char full_path[MAX_COMMAND_LENGTH];
	int status;
	size_t n = 0;
	ssize_t nchars_read;

	paths[0] = "/bin";

	while (1)
	{
		display_prompt();
		nchars_read = getline(&lineptr, &n, stdin);
		if (nchars_read == -1)
		{
			printf("Exit");
			return (-1);
		}
		if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
		break;
		command[strcspn(command, "\n")] = '\0';
		if (feof(stdin))
		break;
		parse_command(command, arguments);
		if (execute_builtin(arguments))
		continue;
		if (!find_command(arguments[0], paths, full_path))
		{
			fprintf(stderr, "%s: command not found\n", arguments[0]);
			continue;
		}
		status = execute_command(full_path, arguments);

		if (status == -1)
		{
			perror("Execution error");
			exit(1);
		}
	}
	return (0);
}
