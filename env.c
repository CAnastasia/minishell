/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   env.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: canastas <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 19:37:48 by canastas     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/18 00:00:13 by canastas    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/minishell.h"

void	set_path(char *str, char ***paths)
{
	if (str != NULL)
	{
		*paths = ft_strsplit(str, ':');
		free(str);
	}
	else
		*paths = NULL;
}

void	path_str(char **envs, char ***paths)
{
	int		i;
	char	*str;
	int		j;
	int		k;

	i = 0;
	str = NULL;
	while (envs[i])
	{
		if (ft_strncmp(envs[i], "PATH=", 5) == 0)
		{
			str = ft_strnew(ft_strlen(envs[i]) - 5);
			j = 5;
			k = 0;
			while (j < (int)ft_strlen(envs[i]))
			{
				str[k] = envs[i][j];
				k++;
				j++;
			}
		}
		i++;
	}
	set_path(str, paths);
}

char	**copy_env(char **environ, int size)
{
	char	**env;
	int		i;

	i = 0;
	if (!(env = (char**)malloc(sizeof(*env) * (size + 1))))
		return (NULL);
	env[size] = NULL;
	while (environ[i] != NULL)
	{
		env[i] = ft_strdup(environ[i]);
		i++;
	}
	return (env);
}

void	check_path_loop(char **path_env, char **path, char **str, int *count)
{
	int		j;
	char	*join_slash;
	char	*join_cmd;

	j = 0;
	while (path_env[j])
	{
		join_slash = ft_strjoin(path_env[j], "/");
		join_cmd = ft_strjoin(join_slash, *str);
		free(join_slash);
		if (access(join_cmd, F_OK) == 0)
		{
			if (*count >= 1)
				free(*path);
			*path = ft_strdup(join_cmd);
			(*count)++;
		}
		j++;
		free(join_cmd);
	}
}

int		check_path(char **path_env, char **path, char **str)
{
	int	count;

	count = 0;
	if (path_env != NULL)
		check_path_loop(path_env, path, str, &count);
	return (count);
}
