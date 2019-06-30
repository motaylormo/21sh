/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:50:46 by mtaylor           #+#    #+#             */
/*   Updated: 2019/06/17 11:50:47 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

/*
**	Make an envp to pass to a program that's the same as the working env
*/
static char	**queue_to_strvector(void)
{
	char	**envp;
	char	temp[PATH_MAX + 1];
	t_node	*n;
	int		i;

	i = 0;
	n = shenv_singleton(NULL)->envlist->first;
	while (n)
	{
		i++;
		n = n->next;
	}
	envp = ft_memalloc(sizeof(char*) * (i + 1));
	i = 0;
	n = shenv_singleton(NULL)->envlist->first;
	while (n)
	{
		ft_strcpy(temp, n->label);
		ft_strcat(temp, "=");
		ft_strcat(temp, n->data);
		envp[i++] = ft_strdup(temp);
		n = n->next;
	}
	return (envp);
}

/*
**	Catch signals for the parent process and nullify them.
**	Let the signals do their thing in the child process.
*/

static void	sig_handler(int sig)
{
	(void)sig;
	ft_printf("\n");
	signal(SIGINT, sig_handler);
}

void		run_executable(char *path, char **argv)
{
	pid_t	process_id;
	char	**envp;

	if (access(path, X_OK) != 0)
		handle_error(error_file, path);
	else
	{
		envp = queue_to_strvector();
		process_id = fork();
		if (process_id < 0)
			handle_error(error_forking, NULL);
		else if (process_id == 0)
		{
			execve(path, argv, envp);
			exit(0);
		}
		else if (process_id > 0)
		{
			signal(SIGINT, sig_handler);
			wait(&process_id);
		}
		ft_matrixdel(&envp);
	}
}