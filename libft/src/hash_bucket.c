/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_bucket.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 07:25:23 by callen            #+#    #+#             */
/*   Updated: 2019/05/14 07:25:47 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashtab.h"

/*
** Return the location of the bucket which should contain the data
** for STRING.  TABLE is a pointer to a t_htab.
*/

int			hash_bucket(const char *string, t_htab *table)
{
	unsigned	h;

	return (HASH_BUCKET(string, table, h));
}
