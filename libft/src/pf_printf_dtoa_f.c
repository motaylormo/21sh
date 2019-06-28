/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_dtoa_f.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 20:36:21 by callen            #+#    #+#             */
/*   Updated: 2019/06/06 11:51:58 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static int	pf_fpclassify_f(double n)
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
#define FCHK(nbr) (pf_fpclassify_f((nbr)) < FP_ZER)
#ifdef TOCHAR
# undef TOCHAR
#endif
#define TOCHAR(nbr) ((nbr) < 10 ? (nbr)+'0' : ((nbr)%10)+'0')

int			ft_printf_dtoa_f(double nbr, t_flags *flags, char **str)
{
	int		size;
	int		i;
	char	*ent;
	char	*dec;

	size = ft_printf_dtoa_ent(nbr, &ent, !(FLAGS & FUP));
	flags->prec = (!FCHK(nbr) * flags->prec) + (!(FLAGS & FPREC)) * 6;
	if (!flags->prec)
	{
		*str = ent;
		return (size);
	}
	if (!(dec = malloc(sizeof(*dec) * (flags->prec + 3))))
		ft_puterr("malloc error in ft_printf_dtoa_f.c");
	dec[0] = '.';
	i = 1;
	while (i < flags->prec + 2)
	{
		nbr = (nbr - (int)nbr) * 10 * (-2 * (nbr < 0) + 1);
		dec[i] = TOCHAR((int)(nbr));
		i++;
	}
	dec[i] = '\0';
	*str = ft_strjoin_free(ent, dec, 'L' + 'R');
	return (size + flags->prec + 1);
}

#undef FCHK
#undef TOCHAR
