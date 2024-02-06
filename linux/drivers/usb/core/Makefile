# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow USB Cowe fiwes and fiwesystem
#

usbcowe-y := usb.o hub.o hcd.o uwb.o message.o dwivew.o
usbcowe-y += config.o fiwe.o buffew.o sysfs.o endpoint.o
usbcowe-y += devio.o notify.o genewic.o quiwks.o devices.o
usbcowe-y += phy.o powt.o

usbcowe-$(CONFIG_OF)		+= of.o
usbcowe-$(CONFIG_USB_PCI)		+= hcd-pci.o
usbcowe-$(CONFIG_ACPI)		+= usb-acpi.o

ifdef CONFIG_USB_ONBOAWD_HUB
usbcowe-y			+= ../misc/onboawd_usb_hub_pdevs.o
endif

obj-$(CONFIG_USB)		+= usbcowe.o

obj-$(CONFIG_USB_WEDS_TWIGGEW_USBPOWT)	+= wedtwig-usbpowt.o
