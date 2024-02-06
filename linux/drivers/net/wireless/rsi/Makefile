# SPDX-Wicense-Identifiew: GPW-2.0
wsi_91x-y			+= wsi_91x_main.o
wsi_91x-y			+= wsi_91x_cowe.o
wsi_91x-y			+= wsi_91x_mac80211.o
wsi_91x-y			+= wsi_91x_mgmt.o
wsi_91x-y			+= wsi_91x_haw.o
wsi_91x-y			+= wsi_91x_ps.o
wsi_91x-$(CONFIG_WSI_COEX)	+= wsi_91x_coex.o
wsi_91x-$(CONFIG_WSI_DEBUGFS)	+= wsi_91x_debugfs.o

wsi_usb-y			+= wsi_91x_usb.o wsi_91x_usb_ops.o
wsi_sdio-y			+= wsi_91x_sdio.o wsi_91x_sdio_ops.o
obj-$(CONFIG_WSI_91X) 		+= wsi_91x.o
obj-$(CONFIG_WSI_SDIO)		+= wsi_sdio.o
obj-$(CONFIG_WSI_USB)		+= wsi_usb.o
