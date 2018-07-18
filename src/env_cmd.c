/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   env_cmd.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: canastas <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 18:23:52 by canastas     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/18 00:02:26 by canastas    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		size_env_add(char **inp)
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	while (inp[i])
	{
		if (ft_strchr(inp[i], '=') && inp[i][0] != '=')
			count++;
		i++;
	}
	return (count);
}

void	opt_env_i(char ***tmp_env, char **str, int *j)
{
	int	i;
	int	tmp;

	tmp = *j;
	free_str(*tmp_env);
	*tmp_env = NULL;
	if (tmp + 1 < size_str(str) && ft_strchr(str[tmp + 1], '=') &&
			str[tmp + 1][0] != '=' && (i = 1))
	{
		(*j)++;
		while (*j < size_str(str))
		{
			if (ft_strchr(str[*j], '=') && str[*j][0] != '=')
			{
				*tmp_env = copy_var_env_cmd(*tmp_env, i, str, *j);
				i++;
				(*j)++;
			}
			else
			{
				(*j)--;
				return ;
			}
		}
	}
}

int		opt_u(char **str, int *i, char **tmp_env)
{
	if (str[*i + 1])
	{
		unset(&tmp_env, str[*i + 1], ft_strlen(str[*i + 1]));
		(*i)++;
	}
	else
	{
		ft_putendl_fd("env: option requires an argument -- 'u'", 2);
		ft_putendl_fd("usage: env [-u name]", 1);
		free_str(tmp_env);
		return (1);
	}
	return (0);
}

int		opt_env(char **str, t_env_tools *env, char *path,
		int index_size[2])
{
	if (!ft_strcmp(str[index_size[0]], "-i"))
		opt_env_i(&env->tmp_env, str, &index_size[0]);
	else if (!ft_strcmp(str[index_size[0]], "-u") && env->tmp_env != NULL)
	{
		if (opt_u(str, &index_size[0], env->tmp_env))
			return (1);
	}
	else if (ft_strchr(str[index_size[0]], '=') &&
			str[index_size[0]][0] != '=')
	{
		index_size[1] = (int)(ft_strchr(str[index_size[0]], '=') -
				str[index_size[0]]);
		modify_env(&env->tmp_env, str[index_size[0]], str, index_size);
	}
	else
	{
		error_exec_or_exec(env->paths, path, str, env->tmp_env);
		if (env->tmp_env)
			free_str(env->tmp_env);
		return (1);
	}
	return (0);
}

void	env_exec(char **str, t_env_tools *env, char *path)
{
	int index_size[2];
	int check_opt;

	check_opt = 0;
	index_size[0] = 1;
	index_size[1] = 0;
	env->tmp_env = copy_env(env->env_cpy, size_str(env->env_cpy));
	if (size_str(str) == 1)
		print_array_of_string(env->tmp_env);
	else
	{
		while (index_size[0] < size_str(str))
		{
			check_opt = opt_env(str, env, path, index_size);
			if (check_opt == 1)
				return ;
			index_size[0]++;
		}
		if (env->tmp_env != NULL)
			print_array_of_string(env->tmp_env);
	}
	if (env->tmp_env != NULL)
		free_str(env->tmp_env);
}
