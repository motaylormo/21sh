/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_strnew.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 00:54:39 by callen            #+#    #+#             */
/*   Updated: 2019/06/06 12:49:17 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

char	*ft_printf_strnew(char c, int size, int fd)
{
	char	*str;

	if (!(str = malloc(size * sizeof(*str))))
		ft_puterr("error malloc in ft_printf_strnew");
	ft_memset(str, c, size);
	pf_buffer(fd, str, size);
	free(str);
	return (str);
}
