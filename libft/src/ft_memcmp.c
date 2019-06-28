/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 22:56:26 by callen            #+#    #+#             */
/*   Updated: 2018/09/23 22:56:28 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const uint8_t	*b1;
	const uint8_t	*b2;

	b1 = (const uint8_t *)s1;
	b2 = (const uint8_t *)s2;
	while (n--)
	{
		if (*b1 != *b2)
			return ((int)(*b1 - *b2));
		b1++;
		b2++;
	}
	return (0);
}
