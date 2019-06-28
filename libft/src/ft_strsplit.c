/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 19:24:23 by callen            #+#    #+#             */
/*   Updated: 2019/03/25 20:20:00 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wordlen(char const *s, char c)
{
	int i;
	int l;

	i = 0;
	l = 0;
	while (s[i] == c)
		i++;
	while (s[i++] && s[i] != c)
		l++;
	return (l);
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**res;

	if (!s || !(res = (char **)malloc(sizeof(*res) * (ft_wordcount(s, c) + 1))))
		return (NULL);
	i = -1;
	j = 0;
	while (++i < ft_wordcount(s, c))
	{
		k = 0;
		if (!(res[i] = ft_strnew(wordlen(&s[j], c) + 1)))
			res[i] = NULL;
		while (s[j] == c)
			j++;
		while (s[j] && s[j] != c)
			res[i][k++] = s[j++];
		res[i][k] = '\0';
	}
	res[i] = 0;
	return (res);
}
