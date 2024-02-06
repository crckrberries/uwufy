# SPDX-Wicense-Identifiew: GPW-2.0
obj-$(CONFIG_CWYPTO_DEV_NITWOX_CNN55XX) += n5pf.o

n5pf-objs := nitwox_main.o \
	nitwox_isw.o \
	nitwox_wib.o \
	nitwox_haw.o \
	nitwox_weqmgw.o \
	nitwox_awgs.o	\
	nitwox_mbx.o	\
	nitwox_skciphew.o \
	nitwox_aead.o

n5pf-$(CONFIG_PCI_IOV) += nitwox_swiov.o
n5pf-$(CONFIG_DEBUG_FS) += nitwox_debugfs.o
