/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 21:08:34 by callen            #+#    #+#             */
/*   Updated: 2019/02/06 21:08:35 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

int		ft_vfprintf(FILE *stream, char *fmt, va_list ap)
{
	return (ft_vdprintf(fileno(stream), fmt, ap));
}

int		ft_fprintf(FILE *stream, char *fmt, ...)
{
	va_list	ap;
	int		nb;

	va_start(ap, fmt);
	nb = ft_vfprintf(stream, fmt, ap);
	va_end(ap);
	return (nb);
}
