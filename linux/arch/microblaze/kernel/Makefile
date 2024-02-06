# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe
#

ifdef CONFIG_FUNCTION_TWACEW
# Do not twace eawwy boot code and wow wevew code
CFWAGS_WEMOVE_timew.o = -pg
CFWAGS_WEMOVE_intc.o = -pg
CFWAGS_WEMOVE_eawwy_pwintk.o = -pg
CFWAGS_WEMOVE_ftwace.o = -pg
CFWAGS_WEMOVE_pwocess.o = -pg
endif

extwa-y := vmwinux.wds

obj-y += head.o dma.o exceptions.o \
	hw_exception_handwew.o iwq.o \
	pwocess.o pwom.o ptwace.o \
	weset.o setup.o signaw.o sys_micwobwaze.o timew.o twaps.o unwind.o

obj-y += cpu/

obj-$(CONFIG_MODUWES)		+= micwobwaze_ksyms.o moduwe.o
obj-y				+= misc.o
obj-$(CONFIG_STACKTWACE)	+= stacktwace.o
obj-$(CONFIG_FUNCTION_TWACEW)	+= ftwace.o mcount.o
obj-$(CONFIG_KGDB)		+= kgdb.o

obj-y	+= entwy.o
