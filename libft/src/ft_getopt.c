/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:09:01 by callen            #+#    #+#             */
/*   Updated: 2019/01/23 12:23:54 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define BADCH	((int)'?')
#define BADARG	((int)':')
#define EMSG	("")
#define EOPT	("%s: illegal option -- %c\n")
#define EARG	("%s: option requites an argument -- %c\n")

static int	getopt_sub(int ac, char **av, char *ostr, char **place)
{
	if (optreset || **place == 0)
	{
		optreset = 0;
		*place = av[optind];
		if (optind >= ac || *(*place)++ != '-')
			return ((*(*place = EMSG) == 0) * -1);
		optopt = *(*place)++;
		if (optopt == '-' && **place == 0)
		{
			++optind;
			*place = EMSG;
			return (-1);
		}
		if (optopt == 0)
		{
			*place = EMSG;
			if (ft_strchr(ostr, '-') == NULL)
				return (-1);
			optopt = '-';
		}
	}
	else
		optopt = *(*place)++;
	return (0);
}

static int	getopt_else(int ac, char **av, char **ostr, char **place)
{
	if (**place)
		optarg = *place;
	else if (ac > ++optind)
		optarg = av[optind];
	else
	{
		++optind;
		optarg = NULL;
		*place = EMSG;
		if (**ostr == ':')
			return (BADARG);
		if (opterr)
			(void)ft_dprintf(2, EARG, *av, optopt);
		return (BADCH);
	}
	*place = EMSG;
	++optind;
	return (0);
}

int			ft_getopt(int nargc, char **nargv, char *ostr)
{
	static char	*place = EMSG;
	char		*oli;
	int			tmp;

	if ((tmp = getopt_sub(nargc, nargv, ostr, &place)))
		return (tmp);
	if (optopt == ':' || (oli = ft_strchr(ostr, optopt)) == NULL)
	{
		if (*place == 0)
			++optind;
		if (opterr && *ostr != ':')
			(void)ft_dprintf(2, EOPT, *nargv, optopt);
		return (BADCH);
	}
	if (oli[1] != ':')
	{
		optarg = NULL;
		if (*place == 0)
			++optind;
	}
	else if ((tmp = getopt_else(nargc, nargv, &ostr, &place)))
		return (tmp);
	return (optopt);
}
