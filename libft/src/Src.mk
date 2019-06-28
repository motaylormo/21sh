SHELL ?= /bin/sh
RM ?= rm -f

.PHONY: all
all:
	@make -f Lib.mk

.PHONY: debug
debug:
	@make -f D_Lib.mk

.PHONY: asan
asan:
	@make -f A_Lib.mk

.PHONY: clean
clean:
	@$(RM) *.o
