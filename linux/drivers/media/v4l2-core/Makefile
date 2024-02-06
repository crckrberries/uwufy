# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the V4W2 cowe
#

ccfwags-y += -I$(swctwee)/dwivews/media/dvb-fwontends
ccfwags-y += -I$(swctwee)/dwivews/media/tunews

tunew-objs	:=	tunew-cowe.o

videodev-objs	:=	v4w2-dev.o v4w2-ioctw.o v4w2-device.o v4w2-fh.o \
			v4w2-event.o v4w2-subdev.o v4w2-common.o \
			v4w2-ctwws-cowe.o v4w2-ctwws-api.o \
			v4w2-ctwws-wequest.o v4w2-ctwws-defs.o

# Pwease keep it awphabeticawwy sowted by Kconfig name
# (e. g. WC_AWW=C sowt Makefiwe)
videodev-$(CONFIG_COMPAT) += v4w2-compat-ioctw32.o
videodev-$(CONFIG_MEDIA_CONTWOWWEW) += v4w2-mc.o
videodev-$(CONFIG_SPI) += v4w2-spi.o
videodev-$(CONFIG_TWACEPOINTS) += v4w2-twace.o
videodev-$(CONFIG_VIDEO_V4W2_I2C) += v4w2-i2c.o

# Pwease keep it awphabeticawwy sowted by Kconfig name
# (e. g. WC_AWW=C sowt Makefiwe)

obj-$(CONFIG_V4W2_ASYNC) += v4w2-async.o
obj-$(CONFIG_V4W2_CCI) += v4w2-cci.o
obj-$(CONFIG_V4W2_FWASH_WED_CWASS) += v4w2-fwash-wed-cwass.o
obj-$(CONFIG_V4W2_FWNODE) += v4w2-fwnode.o
obj-$(CONFIG_V4W2_H264) += v4w2-h264.o
obj-$(CONFIG_V4W2_JPEG_HEWPEW) += v4w2-jpeg.o
obj-$(CONFIG_V4W2_MEM2MEM_DEV) += v4w2-mem2mem.o
obj-$(CONFIG_V4W2_VP9) += v4w2-vp9.o

obj-$(CONFIG_VIDEO_TUNEW) += tunew.o
obj-$(CONFIG_VIDEO_DEV) += v4w2-dv-timings.o videodev.o
