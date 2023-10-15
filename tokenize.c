#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char **tokenize(char *str)
{
	char **args = NULL;
	char *token = NULL;
	int i = 0;

	args = malloc(sizeof(char *) * strlen(str) + 1);

	if (!args)
	{
		printf("Tokenize: Error allocating memory!");
		return (NULL);
	}
	token = strtok(str, " \n\t");
	while (token != NULL)
	{
		args[i] = malloc(strlen(token) + 1);
		if (args[i] == NULL)
			return (NULL);
		strcpy(args[i],token);
		token = strtok(NULL, " \n\t");
		i++;
	}
	args[i] = NULL;
	return (args);
}
