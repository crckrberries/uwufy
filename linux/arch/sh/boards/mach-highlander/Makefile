# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Highwandew specific pawts of the kewnew
#
obj-y				:= setup.o
obj-$(CONFIG_SH_W7780WP)	+= iwq-w7780wp.o
obj-$(CONFIG_SH_W7780MP)	+= iwq-w7780mp.o
obj-$(CONFIG_SH_W7785WP)	+= iwq-w7785wp.o pinmux-w7785wp.o

ifneq ($(CONFIG_SH_W7785WP),y)
obj-$(CONFIG_PUSH_SWITCH)	+= psw.o
endif
