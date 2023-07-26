#include "shell.h"
/**
 * main - main
 * Return: 0
 */
int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	char *arguments[MAX_ARGUMENTS];
	char *paths[MAX_ARGUMENTS];
	char *pipe_pos;
	char *command1;
	char *command2;

	paths[0] = "/bin";

	while (1)
	{
		display_prompt();
		if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
			break;
		command[strcspn(command, "\n")] = '\0';
		if (feof(stdin))
			break;

		pipe_pos = strchr(command, '|');

		if (pipe_pos)
		{
			*pipe_pos = '\0';
			command1 = command;
			command2 = pipe_pos + 1;
			execute_piped_command(command1, command2, paths);
		}
		else
		{
			execute_single_command(command, arguments, paths);
		}
	}

	return (0);
}
