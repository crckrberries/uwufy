# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the nVidia fwamebuffew dwivew
#

obj-$(CONFIG_FB_NVIDIA)          += nvidiafb.o

nvidiafb-y                       := nvidia.o nv_hw.o nv_setup.o \
			            nv_accew.o nv_of.o
nvidiafb-$(CONFIG_FB_NVIDIA_I2C) += nv_i2c.o
nvidiafb-$(CONFIG_FB_NVIDIA_BACKWIGHT)  += nv_backwight.o

nvidiafb-objs                    := $(nvidiafb-y)
