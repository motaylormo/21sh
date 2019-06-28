/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 20:36:46 by callen            #+#    #+#             */
/*   Updated: 2019/06/06 13:46:30 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static int	internal_printf(char *fmt, t_flags *flags, va_list ap)
{
	while (*fmt)
	{
		if (*fmt == '%')
		{
			if ((NB += ft_per(&fmt, flags, ap)) == -1)
				return (-1);
		}
		else if (*fmt == '{')
			NB += pf_color(&fmt, FD);
		else
		{
			pf_buffer(FD, fmt, 1);
			NB++;
		}
		fmt++;
	}
	pf_buffer(FD, NULL, -1);
	return (0);
}

int			ft_vdprintf(int fd, char *fmt, va_list ap)
{
	t_flags	flags;

	flags.fd = fd;
	flags.nb = 0;
	if (internal_printf(fmt, &flags, ap) < 0)
		return (-1);
	return (flags.nb);
}

int			ft_vprintf(char *fmt, va_list ap)
{
	t_flags	flags;

	flags.fd = STDOUT_FILENO;
	flags.nb = 0;
	if (internal_printf(fmt, &flags, ap) < 0)
		return (-1);
	return (flags.nb);
}

int			ft_printf(char *fmt, ...)
{
	va_list	ap;
	int		nb;

	va_start(ap, fmt);
	nb = ft_vdprintf(STDOUT_FILENO, fmt, ap);
	va_end(ap);
	return (nb);
}

int			ft_dprintf(int fd, char *fmt, ...)
{
	va_list	ap;
	int		nb;

	va_start(ap, fmt);
	nb = ft_vdprintf(fd, fmt, ap);
	va_end(ap);
	return (nb);
}
