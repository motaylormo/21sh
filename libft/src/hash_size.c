/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 07:31:24 by callen            #+#    #+#             */
/*   Updated: 2019/05/14 07:31:27 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashtab.h"

/*
** Return the size of a hash table
*/

int				hash_size(t_htab *table)
{
	return (HASH_ENTRIES(table));
}
