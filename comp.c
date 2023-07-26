#include "shell.h"

/**
 * redirect_output - func ouput
 * @pipefd: pipefd[2]
 * @end: end
 */
void redirect_output(int pipefd[2], int end)
{
	close(pipefd[1 - end]);
	dup2(pipefd[end], STDOUT_FILENO);
	close(pipefd[end]);
}
/**
 * redirect_input - func input
 * @pipefd: pipefd[2]
 * @end: end
 */
void redirect_input(int pipefd[2], int end)
{
	close(pipefd[end]);
	dup2(pipefd[1 - end], STDIN_FILENO);
	close(pipefd[1 - end]);
}
/**
 * execute_single_command - execute_single_command
 * @command: command
 * @arguments: arguments
 * @paths: path
 * Return:0
 */
int execute_single_command(char *command, char **arguments, char **paths)
{
	char full_path[MAX_COMMAND_LENGTH];

	parse_command(command, arguments);
	if (execute_builtin(arguments))
	return (0);

	if (!find_command(arguments[0], paths, full_path))
	{
	fprintf(stderr, "%s: command not found\n", arguments[0]);
	return (-1);
	}

	return (execute_command(full_path, arguments));
}

/**
 * execute_piped_command - execute_piped_command
 *
 * @command1: command2
 * @command2: command2
 * @paths: paths
 * Return: nothing
 */
int execute_piped_command(char *command1, char *command2, char **paths)
{
	char *arguments1[MAX_ARGUMENTS];
	char *arguments2[MAX_ARGUMENTS];
	int pipefd[2];
	pid_t pid1, pid2;

	if (pipe(pipefd) == -1)
	{
		perror("Pipe error");
		exit(EXIT_FAILURE);
	}
	pid1 = fork();
	if (pid1 == 0)
	{
		redirect_output(pipefd, 1);
		return (execute_single_command(command1, arguments1, paths));
	}
	else if (pid1 < 0)
	{
		perror("Fork error");
		exit(EXIT_FAILURE);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		redirect_input(pipefd, 0);
		return (execute_single_command(command2, arguments2, paths));
	}
	else if (pid2 < 0)
	{
		perror("Fork error");
		exit(EXIT_FAILURE);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
