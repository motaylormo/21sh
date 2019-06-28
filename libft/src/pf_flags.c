/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 20:30:00 by callen            #+#    #+#             */
/*   Updated: 2019/06/27 20:28:40 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static t_pars	pf_fill_fltab(uint32_t u, void (*f)(t_flags *, uint32_t,
								char **, va_list))
{
	t_pars ret;

	ret.u = u;
	ret.f = f;
	return (ret);
}

/*
** TODO: dollar sign and apostrophe
*/

static void		ft_fill_tab(t_pars *f)
{
	(f)[' '] = pf_fill_fltab(FSPACE, ft_fillflags);
	(f)['#'] = pf_fill_fltab(FHT, ft_fillflags);
	(f)['$'] = pf_fill_fltab(FDOL, pf_dollarsign);
	(f)['*'] = pf_fill_fltab(0, ft_padding);
	(f)['+'] = pf_fill_fltab(FADD, ft_fillflags);
	(f)['-'] = pf_fill_fltab(FSUB, ft_fillflags);
	(f)['.'] = pf_fill_fltab(FPREC, ft_precs);
	(f)['0'] = pf_fill_fltab(FZE, ft_fillflags);
	(f)['1'] = pf_fill_fltab(0, ft_padding);
	(f)['2'] = pf_fill_fltab(0, ft_padding);
	(f)['3'] = pf_fill_fltab(0, ft_padding);
	(f)['4'] = pf_fill_fltab(0, ft_padding);
	(f)['5'] = pf_fill_fltab(0, ft_padding);
	(f)['6'] = pf_fill_fltab(0, ft_padding);
	(f)['7'] = pf_fill_fltab(0, ft_padding);
	(f)['8'] = pf_fill_fltab(0, ft_padding);
	(f)['9'] = pf_fill_fltab(0, ft_padding);
	(f)['L'] = pf_fill_fltab(FL2, ft_fillflags);
	(f)['h'] = pf_fill_fltab(FH, ft_type);
	(f)['j'] = pf_fill_fltab(FJ, ft_type);
	(f)['l'] = pf_fill_fltab(FL, ft_type);
	(f)['z'] = pf_fill_fltab(FZ, ft_type);
}

void			pf_dollarsign(t_flags *flags, uint32_t u, char **str,
		va_list ap)
{
	(void)u;
	(void)ap;
	(*str)++;
	if (str && *str && **str == '$')
	{
		FLAGS |= FDOL;
		return ;
	}
}

void			ft_flags(char **str, t_flags *flags, va_list ap)
{
	static t_pars f[256];

	if (f[' '].u != FSPACE)
		ft_fill_tab((t_pars*)(&f));
	(*f[(int)**str].f)(flags, f[(int)**str].u, str, ap);
}
