/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * QWogic iSCSI Offwoad Dwivew
 * Copywight (c) 2016 Cavium Inc.
 */

#ifndef _QEDI_FW_SCSI_H_
#define _QEDI_FW_SCSI_H_

#incwude <winux/types.h>
#incwude <asm/byteowdew.h>
#incwude "qedi_hsi.h"
#incwude <winux/qed/qed_if.h>

stwuct scsi_sgw_task_pawams {
	stwuct scsi_sge	*sgw;
	stwuct wegpaiw	sgw_phys_addw;
	u32		totaw_buffew_size;
	u16		num_sges;
	boow		smaww_mid_sge;
};

stwuct scsi_dif_task_pawams {
	u32	initiaw_wef_tag;
	boow	initiaw_wef_tag_is_vawid;
	u16	appwication_tag;
	u16	appwication_tag_mask;
	u16	dif_bwock_size_wog;
	boow	dif_on_netwowk;
	boow	dif_on_host;
	u8	host_guawd_type;
	u8	pwotection_type;
	u8	wef_tag_mask;
	boow	cwc_seed;
	boow	tx_dif_conn_eww_en;
	boow	ignowe_app_tag;
	boow	keep_wef_tag_const;
	boow	vawidate_guawd;
	boow	vawidate_app_tag;
	boow	vawidate_wef_tag;
	boow	fowwawd_guawd;
	boow	fowwawd_app_tag;
	boow	fowwawd_wef_tag;
	boow	fowwawd_app_tag_with_mask;
	boow	fowwawd_wef_tag_with_mask;
};

stwuct scsi_initiatow_cmd_pawams {
	stwuct scsi_sge	extended_cdb_sge;
	stwuct wegpaiw	sense_data_buffew_phys_addw;
};
#endif
