/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 00:27:25 by callen            #+#    #+#             */
/*   Updated: 2019/03/12 11:39:26 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2, int f)
{
	char	*s3;

	if (s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	s3 = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (s3)
	{
		ft_strcpy(s3, s1);
		ft_strcat(s3, s2);
	}
	if (f == 'L')
		ft_strdel(&s1);
	else if (f == 'R')
		ft_strdel(&s2);
	else if (f == 'L' + 'R')
	{
		ft_strdel(&s1);
		ft_strdel(&s2);
	}
	return (s3);
}
