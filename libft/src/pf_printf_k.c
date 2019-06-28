/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_k.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 00:51:45 by callen            #+#    #+#             */
/*   Updated: 2019/06/06 12:21:43 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static int	pf_getflags_k(int size, char *str, t_flags *flags)
{
	int		sp;

	sp = flags->blanks - size;
	if (!(flags->flags & FSUB) && sp > 0)
		ft_printf_strnew(' ' + 16 * ((FLAGS & FZE) > 0), sp, FD);
	pf_buffer(FD, str, size);
	if (flags->flags & FSUB && sp > 0)
		ft_printf_strnew(' ', sp, FD);
	return (size + sp * (sp > 0));
}

int			ft_printf_k(t_flags *flags, va_list ap)
{
	int		size;
	char	*str;
	time_t	k;

	k = va_arg(ap, time_t);
	if (!(FLAGS & FPREC))
		flags->prec = 2;
	size = ft_printf_ktoa(k, &str);
	size = pf_getflags_k(size, str, flags);
	free(str);
	return (size);
}
