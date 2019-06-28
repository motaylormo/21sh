/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 00:55:11 by callen            #+#    #+#             */
/*   Updated: 2019/06/06 12:43:10 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static void	pf_initflags_p(int opt[5], int size, t_flags *flags, int zero)
{
	PREC = flags->prec - size;
	ZERO = (FLAGS & FPREC) && (flags->prec == 0) && zero;
	BLANKS = flags->blanks - size - PREC * (PREC > 0) - 2;
	if (!(FLAGS & FPREC) && (FLAGS & FZE) && !(FLAGS & FSUB))
	{
		PREC = flags->blanks - size - 2;
		BLANKS = 0;
	}
}

static int	pf_getflags_p(int size, char *str, t_flags *flags, int zero)
{
	int		opt[5];

	pf_initflags_p(opt, size, flags, zero);
	if (!(FLAGS & FSUB) && BLANKS > 0)
		ft_printf_strnew(' ', BLANKS, FD);
	pf_buffer(FD, "0x", 2);
	if (PREC > 0)
		ft_printf_strnew('0', PREC, FD);
	if (ZERO)
		size -= 1;
	else
		pf_buffer(FD, str, size);
	if ((FLAGS & FSUB) && BLANKS > 0)
		ft_printf_strnew(' ', BLANKS, FD);
	return (size + PREC * (PREC > 0) + BLANKS * (BLANKS > 0) + 2);
}

int			ft_printf_p(t_flags *flags, va_list ap)
{
	int		size;
	char	*str;
	void	*p;

	p = va_arg(ap, void *);
	size = ft_printf_itoa_base((uint64_t)p, 16, &str, 0);
	size = pf_getflags_p(size, str, flags, p == 0);
	free(str);
	return (size);
}
