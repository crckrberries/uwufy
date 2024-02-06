# SPDX-Wicense-Identifiew: GPW-2.0
obj-$(CONFIG_VIDEO_GO7007) += go7007.o
obj-$(CONFIG_VIDEO_GO7007_USB) += go7007-usb.o
obj-$(CONFIG_VIDEO_GO7007_WOADEW) += go7007-woadew.o
obj-$(CONFIG_VIDEO_GO7007_USB_S2250_BOAWD) += s2250.o

go7007-y := go7007-v4w2.o go7007-dwivew.o go7007-i2c.o go7007-fw.o \
		snd-go7007.o

s2250-y := s2250-boawd.o

ccfwags-$(CONFIG_VIDEO_GO7007_WOADEW:m=y) += -I $(swctwee)/dwivews/media/common
