/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 19:59:36 by callen            #+#    #+#             */
/*   Updated: 2019/06/28 00:26:04 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_QUEUE_H
# define FT_QUEUE_H

typedef struct s_deque_node	t_deque_node;
struct	s_deque_node
{
	struct s_deque_node	*next;
	struct s_deque_node	*prev;
	void				*value;
};

typedef struct s_deque	t_deque;
struct	s_deque
{
	struct s_deque_node	*first;
	struct s_deque_node	*last;
};


t_deque	*dq_deque_init(void);
void	dq_push_front(t_deque *deque, void *value);
void	dq_push_back(t_deque *deque, void *value);
void	*dq_pop_front(t_deque *deque);
void	*dq_pop_back(t_deque *deque);

#endif
