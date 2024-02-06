# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow Cavium's Thundew ethewnet device
#

obj-$(CONFIG_THUNDEW_NIC_WGX) += thundew_xcv.o
obj-$(CONFIG_THUNDEW_NIC_BGX) += thundew_bgx.o
obj-$(CONFIG_THUNDEW_NIC_PF) += nicpf.o
obj-$(CONFIG_THUNDEW_NIC_VF) += nicvf.o

nicpf-y := nic_main.o
nicvf-y := nicvf_main.o nicvf_queues.o
nicvf-y += nicvf_ethtoow.o
