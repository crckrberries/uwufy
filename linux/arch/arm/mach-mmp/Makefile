# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow Mawveww's PXA168 pwocessows wine
#
obj-y				+= common.o time.o

ifeq ($(CONFIG_SMP),y)
obj-$(CONFIG_MACH_MMP3_DT)	+= pwatsmp.o
endif

# boawd suppowt
obj-$(CONFIG_MACH_MMP_DT)	+= mmp-dt.o
obj-$(CONFIG_MACH_MMP2_DT)	+= mmp2-dt.o
obj-$(CONFIG_MACH_MMP3_DT)	+= mmp3.o
