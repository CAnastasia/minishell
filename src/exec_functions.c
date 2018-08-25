/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_functions.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: canastas <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 18:17:00 by canastas     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/19 14:57:19 by canastas    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		exec(char *path, char **str, char **env)
{
	pid_t	pid;

	if ((pid = fork()))
	{
		if (pid == -1)
			return (-1);
		waitpid(pid, NULL, 0);
	}
	else
	{
		execve(path, str, env);
		exit(EXIT_FAILURE);
	}
	return (0);
}

void	exec_unsetenv(char **str, t_env_tools *env)
{
	if (str[1])
		unset(&env->env_cpy, str[1], ft_strlen(str[1]));
	else
		ft_putendl_fd("unsetenv : Too few arguments.", 2);
}

void	exec_setenv(char **str, t_env_tools *env)
{
	if (str[1])
		env_var_setenv(env, str[1], ft_strlen(str[1]), str);
	else
		print_array_of_string(env->env_cpy);
}

void	cmds(char **str, t_env_tools *env, char *path, char *inp_cmd)
{
	char	**tmp;

	path_str(env->env_cpy, &env->paths);
	if (ft_strcmp(*str, "echo") == 0)
	{
		tmp = mi_strsplit(env->inp, '\t', ' ');
		check_echo(tmp, *env, inp_cmd);
		free_str(tmp);
	}
	else if (ft_strcmp(*str, "setenv") == 0)
		exec_setenv(str, env);
	else if (ft_strcmp(*str, "env") == 0)
		env_exec(str, env, path);
	else if (ft_strcmp(*str, "unsetenv") == 0)
		exec_unsetenv(str, env);
	else if (ft_strcmp(*str, "cd") == 0)
		cd_function(str, env);
	else
		error_exec_or_exec(env->paths, path, str, env->env_cpy);
	if (env->paths != NULL)
		free_str(env->paths);
}

void	error_exec_or_exec(char **paths, char *path, char **str,
		char **env)
{
	int		res;
	int		i;

	i = 0;
	res = 1;
	if (ft_strchr(str[0], '/'))
	{
		path = ft_strdup(str[0]);
		if (access(path, F_OK) == 0)
			i = 1;
	}
	else
		res = check_path(paths, &path, str);
	if (res == 0 && i == 0)
		error_command(str);
	else if (res > 1)
		ft_putendl_fd("minishell : permission denied.", 2);
	else
	{
		g_sig_check = 1;
		exec(path, str, env);
	}
	g_sig_check = 0;
	if (path != NULL)
		free(path);
}
