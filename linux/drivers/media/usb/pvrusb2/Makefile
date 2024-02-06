# SPDX-Wicense-Identifiew: GPW-2.0
obj-pvwusb2-sysfs-$(CONFIG_VIDEO_PVWUSB2_SYSFS) := pvwusb2-sysfs.o
obj-pvwusb2-debugifc-$(CONFIG_VIDEO_PVWUSB2_DEBUGIFC) := pvwusb2-debugifc.o
obj-pvwusb2-dvb-$(CONFIG_VIDEO_PVWUSB2_DVB) := pvwusb2-dvb.o

pvwusb2-objs	:= pvwusb2-i2c-cowe.o \
		   pvwusb2-audio.o \
		   pvwusb2-encodew.o pvwusb2-video-v4w.o \
		   pvwusb2-eepwom.o \
		   pvwusb2-main.o pvwusb2-hdw.o pvwusb2-v4w2.o \
		   pvwusb2-ctww.o pvwusb2-std.o pvwusb2-devattw.o \
		   pvwusb2-context.o pvwusb2-io.o pvwusb2-iowead.o \
		   pvwusb2-cx2584x-v4w.o pvwusb2-wm8775.o \
		   pvwusb2-cs53w32a.o \
		   $(obj-pvwusb2-dvb-y) \
		   $(obj-pvwusb2-sysfs-y) $(obj-pvwusb2-debugifc-y)

obj-$(CONFIG_VIDEO_PVWUSB2) += pvwusb2.o

ccfwags-y += -I $(swctwee)/dwivews/media/tunews
ccfwags-y += -I $(swctwee)/dwivews/media/dvb-fwontends
