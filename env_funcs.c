#include "shell.h"

/**
 * create_env - create env from main
 * @env: environment
 * Return: new environment
 */
char **create_env(char **env)
{
	char **newenv = NULL;
	size_t i = 0;

	while (env[i] != NULL)
		i++;
	newenv = malloc(sizeof(char *) * (i + 1));
	if (newenv == NULL)
	{
		perror("Fatal Error");
		exit(1);
	}
	for (i = 0; env[i] != NULL; i++)
		newenv[i] = str_dup(env[i]);
	newenv[i] = NULL;
	return (newenv);
}

/**
 * free_env - free's environment
 * @env: current environment
 * Return: void
 */
void free_env(char **env)
{
	size_t n;

	while (env[n] != NULL)
	{
		free(env[n]);
		n++;
	}
	free(env);
}
