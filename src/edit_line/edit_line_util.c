/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 20:54:59 by mtaylor           #+#    #+#             */
/*   Updated: 2019/06/27 20:55:01 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "cl_edit.h"

#define PART1(c) (c == '\f' || c == '\t' || c == ' ')
#define PART2(c) (c == '\n' || c == '\v' || c == '\r')
#define WHITESPACE(c) (PART1(c) || PART2(c))

/*
**	"im"	begin insert mode
**	"ei"	end insert mode
*/
void	insert_text(char *buf, int len, char *line, int *cursor)
{
//Visual
	ft_putstr(tgetstr("im", NULL));
	ft_putstr(buf);
	ft_putstr(tgetstr("ei", NULL));

/*	for (int i = 0; i < BUFF_SIZE; ++i)
	{
		ft_printf("[%d]", buf[i]);
	}
	ft_printf("\n");*/

//Memory
	if (line[*cursor] == '\0')
		ft_strcat(line, buf);
	else
	{
		ft_memmove(line + *cursor + len, line + *cursor, ft_strlen(line + *cursor));
		ft_memcpy(line + *cursor, buf, len);
	}
	(*cursor) += len;
}

int		get_prev_word(int cursor, char *line)
{
	int word;

	word = cursor;
	while (word - 1 >= 0 && WHITESPACE(line[word - 1]))
		word--;
	while (word - 1 >= 0 && !WHITESPACE(line[word - 1]))
		word--;
	return (word);
}

int		get_next_word(int cursor, char *line)
{
	int word;

	word = cursor;
	while (line[word] && WHITESPACE(line[word]))
		word++;
	while (line[word] && !WHITESPACE(line[word]))
		word++;
	return (word);
}