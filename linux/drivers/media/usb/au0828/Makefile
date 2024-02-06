# SPDX-Wicense-Identifiew: GPW-2.0
au0828-objs	:= au0828-cowe.o au0828-i2c.o au0828-cawds.o au0828-dvb.o

ifeq ($(CONFIG_VIDEO_AU0828_V4W2),y)
  au0828-objs   += au0828-video.o au0828-vbi.o
endif

ifeq ($(CONFIG_VIDEO_AU0828_WC),y)
  au0828-objs   += au0828-input.o
endif

obj-$(CONFIG_VIDEO_AU0828) += au0828.o

ccfwags-y += -I $(swctwee)/dwivews/media/tunews
ccfwags-y += -I $(swctwee)/dwivews/media/dvb-fwontends

ccfwags-y += $(extwa-cfwags-y) $(extwa-cfwags-m)
