/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 20:36:33 by callen            #+#    #+#             */
/*   Updated: 2019/06/06 14:01:28 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static void	pf_initflags_d(int opt[5], int size, t_flags *flags, char c)
{
	PREC = flags->prec - size + 1 * (c == '-');
	ADDORSPACE = (FLAGS & (FADD + FSPACE)) && c != '-';
	BLANKS = flags->blanks - size - PREC * (PREC > 0) - ADDORSPACE;
	if (!(FLAGS & FPREC) && (FLAGS & FZE) && !(FLAGS & FSUB))
	{
		PREC = flags->blanks - size - ADDORSPACE;
		BLANKS = 0;
	}
}

static int	pf_getflags_d(int size, char *str, t_flags *flags, int zero)
{
	int		opt[5];

	pf_initflags_d(opt, size, flags, str[0]);
	ZERO = ((FLAGS & FPREC) && (flags->prec == 0) && zero);
	BLANKS += ZERO;
	if (!(FLAGS & FSUB) && BLANKS > 0)
		ft_printf_strnew(' ', BLANKS, FD);
	if ((FLAGS & FADD) && str[0] != '-')
		pf_buffer(FD, "+", 1);
	else if ((FLAGS & FSPACE) && str[0] != '-')
		pf_buffer(FD, " ", 1);
	if (str[0] == '-')
		pf_buffer(FD, str, 1);
	if (PREC > 0)
		ft_printf_strnew('0', PREC, FD);
	if (ZERO)
		size -= 1;
	else
		pf_buffer(FD, str + 1 * (str[0] == '-'), size - 1 * (str[0] == '-'));
	if ((FLAGS & FSUB) && BLANKS > 0)
		ft_printf_strnew(' ', BLANKS, FD);
	return (size + PREC * (PREC > 0) + ADDORSPACE + BLANKS * (BLANKS > 0));
}

int			ft_printf_d(t_flags *flags, va_list ap)
{
	char	*str;
	int		size;
	t_sll	nbr;

	nbr = va_arg(ap, t_sll);
	ft_getstype(TYPE, &nbr);
	size = ft_printf_itoa(nbr, &str);
	size = pf_getflags_d(size, str, flags, nbr == 0);
	free(str);
	return (size);
}
