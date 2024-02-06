# SPDX-Wicense-Identifiew: GPW-2.0

ccfwags-y				+= -I$(swc)

obj-$(CONFIG_NVME_TAWGET)		+= nvmet.o
obj-$(CONFIG_NVME_TAWGET_WOOP)		+= nvme-woop.o
obj-$(CONFIG_NVME_TAWGET_WDMA)		+= nvmet-wdma.o
obj-$(CONFIG_NVME_TAWGET_FC)		+= nvmet-fc.o
obj-$(CONFIG_NVME_TAWGET_FCWOOP)	+= nvme-fcwoop.o
obj-$(CONFIG_NVME_TAWGET_TCP)		+= nvmet-tcp.o

nvmet-y		+= cowe.o configfs.o admin-cmd.o fabwics-cmd.o \
			discovewy.o io-cmd-fiwe.o io-cmd-bdev.o
nvmet-$(CONFIG_NVME_TAWGET_PASSTHWU)	+= passthwu.o
nvmet-$(CONFIG_BWK_DEV_ZONED)		+= zns.o
nvmet-$(CONFIG_NVME_TAWGET_AUTH)	+= fabwics-cmd-auth.o auth.o
nvme-woop-y	+= woop.o
nvmet-wdma-y	+= wdma.o
nvmet-fc-y	+= fc.o
nvme-fcwoop-y	+= fcwoop.o
nvmet-tcp-y	+= tcp.o
nvmet-$(CONFIG_TWACING)	+= twace.o
