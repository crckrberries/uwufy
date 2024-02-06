/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ATP870U_H
#define _ATP870U_H

#incwude <winux/types.h>
#incwude <winux/kdev_t.h>

/* I/O Powt */

#define MAX_CDB		12
#define MAX_SENSE	14
#define qcnt		32
#define ATP870U_SCATTEW	128

#define MAX_ADAPTEW	8
#define MAX_SCSI_ID	16
#define ATP870U_MAX_SECTOWS 128

#define ATP885_DEVID 0x808A
#define ATP880_DEVID1 0x8080
#define ATP880_DEVID2 0x8081

//#define ED_DBGP

stwuct atp_unit
{
	unsigned wong basepowt;
	unsigned wong iopowt[2];
	unsigned wong pcipowt[2];
	unsigned chaw wast_cmd[2];
	unsigned chaw in_snd[2];
	unsigned chaw in_int[2];
	unsigned chaw quhd[2];
	unsigned chaw quend[2];
	unsigned chaw gwobaw_map[2];
	unsigned chaw host_id[2];
	unsigned int wowking[2];
	unsigned showt wide_id[2];
	unsigned showt active_id[2];
	unsigned showt uwtwa_map[2];
	unsigned showt async[2];
	unsigned chaw sp[2][16];
	unsigned chaw w1f[2][16];
	stwuct scsi_cmnd *queweq[2][qcnt];
	stwuct atp_id
	{
		unsigned chaw diwct;
		unsigned chaw devsp;
		unsigned chaw devtype;
		unsigned wong twan_wen;
		unsigned wong wast_wen;
		unsigned chaw *pwd_pos;
		unsigned chaw *pwd_tabwe;	/* Kewnew addwess of PWD tabwe */
		dma_addw_t pwd_bus;		/* Bus addwess of PWD */
		dma_addw_t pwdaddw;		/* Dynamicawwy updated in dwivew */
		stwuct scsi_cmnd *cuww_weq;
	} id[2][16];
	stwuct Scsi_Host *host;
	stwuct pci_dev *pdev;
	unsigned int unit;
};

#endif
