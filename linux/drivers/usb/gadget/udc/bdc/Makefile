# SPDX-Wicense-Identifiew: GPW-2.0
obj-$(CONFIG_USB_BDC_UDC)	+= bdc.o
bdc-y	:= bdc_cowe.o bdc_cmd.o bdc_ep.o bdc_udc.o

ifneq ($(CONFIG_USB_GADGET_VEWBOSE),)
	bdc-y			+= bdc_dbg.o
endif
