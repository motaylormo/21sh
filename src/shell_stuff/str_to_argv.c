/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 12:58:07 by mtaylor           #+#    #+#             */
/*   Updated: 2019/06/16 12:58:08 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

/*
**	Like ft_strsplit()
**		but the delimiter is defined by a function
**		and handling "quoted args" 'of either kind'
*/

static int	count_args(char *str, int (*f)(int))
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str && (*f)(*str))
			str++;
		if (*str && QUOTIES(*str) && ft_strchr(str + 1, *str))
		{
			str = ft_strchr(str + 1, *str);
			if (str++)
				count++;
		}
		else if (*str && !(*f)(*str))
		{
			while (*str && !(*f)(*str))
				str++;
			count++;
		}
	}
	return (count);
}

static char	**get_args(char *str, char **argv, int argc, int (*f)(int))
{
	int	len;
	int	i;

	i = 0;
	while ((i < argc) && *str)
	{
		while (*str && (*f)(*str))
			str++;
		len = 0;
		if (*str && QUOTIES(*str) && ft_strchr(str + 1, *str))
		{
			if ((len = ft_strchri(str + 1, *str)) > 0)
				argv[i++] = ft_strsub(str, 1, len);
			str += len + 2;
		}
		else if (*str && !(*f)(*str))
		{
			while (str[len] && !(*f)(str[len]))
				len++;
			argv[i++] = ft_strsub(str, 0, len);
			str += len;
		}
	}
	return (argv);
}

char		**str_to_argv(char *str, int (*f)(int))
{
	int		argc;
	char	**argv;

	if (str == NULL)
		return (NULL);
	if ((argc = count_args(str, f)) < 1)
		return (NULL);
	if (!(argv = ft_memalloc(sizeof(char*) * (argc + 1))))
		return (NULL);
	argv = get_args(str, argv, argc, f);
	return (argv);
}

int		issemicolon(int c)
{
	return (c == ';');
}
