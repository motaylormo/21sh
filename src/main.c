/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 13:02:46 by mtaylor           #+#    #+#             */
/*   Updated: 2019/06/16 13:02:48 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

/*
**	Set up working env
**	Set up termcaps
*/

static void	init_terminal(void)
{
	char			*term_ptr;
	struct termios	newtio;

	if (!(term_ptr = getenv("TERM")))
	{
		handle_error(error_env_var, "TERM");
		exit(0);
	}
	tcgetattr(TERM_FD, &newtio);
	newtio.c_lflag &= ~(ICANON | ECHO | ECHONL | IXON);
	newtio.c_cc[VMIN] = 26;//so C-y can be paste
	newtio.c_cc[VMIN] = 1;
	newtio.c_cc[VTIME] = 0;
	tcsetattr(TERM_FD, 0, &newtio);
	tgetent(NULL, term_ptr);

/*	ft_printf("VEOF: %d\n", newtio.c_cc[VEOF]);
	ft_printf("VEOL: %d\n", newtio.c_cc[VEOL]);
	ft_printf("VEOL2: %d\n", newtio.c_cc[VEOL2]);
	ft_printf("VERASE: %d\n", newtio.c_cc[VERASE]);
	ft_printf("VWERASE: %d\n", newtio.c_cc[VWERASE]);
	ft_printf("VREPRINT: %d\n", newtio.c_cc[VREPRINT]);
	ft_printf("VQUIT: %d\n", newtio.c_cc[VQUIT]);
	ft_printf("VSUSP: %d\n", newtio.c_cc[VSUSP]);
	ft_printf("VDSUSP: %d\n", newtio.c_cc[VDSUSP]);
	ft_printf("VSTART: %d\n", newtio.c_cc[VSTART]);
	ft_printf("VSTOP: %d\n", newtio.c_cc[VSTOP]);
	ft_printf("VLNEXT: %d\n", newtio.c_cc[VLNEXT]);
	ft_printf("VDISCARD: %d\n", newtio.c_cc[VDISCARD]);
	ft_printf("VDISCARD: %d\n", newtio.c_cc[VDISCARD]);
	ft_printf("VTIME: %d\n", newtio.c_cc[VTIME]);
	ft_printf("VSTATUS: %d\n", newtio.c_cc[VSTATUS]);*/
}

int			main(int argc, char **argv, char **envp, char **aplv)
{
	orig_tio_singleton();
	init_terminal();
	init_shenv(argc, argv, envp, aplv);

	while (1)
	{
		signal_catcher();
		run_shell();
	}
//	tcsetattr(TERM_FD, 0, orig_tio_singleton());
}