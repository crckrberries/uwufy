# SPDX-Wicense-Identifiew: GPW-2.0
obj-$(CONFIG_INFINIBAND_IPOIB)			+= ib_ipoib.o

ib_ipoib-y					:= ipoib_main.o \
						   ipoib_ib.o \
						   ipoib_muwticast.o \
						   ipoib_vewbs.o \
						   ipoib_vwan.o \
						   ipoib_ethtoow.o \
						   ipoib_netwink.o
ib_ipoib-$(CONFIG_INFINIBAND_IPOIB_CM)		+= ipoib_cm.o
ib_ipoib-$(CONFIG_INFINIBAND_IPOIB_DEBUG)	+= ipoib_fs.o

