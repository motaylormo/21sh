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

void	copypaste(int key, char *line, int *cursor)
{
	static char	buf[LINE_MAX + 1];
	static int	flag = 0;
	int			i;

	if (key == key_ctrl_k || key == key_ctrl_w)
		flag = 1;
	//from cursor position to the end of the line
	if (key == key_ctrl_k)
	{
		i = seg_to_copybuf(buf, line, *cursor, ft_strlen(line));
		while (i--)
			edit_key(key_delete, line, cursor);
	}
	//the immediately preceeding word into the temp-buffer, including any trailing whitespace
	if (key == key_ctrl_w)
	{
		i = seg_to_copybuf(buf, line, get_prev_word(*cursor, line), *cursor);
		while (i--)
			edit_key(key_backspace, line, cursor);
	}
	if (key == key_ctrl_y && flag == 1)
		insert_text(buf, ft_strlen(buf), line, cursor);
//	ft_printf("\ncopybuffer[%s]\n", buf);
}