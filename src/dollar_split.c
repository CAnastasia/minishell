/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   dollar_split.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: canastas <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 19:28:39 by canastas     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/17 19:32:55 by canastas    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*dol_var_ret(char *str, t_env_tools env, int j)
{
	char	*var;
	int		size;
	char	*tmp;

	size = 0;
	tmp = str;
	if ((str[j] == '$' && count_expansion(str, '$') == 1))
	{
		if (str[j] == '$' && str[j + 1] == '\0')
			ft_putchar('$');
		size = ft_strlen(ft_strchr(str, '$'));
		tmp = ft_strsub(ft_strchr(str, '$'), 1, size);
		var = env_var(env, tmp, ft_strlen(tmp));
		free(tmp);
		ft_putstr(var);
		return (var);
	}
	else
		return (NULL);
}

char	*dollar_expention(char *str, t_env_tools env)
{
	int		j;
	char	*split_echo;
	char	*var;

	j = 0;
	var = NULL;
	split_echo = ft_strsub(str, 0, ft_strlen(str) -
	ft_strlen(ft_strchr(str, '$')));
	ft_putstr(split_echo);
	free(split_echo);
	if (count_char(str, '$') > 1)
		split_dollar_exp(str, env);
	else
	{
		while (str[j])
		{
			if (!(var = dol_var_ret(str, env, j)))
				j++;
			else
				return (var);
		}
	}
	return (NULL);
}

int		var_env(int i, char *str)
{
	int	count;

	count = 0;
	while ((str[i] != '\0' && str[i] != ' ' && str[i] != '\t'
			&& str[i] != '\"' && str[i] != '\'') && i < (int)ft_strlen(str))
	{
		i++;
		count++;
	}
	return (count);
}

char	*var_env_char(int j, char *str)
{
	int		i;
	char	*ret;

	i = 0;
	ret = ft_strnew(var_env(j, str));
	while ((str[j] != '\0' && str[j] != ' ' && str[j] != '\t' &&
			str[j] != '\"' && str[j] != '\'') && j < (int)ft_strlen(str))
	{
		ret[i] = str[j];
		j++;
		i++;
	}
	return (ret);
}

void	dollar_in_quote(t_env_tools env, int *i, char *inp, char **tmp)
{
	char	*var;

	var = var_env_char(*i, inp);
	*tmp = dollar_expention(var, env);
	if (*tmp != NULL)
		ft_putchar(' ');
	free(var);
	free(*tmp);
	*i += var_env(*i, inp);
}
