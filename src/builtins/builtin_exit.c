/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:06:40 by mtaylor           #+#    #+#             */
/*   Updated: 2019/06/17 11:06:41 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	builtin_exit(char **argv)
{
	ft_putstr("exit\n");
	strvec_flush(argv);
	tcsetattr(STDIN_FILENO, 0, orig_tio_singleton());
	exit(0);
}
