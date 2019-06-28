/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_g_f.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 20:35:30 by callen            #+#    #+#             */
/*   Updated: 2019/06/06 12:13:41 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static void	pf_initflags_g_f(int opt[4], int size, t_flags *flags, char c)
{
	ADDORSPACE = (FLAGS & (FADD + FSPACE)) > 0 && c != '-';
	BLANKS = flags->blanks - size - ADDORSPACE;
	SUB = BLANKS > 0 && !(FLAGS & FSUB) && (FLAGS & FZE) && c == '-';
}

static int	pf_getflags_g_f(int size, char *str, t_flags *flags)
{
	int		opt[4];

	pf_initflags_g_f(opt, size, flags, str[0]);
	if (BLANKS > 0 && !(FLAGS & FSUB) && !(FLAGS & FZE))
		ft_printf_strnew(' ', BLANKS, FD);
	if (FLAGS & FADD && str[0] != '-')
		pf_buffer(FD, "+", 1);
	else if (FLAGS & FSPACE && str[0] != '-')
		pf_buffer(FD, " ", 1);
	if (SUB)
		pf_buffer(FD, str, 1);
	if (BLANKS > 0 && !(FLAGS & FSUB) && (FLAGS & FZE))
		ft_printf_strnew('0', BLANKS, FD);
	pf_buffer(FD, str + SUB, size - SUB);
	if (BLANKS > 0 && (FLAGS & FSUB))
		ft_printf_strnew(' ', BLANKS, FD);
	return (size + ADDORSPACE + BLANKS * (BLANKS > 0));
}

static void	pf_precision_g_f(char *str)
{
	if (*str >= '5')
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
}

static int	pf_truncate_g_f(char *str)
{
	int		i;

	i = 0;
	while (*(str - i) == '0')
		i++;
	return (i);
}

int			ft_printf_g_f(double nbr, t_flags *flags)
{
	int		size;
	char	*str;

	size = ft_printf_dtoa_g_f(nbr, flags, &str);
	if (flags->prec > 0)
	{
		pf_precision_g_f(str + size);
		size -= pf_truncate_g_f(str + size - 1);
	}
	size = pf_getflags_g_f(size, str, flags);
	free(str);
	return (size);
}
