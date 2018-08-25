/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_vars.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: canastas <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 19:45:19 by canastas     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/17 19:49:26 by canastas    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		size_str(char **environ)
{
	int	i;

	i = 0;
	while (environ[i] != NULL)
		i++;
	return (i);
}

int		check_zero(char *str)
{
	int	i;
	int	verif;

	i = 0;
	verif = 0;
	while (str[i])
	{
		if (str[i] == '\0')
			verif++;
		i++;
	}
	if (verif == (int)ft_strlen(str))
		return (1);
	return (0);
}

void	print_array_of_string(char **env)
{
	int	i;

	i = 0;
	if (env[i])
	{
		while (env[i])
		{
			if (!check_zero(env[i]))
				ft_putendl(env[i]);
			i++;
		}
	}
}

void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

void	free_str_2(char **str, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (str[i] != NULL)
			free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}
