#include "shell.h"


/**
 * puts_2 - print error
 * @str: str
 *
 * Return: nothing
 */
void puts_2(char *str)
{
	ssize_t m, n;

	m = str_len(str);
	n = write(STDERR_FILENO, str, m);
	if (n != m)
	{
		perror("Fatal Error");
		exit(1);
	}

}

/**
 * p_error - -Perror
 * @vars: var
 * @msg: string
 *
 * Return: nothing
 */
void p_error(var_list_t *vars, char *msg)
{
	char *t;

	puts_2(vars->argv[0]);
	puts_2(": ");
	t = to_ascii(vars->tally);
	puts_2(t);
	free(t);
	puts_2(": ");
	puts_2(vars->args[0]);
	if (msg)
	{
		puts_2(msg);
	}
	else
		perror("");
}

/**
 * to_ascii - %ud to %s changer
 * @tally: ud
 *
 * Return: address
 */
char *to_ascii(unsigned int tally)
{
	char *ms;
	unsigned int m, ints;

	m = tally;
	for (ints = 0; m != 0; ints++)
		m /= 10;
	ms = malloc(sizeof(char) * (ints + 1));
	if (ms == NULL)
	{
		perror("Fatal Error1");
		exit(127);
	}
	ms[ints] = '\0';
	for (--ints; tally; --ints)
	{
		ms[ints] = (tally % 10) + '0';
		tally /= 10;
	}
	return (ms);
}
