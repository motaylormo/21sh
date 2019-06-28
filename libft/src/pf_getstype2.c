/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getstype2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 20:31:08 by callen            #+#    #+#             */
/*   Updated: 2019/01/10 14:07:54 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

void	ft_typesj(t_sll *nbr)
{
	*nbr = (intmax_t)(*nbr);
}

void	ft_typesz(t_sll *nbr)
{
	*nbr = (ssize_t)(*nbr);
}

void	ft_typesl(t_sll *nbr)
{
	*nbr = (long)(*nbr);
}

void	ft_typesll(t_sll *nbr)
{
	(void)nbr;
}
