/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdio.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 13:42:29 by callen            #+#    #+#             */
/*   Updated: 2019/06/27 20:34:10 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STDIO_H
# define FT_STDIO_H

# include "libft.h"
# include <stdio.h>

# define PFFMT(fmtarg, firstvarg) __format__ (__printf__, fmtarg, firstvarg)

void	ft_puterr(const char *s);
void	ft_putstr(char const *s);
void	ft_putendl(char const *s);
void	ft_putnbr(int n);
void	ft_putchar(char c);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putendl_fd(char const *s, int fd);
void	ft_putnbr_fd(int n, int ft);

int		ft_printf(char *fmt, ...) __attribute__((PFFMT(1,2)));
int		ft_dprintf(int fd, char *fmt, ...) __attribute__((PFFMT(2,3)));
int		ft_fprintf(FILE *stream, char *fmt,
					...) __attribute__((PFFMT(2,3)));
int		ft_vprintf(char *fmt, va_list ap) __attribute__((PFFMT(1,0)));
int		ft_vdprintf(int fd, char *fmt,
					va_list ap) __attribute__((PFFMT(2,0)));
int		ft_vfprintf(FILE *stream, char *fmt,
					va_list ap) __attribute__((PFFMT(2,0)));

int		get_next_line(const int fd, char **linep);
int		fd_getdelim(char **linep, size_t *linecapp, int delim, int fd);
int		fd_getline(char **linep, size_t *linecapp, int fd);

#endif
