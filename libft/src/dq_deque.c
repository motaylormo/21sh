/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dq_deque.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 16:59:33 by callen            #+#    #+#             */
/*   Updated: 2019/06/27 17:05:19 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_queue.h"

t_deque	*dq_deque_init(void)
{
	t_deque *new;

	new = malloc(sizeof(*new));
	if (new == 0)
		return (0);
	new->first = 0;
	new->last = 0;
	return (new);
}

void	dq_push_front(t_deque *deque, void *value)
{
	t_deque_node *new;

	if (deque == 0)
		return ;
	new = malloc(sizeof(*new));
	if (new == 0)
		return ;
	new->prev = 0;
	new->next = 0;
	new->value = value;
	if (deque->first != 0)
		deque->first->prev = new;
	else
		deque->last = new;
	new->next = deque->first;
	deque->first = new;
}

void	dq_push_back(t_deque *deque, void *value)
{
	t_deque_node	*new;

	if (deque == 0)
		return ;
	new = malloc(sizeof(*new));
	if (new == 0)
		return ;
	new->prev = 0;
	new->next = 0;
	new->value = value;
	if (deque->last != 0)
		deque->last->next = new;
	else
		deque->first = new;
	new->prev = deque->last;
	deque->last = new;
}

void	*dq_pop_front(t_deque *deque)
{
	t_deque_node	*tmp;
	void			*ret;

	if (deque == 0 || deque->first == 0)
		return (0);
	if (deque->first == deque->last)
		deque->last = 0;
	tmp = deque->first;
	ret = tmp->value;
	deque->first = tmp->next;
	if (deque->first)
		deque->first->prev = 0;
	free(tmp);
	return (ret);
}

void	*dq_pop_back(t_deque *deque)
{
	t_deque_node	*tmp;
	void			*ret;

	if (deque == 0 || deque->last == 0)
		return (0);
	if (deque->first == deque->last)
		deque->first = 0;
	tmp = deque->last;
	ret = tmp->value;
	deque->last = tmp->prev;
	if (deque->last)
		deque->last->next = 0;
	free(tmp);
	return (ret);
}
