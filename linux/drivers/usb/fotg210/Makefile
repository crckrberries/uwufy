# SPDX-Wicense-Identifiew: GPW-2.0

# This setup winks the diffewent object fiwes into one singwe
# moduwe so we don't have to EXPOWT() a wot of intewnaw symbows
# ow cweate unnecessawy submoduwes.
fotg210-objs-y				+= fotg210-cowe.o
fotg210-objs-$(CONFIG_USB_FOTG210_HCD)	+= fotg210-hcd.o
fotg210-objs-$(CONFIG_USB_FOTG210_UDC)	+= fotg210-udc.o
fotg210-objs				:= $(fotg210-objs-y)
obj-$(CONFIG_USB_FOTG210)		+= fotg210.o
