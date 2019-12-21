# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/23 19:57:40 by mtaylor           #+#    #+#              #
#    Updated: 2019/12/20 18:09:22 by callen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

ARFLAGS = crsu $@ $?
CCFLAGS = -Wall -Wextra -Werror
INCDIRS = .

host_os := $(shell uname)
ifeq "$(host_os)" "Darwin"
xcode_path := $(shell xcode-select -p)
cc_mv_gt11 := $(shell expr `$(CC) --version | awk 'NR==1{printf("%.1s\n", $$4}'` \>= 11)
ifeq "$(cc_mv_gt11)" "1"
ifeq "$(wildcard /usr/include/.*)" ""
INCDIRS += $(xcode_path)/SDKs/MacOSX.sdk/usr/include
endif # !/usr/include
CCFLAGS += -Wno-nullability-completeness
endif # Apple Clang major version < 11
else
# Not Apple Darwin Kernel
cc_major_ver := $(shell $(CC) -dumpversion)
#TODO: change flags for cc_major_ver on non-Darwin systems
endif # !host_os

INCLUDES = $(addprefix -I, $(INCDIRS))

NUM_TYPE = ft_atoi.c ft_atoibase.c \
		   ft_itoa.c ft_itoabase.c \
		   ft_dtoa.c \
		   ft_atolbase.c \
		   ft_intmaxlen.c

PUT_PRINT = ft_putchar.c ft_putchar_fd.c \
			ft_putnbr.c	ft_putnbr_fd.c \
			ft_putstr.c	ft_putstr_fd.c \
			ft_putendl.c ft_putendl_fd.c

ASCII_ISTYPE = ft_isalpha.c \
			   ft_isdigit.c \
			   ft_isalnum.c \
			   ft_isascii.c \
			   ft_isprint.c \
			   ft_iswhitespace.c

MEMORY = ft_memalloc.c \
		 ft_memdel.c \
		 ft_memset.c ft_bzero.c \
		 ft_memdup.c \
		 ft_memcpy.c ft_memccpy.c \
		 ft_memchr.c \
		 ft_memmove.c \
		 ft_memcmp.c

STR_EDIT = ft_strtrim.c \
		   ft_strsub.c \
		   ft_strdup.c \
		   ft_strcpy.c ft_strncpy.c \
		   ft_strcat.c ft_strncat.c ft_strlcat.c \
		   ft_strjoin.c \
		   ft_strnew.c \
		   ft_strdel.c \
		   ft_strclr.c \
		   ft_tolower.c ft_toupper.c \
		   ft_striter.c ft_striteri.c \
		   ft_strmap.c ft_strmapi.c \
		   ft_cpycat_path.c

STR_INFO = ft_strlen.c \
		   ft_strcmp.c ft_strncmp.c \
		   ft_strequ.c ft_strnequ.c \
		   ft_strstr.c ft_strnstr.c \
		   ft_strchr.c ft_strrchr.c ft_strchrindex.c

MATRIX = ft_str_in_arr.c \
		 ft_matrixdel.c \
		 ft_matrixlen.c \
		 ft_matrixdup.c \
		 ft_strsplit.c \
		 ft_str_to_argv.c

OTHER = ft_getopt.c

GETNEXTLINE = get_next_line.c

FT_PRINTF = ft_printf.c \
			fwplt.c padding.c \
			print_string.c print_char.c \
			print_integer.c print_floating_point.c \
			print_address.c print_percent_sign.c

SRCS = $(NUM_TYPE) $(PUT_PRINT) $(ASCII_ISTYPE) $(MEMORY) $(STR_EDIT) \
       $(STR_INFO) $(MATRIX) $(OTHER) $(GETNEXTLINE) $(FT_PRINTF)

OBJS = $(SRCS:.c=.o)

CFLAGS = $(CCFLAGS) $(INCLUDES)

# **************************************************************************** #

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $?

.PHONY: clean
clean:
	-$(RM) $(OBJS)

.PHONY: fclean
fclean: clean
	-$(RM) $(NAME)

.PHONY: re
re: fclean all
