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
	{"\e[A", key_up},
	{"\e[B", key_down},
	{(NULL), 0}
};

static const t_key	g_edit_keys[] = {
	{"\e[C", key_right},
	{"\x06", key_right},
	{"\e[D", key_left},
	{"\x02", key_left},
	{"\x7f", key_backspace},
	{"\e[3~", key_delete},//	delete
	{"\x04", key_delete},//		ctrl-d (d = delete)
	{"\e[H", key_home},//	home
	{"\x01", key_home},//	ctrl-a (a = ???)
	{"\e[F", key_end},//	end
	{"\x05", key_end},//	ctrl-e (e = end)
	{"\e[1;5D", key_word_left},//	ctrl-left
	{"\eb", key_word_left},//		option-b (b = backwards)
	{"\e[1;5C", key_word_right},//	ctrl-right
	{"\ef", key_word_right},//		option-f (f = forwards)
	{(NULL), 0}
};

static const t_key	g_copypaste_keys[] = {
	{"\x0b", key_cut_to_end},//	ctrl-k (k = kill aka cut)
	{"\x17", key_cut_word},//	ctrl-w (w = word)
	{"\x19", key_paste},//		ctrl-y (y = ???)
	{(NULL), 0}
};

static int	get_key(char *buf, const t_key arr[])
{
	int i;

	i = -1;
	while (arr[++i].seq)
	{
		if (ft_strequ(buf, arr[i].seq))
			return (arr[i].enumcode);
	}
	return (0);
}

int		get_prev_word(int cursor, char *line)
{
	int word;

	word = cursor;
	while (word - 1 >= 0 && ft_isspace(line[word - 1]))
		word--;
	while (word - 1 >= 0 && !ft_isspace(line[word - 1]))
		word--;
	return (word);
}

int		get_next_word(int cursor, char *line)
{
	int word;

	word = cursor;
	while (line[word] && ft_isspace(line[word]))
		word++;
	while (line[word] && !ft_isspace(line[word]))
		word++;
	return (word);
}

/*
** 31 lines
*/
void	get_command_line(int fd, char *line)
{
	t_cl_node	*curr;
	char		buf[BUFF_SIZE + 1];
	int			ret;
	int			cursor;
	int			enumkey;

	curr = NULL;
	cursor = 0;
	ft_bzero(line, LINE_MAX + 1);
	while (1)
	{
		ft_bzero(buf, sizeof(buf)/sizeof(*buf));
		ret = read(fd, buf, BUFF_SIZE);
		// ft_dprintf(2, "|DBG: key.buf(%s)|\n", key.buf);
		if (ft_strequ(buf, "\n"))
			break ;
		else if (cursor == 0 && ft_strequ(buf, "\x04"))
		{
			ft_printf("exit\n");
			builtin_exit(NULL);
		}
		else if ((enumkey = get_key(buf, g_history_keys)))
			get_command_history(enumkey, line, &curr, &cursor);
		else if ((enumkey = get_key(buf, g_edit_keys)))
			edit_key(enumkey, line, &cursor);
		else if ((enumkey = get_key(buf, g_copypaste_keys)))
			copypaste(enumkey, line, &cursor);
		else
			insert_text(buf, ret, line, &cursor);
	}
}
