#include "includes/minishell.h"

void    modify_env(char ***env_tab, char *str,  char **inp, int index_size[2])
{
     int i;
     char *ret_var;
     int size_env;
     char **cpy;

    i = 0;
    size_env = 0;
	while(i < size_str(*env_tab))
	{
		size_env = (int)(ft_strchr(env_tab[0][i],'=') - env_tab[0][i]);
		if (!ft_strncmp(env_tab[0][i], str, size_env) && index_size[1] == size_env)
		{
			free(env_tab[0][i]);
			ret_var= ft_strdup(inp[index_size[0]]);
			env_tab[0][i]=ft_strdup(ret_var);
			free (ret_var);
			return ;
		}
		i++;
	}
   // cpy = *env_tab;
	*env_tab = copy_var_env_cmd(*env_tab, size_str(*env_tab) + 1, inp, index_size[0]);
}

int is_alnum_str(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int     modify_var(t_env_tools *env, char *str, int size, char **inp)
{
	int i;
	char *ret_var;
	int size_env;

	i = 0;
	while(env->env_cpy[i])
	{
		size_env = (int)(ft_strchr(env->env_cpy[i],'=') - env->env_cpy[i]);
		if (!ft_strncmp(env->env_cpy[i], str, size_env) && size == size_env)
		{
			free(env->env_cpy[i]);
			env->env_cpy[i]= ft_strjoin(inp[1],"=");
			ret_var= ft_strdup(env->env_cpy[i]);
			free(env->env_cpy[i]);
			if(inp[2] != NULL)
				env->env_cpy[i]=ft_strjoin(ret_var, inp[2]);
			else
				env->env_cpy[i]=ft_strdup(ret_var);
			free (ret_var);
			return (1);
		}
		i++;
	}
	return (0);
}


void    env_var_setenv(t_env_tools *env, char *str, int size, char **inp)
{
	int i;
	char *ret_var;
	int size_env;
	char **cpy;

	i = 0;
	if (size_str(inp) > 3)
		ft_putendl_fd("Too many arguments.", 2);
	else
	{
		if (modify_var(env, str, size, inp))
		    return ;
		if (ft_isdigit(inp[1][0]))
			ft_putendl_fd("Variable name must begin with a letter.", 2);
		else if(!is_alnum_str(inp[1]))
			ft_putendl_fd("Variable name must contain alphanumeric characters.",2);
		else
		{
			cpy=env->env_cpy;
			env->env_cpy = copy_var_env(env->env_cpy,size_str(env->env_cpy) + 1, inp);
			free_str(cpy);
		}
	}
}


char **copy_var_env(char **environ, int size,char **inp)
{
	char **env;
	char *ret_var;
	int i;
	int j;

	j = 0;
	i = 0;
	if (!(env = (char**)malloc(sizeof(*env) * (size + 1))))
		return (NULL);
	env[size] = NULL;
	while(i < size-1)
	{
		env[i] = ft_strdup(environ[i]);
		i++;
	}
	env[i]= ft_strjoin(inp[1],"=");
	ret_var= ft_strdup(env[i]);
	free(env[i]);
	if(inp[2] != NULL)
		env[i]=ft_strjoin(ret_var, inp[2]);
	else
		env[i]=ft_strdup(ret_var);
	free (ret_var);
	return (env);
}


char **copy_var_env_cmd(char **environ, int size,char **inp, int j)
{
	char **env;
	char *ret_var;
	int i;
	int size_of_var;

	i = 0;
	size_of_var = size_env_add(inp);
	if (!(env = (char**)malloc(sizeof(*env) * (size + 1))))
		return (NULL);
	env[size] = NULL;
	while(i < size - 1)
	{
		env[i] = ft_strdup(environ[i]);
		free(environ[i]);
		i++;
	}
	ret_var = ft_strdup(inp[j]);
	env[i]=ft_strdup(ret_var);
	free(ret_var);
	free(environ);
	return (env);
}

