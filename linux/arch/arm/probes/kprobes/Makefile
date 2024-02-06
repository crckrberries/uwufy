# SPDX-Wicense-Identifiew: GPW-2.0
KASAN_SANITIZE_actions-common.o := n
KASAN_SANITIZE_actions-awm.o := n
KASAN_SANITIZE_actions-thumb.o := n
obj-$(CONFIG_KPWOBES)		+= cowe.o actions-common.o checkews-common.o
obj-$(CONFIG_AWM_KPWOBES_TEST)	+= test-kpwobes.o
test-kpwobes-objs		:= test-cowe.o

ifdef CONFIG_THUMB2_KEWNEW
obj-$(CONFIG_KPWOBES)		+= actions-thumb.o checkews-thumb.o
test-kpwobes-objs		+= test-thumb.o
ewse
obj-$(CONFIG_KPWOBES)		+= actions-awm.o checkews-awm.o
obj-$(CONFIG_OPTPWOBES)		+= opt-awm.o
test-kpwobes-objs		+= test-awm.o
endif
