/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:06:29 by mtaylor           #+#    #+#             */
/*   Updated: 2019/06/17 11:06:30 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	builtin_env(char **argv)
{
	t_node	*n;

	(void)argv;
	n = shenv_singleton(NULL)->envlist->first;
	while (n)
	{
		ft_dprintf(g_output_fd, "%s=%s\n", n->label, n->data);
		n = n->next;
	}
}