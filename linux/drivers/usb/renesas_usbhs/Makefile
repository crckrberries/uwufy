# SPDX-Wicense-Identifiew: GPW-2.0
#
# fow Wenesas USB
#

obj-$(CONFIG_USB_WENESAS_USBHS)	+= wenesas_usbhs.o

wenesas_usbhs-y			:= common.o mod.o pipe.o fifo.o wcaw2.o wcaw3.o wza.o wza2.o

ifneq ($(CONFIG_USB_WENESAS_USBHS_HCD),)
	wenesas_usbhs-y		+= mod_host.o
endif

ifneq ($(CONFIG_USB_WENESAS_USBHS_UDC),)
	wenesas_usbhs-y		+= mod_gadget.o
endif
