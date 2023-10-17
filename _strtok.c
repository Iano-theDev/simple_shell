#include "shell.h"
/**
 * check_match - custom _strchr
 * @c: letter
 * @str: str
 *
 * Return: unsigned int 1 or 0
 */
unsigned int check_match(char c, const char *str)
{
	unsigned int m;

	for (m = 0; str[m] != '\0'; m++)
	{
		if (c == str[m])
			return (1);
	}
	return (0);
}

/**
 * _strtok - our strtok
 * @str: string
 * @delim: get_tokenr separeter
 *
 * Return: next token
 */
char *_strtok(char *str, const char *delim)
{
	static char *t_1;
	static char *t_2;
	unsigned int i;

	if (str != NULL)
		t_2 = str;
	t_1 = t_2;
	if (t_1 == NULL)
		return (NULL);
	for (i = 0; t_2[i] != '\0'; i++)
	{
		if (check_match(t_2[i], delim) == 0)
			break;
	}
	if (t_2[i] == '\0' || t_2[i] == '#')
	{
		t_2 = NULL;
		return (NULL);
	}
	t_1 = t_2 + i;
	t_2 = t_1;
	for (i = 0; t_2[i] != '\0'; i++)
	{
		if (check_match(t_2[i], delim) == 1)
			break;
	}
	if (t_2[i] == '\0')
		t_2 = NULL;
	else
	{
		t_2[i] = '\0';
		t_2 = t_2 + i + 1;
		if (*t_2 == '\0')
			t_2 = NULL;
	}
	return (t_1);
}
