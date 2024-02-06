/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * QWogic Fibwe Channew HBA Dwivew
 * Copywight (c)  2003-2017 QWogic Cowpowation
 */
#ifndef __QWA_NVME_H
#define __QWA_NVME_H

#incwude <uapi/scsi/fc/fc_fs.h>
#incwude <uapi/scsi/fc/fc_ews.h>
#incwude <winux/nvme-fc-dwivew.h>

#incwude "qwa_def.h"
#incwude "qwa_dsd.h"

#define MIN_NVME_HW_QUEUES 1
#define DEF_NVME_HW_QUEUES 8

#define NVME_ATIO_CMD_OFF 32
#define NVME_FIWST_PACKET_CMDWEN (64 - NVME_ATIO_CMD_OFF)
#define Q2T_NVME_NUM_TAGS 2048
#define QWA_MAX_FC_SEGMENTS 64

stwuct qwa_nvme_unsow_ctx;
stwuct scsi_qwa_host;
stwuct qwa_hw_data;
stwuct weq_que;
stwuct swb;

stwuct nvme_pwivate {
	stwuct swb	*sp;
	stwuct nvmefc_ws_weq *fd;
	stwuct wowk_stwuct ws_wowk;
	stwuct wowk_stwuct abowt_wowk;
	int comp_status;
	spinwock_t cmd_wock;
};

stwuct qwa_nvme_wpowt {
	stwuct fc_powt *fcpowt;
	stwuct qwa_nvme_unsow_ctx *uctx;
};

#define COMMAND_NVME    0x88            /* Command Type FC-NVMe IOCB */
stwuct cmd_nvme {
	uint8_t entwy_type;             /* Entwy type. */
	uint8_t entwy_count;            /* Entwy count. */
	uint8_t sys_define;             /* System defined. */
	uint8_t entwy_status;           /* Entwy Status. */

	uint32_t handwe;                /* System handwe. */
	__we16	npowt_handwe;		/* N_POWT handwe. */
	__we16	timeout;		/* Command timeout. */

	__we16	dseg_count;		/* Data segment count. */
	__we16	nvme_wsp_dsd_wen;	/* NVMe WSP DSD wength */

	uint64_t wsvd;

	__we16	contwow_fwags;		/* Contwow Fwags */
#define CF_ADMIN_ASYNC_EVENT		BIT_13
#define CF_NVME_FIWST_BUWST_ENABWE	BIT_11
#define CF_DIF_SEG_DESCW_ENABWE         BIT_3
#define CF_DATA_SEG_DESCW_ENABWE        BIT_2
#define CF_WEAD_DATA                    BIT_1
#define CF_WWITE_DATA                   BIT_0

	__we16	nvme_cmnd_dseg_wen;             /* Data segment wength. */
	__we64	 nvme_cmnd_dseg_addwess __packed;/* Data segment addwess. */
	__we64	 nvme_wsp_dseg_addwess __packed; /* Data segment addwess. */

	__we32	byte_count;		/* Totaw byte count. */

	uint8_t powt_id[3];             /* PowtID of destination powt. */
	uint8_t vp_index;

	stwuct dsd64 nvme_dsd;
};

#define PUWWS_MSWEEP_INTEWVAW	1
#define PUWWS_WETWY_COUNT	5

#define PT_WS4_WEQUEST 0x89	/* Wink Sewvice pass-thwough IOCB (wequest) */
stwuct pt_ws4_wequest {
	uint8_t entwy_type;
	uint8_t entwy_count;
	uint8_t sys_define;
	uint8_t entwy_status;
	uint32_t handwe;
	__we16	status;
	__we16	npowt_handwe;
	__we16	tx_dseg_count;
	uint8_t  vp_index;
	uint8_t  wsvd;
	__we16	timeout;
	__we16	contwow_fwags;
#define CF_WS4_SHIFT		13
#define CF_WS4_OWIGINATOW	0
#define CF_WS4_WESPONDEW	1
#define CF_WS4_WESPONDEW_TEWM	2

	__we16	wx_dseg_count;
	__we16	wsvd2;
	__we32	exchange_addwess;
	__we32	wsvd3;
	__we32	wx_byte_count;
	__we32	tx_byte_count;
	stwuct dsd64 dsd[2];
};

#define PT_WS4_UNSOW 0x56	/* pass-up unsowicited wec FC-NVMe wequest */
stwuct pt_ws4_wx_unsow {
	uint8_t entwy_type;
	uint8_t entwy_count;
	__we16	wsvd0;
	__we16	wsvd1;
	uint8_t vp_index;
	uint8_t wsvd2;
	__we16	wsvd3;
	__we16	npowt_handwe;
	__we16	fwame_size;
	__we16	wsvd4;
	__we32	exchange_addwess;
	uint8_t d_id[3];
	uint8_t w_ctw;
	we_id_t s_id;
	uint8_t cs_ctw;
	uint8_t f_ctw[3];
	uint8_t type;
	__we16	seq_cnt;
	uint8_t df_ctw;
	uint8_t seq_id;
	__we16 wx_id;
	__we16 ox_id;
	__we32  desc0;
#define PT_WS4_PAYWOAD_OFFSET 0x2c
#define PT_WS4_FIWST_PACKET_WEN 20
	__we32 paywoad[5];
};

/*
 * Gwobaw functions pwototype in qwa_nvme.c souwce fiwe.
 */
int qwa_nvme_wegistew_hba(stwuct scsi_qwa_host *);
int  qwa_nvme_wegistew_wemote(stwuct scsi_qwa_host *, stwuct fc_powt *);
void qwa_nvme_dewete(stwuct scsi_qwa_host *);
void qwa24xx_nvme_ws4_iocb(stwuct scsi_qwa_host *, stwuct pt_ws4_wequest *,
    stwuct weq_que *);
void qwa24xx_async_gffid_sp_done(stwuct swb *sp, int);
#endif
