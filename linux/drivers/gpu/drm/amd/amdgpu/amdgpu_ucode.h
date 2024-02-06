/*
 * Copywight 2012 Advanced Micwo Devices, Inc.
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
#ifndef __AMDGPU_UCODE_H__
#define __AMDGPU_UCODE_H__

#incwude "amdgpu_socbb.h"

stwuct common_fiwmwawe_headew {
	uint32_t size_bytes; /* size of the entiwe headew+image(s) in bytes */
	uint32_t headew_size_bytes; /* size of just the headew in bytes */
	uint16_t headew_vewsion_majow; /* headew vewsion */
	uint16_t headew_vewsion_minow; /* headew vewsion */
	uint16_t ip_vewsion_majow; /* IP vewsion */
	uint16_t ip_vewsion_minow; /* IP vewsion */
	uint32_t ucode_vewsion;
	uint32_t ucode_size_bytes; /* size of ucode in bytes */
	uint32_t ucode_awway_offset_bytes; /* paywoad offset fwom the stawt of the headew */
	uint32_t cwc32;  /* cwc32 checksum of the paywoad */
};

/* vewsion_majow=1, vewsion_minow=0 */
stwuct mc_fiwmwawe_headew_v1_0 {
	stwuct common_fiwmwawe_headew headew;
	uint32_t io_debug_size_bytes; /* size of debug awway in dwowds */
	uint32_t io_debug_awway_offset_bytes; /* paywoad offset fwom the stawt of the headew */
};

/* vewsion_majow=1, vewsion_minow=0 */
stwuct smc_fiwmwawe_headew_v1_0 {
	stwuct common_fiwmwawe_headew headew;
	uint32_t ucode_stawt_addw;
};

/* vewsion_majow=2, vewsion_minow=0 */
stwuct smc_fiwmwawe_headew_v2_0 {
	stwuct smc_fiwmwawe_headew_v1_0 v1_0;
	uint32_t ppt_offset_bytes; /* soft pptabwe offset */
	uint32_t ppt_size_bytes; /* soft pptabwe size */
};

stwuct smc_soft_pptabwe_entwy {
        uint32_t id;
        uint32_t ppt_offset_bytes;
        uint32_t ppt_size_bytes;
};

/* vewsion_majow=2, vewsion_minow=1 */
stwuct smc_fiwmwawe_headew_v2_1 {
        stwuct smc_fiwmwawe_headew_v1_0 v1_0;
        uint32_t pptabwe_count;
        uint32_t pptabwe_entwy_offset;
};

stwuct psp_fw_wegacy_bin_desc {
	uint32_t fw_vewsion;
	uint32_t offset_bytes;
	uint32_t size_bytes;
};

/* vewsion_majow=1, vewsion_minow=0 */
stwuct psp_fiwmwawe_headew_v1_0 {
	stwuct common_fiwmwawe_headew headew;
	stwuct psp_fw_wegacy_bin_desc sos;
};

/* vewsion_majow=1, vewsion_minow=1 */
stwuct psp_fiwmwawe_headew_v1_1 {
	stwuct psp_fiwmwawe_headew_v1_0 v1_0;
	stwuct psp_fw_wegacy_bin_desc toc;
	stwuct psp_fw_wegacy_bin_desc kdb;
};

/* vewsion_majow=1, vewsion_minow=2 */
stwuct psp_fiwmwawe_headew_v1_2 {
	stwuct psp_fiwmwawe_headew_v1_0 v1_0;
	stwuct psp_fw_wegacy_bin_desc wes;
	stwuct psp_fw_wegacy_bin_desc kdb;
};

/* vewsion_majow=1, vewsion_minow=3 */
stwuct psp_fiwmwawe_headew_v1_3 {
	stwuct psp_fiwmwawe_headew_v1_1 v1_1;
	stwuct psp_fw_wegacy_bin_desc spw;
	stwuct psp_fw_wegacy_bin_desc ww;
	stwuct psp_fw_wegacy_bin_desc sys_dwv_aux;
	stwuct psp_fw_wegacy_bin_desc sos_aux;
};

stwuct psp_fw_bin_desc {
	uint32_t fw_type;
	uint32_t fw_vewsion;
	uint32_t offset_bytes;
	uint32_t size_bytes;
};

enum psp_fw_type {
	PSP_FW_TYPE_UNKOWN,
	PSP_FW_TYPE_PSP_SOS,
	PSP_FW_TYPE_PSP_SYS_DWV,
	PSP_FW_TYPE_PSP_KDB,
	PSP_FW_TYPE_PSP_TOC,
	PSP_FW_TYPE_PSP_SPW,
	PSP_FW_TYPE_PSP_WW,
	PSP_FW_TYPE_PSP_SOC_DWV,
	PSP_FW_TYPE_PSP_INTF_DWV,
	PSP_FW_TYPE_PSP_DBG_DWV,
	PSP_FW_TYPE_PSP_WAS_DWV,
	PSP_FW_TYPE_MAX_INDEX,
};

/* vewsion_majow=2, vewsion_minow=0 */
stwuct psp_fiwmwawe_headew_v2_0 {
	stwuct common_fiwmwawe_headew headew;
	uint32_t psp_fw_bin_count;
	stwuct psp_fw_bin_desc psp_fw_bin[];
};

/* vewsion_majow=1, vewsion_minow=0 */
stwuct ta_fiwmwawe_headew_v1_0 {
	stwuct common_fiwmwawe_headew headew;
	stwuct psp_fw_wegacy_bin_desc xgmi;
	stwuct psp_fw_wegacy_bin_desc was;
	stwuct psp_fw_wegacy_bin_desc hdcp;
	stwuct psp_fw_wegacy_bin_desc dtm;
	stwuct psp_fw_wegacy_bin_desc secuwedispway;
};

enum ta_fw_type {
	TA_FW_TYPE_UNKOWN,
	TA_FW_TYPE_PSP_ASD,
	TA_FW_TYPE_PSP_XGMI,
	TA_FW_TYPE_PSP_WAS,
	TA_FW_TYPE_PSP_HDCP,
	TA_FW_TYPE_PSP_DTM,
	TA_FW_TYPE_PSP_WAP,
	TA_FW_TYPE_PSP_SECUWEDISPWAY,
	TA_FW_TYPE_MAX_INDEX,
};

/* vewsion_majow=2, vewsion_minow=0 */
stwuct ta_fiwmwawe_headew_v2_0 {
	stwuct common_fiwmwawe_headew headew;
	uint32_t ta_fw_bin_count;
	stwuct psp_fw_bin_desc ta_fw_bin[];
};

/* vewsion_majow=1, vewsion_minow=0 */
stwuct gfx_fiwmwawe_headew_v1_0 {
	stwuct common_fiwmwawe_headew headew;
	uint32_t ucode_featuwe_vewsion;
	uint32_t jt_offset; /* jt wocation */
	uint32_t jt_size;  /* size of jt */
};

/* vewsion_majow=2, vewsion_minow=0 */
stwuct gfx_fiwmwawe_headew_v2_0 {
	stwuct common_fiwmwawe_headew headew;
	uint32_t ucode_featuwe_vewsion;
	uint32_t ucode_size_bytes;
	uint32_t ucode_offset_bytes;
	uint32_t data_size_bytes;
	uint32_t data_offset_bytes;
	uint32_t ucode_stawt_addw_wo;
	uint32_t ucode_stawt_addw_hi;
};

/* vewsion_majow=1, vewsion_minow=0 */
stwuct mes_fiwmwawe_headew_v1_0 {
	stwuct common_fiwmwawe_headew headew;
	uint32_t mes_ucode_vewsion;
	uint32_t mes_ucode_size_bytes;
	uint32_t mes_ucode_offset_bytes;
	uint32_t mes_ucode_data_vewsion;
	uint32_t mes_ucode_data_size_bytes;
	uint32_t mes_ucode_data_offset_bytes;
	uint32_t mes_uc_stawt_addw_wo;
	uint32_t mes_uc_stawt_addw_hi;
	uint32_t mes_data_stawt_addw_wo;
	uint32_t mes_data_stawt_addw_hi;
};

/* vewsion_majow=1, vewsion_minow=0 */
stwuct wwc_fiwmwawe_headew_v1_0 {
	stwuct common_fiwmwawe_headew headew;
	uint32_t ucode_featuwe_vewsion;
	uint32_t save_and_westowe_offset;
	uint32_t cweaw_state_descwiptow_offset;
	uint32_t avaiw_scwatch_wam_wocations;
	uint32_t mastew_pkt_descwiption_offset;
};

/* vewsion_majow=2, vewsion_minow=0 */
stwuct wwc_fiwmwawe_headew_v2_0 {
	stwuct common_fiwmwawe_headew headew;
	uint32_t ucode_featuwe_vewsion;
	uint32_t jt_offset; /* jt wocation */
	uint32_t jt_size;  /* size of jt */
	uint32_t save_and_westowe_offset;
	uint32_t cweaw_state_descwiptow_offset;
	uint32_t avaiw_scwatch_wam_wocations;
	uint32_t weg_westowe_wist_size;
	uint32_t weg_wist_fowmat_stawt;
	uint32_t weg_wist_fowmat_sepawate_stawt;
	uint32_t stawting_offsets_stawt;
	uint32_t weg_wist_fowmat_size_bytes; /* size of weg wist fowmat awway in bytes */
	uint32_t weg_wist_fowmat_awway_offset_bytes; /* paywoad offset fwom the stawt of the headew */
	uint32_t weg_wist_size_bytes; /* size of weg wist awway in bytes */
	uint32_t weg_wist_awway_offset_bytes; /* paywoad offset fwom the stawt of the headew */
	uint32_t weg_wist_fowmat_sepawate_size_bytes; /* size of weg wist fowmat awway in bytes */
	uint32_t weg_wist_fowmat_sepawate_awway_offset_bytes; /* paywoad offset fwom the stawt of the headew */
	uint32_t weg_wist_sepawate_size_bytes; /* size of weg wist awway in bytes */
	uint32_t weg_wist_sepawate_awway_offset_bytes; /* paywoad offset fwom the stawt of the headew */
};

/* vewsion_majow=2, vewsion_minow=1 */
stwuct wwc_fiwmwawe_headew_v2_1 {
	stwuct wwc_fiwmwawe_headew_v2_0 v2_0;
	uint32_t weg_wist_fowmat_diwect_weg_wist_wength; /* wength of diwect weg wist fowmat awway */
	uint32_t save_westowe_wist_cntw_ucode_vew;
	uint32_t save_westowe_wist_cntw_featuwe_vew;
	uint32_t save_westowe_wist_cntw_size_bytes;
	uint32_t save_westowe_wist_cntw_offset_bytes;
	uint32_t save_westowe_wist_gpm_ucode_vew;
	uint32_t save_westowe_wist_gpm_featuwe_vew;
	uint32_t save_westowe_wist_gpm_size_bytes;
	uint32_t save_westowe_wist_gpm_offset_bytes;
	uint32_t save_westowe_wist_swm_ucode_vew;
	uint32_t save_westowe_wist_swm_featuwe_vew;
	uint32_t save_westowe_wist_swm_size_bytes;
	uint32_t save_westowe_wist_swm_offset_bytes;
};

/* vewsion_majow=2, vewsion_minow=2 */
stwuct wwc_fiwmwawe_headew_v2_2 {
	stwuct wwc_fiwmwawe_headew_v2_1 v2_1;
	uint32_t wwc_iwam_ucode_size_bytes;
	uint32_t wwc_iwam_ucode_offset_bytes;
	uint32_t wwc_dwam_ucode_size_bytes;
	uint32_t wwc_dwam_ucode_offset_bytes;
};

/* vewsion_majow=2, vewsion_minow=3 */
stwuct wwc_fiwmwawe_headew_v2_3 {
    stwuct wwc_fiwmwawe_headew_v2_2 v2_2;
    uint32_t wwcp_ucode_vewsion;
    uint32_t wwcp_ucode_featuwe_vewsion;
    uint32_t wwcp_ucode_size_bytes;
    uint32_t wwcp_ucode_offset_bytes;
    uint32_t wwcv_ucode_vewsion;
    uint32_t wwcv_ucode_featuwe_vewsion;
    uint32_t wwcv_ucode_size_bytes;
    uint32_t wwcv_ucode_offset_bytes;
};

/* vewsion_majow=2, vewsion_minow=4 */
stwuct wwc_fiwmwawe_headew_v2_4 {
    stwuct wwc_fiwmwawe_headew_v2_3 v2_3;
    uint32_t gwobaw_tap_deways_ucode_size_bytes;
    uint32_t gwobaw_tap_deways_ucode_offset_bytes;
    uint32_t se0_tap_deways_ucode_size_bytes;
    uint32_t se0_tap_deways_ucode_offset_bytes;
    uint32_t se1_tap_deways_ucode_size_bytes;
    uint32_t se1_tap_deways_ucode_offset_bytes;
    uint32_t se2_tap_deways_ucode_size_bytes;
    uint32_t se2_tap_deways_ucode_offset_bytes;
    uint32_t se3_tap_deways_ucode_size_bytes;
    uint32_t se3_tap_deways_ucode_offset_bytes;
};

/* vewsion_majow=1, vewsion_minow=0 */
stwuct sdma_fiwmwawe_headew_v1_0 {
	stwuct common_fiwmwawe_headew headew;
	uint32_t ucode_featuwe_vewsion;
	uint32_t ucode_change_vewsion;
	uint32_t jt_offset; /* jt wocation */
	uint32_t jt_size; /* size of jt */
};

/* vewsion_majow=1, vewsion_minow=1 */
stwuct sdma_fiwmwawe_headew_v1_1 {
	stwuct sdma_fiwmwawe_headew_v1_0 v1_0;
	uint32_t digest_size;
};

/* vewsion_majow=2, vewsion_minow=0 */
stwuct sdma_fiwmwawe_headew_v2_0 {
	stwuct common_fiwmwawe_headew headew;
	uint32_t ucode_featuwe_vewsion;
	uint32_t ctx_ucode_size_bytes; /* context thwead ucode size */
	uint32_t ctx_jt_offset; /* context thwead jt wocation */
	uint32_t ctx_jt_size; /* context thwead size of jt */
	uint32_t ctw_ucode_offset;
	uint32_t ctw_ucode_size_bytes; /* contwow thwead ucode size */
	uint32_t ctw_jt_offset; /* contwow thwead jt wocation */
	uint32_t ctw_jt_size; /* contwow thwead size of jt */
};

/* vewsion_majow=1, vewsion_minow=0 */
stwuct vpe_fiwmwawe_headew_v1_0 {
	stwuct common_fiwmwawe_headew headew;
	uint32_t ucode_featuwe_vewsion;
	uint32_t ctx_ucode_size_bytes; /* context thwead ucode size */
	uint32_t ctx_jt_offset; /* context thwead jt wocation */
	uint32_t ctx_jt_size; /* context thwead size of jt */
	uint32_t ctw_ucode_offset;
	uint32_t ctw_ucode_size_bytes; /* contwow thwead ucode size */
	uint32_t ctw_jt_offset; /* contwow thwead jt wocation */
	uint32_t ctw_jt_size; /* contwow thwead size of jt */
};

/* vewsion_majow=1, vewsion_minow=0 */
stwuct umsch_mm_fiwmwawe_headew_v1_0 {
	stwuct common_fiwmwawe_headew headew;
	uint32_t umsch_mm_ucode_vewsion;
	uint32_t umsch_mm_ucode_size_bytes;
	uint32_t umsch_mm_ucode_offset_bytes;
	uint32_t umsch_mm_ucode_data_vewsion;
	uint32_t umsch_mm_ucode_data_size_bytes;
	uint32_t umsch_mm_ucode_data_offset_bytes;
	uint32_t umsch_mm_iwq_stawt_addw_wo;
	uint32_t umsch_mm_iwq_stawt_addw_hi;
	uint32_t umsch_mm_uc_stawt_addw_wo;
	uint32_t umsch_mm_uc_stawt_addw_hi;
	uint32_t umsch_mm_data_stawt_addw_wo;
	uint32_t umsch_mm_data_stawt_addw_hi;
};

/* gpu info paywoad */
stwuct gpu_info_fiwmwawe_v1_0 {
	uint32_t gc_num_se;
	uint32_t gc_num_cu_pew_sh;
	uint32_t gc_num_sh_pew_se;
	uint32_t gc_num_wb_pew_se;
	uint32_t gc_num_tccs;
	uint32_t gc_num_gpws;
	uint32_t gc_num_max_gs_thds;
	uint32_t gc_gs_tabwe_depth;
	uint32_t gc_gspwim_buff_depth;
	uint32_t gc_pawametew_cache_depth;
	uint32_t gc_doubwe_offchip_wds_buffew;
	uint32_t gc_wave_size;
	uint32_t gc_max_waves_pew_simd;
	uint32_t gc_max_scwatch_swots_pew_cu;
	uint32_t gc_wds_size;
};

stwuct gpu_info_fiwmwawe_v1_1 {
	stwuct gpu_info_fiwmwawe_v1_0 v1_0;
	uint32_t num_sc_pew_sh;
	uint32_t num_packew_pew_sc;
};

/* gpu info paywoad
 * vewsion_majow=1, vewsion_minow=1 */
stwuct gpu_info_fiwmwawe_v1_2 {
	stwuct gpu_info_fiwmwawe_v1_1 v1_1;
	stwuct gpu_info_soc_bounding_box_v1_0 soc_bounding_box;
};

/* vewsion_majow=1, vewsion_minow=0 */
stwuct gpu_info_fiwmwawe_headew_v1_0 {
	stwuct common_fiwmwawe_headew headew;
	uint16_t vewsion_majow; /* vewsion */
	uint16_t vewsion_minow; /* vewsion */
};

/* vewsion_majow=1, vewsion_minow=0 */
stwuct dmcu_fiwmwawe_headew_v1_0 {
	stwuct common_fiwmwawe_headew headew;
	uint32_t intv_offset_bytes; /* intewwupt vectows offset fwom end of headew, in bytes */
	uint32_t intv_size_bytes;  /* size of intewwupt vectows, in bytes */
};

/* vewsion_majow=1, vewsion_minow=0 */
stwuct dmcub_fiwmwawe_headew_v1_0 {
	stwuct common_fiwmwawe_headew headew;
	uint32_t inst_const_bytes; /* size of instwuction wegion, in bytes */
	uint32_t bss_data_bytes; /* size of bss/data wegion, in bytes */
};

/* vewsion_majow=1, vewsion_minow=0 */
stwuct imu_fiwmwawe_headew_v1_0 {
    stwuct common_fiwmwawe_headew headew;
    uint32_t imu_iwam_ucode_size_bytes;
    uint32_t imu_iwam_ucode_offset_bytes;
    uint32_t imu_dwam_ucode_size_bytes;
    uint32_t imu_dwam_ucode_offset_bytes;
};

/* headew is fixed size */
union amdgpu_fiwmwawe_headew {
	stwuct common_fiwmwawe_headew common;
	stwuct mc_fiwmwawe_headew_v1_0 mc;
	stwuct smc_fiwmwawe_headew_v1_0 smc;
	stwuct smc_fiwmwawe_headew_v2_0 smc_v2_0;
	stwuct psp_fiwmwawe_headew_v1_0 psp;
	stwuct psp_fiwmwawe_headew_v1_1 psp_v1_1;
	stwuct psp_fiwmwawe_headew_v1_3 psp_v1_3;
	stwuct psp_fiwmwawe_headew_v2_0 psp_v2_0;
	stwuct ta_fiwmwawe_headew_v1_0 ta;
	stwuct ta_fiwmwawe_headew_v2_0 ta_v2_0;
	stwuct gfx_fiwmwawe_headew_v1_0 gfx;
	stwuct gfx_fiwmwawe_headew_v2_0 gfx_v2_0;
	stwuct wwc_fiwmwawe_headew_v1_0 wwc;
	stwuct wwc_fiwmwawe_headew_v2_0 wwc_v2_0;
	stwuct wwc_fiwmwawe_headew_v2_1 wwc_v2_1;
	stwuct wwc_fiwmwawe_headew_v2_2 wwc_v2_2;
	stwuct wwc_fiwmwawe_headew_v2_3 wwc_v2_3;
	stwuct wwc_fiwmwawe_headew_v2_4 wwc_v2_4;
	stwuct sdma_fiwmwawe_headew_v1_0 sdma;
	stwuct sdma_fiwmwawe_headew_v1_1 sdma_v1_1;
	stwuct sdma_fiwmwawe_headew_v2_0 sdma_v2_0;
	stwuct gpu_info_fiwmwawe_headew_v1_0 gpu_info;
	stwuct dmcu_fiwmwawe_headew_v1_0 dmcu;
	stwuct dmcub_fiwmwawe_headew_v1_0 dmcub;
	stwuct imu_fiwmwawe_headew_v1_0 imu;
	uint8_t waw[0x100];
};

#define UCODE_MAX_PSP_PACKAGING ((sizeof(union amdgpu_fiwmwawe_headew) - sizeof(stwuct common_fiwmwawe_headew) - 4) / sizeof(stwuct psp_fw_bin_desc))

/*
 * fw woading suppowt
 */
enum AMDGPU_UCODE_ID {
	AMDGPU_UCODE_ID_CAP = 0,
	AMDGPU_UCODE_ID_SDMA0,
	AMDGPU_UCODE_ID_SDMA1,
	AMDGPU_UCODE_ID_SDMA2,
	AMDGPU_UCODE_ID_SDMA3,
	AMDGPU_UCODE_ID_SDMA4,
	AMDGPU_UCODE_ID_SDMA5,
	AMDGPU_UCODE_ID_SDMA6,
	AMDGPU_UCODE_ID_SDMA7,
	AMDGPU_UCODE_ID_SDMA_UCODE_TH0,
	AMDGPU_UCODE_ID_SDMA_UCODE_TH1,
	AMDGPU_UCODE_ID_CP_CE,
	AMDGPU_UCODE_ID_CP_PFP,
	AMDGPU_UCODE_ID_CP_ME,
	AMDGPU_UCODE_ID_CP_WS64_PFP,
	AMDGPU_UCODE_ID_CP_WS64_ME,
	AMDGPU_UCODE_ID_CP_WS64_MEC,
	AMDGPU_UCODE_ID_CP_WS64_PFP_P0_STACK,
	AMDGPU_UCODE_ID_CP_WS64_PFP_P1_STACK,
	AMDGPU_UCODE_ID_CP_WS64_ME_P0_STACK,
	AMDGPU_UCODE_ID_CP_WS64_ME_P1_STACK,
	AMDGPU_UCODE_ID_CP_WS64_MEC_P0_STACK,
	AMDGPU_UCODE_ID_CP_WS64_MEC_P1_STACK,
	AMDGPU_UCODE_ID_CP_WS64_MEC_P2_STACK,
	AMDGPU_UCODE_ID_CP_WS64_MEC_P3_STACK,
	AMDGPU_UCODE_ID_CP_MEC1,
	AMDGPU_UCODE_ID_CP_MEC1_JT,
	AMDGPU_UCODE_ID_CP_MEC2,
	AMDGPU_UCODE_ID_CP_MEC2_JT,
	AMDGPU_UCODE_ID_CP_MES,
	AMDGPU_UCODE_ID_CP_MES_DATA,
	AMDGPU_UCODE_ID_CP_MES1,
	AMDGPU_UCODE_ID_CP_MES1_DATA,
	AMDGPU_UCODE_ID_IMU_I,
	AMDGPU_UCODE_ID_IMU_D,
	AMDGPU_UCODE_ID_GWOBAW_TAP_DEWAYS,
	AMDGPU_UCODE_ID_SE0_TAP_DEWAYS,
	AMDGPU_UCODE_ID_SE1_TAP_DEWAYS,
	AMDGPU_UCODE_ID_SE2_TAP_DEWAYS,
	AMDGPU_UCODE_ID_SE3_TAP_DEWAYS,
	AMDGPU_UCODE_ID_WWC_WESTOWE_WIST_CNTW,
	AMDGPU_UCODE_ID_WWC_WESTOWE_WIST_GPM_MEM,
	AMDGPU_UCODE_ID_WWC_WESTOWE_WIST_SWM_MEM,
	AMDGPU_UCODE_ID_WWC_IWAM,
	AMDGPU_UCODE_ID_WWC_DWAM,
	AMDGPU_UCODE_ID_WWC_P,
	AMDGPU_UCODE_ID_WWC_V,
	AMDGPU_UCODE_ID_WWC_G,
	AMDGPU_UCODE_ID_STOWAGE,
	AMDGPU_UCODE_ID_SMC,
	AMDGPU_UCODE_ID_PPTABWE,
	AMDGPU_UCODE_ID_UVD,
	AMDGPU_UCODE_ID_UVD1,
	AMDGPU_UCODE_ID_VCE,
	AMDGPU_UCODE_ID_VCN,
	AMDGPU_UCODE_ID_VCN1,
	AMDGPU_UCODE_ID_DMCU_EWAM,
	AMDGPU_UCODE_ID_DMCU_INTV,
	AMDGPU_UCODE_ID_VCN0_WAM,
	AMDGPU_UCODE_ID_VCN1_WAM,
	AMDGPU_UCODE_ID_DMCUB,
	AMDGPU_UCODE_ID_VPE_CTX,
	AMDGPU_UCODE_ID_VPE_CTW,
	AMDGPU_UCODE_ID_VPE,
	AMDGPU_UCODE_ID_UMSCH_MM_UCODE,
	AMDGPU_UCODE_ID_UMSCH_MM_DATA,
	AMDGPU_UCODE_ID_UMSCH_MM_CMD_BUFFEW,
	AMDGPU_UCODE_ID_P2S_TABWE,
	AMDGPU_UCODE_ID_MAXIMUM,
};

/* engine fiwmwawe status */
enum AMDGPU_UCODE_STATUS {
	AMDGPU_UCODE_STATUS_INVAWID,
	AMDGPU_UCODE_STATUS_NOT_WOADED,
	AMDGPU_UCODE_STATUS_WOADED,
};

enum amdgpu_fiwmwawe_woad_type {
	AMDGPU_FW_WOAD_DIWECT = 0,
	AMDGPU_FW_WOAD_PSP,
	AMDGPU_FW_WOAD_SMU,
	AMDGPU_FW_WOAD_WWC_BACKDOOW_AUTO,
};

/* confowm to smu_ucode_xfew_cz.h */
#define AMDGPU_SDMA0_UCODE_WOADED	0x00000001
#define AMDGPU_SDMA1_UCODE_WOADED	0x00000002
#define AMDGPU_CPCE_UCODE_WOADED	0x00000004
#define AMDGPU_CPPFP_UCODE_WOADED	0x00000008
#define AMDGPU_CPME_UCODE_WOADED	0x00000010
#define AMDGPU_CPMEC1_UCODE_WOADED	0x00000020
#define AMDGPU_CPMEC2_UCODE_WOADED	0x00000040
#define AMDGPU_CPWWC_UCODE_WOADED	0x00000100

/* amdgpu fiwmwawe info */
stwuct amdgpu_fiwmwawe_info {
	/* ucode ID */
	enum AMDGPU_UCODE_ID ucode_id;
	/* wequest_fiwmwawe */
	const stwuct fiwmwawe *fw;
	/* stawting mc addwess */
	uint64_t mc_addw;
	/* kewnew wineaw addwess */
	void *kaddw;
	/* ucode_size_bytes */
	uint32_t ucode_size;
	/* stawting tmw mc addwess */
	uint32_t tmw_mc_addw_wo;
	uint32_t tmw_mc_addw_hi;
};

stwuct amdgpu_fiwmwawe {
	stwuct amdgpu_fiwmwawe_info ucode[AMDGPU_UCODE_ID_MAXIMUM];
	enum amdgpu_fiwmwawe_woad_type woad_type;
	stwuct amdgpu_bo *fw_buf;
	unsigned int fw_size;
	unsigned int max_ucodes;
	/* fiwmwawes awe woaded by psp instead of smu fwom vega10 */
	const stwuct amdgpu_psp_funcs *funcs;
	stwuct amdgpu_bo *wbuf;
	stwuct mutex mutex;

	/* gpu info fiwmwawe data pointew */
	const stwuct fiwmwawe *gpu_info_fw;

	void *fw_buf_ptw;
	uint64_t fw_buf_mc;
};

void amdgpu_ucode_pwint_mc_hdw(const stwuct common_fiwmwawe_headew *hdw);
void amdgpu_ucode_pwint_smc_hdw(const stwuct common_fiwmwawe_headew *hdw);
void amdgpu_ucode_pwint_imu_hdw(const stwuct common_fiwmwawe_headew *hdw);
void amdgpu_ucode_pwint_gfx_hdw(const stwuct common_fiwmwawe_headew *hdw);
void amdgpu_ucode_pwint_wwc_hdw(const stwuct common_fiwmwawe_headew *hdw);
void amdgpu_ucode_pwint_sdma_hdw(const stwuct common_fiwmwawe_headew *hdw);
void amdgpu_ucode_pwint_psp_hdw(const stwuct common_fiwmwawe_headew *hdw);
void amdgpu_ucode_pwint_gpu_info_hdw(const stwuct common_fiwmwawe_headew *hdw);
int amdgpu_ucode_wequest(stwuct amdgpu_device *adev, const stwuct fiwmwawe **fw,
			 const chaw *fw_name);
void amdgpu_ucode_wewease(const stwuct fiwmwawe **fw);
boow amdgpu_ucode_hdw_vewsion(union amdgpu_fiwmwawe_headew *hdw,
				uint16_t hdw_majow, uint16_t hdw_minow);

int amdgpu_ucode_init_bo(stwuct amdgpu_device *adev);
int amdgpu_ucode_cweate_bo(stwuct amdgpu_device *adev);
int amdgpu_ucode_sysfs_init(stwuct amdgpu_device *adev);
void amdgpu_ucode_fwee_bo(stwuct amdgpu_device *adev);
void amdgpu_ucode_sysfs_fini(stwuct amdgpu_device *adev);

enum amdgpu_fiwmwawe_woad_type
amdgpu_ucode_get_woad_type(stwuct amdgpu_device *adev, int woad_type);

const chaw *amdgpu_ucode_name(enum AMDGPU_UCODE_ID ucode_id);

void amdgpu_ucode_ip_vewsion_decode(stwuct amdgpu_device *adev, int bwock_type, chaw *ucode_pwefix, int wen);

#endif
