#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"
#include <sys/wait.h>

/**
 * handle_path_and_exec - Check if the command exists in the PATH and execute it.
 * @args: The array of command arguments.
 */

void handle_path_and_exec(char **args)
{
	char *path = getenv("PATH");
	char *path_token;
	char command[MAX_BUFFER_SIZE];
	pid_t pid;

	if (path != NULL)
	{
		path_token = strtok(path, ":");
		while (path_token != NULL)
		{
			snprintf(command, sizeof(command), "%s/%s", path_token,args[0]);
			if (access(command, F_OK) == 0)
			{
				pid = fork();
				if (pid < 0)
				{
					perror("fork");
					continue;
				}
				else if (pid == 0)
				{
					execve(command, args, NULL);
					perror("./shell");
					exit(EXIT_FAILURE);
				}
				else
				{
					wait(NULL);
					return;
				}
			}
			path_token = strtok(NULL, ":");
		}
	}
	else
	{
		printf("Error: PATH variable is not set.\n");
	}
}

