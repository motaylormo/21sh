/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 17:17:38 by mtaylor           #+#    #+#             */
/*   Updated: 2019/06/16 17:17:39 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static void	pwd_prompt(void)
{
	char	pwd[PATH_MAX + 1];
	char	*home_ptr;
	int		color;
	int		start = 0;

	getcwd(pwd, PATH_MAX);
	if ((home_ptr = find_env("HOME")) &&
		ft_strnequ(home_ptr, pwd, ft_strlen(home_ptr)))
	{
		start = ft_strlen(home_ptr);
		ft_printf(COLOR_TRIM "~");
	}
	color = 0;
	for (int i = start; pwd[i]; ++i)
	{
		if (pwd[i] == '/')
		{
			ft_printf(COLOR_TRIM "/");
			color = (color == 1) ? 0 : 1;
			ft_printf((color == 1) ? COLOR2 : COLOR1);
		}
		else
			ft_printf("%c", pwd[i]);
	}
}

void		print_prompt(void)
{
	char	*prompt_str;

	if ((prompt_str = find_env("PS1")))
		ft_putstr(prompt_str);
	else if ((prompt_str = find_env("PS2")))
		ft_putstr(prompt_str);
	else if ((prompt_str = find_env("PS3")))
		ft_putstr(prompt_str);
	else if ((prompt_str = find_env("PS4")))
		ft_putstr(prompt_str);
	else
		pwd_prompt();//ft_printf(PROMPT);
	ft_putstr(COLOR_OFF " ");
}
