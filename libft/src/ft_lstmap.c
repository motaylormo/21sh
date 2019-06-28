/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 21:47:21 by callen            #+#    #+#             */
/*   Updated: 2019/05/15 19:42:41 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;

	new = NULL;
	if (!lst)
		return (NULL);
	if ((new = (f(ft_lstnew(lst->content, lst->content_size)))))
		new->next = ft_lstmap(lst->next, f);
	return (new);
}
