/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ind.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 00:50:56 by callen            #+#    #+#             */
/*   Updated: 2019/06/06 12:18:55 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static int	pf_sizechar_ind(wchar_t c)
{
	if (!(c >> (7 + (MB_CUR_MAX == 1))))
		return (1);
	else if (!(c >> 11))
		return (2);
	else if (!(c >> 16))
		return (3);
	else if (!(c >> 21))
		return (4);
	return (-1);
}

int			ft_printf_ind(wchar_t c, t_flags *flags)
{
	int		size;
	int		blanks;

	if (!(FLAGS & FL))
		c = (unsigned char)c;
	else if (((MB_CUR_MAX == 1) && c > 255) || c < 0)
		return (-1);
	if ((c >= 0xd800 && c <= 0xdfff) || c > 0x10ffff)
		return (-1);
	if (FLAGS & FL)
		size = pf_sizechar_ind(c);
	else
		size = 1;
	blanks = flags->blanks - size;
	if (blanks > 0 && !(FLAGS & FSUB))
		ft_printf_strnew(' ' + 16 * ((FLAGS & FZE) > 0), blanks, FD);
	if (!(FLAGS & FL) && MB_CUR_MAX > 1)
		pf_buffer(FD, &c, 1);
	else
		ft_printf_putchar_fd(c, FD);
	if (blanks > 0 && (FLAGS & FSUB))
		ft_printf_strnew(' ', blanks, FD);
	return (size + blanks * (blanks > 0));
}
