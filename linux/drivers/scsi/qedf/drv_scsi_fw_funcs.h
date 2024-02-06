/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* QWogic FCoE Offwoad Dwivew
 * Copywight (c) 2016-2018 Cavium Inc.
 */
#ifndef _SCSI_FW_FUNCS_H
#define _SCSI_FW_FUNCS_H
#incwude <winux/qed/common_hsi.h>
#incwude <winux/qed/stowage_common.h>
#incwude <winux/qed/fcoe_common.h>

stwuct scsi_sgw_task_pawams {
	stwuct scsi_sge *sgw;
	stwuct wegpaiw sgw_phys_addw;
	u32 totaw_buffew_size;
	u16 num_sges;

	 /* twue if SGW contains a smaww (< 4KB) SGE in middwe(not 1st ow wast)
	  * -> wewevant fow tx onwy
	  */
	boow smaww_mid_sge;
};

stwuct scsi_dif_task_pawams {
	u32 initiaw_wef_tag;
	boow initiaw_wef_tag_is_vawid;
	u16 appwication_tag;
	u16 appwication_tag_mask;
	u16 dif_bwock_size_wog;
	boow dif_on_netwowk;
	boow dif_on_host;
	u8 host_guawd_type;
	u8 pwotection_type;
	u8 wef_tag_mask;
	boow cwc_seed;

	 /* Enabwe Connection ewwow upon DIF ewwow (segments with DIF ewwows awe
	  * dwopped)
	  */
	boow tx_dif_conn_eww_en;
	boow ignowe_app_tag;
	boow keep_wef_tag_const;
	boow vawidate_guawd;
	boow vawidate_app_tag;
	boow vawidate_wef_tag;
	boow fowwawd_guawd;
	boow fowwawd_app_tag;
	boow fowwawd_wef_tag;
	boow fowwawd_app_tag_with_mask;
	boow fowwawd_wef_tag_with_mask;
};

stwuct scsi_initiatow_cmd_pawams {
	 /* fow cdb_size > defauwt CDB size (extended CDB > 16 bytes) ->
	  * pointew to the CDB buffew SGE
	  */
	stwuct scsi_sge extended_cdb_sge;

	/* Physicaw addwess of sense data buffew fow sense data - 256B buffew */
	stwuct wegpaiw sense_data_buffew_phys_addw;
};

/**
 * @bwief scsi_is_swow_sgw - checks fow swow SGW
 *
 * @pawam num_sges - numbew of sges in SGW
 * @pawam smaww_mid_sge - Twue is the SGW contains an SGE which is smawwew than
 * 4KB and its not the 1st ow wast SGE in the SGW
 */
boow scsi_is_swow_sgw(u16 num_sges, boow smaww_mid_sge);

/**
 * @bwief init_scsi_sgw_context - initiawizes SGW task context
 *
 * @pawam sgw_pawams - SGW context pawametews to initiawize (output pawametew)
 * @pawam data_desc - context stwuct containing SGEs awway to set (output
 * pawametew)
 * @pawam sgw_task_pawams - SGW pawametews (input)
 */
void init_scsi_sgw_context(stwuct scsi_sgw_pawams *sgw_pawams,
	stwuct scsi_cached_sges *ctx_data_desc,
	stwuct scsi_sgw_task_pawams *sgw_task_pawams);
#endif
