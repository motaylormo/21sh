/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_dtoa_la.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 20:36:11 by callen            #+#    #+#             */
/*   Updated: 2019/06/06 14:02:06 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

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
	while (*nbr >= 2)
	{
		*nbr /= 2;
		(*exp)++;
	}
	while (*nbr < 1)
	{
		*nbr *= 2;
		(*exp)--;
	}
	if (*sub)
		*i = 1;
	else
		*i = 0;
}

static void	pf_finishdtoa_e(char *str, int exp, int i, long double nbr)
{
	i += ft_printf_itoa_a(exp, str + i);
	str[i] = (int)((nbr - (int)nbr) * 10) + '0';
	str[i + 1] = '\0';
}

static char	pf_getchar_e(int nb, int up)
{
	if (nb < 10)
		return (nb + '0');
	return (nb - 10 + 'a' - 32 * up);
}

int			ft_printf_dtoa_la(long double nbr, t_flags *flags, char **str)
{
	int		exp;
	int		sub;
	int		size;
	int		i;

	pf_initdtoa_e(&nbr, &sub, &exp, &i);
	flags->prec += 13 * (!(FLAGS & FPREC));
	size = 1 + flags->prec + (flags->prec > 0) + sub;
	if (!(*str = (char *)malloc(sizeof(**str) * (size + 2 + sub))))
		ft_puterr("malloc error in ft_dtoa_la.c");
	if (sub)
		(*str)[0] = '-';
	(*str)[i] = (int)nbr + '0';
	i += 1 + (flags->prec > 0);
	if (flags->prec > 0)
		(*str)[i - 1] = '.';
	while (i < flags->prec + 1 + (flags->prec > 0) + sub)
	{
		nbr = (nbr - (int)nbr) * 16;
		(*str)[i] = pf_getchar_e((int)nbr, (FLAGS & FUP) > 0);
		i++;
	}
	(*str)[i] = 'p' - 32 * ((FLAGS & FUP) > 0);
	pf_finishdtoa_e(*str + 1, exp, i, nbr);
	return (size);
}
