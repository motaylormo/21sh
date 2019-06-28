/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 15:19:17 by callen            #+#    #+#             */
/*   Updated: 2019/03/06 15:15:44 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define X(a) ((a) == 'x' || (a) == 'X')

/*
** Lookup table for digit values. -1==255>=36 -> invalid
*/

static const unsigned char g_tbl[] = { -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -1, -1, -1, -1, -1, -1,
	-1, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
	25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, -1, -1, -1, -1, -1,
	-1, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
	25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
};

static inline void	conv(const uint8_t *v, const char *s, int b, int h[3])
{
	while (1)
	{
		if (v[h[2]] < b)
			h[0] = h[0] * b + v[h[2]];
		else
			break ;
		h[2] = *s++;
	}
}

int					ft_atoi_base(const char *s, int b)
{
	const uint8_t	*v = g_tbl + 1;
	int				h[3];

	h[0] = 0;
	h[1] = 0;
	while (ft_isspace(h[2] = *s++))
		;
	if (h[2] == '+' || h[2] == '-')
	{
		h[1] = -(h[2] == '-');
		h[2] = *s++;
	}
	if ((b == 0 || b == 16) && h[2] == '0' && X(*s) && v[h[2]] < b)
	{
		h[2] = s[1];
		s += 2;
		b = 16;
	}
	if (b == 0)
		b = (!v[h[2]] ? 8 : 10);
	conv(v, s, b, h);
	return ((h[0] ^ h[1]) - h[1]);
}