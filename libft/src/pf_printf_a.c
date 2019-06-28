/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 20:36:43 by callen            #+#    #+#             */
/*   Updated: 2019/06/06 11:38:46 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static void	pf_initflags_a(int opt[4], int size, t_flags *flags, char c)
{
	ADDORSPACE = (FLAGS & (FADD + FSPACE)) > 0 && c != '-';
	BLANKS = flags->blanks - size - ADDORSPACE;
	SUB = c == '-';
}

static int	pf_getflags_a(int size, char *str, t_flags *flags)
{
	int		opt[4];

	pf_initflags_a(opt, size, flags, str[0]);
	if (BLANKS > 0 && !(FLAGS & FSUB) && !(FLAGS & FZE))
		ft_printf_strnew(' ', BLANKS, FD);
	if (FLAGS & FADD && str[0] != '-')
		pf_buffer(FD, "+", 1);
	else if (FLAGS & FSPACE && str[0] != '-')
		pf_buffer(FD, " ", 1);
	if (SUB)
		pf_buffer(FD, str, 1);
	if (FLAGS & FUP)
		pf_buffer(FD, "0X", 2);
	else
		pf_buffer(FD, "0x", 2);
	if (BLANKS > 0 && !(FLAGS & FSUB) && (FLAGS & FZE))
		ft_printf_strnew('0', BLANKS, FD);
	pf_buffer(FD, str + SUB, size - SUB);
	if (BLANKS > 0 && (FLAGS & FSUB))
		ft_printf_strnew(' ', BLANKS, FD);
	return (size + ADDORSPACE + BLANKS * (BLANKS > 0) + 2);
}

static int	pf_precision_a(char *str)
{
	int		size;

	size = ft_strlen(str);
	if (*(str + size - 1) >= '5')
	{
		while (*(str - 1) == '9')
		{
			str--;
			*str = '0';
		}
		str--;
		if (*str != '.')
			*str += 1;
		else
			*(str - 1) += 1;
	}
	return (size);
}

static int	pf_truncate_a(char *str)
{
	int		i;

	i = 0;
	while (*(str - i) == '0')
		i++;
	if (i > 0)
		ft_memmove(str - i + 1, str + 1, ft_strlen(str));
	return (i);
}

int			ft_printf_a(t_flags *flags, va_list ap)
{
	int		size;
	int		len;
	char	*str;
	double	nbr;

	if (FLAGS & FL2)
		return (ft_printf_la(va_arg(ap, long double), flags));
	nbr = va_arg(ap, double);
	len = 0;
	size = ft_printf_dtoa_a(nbr, flags, &str);
	if (flags->prec >= 0)
	{
		len = pf_precision_a(str + size);
		size -= pf_truncate_a(str + size - 1);
	}
	size = pf_getflags_a(size + len - 1, str, flags);
	free(str);
	return (size);
}
