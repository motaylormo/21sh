/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:36:23 by mtaylor           #+#    #+#             */
/*   Updated: 2019/06/17 11:36:24 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		ft_bzero(shenv_singleton(NULL)->cl, LINE_MAX);
		print_prompt();
	}
}

void		signal_catcher(void)
{
	signal(SIGINT, sigint_handler);
}
