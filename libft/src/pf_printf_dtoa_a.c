/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_dtoa_a.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 20:36:31 by callen            #+#    #+#             */
/*   Updated: 2019/06/06 11:52:43 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static int	pf_fpclassify_a(double n)
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
#define FCHK(nbr) (pf_fpclassify_a((nbr)) < FP_ZER)

static void	pf_initdtoa_a(double *nbr, int *sub, int *exp, int *i)
{
	if (*nbr < 0.0)
	{
		*sub = 1;
		*nbr = -*nbr;
	}
	else
		*sub = 0;
	*exp = 0;
	while (*nbr >= 2.0)
	{
		*nbr /= 2;
		(*exp)++;
	}
	while (*nbr && *nbr < 1.0)
	{
		*nbr *= 2;
		(*exp)--;
	}
	if (*sub)
		*i = 1;
	else
		*i = 0;
}

static void	pf_finishdtoa_a(char *str, int exp, int i, double nbr)
{
	i += ft_printf_itoa_a(exp, str + i);
	str[i] = (int)((nbr - (int)nbr) * 10) + '0';
	str[i + 1] = '\0';
}

static char	pf_getchar(int nb, int up)
{
	if (nb < 10)
		return (nb + '0');
	return ((nb - 10 + 'a') - (32 * up));
}

int			ft_printf_dtoa_a(double nbr, t_flags *flags, char **str)
{
	int		exp;
	int		sub;
	int		size;
	int		i;

	pf_initdtoa_a(&nbr, &sub, &exp, &i);
	flags->prec = (!FCHK(nbr) * flags->prec) + (1 * (!(FLAGS & FPREC)));
	size = 1 + flags->prec + (flags->prec > 0) + sub;
	if (!(*str = malloc(sizeof(**str) * (size + 2 + sub))))
		ft_puterr("malloc error in ft_printf_dtoa_a.c");
	if (sub)
		(*str)[0] = '-';
	(*str)[i] = (int)nbr + '0';
	i += (1 + (flags->prec > 0));
	if (flags->prec > 0 && exp && ((nbr - (int)nbr) / 16))
		(*str)[i - 1] = '.';
	while (i < flags->prec + 1 + (flags->prec > 0) + sub)
	{
		nbr = (nbr - (int)nbr) * 16;
		(*str)[i] = pf_getchar((int)nbr, (FLAGS & FUP) > 0);
		i++;
	}
	(*str)[i] = 'p' - (32 * ((FLAGS & FUP) > 0));
	pf_finishdtoa_a(*str + 1, exp, i, nbr);
	return (size);
}

#undef FCHK
