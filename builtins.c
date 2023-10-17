#include "shell.h"
#include <stddef.h>

/**
 * _env - prints the current environment
 * @vars: variables struct
 * Return: void.
 */
void _env(var_list_t *vars)
{
	size_t j;

	for (j = 0; vars->env[j]; j++)
	{
		put_str(vars->env[j]);
		put_str("\n");
	}
	vars->status = 0;
}

/**
 * set_env - create or edit variable
 * @vars: variables struct
 * Return: void
 */
void set_env(var_list_t *vars)
{
	char **key;
	char *var;

	if (!(vars->args[1]) || !(vars->args[2]))
	{
		p_error(vars, "Check number of arguments\n");
		vars->status = 2;
		return;
	}
	key = search_key(vars->env, vars->args[1]);
	if (!key)
		create_key(vars);
	else
	{
		var = get_value(vars->args[1], vars->args[2]);
		if (!var)
		{
			free(vars->args);
			free(vars->store);
			free(vars->cmd);
			free_env(vars->env);
			p_error(vars, NULL);
			exit(127);
		}
		free(*key);
		*key = var;
	}
	vars->status = 0;
}


/**
 * unset_env - remove environment variable
 * @vars: variables structure
 * Return: void
 */
void unset_env(var_list_t *vars)
{
	size_t i, j;
	char **key, **env_2;

	if (!(vars->args[1]))
	{
		p_error(vars, ": Incorrect number of arguments\n");
		vars->status = 2;
		return;
	}
	key = search_key(vars->env, vars->args[1]);
	if (key == NULL)
	{
		p_error(vars, ": No variable to unset");
		return;
	}
	for (i = 0; vars->env[i] != NULL; i++)
		;
	env_2 = malloc(sizeof(char *) * i);
	if (env_2 == NULL)
	{
		p_error(vars, NULL);
		vars->status = 127;
		exit_prog(vars);
	}
	for (i = 0; vars->env[i] != *key; i++)
		env_2[i] = vars->env[i];
	for (j = i + 1; vars->env[j] != NULL; j++, i++)
		env_2[i] = vars->env[j];
	env_2[i] = NULL;
	free(*key);
	free(vars->env);
	vars->env = env_2;
	vars->status = 0;
}

/**
 * parse_builtins - checks for builtin command
 * @vars: variables
 * Return: function pointer, NULL otherwise
 */
void (*parse_builtins(var_list_t *vars))(var_list_t *vars)
{
	size_t j;
	builtins_t check[] = {
		{"exit", exit_prog},
		{"env", _env},
		{"setenv", set_env},
		{"unsetenv", unset_env},
		{NULL, NULL}
	};

	for (j = 0; check[j].f != NULL; j++)
	{
		if (str_cmp(vars->args[0], check[j].name) == 0)
			break;
	}
	if (check[j].f != NULL)
		check[j].f(vars);
	return (check[j].f);
}

/**
 * exit_prog - exit program
 * @vars: variables
 * Return: void
 */
void exit_prog(var_list_t *vars)
{
	int res;

	if (str_cmp(vars->args[0], "exit") == 0 && vars->args[1] != NULL)
	{
		res = to_int(vars->args[1]);
		if (res == -1)
		{
			vars->status = 2;
			p_error(vars, ": Illegal number: ");
			puts_2(vars->args[1]);
			puts_2("\n");
			free(vars->cmd);
			vars->cmd = NULL;
			return;
		}
		vars->status = res;
	}
	free(vars->args);
	free(vars->store);
	free(vars->cmd);
	free_env(vars->env);
	exit(vars->status);
}
