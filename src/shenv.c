/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 14:43:34 by mtaylor           #+#    #+#             */
/*   Updated: 2019/06/16 14:43:35 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void	enqueue(t_queue *q, t_node *n)
{
	if (!n)
		return ;
	n->next = NULL;
	if (q->first == NULL)
	{
		q->first = n;
		q->last = n;
	}
	else
	{
		q->last->next = n;
		q->last = q->last->next;
	}
}

int		enqueue_env(t_queue *q, char *str)
{
	t_node	*n;
	int		eq_index;

	if ((eq_index = ft_strchri(str, '=')) == -1)
		return (0);
	n = ft_memalloc(sizeof(t_node));
	ft_strncpy(n->label, str, eq_index);
	ft_strcpy(n->data, str + eq_index + 1);
	enqueue(q, n);
	return (1);
}

static t_queue	*envp_to_queue(char **envp)
{
	t_queue	*q;
	char	*tmp;
	int		i;

	q = ft_memalloc(sizeof(t_queue));
	i = -1;
	while (envp[++i])
	{
		enqueue_env(q, envp[i]);
		if (q->last && ft_strequ(q->last->label, "SHLVL"))
		{
			tmp = ft_itoa(ft_atoi(q->last->data) + 1);
			ft_strcpy(q->last->data, tmp);
			ft_strdel(&tmp);
		}
	}
	return (q);
}

void		init_shenv(int argc, char **argv, char **envp, char **aplv)
{
	t_shenv	*shenv;
	t_args	*main_args;

	main_args = ft_memalloc(sizeof(t_args));
	main_args->argc = argc;
	main_args->argv = argv;
	main_args->envp = envp;
	main_args->aplv = aplv;

	shenv = ft_memalloc(sizeof(t_shenv));
	shenv->main_args = main_args;
	shenv->envlist = envp_to_queue(envp);

	shenv_singleton(shenv);
}

char		*find_env(char *label)
{
	t_shenv	*e;
	t_node	*n;

	if (!(e = shenv_singleton(NULL)) || !e->envlist)
		return (NULL);
	n = e->envlist->first;
	while (n)
	{
		if (ft_strequ(n->label, label))
			return (n->data);
		n = n->next;
	}
	return (NULL);
}
