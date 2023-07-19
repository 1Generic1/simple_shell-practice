#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"


/**
 * main - Entry point of the shell program
 *
 * Return: Always 0 (success)
 */
int main(void)
{
	char buffer[MAX_BUFFER_SIZE];
	ssize_t read_chars;
	char *args[] = {NULL};
	char *token;
	int i;

	while (1)
	{
		printf("shell$ ");
		read_chars = read(STDIN_FILENO, buffer, MAX_BUFFER_SIZE);
		if (read_chars == -1)
		{
			perror("read");
			continue;
		}
		if (read_chars == 0)
		{
			printf("\n");
			break;
		}
		buffer[read_chars - 1] = '\0';
		if (strcmp(buffer, "exit") == 0)
			break;
		/* Tokenize the input into arguments */
		token = strtok(buffer, " ");
		i = 0;
		while (token != NULL && i < MAX_ARGS - 1)
		{
			args[i] = token;
			i++;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;
		handle_path_and_exec(args);
	}
	return (0);
}
