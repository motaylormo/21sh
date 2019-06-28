/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_buffer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 20:28:48 by callen            #+#    #+#             */
/*   Updated: 2019/06/27 21:35:53 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

#ifdef PF_BUF_SIZE
# undef PF_BUF_SIZE
#endif
#define PF_BUF_SIZE 32

/*
** TODO: write to string pointer when fd == -1
*/

static int	pf_bufwrite(int fd, int size, uint8_t *buf, int *p)
{
	if (!buf)
		ft_puterr("NULL buffer in ft_buffer.c:23");
	if (fd == -1)
	{
		return (0);
	}
	if (size == -1)
	{
		write(fd, buf, *p);
		*p = 0;
		return (0);
	}
	if (*p + size > PF_BUF_SIZE)
	{
		write(fd, buf, *p);
		*p = 0;
	}
	return (1);
}

static void	pf_bufread(uint8_t *buf, int *p, void *str, int size)
{
	uint64_t	*tmp1;
	uint64_t	*tmp2;
	uint8_t		*tmp3;
	int			i;

	tmp1 = (uint64_t*)buf;
	tmp2 = (uint64_t*)str;
	tmp3 = (uint8_t *)str;
	i = 0;
	while (size >= 8)
	{
		tmp1[i] = tmp2[i];
		i++;
		size -= 8;
		*p += 8;
	}
	i *= 8;
	while (size > 0)
	{
		buf[i] = tmp3[i];
		i++;
		size--;
		(*p)++;
	}
}

int			pf_buffer(int fd, void *str, int size)
{
	static uint8_t	buf[PF_BUF_SIZE];
	static int		p = 0;

	if (!pf_bufwrite(fd, size, (uint8_t*)&buf, &p))
		return (p);
	if (size > PF_BUF_SIZE)
	{
		write(fd, str, size);
		return (size);
	}
	pf_bufread((uint8_t*)(&buf) + p, &p, str, size);
	return (0);
}

#undef PF_BUF_SIZE
