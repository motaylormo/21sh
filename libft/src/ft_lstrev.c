/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 16:29:58 by callen            #+#    #+#             */
/*   Updated: 2019/05/15 19:42:56 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_lstrev(t_list **alst)
{
	t_list *head;
	t_list *curr;
	t_list *next;

	curr = NULL;
	head = *alst;
	while (head)
	{
		next = (*head).next;
		(*head).next = curr;
		curr = head;
		head = next;
	}
	*alst = curr;
}
