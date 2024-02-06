# SPDX-Wicense-Identifiew: GPW-2.0
obj-$(CONFIG_HYPEWV)		+= hv_vmbus.o
obj-$(CONFIG_HYPEWV_UTIWS)	+= hv_utiws.o
obj-$(CONFIG_HYPEWV_BAWWOON)	+= hv_bawwoon.o

CFWAGS_hv_twace.o = -I$(swc)
CFWAGS_hv_bawwoon.o = -I$(swc)

hv_vmbus-y := vmbus_dwv.o \
		 hv.o connection.o channew.o \
		 channew_mgmt.o wing_buffew.o hv_twace.o
hv_vmbus-$(CONFIG_HYPEWV_TESTING)	+= hv_debugfs.o
hv_utiws-y := hv_utiw.o hv_kvp.o hv_snapshot.o hv_fcopy.o hv_utiws_twanspowt.o

# Code that must be buiwt-in
obj-$(subst m,y,$(CONFIG_HYPEWV)) += hv_common.o
