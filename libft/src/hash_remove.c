/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_remove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 07:27:12 by callen            #+#    #+#             */
/*   Updated: 2019/05/15 20:09:59 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashtab.h"

/*
** Remove the item specified by STRING from the hash table TABLE.
** The item removed is returned, so you can free its contents.  If
** the item isn't in this table NULL is returned.
*/

#ifdef PREV
# undef PREV
#endif
#define PREV (void)flags; prev = NULL

t_bkt		*hash_remove(const char *string, t_htab *table, int flags)
{
	int			bkt;
	t_bkt		*prev;
	t_bkt		*temp;
	unsigned	hv;

	if (table == 0 || HASH_ENTRIES(table) == 0)
		return (NULL);
	bkt = HASH_BUCKET(string, table, hv);
	PREV;
	temp = table->bktarr[bkt];
	while (temp)
	{
		if (hv == temp->khash && ft_strequ(temp->key, string))
		{
			if (prev)
				prev->next = temp->next;
			else
				table->bktarr[bkt] = temp->next;
			table->nents--;
			return (temp);
		}
		prev = temp;
		temp = temp->next;
	}
	return (NULL);
}

#undef PREV
