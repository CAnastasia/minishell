#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>
# include <sys/types.h>
# include <stdlib.h>
# include "../libft/includes/libft.h"

typedef struct		s_env_tools
{
	char **env_cpy;
	char **paths;
}					t_env_tools;

void  path_str(t_env_tools *env);
int size_str(char **environ);
char **copy_env(char **environ, int size);
void free_str(char **str);
int check_path(t_env_tools env, char **path, char **str);
void check_echo(char **str, t_env_tools env);
int count_char(char *str,char c);
void quotation_split(char *str);

#endif