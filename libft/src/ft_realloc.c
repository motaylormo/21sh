/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 19:03:05 by callen            #+#    #+#             */
/*   Updated: 2019/05/23 22:34:23 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *p, size_t len, size_t size)
{
	void *tmp;

	if (!(tmp = malloc(size)))
		ft_puterr("libft error: ft_realloc: malloc failed");
	if (!p)
		return (tmp);
	ft_memcpy(tmp, p, len);
	free(p);
	return (tmp);
}
