/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:05:58 by mtaylor           #+#    #+#             */
/*   Updated: 2019/06/17 11:05:59 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	builtin_echo(char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		ft_printf("%s", argv[i]);
		if (argv[i + 1])
			ft_printf("%c", ' ');
	}
	ft_printf("\n");
}