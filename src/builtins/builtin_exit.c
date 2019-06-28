/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:06:40 by mtaylor           #+#    #+#             */
/*   Updated: 2019/06/28 01:04:36 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

extern void	ft_matrixdel(char ***arrayp);

void	builtin_exit(char **argv)
{
	ft_matrixdel(&argv);
	tcsetattr(TERM_FD, 0, orig_tio_singleton());
	exit(0);
}
