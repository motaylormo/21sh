/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 21:37:11 by callen            #+#    #+#             */
/*   Updated: 2019/05/27 21:47:33 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*s2;

	if ((s2 = malloc(n + 1)) == NULL)
		return (NULL);
	ft_memcpy(s2, s1, n);
	s2[n] = '\0';
	return (s2);
}
