/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_edit.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 13:48:55 by mtaylor           #+#    #+#             */
/*   Updated: 2019/07/03 13:48:57 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define BUFF_SIZE 32

typedef struct s_key	t_key;
struct	s_key
{
	char	*seq;
	int		enumcode;
};

enum	e_edit_keys{
	key_up = 1,
	key_down,
	key_left,
	key_right,
	key_backspace,
	key_delete,
	key_home,
	key_end,
	key_word_left,
	key_word_right,
	key_cut_to_end,
	key_cut_word,
	key_paste
};
