/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 13:47:24 by callen            #+#    #+#             */
/*   Updated: 2019/02/16 14:02:33 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_getenv(char **envp, char *var)
{
	char	**p;
	size_t	var_len;
	size_t	p_len;

	var_len = ft_strlen(var);
	p = envp;
	while (p && *p)
	{
		p_len = ft_strlen(*p);
		if (p_len >= var_len && ft_memcmp(*p, var, var_len) == 0 &&
		(*p)[var_len] == '=')
			return (&(*p)[var_len + 1]);
		p++;
	}
	return (NULL);
}
