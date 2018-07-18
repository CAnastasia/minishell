/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   echo.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: canastas <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 19:33:08 by canastas     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/17 19:37:29 by canastas    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo_tools(char **str, t_env_tools env)
{
	int		i;
	char	*var;

	i = 1;
	while (str[i])
	{
		if (!ft_strcmp(str[i], "~"))
			home(env);
		else if (count_expansion(str[i], '$') == 1)
		{
			var = dollar_expention(str[i], env);
			if (var != NULL)
			{
				ft_putchar(' ');
				free(var);
			}
		}
		else
		{
			ft_putstr(str[i]);
			ft_putchar(' ');
		}
		i++;
	}
	ft_putchar('\n');
}

void	out_of_quote(char *inp, t_env_tools env, int *i, char *tmp)
{
	if (inp[*i] == ' ' || inp[*i] == '\t')
	{
		if (inp[*i + 1] > 32 && inp[*i + 1] != '\0')
		{
			if (tmp != NULL)
				write(1, " ", 1);
		}
	}
	else if ((inp[*i] == '$' && count_expansion(inp, '$') == 1))
		dollar_in_quote(env, i, inp, &tmp);
	else if (inp[*i] == '~')
		home(env);
	else if (inp[*i] != ' ' && inp[*i] != '\t')
	{
		tmp = inp;
		write(1, &inp[*i], 1);
	}
}

void	between_quote(int *i, char *inp, t_env_tools env, char *tmp)
{
	(*i)++;
	while ((inp[*i] != '\"' && inp[*i] != '\'') && inp[*i] != '\0')
	{
		if ((inp[*i] == '$' && count_expansion(inp, '$') == 1))
			dollar_in_quote(env, i, inp, &tmp);
		else
		{
			tmp = inp;
			ft_putchar(inp[*i]);
			(*i)++;
		}
	}
}

void	check_echo(char **str, t_env_tools env, char *inp)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (inp == NULL)
		ft_putchar('\n');
	else if ((count_char(inp, '\"') % 2 == 0 && ft_strchr(inp, '\"') != NULL)
			|| (count_char(inp, '\'') % 2 == 0 &&
			ft_strchr(inp, '\'') != NULL))
	{
		while (inp[i] == ' ' || inp[i] == '\t')
			i++;
		while (inp[i])
		{
			if (inp[i] != '\"' && inp[i] != '\'')
				out_of_quote(inp, env, &i, tmp);
			else
				between_quote(&i, inp, env, tmp);
			i++;
		}
		ft_putchar('\n');
	}
	else if (ft_strchr(inp, '\"') == NULL && ft_strchr(inp, '\'') == NULL)
		echo_tools(str, env);
}
