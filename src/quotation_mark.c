/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   quotation_mark.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: canastas <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 19:49:37 by canastas     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/17 19:53:44 by canastas    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		number_of_words(char const *s, char c, char d)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c || s[i] == d)
			i++;
		while ((s[i] != c && s[i] != d) && s[i] != '\0')
			i++;
		if (s[i - 1] != c && s[i - 1] != d)
			j++;
	}
	return (j);
}

static int		nr_of_char(char const *str, char c, int *i, char d)
{
	int j;

	j = 0;
	while (str[*i] == c || str[*i] == d)
		(*i)++;
	while ((str[*i] != c && str[*i] != d) && str[*i] != '\0')
	{
		(*i)++;
		j++;
	}
	return (j);
}

static char		*final_tab(char *dest, char const *src, char c, char d)
{
	int i;

	i = 0;
	while (src[i] != '\0' && (src[i] != c && src[i] != d))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char			**mi_strsplit(char const *s, char c, char d)
{
	int		i;
	int		j;
	int		m;
	int		p;
	char	**str;

	i = 0;
	j = 0;
	m = 0;
	if (!s)
		return (NULL);
	m = number_of_words(s, c, d);
	if (!(str = (char**)malloc(sizeof(*str) * (m + 1))))
		return (NULL);
	str[m] = 0;
	while (i < m)
	{
		p = nr_of_char(s, c, &j, d);
		if (!(str[i] = (char*)malloc(sizeof(*str) * p + 1)))
			return (NULL);
		str[i] = final_tab(str[i], &s[j - p], c, d);
		i++;
	}
	return (str);
}

char			*mi_strchr(const char *s, int c, int d)
{
	while (*s != (char)c && *s != (char)d)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char*)s);
}
