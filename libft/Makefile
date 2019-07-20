# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: callen <callen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/16 21:01:37 by callen            #+#    #+#              #
#    Updated: 2019/07/19 20:51:56 by callen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft.a
DNAME := d_libft.a
ANAME := a_libft.a

CC := clang
AR := ar
RANLIB := ranlib
RM := rm -f
MV := mv
MKDIR := mkdir -p
SHELL := /bin/sh
NORME ?= pynorme

TESTMAIN := ./tests/test_main.c
INCDIR := include
SRCDIR := src

NORMEFILES := $(addsuffix *.h,$(INCDIR)/) $(addsuffix *.c,$(SRCDIR)/)

.PHONY: all
all: $(NAME)

$(NAME): libobj
	@$(AR) -cr $@ $(SRCDIR)/*.o
	$(RANLIB) $@

.PHONY: libobj
libobj:
	@make -s -C $(SRCDIR) -f Src.mk all

.PHONY: debug
debug: $(DNAME)

$(DNAME): dlibobj
	@$(AR) -rcu $@ $(SRCDIR)/*.o
	$(RANLIB) $@

.PHONY: dlibobj
dlibobj:
	@make -s -C $(SRCDIR) -f Src.mk debug

.PHONY: asan
asan: $(ANAME)

$(ANAME): alibobj
	@$(AR) -rcu $@ $(SRCDIR)/*.o
	$(RANLIB) $@

.PHONY: alibobj
alibobj:
	@make -s -C $(SRCDIR) -f Src.mk asan

.PHONY: clean
clean:
	@make -C $(SRCDIR) -f Src.mk clean

.PHONY: dclean
dclean: clean
	@$(RM) $(DNAME)

.PHONY: aclean
aclean: clean
	@$(RM) $(ANAME)

.PHONY: testclean
testclean:
	@$(RM) test.out d_test.out a_test.out
	@$(RM) -R d_test.out.dSYM a_test.out a_test.out.dSYM

.PHONY: fclean
fclean: clean
	@$(RM) $(NAME)

.PHONY: re
re: fclean all

tags:
	ctags -f $@ -R .

TAGS:
	ctags -f $@ -e -R .

.PHONY: test
test: $(NAME)
	@$(CC) -I$(INCDIR) $(CFLAGS) $(NAME) $(TESTMAIN) -o $@.out

.PHONY: d_test
d_test: debug
	@$(CC) -I$(INCDIR) $(DFLAGS) $(DNAME) $(TESTMAIN) -o $@.out

.PHONY: a_test
a_test: asan
	@$(CC) -I$(INCDIR) $(AFLAGS) $(ANAME) $(TESTMAIN) -o $@.out

.PHONY: norme
norme:
	$(NORME) $(NORMEFILES)

.PHONY: codesize
codesize:
	@printf "Lines of code: "
	@cat $(NORMEFILES) | grep -Ev '(^\/\*|^\*\*|^\*\/$$|^$$|\*\/)' | wc -l

#SRC := \
ft_atoi.c \
ft_bzero.c \
ft_getopt.c \
ft_nbrlen_base.c \
ft_isalnum.c \
ft_isalpha.c \
ft_isascii.c \
ft_isblank.c \
ft_isdigit.c \
ft_islower.c \
ft_isprint.c \
ft_isspace.c \
ft_isupper.c \
ft_itoa.c \
ft_itoa_base.c \
ft_lstadd_tail.c \
ft_lstadd.c \
ft_lstdel.c \
ft_lstdelone.c \
ft_lstiter.c \
ft_lstmap.c \
ft_lstnew.c \
ft_lstrev.c \
ft_memalloc.c \
ft_memccpy.c \
ft_memchr.c \
ft_memcmp.c \
ft_memcpy.c \
ft_memdel.c \
ft_memmove.c \
ft_memset.c \
ft_putchar_fd.c \
ft_putchar.c \
ft_putendl_fd.c \
ft_putendl.c \
ft_puterr.c \
ft_putnbr_fd.c \
ft_putnbr.c \
ft_putstr_fd.c \
ft_putstr.c \
ft_realloc.c \
ft_strcat.c \
ft_strclr.c \
ft_strchr.c \
ft_strchri.c \
ft_strcmp.c \
ft_strcpy.c \
ft_strdel.c \
ft_strdup.c \
ft_strndup.c \
ft_strequ.c \
ft_striter.c \
ft_striteri.c \
ft_strjoin.c \
ft_strjoin_free.c \
ft_strlcat.c \
ft_strlen.c \
ft_strmap.c \
ft_strmapi.c \
ft_strncat.c \
ft_strncmp.c \
ft_strncpy.c \
ft_strnequ.c \
ft_strnew.c \
ft_strnstr.c \
ft_strrchr.c \
ft_strstr.c \
ft_getenv.c \
ft_dtoa.c \
ft_wordcount.c \
ft_ostrlen.c \
ft_strchrnul.c \
ft_strspn.c \
ft_strcspn.c\
ft_strtok_r.c \
ft_strtok.c \
ft_strsplit.c \
ft_strsub.c \
ft_strtrim.c \
ft_toupper.c \
ft_tolower.c \
ft_wstrcpy.c \
ft_atoi_base.c \
fd_getdelim.c \
get_next_line.c \
pf_buffer.c \
pf_color.c \
pf_conv.c \
pf_convspe.c \
pf_flags.c \
pf_getstype.c \
pf_getstype2.c \
pf_getutype.c \
pf_getutype2.c \
pf_pars.c \
pf_per.c \
pf_printf.c \
pf_printf_a.c \
pf_printf_b.c \
pf_printf_c.c \
pf_printf_d.c \
pf_printf_dtoa_a.c \
pf_printf_dtoa_e.c \
pf_printf_dtoa_ent.c \
pf_printf_dtoa_f.c \
pf_printf_dtoa_g_e.c \
pf_printf_dtoa_g_f.c \
pf_printf_dtoa_la.c \
pf_printf_dtoa_le.c \
pf_printf_dtoa_lent.c \
pf_printf_dtoa_lf.c \
pf_printf_dtoa_lg_le.c \
pf_printf_dtoa_lg_lf.c \
pf_printf_e.c \
pf_printf_f.c \
pf_printf_g.c \
pf_printf_g_e.c \
pf_printf_g_f.c \
pf_printf_getdaymonth.c \
pf_printf_ind.c \
pf_printf_itoa.c \
pf_printf_itoa_a.c \
pf_printf_itoa_base.c \
pf_printf_k.c \
pf_printf_ktoa.c \
pf_printf_la.c \
pf_printf_le.c \
pf_printf_lf.c \
pf_printf_lg.c \
pf_printf_lg_le.c \
pf_printf_lg_lf.c \
pf_printf_ls.c \
pf_printf_o.c \
pf_printf_p.c \
pf_printf_putchar_fd.c \
pf_printf_s.c \
pf_printf_strnew.c \
pf_printf_u.c \
pf_printf_x.c \
pf_printf_n.c \
pf_fprintf.c \
fq_queue.c \
hash_bucket.c \
hash_copy.c \
hash_create.c \
hash_dispose.c \
hash_flush.c \
hash_insert.c \
hash_pstats.c \
hash_remove.c \
hash_search.c \
hash_size.c \
hash_string.c \
hash_walk.c \
dq_deque.c
