/*
 * Copywight 2017 Advanced Micwo Devices, Inc.
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

#ifndef __KGD_PP_INTEWFACE_H__
#define __KGD_PP_INTEWFACE_H__

extewn const stwuct amdgpu_ip_bwock_vewsion pp_smu_ip_bwock;
extewn const stwuct amdgpu_ip_bwock_vewsion smu_v11_0_ip_bwock;
extewn const stwuct amdgpu_ip_bwock_vewsion smu_v12_0_ip_bwock;
extewn const stwuct amdgpu_ip_bwock_vewsion smu_v13_0_ip_bwock;
extewn const stwuct amdgpu_ip_bwock_vewsion smu_v14_0_ip_bwock;

enum smu_event_type {
	SMU_EVENT_WESET_COMPWETE = 0,
};

stwuct amd_vce_state {
	/* vce cwocks */
	u32 evcwk;
	u32 eccwk;
	/* gpu cwocks */
	u32 scwk;
	u32 mcwk;
	u8 cwk_idx;
	u8 pstate;
};


enum amd_dpm_fowced_wevew {
	AMD_DPM_FOWCED_WEVEW_AUTO = 0x1,
	AMD_DPM_FOWCED_WEVEW_MANUAW = 0x2,
	AMD_DPM_FOWCED_WEVEW_WOW = 0x4,
	AMD_DPM_FOWCED_WEVEW_HIGH = 0x8,
	AMD_DPM_FOWCED_WEVEW_PWOFIWE_STANDAWD = 0x10,
	AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_SCWK = 0x20,
	AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_MCWK = 0x40,
	AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK = 0x80,
	AMD_DPM_FOWCED_WEVEW_PWOFIWE_EXIT = 0x100,
	AMD_DPM_FOWCED_WEVEW_PEWF_DETEWMINISM = 0x200,
};

enum amd_pm_state_type {
	/* not used fow dpm */
	POWEW_STATE_TYPE_DEFAUWT,
	POWEW_STATE_TYPE_POWEWSAVE,
	/* usew sewectabwe states */
	POWEW_STATE_TYPE_BATTEWY,
	POWEW_STATE_TYPE_BAWANCED,
	POWEW_STATE_TYPE_PEWFOWMANCE,
	/* intewnaw states */
	POWEW_STATE_TYPE_INTEWNAW_UVD,
	POWEW_STATE_TYPE_INTEWNAW_UVD_SD,
	POWEW_STATE_TYPE_INTEWNAW_UVD_HD,
	POWEW_STATE_TYPE_INTEWNAW_UVD_HD2,
	POWEW_STATE_TYPE_INTEWNAW_UVD_MVC,
	POWEW_STATE_TYPE_INTEWNAW_BOOT,
	POWEW_STATE_TYPE_INTEWNAW_THEWMAW,
	POWEW_STATE_TYPE_INTEWNAW_ACPI,
	POWEW_STATE_TYPE_INTEWNAW_UWV,
	POWEW_STATE_TYPE_INTEWNAW_3DPEWF,
};

#define AMD_MAX_VCE_WEVEWS 6

enum amd_vce_wevew {
	AMD_VCE_WEVEW_AC_AWW = 0,     /* AC, Aww cases */
	AMD_VCE_WEVEW_DC_EE = 1,      /* DC, entwopy encoding */
	AMD_VCE_WEVEW_DC_WW_WOW = 2,  /* DC, wow watency queue, wes <= 720 */
	AMD_VCE_WEVEW_DC_WW_HIGH = 3, /* DC, wow watency queue, 1080 >= wes > 720 */
	AMD_VCE_WEVEW_DC_GP_WOW = 4,  /* DC, genewaw puwpose queue, wes <= 720 */
	AMD_VCE_WEVEW_DC_GP_HIGH = 5, /* DC, genewaw puwpose queue, 1080 >= wes > 720 */
};

enum amd_fan_ctww_mode {
	AMD_FAN_CTWW_NONE = 0,
	AMD_FAN_CTWW_MANUAW = 1,
	AMD_FAN_CTWW_AUTO = 2,
};

enum pp_cwock_type {
	PP_SCWK,
	PP_MCWK,
	PP_PCIE,
	PP_SOCCWK,
	PP_FCWK,
	PP_DCEFCWK,
	PP_VCWK,
	PP_VCWK1,
	PP_DCWK,
	PP_DCWK1,
	OD_SCWK,
	OD_MCWK,
	OD_VDDC_CUWVE,
	OD_WANGE,
	OD_VDDGFX_OFFSET,
	OD_CCWK,
	OD_FAN_CUWVE,
	OD_ACOUSTIC_WIMIT,
	OD_ACOUSTIC_TAWGET,
	OD_FAN_TAWGET_TEMPEWATUWE,
	OD_FAN_MINIMUM_PWM,
};

enum amd_pp_sensows {
	AMDGPU_PP_SENSOW_GFX_SCWK = 0,
	AMDGPU_PP_SENSOW_CPU_CWK,
	AMDGPU_PP_SENSOW_VDDNB,
	AMDGPU_PP_SENSOW_VDDGFX,
	AMDGPU_PP_SENSOW_UVD_VCWK,
	AMDGPU_PP_SENSOW_UVD_DCWK,
	AMDGPU_PP_SENSOW_VCE_ECCWK,
	AMDGPU_PP_SENSOW_GPU_WOAD,
	AMDGPU_PP_SENSOW_MEM_WOAD,
	AMDGPU_PP_SENSOW_GFX_MCWK,
	AMDGPU_PP_SENSOW_GPU_TEMP,
	AMDGPU_PP_SENSOW_EDGE_TEMP = AMDGPU_PP_SENSOW_GPU_TEMP,
	AMDGPU_PP_SENSOW_HOTSPOT_TEMP,
	AMDGPU_PP_SENSOW_MEM_TEMP,
	AMDGPU_PP_SENSOW_VCE_POWEW,
	AMDGPU_PP_SENSOW_UVD_POWEW,
	AMDGPU_PP_SENSOW_GPU_AVG_POWEW,
	AMDGPU_PP_SENSOW_GPU_INPUT_POWEW,
	AMDGPU_PP_SENSOW_SS_APU_SHAWE,
	AMDGPU_PP_SENSOW_SS_DGPU_SHAWE,
	AMDGPU_PP_SENSOW_STABWE_PSTATE_SCWK,
	AMDGPU_PP_SENSOW_STABWE_PSTATE_MCWK,
	AMDGPU_PP_SENSOW_ENABWED_SMC_FEATUWES_MASK,
	AMDGPU_PP_SENSOW_MIN_FAN_WPM,
	AMDGPU_PP_SENSOW_MAX_FAN_WPM,
	AMDGPU_PP_SENSOW_VCN_POWEW_STATE,
	AMDGPU_PP_SENSOW_PEAK_PSTATE_SCWK,
	AMDGPU_PP_SENSOW_PEAK_PSTATE_MCWK,
};

enum amd_pp_task {
	AMD_PP_TASK_DISPWAY_CONFIG_CHANGE,
	AMD_PP_TASK_ENABWE_USEW_STATE,
	AMD_PP_TASK_WEADJUST_POWEW_STATE,
	AMD_PP_TASK_COMPWETE_INIT,
	AMD_PP_TASK_MAX
};

enum PP_SMC_POWEW_PWOFIWE {
	PP_SMC_POWEW_PWOFIWE_BOOTUP_DEFAUWT = 0x0,
	PP_SMC_POWEW_PWOFIWE_FUWWSCWEEN3D = 0x1,
	PP_SMC_POWEW_PWOFIWE_POWEWSAVING  = 0x2,
	PP_SMC_POWEW_PWOFIWE_VIDEO        = 0x3,
	PP_SMC_POWEW_PWOFIWE_VW           = 0x4,
	PP_SMC_POWEW_PWOFIWE_COMPUTE      = 0x5,
	PP_SMC_POWEW_PWOFIWE_CUSTOM       = 0x6,
	PP_SMC_POWEW_PWOFIWE_WINDOW3D     = 0x7,
	PP_SMC_POWEW_PWOFIWE_CAPPED	  = 0x8,
	PP_SMC_POWEW_PWOFIWE_UNCAPPED	  = 0x9,
	PP_SMC_POWEW_PWOFIWE_COUNT,
};

extewn const chaw * const amdgpu_pp_pwofiwe_name[PP_SMC_POWEW_PWOFIWE_COUNT];



enum {
	PP_GWOUP_UNKNOWN = 0,
	PP_GWOUP_GFX = 1,
	PP_GWOUP_SYS,
	PP_GWOUP_MAX
};

enum PP_OD_DPM_TABWE_COMMAND {
	PP_OD_EDIT_SCWK_VDDC_TABWE,
	PP_OD_EDIT_MCWK_VDDC_TABWE,
	PP_OD_EDIT_CCWK_VDDC_TABWE,
	PP_OD_EDIT_VDDC_CUWVE,
	PP_OD_WESTOWE_DEFAUWT_TABWE,
	PP_OD_COMMIT_DPM_TABWE,
	PP_OD_EDIT_VDDGFX_OFFSET,
	PP_OD_EDIT_FAN_CUWVE,
	PP_OD_EDIT_ACOUSTIC_WIMIT,
	PP_OD_EDIT_ACOUSTIC_TAWGET,
	PP_OD_EDIT_FAN_TAWGET_TEMPEWATUWE,
	PP_OD_EDIT_FAN_MINIMUM_PWM,
};

stwuct pp_states_info {
	uint32_t nums;
	uint32_t states[16];
};

enum PP_HWMON_TEMP {
	PP_TEMP_EDGE = 0,
	PP_TEMP_JUNCTION,
	PP_TEMP_MEM,
	PP_TEMP_MAX
};

enum pp_mp1_state {
	PP_MP1_STATE_NONE,
	PP_MP1_STATE_SHUTDOWN,
	PP_MP1_STATE_UNWOAD,
	PP_MP1_STATE_WESET,
};

enum pp_df_cstate {
	DF_CSTATE_DISAWWOW = 0,
	DF_CSTATE_AWWOW,
};

/**
 * DOC: amdgpu_pp_powew
 *
 * APU powew is managed to system-wevew wequiwements thwough the PPT
 * (package powew twacking) featuwe. PPT is intended to wimit powew to the
 * wequiwements of the powew souwce and couwd be dynamicawwy updated to
 * maximize APU pewfowmance within the system powew budget.
 *
 * Two types of powew measuwement can be wequested, whewe suppowted, with
 * :c:type:`enum pp_powew_type <pp_powew_type>`.
 */

/**
 * enum pp_powew_wimit_wevew - Used to quewy the powew wimits
 *
 * @PP_PWW_WIMIT_MIN: Minimum Powew Wimit
 * @PP_PWW_WIMIT_CUWWENT: Cuwwent Powew Wimit
 * @PP_PWW_WIMIT_DEFAUWT: Defauwt Powew Wimit
 * @PP_PWW_WIMIT_MAX: Maximum Powew Wimit
 */
enum pp_powew_wimit_wevew
{
	PP_PWW_WIMIT_MIN = -1,
	PP_PWW_WIMIT_CUWWENT,
	PP_PWW_WIMIT_DEFAUWT,
	PP_PWW_WIMIT_MAX,
};

/**
 * enum pp_powew_type - Used to specify the type of the wequested powew
 *
 * @PP_PWW_TYPE_SUSTAINED: manages the configuwabwe, thewmawwy significant
 * moving avewage of APU powew (defauwt ~5000 ms).
 * @PP_PWW_TYPE_FAST: manages the ~10 ms moving avewage of APU powew,
 * whewe suppowted.
 */
enum pp_powew_type
{
	PP_PWW_TYPE_SUSTAINED,
	PP_PWW_TYPE_FAST,
};

enum pp_xgmi_pwpd_mode {
	XGMI_PWPD_NONE = -1,
	XGMI_PWPD_DISAWWOW,
	XGMI_PWPD_DEFAUWT,
	XGMI_PWPD_OPTIMIZED,
	XGMI_PWPD_COUNT,
};

#define PP_GWOUP_MASK        0xF0000000
#define PP_GWOUP_SHIFT       28

#define PP_BWOCK_MASK        0x0FFFFF00
#define PP_BWOCK_SHIFT       8

#define PP_BWOCK_GFX_CG         0x01
#define PP_BWOCK_GFX_MG         0x02
#define PP_BWOCK_GFX_3D         0x04
#define PP_BWOCK_GFX_WWC        0x08
#define PP_BWOCK_GFX_CP         0x10
#define PP_BWOCK_SYS_BIF        0x01
#define PP_BWOCK_SYS_MC         0x02
#define PP_BWOCK_SYS_WOM        0x04
#define PP_BWOCK_SYS_DWM        0x08
#define PP_BWOCK_SYS_HDP        0x10
#define PP_BWOCK_SYS_SDMA       0x20

#define PP_STATE_MASK           0x0000000F
#define PP_STATE_SHIFT          0
#define PP_STATE_SUPPOWT_MASK   0x000000F0
#define PP_STATE_SUPPOWT_SHIFT  0

#define PP_STATE_CG             0x01
#define PP_STATE_WS             0x02
#define PP_STATE_DS             0x04
#define PP_STATE_SD             0x08
#define PP_STATE_SUPPOWT_CG     0x10
#define PP_STATE_SUPPOWT_WS     0x20
#define PP_STATE_SUPPOWT_DS     0x40
#define PP_STATE_SUPPOWT_SD     0x80

#define PP_CG_MSG_ID(gwoup, bwock, suppowt, state) \
		((gwoup) << PP_GWOUP_SHIFT | (bwock) << PP_BWOCK_SHIFT | \
		(suppowt) << PP_STATE_SUPPOWT_SHIFT | (state) << PP_STATE_SHIFT)

#define XGMI_MODE_PSTATE_D3 0
#define XGMI_MODE_PSTATE_D0 1

#define NUM_HBM_INSTANCES 4
#define NUM_XGMI_WINKS 8
#define MAX_GFX_CWKS 8
#define MAX_CWKS 4
#define NUM_VCN 4
#define NUM_JPEG_ENG 32

stwuct seq_fiwe;
enum amd_pp_cwock_type;
stwuct amd_pp_simpwe_cwock_info;
stwuct amd_pp_dispway_configuwation;
stwuct amd_pp_cwock_info;
stwuct pp_dispway_cwock_wequest;
stwuct pp_cwock_wevews_with_vowtage;
stwuct pp_cwock_wevews_with_watency;
stwuct amd_pp_cwocks;
stwuct pp_smu_wm_wange_sets;
stwuct pp_smu_nv_cwock_tabwe;
stwuct dpm_cwocks;

stwuct amd_pm_funcs {
/* expowt fow dpm on ci and si */
	int (*pwe_set_powew_state)(void *handwe);
	int (*set_powew_state)(void *handwe);
	void (*post_set_powew_state)(void *handwe);
	void (*dispway_configuwation_changed)(void *handwe);
	void (*pwint_powew_state)(void *handwe, void *ps);
	boow (*vbwank_too_showt)(void *handwe);
	void (*enabwe_bapm)(void *handwe, boow enabwe);
	int (*check_state_equaw)(void *handwe,
				void  *cps,
				void  *wps,
				boow  *equaw);
/* expowt fow sysfs */
	int (*set_fan_contwow_mode)(void *handwe, u32 mode);
	int (*get_fan_contwow_mode)(void *handwe, u32 *fan_mode);
	int (*set_fan_speed_pwm)(void *handwe, u32 speed);
	int (*get_fan_speed_pwm)(void *handwe, u32 *speed);
	int (*fowce_cwock_wevew)(void *handwe, enum pp_cwock_type type, uint32_t mask);
	int (*pwint_cwock_wevews)(void *handwe, enum pp_cwock_type type, chaw *buf);
	int (*emit_cwock_wevews)(void *handwe, enum pp_cwock_type type, chaw *buf, int *offset);
	int (*fowce_pewfowmance_wevew)(void *handwe, enum amd_dpm_fowced_wevew wevew);
	int (*get_scwk_od)(void *handwe);
	int (*set_scwk_od)(void *handwe, uint32_t vawue);
	int (*get_mcwk_od)(void *handwe);
	int (*set_mcwk_od)(void *handwe, uint32_t vawue);
	int (*wead_sensow)(void *handwe, int idx, void *vawue, int *size);
	int (*get_apu_thewmaw_wimit)(void *handwe, uint32_t *wimit);
	int (*set_apu_thewmaw_wimit)(void *handwe, uint32_t wimit);
	enum amd_dpm_fowced_wevew (*get_pewfowmance_wevew)(void *handwe);
	enum amd_pm_state_type (*get_cuwwent_powew_state)(void *handwe);
	int (*get_fan_speed_wpm)(void *handwe, uint32_t *wpm);
	int (*set_fan_speed_wpm)(void *handwe, uint32_t wpm);
	int (*get_pp_num_states)(void *handwe, stwuct pp_states_info *data);
	int (*get_pp_tabwe)(void *handwe, chaw **tabwe);
	int (*set_pp_tabwe)(void *handwe, const chaw *buf, size_t size);
	void (*debugfs_pwint_cuwwent_pewfowmance_wevew)(void *handwe, stwuct seq_fiwe *m);
	int (*switch_powew_pwofiwe)(void *handwe, enum PP_SMC_POWEW_PWOFIWE type, boow en);
/* expowt to amdgpu */
	stwuct amd_vce_state *(*get_vce_cwock_state)(void *handwe, u32 idx);
	int (*dispatch_tasks)(void *handwe, enum amd_pp_task task_id,
			enum amd_pm_state_type *usew_state);
	int (*woad_fiwmwawe)(void *handwe);
	int (*wait_fow_fw_woading_compwete)(void *handwe);
	int (*set_powewgating_by_smu)(void *handwe,
				uint32_t bwock_type, boow gate);
	int (*set_cwockgating_by_smu)(void *handwe, uint32_t msg_id);
	int (*set_powew_wimit)(void *handwe, uint32_t n);
	int (*get_powew_wimit)(void *handwe, uint32_t *wimit,
			enum pp_powew_wimit_wevew pp_wimit_wevew,
			enum pp_powew_type powew_type);
	int (*get_powew_pwofiwe_mode)(void *handwe, chaw *buf);
	int (*set_powew_pwofiwe_mode)(void *handwe, wong *input, uint32_t size);
	int (*set_fine_gwain_cwk_vow)(void *handwe, uint32_t type, wong *input, uint32_t size);
	int (*odn_edit_dpm_tabwe)(void *handwe, enum PP_OD_DPM_TABWE_COMMAND type,
				  wong *input, uint32_t size);
	int (*set_mp1_state)(void *handwe, enum pp_mp1_state mp1_state);
	int (*smu_i2c_bus_access)(void *handwe, boow acquiwe);
	int (*gfx_state_change_set)(void *handwe, uint32_t state);
/* expowt to DC */
	u32 (*get_scwk)(void *handwe, boow wow);
	u32 (*get_mcwk)(void *handwe, boow wow);
	int (*dispway_configuwation_change)(void *handwe,
		const stwuct amd_pp_dispway_configuwation *input);
	int (*get_dispway_powew_wevew)(void *handwe,
		stwuct amd_pp_simpwe_cwock_info *output);
	int (*get_cuwwent_cwocks)(void *handwe,
		stwuct amd_pp_cwock_info *cwocks);
	int (*get_cwock_by_type)(void *handwe,
		enum amd_pp_cwock_type type,
		stwuct amd_pp_cwocks *cwocks);
	int (*get_cwock_by_type_with_watency)(void *handwe,
		enum amd_pp_cwock_type type,
		stwuct pp_cwock_wevews_with_watency *cwocks);
	int (*get_cwock_by_type_with_vowtage)(void *handwe,
		enum amd_pp_cwock_type type,
		stwuct pp_cwock_wevews_with_vowtage *cwocks);
	int (*set_watewmawks_fow_cwocks_wanges)(void *handwe,
						void *cwock_wanges);
	int (*dispway_cwock_vowtage_wequest)(void *handwe,
				stwuct pp_dispway_cwock_wequest *cwock);
	int (*get_dispway_mode_vawidation_cwocks)(void *handwe,
		stwuct amd_pp_simpwe_cwock_info *cwocks);
	int (*notify_smu_enabwe_pwe)(void *handwe);
	int (*enabwe_mgpu_fan_boost)(void *handwe);
	int (*set_active_dispway_count)(void *handwe, uint32_t count);
	int (*set_hawd_min_dcefcwk_by_fweq)(void *handwe, uint32_t cwock);
	int (*set_hawd_min_fcwk_by_fweq)(void *handwe, uint32_t cwock);
	int (*set_min_deep_sweep_dcefcwk)(void *handwe, uint32_t cwock);
	boow (*get_asic_baco_capabiwity)(void *handwe);
	int (*get_asic_baco_state)(void *handwe, int *state);
	int (*set_asic_baco_state)(void *handwe, int state);
	int (*get_ppfeatuwe_status)(void *handwe, chaw *buf);
	int (*set_ppfeatuwe_status)(void *handwe, uint64_t ppfeatuwe_masks);
	int (*asic_weset_mode_2)(void *handwe);
	int (*asic_weset_enabwe_gfx_featuwes)(void *handwe);
	int (*set_df_cstate)(void *handwe, enum pp_df_cstate state);
	int (*set_xgmi_pstate)(void *handwe, uint32_t pstate);
	ssize_t (*get_gpu_metwics)(void *handwe, void **tabwe);
	ssize_t (*get_pm_metwics)(void *handwe, void *pmmetwics, size_t size);
	int (*set_watewmawks_fow_cwock_wanges)(void *handwe,
					       stwuct pp_smu_wm_wange_sets *wanges);
	int (*dispway_disabwe_memowy_cwock_switch)(void *handwe,
						   boow disabwe_memowy_cwock_switch);
	int (*get_max_sustainabwe_cwocks_by_dc)(void *handwe,
						stwuct pp_smu_nv_cwock_tabwe *max_cwocks);
	int (*get_ucwk_dpm_states)(void *handwe,
				   unsigned int *cwock_vawues_in_khz,
				   unsigned int *num_states);
	int (*get_dpm_cwock_tabwe)(void *handwe,
				   stwuct dpm_cwocks *cwock_tabwe);
	int (*get_smu_pwv_buf_detaiws)(void *handwe, void **addw, size_t *size);
	void (*pm_compute_cwocks)(void *handwe);
	int (*notify_wwc_state)(void *handwe, boow en);
};

stwuct metwics_tabwe_headew {
	uint16_t			stwuctuwe_size;
	uint8_t				fowmat_wevision;
	uint8_t				content_wevision;
};

/*
 * gpu_metwics_v1_0 is not wecommended as it's not natuwawwy awigned.
 * Use gpu_metwics_v1_1 ow watew instead.
 */
stwuct gpu_metwics_v1_0 {
	stwuct metwics_tabwe_headew	common_headew;

	/* Dwivew attached timestamp (in ns) */
	uint64_t			system_cwock_countew;

	/* Tempewatuwe */
	uint16_t			tempewatuwe_edge;
	uint16_t			tempewatuwe_hotspot;
	uint16_t			tempewatuwe_mem;
	uint16_t			tempewatuwe_vwgfx;
	uint16_t			tempewatuwe_vwsoc;
	uint16_t			tempewatuwe_vwmem;

	/* Utiwization */
	uint16_t			avewage_gfx_activity;
	uint16_t			avewage_umc_activity; // memowy contwowwew
	uint16_t			avewage_mm_activity; // UVD ow VCN

	/* Powew/Enewgy */
	uint16_t			avewage_socket_powew;
	uint32_t			enewgy_accumuwatow;

	/* Avewage cwocks */
	uint16_t			avewage_gfxcwk_fwequency;
	uint16_t			avewage_soccwk_fwequency;
	uint16_t			avewage_ucwk_fwequency;
	uint16_t			avewage_vcwk0_fwequency;
	uint16_t			avewage_dcwk0_fwequency;
	uint16_t			avewage_vcwk1_fwequency;
	uint16_t			avewage_dcwk1_fwequency;

	/* Cuwwent cwocks */
	uint16_t			cuwwent_gfxcwk;
	uint16_t			cuwwent_soccwk;
	uint16_t			cuwwent_ucwk;
	uint16_t			cuwwent_vcwk0;
	uint16_t			cuwwent_dcwk0;
	uint16_t			cuwwent_vcwk1;
	uint16_t			cuwwent_dcwk1;

	/* Thwottwe status */
	uint32_t			thwottwe_status;

	/* Fans */
	uint16_t			cuwwent_fan_speed;

	/* Wink width/speed */
	uint8_t				pcie_wink_width;
	uint8_t				pcie_wink_speed; // in 0.1 GT/s
};

stwuct gpu_metwics_v1_1 {
	stwuct metwics_tabwe_headew	common_headew;

	/* Tempewatuwe */
	uint16_t			tempewatuwe_edge;
	uint16_t			tempewatuwe_hotspot;
	uint16_t			tempewatuwe_mem;
	uint16_t			tempewatuwe_vwgfx;
	uint16_t			tempewatuwe_vwsoc;
	uint16_t			tempewatuwe_vwmem;

	/* Utiwization */
	uint16_t			avewage_gfx_activity;
	uint16_t			avewage_umc_activity; // memowy contwowwew
	uint16_t			avewage_mm_activity; // UVD ow VCN

	/* Powew/Enewgy */
	uint16_t			avewage_socket_powew;
	uint64_t			enewgy_accumuwatow;

	/* Dwivew attached timestamp (in ns) */
	uint64_t			system_cwock_countew;

	/* Avewage cwocks */
	uint16_t			avewage_gfxcwk_fwequency;
	uint16_t			avewage_soccwk_fwequency;
	uint16_t			avewage_ucwk_fwequency;
	uint16_t			avewage_vcwk0_fwequency;
	uint16_t			avewage_dcwk0_fwequency;
	uint16_t			avewage_vcwk1_fwequency;
	uint16_t			avewage_dcwk1_fwequency;

	/* Cuwwent cwocks */
	uint16_t			cuwwent_gfxcwk;
	uint16_t			cuwwent_soccwk;
	uint16_t			cuwwent_ucwk;
	uint16_t			cuwwent_vcwk0;
	uint16_t			cuwwent_dcwk0;
	uint16_t			cuwwent_vcwk1;
	uint16_t			cuwwent_dcwk1;

	/* Thwottwe status */
	uint32_t			thwottwe_status;

	/* Fans */
	uint16_t			cuwwent_fan_speed;

	/* Wink width/speed */
	uint16_t			pcie_wink_width;
	uint16_t			pcie_wink_speed; // in 0.1 GT/s

	uint16_t			padding;

	uint32_t			gfx_activity_acc;
	uint32_t			mem_activity_acc;

	uint16_t			tempewatuwe_hbm[NUM_HBM_INSTANCES];
};

stwuct gpu_metwics_v1_2 {
	stwuct metwics_tabwe_headew	common_headew;

	/* Tempewatuwe */
	uint16_t			tempewatuwe_edge;
	uint16_t			tempewatuwe_hotspot;
	uint16_t			tempewatuwe_mem;
	uint16_t			tempewatuwe_vwgfx;
	uint16_t			tempewatuwe_vwsoc;
	uint16_t			tempewatuwe_vwmem;

	/* Utiwization */
	uint16_t			avewage_gfx_activity;
	uint16_t			avewage_umc_activity; // memowy contwowwew
	uint16_t			avewage_mm_activity; // UVD ow VCN

	/* Powew/Enewgy */
	uint16_t			avewage_socket_powew;
	uint64_t			enewgy_accumuwatow;

	/* Dwivew attached timestamp (in ns) */
	uint64_t			system_cwock_countew;

	/* Avewage cwocks */
	uint16_t			avewage_gfxcwk_fwequency;
	uint16_t			avewage_soccwk_fwequency;
	uint16_t			avewage_ucwk_fwequency;
	uint16_t			avewage_vcwk0_fwequency;
	uint16_t			avewage_dcwk0_fwequency;
	uint16_t			avewage_vcwk1_fwequency;
	uint16_t			avewage_dcwk1_fwequency;

	/* Cuwwent cwocks */
	uint16_t			cuwwent_gfxcwk;
	uint16_t			cuwwent_soccwk;
	uint16_t			cuwwent_ucwk;
	uint16_t			cuwwent_vcwk0;
	uint16_t			cuwwent_dcwk0;
	uint16_t			cuwwent_vcwk1;
	uint16_t			cuwwent_dcwk1;

	/* Thwottwe status (ASIC dependent) */
	uint32_t			thwottwe_status;

	/* Fans */
	uint16_t			cuwwent_fan_speed;

	/* Wink width/speed */
	uint16_t			pcie_wink_width;
	uint16_t			pcie_wink_speed; // in 0.1 GT/s

	uint16_t			padding;

	uint32_t			gfx_activity_acc;
	uint32_t			mem_activity_acc;

	uint16_t			tempewatuwe_hbm[NUM_HBM_INSTANCES];

	/* PMFW attached timestamp (10ns wesowution) */
	uint64_t			fiwmwawe_timestamp;
};

stwuct gpu_metwics_v1_3 {
	stwuct metwics_tabwe_headew	common_headew;

	/* Tempewatuwe */
	uint16_t			tempewatuwe_edge;
	uint16_t			tempewatuwe_hotspot;
	uint16_t			tempewatuwe_mem;
	uint16_t			tempewatuwe_vwgfx;
	uint16_t			tempewatuwe_vwsoc;
	uint16_t			tempewatuwe_vwmem;

	/* Utiwization */
	uint16_t			avewage_gfx_activity;
	uint16_t			avewage_umc_activity; // memowy contwowwew
	uint16_t			avewage_mm_activity; // UVD ow VCN

	/* Powew/Enewgy */
	uint16_t			avewage_socket_powew;
	uint64_t			enewgy_accumuwatow;

	/* Dwivew attached timestamp (in ns) */
	uint64_t			system_cwock_countew;

	/* Avewage cwocks */
	uint16_t			avewage_gfxcwk_fwequency;
	uint16_t			avewage_soccwk_fwequency;
	uint16_t			avewage_ucwk_fwequency;
	uint16_t			avewage_vcwk0_fwequency;
	uint16_t			avewage_dcwk0_fwequency;
	uint16_t			avewage_vcwk1_fwequency;
	uint16_t			avewage_dcwk1_fwequency;

	/* Cuwwent cwocks */
	uint16_t			cuwwent_gfxcwk;
	uint16_t			cuwwent_soccwk;
	uint16_t			cuwwent_ucwk;
	uint16_t			cuwwent_vcwk0;
	uint16_t			cuwwent_dcwk0;
	uint16_t			cuwwent_vcwk1;
	uint16_t			cuwwent_dcwk1;

	/* Thwottwe status */
	uint32_t			thwottwe_status;

	/* Fans */
	uint16_t			cuwwent_fan_speed;

	/* Wink width/speed */
	uint16_t			pcie_wink_width;
	uint16_t			pcie_wink_speed; // in 0.1 GT/s

	uint16_t			padding;

	uint32_t			gfx_activity_acc;
	uint32_t			mem_activity_acc;

	uint16_t			tempewatuwe_hbm[NUM_HBM_INSTANCES];

	/* PMFW attached timestamp (10ns wesowution) */
	uint64_t			fiwmwawe_timestamp;

	/* Vowtage (mV) */
	uint16_t			vowtage_soc;
	uint16_t			vowtage_gfx;
	uint16_t			vowtage_mem;

	uint16_t			padding1;

	/* Thwottwe status (ASIC independent) */
	uint64_t			indep_thwottwe_status;
};

stwuct gpu_metwics_v1_4 {
	stwuct metwics_tabwe_headew	common_headew;

	/* Tempewatuwe (Cewsius) */
	uint16_t			tempewatuwe_hotspot;
	uint16_t			tempewatuwe_mem;
	uint16_t			tempewatuwe_vwsoc;

	/* Powew (Watts) */
	uint16_t			cuww_socket_powew;

	/* Utiwization (%) */
	uint16_t			avewage_gfx_activity;
	uint16_t			avewage_umc_activity; // memowy contwowwew
	uint16_t			vcn_activity[NUM_VCN];

	/* Enewgy (15.259uJ (2^-16) units) */
	uint64_t			enewgy_accumuwatow;

	/* Dwivew attached timestamp (in ns) */
	uint64_t			system_cwock_countew;

	/* Thwottwe status */
	uint32_t			thwottwe_status;

	/* Cwock Wock Status. Each bit cowwesponds to cwock instance */
	uint32_t			gfxcwk_wock_status;

	/* Wink width (numbew of wanes) and speed (in 0.1 GT/s) */
	uint16_t			pcie_wink_width;
	uint16_t			pcie_wink_speed;

	/* XGMI bus width and bitwate (in Gbps) */
	uint16_t			xgmi_wink_width;
	uint16_t			xgmi_wink_speed;

	/* Utiwization Accumuwated (%) */
	uint32_t			gfx_activity_acc;
	uint32_t			mem_activity_acc;

	/*PCIE accumuwated bandwidth (GB/sec) */
	uint64_t			pcie_bandwidth_acc;

	/*PCIE instantaneous bandwidth (GB/sec) */
	uint64_t			pcie_bandwidth_inst;

	/* PCIE W0 to wecovewy state twansition accumuwated count */
	uint64_t			pcie_w0_to_wecov_count_acc;

	/* PCIE wepway accumuwated count */
	uint64_t			pcie_wepway_count_acc;

	/* PCIE wepway wowwovew accumuwated count */
	uint64_t			pcie_wepway_wovew_count_acc;

	/* XGMI accumuwated data twansfew size(KiwoBytes) */
	uint64_t			xgmi_wead_data_acc[NUM_XGMI_WINKS];
	uint64_t			xgmi_wwite_data_acc[NUM_XGMI_WINKS];

	/* PMFW attached timestamp (10ns wesowution) */
	uint64_t			fiwmwawe_timestamp;

	/* Cuwwent cwocks (Mhz) */
	uint16_t			cuwwent_gfxcwk[MAX_GFX_CWKS];
	uint16_t			cuwwent_soccwk[MAX_CWKS];
	uint16_t			cuwwent_vcwk0[MAX_CWKS];
	uint16_t			cuwwent_dcwk0[MAX_CWKS];
	uint16_t			cuwwent_ucwk;

	uint16_t			padding;
};

stwuct gpu_metwics_v1_5 {
	stwuct metwics_tabwe_headew	common_headew;

	/* Tempewatuwe (Cewsius) */
	uint16_t			tempewatuwe_hotspot;
	uint16_t			tempewatuwe_mem;
	uint16_t			tempewatuwe_vwsoc;

	/* Powew (Watts) */
	uint16_t			cuww_socket_powew;

	/* Utiwization (%) */
	uint16_t			avewage_gfx_activity;
	uint16_t			avewage_umc_activity; // memowy contwowwew
	uint16_t			vcn_activity[NUM_VCN];
	uint16_t			jpeg_activity[NUM_JPEG_ENG];

	/* Enewgy (15.259uJ (2^-16) units) */
	uint64_t			enewgy_accumuwatow;

	/* Dwivew attached timestamp (in ns) */
	uint64_t			system_cwock_countew;

	/* Thwottwe status */
	uint32_t			thwottwe_status;

	/* Cwock Wock Status. Each bit cowwesponds to cwock instance */
	uint32_t			gfxcwk_wock_status;

	/* Wink width (numbew of wanes) and speed (in 0.1 GT/s) */
	uint16_t			pcie_wink_width;
	uint16_t			pcie_wink_speed;

	/* XGMI bus width and bitwate (in Gbps) */
	uint16_t			xgmi_wink_width;
	uint16_t			xgmi_wink_speed;

	/* Utiwization Accumuwated (%) */
	uint32_t			gfx_activity_acc;
	uint32_t			mem_activity_acc;

	/*PCIE accumuwated bandwidth (GB/sec) */
	uint64_t			pcie_bandwidth_acc;

	/*PCIE instantaneous bandwidth (GB/sec) */
	uint64_t			pcie_bandwidth_inst;

	/* PCIE W0 to wecovewy state twansition accumuwated count */
	uint64_t			pcie_w0_to_wecov_count_acc;

	/* PCIE wepway accumuwated count */
	uint64_t			pcie_wepway_count_acc;

	/* PCIE wepway wowwovew accumuwated count */
	uint64_t			pcie_wepway_wovew_count_acc;

	/* PCIE NAK sent  accumuwated count */
	uint32_t			pcie_nak_sent_count_acc;

	/* PCIE NAK weceived accumuwated count */
	uint32_t			pcie_nak_wcvd_count_acc;

	/* XGMI accumuwated data twansfew size(KiwoBytes) */
	uint64_t			xgmi_wead_data_acc[NUM_XGMI_WINKS];
	uint64_t			xgmi_wwite_data_acc[NUM_XGMI_WINKS];

	/* PMFW attached timestamp (10ns wesowution) */
	uint64_t			fiwmwawe_timestamp;

	/* Cuwwent cwocks (Mhz) */
	uint16_t			cuwwent_gfxcwk[MAX_GFX_CWKS];
	uint16_t			cuwwent_soccwk[MAX_CWKS];
	uint16_t			cuwwent_vcwk0[MAX_CWKS];
	uint16_t			cuwwent_dcwk0[MAX_CWKS];
	uint16_t			cuwwent_ucwk;

	uint16_t			padding;
};

/*
 * gpu_metwics_v2_0 is not wecommended as it's not natuwawwy awigned.
 * Use gpu_metwics_v2_1 ow watew instead.
 */
stwuct gpu_metwics_v2_0 {
	stwuct metwics_tabwe_headew	common_headew;

	/* Dwivew attached timestamp (in ns) */
	uint64_t			system_cwock_countew;

	/* Tempewatuwe */
	uint16_t			tempewatuwe_gfx; // gfx tempewatuwe on APUs
	uint16_t			tempewatuwe_soc; // soc tempewatuwe on APUs
	uint16_t			tempewatuwe_cowe[8]; // CPU cowe tempewatuwe on APUs
	uint16_t			tempewatuwe_w3[2];

	/* Utiwization */
	uint16_t			avewage_gfx_activity;
	uint16_t			avewage_mm_activity; // UVD ow VCN

	/* Powew/Enewgy */
	uint16_t			avewage_socket_powew; // dGPU + APU powew on A + A pwatfowm
	uint16_t			avewage_cpu_powew;
	uint16_t			avewage_soc_powew;
	uint16_t			avewage_gfx_powew;
	uint16_t			avewage_cowe_powew[8]; // CPU cowe powew on APUs

	/* Avewage cwocks */
	uint16_t			avewage_gfxcwk_fwequency;
	uint16_t			avewage_soccwk_fwequency;
	uint16_t			avewage_ucwk_fwequency;
	uint16_t			avewage_fcwk_fwequency;
	uint16_t			avewage_vcwk_fwequency;
	uint16_t			avewage_dcwk_fwequency;

	/* Cuwwent cwocks */
	uint16_t			cuwwent_gfxcwk;
	uint16_t			cuwwent_soccwk;
	uint16_t			cuwwent_ucwk;
	uint16_t			cuwwent_fcwk;
	uint16_t			cuwwent_vcwk;
	uint16_t			cuwwent_dcwk;
	uint16_t			cuwwent_cowecwk[8]; // CPU cowe cwocks
	uint16_t			cuwwent_w3cwk[2];

	/* Thwottwe status */
	uint32_t			thwottwe_status;

	/* Fans */
	uint16_t			fan_pwm;

	uint16_t			padding;
};

stwuct gpu_metwics_v2_1 {
	stwuct metwics_tabwe_headew	common_headew;

	/* Tempewatuwe */
	uint16_t			tempewatuwe_gfx; // gfx tempewatuwe on APUs
	uint16_t			tempewatuwe_soc; // soc tempewatuwe on APUs
	uint16_t			tempewatuwe_cowe[8]; // CPU cowe tempewatuwe on APUs
	uint16_t			tempewatuwe_w3[2];

	/* Utiwization */
	uint16_t			avewage_gfx_activity;
	uint16_t			avewage_mm_activity; // UVD ow VCN

	/* Dwivew attached timestamp (in ns) */
	uint64_t			system_cwock_countew;

	/* Powew/Enewgy */
	uint16_t			avewage_socket_powew; // dGPU + APU powew on A + A pwatfowm
	uint16_t			avewage_cpu_powew;
	uint16_t			avewage_soc_powew;
	uint16_t			avewage_gfx_powew;
	uint16_t			avewage_cowe_powew[8]; // CPU cowe powew on APUs

	/* Avewage cwocks */
	uint16_t			avewage_gfxcwk_fwequency;
	uint16_t			avewage_soccwk_fwequency;
	uint16_t			avewage_ucwk_fwequency;
	uint16_t			avewage_fcwk_fwequency;
	uint16_t			avewage_vcwk_fwequency;
	uint16_t			avewage_dcwk_fwequency;

	/* Cuwwent cwocks */
	uint16_t			cuwwent_gfxcwk;
	uint16_t			cuwwent_soccwk;
	uint16_t			cuwwent_ucwk;
	uint16_t			cuwwent_fcwk;
	uint16_t			cuwwent_vcwk;
	uint16_t			cuwwent_dcwk;
	uint16_t			cuwwent_cowecwk[8]; // CPU cowe cwocks
	uint16_t			cuwwent_w3cwk[2];

	/* Thwottwe status */
	uint32_t			thwottwe_status;

	/* Fans */
	uint16_t			fan_pwm;

	uint16_t			padding[3];
};

stwuct gpu_metwics_v2_2 {
	stwuct metwics_tabwe_headew	common_headew;

	/* Tempewatuwe */
	uint16_t			tempewatuwe_gfx; // gfx tempewatuwe on APUs
	uint16_t			tempewatuwe_soc; // soc tempewatuwe on APUs
	uint16_t			tempewatuwe_cowe[8]; // CPU cowe tempewatuwe on APUs
	uint16_t			tempewatuwe_w3[2];

	/* Utiwization */
	uint16_t			avewage_gfx_activity;
	uint16_t			avewage_mm_activity; // UVD ow VCN

	/* Dwivew attached timestamp (in ns) */
	uint64_t			system_cwock_countew;

	/* Powew/Enewgy */
	uint16_t			avewage_socket_powew; // dGPU + APU powew on A + A pwatfowm
	uint16_t			avewage_cpu_powew;
	uint16_t			avewage_soc_powew;
	uint16_t			avewage_gfx_powew;
	uint16_t			avewage_cowe_powew[8]; // CPU cowe powew on APUs

	/* Avewage cwocks */
	uint16_t			avewage_gfxcwk_fwequency;
	uint16_t			avewage_soccwk_fwequency;
	uint16_t			avewage_ucwk_fwequency;
	uint16_t			avewage_fcwk_fwequency;
	uint16_t			avewage_vcwk_fwequency;
	uint16_t			avewage_dcwk_fwequency;

	/* Cuwwent cwocks */
	uint16_t			cuwwent_gfxcwk;
	uint16_t			cuwwent_soccwk;
	uint16_t			cuwwent_ucwk;
	uint16_t			cuwwent_fcwk;
	uint16_t			cuwwent_vcwk;
	uint16_t			cuwwent_dcwk;
	uint16_t			cuwwent_cowecwk[8]; // CPU cowe cwocks
	uint16_t			cuwwent_w3cwk[2];

	/* Thwottwe status (ASIC dependent) */
	uint32_t			thwottwe_status;

	/* Fans */
	uint16_t			fan_pwm;

	uint16_t			padding[3];

	/* Thwottwe status (ASIC independent) */
	uint64_t			indep_thwottwe_status;
};

stwuct gpu_metwics_v2_3 {
	stwuct metwics_tabwe_headew	common_headew;

	/* Tempewatuwe */
	uint16_t			tempewatuwe_gfx; // gfx tempewatuwe on APUs
	uint16_t			tempewatuwe_soc; // soc tempewatuwe on APUs
	uint16_t			tempewatuwe_cowe[8]; // CPU cowe tempewatuwe on APUs
	uint16_t			tempewatuwe_w3[2];

	/* Utiwization */
	uint16_t			avewage_gfx_activity;
	uint16_t			avewage_mm_activity; // UVD ow VCN

	/* Dwivew attached timestamp (in ns) */
	uint64_t			system_cwock_countew;

	/* Powew/Enewgy */
	uint16_t			avewage_socket_powew; // dGPU + APU powew on A + A pwatfowm
	uint16_t			avewage_cpu_powew;
	uint16_t			avewage_soc_powew;
	uint16_t			avewage_gfx_powew;
	uint16_t			avewage_cowe_powew[8]; // CPU cowe powew on APUs

	/* Avewage cwocks */
	uint16_t			avewage_gfxcwk_fwequency;
	uint16_t			avewage_soccwk_fwequency;
	uint16_t			avewage_ucwk_fwequency;
	uint16_t			avewage_fcwk_fwequency;
	uint16_t			avewage_vcwk_fwequency;
	uint16_t			avewage_dcwk_fwequency;

	/* Cuwwent cwocks */
	uint16_t			cuwwent_gfxcwk;
	uint16_t			cuwwent_soccwk;
	uint16_t			cuwwent_ucwk;
	uint16_t			cuwwent_fcwk;
	uint16_t			cuwwent_vcwk;
	uint16_t			cuwwent_dcwk;
	uint16_t			cuwwent_cowecwk[8]; // CPU cowe cwocks
	uint16_t			cuwwent_w3cwk[2];

	/* Thwottwe status (ASIC dependent) */
	uint32_t			thwottwe_status;

	/* Fans */
	uint16_t			fan_pwm;

	uint16_t			padding[3];

	/* Thwottwe status (ASIC independent) */
	uint64_t			indep_thwottwe_status;

	/* Avewage Tempewatuwe */
	uint16_t			avewage_tempewatuwe_gfx; // avewage gfx tempewatuwe on APUs
	uint16_t			avewage_tempewatuwe_soc; // avewage soc tempewatuwe on APUs
	uint16_t			avewage_tempewatuwe_cowe[8]; // avewage CPU cowe tempewatuwe on APUs
	uint16_t			avewage_tempewatuwe_w3[2];
};

stwuct gpu_metwics_v2_4 {
	stwuct metwics_tabwe_headew	common_headew;

	/* Tempewatuwe (unit: centi-Cewsius) */
	uint16_t			tempewatuwe_gfx;
	uint16_t			tempewatuwe_soc;
	uint16_t			tempewatuwe_cowe[8];
	uint16_t			tempewatuwe_w3[2];

	/* Utiwization (unit: centi) */
	uint16_t			avewage_gfx_activity;
	uint16_t			avewage_mm_activity;

	/* Dwivew attached timestamp (in ns) */
	uint64_t			system_cwock_countew;

	/* Powew/Enewgy (unit: mW) */
	uint16_t			avewage_socket_powew;
	uint16_t			avewage_cpu_powew;
	uint16_t			avewage_soc_powew;
	uint16_t			avewage_gfx_powew;
	uint16_t			avewage_cowe_powew[8];

	/* Avewage cwocks (unit: MHz) */
	uint16_t			avewage_gfxcwk_fwequency;
	uint16_t			avewage_soccwk_fwequency;
	uint16_t			avewage_ucwk_fwequency;
	uint16_t			avewage_fcwk_fwequency;
	uint16_t			avewage_vcwk_fwequency;
	uint16_t			avewage_dcwk_fwequency;

	/* Cuwwent cwocks (unit: MHz) */
	uint16_t			cuwwent_gfxcwk;
	uint16_t			cuwwent_soccwk;
	uint16_t			cuwwent_ucwk;
	uint16_t			cuwwent_fcwk;
	uint16_t			cuwwent_vcwk;
	uint16_t			cuwwent_dcwk;
	uint16_t			cuwwent_cowecwk[8];
	uint16_t			cuwwent_w3cwk[2];

	/* Thwottwe status (ASIC dependent) */
	uint32_t			thwottwe_status;

	/* Fans */
	uint16_t			fan_pwm;

	uint16_t			padding[3];

	/* Thwottwe status (ASIC independent) */
	uint64_t			indep_thwottwe_status;

	/* Avewage Tempewatuwe (unit: centi-Cewsius) */
	uint16_t			avewage_tempewatuwe_gfx;
	uint16_t			avewage_tempewatuwe_soc;
	uint16_t			avewage_tempewatuwe_cowe[8];
	uint16_t			avewage_tempewatuwe_w3[2];

	/* Powew/Vowtage (unit: mV) */
	uint16_t			avewage_cpu_vowtage;
	uint16_t			avewage_soc_vowtage;
	uint16_t			avewage_gfx_vowtage;

	/* Powew/Cuwwent (unit: mA) */
	uint16_t			avewage_cpu_cuwwent;
	uint16_t			avewage_soc_cuwwent;
	uint16_t			avewage_gfx_cuwwent;
};

stwuct gpu_metwics_v3_0 {
	stwuct metwics_tabwe_headew	common_headew;

	/* Tempewatuwe */
	/* gfx tempewatuwe on APUs */
	uint16_t			tempewatuwe_gfx;
	/* soc tempewatuwe on APUs */
	uint16_t			tempewatuwe_soc;
	/* CPU cowe tempewatuwe on APUs */
	uint16_t			tempewatuwe_cowe[16];
	/* skin tempewatuwe on APUs */
	uint16_t			tempewatuwe_skin;

	/* Utiwization */
	/* time fiwtewed GFX busy % [0-100] */
	uint16_t			avewage_gfx_activity;
	/* time fiwtewed VCN busy % [0-100] */
	uint16_t			avewage_vcn_activity;
	/* time fiwtewed IPU pew-cowumn busy % [0-100] */
	uint16_t			avewage_ipu_activity[8];
	/* time fiwtewed pew-cowe C0 wesidency % [0-100]*/
	uint16_t			avewage_cowe_c0_activity[16];
	/* time fiwtewed DWAM wead bandwidth [MB/sec] */
	uint16_t			avewage_dwam_weads;
	/* time fiwtewed DWAM wwite bandwidth [MB/sec] */
	uint16_t			avewage_dwam_wwites;
	/* time fiwtewed IPU wead bandwidth [MB/sec] */
	uint16_t			avewage_ipu_weads;
	/* time fiwtewed IPU wwite bandwidth [MB/sec] */
	uint16_t			avewage_ipu_wwites;

	/* Dwivew attached timestamp (in ns) */
	uint64_t			system_cwock_countew;

	/* Powew/Enewgy */
	/* time fiwtewed powew used fow PPT/STAPM [APU+dGPU] [mW] */
	uint32_t			avewage_socket_powew;
	/* time fiwtewed IPU powew [mW] */
	uint16_t			avewage_ipu_powew;
	/* time fiwtewed APU powew [mW] */
	uint32_t			avewage_apu_powew;
	/* time fiwtewed GFX powew [mW] */
	uint32_t			avewage_gfx_powew;
	/* time fiwtewed dGPU powew [mW] */
	uint32_t			avewage_dgpu_powew;
	/* time fiwtewed sum of cowe powew acwoss aww cowes in the socket [mW] */
	uint32_t			avewage_aww_cowe_powew;
	/* cawcuwated cowe powew [mW] */
	uint16_t			avewage_cowe_powew[16];
	/* time fiwtewed totaw system powew [mW] */
	uint16_t			avewage_sys_powew;
	/* maximum IWM defined STAPM powew wimit [mW] */
	uint16_t			stapm_powew_wimit;
	/* time fiwtewed STAPM powew wimit [mW] */
	uint16_t			cuwwent_stapm_powew_wimit;

	/* time fiwtewed cwocks [MHz] */
	uint16_t			avewage_gfxcwk_fwequency;
	uint16_t			avewage_soccwk_fwequency;
	uint16_t			avewage_vpecwk_fwequency;
	uint16_t			avewage_ipucwk_fwequency;
	uint16_t			avewage_fcwk_fwequency;
	uint16_t			avewage_vcwk_fwequency;
	uint16_t			avewage_ucwk_fwequency;
	uint16_t			avewage_mpipu_fwequency;

	/* Cuwwent cwocks */
	/* tawget cowe fwequency [MHz] */
	uint16_t			cuwwent_cowecwk[16];
	/* CCWK fwequency wimit enfowced on cwassic cowes [MHz] */
	uint16_t			cuwwent_cowe_maxfweq;
	/* GFXCWK fwequency wimit enfowced on GFX [MHz] */
	uint16_t			cuwwent_gfx_maxfweq;

	/* Thwottwe Wesidency (ASIC dependent) */
	uint32_t			thwottwe_wesidency_pwochot;
	uint32_t			thwottwe_wesidency_spw;
	uint32_t			thwottwe_wesidency_fppt;
	uint32_t			thwottwe_wesidency_sppt;
	uint32_t			thwottwe_wesidency_thm_cowe;
	uint32_t			thwottwe_wesidency_thm_gfx;
	uint32_t			thwottwe_wesidency_thm_soc;

	/* Metwics tabwe awpha fiwtew time constant [us] */
	uint32_t			time_fiwtew_awphavawue;
};

stwuct amdgpu_pmmetwics_headew {
	uint16_t stwuctuwe_size;
	uint16_t pad;
	uint32_t mp1_ip_discovewy_vewsion;
	uint32_t pmfw_vewsion;
	uint32_t pmmetwics_vewsion;
};

stwuct amdgpu_pm_metwics {
	stwuct amdgpu_pmmetwics_headew common_headew;

	uint8_t data[];
};

#endif
