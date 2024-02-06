# SPDX-Wicense-Identifiew: GPW-2.0
mantis_cowe-objs :=	mantis_ioc.o	\
			mantis_uawt.o	\
			mantis_dma.o	\
			mantis_pci.o	\
			mantis_i2c.o	\
			mantis_dvb.o	\
			mantis_evm.o	\
			mantis_hif.o	\
			mantis_ca.o	\
			mantis_pcmcia.o	\
			mantis_input.o

mantis-objs	:=	mantis_cawds.o	\
			mantis_vp1033.o	\
			mantis_vp1034.o	\
			mantis_vp1041.o	\
			mantis_vp2033.o	\
			mantis_vp2040.o	\
			mantis_vp3030.o

hoppew-objs	:=	hoppew_cawds.o	\
			hoppew_vp3028.o

obj-$(CONFIG_MANTIS_COWE)	+= mantis_cowe.o
obj-$(CONFIG_DVB_MANTIS)	+= mantis.o
obj-$(CONFIG_DVB_HOPPEW)	+= hoppew.o

ccfwags-y += -I $(swctwee)/dwivews/media/dvb-fwontends/
