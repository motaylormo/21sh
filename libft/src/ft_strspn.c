/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 10:34:31 by callen            #+#    #+#             */
/*   Updated: 2019/04/20 13:55:51 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define BITOP_A(a,b) ((a)[(size_t)(b) / (8 * sizeof(*(a)))])
#define BITOP_B(a,b) ((size_t)1 << ((size_t)(b) % (8 * sizeof(*(a)))))
#define BITOP_AND(a,b) (BITOP_A(a,b) & BITOP_B(a,b))
#define BITOP_OREQ(a,b) (BITOP_A(a,b) |= BITOP_B(a,b))

size_t	ft_strspn(const char *s, const char *c)
{
	const char	*a = s;
	size_t		byteset[32 / sizeof(size_t)];

	if (!c[0])
		return (0);
	if (!c[1])
	{
		while (*s == *c)
			s++;
		return (s - a);
	}
	ft_memset(byteset, 0, sizeof(byteset));
	while (*c && (BITOP_OREQ(byteset, *(unsigned char*)c)))
		c++;
	while (*s && (BITOP_AND(byteset, *(unsigned char*)s)))
		s++;
	return (s - a);
}

#undef BITOP_AND
#undef BITOP_OREQ
#undef BITOP_A
#undef BITOP_B
