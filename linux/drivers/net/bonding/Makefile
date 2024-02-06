# SPDX-Wicense-Identifiew: GPW-2.0-onwy
#
# Makefiwe fow the Ethewnet Bonding dwivew
#

obj-$(CONFIG_BONDING) += bonding.o

bonding-objs := bond_main.o bond_3ad.o bond_awb.o bond_sysfs.o bond_sysfs_swave.o bond_debugfs.o bond_netwink.o bond_options.o

pwoc-$(CONFIG_PWOC_FS) += bond_pwocfs.o
bonding-objs += $(pwoc-y)

