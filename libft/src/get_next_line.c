/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 15:42:12 by callen            #+#    #+#             */
/*   Updated: 2019/06/27 20:30:49 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "ft_printf_internal.h"

int			get_next_line(const int fd, char **linep)
{
	return (fd_getdelim(linep, 0, '\n', fd));
}

#if 0
# ifdef BUFF_SIZE
#  undef BUFF_SIZE
# endif
# define BUFF_SIZE 64
# ifdef FD_MAX
#  undef FD_MAX
# endif
# define FD_MAX 4864

static long	ft_read(int fd, char **src)
{
	register long	len;
	char			*res;
	char			tmp[BUFF_SIZE + 1];

	ft_bzero(tmp, BUFF_SIZE + 1);
	len = read(fd, tmp, BUFF_SIZE);
	if (*src && len > 0)
	{
		res = ft_strjoin(*src, tmp);
		ft_strdel(src);
		*src = res;
	}
	else if (*src == NULL && len > 0)
		*src = ft_strdup(tmp);
	return (len);
}

static int	ft_find_line(char **src, char **line, unsigned index)
{
	char *tmp;

	tmp = *src;
	if (tmp[index] != '\0')
	{
		if (index == 0)
			*line = ft_strncpy(ft_strnew(0), tmp, index);
		else
			*line = ft_strsub(*src, 0, index);
		tmp = ft_strsub(*src, (index + 1), (ft_strlen(*src) - index - 1));
		ft_strdel(src);
		*src = tmp;
	}
	else
	{
		*line = ft_strdup(*src);
		ft_strdel(src);
	}
	return (1);
}

static int	ft_get_line(char **src, int fd, char **line)
{
	char				*tmp;
	register long		len_read;
	register unsigned	index;

	len_read = 1;
	if (*src == NULL)
		len_read = ft_read(fd, src);
	while (len_read != -1)
	{
		tmp = *src;
		if ((tmp == NULL || tmp[0] == '\0') && len_read == 0)
			return (0);
		index = 0;
		while (tmp[index])
		{
			if (tmp[index] == '\n')
				return (ft_find_line(src, line, index));
			else if (tmp[index + 1] == '\0' && len_read == 0)
				return (ft_find_line(src, line, (index + 1)));
			index++;
		}
		len_read = ft_read(fd, src);
	}
	return (-1);
}

int			get_next_line(const int fd, char **line)
{
	static t_gnl	*list;
	t_gnl			*point;

	if (BUFF_SIZE <= 0 || fd < 0 || !line)
		return (-1);
	point = list;
	while (point)
	{
		if (point->fd == fd)
			return (ft_get_line(&point->line, point->fd, line));
		point = point->next;
	}
	if (!(point = (t_gnl*)malloc(sizeof(t_gnl))))
		return (-1);
	point->fd = fd;
	point->line = NULL;
	point->next = list;
	list = point;
	return (ft_get_line(&point->line, point->fd, line));
}

# undef BUFF_SIZE
# undef FD_MAX
#endif
