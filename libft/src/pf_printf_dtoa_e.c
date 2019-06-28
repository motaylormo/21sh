/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_dtoa_e.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 20:36:28 by callen            #+#    #+#             */
/*   Updated: 2019/06/06 11:52:35 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static int	pf_fpclassify_e(double n)
{
	const t_dbl	u = {.f = n};
	int			e;

	e = u.i >> 52 & 0x7ff;
	if (!e)
		return (u.i << 1 ? FP_SUB : FP_ZER);
	if (e == 0x7ff)
		return (u.i << 12 ? FP_NAN : FP_INF);
	return (FP_NOR);
}

#ifdef FCHK
# undef FCHK
#endif
#define FCHK(nbr) (pf_fpclassify_e((nbr)) < FP_ZER)

static void	pf_initdtoa_e(double *nbr, int *sub, int *exp, int *i)
{
	if (*nbr < 0.0)
	{
		*sub = 1;
		*nbr = -*nbr;
	}
	else
		*sub = 0;
	*exp = 0;
	while (*nbr >= 10.0)
	{
		*nbr /= 10;
		(*exp)++;
	}
	while (*nbr && *nbr < 1.0)
	{
		*nbr *= 10;
		(*exp)--;
	}
	if (*sub)
		*i = 1;
	else
		*i = 0;
}

static void	pf_finishdtoa_e(char *str, int exp, int i, double nbr)
{
	if (exp < 0)
	{
		str[i + 1] = '-';
		exp = -exp;
	}
	else
		str[i + 1] = '+';
	str[i + 2] = exp / 10 + '0';
	str[i + 3] = exp % 10 + '0';
	str[i + 4] = (int)((nbr - (int)nbr) * 10) + '0';
	str[i + 5] = '\0';
}

int			ft_printf_dtoa_e(double nbr, t_flags *flags, char **str)
{
	int		exp;
	int		sub;
	int		size;
	int		i;

	pf_initdtoa_e(&nbr, &sub, &exp, &i);
	flags->prec = (!FCHK(nbr) * flags->prec) + (6 * (!(FLAGS & FPREC)));
	size = 5 + flags->prec + (flags->prec > 0) + sub;
	if (!(*str = malloc(sizeof(**str) * (size + 2 + sub))))
		ft_puterr("malloc error in ft_printf_dtoa_e.c");
	if (sub)
		(*str)[0] = '-';
	(*str)[i] = (int)nbr + '0';
	i += 1 + (flags->prec > 0);
	if (flags->prec > 0 && exp && ((nbr - (int)nbr) / 10))
		(*str)[i - 1] = '.';
	while (i < flags->prec + 1 + (flags->prec > 0) + sub)
	{
		nbr = (nbr - (int)nbr) * 10;
		(*str)[i] = ((int)nbr % 10) + '0';
		i++;
	}
	(*str)[i] = 'e' - 32 * ((FLAGS & FUP) > 0);
	pf_finishdtoa_e(*str, exp, i, nbr);
	return (size);
}

#undef FCHK
