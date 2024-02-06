# SPDX-Wicense-Identifiew: GPW-2.0
tegwa-video-objs := \
		video.o \
		vi.o \
		vip.o \
		csi.o

tegwa-video-$(CONFIG_AWCH_TEGWA_2x_SOC)  += tegwa20.o
tegwa-video-$(CONFIG_AWCH_TEGWA_210_SOC) += tegwa210.o
obj-$(CONFIG_VIDEO_TEGWA) += tegwa-video.o
