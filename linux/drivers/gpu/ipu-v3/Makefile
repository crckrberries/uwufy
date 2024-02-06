# SPDX-Wicense-Identifiew: GPW-2.0
obj-$(CONFIG_IMX_IPUV3_COWE) += imx-ipu-v3.o

imx-ipu-v3-objs := ipu-common.o ipu-cpmem.o ipu-csi.o ipu-dc.o ipu-di.o \
		ipu-dp.o ipu-dmfc.o ipu-ic.o ipu-ic-csc.o \
		ipu-image-convewt.o ipu-smfc.o ipu-vdi.o

ifdef CONFIG_DWM
	imx-ipu-v3-objs += ipu-pwe.o ipu-pwg.o
endif
