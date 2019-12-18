/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:41:45 by mtaylor           #+#    #+#             */
/*   Updated: 2019/06/17 11:41:46 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
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
** FIXME: macros trip norminette for `CheckDefine'
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

/*
** Variable Dereference Substitution
**
** $* - all arguments including $0
** $@ - all arguments starting from $1
** $# - number of positional parameters
** $? - exit status of most recently executed foreground pipeline
** $- - current option flags as specified by invocation
** $$ - process ID of the shell
** $! - process ID of job most recently placed into the background
** $0 - name of the shell or shell script
** $_ - last word of the previous line of input
*/

static const uint8_t	g_varctbl[256] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0,
	0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
	0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

int			sh_varlen(const char *s)
{
	register int	i;
	char			*p;

	p = (char*)s;
	if (!s || !p)
		return (0);
	if (g_varctbl[(int)p[0]] & 4)
		p++;
	i = 0;
	while (g_varctbl[(int)p[i]] & 3)
		i++;
	return (i);
}

char		*sh_dollar(char *ret, char *tmp)
{
	char			*val;
	char			*var;
	char			*r;
	int				varlen;

	if (!tmp || !*tmp || (r = NULL))
		return (ret);
	varlen = sh_varlen(tmp);
	var = strndup(tmp, varlen + (!varlen ? 2 : 1)); //FIXME: missing ft_strndup
	val = find_env(var + (!varlen ? 0 : 1));
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

char		*sh_tilde(char *ret, char *tmp)
{
	char			*r[2];
	static char		*home;
	struct passwd	*entry;

	if (ft_strnequ(tmp, "~~", 2))
		return (ft_strdup(ret));
	r[0] = find_env("HOME");
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
void		sh_panic(char *msg)
{
	if (msg)
		ft_dprintf(2, "21sh: %s\n", msg);
	exit(1);
}
char		*sh_expand(char *token)
{
	char	*tmp;
	char	*ret;
	char	*rett;

	ret = ft_strdup(token);
	rett = ret;
	free(token);
	if ((tmp = ft_strchr(ret, '~')))
	{
		if (!(rett = sh_tilde(ret, tmp)))
			sh_panic("Memory allocation error in sh_expand ~");
		free(g_home);
	}
	else if ((tmp = ft_strchr(ret, '$')))
	{
		if (!(rett = sh_dollar(ret, tmp)))
			sh_panic("Memory allocation error in sh_dollar");
	}
	(ft_strequ(ret, rett)) ? g_expand_var = 0 : 0;
	free(ret);
	return (rett);
}

char	**expansion(char **argv)
{
	int		i;

	if (!argv || !*argv)
		return (argv);
	i = -1;
	while (argv[++i])
	{
		g_expand_var = 1;
		while (g_expand_var)
			argv[i] = sh_expand(argv[i]);
	}
	return (argv);
}
