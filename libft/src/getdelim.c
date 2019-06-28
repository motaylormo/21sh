/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getdelim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 15:42:12 by callen            #+#    #+#             */
/*   Updated: 2019/06/27 21:38:00 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_stdio.h"
#include "ft_printf_internal.h"

#ifdef BUFF_SIZE
# undef BUFF_SIZE
#endif
#define BUFF_SIZE 64

#ifdef FD_MAX
# undef FD_MAX
#endif
#define FD_MAX 65535

static ssize_t	getdelim_read(int fd, char **src)
{
	register ssize_t	len;
	register char		*res;
	char				tmp[BUFF_SIZE + 1];

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

static int		getdelim_find(char **src, char **line, unsigned index)
{
	register char *tmp;

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

static int		getdelim_line(char **src, char **line, int fd, int delim)
{
	register char		*tmp;
	register ssize_t	len_read;
	register unsigned	index;

	len_read = 1;
	if (*src == NULL)
		len_read = getdelim_read(fd, src);
	while (len_read != -1)
	{
		tmp = *src;
		if ((tmp == NULL || tmp[0] == '\0') && len_read == 0)
			return (0);
		index = 0;
		while (tmp[index])
		{
			if (tmp[index] == delim)
				return (getdelim_find(src, line, index));
			else if (tmp[index + 1] == '\0' && len_read == 0)
				return (getdelim_find(src, line, (index + 1)));
			index++;
		}
		len_read = getdelim_read(fd, src);
	}
	return (-1);
}

int				fd_getdelim(char **linep, size_t *linecapp, int delim, int fd)
{
	static t_gnl	*list;
	t_gnl			*point;

	(void)linecapp;
	if (BUFF_SIZE <= 0 || fd < 0 || !linep)
		return (-1);
	point = list;
	while (point)
	{
		if (point->fd == fd)
			return (getdelim_line(&point->line, linep, point->fd, delim));
		point = point->next;
	}
	if (!(point = malloc(sizeof(t_gnl))))
		return (-1);
	point->fd = fd;
	point->line = NULL;
	point->next = list;
	list = point;
	return (getdelim_line(&point->line, linep, point->fd, delim));
}

int				fd_getline(char **linep, size_t *linecapp, int fd)
{
	return (fd_getdelim(linep, linecapp, '\n', fd));
}

#undef BUFF_SIZE
#undef FD_MAX
