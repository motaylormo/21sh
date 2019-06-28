/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ostrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:08:00 by callen            #+#    #+#             */
/*   Updated: 2019/03/26 16:08:40 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define FT_LOBITS		0x0101010101010101ULL
#define FT_HIBITS		0x8080808080808080ULL
#define CHECK(x) if(!p[x]) return (p - s + x)

size_t	ft_ostrlen(const char *s)
{
	const char		*p = s;
	const uint64_t	*lp;

	while ((uint64_t)p & (sizeof(long) - 1))
		if (*p++ == '\0')
			return (--p - s);
	lp = (const uint64_t*)p;
	while (1)
	{
		if ((*lp - FT_LOBITS) & FT_HIBITS)
		{
			p = (const char*)(lp);
			CHECK(0);
			CHECK(1);
			CHECK(2);
			CHECK(3);
			CHECK(4);
			CHECK(5);
			CHECK(6);
			CHECK(7);
		}
		lp++;
	}
	return (0);
}

#undef FT_LOBITS
#undef FT_HIBITS
#undef CHECK
