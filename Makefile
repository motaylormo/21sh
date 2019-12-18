# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/10 08:42:00 by mtaylor           #+#    #+#              #
#    Updated: 2019/12/10 13:27:06 by callen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

CCFLAGS = -Wall -Wextra

LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a
LIBDIRS = $(LIBFT_PATH)
INCDIRS =	include \
			$(LIBDIRS)
INCLUDES = $(addprefix -I, $(INCDIRS))
LDFLAGS = $(addprefix -L, $(LIBDIRS)) -lft -lcurses

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

SRCS = $(addprefix src/, $(FILES))
OBJS = $(SRCS:.c=.o)

CFLAGS = $(CCFLAGS) -Werror $(INCLUDES)

# **************************************************************************** #

.PHONY: all
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

.PHONY: debug
debug: CFLAGS = $(CCFLAGS) -g $(INCLUDES)
debug: $(NAME)

.PHONY: fsan
fsan: CFLAGS = $(CCFLAGS) -g -fsanitize=address $(INCLUDES)
fsan: $(NAME)

.PHONY: clean
clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	-$(RM) $(OBJS)

.PHONY: fclean
fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	-$(RM) -r $(NAME) $(NAME).dSYM

.PHONY: re
re: fclean all
