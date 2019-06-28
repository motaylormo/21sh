/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 16:30:29 by callen            #+#    #+#             */
/*   Updated: 2018/09/21 16:30:30 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	uint8_t	*tmp;
	size_t	i;

	i = -1;
	tmp = (uint8_t *)dst;
	while (++i < n)
	{
		*(tmp + i) = *((uint8_t *)src + i);
		if (*((uint8_t *)src + i) == (uint8_t)c)
			return (dst + i + 1);
	}
	return (NULL);
}
