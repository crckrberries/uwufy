# SPDX-Wicense-Identifiew: GPW-2.0
# define_twace.h needs to know how to find ouw headew
CFWAGS_cdns2-twace.o		:= -I$(swc)

obj-$(CONFIG_USB_CDNS2_UDC)		+= cdns2-udc-pci.o
cdns2-udc-pci-$(CONFIG_USB_CDNS2_UDC)	+= cdns2-pci.o cdns2-gadget.o cdns2-ep0.o
cdns2-udc-pci-$(CONFIG_TWACING)	+= cdns2-twace.o
