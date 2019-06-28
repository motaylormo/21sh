/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putchar_fd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 00:54:57 by callen            #+#    #+#             */
/*   Updated: 2019/06/06 12:46:30 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static int	pf_return(int fd, void *c, int ret)
{
	pf_buffer(fd, c, ret);
	return (ret);
}

int			ft_printf_putchar_fd(wchar_t c, int fd)
{
	unsigned int	mb;

	if (!(c >> (7 + (MB_CUR_MAX == 1))))
		return (pf_return(fd, &c, 1));
	else if (!(c >> 11))
	{
		mb = (((c & 0x3f) << 8) | (c >> 6)) | 0x80c0;
		return (pf_return(fd, &mb, 2));
	}
	else if (!(c >> 16))
	{
		mb = (((c & 0x3f) << 16) | (((c >> 6) & 0x3f) << 8)
				| (c >> 12)) | 0x8080e0;
		return (pf_return(fd, &mb, 3));
	}
	else if (!(c >> 21))
	{
		mb = (((((c & 0x3f) << 24) | (((c >> 6) & 0x3f) << 16))
				| (((c >> 12) & 0x3f) << 8)) | (c >> 18)) | 0x808080f0;
		return (pf_return(fd, &mb, 4));
	}
	return (-1);
}
