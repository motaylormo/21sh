/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_itoa_base.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 00:50:22 by callen            #+#    #+#             */
/*   Updated: 2019/06/06 12:21:03 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static char	pf_getchar_itoab(int n, int up)
{
	if (n < 10)
		return (n + '0');
	return (n - 10 + 'a' - 32 * up);
}

int			ft_printf_itoa_base(t_ull nbr, int base, char **str, int up)
{
	int			size;
	t_ull		d;
	int			i;

	size = 1;
	d = 1;
	while (d <= nbr / base)
	{
		d *= base;
		size += 1;
	}
	if (!(*str = (char *)malloc(sizeof(**str) * (size + 1))))
		ft_puterr("malloc error in ft_printf_itoa_base");
	i = 0;
	while (d > 0)
	{
		(*str)[i] = pf_getchar_itoab(nbr / d, up);
		nbr %= d;
		d /= base;
		i++;
	}
	(*str)[i] = '\0';
	return (size);
}
