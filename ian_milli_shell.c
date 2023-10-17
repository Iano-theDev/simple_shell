#include "shell.h"

/* ctrl C Global var */
unsigned int sig_flag;

/**
 * sig_handler - take care ctrl C
 * @uuv:  var unused
 *
 * Return: void
 */
static void sig_handler(int uuv)
{
	(void) uuv;
	if (sig_flag == 0)
		put_str("\n$ ");
	else
		put_str("\n");
}

/**
 * main - entry point
 * @argc: ac
 * @argv: args
 * @environment: env
 *
 * Return: 0 up on success
 */
int main(int argc __attribute__((unused)), char **argv, char **environment)
{
	size_t s_buf = 0;
	unsigned int isp = 0, i;
	var_list_t vars = {NULL, NULL, NULL, 0, NULL, 0, NULL};

	vars.argv = argv;
	vars.env = create_env(environment);
	signal(SIGINT, sig_handler);
	if (!isatty(STDIN_FILENO))
		isp = 1;
	if (isp == 0)
		put_str("$ ");
	sig_flag = 0;
	while (getline(&(vars.store), &s_buf, stdin) != -1)
	{
		sig_flag = 1;
		vars.tally++;
		vars.cmd = get_token(vars.store, ";");
		for (i = 0; vars.cmd && vars.cmd[i] != NULL; i++)
		{
			vars.args = get_token(vars.cmd[i], "\n \t\r");
			if (vars.args && vars.args[0])
				if (parse_builtins(&vars) == NULL)
					validate_path(&vars);
		free(vars.args);
		}
		free(vars.store);
		free(vars.cmd);
		sig_flag = 0;
		if (isp == 0)
			put_str("$ ");
		vars.store = NULL;
	}
	if (isp == 0)
		put_str("\n");
	free_env(vars.env);
	free(vars.store);
	exit(vars.status);
}
