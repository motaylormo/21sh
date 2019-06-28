/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_per.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 20:36:49 by callen            #+#    #+#             */
/*   Updated: 2019/06/06 13:42:53 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static void	init_opts(int *tab)
{
	(tab)[' '] = 1;
	(tab)['$'] = 1;
	(tab)['#'] = 1;
	(tab)['*'] = 1;
	(tab)['+'] = 1;
	(tab)['-'] = 1;
	(tab)['.'] = 1;
	(tab)['0'] = 1;
	(tab)['1'] = 1;
	(tab)['2'] = 1;
	(tab)['3'] = 1;
	(tab)['4'] = 1;
	(tab)['5'] = 1;
	(tab)['6'] = 1;
	(tab)['7'] = 1;
	(tab)['8'] = 1;
	(tab)['9'] = 1;
	(tab)['L'] = 1;
	(tab)['h'] = 1;
	(tab)['l'] = 1;
	(tab)['j'] = 1;
	(tab)['z'] = 1;
}

static int	ft_if(char c)
{
	static int	tab[256] = {0};

	if (!tab[' '])
		init_opts((int*)(&tab));
	return (tab[(int)c]);
}

static void	ft_seg(char **str, t_flags *flags, va_list ap)
{
	(*str)++;
	while (ft_if(**str))
	{
		ft_flags(str, flags, ap);
		(*str)++;
	}
}

static void	ft_initstruct(t_flags *flags)
{
	flags->blanks = 0;
	flags->prec = 0;
	flags->flags = 0;
	flags->type = 0;
}

int			ft_per(char **str, t_flags *flags, va_list ap)
{
	int nb;

	ft_initstruct(flags);
	ft_seg(str, flags, ap);
	if ((nb = ft_conv(**str, ap, flags)) == -1)
		return (-1);
	else if (nb == -2)
	{
		nb = 0;
		(*str)--;
	}
	else if (nb == -3)
		nb = ft_printf_ind(**str, flags);
	return (nb);
}
