/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_dtoa_g_f.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 20:36:15 by callen            #+#    #+#             */
/*   Updated: 2019/06/06 11:54:35 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static int	pf_fpclassify_g_f(double n)
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
#define FCHK(nbr) (pf_fpclassify_g_f((nbr)) < FP_ZER)

int			ft_printf_dtoa_g_f(double nbr, t_flags *flags, char **str)
{
	int		size;
	int		i;
	char	*ent;
	char	*dec;

	size = ft_printf_dtoa_ent(nbr, &ent, !(FLAGS & FUP));
	flags->prec += (!(FLAGS & FPREC)) * 6 - size + (nbr < 0);
	if (!flags->prec || !FCHK(nbr))
	{
		*str = ent;
		return (size);
	}
	if (!(dec = malloc(sizeof(*dec) * (flags->prec + 3))))
		ft_puterr("malloc error in ft_printf_dtoa_g_f.c");
	dec[0] = '.';
	i = 1;
	while (i < flags->prec + 2)
	{
		nbr = (nbr - (int)nbr) * 10 * (-2 * (nbr < 0) + 1);
		dec[i] = ((int)(nbr) % 10) + '0';
		i++;
	}
	dec[i] = '\0';
	*str = ft_strjoin_free(ent, dec, 'L' + 'R');
	return (size + flags->prec + 1);
}

#undef FCHK
