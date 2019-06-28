/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_flush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 07:20:24 by callen            #+#    #+#             */
/*   Updated: 2019/05/14 08:24:26 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashtab.h"

/*
** Remove and discard all entries in TABLE.  If FREE_DATA is non-null, it
** is a function to call to dispose of a hash item's data.  Otherwise,
** free() is called.
*/

void		hash_flush(t_htab *table, t_shfree *free_data)
{
	int				i;
	register t_bkt	*bkt;
	register t_bkt	*item;

	if (table == 0 || HASH_ENTRIES(table) == 0)
		return ;
	i = -1;
	while (++i < table->nbkts)
	{
		bkt = table->bktarr[i];
		while (bkt)
		{
			item = bkt;
			bkt = bkt->next;
			if (free_data)
				(*free_data)(item->data);
			else
				free(item->data);
			free(item->key);
			free(item);
		}
		table->bktarr[i] = NULL;
	}
	table->nents = 0;
}
