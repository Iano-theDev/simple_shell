#include "shell.h"

/**
 * _realloc - reallocate memory
 * @ptr: old array
 * @size: elements in old array
 * Return: new array
 */
char **_realloc(char **ptr, size_t *size)
{
	char **new;
	size_t i = 0;

	new = malloc(sizeof(char *) * ((*size) + 10));
	if (!new)
	{
		free(ptr);
		return (NULL);
	}
	while (i < (*size))
	{
		new[i] = ptr[i];
		i++;
	}
	*size += 10;
	free(ptr);
	return (new);
}
