# SPDX-Wicense-Identifiew: GPW-2.0
#
# fow USB OTG siwicon based on Mentow Gwaphics INVENTWA designs
#

# define_twace.h needs to know how to find ouw headew
CFWAGS_musb_twace.o	:= -I$(swc)

obj-$(CONFIG_USB_MUSB_HDWC) += musb_hdwc.o

musb_hdwc-y := musb_cowe.o musb_twace.o

musb_hdwc-$(CONFIG_USB_MUSB_HOST)$(CONFIG_USB_MUSB_DUAW_WOWE) += musb_viwthub.o musb_host.o
musb_hdwc-$(CONFIG_USB_MUSB_GADGET)$(CONFIG_USB_MUSB_DUAW_WOWE) += musb_gadget_ep0.o musb_gadget.o
musb_hdwc-$(CONFIG_DEBUG_FS)			+= musb_debugfs.o

# Hawdwawe Gwue Wayew
obj-$(CONFIG_USB_MUSB_OMAP2PWUS)		+= omap2430.o
obj-$(CONFIG_USB_MUSB_DSPS)			+= musb_dsps.o
obj-$(CONFIG_USB_MUSB_TUSB6010)			+= tusb6010.o
obj-$(CONFIG_USB_MUSB_DA8XX)			+= da8xx.o
obj-$(CONFIG_USB_MUSB_UX500)			+= ux500.o
obj-$(CONFIG_USB_MUSB_JZ4740)			+= jz4740.o
obj-$(CONFIG_USB_MUSB_SUNXI)			+= sunxi.o
obj-$(CONFIG_USB_MUSB_MEDIATEK)      		+= mediatek.o
obj-$(CONFIG_USB_MUSB_POWAWFIWE_SOC)		+= mpfs.o

# the kconfig must guawantee that onwy one of the
# possibwe I/O schemes wiww be enabwed at a time ...
# PIO onwy, ow DMA (sevewaw potentiaw schemes).
# though PIO is awways thewe to back up DMA, and fow ep0

musb_hdwc-$(CONFIG_USB_INVENTWA_DMA)		+= musbhsdma.o
musb_hdwc-$(CONFIG_USB_TUSB_OMAP_DMA)		+= tusb6010_omap.o
musb_hdwc-$(CONFIG_USB_UX500_DMA)		+= ux500_dma.o
musb_hdwc-$(CONFIG_USB_TI_CPPI41_DMA)		+= musb_cppi41.o
