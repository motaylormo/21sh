/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_dtoa_lg_lf.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 20:35:52 by callen            #+#    #+#             */
/*   Updated: 2019/06/06 12:03:00 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static int	pf_fpclassifyl_lg_lf(long double n)
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
#define FCHK(nbr) (pf_fpclassifyl_lg_lf((nbr)) < FP_ZER)
#ifdef FCHKPREC
# undef FCHKPREC
#endif
#define FCHKPREC(nbr) (!FCHK((nbr)) * flags->prec)

int			ft_printf_dtoa_lg_lf(long double nbr, t_flags *flags, char **str)
{
	int		size;
	int		i;
	char	*ent;
	char	*dec;

	size = ft_printf_dtoa_lent(nbr, &ent, !(FLAGS & FUP));
	flags->prec = FCHKPREC(nbr) + (!(FLAGS & FPREC)) * 6 - size + (nbr < 0);
	if (!flags->prec)
	{
		*str = ent;
		return (size);
	}
	if (!(dec = malloc(sizeof(*dec) * (flags->prec + 3))))
		ft_puterr("malloc error in ft_printf_dtoa_lg_lf.c");
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

#undef FCHKPREC
#undef FCHK
