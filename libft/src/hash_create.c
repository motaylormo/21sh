/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 07:30:33 by callen            #+#    #+#             */
/*   Updated: 2019/05/14 07:30:36 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashtab.h"

/*
** Make a new hash table with BUCKETS number of buckets.  Initialize
** each slot in the table to NULL.
*/

t_htab			*hash_create(int buckets)
{
	t_htab			*new_table;
	register int	i;

	new_table = malloc(sizeof(t_htab));
	if (buckets == 0)
		buckets = DEFAULT_HASH_BUCKETS;
	new_table->bktarr = malloc(buckets * sizeof(t_bkt*));
	new_table->nbkts = buckets;
	new_table->nents = 0;
	i = -1;
	while (++i < buckets)
		new_table->bktarr[i] = NULL;
	return (new_table);
}
