/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getutype.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 20:32:43 by callen            #+#    #+#             */
/*   Updated: 2019/01/10 14:08:07 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

void		ft_typeuint(t_ull *nbr)
{
	*nbr = (unsigned int)(*nbr);
}

void		ft_typeuhh(t_ull *nbr)
{
	*nbr = (unsigned char)(*nbr);
}

void		ft_typeuh(t_ull *nbr)
{
	*nbr = (unsigned short)(*nbr);
}

static void	ft_fill_tab(void (**f)(t_ull *))
{
	(f)[0] = ft_typeuint;
	(f)[FHH] = ft_typeuhh;
	(f)[FH] = ft_typeuh;
	(f)[FJ] = ft_typeuj;
	(f)[FZ] = ft_typeuz;
	(f)[FL] = ft_typeul;
	(f)[FLL] = ft_typeull;
}

void		ft_getutype(uint32_t type, t_ull *nbr)
{
	static void	(*f[7])(t_ull *);

	if (!f[0])
		ft_fill_tab((void (**)(t_ull*))(&f));
	(*f[type])(nbr);
}
