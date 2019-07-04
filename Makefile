# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/10 08:42:00 by mtaylor           #+#    #+#              #
#    Updated: 2019/06/28 00:23:55 by callen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh
CCFLAGS = -Wall -Wextra -Werror -g

SHELL = /bin/sh

CC = clang
RM = rm -f

LIBPATH = libft
LIBS = -lft -lcurses
LDFLAGS = -L$(LIBPATH)

SRCDIR = src

INCDIR = include
INCLUDES = -I$(INCDIR) -I$(LIBPATH)/$(INCDIR)

CFLAGS = $(CCFLAGS) $(INCLUDES)

BUILTINS =	builtin_echo.c \
			builtin_cd.c \
			builtin_setenv.c \
			builtin_unsetenv.c \
			builtin_env.c \
			builtin_exit.c

SH_STUFF =	executable.c \
			expansion.c \
			prompt.c \
			shell.c \
			str_to_argv.c \
			redirection.c

EDIT_LINE =	command_line.c \
			edit_keys.c \
			copy_paste.c \
			cl_history.c \
			edit_line_util.c

STRVECLIB =	strvec_one.c \
			strvec_two.c \
			strvec_conv.c \
			strlist_one.c \
			strlist_two.c \
			strlist_three.c

LINKEDLST =	generic_list.c \
			word_list_init.c

FILES =	$(addprefix builtins/, $(BUILTINS)) \
		$(addprefix shell_stuff/, $(SH_STUFF)) \
		$(addprefix edit_line/, $(EDIT_LINE)) \
		$(addprefix string_vectors/, $(STRVECLIB)) \
		$(addprefix linked_lists/, $(LINKEDLST)) \
		main.c \
		shenv.c \
		errors.c \
		signals.c \
		singletons.c

SRC =	$(addprefix $(SRCDIR)/, $(FILES))
OBJ = $(SRC:.c=.o)

# **************************************************************************** #

.PHONY: all
all: $(NAME)

$(NAME): objfiles
	make -s -C $(LIBPATH) all
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) $(OBJ) -o $(NAME)

.PHONY: objfiles
objfiles: $(SRC:.c=.o)

.PHONY: debug
debug: LIBS = libft/d_libft.a -lcurses
debug: objfiles
	make -s -C $(LIBPATH) debug
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) $(OBJ) -o $(NAME)

.PHONY: fsan
fsan: LIBS = libft/a_libft.a -lcurses
fsan: CCFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
fsan:
	make -s -C $(LIBPATH) asan
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) $(SRC) -o $(NAME)

.PHONY: clean
clean:
	make -s -C $(LIBPATH) clean
	$(RM) $(OBJ)

.PHONY: fclean
fclean: clean
	make -s -C $(LIBPATH) fclean
	$(RM) $(NAME)
	$(RM) -R $(NAME).dSYM

.PHONY: re
re: fclean all
