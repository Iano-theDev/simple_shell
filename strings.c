#include "shell.h"

/**
 * str_len - gets length of a string
 * @str: string
 * Return: length of str
 */
unsigned int str_len(char *str)
{
	size_t len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

/**
 * put_str - prints a string to standard output
 * @str: string
 * Return: number of chars printed, -1 otherwie
 */
ssize_t put_str(char *str)
{
	ssize_t num, len;

	num = str_len(str);
	len = write(STDOUT_FILENO, str, num);
	if (len != num)
	{
		perror("Error");
		return (-1);
	}
	return (len);
}

/**
 * str_cmp - compares two string
 * @strcmp1: string one
 * @strcmp2: string two
 * Return: 0 on success, anything otherwise
 */
int str_cmp(char *strcmp1, char *strcmp2)
{
	int a;

	a = 0;
	while (strcmp1[a] == strcmp2[a])
	{
		if (strcmp1[a] == '\0')
			return (0);
		a++;
	}
	return (strcmp1[a] - strcmp2[a]);
}

/**
 * str_dup - duplicates a string in newly allocated memory
 * @strtodup: string to be duplicated
 * Return: a pointer to the new duplicated string
 */
char *str_dup(char *strtodup)
{
	char *new;
	int i, len = 0;

	if (strtodup == 0)
		return (NULL);

	while (strtodup[len])
		len++;
	new = malloc((len + 1) * sizeof(char));

	for (i = 0; i <= len; i++)
		new[i] = strtodup[i];
	while (i <= len)
		new[i] = strtodup[i];

	return (new);
}

/**
 * str_cat - concatenates two strings
 * @strc1: string one
 * @strc2: string two
 * Return: concatnated string
 */
char *str_cat(char *strc1, char *strc2)
{
	char *_str;
	unsigned int len_str1, len_str2, new_len, i, j;

	len_str1 = 0;
	len_str2 = 0;
	if (strc1 == NULL)
		len_str1 = 0;
	else
	{
		for (len_str1 = 0; strc1[len_str1]; len_str1++)
			;
	}
	if (strc2 == NULL)
		len_str2 = 0;
	else
	{
		for (len_str2 = 0; strc2[len_str2]; len_str2++)
			;
	}
	new_len = len_str1 + len_str2 + 2;
	_str = malloc(new_len * sizeof(char));
	if (_str == NULL)
		return (NULL);
	for (i = 0; i < len_str1; i++)
		_str[i] = strc1[i];
	_str[i] = '/';
	for (j = 0; j < len_str2; j++)
		_str[i + 1 + j] = strc2[j];
	_str[len_str1 + len_str2 + 1] = '\0';
	return (_str);
}
