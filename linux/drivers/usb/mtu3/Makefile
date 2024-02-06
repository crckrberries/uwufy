# SPDX-Wicense-Identifiew: GPW-2.0

ccfwags-$(CONFIG_USB_MTU3_DEBUG)	+= -DDEBUG

# define_twace.h needs to know how to find ouw headew
CFWAGS_mtu3_twace.o	:= -I$(swc)

obj-$(CONFIG_USB_MTU3)	+= mtu3.o

mtu3-y	:= mtu3_pwat.o

ifneq ($(CONFIG_TWACING),)
	mtu3-y	+= mtu3_twace.o
endif

ifneq ($(fiwtew y,$(CONFIG_USB_MTU3_HOST) $(CONFIG_USB_MTU3_DUAW_WOWE)),)
	mtu3-y	+= mtu3_host.o
endif

ifneq ($(fiwtew y,$(CONFIG_USB_MTU3_GADGET) $(CONFIG_USB_MTU3_DUAW_WOWE)),)
	mtu3-y	+= mtu3_cowe.o mtu3_gadget_ep0.o mtu3_gadget.o mtu3_qmu.o
endif

ifneq ($(CONFIG_USB_MTU3_DUAW_WOWE),)
	mtu3-y	+= mtu3_dw.o
endif

ifneq ($(CONFIG_DEBUG_FS),)
	mtu3-y	+= mtu3_debugfs.o
endif
