/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 19:20:10 by mtaylor           #+#    #+#             */
/*   Updated: 2019/06/19 19:20:12 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

/*
**	"le"	cursor left one character
*/
static int	cursor_left(int *cursor)
{
	if (*cursor > 0)
	{
		ft_putstr(tgetstr("le", NULL));
		(*cursor)--;
		return (1);
	}
	return (0);
}

/*
**	"nd"	cursor right one character
*/
static int	cursor_right(int *cursor, char *line)
{
	if (line[*cursor] && *cursor + 1 <= LINE_MAX)
	{
		ft_putstr(tgetstr("nd", NULL));
		(*cursor)++;
		return (1);
	}
	return (0);
}

/*
**	"dc"	delete one character
*/
static int	delete_char(int *cursor, char *line)
{
	if (line[*cursor])
	{
		ft_putstr(tgetstr("dc", NULL));
		ft_memmove(line + *cursor, line + *cursor + 1, ft_strlen(line + *cursor));
		return (1);
	}
	return (0);
}

/*
** 'C-f' and 'C-b' seem to increase the limit of cursor
*/
void		edit_key(int key, char *line, int *cursor)
{
	// ft_dprintf(2, "|DBG: edit_key key(%d) cursor(%d)|\n", key,*cursor);
	if (key == key_left)
		cursor_left(cursor);
	if (key == key_right)
		cursor_right(cursor, line);
	if (key == key_delete)
		delete_char(cursor, line);
	if (key == key_backspace)
	{
		if (cursor_left(cursor))
			delete_char(cursor, line);
	}
	if (key == key_home)
		while (cursor_left(cursor));
	if (key == key_end)
		while (cursor_right(cursor, line));
	if (key == key_word_left)
	{
		int word = get_prev_word(*cursor, line);
		while (*cursor != word)
			cursor_left(cursor);
	}
	if (key == key_word_right)
	{
		int word = get_next_word(*cursor, line);
		while (*cursor != word)
			cursor_right(cursor, line);
	}
}
