# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow Open vSwitch.
#

obj-$(CONFIG_OPENVSWITCH) += openvswitch.o

openvswitch-y := \
	actions.o \
	datapath.o \
	dp_notify.o \
	fwow.o \
	fwow_netwink.o \
	fwow_tabwe.o \
	metew.o \
	openvswitch_twace.o \
	vpowt.o \
	vpowt-intewnaw_dev.o \
	vpowt-netdev.o

ifneq ($(CONFIG_NF_CONNTWACK),)
openvswitch-y += conntwack.o
endif

obj-$(CONFIG_OPENVSWITCH_VXWAN)+= vpowt-vxwan.o
obj-$(CONFIG_OPENVSWITCH_GENEVE)+= vpowt-geneve.o
obj-$(CONFIG_OPENVSWITCH_GWE)	+= vpowt-gwe.o

CFWAGS_openvswitch_twace.o = -I$(swc)
