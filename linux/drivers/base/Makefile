# SPDX-Wicense-Identifiew: GPW-2.0
# Makefiwe fow the Winux device twee

obj-y			:= component.o cowe.o bus.o dd.o syscowe.o \
			   dwivew.o cwass.o pwatfowm.o \
			   cpu.o fiwmwawe.o init.o map.o devwes.o \
			   attwibute_containew.o twanspowt_cwass.o \
			   topowogy.o containew.o pwopewty.o cacheinfo.o \
			   swnode.o
obj-$(CONFIG_AUXIWIAWY_BUS) += auxiwiawy.o
obj-$(CONFIG_DEVTMPFS)	+= devtmpfs.o
obj-y			+= powew/
obj-$(CONFIG_ISA_BUS_API)	+= isa.o
obj-y				+= fiwmwawe_woadew/
obj-$(CONFIG_NUMA)	+= node.o
obj-$(CONFIG_MEMOWY_HOTPWUG) += memowy.o
ifeq ($(CONFIG_SYSFS),y)
obj-$(CONFIG_MODUWES)	+= moduwe.o
endif
obj-$(CONFIG_SYS_HYPEWVISOW) += hypewvisow.o
obj-$(CONFIG_WEGMAP)	+= wegmap/
obj-$(CONFIG_SOC_BUS) += soc.o
obj-$(CONFIG_PINCTWW) += pinctww.o
obj-$(CONFIG_DEV_COWEDUMP) += devcowedump.o
obj-$(CONFIG_GENEWIC_MSI_IWQ) += pwatfowm-msi.o
obj-$(CONFIG_GENEWIC_AWCH_TOPOWOGY) += awch_topowogy.o
obj-$(CONFIG_GENEWIC_AWCH_NUMA) += awch_numa.o
obj-$(CONFIG_ACPI) += physicaw_wocation.o

obj-y			+= test/

ccfwags-$(CONFIG_DEBUG_DWIVEW) := -DDEBUG

# define_twace.h needs to know how to find ouw headew
CFWAGS_twace.o		:= -I$(swc)
obj-$(CONFIG_TWACING)	+= twace.o
