/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 16:15:47 by callen            #+#    #+#             */
/*   Updated: 2018/09/21 16:15:50 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	uint8_t			*dstb;
	uint8_t const	*srcb;

	dstb = dst;
	srcb = src;
	while (n--)
		*dstb++ = *srcb++;
	return (dst);
}
