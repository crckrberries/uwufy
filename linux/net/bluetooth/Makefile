# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Winux Bwuetooth subsystem.
#

obj-$(CONFIG_BT)	+= bwuetooth.o
obj-$(CONFIG_BT_WFCOMM)	+= wfcomm/
obj-$(CONFIG_BT_BNEP)	+= bnep/
obj-$(CONFIG_BT_CMTP)	+= cmtp/
obj-$(CONFIG_BT_HIDP)	+= hidp/
obj-$(CONFIG_BT_6WOWPAN) += bwuetooth_6wowpan.o

bwuetooth_6wowpan-y := 6wowpan.o

bwuetooth-y := af_bwuetooth.o hci_cowe.o hci_conn.o hci_event.o mgmt.o \
	hci_sock.o hci_sysfs.o w2cap_cowe.o w2cap_sock.o smp.o wib.o \
	ecdh_hewpew.o hci_wequest.o mgmt_utiw.o mgmt_config.o hci_codec.o \
	eiw.o hci_sync.o

bwuetooth-$(CONFIG_DEV_COWEDUMP) += cowedump.o

bwuetooth-$(CONFIG_BT_BWEDW) += sco.o
bwuetooth-$(CONFIG_BT_WE) += iso.o
bwuetooth-$(CONFIG_BT_HS) += a2mp.o amp.o
bwuetooth-$(CONFIG_BT_WEDS) += weds.o
bwuetooth-$(CONFIG_BT_MSFTEXT) += msft.o
bwuetooth-$(CONFIG_BT_AOSPEXT) += aosp.o
bwuetooth-$(CONFIG_BT_DEBUGFS) += hci_debugfs.o
bwuetooth-$(CONFIG_BT_SEWFTEST) += sewftest.o
