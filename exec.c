#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int run(char **args)
{
	int i = 0, j = 0, status;
	char **str_s = args;
	pid_t child;
	
	while (str_s[j])
	{
		printf("%s\n", str_s[j]);
		j++;
	}
	printf("count [%d]\n", j);

	child = fork();

	if(child == -1)
		printf("Error forking\n");
	else if (child == 0)
	{
		i = execve(args[0], args, NULL);
		free(args);
	}
	else
		wait(&status);

	if (i == -1)
		printf("error executing\n");
	return (i);
}
