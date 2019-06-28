/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_macros.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 19:59:28 by callen            #+#    #+#             */
/*   Updated: 2019/05/15 19:59:29 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MACROS_H
# define FT_MACROS_H

# define ABS(a) ((a) < 0 ? (-a) : (a))
# define MAX(a, b) (((b) & ((a - b) >> 31)) | ((a) & (~(a - b) >> 31)))
# define MIN(a, b) (((a) & ((a - b) >> 31)) | ((b) & (~(a - b) >> 31)))
# define ITOCB(n, b) ((n % b) + (n % b < 10 ? '0' : 'a' - 10))

# define FT_UCHAR_MAX (unsigned char)(~0)
# define FT_CHAR_MAX (signed char)(FT_UCHAR_MAX / 2)
# define FT_CHAR_MIN (~FT_CHAR_MAX)

# define FT_USHRT_MAX (unsigned short)(~0)
# define FT_SHRT_MAX (signed short)(FT_USHRT_MAX / 2)
# define FT_SHRT_MIN (~FT_SHRT_MAX)

# define FT_UINT_MAX (~(0U))
# define FT_INT_MAX (signed int)(FT_UINT_MAX / 2)
# define FT_INT_MIN (~(FT_INT_MAX))

# define FT_ULONG_MAX (~(0UL))
# define FT_LONG_MAX (signed long)(FT_ULONG_MAX / 2)
# define FT_LONG_MIN (~(FT_LONG_MAX))

# define FT_ULLONG_MAX (~(0ULL))
# define FT_LLONG_MAX (signed long long)(FT_ULLONG_MAX / 2)
# define FT_LLONG_MIN (~(FT_LLONG_MAX))

# define RET_IF(c, r) if (c) return (r)
# define RET_NONE(c) if (c) return
# define IF_NULL(x) if (x) return (NULL)
# define DO_IF(c, d) if (c) d
# define DO_ALL(c, ...) if (c) __VA_ARGS__
# define WHILE(c, d) while (c) d
# define ELSE_DO(d) else d
# define IF_ELSE(c, a, b) DO_IF(c, a); ELSE_DO(b)

#endif
