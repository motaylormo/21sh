/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:06:07 by mtaylor           #+#    #+#             */
/*   Updated: 2019/06/17 11:06:08 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

/*
**	cd -	oldpwd
**	cd		home
*/

static int	get_cd_path(char *arg, char *path)
{
	char	*env_var;
	char	*data_ptr;

	env_var = NULL;
	if (!arg)
		env_var = "HOME";
	else if (ft_strequ(arg, "-"))
		env_var = "OLDPWD";
	if (env_var)
	{
		if ((data_ptr = find_env(env_var)))
			ft_strcpy(path, data_ptr);
		else
		{
			handle_error(error_env_var, env_var);
			return (0);
		}
	}
	else
		ft_strcpy(path, arg);
	return (1);
}

void	builtin_cd(char **argv)
{
	t_shenv	*e;
	char	*pwd;
	char	*oldpwd;
	char	path[PATH_MAX + 1];

	if (!(pwd = find_env("PWD")))
	{
		e = shenv_singleton(NULL);
		enqueue_env(e->envlist, "PWD=");
		pwd = find_env("PWD");
		getcwd(pwd, PATH_MAX);
	}
	if (!(get_cd_path(argv[1], path)))
		return ;
	if (chdir(path) == -1)
		return (handle_error(error_file, path));
	if ((oldpwd = find_env("OLDPWD")))
		ft_strcpy(oldpwd, pwd);
	getcwd(pwd, PATH_MAX);
}