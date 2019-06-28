/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 17:26:18 by mtaylor           #+#    #+#             */
/*   Updated: 2019/06/19 17:26:19 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static const t_key	g_history_keys[] = {
	(t_key){"\e[A", key_up},
	(t_key){"\e[B", key_down},
	(t_key){(NULL), 0}
};

static const t_key	g_edit_keys[] = {
	(t_key){"\e[C", key_right},
	(t_key){"\e[D", key_left},
	(t_key){"\x7f", key_backspace},
	(t_key){"\e[3~", key_delete},	(t_key){"\x04", key_delete},//ctrl-d
	(t_key){"\e[H", key_home},	(t_key){"\x01", key_home},//ctrl-a
	(t_key){"\e[F", key_end},	(t_key){"\x05", key_end},//ctrl-e
	(t_key){"\e[1;5D", key_word_left},//ctrl-left
	(t_key){"\eb", key_word_left},//option-b (b = backwards)
	(t_key){"\e[1;5C", key_word_right},//ctrl-right
	(t_key){"\ef", key_word_right},//option-f (f = forwards)
	(t_key){(NULL), 0}
};

static const t_key	g_copypaste_keys[] = {
	(t_key){"\x0b", key_ctrl_k},
	(t_key){"\x17", key_ctrl_w},
	(t_key){"\x19", key_ctrl_y},
	(t_key){(NULL), 0}
};

static int	get_key(t_buf key, const t_key arr[])
{
	for (int i = 0; arr[i].seq; ++i)
	{
		if (ft_strequ(key.buf, arr[i].seq))
			return (arr[i].enumcode);
	}
	return (0);
}

int		get_prev_word(int cursor, char *line)
{
	int word;

	word = cursor;
	while (word - 1 >= 0 && ft_iswhitespace(line[word - 1]))
		word--;
	while (word - 1 >= 0 && !ft_iswhitespace(line[word - 1]))
		word--;
	return (word);
}

int		get_next_word(int cursor, char *line)
{
	int word;

	word = cursor;
	while (line[word] && ft_iswhitespace(line[word]))
		word++;
	while (line[word] && !ft_iswhitespace(line[word]))
		word++;
	return (word);
}

void	get_command_line(int fd, char *line)
{
	t_cl_node	*curr;
	t_buf		key;
	int			cursor;
	int			enumkey;
	
	curr = NULL;
	cursor = 0;
	ft_bzero(line, LINE_MAX + 1);
	while (1)
	{
		ft_bzero(&key, sizeof(t_buf));
		key.ret = read(fd, key.buf, BUFF_SIZE);
		if (ft_strequ(key.buf, "\n"))
			break ;
		else if ((enumkey = get_key(key, g_history_keys)))
			get_command_history(enumkey, line, &curr, &cursor);
		else if ((enumkey = get_key(key, g_edit_keys)))
			edit_key(enumkey, line, &cursor);
		else if ((enumkey = get_key(key, g_copypaste_keys)))
			copypaste(enumkey, line, &cursor);
		else
			insert_text(key.buf, key.ret, line, &cursor);
	}
	ft_putchar('\n');
	add_cl_to_history(line);
}
