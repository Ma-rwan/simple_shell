#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;

void display_prompt(void);
void parse_command(char *command, char **arguments);
int execute_command(char *command, char **arguments);
int find_command(char *command, char **paths, char *full_path);
char **get_paths();
int execute_builtin(char **arguments);

#endif
