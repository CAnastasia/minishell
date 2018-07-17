#include "includes/minishell.h"

char *input()
{
	char *str;
	char *ret_str;
	ret_str = NULL;
	ft_putstr("$>");
	if ((get_next_line(0, &str)))
	{
		ret_str = ft_strdup(str);
		free(str);
	}
	return(ret_str);
}

int exec(char *path, char**str, char **env)

{
	char *hei;
	hei = path;
	pid_t pid;
	if ((pid = fork()))
	{
		if (pid == -1)
			return (-1);
		waitpid(pid, NULL, 0);
	}
	else
	{
		execve(path, str,  env);
		exit(EXIT_FAILURE);
	}

	return(0);
}
void quote_loop(int *i, char *inp, char tmp[ft_strlen(inp)], int *j)
{
	if (inp[*i] == '\"')
	{
		tmp[*j] = inp[*i];
		(*i)++;
		while(inp[*i] != '\"' && inp[*i] != '\0')
		{
			tmp[*j] = inp[*i];
			(*i)++;
			(*j)++;
		}
	}
	else if (inp[*i] == ' ' || inp[*i] == '\t')
	{
		if (inp[*i + 1] > 32 && inp[*i + 1] != '\0')
		{
			tmp[*j] = '\"';
			(*j)++;
		}
	}
	else
	{
		tmp[*j] = inp[*i];
		(*j)++;
	}
}
char **quot_mark_split(char *inp)
{
	char **res;
	int i;
	char tmp[ft_strlen(inp)];

	int j;
	i = 0;
	j = 0;
	res = NULL;
	if (count_char(inp, '\"') % 2)
		return (res);
	while(i < ft_strlen(inp))
	{
		quote_loop(&i, inp, tmp, &j);
		i++;
	}
	tmp[j] = '\0';
	res = ft_strsplit(tmp, '\"');
	return res;
}

char **search_for_var(char **str, t_env_tools env)
{
	int i;
	char **str_res;
	char *var;

	i = 0;
	if (str)
	{
		if (!(str_res = (char**)malloc(sizeof(*str) * (size_str(str) + 1))))
			return (NULL);
		str_res[size_str(str)] = NULL;
		while(str[i])
		{
			if (str[i][0] == '$')
			{
				var = ft_strsub(str[i], 1, ft_strlen(str[i]) - 1);
				if ((str_res[i] = env_var(env, var, ft_strlen(var))) == NULL)
					str_res[i] = ft_strdup(str[i]);
				free(var);
			}
			else
				str_res[i] = ft_strdup(str[i]);
			i++;
		}
	}
	return(str_res);
}

void initialitation(char **inp_cmd, char ***str, t_env_tools *env)
{
	env->inp = input();
	if(env->inp == NULL)
		exit(1);
	*inp_cmd = ft_strsub(mi_strchr(env->inp, ' ', '\t'), 1, ft_strlen(env->inp) - 1);
	*str = quot_mark_split(env->inp);
	env->str_input = search_for_var(*str,*env);
}
void exec_instructions(t_env_tools *env, char *inp_cmd)
{
	char *path;

	path = NULL;
	if (*env->str_input == NULL)
		;
	else if (ft_strcmp(*env->str_input, "exit") == 0 || env->inp == NULL)
	{
		if (env->str_input != NULL)
			free_str(env->str_input);
		ft_putstr("exit\n");
		exit(1);
	}
	else
		cmds(env->str_input, env, path, inp_cmd);
}

void instructions_loop(char **str, char *inp_cmd, t_env_tools env)
{
	int size;

	size = 0;
	while (1)
	{
		initialitation(&inp_cmd, &str, &env);
		if (str != NULL)
		{
			size = size_str(str);
			free_str(str);
		}
		if (env.str_input)
			exec_instructions(&env,inp_cmd);
		if (env.str_input != NULL)
			free_str_2(env.str_input,size);
		if (env.inp != NULL)
			free(env.inp);
		if (inp_cmd != NULL)
			free(inp_cmd);
	}
}

int main(int argc, char **argv, char  **environ)
{
	char **str;
	t_env_tools env;
	char *inp_cmd;

	env.paths = NULL;
	env.env_cpy = copy_env(environ, size_str(environ));
	instructions_loop(str, inp_cmd, env);
	if (env.env_cpy != NULL)
		free_str(env.env_cpy);
	return (0);
}
void exec_unsetenv(char **str, t_env_tools *env)
{
	if (str[1])
		unset(&env->env_cpy, str[1], ft_strlen(str[1]), str);
	else
		ft_putendl_fd("unsetenv : Too few arguments.", 2);
}

void exec_setenv(char **str, t_env_tools *env)
{
	if (str[1])
		env_var_setenv(env, str[1], ft_strlen(str[1]), str);
	else
		print_array_of_string(env->env_cpy);
}

void	cmds(char **str, t_env_tools *env, char *path, char *inp_cmd)
{
	char **tmp;

	path_str(env->env_cpy, &env->paths);
	if (ft_strcmp(*str, "echo") == 0)
	{
		tmp = mi_strsplit(env->inp, '\t', ' ');
		check_echo(tmp, *env, inp_cmd);
		free_str(tmp);
	}
	else if(ft_strcmp(*str, "setenv") == 0)
		exec_setenv(str, env);
	else if(ft_strcmp(*str, "env") == 0)
		env_exec(str, env, path);
	else if (ft_strcmp(*str, "unsetenv") == 0)
		exec_unsetenv(str, env);
	else if(ft_strcmp(*str, "cd") == 0)
		cd_function(str, env);
	else
		error_exec_or_exec(env->paths, path, str, env->env_cpy);
	if (env->paths != NULL)
		free_str(env->paths);
}

void error_exec_or_exec(char **paths,char *path,char **str, char **env)
{
	int res;

	res = check_path(paths, &path, str);
	if (res == 0)
	{
		ft_putstr_fd("minishell : command not found : ", 2);
		ft_putstr_fd(*str,2);
		ft_putchar('\n');
	}
	else if (res > 1)
		ft_putendl_fd("minishell : permission denied.", 2);
	else
		exec(path, str, env);
	if(path != NULL)
		free(path);
}
