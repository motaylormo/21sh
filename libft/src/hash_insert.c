/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_insert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 19:46:56 by callen            #+#    #+#             */
/*   Updated: 2019/05/14 07:28:58 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashtab.h"

/*
** Create an entry for STRING, in TABLE.  If the entry already
** exists, then return it (unless the HASH_NOSRCH flag is set).
*/

t_bkt		*hash_insert(char *string, t_htab *table, int flags)
{
	t_bkt		*item;
	int			bucket;
	unsigned	hv;

	if (table == 0)
		table = hash_create(0);
	item = (flags & HASH_NOSRCH) ? NULL : hash_search(string, table, 0);
	if (item == 0)
	{
		bucket = HASH_BUCKET(string, table, hv);
		item = malloc(sizeof(t_bkt));
		item->next = table->bktarr[bucket];
		table->bktarr[bucket] = item;
		item->data = NULL;
		item->key = string;
		item->khash = hv;
		item->tfnd = 0;
		table->nents++;
	}
	return (item);
}
