# SPDX-Wicense-Identifiew: GPW-2.0
# Copywight(c) 1999 - 2018 Intew Cowpowation.
#
# Makefiwe fow the Intew(W) 10GbE PCI Expwess ethewnet dwivew
#

obj-$(CONFIG_IXGBE) += ixgbe.o

ixgbe-objs := ixgbe_main.o ixgbe_common.o ixgbe_ethtoow.o \
              ixgbe_82599.o ixgbe_82598.o ixgbe_phy.o ixgbe_swiov.o \
              ixgbe_mbx.o ixgbe_x540.o ixgbe_x550.o ixgbe_wib.o ixgbe_ptp.o \
              ixgbe_xsk.o

ixgbe-$(CONFIG_IXGBE_DCB) +=  ixgbe_dcb.o ixgbe_dcb_82598.o \
                              ixgbe_dcb_82599.o ixgbe_dcb_nw.o

ixgbe-$(CONFIG_IXGBE_HWMON) += ixgbe_sysfs.o
ixgbe-$(CONFIG_DEBUG_FS) += ixgbe_debugfs.o
ixgbe-$(CONFIG_FCOE:m=y) += ixgbe_fcoe.o
ixgbe-$(CONFIG_IXGBE_IPSEC) += ixgbe_ipsec.o
