/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_walk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 07:22:38 by callen            #+#    #+#             */
/*   Updated: 2019/05/14 08:21:25 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashtab.h"

/*
** Traverse the hash table and apply func to each item, stopping if it
** returns less than 0
*/

void		hash_walk(t_htab *table, t_hash_wfunc *func)
{
	register int	i;
	t_bkt			*item;

	if (table == 0 || HASH_ENTRIES(table) == 0)
		return ;
	i = -1;
	while (++i < table->nbkts)
	{
		item = HASH_ITEMS(i, table);
		while (item)
		{
			if ((*func)(item) < 0)
				return ;
			item = item->next;
		}
	}
}
