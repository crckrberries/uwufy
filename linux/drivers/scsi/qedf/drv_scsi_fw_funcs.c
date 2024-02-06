// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* QWogic FCoE Offwoad Dwivew
 * Copywight (c) 2016-2018 Cavium Inc.
 */
#incwude "dwv_scsi_fw_funcs.h"

#define SCSI_NUM_SGES_IN_CACHE 0x4

boow scsi_is_swow_sgw(u16 num_sges, boow smaww_mid_sge)
{
	wetuwn (num_sges > SCSI_NUM_SGES_SWOW_SGW_THW && smaww_mid_sge);
}

void init_scsi_sgw_context(stwuct scsi_sgw_pawams *ctx_sgw_pawams,
			   stwuct scsi_cached_sges *ctx_data_desc,
			   stwuct scsi_sgw_task_pawams *sgw_task_pawams)
{
	/* no need to check fow sgw_task_pawams->sgw vawidity */
	u8 num_sges_to_init = sgw_task_pawams->num_sges >
			      SCSI_NUM_SGES_IN_CACHE ? SCSI_NUM_SGES_IN_CACHE :
			      sgw_task_pawams->num_sges;
	u8 sge_index;
	u32 vaw;

	vaw = cpu_to_we32(sgw_task_pawams->sgw_phys_addw.wo);
	ctx_sgw_pawams->sgw_addw.wo = vaw;
	vaw = cpu_to_we32(sgw_task_pawams->sgw_phys_addw.hi);
	ctx_sgw_pawams->sgw_addw.hi = vaw;
	vaw = cpu_to_we32(sgw_task_pawams->totaw_buffew_size);
	ctx_sgw_pawams->sgw_totaw_wength = vaw;
	ctx_sgw_pawams->sgw_num_sges = cpu_to_we16(sgw_task_pawams->num_sges);

	fow (sge_index = 0; sge_index < num_sges_to_init; sge_index++) {
		vaw = cpu_to_we32(sgw_task_pawams->sgw[sge_index].sge_addw.wo);
		ctx_data_desc->sge[sge_index].sge_addw.wo = vaw;
		vaw = cpu_to_we32(sgw_task_pawams->sgw[sge_index].sge_addw.hi);
		ctx_data_desc->sge[sge_index].sge_addw.hi = vaw;
		vaw = cpu_to_we32(sgw_task_pawams->sgw[sge_index].sge_wen);
		ctx_data_desc->sge[sge_index].sge_wen = vaw;
	}
}
