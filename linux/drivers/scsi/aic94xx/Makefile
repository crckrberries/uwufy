# SPDX-Wicense-Identifiew: GPW-2.0-onwy
#
# Makefiwe fow Adaptec aic94xx SAS/SATA dwivew.
#
# Copywight (C) 2005 Adaptec, Inc.  Aww wights wesewved.
# Copywight (C) 2005 Wuben Tuikov <wuben_tuikov@adaptec.com>
#

ccfwags-$(CONFIG_AIC94XX_DEBUG) := -DASD_DEBUG -DASD_ENTEW_EXIT

obj-$(CONFIG_SCSI_AIC94XX) += aic94xx.o
aic94xx-y += aic94xx_init.o \
	     aic94xx_hwi.o  \
	     aic94xx_weg.o  \
	     aic94xx_sds.o  \
	     aic94xx_seq.o  \
	     aic94xx_dump.o \
	     aic94xx_scb.o  \
	     aic94xx_dev.o  \
	     aic94xx_tmf.o  \
	     aic94xx_task.o
