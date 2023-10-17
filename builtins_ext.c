#include "shell.h"

/**
 * to_int - str to int
 * @str: str
 * Return: int
 */
int to_int(char *str)
{
	int m = 0, mt;
	unsigned int l, its;

	mt = INT_MAX;
	for (its = 0; mt != 0; its++)
		mt /= 10;
	for (l = 0; str[l] != '\0' && l < its; l++)
	{
		m *= 10;
		if (str[l] < '0' || str[l] > '9')
			return (-1);
		if ((l == its - 1) && (str[l] - '0' > INT_MAX % 10))
			return (-1);
		m += str[l] - '0';
		if ((l == its - 2) && (str[l + 1] != '\0') && (m > INT_MAX / 10))
			return (-1);
	}
	if (l > its)
		return (-1);
	return (m);
}

/**
 * search_key - env finder
 * @env: env
 * @key: var
 * Return: var address
 */
char **search_key(char **env, char *key)
{
	unsigned int l, m, slen;

	slen = str_len(key);
	for (l = 0; env[l] != NULL; l++)
	{
		for (m = 0; m < slen; m++)
			if (key[m] != env[l][m])
				break;
		if (m == slen && env[l][m] == '=')
			return (&env[l]);
	}
	return (NULL);
}

/**
 * get_value - new var creater
 * @key: var
 * @value: val
 * Return: address
 */
char *get_value(char *key, char *value)
{
	unsigned int s1, s2, l, m;
	char *n;

	s1 = str_len(key);
	s2 = str_len(value);
	n = malloc(sizeof(char) * (s1 + s2 + 2));
	if (n == NULL)
		return (NULL);
	for (l = 0; key[l] != '\0'; l++)
		n[l] = key[l];
	n[l] = '=';
	for (m = 0; value[m] != '\0'; m++)
		n[l + 1 + m] = value[m];
	n[l + 1 + m] = '\0';
	return (n);
}

/**
 * create_key - env creater
 * @vars: ptr
 * Return: nothing
 */
void create_key(var_list_t *vars)
{
	unsigned int j;
	char **env2;

	for (j = 0; vars->env[j] != NULL; j++)
		;
	env2 = malloc(sizeof(char *) * (j + 2));
	if (env2 == NULL)
	{
		p_error(vars, NULL);
		vars->status = 127;
		exit_prog(vars);
	}
	for (j = 0; vars->env[j] != NULL; j++)
		env2[j] = vars->env[j];
	env2[j] = get_value(vars->args[1], vars->args[2]);
	if (env2[j] == NULL)
	{
		p_error(vars, NULL);
		free(vars->store);
		free(vars->cmd);
		free(vars->args);
		free_env(vars->env);
		free(env2);
		exit(127);
	}
	env2[j + 1] = NULL;
	free(vars->env);
	vars->env = env2;
}
