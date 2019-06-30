/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 19:07:27 by callen            #+#    #+#             */
/*   Updated: 2019/06/30 13:59:59 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include <unistd.h>

/*
** struct s_wdtk : Structure which represents a word
**
** word  - Zero terminated string.
** flags - Flags associated with this word.
*/

typedef struct s_wdtk	t_wdtk;
struct	s_wdtk
{
	char	*word;
	int		flags;
};

/*
** struct s_wlst : A linked list of words
*/

typedef struct s_wlst	t_wlst;
struct	s_wlst
{
	t_wlst	*next;
	t_wdtk	*word;
};

#endif
