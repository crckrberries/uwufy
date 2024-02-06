# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the USB input dwivews
#

usbhid-y	:= hid-cowe.o
usbhid-$(CONFIG_USB_HIDDEV)	+= hiddev.o
usbhid-$(CONFIG_HID_PID)	+= hid-pidff.o

obj-$(CONFIG_USB_HID)		+= usbhid.o
obj-$(CONFIG_USB_KBD)		+= usbkbd.o
obj-$(CONFIG_USB_MOUSE)		+= usbmouse.o

