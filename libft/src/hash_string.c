/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 07:24:40 by callen            #+#    #+#             */
/*   Updated: 2019/05/14 07:24:57 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashtab.h"

/*
** This is the best 32-bit string hash function I found. It's one of the
** Fowler-Noll-Vo family (FNV-1).
** The magic is in the interesting relationship between the special prime
** 16777619 (2^24 + 403) and 2^32 and 2^8.
*/

#define FNV_OFFSET 2166136261
#define FNV_PRIME 16777619

/*
** If you want to use 64 bits, use
** FNV_OFFSET	14695981039346656037
** FNV_PRIMT	1099511628211
*/

/*
** The `khash' check below requires that strings that compare equally with
** strcmp hash to the same value.
*/

unsigned	hash_string(const char *s)
{
	register unsigned	i;

	i = FNV_OFFSET;
	while (*s)
	{
		i *= FNV_PRIME;
		i ^= *s;
		s++;
	}
	return (i);
}
