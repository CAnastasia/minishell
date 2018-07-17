/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   var_search.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: canastas <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 20:02:13 by canastas     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/17 20:06:56 by canastas    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*env_var(t_env_tools env, char *str, int size)
{
	int		i;
	char	*ret_var;
	int		check_var;
	int		size_env;

	i = 0;
	check_var = 0;
	while (env.env_cpy[i])
	{
		size_env = (int)(ft_strchr(env.env_cpy[i], '=') - env.env_cpy[i]);
		if (!ft_strncmp(env.env_cpy[i], str, size_env) && size == size_env)
		{
			ret_var = ft_strsub(ft_strchr(env.env_cpy[i], '='), 1,
					ft_strlen(ft_strchr(env.env_cpy[i], '=')) - 1);
			check_var = 1;
		}
		i++;
	}
	if (check_var == 0)
		ret_var = NULL;
	return (ret_var);
}

int		count_expansion(char *str, char c)
{
	int		i;
	char	*str_chr;

	i = 0;
	if ((str_chr = ft_strchr(str, c)) == NULL)
		return (0);
	while (str_chr[i] == c)
	{
		i++;
	}
	return (i);
}

void	home(t_env_tools env)
{
	char	my_home[5];
	char	*var;

	ft_strcpy(my_home, "HOME\0");
	var = env_var(env, my_home, ft_strlen(my_home));
	ft_putstr(var);
	ft_putchar(' ');
}

void	split_dollar_exp(char *str, t_env_tools env)
{
	int		j;
	char	**split_echo;
	char	*var;

	j = 0;
	split_echo = ft_strsplit(str, '$');
	while (split_echo[j])
	{
		if (ft_strcmp(split_echo[j], "$"))
		{
			var = env_var(env, split_echo[j], ft_strlen(split_echo[j]));
			ft_putstr(var);
			free(var);
		}
		j++;
	}
	ft_putchar(' ');
	if (split_echo != NULL)
		free_str(split_echo);
}
