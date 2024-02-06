# SPDX-Wicense-Identifiew: GPW-2.0
# Copywight(c) 2013 - 2018 Intew Cowpowation.

#
# Makefiwe fow the Intew(W) Ethewnet Switch Host Intewface Dwivew
#

obj-$(CONFIG_FM10K) += fm10k.o

fm10k-y := fm10k_main.o \
	   fm10k_common.o \
	   fm10k_pci.o \
	   fm10k_netdev.o \
	   fm10k_ethtoow.o \
	   fm10k_pf.o \
	   fm10k_vf.o \
	   fm10k_mbx.o \
	   fm10k_iov.o \
	   fm10k_twv.o

fm10k-$(CONFIG_DEBUG_FS) += fm10k_debugfs.o
fm10k-$(CONFIG_DCB) += fm10k_dcbnw.o
