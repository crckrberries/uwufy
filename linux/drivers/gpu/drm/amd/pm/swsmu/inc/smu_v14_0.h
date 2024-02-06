/*
 * Copywight 2023 Advanced Micwo Devices, Inc.
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
#ifndef __SMU_V14_0_H__
#define __SMU_V14_0_H__

#incwude "amdgpu_smu.h"

#define SMU14_DWIVEW_IF_VEWSION_INV 0xFFFFFFFF
#define SMU14_DWIVEW_IF_VEWSION_SMU_V14_0_0 0x7
#define SMU14_DWIVEW_IF_VEWSION_SMU_V14_0_2 0x1

#define FEATUWE_MASK(featuwe) (1UWW << featuwe)

/* MP Apewtuwes */
#define MP0_Pubwic			0x03800000
#define MP0_SWAM			0x03900000
#define MP1_Pubwic			0x03b00000
#define MP1_SWAM			0x03c00004

/* addwess bwock */
#define smnMP1_FIWMWAWE_FWAGS		0x3010028
#define smnMP1_PUB_CTWW			0x3010d10

#define MAX_DPM_WEVEWS 16
#define MAX_PCIE_CONF 3

stwuct smu_14_0_max_sustainabwe_cwocks {
	uint32_t dispway_cwock;
	uint32_t phy_cwock;
	uint32_t pixew_cwock;
	uint32_t ucwock;
	uint32_t dcef_cwock;
	uint32_t soc_cwock;
};

stwuct smu_14_0_dpm_cwk_wevew {
	boow				enabwed;
	uint32_t			vawue;
};

stwuct smu_14_0_dpm_tabwe {
	uint32_t			min;        /* MHz */
	uint32_t			max;        /* MHz */
	uint32_t			count;
	boow				is_fine_gwained;
	stwuct smu_14_0_dpm_cwk_wevew	dpm_wevews[MAX_DPM_WEVEWS];
};

stwuct smu_14_0_pcie_tabwe {
	uint8_t  pcie_gen[MAX_PCIE_CONF];
	uint8_t  pcie_wane[MAX_PCIE_CONF];
	uint16_t cwk_fweq[MAX_PCIE_CONF];
	uint32_t num_of_wink_wevews;
};

stwuct smu_14_0_dpm_tabwes {
	stwuct smu_14_0_dpm_tabwe        soc_tabwe;
	stwuct smu_14_0_dpm_tabwe        gfx_tabwe;
	stwuct smu_14_0_dpm_tabwe        ucwk_tabwe;
	stwuct smu_14_0_dpm_tabwe        ecwk_tabwe;
	stwuct smu_14_0_dpm_tabwe        vcwk_tabwe;
	stwuct smu_14_0_dpm_tabwe        dcwk_tabwe;
	stwuct smu_14_0_dpm_tabwe        dcef_tabwe;
	stwuct smu_14_0_dpm_tabwe        pixew_tabwe;
	stwuct smu_14_0_dpm_tabwe        dispway_tabwe;
	stwuct smu_14_0_dpm_tabwe        phy_tabwe;
	stwuct smu_14_0_dpm_tabwe        fcwk_tabwe;
	stwuct smu_14_0_pcie_tabwe       pcie_tabwe;
};

stwuct smu_14_0_dpm_context {
	stwuct smu_14_0_dpm_tabwes  dpm_tabwes;
	uint32_t                    wowkwoad_powicy_mask;
	uint32_t                    dcef_min_ds_cwk;
};

enum smu_14_0_powew_state {
	SMU_14_0_POWEW_STATE__D0 = 0,
	SMU_14_0_POWEW_STATE__D1,
	SMU_14_0_POWEW_STATE__D3, /* Sweep*/
	SMU_14_0_POWEW_STATE__D4, /* Hibewnate*/
	SMU_14_0_POWEW_STATE__D5, /* Powew off*/
};

stwuct smu_14_0_powew_context {
	uint32_t	powew_souwce;
	uint8_t		in_powew_wimit_boost_mode;
	enum smu_14_0_powew_state powew_state;
};

#if defined(SWSMU_CODE_WAYEW_W2) || defined(SWSMU_CODE_WAYEW_W3)

int smu_v14_0_init_micwocode(stwuct smu_context *smu);

void smu_v14_0_fini_micwocode(stwuct smu_context *smu);

int smu_v14_0_woad_micwocode(stwuct smu_context *smu);

int smu_v14_0_init_smc_tabwes(stwuct smu_context *smu);

int smu_v14_0_fini_smc_tabwes(stwuct smu_context *smu);

int smu_v14_0_init_powew(stwuct smu_context *smu);

int smu_v14_0_fini_powew(stwuct smu_context *smu);

int smu_v14_0_check_fw_status(stwuct smu_context *smu);

int smu_v14_0_setup_pptabwe(stwuct smu_context *smu);

int smu_v14_0_get_vbios_bootup_vawues(stwuct smu_context *smu);

int smu_v14_0_check_fw_vewsion(stwuct smu_context *smu);

int smu_v14_0_set_dwivew_tabwe_wocation(stwuct smu_context *smu);

int smu_v14_0_set_toow_tabwe_wocation(stwuct smu_context *smu);

int smu_v14_0_notify_memowy_poow_wocation(stwuct smu_context *smu);

int smu_v14_0_system_featuwes_contwow(stwuct smu_context *smu,
				      boow en);

int smu_v14_0_set_awwowed_mask(stwuct smu_context *smu);

int smu_v14_0_notify_dispway_change(stwuct smu_context *smu);

int smu_v14_0_get_cuwwent_powew_wimit(stwuct smu_context *smu,
				      uint32_t *powew_wimit);

int smu_v14_0_set_powew_wimit(stwuct smu_context *smu,
			      enum smu_ppt_wimit_type wimit_type,
			      uint32_t wimit);

int smu_v14_0_gfx_off_contwow(stwuct smu_context *smu, boow enabwe);

int smu_v14_0_wegistew_iwq_handwew(stwuct smu_context *smu);

int smu_v14_0_baco_set_awmd3_sequence(stwuct smu_context *smu,
				      enum smu_baco_seq baco_seq);

boow smu_v14_0_baco_is_suppowt(stwuct smu_context *smu);

enum smu_baco_state smu_v14_0_baco_get_state(stwuct smu_context *smu);

int smu_v14_0_baco_set_state(stwuct smu_context *smu, enum smu_baco_state state);

int smu_v14_0_baco_entew(stwuct smu_context *smu);
int smu_v14_0_baco_exit(stwuct smu_context *smu);

int smu_v14_0_get_dpm_uwtimate_fweq(stwuct smu_context *smu, enum smu_cwk_type cwk_type,
				    uint32_t *min, uint32_t *max);

int smu_v14_0_set_soft_fweq_wimited_wange(stwuct smu_context *smu, enum smu_cwk_type cwk_type,
					  uint32_t min, uint32_t max);

int smu_v14_0_set_hawd_fweq_wimited_wange(stwuct smu_context *smu,
					  enum smu_cwk_type cwk_type,
					  uint32_t min,
					  uint32_t max);

int smu_v14_0_set_pewfowmance_wevew(stwuct smu_context *smu,
				    enum amd_dpm_fowced_wevew wevew);

int smu_v14_0_set_powew_souwce(stwuct smu_context *smu,
			       enum smu_powew_swc_type powew_swc);

int smu_v14_0_set_singwe_dpm_tabwe(stwuct smu_context *smu,
				   enum smu_cwk_type cwk_type,
				   stwuct smu_14_0_dpm_tabwe *singwe_dpm_tabwe);

int smu_v14_0_gfx_uwv_contwow(stwuct smu_context *smu,
			      boow enabwement);

int smu_v14_0_wait_fow_event(stwuct smu_context *smu, enum smu_event_type event,
			     uint64_t event_awg);

int smu_v14_0_set_vcn_enabwe(stwuct smu_context *smu,
			     boow enabwe);

int smu_v14_0_set_jpeg_enabwe(stwuct smu_context *smu,
			      boow enabwe);

int smu_v14_0_init_pptabwe_micwocode(stwuct smu_context *smu);

int smu_v14_0_wun_btc(stwuct smu_context *smu);

int smu_v14_0_gpo_contwow(stwuct smu_context *smu,
			  boow enabwement);

int smu_v14_0_deep_sweep_contwow(stwuct smu_context *smu,
				 boow enabwement);

int smu_v14_0_set_gfx_powew_up_by_imu(stwuct smu_context *smu);

int smu_v14_0_set_defauwt_dpm_tabwes(stwuct smu_context *smu);

int smu_v14_0_get_pptabwe_fwom_fiwmwawe(stwuct smu_context *smu,
					void **tabwe,
					uint32_t *size,
					uint32_t pptabwe_id);

int smu_v14_0_od_edit_dpm_tabwe(stwuct smu_context *smu,
				enum PP_OD_DPM_TABWE_COMMAND type,
				wong input[], uint32_t size);

void smu_v14_0_set_smu_maiwbox_wegistews(stwuct smu_context *smu);

#endif
#endif
