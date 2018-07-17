/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   unset.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: canastas <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 20:00:26 by canastas     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/17 20:02:04 by canastas    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/minishell.h"

int		count_char(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (str)
	{
		while (str[i] != '\0')
		{
			if (str[i] == c)
				count++;
			i++;
		}
	}
	return (count);
}

char	**copy_var_env_cmd(char **environ, int size, char **inp, int j)
{
	char	**env;
	char	*ret_var;
	int		i;
	int		size_of_var;

	i = 0;
	size_of_var = size_env_add(inp);
	if (!(env = (char**)malloc(sizeof(*env) * (size + 1))))
		return (NULL);
	env[size] = NULL;
	while (i < size - 1)
	{
		env[i] = ft_strdup(environ[i]);
		free(environ[i]);
		i++;
	}
	ret_var = ft_strdup(inp[j]);
	env[i] = ft_strdup(ret_var);
	free(ret_var);
	free(environ);
	return (env);
}

void	unset(char ***env_tab, char *str, int size)
{
	int		i;
	int		size_env;

	i = 0;
	size_env = 0;
	while (i < size_str(*env_tab))
	{
		size_env = (int)(ft_strchr(env_tab[0][i], '=') - env_tab[0][i]);
		if (!ft_strncmp(env_tab[0][i], str, size_env) && size == size_env)
		{
			ft_bzero(env_tab[0][i], ft_strlen(env_tab[0][i]));
			return ;
		}
		i++;
	}
}
