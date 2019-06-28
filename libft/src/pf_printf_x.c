/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 00:55:41 by callen            #+#    #+#             */
/*   Updated: 2019/06/06 12:54:27 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static void	pf_initflags_x(int opt[5], int size, t_flags *flags, int zero)
{
	PREC = flags->prec - size;
	HASHTAG = ((FLAGS & FHT) && !zero) * 2;
	ZERO = ((FLAGS & FPREC) && (flags->prec == 0) && zero);
	BLANKS = flags->blanks - size - PREC * (PREC > 0) -
		HASHTAG + ZERO;
	if (!(FLAGS & FPREC) && (FLAGS & FZE) && !(FLAGS & FSUB))
	{
		PREC = flags->blanks - size - HASHTAG;
		BLANKS = 0;
	}
}

static int	pf_getflags_x(int size, char *str, t_flags *flags, int zero)
{
	int		opt[5];

	pf_initflags_x(opt, size, flags, zero);
	if (!(FLAGS & FSUB) && BLANKS > 0)
		ft_printf_strnew(' ', BLANKS, FD);
	if (HASHTAG && !zero && !(FLAGS & FUP))
		pf_buffer(FD, "0x", 2);
	else if (HASHTAG && !zero)
		pf_buffer(FD, "0X", 2);
	if (PREC > 0)
		ft_printf_strnew('0', PREC, FD);
	if (ZERO)
		size -= 1;
	else
		pf_buffer(FD, str, size);
	if ((FLAGS & FSUB) && BLANKS > 0)
		ft_printf_strnew(' ', BLANKS, FD);
	return (size + PREC * (PREC > 0) +
			BLANKS * (BLANKS > 0) + HASHTAG);
}

int			ft_printf_x(t_flags *flags, va_list ap)
{
	int		size;
	char	*str;
	t_ull	nbr;

	nbr = va_arg(ap, t_ull);
	ft_getutype(TYPE, &nbr);
	size = ft_printf_itoa_base(nbr, 16, &str, (FLAGS & FUP) > 0);
	size = pf_getflags_x(size, str, flags, nbr == 0);
	free(str);
	return (size);
}