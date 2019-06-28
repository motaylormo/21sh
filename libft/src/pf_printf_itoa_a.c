/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_itoa_a.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 00:51:12 by callen            #+#    #+#             */
/*   Updated: 2019/06/06 12:20:25 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static void	pf_init_itoa_a(int *nbr, int *size, int *i, int *sub)
{
	*i = 1;
	*size = 2;
	if (*nbr < 0)
		*sub = 1;
	else
	{
		*nbr = -*nbr;
		*sub = 0;
	}
}

int			ft_printf_itoa_a(int nbr, char *str)
{
	int		size;
	int		d;
	int		i;
	int		sub;

	pf_init_itoa_a(&nbr, &size, &i, &sub);
	d = -1;
	while (d >= nbr / 10)
	{
		d *= 10;
		size += 1;
	}
	if (sub)
		str[0] = '-';
	else
		str[0] = '+';
	while (d < 0)
	{
		str[i] = nbr / d + '0';
		nbr %= d;
		d /= 10;
		i++;
	}
	return (size);
}
