/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_itoa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 00:51:30 by callen            #+#    #+#             */
/*   Updated: 2019/06/06 12:19:53 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static void	pf_init_itoa(t_sll *nbr, int *size, int *i, int *sub)
{
	if (*nbr < 0)
	{
		*sub = 1;
		*size = 2;
		*i = 1;
	}
	else
	{
		*nbr = -*nbr;
		*i = 0;
		*sub = 0;
		*size = 1;
	}
}

int			ft_printf_itoa(t_sll nbr, char **str)
{
	int			size;
	t_sll		d;
	int			i;
	int			sub;

	pf_init_itoa(&nbr, &size, &i, &sub);
	d = -1;
	while (d >= nbr / 10)
	{
		d *= 10;
		size += 1;
	}
	if (!(*str = (char *)malloc(sizeof(**str) * (size + 1))))
		ft_puterr("error malloc in ft_printf_itoa");
	if (sub)
		(*str)[0] = '-';
	while (d < 0)
	{
		(*str)[i] = nbr / d + '0';
		nbr %= d;
		d /= 10;
		i++;
	}
	(*str)[i] = '\0';
	return (size);
}
