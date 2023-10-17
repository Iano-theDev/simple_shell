#include "shell.h"

/**
 * get_token - splits strings using delimeter
 * @store: string to split
 * @delimiter: character to split against
 * Return: array off strings,
 */
char **get_token(char *store, char *delimiter)
{
	size_t i = 0;
	char **words = NULL;
	size_t max_tally = 10;

	if (store == NULL)
		return (NULL);
	words = malloc(sizeof(char *) * max_tally);
	if (words == NULL)
	{
		perror("Fatal Error");
		return (NULL);
	}
	while ((words[i] = _strtok(store, delimiter)) != NULL)
	{
		i++;
		if (i == max_tally)
		{
			words = _realloc(words, &max_tally);
			if (words == NULL)
			{
				perror("Fatal Error");
				return (NULL);
			}
		}
		store = NULL;
	}
	return (words);
}
