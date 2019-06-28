/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_dispose.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 07:21:11 by callen            #+#    #+#             */
/*   Updated: 2019/05/14 08:25:46 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashtab.h"

/*
** Free the hash table pointed to by TABLE.
*/

void		hash_dispose(t_htab *table)
{
	free(table->bktarr);
	free(table);
}
