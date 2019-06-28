/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashtab.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 17:21:28 by callen            #+#    #+#             */
/*   Updated: 2019/05/22 19:15:03 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HASHTAB_H
# define FT_HASHTAB_H

/*
**# include "config.h"
**# include "bashansi.h"
**# include "shell.h"
*/

# include "ft_string.h"
# include <sys/types.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_htab	t_htab;
typedef struct s_bucket	t_bkt;

typedef int		t_hash_wfunc(t_bkt *b);

typedef char	*t_shstrf(char *s);
typedef void	t_shfree(void *p);

/*
** next - Link to next hashed key in this bucket.
** key - What we look up.
** data - What we really want.
** khash - What key hashes to
** tfnd - Number of times this item has been found.
*/

struct			s_bucket
{
	t_bkt		*next;
	char		*key;
	void		*data;
	unsigned	khash;
	int			tfnd;
};

/*
** bucket_array - Where the data is kept.
** nbkts - How many buckets does this table have.
** nents - How many entries does this table have.
*/

struct			s_htab
{
	t_bkt	**bktarr;
	int		nbkts;
	int		nents;
};

/*
** Operations on tables as a whole
*/

t_htab			*hash_create(int n);
t_htab			*hash_copy(t_htab *h, t_shstrf *f);
void			hash_flush(t_htab *h, t_shfree *f);
void			hash_dispose(t_htab *h);
void			hash_walk(t_htab *h, t_hash_wfunc *f);

/*
** Operations to extract information from or pieces of tables
*/

int				hash_bucket(const char *s, t_htab *h);
int				hash_size(t_htab *h);

/*
** Operations on hash table entries
*/

t_bkt			*hash_search(const char *s, t_htab *h, int n);
t_bkt			*hash_insert(char *s, t_htab *h, int n);
t_bkt			*hash_remove(const char *s, t_htab *h, int n);

/*
** Miscellaneous
*/

unsigned		hash_string(const char *s);
void			hash_pstats(t_htab *table, char *name);

/*
** Rely on properties of unsigned division (unsigned/int -> unsigned) and
** don't discard the upper 32 bits of the value, if present.
*/

# define HASH_BUCKET(s,t,h) (((h) = hash_string(s)) & ((t)->nbkts - 1))

/*
** Redefine the function as a macro for speed.
*/

# define HASH_ITEMS(b,t) ((t && (b < t->nbkts)) ? t->bktarr[b] : NULL)

/*
** Default number of buckets in the hash table.
**  - must be power of two
*/

# define DEFAULT_HASH_BUCKETS 128

# define HASH_ENTRIES(ht)	((ht) ? (ht)->nents : 0)
# ifdef SAVESTR
#  undef SAVESTR
# endif
# define SAVESTR(x) ft_strcpy(malloc(1+ft_strlen((x))), (x))

/*
** flags for hash_search and hash_insert
*/

# define HASH_NOSRCH	0x01
# define HASH_CREATE	0x02

#endif
