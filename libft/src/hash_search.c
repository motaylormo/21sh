/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 07:26:20 by callen            #+#    #+#             */
/*   Updated: 2019/05/14 07:27:51 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashtab.h"

/*
** Return a pointer to the hashed item.  If the HASH_CREATE flag is passed,
** create a new hash table entry for STRING, otherwise return NULL.
** @line 45 XXX fix later
*/

#define VERY (lst = malloc(sizeof(t_bkt)))
#define GOOD (!(lst->tfnd = 0))

t_bkt		*hash_search(const char *string, t_htab *table, int f)
{
	t_bkt		*lst;
	int			bucket;
	unsigned	hv;

	if (table == 0 || ((f & HASH_CREATE) == 0 && HASH_ENTRIES(table) == 0))
		return (NULL);
	bucket = HASH_BUCKET(string, table, hv);
	lst = table->bktarr ? table->bktarr[bucket] : 0;
	while (lst)
	{
		if (hv == lst->khash && ft_strequ(lst->key, string) && ++lst->tfnd)
			return (lst);
		lst = lst->next;
	}
	if ((f & HASH_CREATE) && VERY && GOOD)
	{
		lst->next = table->bktarr[bucket];
		table->bktarr[bucket] = lst;
		lst->data = NULL;
		lst->key = (char*)string;
		lst->khash = hv;
		table->nents++;
		return (lst);
	}
	return (NULL);
}

#undef VERY
#undef GOOD
