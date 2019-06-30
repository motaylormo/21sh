/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_paste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 20:48:29 by mtaylor           #+#    #+#             */
/*   Updated: 2019/06/27 20:48:30 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static int	seg_to_copybuf(char *buf, char *str, int start, int end)
{
	ft_memcpy(buf, str + start, end - start);
	buf[end - start] = '\0';
	return (end - start);
}

void		copypaste(int key, char *line, int *cursor)
{
	static char	buf[LINE_MAX + 1];
	static int	flag = 0;
	int			i;

	if (key == key_cut_to_end || key == key_cut_word)
		flag = 1;
	if (key == key_cut_to_end)
	{
		i = seg_to_copybuf(buf, line, *cursor, ft_strlen(line));
		while (i--)
			edit_key(key_delete, line, cursor);
	}
	if (key == key_cut_word)
	{
		i = seg_to_copybuf(buf, line, get_prev_word(*cursor, line), *cursor);
		while (i--)
			edit_key(key_backspace, line, cursor);
	}
	if (key == key_paste && flag == 1)
		insert_text(buf, ft_strlen(buf), line, cursor);
//	ft_printf("\ncopybuffer[%s]\n", buf);
}