/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_treatment.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: canastas <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 19:40:32 by canastas     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/17 20:29:09 by canastas    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/minishell.h"

void	quote_loop(int *i, char *inp, char tmp[ft_strlen(inp)], int *j)
{
	if (inp[*i] == '\"')
	{
		tmp[*j] = inp[*i];
		(*i)++;
		while (inp[*i] != '\"' && inp[*i] != '\0')
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

char	**quot_mark_split(char *inp)
{
	char	**res;
	int		i;
	char	tmp[ft_strlen(inp) + 1];
	int		j;

	i = 0;
	j = 0;
	res = NULL;
	if (count_char(inp, '\"') % 2)
		return (res);
	while (i < (int)ft_strlen(inp))
	{
		quote_loop(&i, inp, tmp, &j);
		i++;
	}
	tmp[j] = '\0';
	res = ft_strsplit(tmp, '\"');
	return (res);
}

char	**search_for_var(char **str, t_env_tools env)
{
	int		i;
	char	**str_res;
	char	*var;

	i = -1;
	str_res = NULL;
	if (str != NULL)
	{
		if (!(str_res = (char**)malloc(sizeof(*str) * (size_str(str) + 1))))
			return (NULL);
		str_res[size_str(str)] = NULL;
		while (str[++i])
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
		}
	}
	return (str_res);
}
