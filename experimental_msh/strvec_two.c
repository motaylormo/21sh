/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strvec_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 00:44:02 by callen            #+#    #+#             */
/*   Updated: 2019/06/03 01:16:20 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_strvec.h"

void		strvec_dispose(char **array)
{
	if (array == NULL)
		return ;
	strvec_flush(array);
	free(array);
}

int			strvec_remove(char **array, char *name)
{
	register int	i;
	register int	j;
	char			*x;

	if (array == NULL)
		return (0);
	i = -1;
	while (array[++i])
		if (ft_strequ(name, array[i]))
		{
			x = array[i];
			j = i - 1;
			while (array[++j])
				array[j] = array[j + 1];
			free(x);
			return (1);
		}
	return (0);
}

int			strvec_nremove(char **array, char *name, int nl)
{
	register int	i;
	register int	j;
	char			*x;

	if (array == NULL)
		return (0);
	i = -1;
	while (array[++i])
		if (ft_strnequ(name, array[i], nl))
		{
			x = array[i];
			j = i - 1;
			while (array[++j])
				array[j] = array[j + 1];
			free(x);
			return (1);
		}
	return (0);
}

int			strvec_strcmp(register char **s1, register char **s2)
{
	int res;

	if ((res = **s1 - **s2) == 0)
		res = ft_strcmp(*s1, *s2);
	return (res);
}

void		strvec_qsort(char **arr, int len)
{
	register char	*piv;
	register char	*tmp;
	register int	i;
	register int	j;

	if (len < 2 || !arr || !*arr)
		return ;
	piv = arr[len / 2];
	i = 0;
	j = len - 1;
	while (1)
	{
		while (strvec_strcmp(arr + i, &piv) > 0)
			i++;
		while (strvec_strcmp(arr + j, &piv) < 0)
			j--;
		if (i >= j)
			break ;
		tmp = arr[i];
		arr[i] = arr[j];
		arr[j] = tmp;
	}
	strvec_qsort(arr, i);
	strvec_qsort(arr + i, len - i);
}

void		strvec_sort(char **array)
{
	register int	len;

	if ((len = strvec_len(array)) < 2 || !array || !*array)
		return ;
	strvec_qsort(array, len);
}
