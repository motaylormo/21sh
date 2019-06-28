/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_n.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 00:55:11 by callen            #+#    #+#             */
/*   Updated: 2019/02/06 18:44:18 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

int			ft_printf_n(t_flags *flags, va_list ap)
{
	void	*p;

	p = va_arg(ap, void*);
	if (p != NULL)
	{
		if (TYPE == FLL)
			*(t_sll*)p = NB;
		else if (TYPE == FZ)
			*(ssize_t*)p = (ssize_t)NB;
		else if (TYPE == FJ)
			*(intmax_t*)p = (intmax_t)NB;
		else if (TYPE == FL)
			*(long*)p = NB;
		else if (TYPE == FH)
			*(short*)p = NB;
		else if (TYPE == FHH)
			*(signed char*)p = NB;
		else
			*(int*)p = NB;
	}
	return (0);
}
