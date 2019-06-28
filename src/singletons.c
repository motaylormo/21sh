/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 13:13:30 by mtaylor           #+#    #+#             */
/*   Updated: 2019/06/21 13:13:31 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_shenv		*shenv_singleton(t_shenv *arg)
{
	static t_shenv	*singleton = NULL;

	if (arg)
		singleton = arg;
	return (singleton);
}

t_cl_list	*history_singleton(void)
{
	static t_cl_list	*singleton = NULL;

	if (singleton == NULL)
		singleton = ft_memalloc(sizeof(t_cl_list));
	return (singleton);
}

struct termios	*orig_tio_singleton(void)
{
	static struct termios	singleton;
	static int				flag = 0;

	if (flag == 0)
	{
		tcgetattr(TERM_FD, &singleton);
		flag = 1;
	}
	return (&singleton);
}

int		window_width(void)
{
	struct winsize	argp;

	ioctl(TERM_FD, TIOCGWINSZ, &argp);
	return (argp.ws_col);
}