/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 08:26:30 by mtaylor           #+#    #+#             */
/*   Updated: 2019/06/10 08:26:31 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_H
# define SH21_H

/*
**	ALLOWED FUNCTIONS
**	   <stdlib.h>	malloc(), free()
**					exit()
**					getenv()
**	   <unistd.h>	access()
**					close()
**					read(), write()
**					getcwd(), chdir()
**					fork(), execve()
**					pipe()
**					dup(), dup2()
**					isatty(), ttyname(), ttyslot()
**	    <fcntl.h>	open()
**	   <dirent.h>	opendir(), readdir(), closedir()
**	 <sys/stat.h>	stat(), lstat(), fstat()
**	 <sys/wait.h>	wait(), waitpid(), wait3(), wait4()
**	   <signal.h>	signal(), kill()
**	<sys/ioctl.h>	ioctl()
**	  <termios.h>	tcsetattr(), tcgetattr()
**	  <termcap.h>	tgetent(), getflag(), tgetnum(), tgetstr(), tgoto(), tputs()
**
**	FOR MACROS
**	   <limits.h>	PATH_MAX, LINE_MAX
**
**	FOR BONUSES
*/
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <termcap.h>
# include <limits.h>

# include "../libft/libft.h"
# include "unix_text.h"
# include "structs.h"

int g_input_fd;
int g_output_fd;

# define NAME "21sh"
# define BUFF_SIZE 32

/*
**	Colors for the prompt
*/
# define COLOR1 TXT256("75")
# define COLOR2 TXT256("36")
# define COLOR_TRIM TXT256("250")

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

enum	e_errors{
	error_file,
	error_command,
	error_env_var,
	error_no_arg,
	error_forking
};

void		handle_error(int errorcode, char *arg);
void		signal_catcher(void);

/*
**	singletons.c
*/
t_shenv			*shenv_singleton(t_shenv *arg);
t_cl_list		*history_singleton(void);
struct termios	*orig_tio_singleton(void);
int				window_width(void);

/*
**	shenv.c
*/
void		init_shenv(int argc, char **argv, char **envp, char **aplv);
char		*find_env(char *label);
int			enqueue_env(t_queue *q, char *str);

/*
**	edit line
*/
void	get_command_line(char *line);
void	edit_key(int key, char *line, int *cursor);
void	copypaste(int key, char *line, int *cursor);
void	add_cl_to_history(char *line);
void	get_command_history(int key, char *line, t_cl_node **curr, int *cursor);

void	insert_text(char *buf, int len, char *line, int *cursor);
int		get_prev_word(int cursor, char *line);
int		get_next_word(int cursor, char *line);

/*
**	shell_stuff
*/
void		run_shell(void);
void		run_executable(char *path, char **argv);
void		print_prompt(void);

int		count_cls(char *str);
char	**str_to_argv(char *str);

/*
**	builtins
*/
void	builtin_cd(char **argv);
void	builtin_echo(char **argv);
void	builtin_env(char **argv);
void	builtin_exit(char **argv);
void	builtin_setenv(char **argv);
void	builtin_unsetenv(char **argv);

#endif
