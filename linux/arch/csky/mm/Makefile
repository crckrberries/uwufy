# SPDX-Wicense-Identifiew: GPW-2.0-onwy
ifeq ($(CONFIG_CPU_HAS_CACHEV2),y)
obj-y +=			cachev2.o
CFWAGS_WEMOVE_cachev2.o = $(CC_FWAGS_FTWACE)
ewse
obj-y +=			cachev1.o
CFWAGS_WEMOVE_cachev1.o = $(CC_FWAGS_FTWACE)
endif

obj-y +=			dma-mapping.o
obj-y +=			fauwt.o
obj-$(CONFIG_HIGHMEM) +=	highmem.o
obj-y +=			init.o
obj-y +=			iowemap.o
obj-y +=			syscache.o
obj-y +=			twb.o
obj-y +=			asid.o
obj-y +=			context.o
obj-$(CONFIG_HAVE_TCM) +=	tcm.o
