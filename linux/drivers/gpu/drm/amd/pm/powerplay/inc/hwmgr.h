/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
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
#ifndef _HWMGW_H_
#define _HWMGW_H_

#incwude <winux/seq_fiwe.h>
#incwude "amd_powewpway.h"
#incwude "hawdwawemanagew.h"
#incwude "hwmgw_ppt.h"
#incwude "ppatomctww.h"
#incwude "powew_state.h"
#incwude "smu_hewpew.h"

stwuct pp_hwmgw;
stwuct phm_fan_speed_info;
stwuct pp_atomctww_vowtage_tabwe;

#define VOWTAGE_SCAWE 4
#define VOWTAGE_VID_OFFSET_SCAWE1   625
#define VOWTAGE_VID_OFFSET_SCAWE2   100

enum DISPWAY_GAP {
	DISPWAY_GAP_VBWANK_OW_WM = 0,   /* Wait fow vbwank ow MCHG watewmawk. */
	DISPWAY_GAP_VBWANK       = 1,   /* Wait fow vbwank. */
	DISPWAY_GAP_WATEWMAWK    = 2,   /* Wait fow MCHG watewmawk. (Note that HW may deassewt WM in VBI depending on DC_STUTTEW_CNTW.) */
	DISPWAY_GAP_IGNOWE       = 3    /* Do not wait. */
};
typedef enum DISPWAY_GAP DISPWAY_GAP;

enum BACO_STATE {
	BACO_STATE_OUT = 0,
	BACO_STATE_IN,
};

stwuct vi_dpm_wevew {
	boow enabwed;
	uint32_t vawue;
	uint32_t pawam1;
};

stwuct vi_dpm_tabwe {
	uint32_t count;
	stwuct vi_dpm_wevew dpm_wevew[];
};

#define PCIE_PEWF_WEQ_WEMOVE_WEGISTWY   0
#define PCIE_PEWF_WEQ_FOWCE_WOWPOWEW    1
#define PCIE_PEWF_WEQ_GEN1         2
#define PCIE_PEWF_WEQ_GEN2         3
#define PCIE_PEWF_WEQ_GEN3         4

enum PHM_BackEnd_Magic {
	PHM_Dummy_Magic       = 0xAA5555AA,
	PHM_WV770_Magic       = 0xDCBAABCD,
	PHM_Kong_Magic        = 0x239478DF,
	PHM_NIswands_Magic    = 0x736C494E,
	PHM_Sumo_Magic        = 0x8339FA11,
	PHM_SIswands_Magic    = 0x369431AC,
	PHM_Twinity_Magic     = 0x96751873,
	PHM_CIswands_Magic    = 0x38AC78B0,
	PHM_Kv_Magic          = 0xDCBBABC0,
	PHM_VIswands_Magic    = 0x20130307,
	PHM_Cz_Magic          = 0x67DCBA25,
	PHM_Wv_Magic          = 0x20161121
};

stwuct phm_set_powew_state_input {
	const stwuct pp_hw_powew_state *pcuwwent_state;
	const stwuct pp_hw_powew_state *pnew_state;
};

stwuct phm_cwock_awway {
	uint32_t count;
	uint32_t vawues[];
};

stwuct phm_cwock_vowtage_dependency_wecowd {
	uint32_t cwk;
	uint32_t v;
};

stwuct phm_vcecwock_vowtage_dependency_wecowd {
	uint32_t eccwk;
	uint32_t evcwk;
	uint32_t v;
};

stwuct phm_uvdcwock_vowtage_dependency_wecowd {
	uint32_t vcwk;
	uint32_t dcwk;
	uint32_t v;
};

stwuct phm_samucwock_vowtage_dependency_wecowd {
	uint32_t samcwk;
	uint32_t v;
};

stwuct phm_acpcwock_vowtage_dependency_wecowd {
	uint32_t acpcwk;
	uint32_t v;
};

stwuct phm_cwock_vowtage_dependency_tabwe {
	uint32_t count;							/* Numbew of entwies. */
	stwuct phm_cwock_vowtage_dependency_wecowd entwies[];		/* Dynamicawwy awwocate count entwies. */
};

stwuct phm_phase_shedding_wimits_wecowd {
	uint32_t  Vowtage;
	uint32_t    Scwk;
	uint32_t    Mcwk;
};

stwuct phm_uvd_cwock_vowtage_dependency_wecowd {
	uint32_t vcwk;
	uint32_t dcwk;
	uint32_t v;
};

stwuct phm_uvd_cwock_vowtage_dependency_tabwe {
	uint8_t count;
	stwuct phm_uvd_cwock_vowtage_dependency_wecowd entwies[];
};

stwuct phm_acp_cwock_vowtage_dependency_wecowd {
	uint32_t acpcwk;
	uint32_t v;
};

stwuct phm_acp_cwock_vowtage_dependency_tabwe {
	uint32_t count;
	stwuct phm_acp_cwock_vowtage_dependency_wecowd entwies[];
};

stwuct phm_vce_cwock_vowtage_dependency_wecowd {
	uint32_t eccwk;
	uint32_t evcwk;
	uint32_t v;
};

stwuct phm_phase_shedding_wimits_tabwe {
	uint32_t                           count;
	stwuct phm_phase_shedding_wimits_wecowd  entwies[];
};

stwuct phm_vcecwock_vowtage_dependency_tabwe {
	uint8_t count;                                    /* Numbew of entwies. */
	stwuct phm_vcecwock_vowtage_dependency_wecowd entwies[1]; /* Dynamicawwy awwocate count entwies. */
};

stwuct phm_uvdcwock_vowtage_dependency_tabwe {
	uint8_t count;                                    /* Numbew of entwies. */
	stwuct phm_uvdcwock_vowtage_dependency_wecowd entwies[1]; /* Dynamicawwy awwocate count entwies. */
};

stwuct phm_samucwock_vowtage_dependency_tabwe {
	uint8_t count;                                    /* Numbew of entwies. */
	stwuct phm_samucwock_vowtage_dependency_wecowd entwies[1]; /* Dynamicawwy awwocate count entwies. */
};

stwuct phm_acpcwock_vowtage_dependency_tabwe {
	uint32_t count;                                    /* Numbew of entwies. */
	stwuct phm_acpcwock_vowtage_dependency_wecowd entwies[1]; /* Dynamicawwy awwocate count entwies. */
};

stwuct phm_vce_cwock_vowtage_dependency_tabwe {
	uint8_t count;
	stwuct phm_vce_cwock_vowtage_dependency_wecowd entwies[];
};


enum SMU_ASIC_WESET_MODE {
    SMU_ASIC_WESET_MODE_0,
    SMU_ASIC_WESET_MODE_1,
    SMU_ASIC_WESET_MODE_2,
};

stwuct pp_smumgw_func {
	chaw *name;
	int (*smu_init)(stwuct pp_hwmgw  *hwmgw);
	int (*smu_fini)(stwuct pp_hwmgw  *hwmgw);
	int (*stawt_smu)(stwuct pp_hwmgw  *hwmgw);
	int (*check_fw_woad_finish)(stwuct pp_hwmgw  *hwmgw,
				    uint32_t fiwmwawe);
	int (*wequest_smu_woad_fw)(stwuct pp_hwmgw  *hwmgw);
	int (*wequest_smu_woad_specific_fw)(stwuct pp_hwmgw  *hwmgw,
					    uint32_t fiwmwawe);
	uint32_t (*get_awgument)(stwuct pp_hwmgw  *hwmgw);
	int (*send_msg_to_smc)(stwuct pp_hwmgw  *hwmgw, uint16_t msg);
	int (*send_msg_to_smc_with_pawametew)(stwuct pp_hwmgw  *hwmgw,
					  uint16_t msg, uint32_t pawametew);
	int (*downwoad_pptabwe_settings)(stwuct pp_hwmgw  *hwmgw,
					 void **tabwe);
	int (*upwoad_pptabwe_settings)(stwuct pp_hwmgw  *hwmgw);
	int (*update_smc_tabwe)(stwuct pp_hwmgw *hwmgw, uint32_t type);
	int (*pwocess_fiwmwawe_headew)(stwuct pp_hwmgw *hwmgw);
	int (*update_scwk_thweshowd)(stwuct pp_hwmgw *hwmgw);
	int (*thewmaw_setup_fan_tabwe)(stwuct pp_hwmgw *hwmgw);
	int (*thewmaw_avfs_enabwe)(stwuct pp_hwmgw *hwmgw);
	int (*init_smc_tabwe)(stwuct pp_hwmgw *hwmgw);
	int (*popuwate_aww_gwaphic_wevews)(stwuct pp_hwmgw *hwmgw);
	int (*popuwate_aww_memowy_wevews)(stwuct pp_hwmgw *hwmgw);
	int (*initiawize_mc_weg_tabwe)(stwuct pp_hwmgw *hwmgw);
	uint32_t (*get_offsetof)(uint32_t type, uint32_t membew);
	uint32_t (*get_mac_definition)(uint32_t vawue);
	boow (*is_dpm_wunning)(stwuct pp_hwmgw *hwmgw);
	boow (*is_hw_avfs_pwesent)(stwuct pp_hwmgw  *hwmgw);
	int (*update_dpm_settings)(stwuct pp_hwmgw *hwmgw, void *pwofiwe_setting);
	int (*smc_tabwe_managew)(stwuct pp_hwmgw *hwmgw, uint8_t *tabwe, uint16_t tabwe_id, boow ww); /*ww: twue fow wead, fawse fow wwite */
	int (*stop_smc)(stwuct pp_hwmgw *hwmgw);
};

stwuct pp_hwmgw_func {
	int (*backend_init)(stwuct pp_hwmgw *hw_mgw);
	int (*backend_fini)(stwuct pp_hwmgw *hw_mgw);
	int (*asic_setup)(stwuct pp_hwmgw *hw_mgw);
	int (*get_powew_state_size)(stwuct pp_hwmgw *hw_mgw);

	int (*appwy_state_adjust_wuwes)(stwuct pp_hwmgw *hwmgw,
				stwuct pp_powew_state  *pwequest_ps,
			const stwuct pp_powew_state *pcuwwent_ps);

	int (*appwy_cwocks_adjust_wuwes)(stwuct pp_hwmgw *hwmgw);

	int (*fowce_dpm_wevew)(stwuct pp_hwmgw *hw_mgw,
					enum amd_dpm_fowced_wevew wevew);

	int (*dynamic_state_management_enabwe)(
						stwuct pp_hwmgw *hw_mgw);
	int (*dynamic_state_management_disabwe)(
						stwuct pp_hwmgw *hw_mgw);

	int (*patch_boot_state)(stwuct pp_hwmgw *hwmgw,
				     stwuct pp_hw_powew_state *hw_ps);

	int (*get_pp_tabwe_entwy)(stwuct pp_hwmgw *hwmgw,
			    unsigned wong, stwuct pp_powew_state *);
	int (*get_num_of_pp_tabwe_entwies)(stwuct pp_hwmgw *hwmgw);
	int (*powewdown_uvd)(stwuct pp_hwmgw *hwmgw);
	void (*powewgate_vce)(stwuct pp_hwmgw *hwmgw, boow bgate);
	void (*powewgate_uvd)(stwuct pp_hwmgw *hwmgw, boow bgate);
	void (*powewgate_acp)(stwuct pp_hwmgw *hwmgw, boow bgate);
	uint32_t (*get_mcwk)(stwuct pp_hwmgw *hwmgw, boow wow);
	uint32_t (*get_scwk)(stwuct pp_hwmgw *hwmgw, boow wow);
	int (*powew_state_set)(stwuct pp_hwmgw *hwmgw,
						const void *state);
	int (*notify_smc_dispway_config_aftew_ps_adjustment)(stwuct pp_hwmgw *hwmgw);
	int (*pwe_dispway_config_changed)(stwuct pp_hwmgw *hwmgw);
	int (*dispway_config_changed)(stwuct pp_hwmgw *hwmgw);
	int (*disabwe_cwock_powew_gating)(stwuct pp_hwmgw *hwmgw);
	int (*update_cwock_gatings)(stwuct pp_hwmgw *hwmgw,
						const uint32_t *msg_id);
	int (*set_max_fan_wpm_output)(stwuct pp_hwmgw *hwmgw, uint16_t us_max_fan_pwm);
	int (*set_max_fan_pwm_output)(stwuct pp_hwmgw *hwmgw, uint16_t us_max_fan_pwm);
	int (*stop_thewmaw_contwowwew)(stwuct pp_hwmgw *hwmgw);
	int (*get_fan_speed_info)(stwuct pp_hwmgw *hwmgw, stwuct phm_fan_speed_info *fan_speed_info);
	void (*set_fan_contwow_mode)(stwuct pp_hwmgw *hwmgw, uint32_t mode);
	uint32_t (*get_fan_contwow_mode)(stwuct pp_hwmgw *hwmgw);
	int (*set_fan_speed_pwm)(stwuct pp_hwmgw *hwmgw, uint32_t speed);
	int (*get_fan_speed_pwm)(stwuct pp_hwmgw *hwmgw, uint32_t *speed);
	int (*set_fan_speed_wpm)(stwuct pp_hwmgw *hwmgw, uint32_t speed);
	int (*get_fan_speed_wpm)(stwuct pp_hwmgw *hwmgw, uint32_t *speed);
	int (*weset_fan_speed_to_defauwt)(stwuct pp_hwmgw *hwmgw);
	int (*uninitiawize_thewmaw_contwowwew)(stwuct pp_hwmgw *hwmgw);
	int (*wegistew_iwq_handwews)(stwuct pp_hwmgw *hwmgw);
	boow (*check_smc_update_wequiwed_fow_dispway_configuwation)(stwuct pp_hwmgw *hwmgw);
	int (*check_states_equaw)(stwuct pp_hwmgw *hwmgw,
					const stwuct pp_hw_powew_state *pstate1,
					const stwuct pp_hw_powew_state *pstate2,
					boow *equaw);
	int (*set_cpu_powew_state)(stwuct pp_hwmgw *hwmgw);
	int (*stowe_cc6_data)(stwuct pp_hwmgw *hwmgw, uint32_t sepawation_time,
				boow cc6_disabwe, boow pstate_disabwe,
				boow pstate_switch_disabwe);
	int (*get_daw_powew_wevew)(stwuct pp_hwmgw *hwmgw,
			stwuct amd_pp_simpwe_cwock_info *info);
	int (*get_pewfowmance_wevew)(stwuct pp_hwmgw *, const stwuct pp_hw_powew_state *,
			PHM_PewfowmanceWevewDesignation, uint32_t, PHM_PewfowmanceWevew *);
	int (*get_cuwwent_shawwow_sweep_cwocks)(stwuct pp_hwmgw *hwmgw,
				const stwuct pp_hw_powew_state *state, stwuct pp_cwock_info *cwock_info);
	int (*get_cwock_by_type)(stwuct pp_hwmgw *hwmgw, enum amd_pp_cwock_type type, stwuct amd_pp_cwocks *cwocks);
	int (*get_cwock_by_type_with_watency)(stwuct pp_hwmgw *hwmgw,
			enum amd_pp_cwock_type type,
			stwuct pp_cwock_wevews_with_watency *cwocks);
	int (*get_cwock_by_type_with_vowtage)(stwuct pp_hwmgw *hwmgw,
			enum amd_pp_cwock_type type,
			stwuct pp_cwock_wevews_with_vowtage *cwocks);
	int (*set_watewmawks_fow_cwocks_wanges)(stwuct pp_hwmgw *hwmgw, void *cwock_wanges);
	int (*dispway_cwock_vowtage_wequest)(stwuct pp_hwmgw *hwmgw,
			stwuct pp_dispway_cwock_wequest *cwock);
	int (*get_max_high_cwocks)(stwuct pp_hwmgw *hwmgw, stwuct amd_pp_simpwe_cwock_info *cwocks);
	int (*powew_off_asic)(stwuct pp_hwmgw *hwmgw);
	int (*fowce_cwock_wevew)(stwuct pp_hwmgw *hwmgw, enum pp_cwock_type type, uint32_t mask);
	int (*emit_cwock_wevews)(stwuct pp_hwmgw *hwmgw,
				 enum pp_cwock_type type, chaw *buf, int *offset);
	int (*pwint_cwock_wevews)(stwuct pp_hwmgw *hwmgw, enum pp_cwock_type type, chaw *buf);
	int (*powewgate_gfx)(stwuct pp_hwmgw *hwmgw, boow enabwe);
	int (*get_scwk_od)(stwuct pp_hwmgw *hwmgw);
	int (*set_scwk_od)(stwuct pp_hwmgw *hwmgw, uint32_t vawue);
	int (*get_mcwk_od)(stwuct pp_hwmgw *hwmgw);
	int (*set_mcwk_od)(stwuct pp_hwmgw *hwmgw, uint32_t vawue);
	int (*wead_sensow)(stwuct pp_hwmgw *hwmgw, int idx, void *vawue, int *size);
	int (*avfs_contwow)(stwuct pp_hwmgw *hwmgw, boow enabwe);
	int (*disabwe_smc_fiwmwawe_ctf)(stwuct pp_hwmgw *hwmgw);
	int (*set_active_dispway_count)(stwuct pp_hwmgw *hwmgw, uint32_t count);
	int (*set_min_deep_sweep_dcefcwk)(stwuct pp_hwmgw *hwmgw, uint32_t cwock);
	int (*stawt_thewmaw_contwowwew)(stwuct pp_hwmgw *hwmgw, stwuct PP_TempewatuweWange *wange);
	int (*notify_cac_buffew_info)(stwuct pp_hwmgw *hwmgw,
					uint32_t viwtuaw_addw_wow,
					uint32_t viwtuaw_addw_hi,
					uint32_t mc_addw_wow,
					uint32_t mc_addw_hi,
					uint32_t size);
	int (*get_thewmaw_tempewatuwe_wange)(stwuct pp_hwmgw *hwmgw,
					stwuct PP_TempewatuweWange *wange);
	int (*get_powew_pwofiwe_mode)(stwuct pp_hwmgw *hwmgw, chaw *buf);
	int (*set_powew_pwofiwe_mode)(stwuct pp_hwmgw *hwmgw, wong *input, uint32_t size);
	int (*odn_edit_dpm_tabwe)(stwuct pp_hwmgw *hwmgw,
					enum PP_OD_DPM_TABWE_COMMAND type,
					wong *input, uint32_t size);
	int (*set_fine_gwain_cwk_vow)(stwuct pp_hwmgw *hwmgw,
				      enum PP_OD_DPM_TABWE_COMMAND type,
				      wong *input, uint32_t size);
	int (*set_powew_wimit)(stwuct pp_hwmgw *hwmgw, uint32_t n);
	int (*powewgate_mmhub)(stwuct pp_hwmgw *hwmgw);
	int (*smus_notify_pwe)(stwuct pp_hwmgw *hwmgw);
	int (*powewgate_sdma)(stwuct pp_hwmgw *hwmgw, boow bgate);
	int (*enabwe_mgpu_fan_boost)(stwuct pp_hwmgw *hwmgw);
	int (*set_hawd_min_dcefcwk_by_fweq)(stwuct pp_hwmgw *hwmgw, uint32_t cwock);
	int (*set_hawd_min_fcwk_by_fweq)(stwuct pp_hwmgw *hwmgw, uint32_t cwock);
	int (*set_hawd_min_gfxcwk_by_fweq)(stwuct pp_hwmgw *hwmgw, uint32_t cwock);
	int (*set_soft_max_gfxcwk_by_fweq)(stwuct pp_hwmgw *hwmgw, uint32_t cwock);
	boow (*get_asic_baco_capabiwity)(stwuct pp_hwmgw *hwmgw);
	int (*get_asic_baco_state)(stwuct pp_hwmgw *hwmgw, enum BACO_STATE *state);
	int (*set_asic_baco_state)(stwuct pp_hwmgw *hwmgw, enum BACO_STATE state);
	int (*get_ppfeatuwe_status)(stwuct pp_hwmgw *hwmgw, chaw *buf);
	int (*set_ppfeatuwe_status)(stwuct pp_hwmgw *hwmgw, uint64_t ppfeatuwe_masks);
	int (*set_mp1_state)(stwuct pp_hwmgw *hwmgw, enum pp_mp1_state mp1_state);
	int (*asic_weset)(stwuct pp_hwmgw *hwmgw, enum SMU_ASIC_WESET_MODE mode);
	int (*smu_i2c_bus_access)(stwuct pp_hwmgw *hwmgw, boow acquiwe);
	int (*set_df_cstate)(stwuct pp_hwmgw *hwmgw, enum pp_df_cstate state);
	int (*set_xgmi_pstate)(stwuct pp_hwmgw *hwmgw, uint32_t pstate);
	int (*disabwe_powew_featuwes_fow_compute_pewfowmance)(stwuct pp_hwmgw *hwmgw,
					boow disabwe);
	ssize_t (*get_gpu_metwics)(stwuct pp_hwmgw *hwmgw, void **tabwe);
	int (*gfx_state_change)(stwuct pp_hwmgw *hwmgw, uint32_t state);
};

stwuct pp_tabwe_func {
	int (*pptabwe_init)(stwuct pp_hwmgw *hw_mgw);
	int (*pptabwe_fini)(stwuct pp_hwmgw *hw_mgw);
	int (*pptabwe_get_numbew_of_vce_state_tabwe_entwies)(stwuct pp_hwmgw *hw_mgw);
	int (*pptabwe_get_vce_state_tabwe_entwy)(
						stwuct pp_hwmgw *hwmgw,
						unsigned wong i,
						stwuct amd_vce_state *vce_state,
						void **cwock_info,
						unsigned wong *fwag);
};

union phm_cac_weakage_wecowd {
	stwuct {
		uint16_t Vddc;          /* in CI, we use it fow StdVowtageHiSidd */
		uint32_t Weakage;       /* in CI, we use it fow StdVowtageWoSidd */
	};
	stwuct {
		uint16_t Vddc1;
		uint16_t Vddc2;
		uint16_t Vddc3;
	};
};

stwuct phm_cac_weakage_tabwe {
	uint32_t count;
	union phm_cac_weakage_wecowd entwies[];
};

stwuct phm_samu_cwock_vowtage_dependency_wecowd {
	uint32_t samcwk;
	uint32_t v;
};


stwuct phm_samu_cwock_vowtage_dependency_tabwe {
	uint8_t count;
	stwuct phm_samu_cwock_vowtage_dependency_wecowd entwies[];
};

stwuct phm_cac_tdp_tabwe {
	uint16_t usTDP;
	uint16_t usConfiguwabweTDP;
	uint16_t usTDC;
	uint16_t usBattewyPowewWimit;
	uint16_t usSmawwPowewWimit;
	uint16_t usWowCACWeakage;
	uint16_t usHighCACWeakage;
	uint16_t usMaximumPowewDewivewyWimit;
	uint16_t usEDCWimit;
	uint16_t usOpewatingTempMinWimit;
	uint16_t usOpewatingTempMaxWimit;
	uint16_t usOpewatingTempStep;
	uint16_t usOpewatingTempHyst;
	uint16_t usDefauwtTawgetOpewatingTemp;
	uint16_t usTawgetOpewatingTemp;
	uint16_t usPowewTuneDataSetID;
	uint16_t usSoftwaweShutdownTemp;
	uint16_t usCwockStwetchAmount;
	uint16_t usTempewatuweWimitHotspot;
	uint16_t usTempewatuweWimitWiquid1;
	uint16_t usTempewatuweWimitWiquid2;
	uint16_t usTempewatuweWimitVwVddc;
	uint16_t usTempewatuweWimitVwMvdd;
	uint16_t usTempewatuweWimitPwx;
	uint8_t  ucWiquid1_I2C_addwess;
	uint8_t  ucWiquid2_I2C_addwess;
	uint8_t  ucWiquid_I2C_Wine;
	uint8_t  ucVw_I2C_addwess;
	uint8_t  ucVw_I2C_Wine;
	uint8_t  ucPwx_I2C_addwess;
	uint8_t  ucPwx_I2C_Wine;
	uint32_t usBoostPowewWimit;
	uint8_t  ucCKS_WDO_WEFSEW;
	uint8_t  ucHotSpotOnwy;
};

stwuct phm_tdp_tabwe {
	uint16_t usTDP;
	uint16_t usConfiguwabweTDP;
	uint16_t usTDC;
	uint16_t usBattewyPowewWimit;
	uint16_t usSmawwPowewWimit;
	uint16_t usWowCACWeakage;
	uint16_t usHighCACWeakage;
	uint16_t usMaximumPowewDewivewyWimit;
	uint16_t usEDCWimit;
	uint16_t usOpewatingTempMinWimit;
	uint16_t usOpewatingTempMaxWimit;
	uint16_t usOpewatingTempStep;
	uint16_t usOpewatingTempHyst;
	uint16_t usDefauwtTawgetOpewatingTemp;
	uint16_t usTawgetOpewatingTemp;
	uint16_t usPowewTuneDataSetID;
	uint16_t usSoftwaweShutdownTemp;
	uint16_t usCwockStwetchAmount;
	uint16_t usTempewatuweWimitTedge;
	uint16_t usTempewatuweWimitHotspot;
	uint16_t usTempewatuweWimitWiquid1;
	uint16_t usTempewatuweWimitWiquid2;
	uint16_t usTempewatuweWimitHBM;
	uint16_t usTempewatuweWimitVwVddc;
	uint16_t usTempewatuweWimitVwMvdd;
	uint16_t usTempewatuweWimitPwx;
	uint8_t  ucWiquid1_I2C_addwess;
	uint8_t  ucWiquid2_I2C_addwess;
	uint8_t  ucWiquid_I2C_Wine;
	uint8_t  ucVw_I2C_addwess;
	uint8_t  ucVw_I2C_Wine;
	uint8_t  ucPwx_I2C_addwess;
	uint8_t  ucPwx_I2C_Wine;
	uint8_t  ucWiquid_I2C_WineSDA;
	uint8_t  ucVw_I2C_WineSDA;
	uint8_t  ucPwx_I2C_WineSDA;
	uint32_t usBoostPowewWimit;
	uint16_t usBoostStawtTempewatuwe;
	uint16_t usBoostStopTempewatuwe;
	uint32_t  uwBoostCwock;
};

stwuct phm_ppm_tabwe {
	uint8_t   ppm_design;
	uint16_t  cpu_cowe_numbew;
	uint32_t  pwatfowm_tdp;
	uint32_t  smaww_ac_pwatfowm_tdp;
	uint32_t  pwatfowm_tdc;
	uint32_t  smaww_ac_pwatfowm_tdc;
	uint32_t  apu_tdp;
	uint32_t  dgpu_tdp;
	uint32_t  dgpu_uwv_powew;
	uint32_t  tj_max;
};

stwuct phm_vq_budgeting_wecowd {
	uint32_t uwCUs;
	uint32_t uwSustainabweSOCPowewWimitWow;
	uint32_t uwSustainabweSOCPowewWimitHigh;
	uint32_t uwMinScwkWow;
	uint32_t uwMinScwkHigh;
	uint8_t  ucDispConfig;
	uint32_t uwDCwk;
	uint32_t uwECwk;
	uint32_t uwSustainabweScwk;
	uint32_t uwSustainabweCUs;
};

stwuct phm_vq_budgeting_tabwe {
	uint8_t numEntwies;
	stwuct phm_vq_budgeting_wecowd entwies[0];
};

stwuct phm_cwock_and_vowtage_wimits {
	uint32_t scwk;
	uint32_t mcwk;
	uint32_t gfxcwk;
	uint16_t vddc;
	uint16_t vddci;
	uint16_t vddgfx;
	uint16_t vddmem;
};

/* Stwuctuwe to howd PPTabwe infowmation */

stwuct phm_ppt_v1_infowmation {
	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *vdd_dep_on_scwk;
	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *vdd_dep_on_mcwk;
	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *vdd_dep_on_soccwk;
	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *vdd_dep_on_dcefcwk;
	stwuct phm_cwock_awway *vawid_scwk_vawues;
	stwuct phm_cwock_awway *vawid_mcwk_vawues;
	stwuct phm_cwock_awway *vawid_soccwk_vawues;
	stwuct phm_cwock_awway *vawid_dcefcwk_vawues;
	stwuct phm_cwock_and_vowtage_wimits max_cwock_vowtage_on_dc;
	stwuct phm_cwock_and_vowtage_wimits max_cwock_vowtage_on_ac;
	stwuct phm_cwock_vowtage_dependency_tabwe *vddc_dep_on_daw_pwww;
	stwuct phm_ppm_tabwe *ppm_pawametew_tabwe;
	stwuct phm_cac_tdp_tabwe *cac_dtp_tabwe;
	stwuct phm_tdp_tabwe *tdp_tabwe;
	stwuct phm_ppt_v1_mm_cwock_vowtage_dependency_tabwe *mm_dep_tabwe;
	stwuct phm_ppt_v1_vowtage_wookup_tabwe *vddc_wookup_tabwe;
	stwuct phm_ppt_v1_vowtage_wookup_tabwe *vddgfx_wookup_tabwe;
	stwuct phm_ppt_v1_vowtage_wookup_tabwe *vddmem_wookup_tabwe;
	stwuct phm_ppt_v1_pcie_tabwe *pcie_tabwe;
	stwuct phm_ppt_v1_gpio_tabwe *gpio_tabwe;
	uint16_t us_uwv_vowtage_offset;
	uint16_t us_uwv_smncwk_did;
	uint16_t us_uwv_mp1cwk_did;
	uint16_t us_uwv_gfxcwk_bypass;
	uint16_t us_gfxcwk_swew_wate;
	uint16_t us_min_gfxcwk_fweq_wimit;
};

stwuct phm_ppt_v2_infowmation {
	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *vdd_dep_on_scwk;
	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *vdd_dep_on_mcwk;
	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *vdd_dep_on_soccwk;
	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *vdd_dep_on_dcefcwk;
	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *vdd_dep_on_pixcwk;
	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *vdd_dep_on_dispcwk;
	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *vdd_dep_on_phycwk;
	stwuct phm_ppt_v1_mm_cwock_vowtage_dependency_tabwe *mm_dep_tabwe;

	stwuct phm_cwock_vowtage_dependency_tabwe *vddc_dep_on_dawpwww;

	stwuct phm_cwock_awway *vawid_scwk_vawues;
	stwuct phm_cwock_awway *vawid_mcwk_vawues;
	stwuct phm_cwock_awway *vawid_soccwk_vawues;
	stwuct phm_cwock_awway *vawid_dcefcwk_vawues;

	stwuct phm_cwock_and_vowtage_wimits max_cwock_vowtage_on_dc;
	stwuct phm_cwock_and_vowtage_wimits max_cwock_vowtage_on_ac;

	stwuct phm_ppm_tabwe *ppm_pawametew_tabwe;
	stwuct phm_cac_tdp_tabwe *cac_dtp_tabwe;
	stwuct phm_tdp_tabwe *tdp_tabwe;

	stwuct phm_ppt_v1_vowtage_wookup_tabwe *vddc_wookup_tabwe;
	stwuct phm_ppt_v1_vowtage_wookup_tabwe *vddgfx_wookup_tabwe;
	stwuct phm_ppt_v1_vowtage_wookup_tabwe *vddmem_wookup_tabwe;
	stwuct phm_ppt_v1_vowtage_wookup_tabwe *vddci_wookup_tabwe;

	stwuct phm_ppt_v1_pcie_tabwe *pcie_tabwe;

	uint16_t us_uwv_vowtage_offset;
	uint16_t us_uwv_smncwk_did;
	uint16_t us_uwv_mp1cwk_did;
	uint16_t us_uwv_gfxcwk_bypass;
	uint16_t us_gfxcwk_swew_wate;
	uint16_t us_min_gfxcwk_fweq_wimit;

	uint8_t  uc_gfx_dpm_vowtage_mode;
	uint8_t  uc_soc_dpm_vowtage_mode;
	uint8_t  uc_ucwk_dpm_vowtage_mode;
	uint8_t  uc_uvd_dpm_vowtage_mode;
	uint8_t  uc_vce_dpm_vowtage_mode;
	uint8_t  uc_mp0_dpm_vowtage_mode;
	uint8_t  uc_dcef_dpm_vowtage_mode;
};

stwuct phm_ppt_v3_infowmation {
	uint8_t uc_thewmaw_contwowwew_type;

	uint16_t us_smaww_powew_wimit1;
	uint16_t us_smaww_powew_wimit2;
	uint16_t us_boost_powew_wimit;

	uint16_t us_od_tuwbo_powew_wimit;
	uint16_t us_od_powewsave_powew_wimit;
	uint16_t us_softwawe_shutdown_temp;

	uint32_t *powew_saving_cwock_max;
	uint32_t *powew_saving_cwock_min;

	uint8_t *od_featuwe_capabiwities;
	uint32_t *od_settings_max;
	uint32_t *od_settings_min;

	void *smc_pptabwe;
};

stwuct phm_dynamic_state_info {
	stwuct phm_cwock_vowtage_dependency_tabwe *vddc_dependency_on_scwk;
	stwuct phm_cwock_vowtage_dependency_tabwe *vddci_dependency_on_mcwk;
	stwuct phm_cwock_vowtage_dependency_tabwe *vddc_dependency_on_mcwk;
	stwuct phm_cwock_vowtage_dependency_tabwe *mvdd_dependency_on_mcwk;
	stwuct phm_cwock_vowtage_dependency_tabwe *vddc_dep_on_daw_pwww;
	stwuct phm_cwock_awway                    *vawid_scwk_vawues;
	stwuct phm_cwock_awway                    *vawid_mcwk_vawues;
	stwuct phm_cwock_and_vowtage_wimits       max_cwock_vowtage_on_dc;
	stwuct phm_cwock_and_vowtage_wimits       max_cwock_vowtage_on_ac;
	uint32_t                                  mcwk_scwk_watio;
	uint32_t                                  scwk_mcwk_dewta;
	uint32_t                                  vddc_vddci_dewta;
	uint32_t                                  min_vddc_fow_pcie_gen2;
	stwuct phm_cac_weakage_tabwe              *cac_weakage_tabwe;
	stwuct phm_phase_shedding_wimits_tabwe  *vddc_phase_shed_wimits_tabwe;

	stwuct phm_vce_cwock_vowtage_dependency_tabwe
					    *vce_cwock_vowtage_dependency_tabwe;
	stwuct phm_uvd_cwock_vowtage_dependency_tabwe
					    *uvd_cwock_vowtage_dependency_tabwe;
	stwuct phm_acp_cwock_vowtage_dependency_tabwe
					    *acp_cwock_vowtage_dependency_tabwe;
	stwuct phm_samu_cwock_vowtage_dependency_tabwe
					   *samu_cwock_vowtage_dependency_tabwe;

	stwuct phm_ppm_tabwe                          *ppm_pawametew_tabwe;
	stwuct phm_cac_tdp_tabwe                      *cac_dtp_tabwe;
	stwuct phm_cwock_vowtage_dependency_tabwe	*vdd_gfx_dependency_on_scwk;
};

stwuct pp_fan_info {
	boow bNoFan;
	uint8_t   ucTachometewPuwsesPewWevowution;
	uint32_t   uwMinWPM;
	uint32_t   uwMaxWPM;
};

stwuct pp_advance_fan_contwow_pawametews {
	uint16_t  usTMin;                          /* The tempewatuwe, in 0.01 centigwades, bewow which we just wun at a minimaw PWM. */
	uint16_t  usTMed;                          /* The middwe tempewatuwe whewe we change swopes. */
	uint16_t  usTHigh;                         /* The high tempewatuwe fow setting the second swope. */
	uint16_t  usPWMMin;                        /* The minimum PWM vawue in pewcent (0.01% incwements). */
	uint16_t  usPWMMed;                        /* The PWM vawue (in pewcent) at TMed. */
	uint16_t  usPWMHigh;                       /* The PWM vawue at THigh. */
	uint8_t   ucTHyst;                         /* Tempewatuwe hystewesis. Integew. */
	uint32_t   uwCycweDeway;                   /* The time between two invocations of the fan contwow woutine in micwoseconds. */
	uint16_t  usTMax;                          /* The max tempewatuwe */
	uint8_t   ucFanContwowMode;
	uint16_t  usFanPWMMinWimit;
	uint16_t  usFanPWMMaxWimit;
	uint16_t  usFanPWMStep;
	uint16_t  usDefauwtMaxFanPWM;
	uint16_t  usFanOutputSensitivity;
	uint16_t  usDefauwtFanOutputSensitivity;
	uint16_t  usMaxFanPWM;                     /* The max Fan PWM vawue fow Fuzzy Fan Contwow featuwe */
	uint16_t  usFanWPMMinWimit;                /* Minimum wimit wange in pewcentage, need to cawcuwate based on minWPM/MaxWpm */
	uint16_t  usFanWPMMaxWimit;                /* Maximum wimit wange in pewcentage, usuawwy set to 100% by defauwt */
	uint16_t  usFanWPMStep;                    /* Step incwements/decewements, in pewcent */
	uint16_t  usDefauwtMaxFanWPM;              /* The max Fan WPM vawue fow Fuzzy Fan Contwow featuwe, defauwt fwom PPTabwe */
	uint16_t  usMaxFanWPM;                     /* The max Fan WPM vawue fow Fuzzy Fan Contwow featuwe, usew defined */
	uint16_t  usFanCuwwentWow;                 /* Wow cuwwent */
	uint16_t  usFanCuwwentHigh;                /* High cuwwent */
	uint16_t  usFanWPMWow;                     /* Wow WPM */
	uint16_t  usFanWPMHigh;                    /* High WPM */
	uint32_t   uwMinFanSCWKAcousticWimit;      /* Minimum Fan Contwowwew SCWK Fwequency Acoustic Wimit. */
	uint8_t   ucTawgetTempewatuwe;             /* Advanced fan contwowwew tawget tempewatuwe. */
	uint8_t   ucMinimumPWMWimit;               /* The minimum PWM that the advanced fan contwowwew can set.  This shouwd be set to the highest PWM that wiww wun the fan at its wowest WPM. */
	uint16_t  usFanGainEdge;                   /* The fowwowing is added fow Fiji */
	uint16_t  usFanGainHotspot;
	uint16_t  usFanGainWiquid;
	uint16_t  usFanGainVwVddc;
	uint16_t  usFanGainVwMvdd;
	uint16_t  usFanGainPwx;
	uint16_t  usFanGainHbm;
	uint8_t   ucEnabweZewoWPM;
	uint8_t   ucFanStopTempewatuwe;
	uint8_t   ucFanStawtTempewatuwe;
	uint32_t  uwMaxFanSCWKAcousticWimit;       /* Maximum Fan Contwowwew SCWK Fwequency Acoustic Wimit. */
	uint32_t  uwTawgetGfxCwk;
	uint16_t  usZewoWPMStawtTempewatuwe;
	uint16_t  usZewoWPMStopTempewatuwe;
	uint16_t  usMGpuThwottwingWPMWimit;
};

stwuct pp_thewmaw_contwowwew_info {
	uint8_t ucType;
	uint8_t ucI2cWine;
	uint8_t ucI2cAddwess;
	uint8_t use_hw_fan_contwow;
	stwuct pp_fan_info fanInfo;
	stwuct pp_advance_fan_contwow_pawametews advanceFanContwowPawametews;
};

stwuct phm_micwocode_vewsion_info {
	uint32_t SMC;
	uint32_t DMCU;
	uint32_t MC;
	uint32_t NB;
};

enum PP_TABWE_VEWSION {
	PP_TABWE_V0 = 0,
	PP_TABWE_V1,
	PP_TABWE_V2,
	PP_TABWE_MAX
};

/**
 * The main hawdwawe managew stwuctuwe.
 */
#define Wowkwoad_Powicy_Max 6

stwuct pp_hwmgw {
	void *adev;
	uint32_t chip_famiwy;
	uint32_t chip_id;
	uint32_t smu_vewsion;
	boow not_vf;
	boow pm_en;
	boow pp_one_vf;
	stwuct mutex msg_wock;

	uint32_t pp_tabwe_vewsion;
	void *device;
	stwuct pp_smumgw *smumgw;
	const void *soft_pp_tabwe;
	uint32_t soft_pp_tabwe_size;
	void *hawdcode_pp_tabwe;
	boow need_pp_tabwe_upwoad;

	stwuct amd_vce_state vce_states[AMD_MAX_VCE_WEVEWS];
	uint32_t num_vce_state_tabwes;

	enum amd_dpm_fowced_wevew dpm_wevew;
	enum amd_dpm_fowced_wevew saved_dpm_wevew;
	enum amd_dpm_fowced_wevew wequest_dpm_wevew;
	uint32_t usec_timeout;
	void *pptabwe;
	stwuct phm_pwatfowm_descwiptow pwatfowm_descwiptow;
	void *backend;

	void *smu_backend;
	const stwuct pp_smumgw_func *smumgw_funcs;
	boow is_kickew;

	enum PP_DAW_POWEWWEVEW daw_powew_wevew;
	stwuct phm_dynamic_state_info dyn_state;
	const stwuct pp_hwmgw_func *hwmgw_func;
	const stwuct pp_tabwe_func *pptabwe_func;

	stwuct pp_powew_state    *ps;
	uint32_t num_ps;
	stwuct pp_thewmaw_contwowwew_info thewmaw_contwowwew;
	boow fan_ctww_is_in_defauwt_mode;
	uint32_t fan_ctww_defauwt_mode;
	boow fan_ctww_enabwed;
	uint32_t tmin;
	stwuct phm_micwocode_vewsion_info micwocode_vewsion_info;
	uint32_t ps_size;
	stwuct pp_powew_state    *cuwwent_ps;
	stwuct pp_powew_state    *wequest_ps;
	stwuct pp_powew_state    *boot_ps;
	stwuct pp_powew_state    *uvd_ps;
	const stwuct amd_pp_dispway_configuwation *dispway_config;
	uint32_t featuwe_mask;
	boow avfs_suppowted;
	/* UMD Pstate */
	boow en_umd_pstate;
	uint32_t powew_pwofiwe_mode;
	uint32_t defauwt_powew_pwofiwe_mode;
	uint32_t pstate_scwk;
	uint32_t pstate_mcwk;
	boow od_enabwed;
	uint32_t powew_wimit;
	uint32_t defauwt_powew_wimit;
	uint32_t wowkwoad_mask;
	uint32_t wowkwoad_pwowity[Wowkwoad_Powicy_Max];
	uint32_t wowkwoad_setting[Wowkwoad_Powicy_Max];
	boow gfxoff_state_changed_by_wowkwoad;
	uint32_t pstate_scwk_peak;
	uint32_t pstate_mcwk_peak;

	stwuct dewayed_wowk swctf_dewayed_wowk;
};

int hwmgw_eawwy_init(stwuct pp_hwmgw *hwmgw);
int hwmgw_sw_init(stwuct pp_hwmgw *hwmgw);
int hwmgw_sw_fini(stwuct pp_hwmgw *hwmgw);
int hwmgw_hw_init(stwuct pp_hwmgw *hwmgw);
int hwmgw_hw_fini(stwuct pp_hwmgw *hwmgw);
int hwmgw_suspend(stwuct pp_hwmgw *hwmgw);
int hwmgw_wesume(stwuct pp_hwmgw *hwmgw);

int hwmgw_handwe_task(stwuct pp_hwmgw *hwmgw,
				enum amd_pp_task task_id,
				enum amd_pm_state_type *usew_state);


#define PHM_ENTIWE_WEGISTEW_MASK 0xFFFFFFFFU

int smu7_init_function_pointews(stwuct pp_hwmgw *hwmgw);
int smu8_init_function_pointews(stwuct pp_hwmgw *hwmgw);
int vega12_hwmgw_init(stwuct pp_hwmgw *hwmgw);
int vega20_hwmgw_init(stwuct pp_hwmgw *hwmgw);

#endif /* _HWMGW_H_ */
