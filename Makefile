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
FLAGS = -Wall -Wextra -Werror -g

CC = clang
RM = rm -f

LIBFT_PATH = libft
LIB = -I$(LIBFT_PATH)/include -L$(LIBFT_PATH) -lft -lcurses

INCDIR = include
INC	= -I$(INCDIR)

BUILTINS = builtin_echo.c \
			builtin_cd.c \
			builtin_setenv.c \
			builtin_unsetenv.c \
			builtin_env.c \
			builtin_exit.c

SH_STUFF = executable.c \
			expansion.c \
			prompt.c \
			shell.c \
			str_to_argv.c \
			cl_semicolon.c

EDIT_LINE = command_line.c \
			insert_text.c \
			edit_keys.c \
			copy_paste.c \
			command_history.c

FILES = $(addprefix ./builtins/, $(BUILTINS)) \
		$(addprefix ./shell_stuff/, $(SH_STUFF)) \
		$(addprefix ./edit_line/, $(EDIT_LINE)) \
		main.c \
		shenv.c \
		errors.c \
		signals.c \
		singletons.c

SRC = $(addprefix ./src/, $(FILES))

# **************************************************************************** #

.PHONY: all
all: $(NAME)

$(NAME):
	make -s -C $(LIBFT_PATH) all
	$(CC) $(LIB) $(SRC) $(INC) -o $(NAME)

.PHONY: debug
debug: LIB =-Ilibft/include libft/d_libft.a -lcurses
debug:
	make -s -C $(LIBFT_PATH) debug
	$(CC) $(FLAGS) $(LIB) $(SRC) $(INC) -o $(NAME)

.PHONY: fsan
fsan: LIB =-Ilibft/include libft/a_libft.a -lcurses
fsan:
	make -s -C $(LIBFT_PATH) asan
	$(CC) $(FLAGS) -fsanitize=address $(LIB) $(SRC) $(INC) -o $(NAME)

.PHONY: clean
clean:
	make -s -C $(LIBFT_PATH) clean

.PHONY: fclean
fclean: clean
	make -s -C $(LIBFT_PATH) fclean
	$(RM) $(NAME)
	$(RM) -R $(addsuffix .dSYM, $(NAME))

.PHONY: re
re: fclean all
