/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_dtoa_ent.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 20:36:24 by callen            #+#    #+#             */
/*   Updated: 2019/06/06 11:49:22 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static int	pf_fpclassify_ent(double n)
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

static void	pf_init_ent(double *nbr, int *size, int *i, int *sub)
{
	*sub = pf_fpclassify_ent(*nbr);
	if (*sub <= 1)
	{
		*size = (t_dbl){*nbr}.i >> 63 == 1 && *sub ? 4 : 3;
		*sub |= 0x7ff00000;
		*i = *nbr < 0 ? 1 : 0;
	}
	else if (*nbr < 0)
	{
		*nbr = -*nbr;
		*sub = 1;
		*size = 2;
		*i = 1;
	}
	else
	{
		*i = 0;
		*sub = 0;
		*size = 1;
	}
}

static int	pf_dblstralloc_ent(char **str, int size, int sub, int up)
{
	if (!(*str = malloc(sizeof(**str) * (size + 1))))
		ft_puterr("malloc error in ft_printf_dtoa_ent.c");
	if ((sub ^ 0x7ff00000) == 1)
	{
		(*str)[0] = (size == 5) ? '-' : 'i' - 32 * !up;
		(*str)[1] = (size == 5) ? 'i' - 32 * !up : 'n' - 32 * !up;
		(*str)[2] = (size == 5) ? 'n' - 32 * !up : 'f' - 32 * !up;
		(*str)[3] = (size == 5) ? 'f' - 32 * !up : '\0';
		(*str)[4] = '\0';
		return (1);
	}
	else if ((sub ^ 0x7ff00000) == 0)
	{
		(*str)[0] = 'n' - 32 * !up;
		(*str)[1] = 'a' - 32 * !up;
		(*str)[2] = 'n' - 32 * !up;
		(*str)[3] = '\0';
		return (1);
	}
	return (0);
}

int			ft_printf_dtoa_ent(double nbr, char **str, int up)
{
	int			size;
	double		d;
	int			i;
	int			sub;

	pf_init_ent(&nbr, &size, &i, &sub);
	d = 1;
	while (d <= nbr / 10 && sub <= 1)
	{
		d *= 10;
		size += 1;
	}
	RET_IF(pf_dblstralloc_ent(str, size + 1, sub, up), size);
	if (sub)
		(*str)[0] = '-';
	while (d >= 1)
	{
		(*str)[i] = (int)(nbr / d) + '0';
		while (nbr >= d)
			nbr -= d;
		d /= 10;
		i++;
	}
	(*str)[i] = '\0';
	return (size);
}
