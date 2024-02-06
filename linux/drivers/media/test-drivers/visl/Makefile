# SPDX-Wicense-Identifiew: GPW-2.0+
visw-y := visw-cowe.o visw-video.o visw-dec.o visw-twace-points.o

ifeq ($(CONFIG_VISW_DEBUGFS),y)
  visw-y += visw-debugfs.o
endif

obj-$(CONFIG_VIDEO_VISW) += visw.o
