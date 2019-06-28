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

#define QUOTIES(c)	((c == '"') || (c == '\''))
/*
**	Like ft_strsplit()
**		but any whitespace, not just spaces
**		and handling "quoted args" 'of either kind'
*/

static int	count_args(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str && ft_isspace(*str))
			str++;
		if (*str && QUOTIES(*str) && ft_strchr(str + 1, *str))
		{
			str = ft_strchr(str + 1, *str);
			if (str++)
				count++;
		}
		else if (*str && !ft_isspace(*str))
		{
			while (*str && !ft_isspace(*str))
				str++;
			count++;
		}
	}
	return (count);
}

static char	**get_args(char *str, char **argv, int argc)
{
	int	len;
	int	i;

	i = 0;
	while ((i < argc) && *str)
	{
		while (*str && ft_isspace(*str))
			str++;
		len = 0;
		if (*str && QUOTIES(*str) && ft_strchr(str + 1, *str))
		{
			if ((len = ft_strchri(str + 1, *str)) > 0)
				argv[i++] = ft_strsub(str, 1, len);
			str += len + 2;
		}
		else if (*str && !ft_isspace(*str))
		{
			while (str[len] && !ft_isspace(str[len]))
				len++;
			argv[i++] = ft_strsub(str, 0, len);
			str += len;
		}
	}
	return (argv);
}

char		**str_to_argv(char *str)
{
	int		argc;
	char	**argv;

	if (str == NULL)
		return (NULL);
	if ((argc = count_args(str)) < 1)
		return (NULL);
	if (!(argv = ft_memalloc(sizeof(char*) * (argc + 1))))
		return (NULL);
	argv = get_args(str, argv, argc);
	return (argv);
}
