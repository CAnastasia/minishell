/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: canastas <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/09 15:40:15 by canastas     #+#   ##    ##    #+#       */
/*   Updated: 2018/02/22 17:10:15 by canastas    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/get_next_line.h"

static		int		read_file(int fd, char **s, int *ret)
{
	char			buff[BUFF_SIZE + 1];
	char			*tmp;

	tmp = *s;
	(*ret) = read(fd, buff, BUFF_SIZE);
	buff[*ret] = '\0';
	if (!(*s))
		*s = ft_strdup(buff);
	else
		*s = ft_strjoin(*s, buff);
	ft_strdel(&tmp);
	return (1);
}

static		int		put_in_line(const int fd, char **line, char **str)
{
	char			*tmp;
	char			*tmp2;

	if ((tmp = ft_strchr(str[fd], '\n')) != NULL)
	{
		tmp2 = str[fd];
		*line = ft_strnew((tmp - str[fd]));
		if (!(*line = ft_strncpy(*line, str[fd], (int)(tmp - str[fd]))))
			return (-1);
		str[fd] = ft_strdup(tmp + 1);
		free(tmp2);
		return (1);
	}
	return (0);
}

static		int		end_file(const int fd, char **line, char **str)
{
	if (ft_strlen(str[fd]) > 0)
	{
		*line = ft_strdup(str[fd]);
		ft_strdel(&str[fd]);
		return (1);
	}
	return (0);
}

int					get_next_line(const int fd, char **line)
{
	static char		*str[99999];
	int				ret;

	ret = 1;
	if (!line || fd < 0 || BUFF_SIZE < 1 || read(fd, NULL, 0) < 0)
		return (-1);
	if (!(str[fd]))
		str[fd] = ft_strdup("");
	while (ret > 0)
	{
		if (put_in_line(fd, line, str))
			return (1);
		if ((!(read_file(fd, &str[fd], &ret)) || ret == -1))
		{
			ft_strdel(&str[fd]);
			return (-1);
		}
	}
	if (end_file(fd, line, str))
		return (1);
	free(*str);
	return (0);
}
