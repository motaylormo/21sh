/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_dtoa_lg_le.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 20:35:58 by callen            #+#    #+#             */
/*   Updated: 2019/06/06 12:02:26 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static int	pf_fpclassifyl_lg_le(long double n)
{
	const t_ldbl	u = {.f = n};
	const int		e = u.i.se & 0x7fff;
	const int		msb = u.i.m >> 63;

	if (!e && !msb)
		return (u.i.m ? FP_SUB : FP_ZER);
	if (e == 0x7fff)
	{
		if (__BYTE_ORDER__ == __LITTLE_ENDIAN__ && !msb)
			return (FP_NAN);
		return (u.i.m << 1 ? FP_NAN : FP_INF);
	}
	if (!msb)
		return (FP_NAN);
	return (FP_NOR);
}

#ifdef FCHK
# undef FCHK
#endif
#define FCHK(nbr) (pf_fpclassifyl_lg_le((nbr)) < FP_ZER)

static void	pf_initdtoa_e(long double *nbr, int *sub, int *exp, int *i)
{
	if (*nbr < 0)
	{
		*sub = 1;
		*nbr = -*nbr;
	}
	else
		*sub = 0;
	*exp = 0;
	while (*nbr >= 10)
	{
		*nbr /= 10;
		(*exp)++;
	}
	while (*nbr < 1)
	{
		*nbr *= 10;
		(*exp)--;
	}
	if (*sub)
		*i = 1;
	else
		*i = 0;
}

static void	pf_signdtoa_e(char *str, int exp, int i, long double nbr)
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

int			ft_printf_dtoa_lg_le(long double nbr, t_flags *flags, char **str)
{
	int		exp;
	int		sub;
	int		size;
	int		i;

	pf_initdtoa_e(&nbr, &sub, &exp, &i);
	flags->prec = (!FCHK(nbr) * flags->prec) - (flags->prec != 0);
	size = 5 + flags->prec + (flags->prec > 0) + sub;
	if (!(*str = malloc(sizeof(**str) * (size + 2 + sub))))
		ft_puterr("malloc error in ft_dtoa_lg_le.c");
	if (sub)
		(*str)[0] = '-';
	(*str)[i] = (int)nbr + '0';
	i += 1 + (flags->prec > 0);
	if (flags->prec > 0)
		(*str)[i - 1] = '.';
	while (i < flags->prec + 1 + (flags->prec > 0) + sub)
	{
		nbr = (nbr - (int)nbr) * 10;
		(*str)[i] = ((int)nbr % 10) + '0';
		i++;
	}
	(*str)[i] = 'e' - 32 * ((FLAGS & FUP) > 0);
	pf_signdtoa_e(*str, exp, i, nbr);
	return (size);
}

#undef FCHK
