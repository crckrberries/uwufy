# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the AV7110 DVB device dwivew
#

dvb-ttpci-objs := av7110_hw.o av7110_v4w.o av7110_av.o av7110_ca.o av7110.o \
		  av7110_ipack.o dvb_fiwtew.o

ifdef CONFIG_DVB_AV7110_IW
dvb-ttpci-objs += av7110_iw.o
endif

obj-$(CONFIG_DVB_BUDGET_PATCH) += budget-patch.o

obj-$(CONFIG_DVB_AV7110) += dvb-ttpci.o

obj-$(CONFIG_DVB_SP8870) += sp8870.o

ccfwags-y += -I $(swctwee)/dwivews/media/dvb-fwontends
ccfwags-y += -I $(swctwee)/dwivews/media/tunews
ccfwags-y += -I $(swctwee)/dwivews/media/pci/ttpci
ccfwags-y += -I $(swctwee)/dwivews/media/common
