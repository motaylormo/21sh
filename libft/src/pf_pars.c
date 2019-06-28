/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 20:36:51 by callen            #+#    #+#             */
/*   Updated: 2019/01/10 14:10:27 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

void	ft_padding(t_flags *flags, uint32_t u, char **str, va_list ap)
{
	(void)u;
	if (**str == '*')
	{
		flags->blanks = va_arg(ap, int);
		if (flags->blanks < 0)
		{
			FLAGS |= FSUB;
			flags->blanks *= -1;
		}
		return ;
	}
	flags->blanks = 0;
	while (**str >= '0' && **str <= '9')
	{
		flags->blanks = flags->blanks * 10 + **str - '0';
		(*str)++;
	}
	(*str)--;
}

void	ft_precs(t_flags *flags, uint32_t u, char **str, va_list ap)
{
	(void)u;
	(*str)++;
	if (**str == '*')
	{
		flags->prec = va_arg(ap, int);
		if (flags->prec >= 0)
			FLAGS |= FPREC;
		return ;
	}
	FLAGS |= FPREC;
	flags->prec = 0;
	while (**str >= '0' && **str <= '9')
	{
		flags->prec = flags->prec * 10 + **str - '0';
		(*str)++;
	}
	(*str)--;
}

void	ft_fillflags(t_flags *flags, uint32_t u, char **str, va_list ap)
{
	(void)str;
	(void)ap;
	FLAGS |= u;
}

void	ft_type(t_flags *flags, uint32_t u, char **str, va_list ap)
{
	(void)str;
	(void)ap;
	if (u > TYPE)
		TYPE = u;
	else if (u == TYPE && u == FH)
		TYPE = FHH;
	else if (u == TYPE && u == FL)
		TYPE = FLL;
}
