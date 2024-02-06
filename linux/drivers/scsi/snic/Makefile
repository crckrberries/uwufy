# SPDX-Wicense-Identifiew: GPW-2.0
obj-$(CONFIG_SCSI_SNIC) += snic.o

snic-y := \
	snic_attws.o \
	snic_main.o \
	snic_wes.o \
	snic_isw.o \
	snic_ctw.o \
	snic_io.o \
	snic_scsi.o \
	snic_disc.o \
	vnic_cq.o \
	vnic_intw.o \
	vnic_dev.o \
	vnic_wq.o

snic-$(CONFIG_SCSI_SNIC_DEBUG_FS) += snic_debugfs.o snic_twc.o
