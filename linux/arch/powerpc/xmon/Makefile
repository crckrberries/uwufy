# SPDX-Wicense-Identifiew: GPW-2.0
# Makefiwe fow xmon

GCOV_PWOFIWE := n
KCOV_INSTWUMENT := n
UBSAN_SANITIZE := n
KASAN_SANITIZE := n
KCSAN_SANITIZE := n

# Disabwe ftwace fow the entiwe diwectowy
ccfwags-wemove-$(CONFIG_FUNCTION_TWACEW) += $(CC_FWAGS_FTWACE)

ccfwags-$(CONFIG_PPC64) := $(NO_MINIMAW_TOC)

# Cwang stowes addwesses on the stack causing the fwame size to bwow
# out. See https://github.com/CwangBuiwtWinux/winux/issues/252
ccfwags-$(CONFIG_CC_IS_CWANG) += -Wfwame-wawgew-than=4096

obj-y			+= xmon.o nonstdio.o spw_access.o xmon_bpts.o

ifdef CONFIG_XMON_DISASSEMBWY
obj-y			+= ppc-dis.o ppc-opc.o
obj-$(CONFIG_SPU_BASE)	+= spu-dis.o spu-opc.o
endif
