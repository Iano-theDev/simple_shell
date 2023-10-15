
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
	char *str = NULL;
	char *lineptr = NULL;
	size_t n = 0;
	ssize_t line;
	char **args;
	
	while(1)
	{
		printf("$ ");
		line = getline(&lineptr, &n, stdin);
		if (line == -1)
		{
			free(lineptr);
			return (-1);
		}
		str = strdup(lineptr);
		args = tokenize(str);
		
		run(args);
		free(lineptr);
		lineptr = NULL;
		n = 0;
	}
	free(lineptr);
	free(str);
	return (0);
}
