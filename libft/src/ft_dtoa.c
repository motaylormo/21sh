/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 10:20:58 by callen            #+#    #+#             */
/*   Updated: 2019/03/24 15:44:18 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	fill_ipart_d(double n, char *str, int i)
{
	double	d;
	double	tmp;
	int		dig;

	d = 1;
	tmp = n / 10;
	while (d <= tmp)
		d *= 10;
	while (d >= 1)
	{
		dig = (int)(n / d);
		str[++i] = ITOCB(dig, 10);
		n -= d * dig;
		d /= 10;
	}
	return (i);
}

static int	ft_fpclassify(double n)
{
	const t_dbl	u = {n};
	int			e;

	e = u.i >> 52 & 0x7ff;
	if (!e)
		return (u.i << 1 ? FP_SUB : FP_ZER);
	if (e == 0x7ff)
		return (u.i << 12 ? FP_NAN : FP_INF);
	return (FP_NOR);
}

static int	check_dbl(double n, char *s)
{
	const int fp = ft_fpclassify(n);
	const int ninf = (n < 0);

	if (fp == FP_NAN)
	{
		s[0] = 'n';
		s[1] = 'a';
		s[2] = 'n';
		s[3] = '\0';
		return (3);
	}
	else if (fp == FP_INF)
	{
		s[0] = ninf ? '-' : 'i';
		s[1] = ninf ? 'i' : 'n';
		s[2] = ninf ? 'n' : 'f';
		s[3] = ninf ? 'f' : '\0';
		s[4] = '\0';
		return (3);
	}
	else
		return (0);
}

char		*ft_dtoa(double n, uint32_t p)
{
	char	str[1024];
	int		i;

	if (check_dbl(n, str))
		return (ft_strdup(str));
	i = -1;
	if (n < 0)
	{
		str[++i] = '-';
		n *= -1.0;
	}
	i = fill_ipart_d(n, str, i);
	if (p)
	{
		str[++i] = '.';
		while (p)
		{
			n = 10 * (n - (uint64_t)n);
			str[++i] = ITOCB((uint64_t)n, 10);
			--p;
		}
	}
	str[++i] = '\0';
	return (ft_strdup(str));
}
