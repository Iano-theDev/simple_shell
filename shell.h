#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include <limits.h>

/**
 * struct variables - variables
 * @args: arguments
 * @store: Buffer
 * @env: environment variables
 * @tally: count of commands
 * @argv: arguments to main
 * @status: exit status
 * @cmd: cmd to execute
 */
typedef struct variables
{
	char **args;
	char *store;
	char **env;
	size_t tally;
	char **argv;
	int status;
	char **cmd;
} var_list_t;

/**
 * struct builtins - builtin functions structure
 * @name: name of command
 * @f: function pointer
 */
typedef struct builtins
{
	char *name;
	void (*f)(var_list_t *);
} builtins_t;
void validate_path(var_list_t *vars);
int exec_path(char *command, var_list_t *vars);
char *get_path(char **env);
int validate_dir(char *str);
int exec_cwd(var_list_t *vars);

char **create_env(char **env);
void free_env(char **env);

void (*parse_builtins(var_list_t *vars))(var_list_t *vars);
void exit_prog(var_list_t *vars);
void _env(var_list_t *vars);
void set_env(var_list_t *vars);
void unset_env(var_list_t *vars);

void p_error(var_list_t *vars, char *msg);
void puts_2(char *str);
char *to_ascii(unsigned int tally);

char **get_token(char *store, char *delimiter);
char **_realloc(char **ptr, size_t *size);
char *_strtok(char *str, const char *delim);

ssize_t put_str(char *str);
char *str_dup(char *strtodup);
int str_cmp(char *strcmp1, char *strcmp2);
char *str_cat(char *strc1, char *strc2);
unsigned int str_len(char *str);

void create_key(var_list_t *vars);
char **search_key(char **env, char *key);
char *get_value(char *key, char *value);
int to_int(char *str);



#endif /* SHELL_H */
