#include "shell.h"

/**
 * exec_path - executes a command in the path
 * @command: full path to the command
 * @vars: pointer to struct of variables
 * Return: 0 on succcess, 1 on failure
 */
int exec_path(char *command, var_list_t *vars)
{
	pid_t child_pid;

	if (access(command, X_OK) == 0)
	{
		child_pid = fork();
		if (child_pid == -1)
			p_error(vars, NULL);
		if (child_pid == 0)
		{
			if (execve(command, vars->args, vars->env) == -1)
				p_error(vars, NULL);
		}
		else
		{
			wait(&vars->status);
			if (WIFEXITED(vars->status))
				vars->status = WEXITSTATUS(vars->status);
			else if (WIFSIGNALED(vars->status) && WTERMSIG(vars->status) == SIGINT)
				vars->status = 130;
			return (0);
		}
		vars->status = 127;
		return (1);
	}
	else
	{
		p_error(vars, ": Permission denied\n");
		vars->status = 126;
	}
	return (0);
}

/**
 * get_path - finds the PATH variable
 * @env: array of environment variables
 *
 * Return: pointer to the node that contains the PATH, or NULL on failure
 */
char *get_path(char **env)
{
	char *path = "PATH=";
	unsigned int i, j;

	for (i = 0; env[i] != NULL; i++)
	{
		for (j = 0; j < 5; j++)
			if (path[j] != env[i][j])
				break;
		if (j == 5)
			break;
	}
	return (env[i]);
}

/**
 * validate_path - checks if the command is in the PATH
 * @vars: variables
 * Return: void
 */
void validate_path(var_list_t *vars)
{
	char *path, *dup_path = NULL, *check = NULL;
	size_t r = 0, i = 0;
	char **path_tok;
	struct stat buf;

	if (validate_dir(vars->args[0]))
		r = exec_cwd(vars);
	else
	{
		path = get_path(vars->env);
		if (path != NULL)
		{
			dup_path = str_dup(path + 5);
			path_tok = get_token(dup_path, ":");
			for (i = 0; path_tok && path_tok[i]; i++, free(check))
			{
				check = str_cat(path_tok[i], vars->args[0]);
				if (stat(check, &buf) == 0)
				{
					r = exec_path(check, vars);
					free(check);
					break;
				}
			}
			free(dup_path);
			if (path_tok == NULL)
			{
				vars->status = 127;
				exit_prog(vars);
			}
		}
		if (path == NULL || path_tok[i] == NULL)
		{
			p_error(vars, ": not found\n");
			vars->status = 127;
		}
		free(path_tok);
	}
	if (r == 1)
		exit_prog(vars);
}

/**
 * exec_cwd - executes the command in the current path
 * @vars: variables structure
 * Return: 0 on success, 1 on failure
 */
int exec_cwd(var_list_t *vars)
{
	pid_t child_pid;
	struct stat buf;

	if (stat(vars->args[0], &buf) == 0)
	{
		if (access(vars->args[0], X_OK) == 0)
		{
			child_pid = fork();
			if (child_pid == -1)
				p_error(vars, NULL);
			if (child_pid == 0)
			{
				if (execve(vars->args[0], vars->args, vars->env) == -1)
					p_error(vars, NULL);
			}
			else
			{
				wait(&vars->status);
				if (WIFEXITED(vars->status))
					vars->status = WEXITSTATUS(vars->status);
				else if (WIFSIGNALED(vars->status) && WTERMSIG(vars->status) == SIGINT)
					vars->status = 130;
				return (0);
			}
			vars->status = 127;
			return (1);
		}
		else
		{
			p_error(vars, ": Permission denied\n");
			vars->status = 126;
		}
			return (0);
	}
	p_error(vars, ": not found\n");
	vars->status = 127;
	return (0);
}

/**
 * validate_dir - checks if the command is a part of a path
 * @str: command
 * Return: 1 on success, 0 otherwise
 */
int validate_dir(char *str)
{
	unsigned int i;

	for (i = 0; str[i]; i++)
	{
		if (str[i] == '/')
			return (1);
	}
	return (0);
}
