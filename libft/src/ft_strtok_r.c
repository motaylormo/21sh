/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 10:37:39 by callen            #+#    #+#             */
/*   Updated: 2019/04/20 10:40:02 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok_r(char *s, const char *sep, char **p)
{
	if (!s && !(s = *p))
		return (NULL);
	s += ft_strspn(s, sep);
	if (!*s)
		return (*p = 0);
	*p = s + (ft_strcspn(s, sep));
	if (**p)
		*(*p)++ = 0;
	else
		*p = 0;
	return (s);
}
