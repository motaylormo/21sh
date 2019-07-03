/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:12:04 by mtaylor           #+#    #+#             */
/*   Updated: 2019/06/17 11:12:07 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <limits.h>

/*
**	For storing working env
*/
typedef struct s_node	t_node;
struct	s_node{
	t_node	*next;
	char	label[PATH_MAX + 1];
	char	data[PATH_MAX + 1];
};

typedef struct s_queue	t_queue;
struct	s_queue{
	t_node	*first;
	t_node	*last;
};

/*
**	For storing the orig stuff from main
*/
typedef struct s_args	t_args;
struct	s_args
{
	int		argc;
	char	**argv;
	char	**envp;
	char	**aplv;
};

/*
**	General program env struct
*/
typedef struct s_env	t_shenv;
struct	s_env
{
	char		cl[LINE_MAX + 1];
	t_args		*main_args;
	t_queue		*envlist;
	int			input_fd;
	int			output_fd;
};

/*
**	Keeping things together in tables
*/
typedef struct s_str_w_func	t_command;
struct	s_str_w_func
{
	char	*str;
	void	(*f)(char**);
};

/*
**	For storing command line history
*/
typedef struct s_dll_node	t_cl_node;
struct	s_dll_node{
	t_cl_node	*next;
	t_cl_node	*prev;
	char		cl[LINE_MAX + 1];
};

typedef struct s_dll_list	t_cl_list;
struct	s_dll_list{
	t_cl_node	*top;
};

#endif
