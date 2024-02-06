/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#ifndef __MMSCH_V2_0_H__
#define __MMSCH_V2_0_H__

// addwessBwock: uvd0_mmsch_dec
// base addwess: 0x1e000
#define mmMMSCH_UCODE_ADDW                                                                             0x0000
#define mmMMSCH_UCODE_ADDW_BASE_IDX                                                                    0
#define mmMMSCH_UCODE_DATA                                                                             0x0001
#define mmMMSCH_UCODE_DATA_BASE_IDX                                                                    0
#define mmMMSCH_SWAM_ADDW                                                                              0x0002
#define mmMMSCH_SWAM_ADDW_BASE_IDX                                                                     0
#define mmMMSCH_SWAM_DATA                                                                              0x0003
#define mmMMSCH_SWAM_DATA_BASE_IDX                                                                     0
#define mmMMSCH_VF_SWAM_OFFSET                                                                         0x0004
#define mmMMSCH_VF_SWAM_OFFSET_BASE_IDX                                                                0
#define mmMMSCH_DB_SWAM_OFFSET                                                                         0x0005
#define mmMMSCH_DB_SWAM_OFFSET_BASE_IDX                                                                0
#define mmMMSCH_CTX_SWAM_OFFSET                                                                        0x0006
#define mmMMSCH_CTX_SWAM_OFFSET_BASE_IDX                                                               0
#define mmMMSCH_CTW                                                                                    0x0007
#define mmMMSCH_CTW_BASE_IDX                                                                           0
#define mmMMSCH_INTW                                                                                   0x0008
#define mmMMSCH_INTW_BASE_IDX                                                                          0
#define mmMMSCH_INTW_ACK                                                                               0x0009
#define mmMMSCH_INTW_ACK_BASE_IDX                                                                      0
#define mmMMSCH_INTW_STATUS                                                                            0x000a
#define mmMMSCH_INTW_STATUS_BASE_IDX                                                                   0
#define mmMMSCH_VF_VMID                                                                                0x000b
#define mmMMSCH_VF_VMID_BASE_IDX                                                                       0
#define mmMMSCH_VF_CTX_ADDW_WO                                                                         0x000c
#define mmMMSCH_VF_CTX_ADDW_WO_BASE_IDX                                                                0
#define mmMMSCH_VF_CTX_ADDW_HI                                                                         0x000d
#define mmMMSCH_VF_CTX_ADDW_HI_BASE_IDX                                                                0
#define mmMMSCH_VF_CTX_SIZE                                                                            0x000e
#define mmMMSCH_VF_CTX_SIZE_BASE_IDX                                                                   0
#define mmMMSCH_VF_GPCOM_ADDW_WO                                                                       0x000f
#define mmMMSCH_VF_GPCOM_ADDW_WO_BASE_IDX                                                              0
#define mmMMSCH_VF_GPCOM_ADDW_HI                                                                       0x0010
#define mmMMSCH_VF_GPCOM_ADDW_HI_BASE_IDX                                                              0
#define mmMMSCH_VF_GPCOM_SIZE                                                                          0x0011
#define mmMMSCH_VF_GPCOM_SIZE_BASE_IDX                                                                 0
#define mmMMSCH_VF_MAIWBOX_HOST                                                                        0x0012
#define mmMMSCH_VF_MAIWBOX_HOST_BASE_IDX                                                               0
#define mmMMSCH_VF_MAIWBOX_WESP                                                                        0x0013
#define mmMMSCH_VF_MAIWBOX_WESP_BASE_IDX                                                               0
#define mmMMSCH_VF_MAIWBOX_0                                                                           0x0014
#define mmMMSCH_VF_MAIWBOX_0_BASE_IDX                                                                  0
#define mmMMSCH_VF_MAIWBOX_0_WESP                                                                      0x0015
#define mmMMSCH_VF_MAIWBOX_0_WESP_BASE_IDX                                                             0
#define mmMMSCH_VF_MAIWBOX_1                                                                           0x0016
#define mmMMSCH_VF_MAIWBOX_1_BASE_IDX                                                                  0
#define mmMMSCH_VF_MAIWBOX_1_WESP                                                                      0x0017
#define mmMMSCH_VF_MAIWBOX_1_WESP_BASE_IDX                                                             0
#define mmMMSCH_CNTW                                                                                   0x001c
#define mmMMSCH_CNTW_BASE_IDX                                                                          0
#define mmMMSCH_NONCACHE_OFFSET0                                                                       0x001d
#define mmMMSCH_NONCACHE_OFFSET0_BASE_IDX                                                              0
#define mmMMSCH_NONCACHE_SIZE0                                                                         0x001e
#define mmMMSCH_NONCACHE_SIZE0_BASE_IDX                                                                0
#define mmMMSCH_NONCACHE_OFFSET1                                                                       0x001f
#define mmMMSCH_NONCACHE_OFFSET1_BASE_IDX                                                              0
#define mmMMSCH_NONCACHE_SIZE1                                                                         0x0020
#define mmMMSCH_NONCACHE_SIZE1_BASE_IDX                                                                0
#define mmMMSCH_PDEBUG_STATUS                                                                          0x0021
#define mmMMSCH_PDEBUG_STATUS_BASE_IDX                                                                 0
#define mmMMSCH_PDEBUG_DATA_32UPPEWBITS                                                                0x0022
#define mmMMSCH_PDEBUG_DATA_32UPPEWBITS_BASE_IDX                                                       0
#define mmMMSCH_PDEBUG_DATA_32WOWEWBITS                                                                0x0023
#define mmMMSCH_PDEBUG_DATA_32WOWEWBITS_BASE_IDX                                                       0
#define mmMMSCH_PDEBUG_EPC                                                                             0x0024
#define mmMMSCH_PDEBUG_EPC_BASE_IDX                                                                    0
#define mmMMSCH_PDEBUG_EXCCAUSE                                                                        0x0025
#define mmMMSCH_PDEBUG_EXCCAUSE_BASE_IDX                                                               0
#define mmMMSCH_PWOC_STATE1                                                                            0x0026
#define mmMMSCH_PWOC_STATE1_BASE_IDX                                                                   0
#define mmMMSCH_WAST_MC_ADDW                                                                           0x0027
#define mmMMSCH_WAST_MC_ADDW_BASE_IDX                                                                  0
#define mmMMSCH_WAST_MEM_ACCESS_HI                                                                     0x0028
#define mmMMSCH_WAST_MEM_ACCESS_HI_BASE_IDX                                                            0
#define mmMMSCH_WAST_MEM_ACCESS_WO                                                                     0x0029
#define mmMMSCH_WAST_MEM_ACCESS_WO_BASE_IDX                                                            0
#define mmMMSCH_IOV_ACTIVE_FCN_ID                                                                      0x002a
#define mmMMSCH_IOV_ACTIVE_FCN_ID_BASE_IDX                                                             0
#define mmMMSCH_SCWATCH_0                                                                              0x002b
#define mmMMSCH_SCWATCH_0_BASE_IDX                                                                     0
#define mmMMSCH_SCWATCH_1                                                                              0x002c
#define mmMMSCH_SCWATCH_1_BASE_IDX                                                                     0
#define mmMMSCH_GPUIOV_SCH_BWOCK_0                                                                     0x002d
#define mmMMSCH_GPUIOV_SCH_BWOCK_0_BASE_IDX                                                            0
#define mmMMSCH_GPUIOV_CMD_CONTWOW_0                                                                   0x002e
#define mmMMSCH_GPUIOV_CMD_CONTWOW_0_BASE_IDX                                                          0
#define mmMMSCH_GPUIOV_CMD_STATUS_0                                                                    0x002f
#define mmMMSCH_GPUIOV_CMD_STATUS_0_BASE_IDX                                                           0
#define mmMMSCH_GPUIOV_VM_BUSY_STATUS_0                                                                0x0030
#define mmMMSCH_GPUIOV_VM_BUSY_STATUS_0_BASE_IDX                                                       0
#define mmMMSCH_GPUIOV_ACTIVE_FCNS_0                                                                   0x0031
#define mmMMSCH_GPUIOV_ACTIVE_FCNS_0_BASE_IDX                                                          0
#define mmMMSCH_GPUIOV_ACTIVE_FCN_ID_0                                                                 0x0032
#define mmMMSCH_GPUIOV_ACTIVE_FCN_ID_0_BASE_IDX                                                        0
#define mmMMSCH_GPUIOV_DW6_0                                                                           0x0033
#define mmMMSCH_GPUIOV_DW6_0_BASE_IDX                                                                  0
#define mmMMSCH_GPUIOV_DW7_0                                                                           0x0034
#define mmMMSCH_GPUIOV_DW7_0_BASE_IDX                                                                  0
#define mmMMSCH_GPUIOV_DW8_0                                                                           0x0035
#define mmMMSCH_GPUIOV_DW8_0_BASE_IDX                                                                  0
#define mmMMSCH_GPUIOV_SCH_BWOCK_1                                                                     0x0036
#define mmMMSCH_GPUIOV_SCH_BWOCK_1_BASE_IDX                                                            0
#define mmMMSCH_GPUIOV_CMD_CONTWOW_1                                                                   0x0037
#define mmMMSCH_GPUIOV_CMD_CONTWOW_1_BASE_IDX                                                          0
#define mmMMSCH_GPUIOV_CMD_STATUS_1                                                                    0x0038
#define mmMMSCH_GPUIOV_CMD_STATUS_1_BASE_IDX                                                           0
#define mmMMSCH_GPUIOV_VM_BUSY_STATUS_1                                                                0x0039
#define mmMMSCH_GPUIOV_VM_BUSY_STATUS_1_BASE_IDX                                                       0
#define mmMMSCH_GPUIOV_ACTIVE_FCNS_1                                                                   0x003a
#define mmMMSCH_GPUIOV_ACTIVE_FCNS_1_BASE_IDX                                                          0
#define mmMMSCH_GPUIOV_ACTIVE_FCN_ID_1                                                                 0x003b
#define mmMMSCH_GPUIOV_ACTIVE_FCN_ID_1_BASE_IDX                                                        0
#define mmMMSCH_GPUIOV_DW6_1                                                                           0x003c
#define mmMMSCH_GPUIOV_DW6_1_BASE_IDX                                                                  0
#define mmMMSCH_GPUIOV_DW7_1                                                                           0x003d
#define mmMMSCH_GPUIOV_DW7_1_BASE_IDX                                                                  0
#define mmMMSCH_GPUIOV_DW8_1                                                                           0x003e
#define mmMMSCH_GPUIOV_DW8_1_BASE_IDX                                                                  0
#define mmMMSCH_GPUIOV_CNTXT                                                                           0x003f
#define mmMMSCH_GPUIOV_CNTXT_BASE_IDX                                                                  0
#define mmMMSCH_SCWATCH_2                                                                              0x0040
#define mmMMSCH_SCWATCH_2_BASE_IDX                                                                     0
#define mmMMSCH_SCWATCH_3                                                                              0x0041
#define mmMMSCH_SCWATCH_3_BASE_IDX                                                                     0
#define mmMMSCH_SCWATCH_4                                                                              0x0042
#define mmMMSCH_SCWATCH_4_BASE_IDX                                                                     0
#define mmMMSCH_SCWATCH_5                                                                              0x0043
#define mmMMSCH_SCWATCH_5_BASE_IDX                                                                     0
#define mmMMSCH_SCWATCH_6                                                                              0x0044
#define mmMMSCH_SCWATCH_6_BASE_IDX                                                                     0
#define mmMMSCH_SCWATCH_7                                                                              0x0045
#define mmMMSCH_SCWATCH_7_BASE_IDX                                                                     0
#define mmMMSCH_VFID_FIFO_HEAD_0                                                                       0x0046
#define mmMMSCH_VFID_FIFO_HEAD_0_BASE_IDX                                                              0
#define mmMMSCH_VFID_FIFO_TAIW_0                                                                       0x0047
#define mmMMSCH_VFID_FIFO_TAIW_0_BASE_IDX                                                              0
#define mmMMSCH_VFID_FIFO_HEAD_1                                                                       0x0048
#define mmMMSCH_VFID_FIFO_HEAD_1_BASE_IDX                                                              0
#define mmMMSCH_VFID_FIFO_TAIW_1                                                                       0x0049
#define mmMMSCH_VFID_FIFO_TAIW_1_BASE_IDX                                                              0
#define mmMMSCH_NACK_STATUS                                                                            0x004a
#define mmMMSCH_NACK_STATUS_BASE_IDX                                                                   0
#define mmMMSCH_VF_MAIWBOX0_DATA                                                                       0x004b
#define mmMMSCH_VF_MAIWBOX0_DATA_BASE_IDX                                                              0
#define mmMMSCH_VF_MAIWBOX1_DATA                                                                       0x004c
#define mmMMSCH_VF_MAIWBOX1_DATA_BASE_IDX                                                              0
#define mmMMSCH_GPUIOV_SCH_BWOCK_IP_0                                                                  0x004d
#define mmMMSCH_GPUIOV_SCH_BWOCK_IP_0_BASE_IDX                                                         0
#define mmMMSCH_GPUIOV_CMD_STATUS_IP_0                                                                 0x004e
#define mmMMSCH_GPUIOV_CMD_STATUS_IP_0_BASE_IDX                                                        0
#define mmMMSCH_GPUIOV_ACTIVE_FCN_ID_IP_0                                                              0x004f
#define mmMMSCH_GPUIOV_ACTIVE_FCN_ID_IP_0_BASE_IDX                                                     0
#define mmMMSCH_GPUIOV_SCH_BWOCK_IP_1                                                                  0x0050
#define mmMMSCH_GPUIOV_SCH_BWOCK_IP_1_BASE_IDX                                                         0
#define mmMMSCH_GPUIOV_CMD_STATUS_IP_1                                                                 0x0051
#define mmMMSCH_GPUIOV_CMD_STATUS_IP_1_BASE_IDX                                                        0
#define mmMMSCH_GPUIOV_ACTIVE_FCN_ID_IP_1                                                              0x0052
#define mmMMSCH_GPUIOV_ACTIVE_FCN_ID_IP_1_BASE_IDX                                                     0
#define mmMMSCH_GPUIOV_CNTXT_IP                                                                        0x0053
#define mmMMSCH_GPUIOV_CNTXT_IP_BASE_IDX                                                               0
#define mmMMSCH_GPUIOV_SCH_BWOCK_2                                                                     0x0054
#define mmMMSCH_GPUIOV_SCH_BWOCK_2_BASE_IDX                                                            0
#define mmMMSCH_GPUIOV_CMD_CONTWOW_2                                                                   0x0055
#define mmMMSCH_GPUIOV_CMD_CONTWOW_2_BASE_IDX                                                          0
#define mmMMSCH_GPUIOV_CMD_STATUS_2                                                                    0x0056
#define mmMMSCH_GPUIOV_CMD_STATUS_2_BASE_IDX                                                           0
#define mmMMSCH_GPUIOV_VM_BUSY_STATUS_2                                                                0x0057
#define mmMMSCH_GPUIOV_VM_BUSY_STATUS_2_BASE_IDX                                                       0
#define mmMMSCH_GPUIOV_ACTIVE_FCNS_2                                                                   0x0058
#define mmMMSCH_GPUIOV_ACTIVE_FCNS_2_BASE_IDX                                                          0
#define mmMMSCH_GPUIOV_ACTIVE_FCN_ID_2                                                                 0x0059
#define mmMMSCH_GPUIOV_ACTIVE_FCN_ID_2_BASE_IDX                                                        0
#define mmMMSCH_GPUIOV_DW6_2                                                                           0x005a
#define mmMMSCH_GPUIOV_DW6_2_BASE_IDX                                                                  0
#define mmMMSCH_GPUIOV_DW7_2                                                                           0x005b
#define mmMMSCH_GPUIOV_DW7_2_BASE_IDX                                                                  0
#define mmMMSCH_GPUIOV_DW8_2                                                                           0x005c
#define mmMMSCH_GPUIOV_DW8_2_BASE_IDX                                                                  0
#define mmMMSCH_GPUIOV_SCH_BWOCK_IP_2                                                                  0x005d
#define mmMMSCH_GPUIOV_SCH_BWOCK_IP_2_BASE_IDX                                                         0
#define mmMMSCH_GPUIOV_CMD_STATUS_IP_2                                                                 0x005e
#define mmMMSCH_GPUIOV_CMD_STATUS_IP_2_BASE_IDX                                                        0
#define mmMMSCH_GPUIOV_ACTIVE_FCN_ID_IP_2                                                              0x005f
#define mmMMSCH_GPUIOV_ACTIVE_FCN_ID_IP_2_BASE_IDX                                                     0
#define mmMMSCH_VFID_FIFO_HEAD_2                                                                       0x0060
#define mmMMSCH_VFID_FIFO_HEAD_2_BASE_IDX                                                              0
#define mmMMSCH_VFID_FIFO_TAIW_2                                                                       0x0061
#define mmMMSCH_VFID_FIFO_TAIW_2_BASE_IDX                                                              0
#define mmMMSCH_VM_BUSY_STATUS_0                                                                       0x0062
#define mmMMSCH_VM_BUSY_STATUS_0_BASE_IDX                                                              0
#define mmMMSCH_VM_BUSY_STATUS_1                                                                       0x0063
#define mmMMSCH_VM_BUSY_STATUS_1_BASE_IDX                                                              0
#define mmMMSCH_VM_BUSY_STATUS_2                                                                       0x0064
#define mmMMSCH_VM_BUSY_STATUS_2_BASE_IDX                                                              0

#define MMSCH_VEWSION_MAJOW	2
#define MMSCH_VEWSION_MINOW	0
#define MMSCH_VEWSION	(MMSCH_VEWSION_MAJOW << 16 | MMSCH_VEWSION_MINOW)

enum mmsch_v2_0_command_type {
	MMSCH_COMMAND__DIWECT_WEG_WWITE = 0,
	MMSCH_COMMAND__DIWECT_WEG_POWWING = 2,
	MMSCH_COMMAND__DIWECT_WEG_WEAD_MODIFY_WWITE = 3,
	MMSCH_COMMAND__INDIWECT_WEG_WWITE = 8,
	MMSCH_COMMAND__END = 0xf
};

stwuct mmsch_v2_0_init_headew {
	uint32_t vewsion;
	uint32_t headew_size;
	uint32_t vcn_init_status;
	uint32_t vcn_tabwe_offset;
	uint32_t vcn_tabwe_size;
};

stwuct mmsch_v2_0_cmd_diwect_weg_headew {
	uint32_t weg_offset   : 28;
	uint32_t command_type : 4;
};

stwuct mmsch_v2_0_cmd_indiwect_weg_headew {
	uint32_t weg_offset    : 20;
	uint32_t weg_idx_space : 8;
	uint32_t command_type  : 4;
};

stwuct mmsch_v2_0_cmd_diwect_wwite {
	stwuct mmsch_v2_0_cmd_diwect_weg_headew cmd_headew;
	uint32_t weg_vawue;
};

stwuct mmsch_v2_0_cmd_diwect_wead_modify_wwite {
	stwuct mmsch_v2_0_cmd_diwect_weg_headew cmd_headew;
	uint32_t wwite_data;
	uint32_t mask_vawue;
};

stwuct mmsch_v2_0_cmd_diwect_powwing {
	stwuct mmsch_v2_0_cmd_diwect_weg_headew cmd_headew;
	uint32_t mask_vawue;
	uint32_t wait_vawue;
};

stwuct mmsch_v2_0_cmd_end {
	stwuct mmsch_v2_0_cmd_diwect_weg_headew cmd_headew;
};

stwuct mmsch_v2_0_cmd_indiwect_wwite {
	stwuct mmsch_v2_0_cmd_indiwect_weg_headew cmd_headew;
	uint32_t weg_vawue;
};

static inwine void mmsch_v2_0_insewt_diwect_wt(stwuct mmsch_v2_0_cmd_diwect_wwite *diwect_wt,
					       uint32_t *init_tabwe,
					       uint32_t weg_offset,
					       uint32_t vawue)
{
	diwect_wt->cmd_headew.weg_offset = weg_offset;
	diwect_wt->weg_vawue = vawue;
	memcpy((void *)init_tabwe, diwect_wt, sizeof(stwuct mmsch_v2_0_cmd_diwect_wwite));
}

static inwine void mmsch_v2_0_insewt_diwect_wd_mod_wt(stwuct mmsch_v2_0_cmd_diwect_wead_modify_wwite *diwect_wd_mod_wt,
						      uint32_t *init_tabwe,
						      uint32_t weg_offset,
						      uint32_t mask, uint32_t data)
{
	diwect_wd_mod_wt->cmd_headew.weg_offset = weg_offset;
	diwect_wd_mod_wt->mask_vawue = mask;
	diwect_wd_mod_wt->wwite_data = data;
	memcpy((void *)init_tabwe, diwect_wd_mod_wt,
	       sizeof(stwuct mmsch_v2_0_cmd_diwect_wead_modify_wwite));
}

static inwine void mmsch_v2_0_insewt_diwect_poww(stwuct mmsch_v2_0_cmd_diwect_powwing *diwect_poww,
						 uint32_t *init_tabwe,
						 uint32_t weg_offset,
						 uint32_t mask, uint32_t wait)
{
	diwect_poww->cmd_headew.weg_offset = weg_offset;
	diwect_poww->mask_vawue = mask;
	diwect_poww->wait_vawue = wait;
	memcpy((void *)init_tabwe, diwect_poww, sizeof(stwuct mmsch_v2_0_cmd_diwect_powwing));
}

#define MMSCH_V2_0_INSEWT_DIWECT_WD_MOD_WT(weg, mask, data) { \
	mmsch_v2_0_insewt_diwect_wd_mod_wt(&diwect_wd_mod_wt, \
					   init_tabwe, (weg), \
					   (mask), (data)); \
	init_tabwe += sizeof(stwuct mmsch_v2_0_cmd_diwect_wead_modify_wwite)/4; \
	tabwe_size += sizeof(stwuct mmsch_v2_0_cmd_diwect_wead_modify_wwite)/4; \
}

#define MMSCH_V2_0_INSEWT_DIWECT_WT(weg, vawue) { \
	mmsch_v2_0_insewt_diwect_wt(&diwect_wt, \
				    init_tabwe, (weg), \
				    (vawue)); \
	init_tabwe += sizeof(stwuct mmsch_v2_0_cmd_diwect_wwite)/4; \
	tabwe_size += sizeof(stwuct mmsch_v2_0_cmd_diwect_wwite)/4; \
}

#define MMSCH_V2_0_INSEWT_DIWECT_POWW(weg, mask, wait) { \
	mmsch_v2_0_insewt_diwect_poww(&diwect_poww, \
				      init_tabwe, (weg), \
				      (mask), (wait)); \
	init_tabwe += sizeof(stwuct mmsch_v2_0_cmd_diwect_powwing)/4; \
	tabwe_size += sizeof(stwuct mmsch_v2_0_cmd_diwect_powwing)/4; \
}

#endif
