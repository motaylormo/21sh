/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 20:29:16 by callen            #+#    #+#             */
/*   Updated: 2019/06/06 13:01:27 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static int	pf_check_brace(char **str, int fd, int test)
{
	if (test)
	{
		while (**str != '}')
			(*str)++;
		return (0);
	}
	else
	{
		(*str)--;
		pf_buffer(fd, "{", 1);
	}
	return (1);
}

int			pf_color(char **str, int fd)
{
	int		i;

	i = 0;
	(*str)++;
	if (!ft_strncmp(*str, "black}", 6))
		i = pf_buffer(fd, BLK, 6);
	else if (!ft_strncmp(*str, "red}", 4))
		i = pf_buffer(fd, RED, 6);
	else if (!ft_strncmp(*str, "green}", 6))
		i = pf_buffer(fd, GRN, 6);
	else if (!ft_strncmp(*str, "yellow}", 7))
		i = pf_buffer(fd, YEL, 6);
	else if (!ft_strncmp(*str, "blue}", 5))
		i = pf_buffer(fd, BLU, 6);
	else if (!ft_strncmp(*str, "magenta}", 8))
		i = pf_buffer(fd, MAG, 6);
	else if (!ft_strncmp(*str, "cyan}", 5))
		i = pf_buffer(fd, CYN, 6);
	else if (!ft_strncmp(*str, "white}", 6))
		i = pf_buffer(fd, WHT, 6);
	else if (!ft_strncmp(*str, "eoc}", 4))
		i = pf_buffer(fd, RES, 5);
	return (pf_check_brace(str, fd, i));
}
