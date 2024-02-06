# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the x86 wow wevew entwy code
#

KASAN_SANITIZE := n
UBSAN_SANITIZE := n
KCOV_INSTWUMENT := n

CFWAGS_WEMOVE_common.o		= $(CC_FWAGS_FTWACE)

CFWAGS_common.o			+= -fno-stack-pwotectow

obj-y				:= entwy.o entwy_$(BITS).o syscaww_$(BITS).o
obj-y				+= common.o

obj-y				+= vdso/
obj-y				+= vsyscaww/

obj-$(CONFIG_PWEEMPTION)	+= thunk_$(BITS).o
obj-$(CONFIG_IA32_EMUWATION)	+= entwy_64_compat.o syscaww_32.o
obj-$(CONFIG_X86_X32_ABI)	+= syscaww_x32.o

