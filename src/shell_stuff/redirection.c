/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 10:30:09 by mtaylor           #+#    #+#             */
/*   Updated: 2019/07/04 10:30:10 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <fcntl.h>

static const t_redir	g_redirects[] = {
	{">>", STDOUT_FILENO, W_OK, (O_WRONLY | O_APPEND)},//	append redirect output
	{">&", STDIN_FILENO, 0, 0},//	duplicat output file descriptor
	{">",  STDOUT_FILENO, W_OK, (O_WRONLY)},//				redirect output
	{"<<", STDIN_FILENO, R_OK, 0},//	"Here-Document" ???
	{"<&", STDIN_FILENO, 0, 0},//	duplicat input file descriptor
	{"<>", 0, 0, 0},//	open file descriptors for reading and writing
	{"<",  STDIN_FILENO, R_OK, (O_RDONLY)},//				redirect intput
	{(NULL), 0, 0, 0}
};

static int	get_file_fd(char *str, int inout, int wflag, int oflags)
{
	int		fd;
	char	*path;

	path = ft_strtrim(str);
	if (access(path, F_OK) == 0 &&
		access(path, wflag) != 0)
	{
		ft_dprintf(STDERR_FILENO, "permission denied: %s\n", path);
		return (-1);
	}
	fd = open(path, oflags | O_CREAT);
//ft_dprintf(2, "|DBG: path(%s) fd(%d)|\n", path, fd);
ft_strdel(&path);

	if (dup2(fd, inout) == -1)
	{
		ft_dprintf(2, "|DBG: first dup2 failed|\n");
		return (-1);
	}

	return (fd);
}

void		redirection(char *str)
{
	while (*str)
	{
		for (int i = 0; g_redirects[i].str; ++i)
		{
			int len = ft_strlen(g_redirects[i].str);
			if (ft_strnequ(str, g_redirects[i].str, len))
			{

ft_dprintf(2, "|DBG: redir(%.*s) path(%s)|\n", len, str, str + len);

				get_file_fd(str + len, g_redirects[i].inout,
										g_redirects[i].wflag,
										g_redirects[i].oflag);
				str[0] = '\0';
				str += len;
			}
		}
		if (*str && QUOTIES(*str) && ft_strchr(str + 1, *str))
			str = ft_strchr(str + 1, *str) + 1;
		else
			str++;
	}
}
