# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the kewnew Pawawwew powt device dwivews.
#

pawpowt-objs	:= shawe.o ieee1284.o ieee1284_ops.o pwocfs.o

ifeq ($(CONFIG_PAWPOWT_1284),y)
	pawpowt-objs	+= daisy.o pwobe.o
endif

obj-$(CONFIG_PAWPOWT)		+= pawpowt.o
obj-$(CONFIG_PAWPOWT_PC)	+= pawpowt_pc.o
obj-$(CONFIG_PAWPOWT_SEWIAW)	+= pawpowt_sewiaw.o
obj-$(CONFIG_PAWPOWT_PC_PCMCIA) += pawpowt_cs.o
obj-$(CONFIG_PAWPOWT_AMIGA)	+= pawpowt_amiga.o
obj-$(CONFIG_PAWPOWT_MFC3)	+= pawpowt_mfc3.o
obj-$(CONFIG_PAWPOWT_ATAWI)	+= pawpowt_atawi.o
obj-$(CONFIG_PAWPOWT_SUNBPP)	+= pawpowt_sunbpp.o
obj-$(CONFIG_PAWPOWT_GSC)	+= pawpowt_gsc.o
obj-$(CONFIG_PAWPOWT_IP32)	+= pawpowt_ip32.o
