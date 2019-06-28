/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 19:59:53 by callen            #+#    #+#             */
/*   Updated: 2019/06/27 20:27:44 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_INTERNAL_H
# define FT_PRINTF_INTERNAL_H

# include "ft_string.h"
# include "ft_stdlib.h"
# include "ft_stdio.h"

typedef struct s_gnl	t_gnl;
struct	s_gnl
{
	t_gnl	*next;
	char	*line;
	int		fd;
};

# define C(x)		(c == (x))

# define FHT		(1 <<  0)
# define FZE		(1 <<  1)
# define FSUB		(1 <<  2)
# define FADD		(1 <<  3)
# define FSPACE		(1 <<  4)
# define FMUL		(1 <<  5)
# define FDOL		(1 <<  6)
# define FL2		(1 <<  7)
# define FAQ		(1 <<  8)
# define FUP		(1 <<  9)
# define FPREC		(1 << 10)
# define FHH		1
# define FH			2
# define FJ			3
# define FZ			4
# define FL			5
# define FLL		6

# define FLAGS		flags->flags
# define TYPE		flags->type
# define FD			flags->fd
# define NB			flags->nb
# define PREC		opt[0]
# define ADDORSPACE	opt[1]
# define BLANKS		opt[2]
# define HASHTAG	opt[3]
# define SUB		opt[3]
# define ZERO		opt[4]
# define PFISSET(a)	(FLAGS & (a))

# define BLK		"\x1B[30m"
# define RED		"\x1B[31m"
# define GRN		"\x1B[32m"
# define YEL		"\x1B[33m"
# define BLU		"\x1B[34m"
# define MAG		"\x1B[35m"
# define CYN		"\x1B[36m"
# define WHT		"\x1B[37m"
# define RES		"\x1B[0m"

typedef unsigned long long	t_ull;
typedef signed long long	t_sll;
typedef struct s_flags		t_flags;
typedef struct s_pars		t_pars;

struct	s_pars
{
	uint32_t	u;
	void		(*f)(t_flags *fl, uint32_t u, char **str, va_list ap);
};

struct	s_flags
{
	int			blanks;
	int			prec;
	int			fd;
	t_sll		nb;
	uint32_t	type;
	uint32_t	flags;
};

void	ft_flags(char **str, t_flags *flags, va_list ap);
int		ft_per(char **str, t_flags *flags, va_list ap);
void	ft_fillflags(t_flags *flags, uint32_t u, char **str, va_list ap);
void	ft_type(t_flags *flags, uint32_t u, char **str, va_list ap);
void	pf_dollarsign(t_flags *flags, uint32_t u, char **str, va_list ap);
void	ft_padding(t_flags *flags, uint32_t u, char **str, va_list ap);
void	ft_precs(t_flags *flags, uint32_t u, char **str, va_list ap);

void	ft_getutype(uint32_t type, t_ull *nbr);
void	ft_typeuint(t_ull *nbr);
void	ft_typeuh(t_ull *nbr);
void	ft_typeuhh(t_ull *nbr);
void	ft_typeuj(t_ull *nbr);
void	ft_typeuz(t_ull *nbr);
void	ft_typeul(t_ull *nbr);
void	ft_typeull(t_ull *nbr);

void	ft_getstype(uint32_t type, t_sll *nbr);
void	ft_typesint(t_sll *nbr);
void	ft_typesh(t_sll *nbr);
void	ft_typeshh(t_sll *nbr);
void	ft_typesj(t_sll *nbr);
void	ft_typesz(t_sll *nbr);
void	ft_typesl(t_sll *nbr);
void	ft_typesll(t_sll *nbr);

int		ft_printf_a(t_flags *flags, va_list ap);
int		ft_printf_b(t_flags *flags, va_list ap);
int		ft_printf_c(t_flags *flags, va_list ap);
int		ft_printf_d(t_flags *flags, va_list ap);
int		ft_printf_e(t_flags *flags, va_list ap);
int		ft_printf_f(t_flags *flags, va_list ap);
int		ft_printf_g(t_flags *flags, va_list ap);
int		ft_printf_k(t_flags *flags, va_list ap);
int		ft_printf_n(t_flags *flags, va_list ap);
int		ft_printf_o(t_flags *flags, va_list ap);
int		ft_printf_p(t_flags *flags, va_list ap);
int		ft_printf_s(t_flags *flags, va_list ap);
int		ft_printf_u(t_flags *flags, va_list ap);
int		ft_printf_x(t_flags *flags, va_list ap);
int		ft_printf_3(t_flags *flags, va_list ap);
int		ft_printf_2(t_flags *flags, va_list ap);
int		ft_printf_per(t_flags *flags, va_list ap);

int		pf_buffer(int fd, void *str, int size);
int		pf_color(char **str, int fd);
int		ft_conv(char c, va_list ap, t_flags *flags);
int		ft_printf_ind(wchar_t c, t_flags *flags);
int		ft_printf_putchar_fd(wchar_t c, int fd);

int		ft_printf_le(long double nbr, t_flags *flags);
int		ft_printf_dtoa_e(double nbr, t_flags *flags, char **str);
int		ft_printf_dtoa_le(long double nbr, t_flags *flags, char **str);

int		ft_printf_lf(long double nbr, t_flags *flags);
int		ft_printf_dtoa_f(double nbr, t_flags *flags, char **str);
int		ft_printf_dtoa_lf(long double nbr, t_flags *flags, char **str);

int		ft_printf_lg(long double nbr, t_flags *flags);
int		ft_printf_g_e(double nbr, t_flags *flags);
int		ft_printf_lg_le(long double nbr, t_flags *flags);
int		ft_printf_dtoa_g_e(double nbr, t_flags *flags, char **str);
int		ft_printf_dtoa_lg_le(long double nbr, t_flags *flags, char **str);

int		ft_printf_g_f(double nbr, t_flags *flags);
int		ft_printf_lg_lf(long double nbr, t_flags *flags);
int		ft_printf_dtoa_g_f(double nbr, t_flags *flags, char **str);
int		ft_printf_dtoa_lg_lf(long double nbr, t_flags *flags, char **str);
int		ft_printf_dtoa_ent(double nbr, char **str, int up);
int		ft_printf_dtoa_lent(long double nbr, char **str, int up);

int		ft_printf_la(long double nbr, t_flags *flags);
int		ft_printf_dtoa_a(double nbr, t_flags *flags, char **str);
int		ft_printf_dtoa_la(long double nbr, t_flags *flags, char **str);

int		ft_printf_ktoa(time_t k, char **str);
time_t	pf_getmonth(time_t *k, time_t bis);
void	pf_day(time_t d, char **str);
void	pf_month(time_t m, char *str);

int		ft_printf_itoa_a(int nbr, char *str);
int		ft_printf_ls(wchar_t *str, t_flags *flags);
int		ft_printf_itoa(t_sll nbr, char **str);
int		ft_printf_itoa_base(t_ull nbr, int base, char **str, int up);
char	*ft_printf_strnew(char c, int size, int fd);

#endif
