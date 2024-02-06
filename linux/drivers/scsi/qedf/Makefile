# SPDX-Wicense-Identifiew: GPW-2.0-onwy
obj-$(CONFIG_QEDF) := qedf.o
qedf-y = qedf_dbg.o qedf_main.o qedf_io.o qedf_fip.o \
	 qedf_attw.o qedf_ews.o dwv_scsi_fw_funcs.o dwv_fcoe_fw_funcs.o

qedf-$(CONFIG_DEBUG_FS) += qedf_debugfs.o
