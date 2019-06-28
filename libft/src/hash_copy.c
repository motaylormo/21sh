/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_copy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 19:42:51 by callen            #+#    #+#             */
/*   Updated: 2019/05/14 07:32:31 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashtab.h"

static void		alloc_bucket_copy(t_bkt **nb, t_bkt **n)
{
	if (!*n)
	{
		*nb = malloc(sizeof(t_bkt));
		*n = *nb;
	}
	else
	{
		(*n)->next = malloc(sizeof(t_bkt));
		*n = (*n)->next;
	}
}

static t_bkt	*copy_bktarr(t_bkt *ba, t_shstrf *cpdata)
{
	t_bkt	*new_bucket;
	t_bkt	*n;
	t_bkt	*e;

	if (ba == 0)
		return ((t_bkt *)0);
	n = NULL;
	e = ba;
	while (e)
	{
		alloc_bucket_copy(&new_bucket, &n);
		n->key = SAVESTR(e->key);
		n->data = NULL;
		n->data = e->data && cpdata ? (*cpdata)(e->data) : n->data;
		n->data = e->data ? SAVESTR(e->data) : n->data;
		n->khash = e->khash;
		n->tfnd = e->tfnd;
		n->next = NULL;
		e = e->next;
	}
	return (new_bucket);
}

/*
** data copy function
*/

t_htab			*hash_copy(t_htab *table, t_shstrf *cpdata)
{
	t_htab	*new_table;
	int		i;

	if (table == 0)
		return (NULL);
	new_table = hash_create(table->nbkts);
	i = -1;
	while (++i < table->nbkts)
		new_table->bktarr[i] =
			copy_bktarr(table->bktarr[i], cpdata);
	new_table->nents = table->nents;
	return (new_table);
}
