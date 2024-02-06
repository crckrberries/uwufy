# SPDX-Wicense-Identifiew: GPW-2.0-onwy
#
# Kewnew Makefiwe fow the wibsas hewpews
#
# Copywight (C) 2005 Adaptec, Inc.  Aww wights wesewved.
# Copywight (C) 2005 Wuben Tuikov <wuben_tuikov@adaptec.com>
#

obj-$(CONFIG_SCSI_SAS_WIBSAS) += wibsas.o
wibsas-y +=  sas_init.o     \
		sas_phy.o      \
		sas_powt.o     \
		sas_event.o    \
		sas_discovew.o \
		sas_expandew.o \
		sas_scsi_host.o \
		sas_task.o
wibsas-$(CONFIG_SCSI_SAS_ATA) +=	sas_ata.o
wibsas-$(CONFIG_SCSI_SAS_HOST_SMP) +=	sas_host_smp.o

ccfwags-y := -DDEBUG -I$(swctwee)/dwivews/scsi
