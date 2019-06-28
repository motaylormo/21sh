/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 20:29:38 by callen            #+#    #+#             */
/*   Updated: 2019/06/06 14:01:00 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static void	pf_fill_tab2(int *tab)
{
	(tab)['X'] = 1;
	(tab)['F'] = 1;
	(tab)['E'] = 1;
	(tab)['G'] = 1;
	(tab)['A'] = 1;
	(tab)['B'] = 2;
	(tab)['D'] = 2;
	(tab)['O'] = 2;
	(tab)['U'] = 2;
	(tab)['C'] = 2;
	(tab)['S'] = 2;
}

static void	pf_upper(char *c, t_flags *flags)
{
	static int	tab[256];

	if (!tab['A'])
		pf_fill_tab2((int*)&tab);
	if (tab[(int)*c] == 1)
	{
		FLAGS |= FUP;
		*c += 32;
	}
	else if (tab[(int)*c] == 2)
	{
		if (TYPE < FL)
			TYPE = FL;
		*c += 32;
	}
}

static void	pf_fill_fntab(int (**f)(t_flags *, va_list))
{
	(f)['\0'] = ft_printf_2;
	(f)['%'] = ft_printf_per;
	(f)['a'] = ft_printf_a;
	(f)['b'] = ft_printf_b;
	(f)['c'] = ft_printf_c;
	(f)['d'] = ft_printf_d;
	(f)['e'] = ft_printf_e;
	(f)['f'] = ft_printf_f;
	(f)['g'] = ft_printf_g;
	(f)['i'] = ft_printf_d;
	(f)['k'] = ft_printf_k;
	(f)['n'] = ft_printf_n;
	(f)['o'] = ft_printf_o;
	(f)['p'] = ft_printf_p;
	(f)['s'] = ft_printf_s;
	(f)['u'] = ft_printf_u;
	(f)['x'] = ft_printf_x;
}

int			ft_conv(char c, va_list ap, t_flags *flags)
{
	static int	(*f[256])(t_flags*, va_list) = {ft_printf_3};
	int			nb;

	if (*f == ft_printf_3)
		pf_fill_fntab((int (**)(t_flags*, va_list))(&f));
	pf_upper(&c, flags);
	nb = (*f[(int)c])(flags, ap);
	return (nb);
}
