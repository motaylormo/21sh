/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 22:42:12 by callen            #+#    #+#             */
/*   Updated: 2018/09/23 22:42:14 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	void	*res;

	res = dst;
	if (dst < src)
		while ((size_t)(dst - res) < len)
			*(uint8_t *)dst++ = *(uint8_t *)src++;
	else
		while (len-- > 0)
			((uint8_t *)dst)[len] = ((uint8_t *)src)[len];
	return (res);
}
