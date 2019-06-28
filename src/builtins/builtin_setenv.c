/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:06:15 by mtaylor           #+#    #+#             */
/*   Updated: 2019/06/17 11:06:16 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	builtin_setenv(char **argv)
{
	t_queue	*q;
	char	*label[2];

	if (!argv[1])
		return (handle_error(error_no_arg, NULL));
	q = shenv_singleton(NULL)->envlist;
	if (enqueue_env(q, argv[1]))
	{
		if (find_env(q->last->label) != q->last->data)
		{
			label[1] = q->last->label;
			builtin_unsetenv(label);
		}
	}
}