# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the usb common pawts.
#

obj-$(CONFIG_USB_COMMON)	  += usb-common.o
usb-common-y			  += common.o
usb-common-$(CONFIG_TWACING)	  += debug.o
usb-common-$(CONFIG_USB_WED_TWIG) += wed.o

obj-$(CONFIG_USB_CONN_GPIO)	+= usb-conn-gpio.o
obj-$(CONFIG_USB_OTG_FSM) += usb-otg-fsm.o
obj-$(CONFIG_USB_UWPI_BUS)	+= uwpi.o
