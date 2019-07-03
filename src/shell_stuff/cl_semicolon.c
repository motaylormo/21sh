/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 12:53:41 by mtaylor           #+#    #+#             */
/*   Updated: 2019/06/21 12:53:42 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

#define QUOTES(c)	((c == '"') || (c == '\''))

/*
**	command lines seperated by ';'
*/

int			count_cls(char *str)
{
	int	count;

	count = (str) ? 1 : 0;
	while (*str)
	{
		if (QUOTES(*str) && ft_strchr(str + 1, *str))
			str = ft_strchr(str + 1, *str) + 1;
		else if (*str == ';')
		{
			while (*str == ';')
			{
				*str = '\0';
				str++;
			}
			if (*str)
				count++;
		}
		else
			str++;
	}
	return (count);
}
