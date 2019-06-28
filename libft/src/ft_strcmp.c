/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 22:27:38 by callen            #+#    #+#             */
/*   Updated: 2019/05/15 20:04:50 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/*
** Compare s1 and s2 returning less than, equal to or greater than zero
** if s1 is lexicographically less than, equal to or greater than s2.
**  -- adapted from Gnu C Library
*/

int		ft_strcmp(const char *s1, const char *s2)
{
	register const unsigned char	*p1;
	register const unsigned char	*p2;
	unsigned char					c1;
	unsigned char					c2;

	p1 = (const unsigned char*)s1;
	p2 = (const unsigned char*)s2;
	c1 = 0;
	c2 = 0;
	while (c1 == c2)
	{
		c1 = (unsigned char)*s1++;
		c2 = (unsigned char)*s2++;
		if (c1 == '\0')
			return (c1 - c2);
	}
	return (c1 - c2);
}
