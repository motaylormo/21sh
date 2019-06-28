/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 00:55:22 by callen            #+#    #+#             */
/*   Updated: 2019/06/06 12:48:41 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static int	pf_getflags_s(int size, char *str, t_flags *flags)
{
	int		sp;

	if (size > flags->prec && (FLAGS & FPREC))
		size = flags->prec;
	sp = flags->blanks - size;
	if (!(flags->flags & FSUB) && sp > 0)
		ft_printf_strnew(' ' + 16 * ((FLAGS & FZE) > 0), sp, FD);
	pf_buffer(FD, str, size);
	if (flags->flags & FSUB && sp > 0)
		ft_printf_strnew(' ', sp, FD);
	return (size + sp * (sp > 0));
}

int			ft_printf_s(t_flags *flags, va_list ap)
{
	int		size;
	int		tmp;
	char	*str;

	if (TYPE == FL)
		return (ft_printf_ls(va_arg(ap, wchar_t*), flags));
	str = va_arg(ap, char*);
	tmp = 0;
	if (!str)
	{
		size = 6;
		if (!(str = malloc(sizeof(*str) * 7)))
			ft_puterr("error malloc in ft_printf_s");
		ft_strcpy(str, "(null)");
		tmp = 1;
	}
	else
		size = ft_strlen(str);
	if (flags->prec < 0)
		flags->prec = size;
	size = pf_getflags_s(size, str, flags);
	if (tmp)
		free(str);
	return (size);
}
