/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:36:17 by mtaylor           #+#    #+#             */
/*   Updated: 2019/06/17 11:36:18 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static const char	*g_error_message[] = {
	[error_command] = "command not found",
	[error_env_var] = "environment variable missing",
	[error_no_arg] = "not enough arguments",
	[error_forking] = "forking error"
};

static void	print_error_message(const char *error, char *arg)
{
	ft_dprintf(STDERR_FILENO, NAME);
	if (error)
		ft_dprintf(STDERR_FILENO, ": %s", error);
	if (arg)
		ft_dprintf(STDERR_FILENO, ": %s", arg);
	ft_dprintf(STDERR_FILENO, "\n");
}

void		handle_error(int errorcode, char *arg)
{
	if (errorcode == error_file)
	{
		if (access(arg, F_OK) != 0)
			print_error_message("no such file or directory", arg);
		else if (access(arg, X_OK) != 0)
			print_error_message("permission denied", arg);
	}
	else
		print_error_message(g_error_message[errorcode], arg);
}