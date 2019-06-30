/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 14:18:43 by mtaylor           #+#    #+#             */
/*   Updated: 2019/06/16 14:18:44 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static const t_command	g_builtins[] = {
	{ "cd", &builtin_cd },
	{ "echo", &builtin_echo },
	{ "env", &builtin_env },
	{ "exit", &builtin_exit },
	{ "setenv", &builtin_setenv },
	{ "unsetenv", &builtin_unsetenv },
	{ (NULL), (NULL) },
};

static int	path(char **argv)
{
	int		i;
	char	**path_arr;
	char	exec_path[PATH_MAX + 1];

	if ((path_arr = ft_strsplit(find_env("PATH"), ':')))
	{
		i = -1;
		while (path_arr[++i])
		{
			ft_cpycat_path(exec_path, path_arr[i], argv[0]);
			if (access(exec_path, F_OK) == 0)
			{
				run_executable(exec_path, argv);
				strvec_flush(path_arr);
				return (1);
			}
		}
		strvec_flush(path_arr);
	}
	return (0);
}

static void	exec_command(char **argv)
{
	int i;

	i = -1;
	while (g_builtins[++i].str)
	{
		if (ft_strequ(argv[0], g_builtins[i].str))
			return (g_builtins[i].f(argv));
	}
	if (path(argv))
		return ;
	if (access(argv[0], F_OK) == 0)
		return (run_executable(argv[0], argv));
	handle_error(error_command, argv[0]);
}

void		run_shell(void)
{
	char	*line_ptr;
	char	**argv;
	char	cls;

	print_prompt();
	line_ptr = shenv_singleton(NULL)->cl;
	get_command_line(STDIN_FILENO, line_ptr);
	/* ft_dprintf(2, "|DBG: run_shell line(%s)|\n", line_ptr); */
	cls = count_cls(line_ptr);
	while (cls--)
	{
		if ((argv = str_to_argv(line_ptr)))
		{
			exec_command(argv);
			strvec_flush(argv);
		}
		line_ptr = ft_strchr(line_ptr, '\0') + 1;
		while (*line_ptr == '\0')
			line_ptr++;
	}
}
