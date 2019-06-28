/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fq_queue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 19:07:21 by callen            #+#    #+#             */
/*   Updated: 2019/06/27 17:10:40 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_queue.h"

t_queue	*ft_queue_init(void)
{
	t_queue	*new;

	new = malloc(sizeof(*new));
	if (new == NULL)
		return (NULL);
	new->first = NULL;
	new->last = NULL;
	return (new);
}

void	ft_enqueue(t_queue *queue, void *content)
{
	t_qnode	*ptr;
	t_qnode	*new;

	if (!(queue && content))
		return ;
	if (!(new = (t_qnode*)malloc(sizeof(t_qnode))))
		return ;
	new->content = content;
	new->next = NULL;
	ptr = queue->first;
	if (!ptr)
	{
		queue->first = new;
		queue->last = new;
		return ;
	}
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
	queue->last = new;
}

void	*ft_dequeue(t_queue *queue)
{
	t_qnode	*a;
	t_qnode	*b;
	void	*content;

	if (!queue)
		return (NULL);
	if (!queue->first)
		return (NULL);
	a = queue->first;
	b = a->next;
	queue->first = b;
	if (!queue->first)
		queue->last = NULL;
	content = a->content;
	free(a);
	return (content);
}

int		ft_queue_is_empty(t_queue *queue)
{
	if (!queue)
		return (1);
	return (queue->first == NULL);
}

void	*ft_queue_peek(t_queue *queue)
{
	if (!queue)
		return (NULL);
	if (!queue->first)
		return (NULL);
	return (queue->first->content);
}
