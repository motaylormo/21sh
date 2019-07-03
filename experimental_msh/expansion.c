/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 01:20:03 by callen            #+#    #+#             */
/*   Updated: 2019/06/03 00:28:29 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "ft_stdio.h"
#include <pwd.h>
#include <sys/types.h>

int			g_exp_dollar = 0;
int			g_expand_var = 0;
char		*g_home = 0;

#define PL (ln[0])
#define RL (ln[1])
#define NL (ln[2])
#define TL (ln[3])
#define SL (ln[4])
#define EL (ln[5])

/*
** PL = pattern string length
** RL = replacement string length
** NL = new string length
** TL = total string length
** SL = remaining string lenth
** EL = after replacement string length
*/
char		*strsub_rep(char *str, char *pat, char *rep)
{
	char	*r;
	int		ln[6];

	PL = ft_strlen(pat);
	RL = ft_strlen(rep);
	TL = ft_strlen(str);
	r = ft_strstr(str, pat);
	SL = ft_strlen(r);
	if (ft_strnequ(r, pat, PL))
	{
		NL = ft_strlen(str) - PL + RL;
		r = ft_strnew(NL);
		ft_strncpy(r, str, TL - SL);
		ft_strncpy(r + (TL - SL), rep, RL);
		EL = ft_strlen(str + TL - SL + PL);
		ft_strncpy(r + TL - SL + RL, str + TL - SL + PL, EL);
	}
	return (r);
}

#undef PL
#undef RL
#undef NL
#undef TL
#undef SL
#undef EL

/*
** Variable Dereference Substitution
**
** $* - flurgh
** $@ - agh
** $# - number of positional parameters
** $? - exit status of most recently executed foreground pipeline
** $- - current option flags as specified by invocation
** $$ - process ID of the shell
** $! - process ID of job most recently placed into the background
** $0 - name of the shell or shell script
** $_ - last word of the previous line of input
*/

char		*msh_dollar(char *ret, char *tmp)
{
	char			*val;
	char			*var;
	char			*r;
	int				varlen;

	if (!tmp || !*tmp || (r = NULL))
		return (ret);
	varlen = msh_varlen(tmp);
	var = ft_strndup(tmp, varlen + (!varlen ? 2 : 1));
	val = get_string_value(var + (!varlen ? 0 : 1));//find_env()
	if (val)
	{
		r = strsub_rep(ret, var, val);
		free(val);
	}
	else
		r = ft_strdup(ret);
	free(var);
	g_exp_dollar = 1;
	return (r);
}

char		*msh_tilde(char *ret, char *tmp)
{
	char			*r[2];
	static char		*home;
	struct passwd	*entry;

	if (ft_strnequ(tmp, "~~", 2))
		return (ft_strdup(ret));
	r[0] = get_string_value("HOME"); //find_env("HOME")
	if (r[0] == 0)
	{
		if (!home)
		{
			entry = getpwuid(getuid());
			if (entry)
				home = ft_strdup(entry->pw_dir);
		}
		r[0] = ft_strdup(home);
	}
	r[1] = strsub_rep(ret, "~", r[0]);
	free(r[0]);
	return (r[1]);
}

/*
**subst.c subst.h
*/

char		*msh_expand(char *token)
{
	char	*tmp;
	char	*ret;
	char	*rett;

	ret = ft_strdup(token);
	rett = ret;
	free(token);
	if ((tmp = ft_strchr(ret, '~')))
	{
		if (!(rett = msh_tilde(ret, tmp)))
			msh_panic("Memory allocation error in msh_expand ~");
		free(g_home);
	}
	else if ((tmp = ft_strchr(ret, '$')))
	{
		if (!(rett = msh_dollar(ret, tmp)))
			msh_panic("Memory allocation error in msh_dollar");
	}
	(ft_strequ(ret, rett)) ? g_expand_var = 0 : 0;
	free(ret);
	return (rett);
}
