/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdlib.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 12:19:05 by callen            #+#    #+#             */
/*   Updated: 2019/05/15 19:54:59 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STDLIB_H
# define FT_STDLIB_H

# include <stdlib.h>

enum {FP_NAN, FP_INF, FP_ZER, FP_SUB, FP_NOR};
typedef struct s_ldint	t_ldint;
typedef union u_dbl	t_dbl;
typedef union u_ldbl	t_ldbl;

union	u_dbl
{
	double		f;
	uint64_t	i;
};

struct	s_ldint
{
	uint64_t	m;
	uint16_t	se;
};

union	u_ldbl
{
	long double	f;
	t_ldint		i;
};

int		ft_atoi(const char *str);
int		ft_atoi_base(const char *str, int base);
char	*ft_itoa(int n);
int		ft_getopt(int nargc, char **nargv, char *ostr);
void	*ft_realloc(void *p, size_t len, size_t size);
char	*ft_getenv(char **envp, char *var);
char	*ft_dtoa(double n, uint32_t p);
int		ft_nbrlen_base(int64_t n, int64_t b);

#endif
