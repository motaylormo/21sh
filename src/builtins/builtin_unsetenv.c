/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:06:22 by mtaylor           #+#    #+#             */
/*   Updated: 2019/06/17 11:06:23 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	builtin_unsetenv(char **argv)
{
	t_queue	*q;
	t_node	*n;
	t_node	*prev;

	if (!argv[1])
		return (handle_error(error_no_arg, NULL));
	q = shenv_singleton(NULL)->envlist;
	n = q->first;
	prev = NULL;
	while (n)
	{
		if (ft_strequ(n->label, argv[1]))
		{
			if (prev)
				prev->next = n->next;
			if (n == q->first)
				q->first = n->next;
			if (n == q->last)
				q->last = prev;
			free(n);
			return ;
		}
		prev = n;
		n = n->next;
	}
	handle_error(error_env_var, argv[1]);
}