/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrnul.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 10:32:23 by callen            #+#    #+#             */
/*   Updated: 2019/04/20 10:33:35 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchrnul(const char *s, int c)
{
	c = (unsigned char)c;
	if (!c)
		return ((char*)s + ft_strlen(s));
	while (*s && *(unsigned char*)s != c)
		s++;
	return ((char*)s);
}
