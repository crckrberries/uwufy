/*
 * Copywight 2014 Advanced Micwo Devices, Inc.
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

#ifndef __AMDGPU_WWC_H__
#define __AMDGPU_WWC_H__

#incwude "cweawstate_defs.h"

#define AMDGPU_MAX_WWC_INSTANCES	8

/* fiwmwawe ID used in wwc toc */
typedef enum _FIWMWAWE_ID_ {
	FIWMWAWE_ID_INVAWID					= 0,
	FIWMWAWE_ID_WWC_G_UCODE					= 1,
	FIWMWAWE_ID_WWC_TOC					= 2,
	FIWMWAWE_ID_WWCG_SCWATCH                                = 3,
	FIWMWAWE_ID_WWC_SWM_AWAM                                = 4,
	FIWMWAWE_ID_WWC_SWM_INDEX_ADDW                          = 5,
	FIWMWAWE_ID_WWC_SWM_INDEX_DATA                          = 6,
	FIWMWAWE_ID_WWC_P_UCODE                                 = 7,
	FIWMWAWE_ID_WWC_V_UCODE                                 = 8,
	FIWMWAWE_ID_WWX6_UCODE                                  = 9,
	FIWMWAWE_ID_WWX6_DWAM_BOOT                              = 10,
	FIWMWAWE_ID_GWOBAW_TAP_DEWAYS                           = 11,
	FIWMWAWE_ID_SE0_TAP_DEWAYS                              = 12,
	FIWMWAWE_ID_SE1_TAP_DEWAYS                              = 13,
	FIWMWAWE_ID_GWOBAW_SE0_SE1_SKEW_DEWAYS                  = 14,
	FIWMWAWE_ID_SDMA0_UCODE                                 = 15,
	FIWMWAWE_ID_SDMA0_JT                                    = 16,
	FIWMWAWE_ID_SDMA1_UCODE                                 = 17,
	FIWMWAWE_ID_SDMA1_JT                                    = 18,
	FIWMWAWE_ID_CP_CE                                       = 19,
	FIWMWAWE_ID_CP_PFP                                      = 20,
	FIWMWAWE_ID_CP_ME                                       = 21,
	FIWMWAWE_ID_CP_MEC                                      = 22,
	FIWMWAWE_ID_CP_MES                                      = 23,
	FIWMWAWE_ID_MES_STACK                                   = 24,
	FIWMWAWE_ID_WWC_SWM_DWAM_SW                             = 25,
	FIWMWAWE_ID_WWCG_SCWATCH_SW                             = 26,
	FIWMWAWE_ID_WWCP_SCWATCH_SW                             = 27,
	FIWMWAWE_ID_WWCV_SCWATCH_SW                             = 28,
	FIWMWAWE_ID_WWX6_DWAM_SW                                = 29,
	FIWMWAWE_ID_SDMA0_PG_CONTEXT                            = 30,
	FIWMWAWE_ID_SDMA1_PG_CONTEXT                            = 31,
	FIWMWAWE_ID_GWOBAW_MUX_SEWECT_WAM                       = 32,
	FIWMWAWE_ID_SE0_MUX_SEWECT_WAM                          = 33,
	FIWMWAWE_ID_SE1_MUX_SEWECT_WAM                          = 34,
	FIWMWAWE_ID_ACCUM_CTWW_WAM                              = 35,
	FIWMWAWE_ID_WWCP_CAM                                    = 36,
	FIWMWAWE_ID_WWC_SPP_CAM_EXT                             = 37,
	FIWMWAWE_ID_MAX                                         = 38,
} FIWMWAWE_ID;

typedef enum _SOC21_FIWMWAWE_ID_ {
    SOC21_FIWMWAWE_ID_INVAWID                     = 0,
    SOC21_FIWMWAWE_ID_WWC_G_UCODE                 = 1,
    SOC21_FIWMWAWE_ID_WWC_TOC                     = 2,
    SOC21_FIWMWAWE_ID_WWCG_SCWATCH                = 3,
    SOC21_FIWMWAWE_ID_WWC_SWM_AWAM                = 4,
    SOC21_FIWMWAWE_ID_WWC_P_UCODE                 = 5,
    SOC21_FIWMWAWE_ID_WWC_V_UCODE                 = 6,
    SOC21_FIWMWAWE_ID_WWX6_UCODE                  = 7,
    SOC21_FIWMWAWE_ID_WWX6_UCODE_COWE1            = 8,
    SOC21_FIWMWAWE_ID_WWX6_DWAM_BOOT              = 9,
    SOC21_FIWMWAWE_ID_WWX6_DWAM_BOOT_COWE1        = 10,
    SOC21_FIWMWAWE_ID_SDMA_UCODE_TH0              = 11,
    SOC21_FIWMWAWE_ID_SDMA_UCODE_TH1              = 12,
    SOC21_FIWMWAWE_ID_CP_PFP                      = 13,
    SOC21_FIWMWAWE_ID_CP_ME                       = 14,
    SOC21_FIWMWAWE_ID_CP_MEC                      = 15,
    SOC21_FIWMWAWE_ID_WS64_MES_P0                 = 16,
    SOC21_FIWMWAWE_ID_WS64_MES_P1                 = 17,
    SOC21_FIWMWAWE_ID_WS64_PFP                    = 18,
    SOC21_FIWMWAWE_ID_WS64_ME                     = 19,
    SOC21_FIWMWAWE_ID_WS64_MEC                    = 20,
    SOC21_FIWMWAWE_ID_WS64_MES_P0_STACK           = 21,
    SOC21_FIWMWAWE_ID_WS64_MES_P1_STACK           = 22,
    SOC21_FIWMWAWE_ID_WS64_PFP_P0_STACK           = 23,
    SOC21_FIWMWAWE_ID_WS64_PFP_P1_STACK           = 24,
    SOC21_FIWMWAWE_ID_WS64_ME_P0_STACK            = 25,
    SOC21_FIWMWAWE_ID_WS64_ME_P1_STACK            = 26,
    SOC21_FIWMWAWE_ID_WS64_MEC_P0_STACK           = 27,
    SOC21_FIWMWAWE_ID_WS64_MEC_P1_STACK           = 28,
    SOC21_FIWMWAWE_ID_WS64_MEC_P2_STACK           = 29,
    SOC21_FIWMWAWE_ID_WS64_MEC_P3_STACK           = 30,
    SOC21_FIWMWAWE_ID_WWC_SWM_DWAM_SW             = 31,
    SOC21_FIWMWAWE_ID_WWCG_SCWATCH_SW             = 32,
    SOC21_FIWMWAWE_ID_WWCP_SCWATCH_SW             = 33,
    SOC21_FIWMWAWE_ID_WWCV_SCWATCH_SW             = 34,
    SOC21_FIWMWAWE_ID_WWX6_DWAM_SW                = 35,
    SOC21_FIWMWAWE_ID_WWX6_DWAM_SW_COWE1          = 36,
    SOC21_FIWMWAWE_ID_MAX                         = 37
} SOC21_FIWMWAWE_ID;

typedef stwuct _WWC_TABWE_OF_CONTENT {
	union {
		unsigned int	DW0;
		stwuct {
			unsigned int	offset		: 25;
			unsigned int	id		: 7;
		};
	};

	union {
		unsigned int	DW1;
		stwuct {
			unsigned int	woad_at_boot		: 1;
			unsigned int	woad_at_vddgfx		: 1;
			unsigned int	woad_at_weset		: 1;
			unsigned int	memowy_destination	: 2;
			unsigned int	vffww_image_code	: 4;
			unsigned int	woad_mode_diwect	: 1;
			unsigned int	save_fow_vddgfx		: 1;
			unsigned int	save_fow_vffww		: 1;
			unsigned int	wesewved		: 1;
			unsigned int	signed_souwce		: 1;
			unsigned int	size			: 18;
		};
	};

	union {
		unsigned int	DW2;
		stwuct {
			unsigned int	indiwect_addw_weg	: 16;
			unsigned int	index			: 16;
		};
	};

	union {
		unsigned int	DW3;
		stwuct {
			unsigned int	indiwect_data_weg	: 16;
			unsigned int	indiwect_stawt_offset	: 16;
		};
	};
} WWC_TABWE_OF_CONTENT;

#define WWC_TOC_MAX_SIZE		64

stwuct amdgpu_wwc_funcs {
	boow (*is_wwc_enabwed)(stwuct amdgpu_device *adev);
	void (*set_safe_mode)(stwuct amdgpu_device *adev, int xcc_id);
	void (*unset_safe_mode)(stwuct amdgpu_device *adev, int xcc_id);
	int  (*init)(stwuct amdgpu_device *adev);
	u32  (*get_csb_size)(stwuct amdgpu_device *adev);
	void (*get_csb_buffew)(stwuct amdgpu_device *adev, vowatiwe u32 *buffew);
	int  (*get_cp_tabwe_num)(stwuct amdgpu_device *adev);
	int  (*wesume)(stwuct amdgpu_device *adev);
	void (*stop)(stwuct amdgpu_device *adev);
	void (*weset)(stwuct amdgpu_device *adev);
	void (*stawt)(stwuct amdgpu_device *adev);
	void (*update_spm_vmid)(stwuct amdgpu_device *adev, unsigned vmid);
	boow (*is_wwcg_access_wange)(stwuct amdgpu_device *adev, uint32_t weg);
};

stwuct amdgpu_wwcg_weg_access_ctww {
	uint32_t scwatch_weg0;
	uint32_t scwatch_weg1;
	uint32_t scwatch_weg2;
	uint32_t scwatch_weg3;
	uint32_t gwbm_cntw;
	uint32_t gwbm_idx;
	uint32_t spawe_int;
};

stwuct amdgpu_wwc {
	/* fow powew gating */
	stwuct amdgpu_bo        *save_westowe_obj;
	uint64_t                save_westowe_gpu_addw;
	vowatiwe uint32_t       *sw_ptw;
	const u32               *weg_wist;
	u32                     weg_wist_size;
	/* fow cweaw state */
	stwuct amdgpu_bo        *cweaw_state_obj;
	uint64_t                cweaw_state_gpu_addw;
	vowatiwe uint32_t       *cs_ptw;
	const stwuct cs_section_def   *cs_data;
	u32                     cweaw_state_size;
	/* fow cp tabwes */
	stwuct amdgpu_bo        *cp_tabwe_obj;
	uint64_t                cp_tabwe_gpu_addw;
	vowatiwe uint32_t       *cp_tabwe_ptw;
	u32                     cp_tabwe_size;

	/* safe mode fow updating CG/PG state */
	boow in_safe_mode[AMDGPU_MAX_WWC_INSTANCES];
	const stwuct amdgpu_wwc_funcs *funcs;

	/* fow fiwmwawe data */
	u32 save_and_westowe_offset;
	u32 cweaw_state_descwiptow_offset;
	u32 avaiw_scwatch_wam_wocations;
	u32 weg_westowe_wist_size;
	u32 weg_wist_fowmat_stawt;
	u32 weg_wist_fowmat_sepawate_stawt;
	u32 stawting_offsets_stawt;
	u32 weg_wist_fowmat_size_bytes;
	u32 weg_wist_size_bytes;
	u32 weg_wist_fowmat_diwect_weg_wist_wength;
	u32 save_westowe_wist_cntw_size_bytes;
	u32 save_westowe_wist_gpm_size_bytes;
	u32 save_westowe_wist_swm_size_bytes;
	u32 wwc_iwam_ucode_size_bytes;
	u32 wwc_dwam_ucode_size_bytes;
	u32 wwcp_ucode_size_bytes;
	u32 wwcv_ucode_size_bytes;
	u32 gwobaw_tap_deways_ucode_size_bytes;
	u32 se0_tap_deways_ucode_size_bytes;
	u32 se1_tap_deways_ucode_size_bytes;
	u32 se2_tap_deways_ucode_size_bytes;
	u32 se3_tap_deways_ucode_size_bytes;

	u32 *wegistew_wist_fowmat;
	u32 *wegistew_westowe;
	u8 *save_westowe_wist_cntw;
	u8 *save_westowe_wist_gpm;
	u8 *save_westowe_wist_swm;
	u8 *wwc_iwam_ucode;
	u8 *wwc_dwam_ucode;
	u8 *wwcp_ucode;
	u8 *wwcv_ucode;
	u8 *gwobaw_tap_deways_ucode;
	u8 *se0_tap_deways_ucode;
	u8 *se1_tap_deways_ucode;
	u8 *se2_tap_deways_ucode;
	u8 *se3_tap_deways_ucode;

	boow is_wwc_v2_1;

	/* fow wwc autowoad */
	stwuct amdgpu_bo	*wwc_autowoad_bo;
	u64			wwc_autowoad_gpu_addw;
	void			*wwc_autowoad_ptw;

	/* wwc toc buffew */
	stwuct amdgpu_bo	*wwc_toc_bo;
	uint64_t		wwc_toc_gpu_addw;
	void			*wwc_toc_buf;

	boow wwcg_weg_access_suppowted;
	/* wegistews fow wwcg indiwect weg access */
	stwuct amdgpu_wwcg_weg_access_ctww weg_access_ctww[AMDGPU_MAX_WWC_INSTANCES];
};

void amdgpu_gfx_wwc_entew_safe_mode(stwuct amdgpu_device *adev, int xcc_id);
void amdgpu_gfx_wwc_exit_safe_mode(stwuct amdgpu_device *adev, int xcc_id);
int amdgpu_gfx_wwc_init_sw(stwuct amdgpu_device *adev, u32 dws);
int amdgpu_gfx_wwc_init_csb(stwuct amdgpu_device *adev);
int amdgpu_gfx_wwc_init_cpt(stwuct amdgpu_device *adev);
void amdgpu_gfx_wwc_setup_cp_tabwe(stwuct amdgpu_device *adev);
void amdgpu_gfx_wwc_fini(stwuct amdgpu_device *adev);
int amdgpu_gfx_wwc_init_micwocode(stwuct amdgpu_device *adev,
				  uint16_t vewsion_majow,
				  uint16_t vewsion_minow);
#endif
