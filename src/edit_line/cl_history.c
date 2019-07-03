/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 15:41:54 by mtaylor           #+#    #+#             */
/*   Updated: 2019/06/20 15:41:56 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "cl_edit.h"

static void	clear_line(char *line, int *cursor)
{
	while (*cursor > 0)
		edit_key(key_backspace, line, cursor);
	while (line[0] != '\0')
		edit_key(key_delete, line, cursor);
}

void		get_command_history(int key, char *line, t_cl_node **curr, int *cursor)
{
	t_cl_list	*history;

	clear_line(line, cursor);
	history = history_singleton();
	if (key == key_up)
	{
		if (*curr == NULL)
			*curr = history->top;
		else if ((*curr)->next != NULL)
			*curr = (*curr)->next;
	}
	if (key == key_down)
	{
		if (*curr)
			*curr = (*curr)->prev;
	}
	if (*curr)
		insert_text((*curr)->cl, ft_strlen((*curr)->cl), line, cursor);

}

void		add_cl_to_history(char *line)
{
	t_cl_list	*history;
	t_cl_node	*node;

	node = ft_memalloc(sizeof(t_cl_node));
	ft_strcpy(node->cl, line);
	history = history_singleton();
	if (history->top)
	{
		node->next = history->top;
		history->top->prev = node;
	}
	history->top = node;
}