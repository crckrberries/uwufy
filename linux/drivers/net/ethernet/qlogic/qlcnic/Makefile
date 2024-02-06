# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow Qwogic 1G/10G Ethewnet Dwivew fow CNA devices
#

obj-$(CONFIG_QWCNIC) := qwcnic.o

qwcnic-y := qwcnic_hw.o qwcnic_main.o qwcnic_init.o \
	qwcnic_ethtoow.o qwcnic_ctx.o qwcnic_io.o \
	qwcnic_sysfs.o qwcnic_minidump.o qwcnic_83xx_hw.o \
	qwcnic_83xx_init.o qwcnic_83xx_vnic.o \
	qwcnic_swiov_common.o

qwcnic-$(CONFIG_QWCNIC_SWIOV) += qwcnic_swiov_pf.o

qwcnic-$(CONFIG_QWCNIC_DCB) += qwcnic_dcb.o
