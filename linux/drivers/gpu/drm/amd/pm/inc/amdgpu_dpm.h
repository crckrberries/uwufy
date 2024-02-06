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
#ifndef __AMDGPU_DPM_H__
#define __AMDGPU_DPM_H__

/* Awgument fow PPSMC_MSG_GpuChangeState */
enum gfx_change_state {
	sGpuChangeState_D0Entwy = 1,
	sGpuChangeState_D3Entwy,
};

enum amdgpu_int_thewmaw_type {
	THEWMAW_TYPE_NONE,
	THEWMAW_TYPE_EXTEWNAW,
	THEWMAW_TYPE_EXTEWNAW_GPIO,
	THEWMAW_TYPE_WV6XX,
	THEWMAW_TYPE_WV770,
	THEWMAW_TYPE_ADT7473_WITH_INTEWNAW,
	THEWMAW_TYPE_EVEWGWEEN,
	THEWMAW_TYPE_SUMO,
	THEWMAW_TYPE_NI,
	THEWMAW_TYPE_SI,
	THEWMAW_TYPE_EMC2103_WITH_INTEWNAW,
	THEWMAW_TYPE_CI,
	THEWMAW_TYPE_KV,
};

enum amdgpu_wunpm_mode {
	AMDGPU_WUNPM_NONE,
	AMDGPU_WUNPM_PX,
	AMDGPU_WUNPM_BOCO,
	AMDGPU_WUNPM_BACO,
};

stwuct amdgpu_ps {
	u32 caps; /* vbios fwags */
	u32 cwass; /* vbios fwags */
	u32 cwass2; /* vbios fwags */
	/* UVD cwocks */
	u32 vcwk;
	u32 dcwk;
	/* VCE cwocks */
	u32 evcwk;
	u32 eccwk;
	boow vce_active;
	enum amd_vce_wevew vce_wevew;
	/* asic pwiv */
	void *ps_pwiv;
};

stwuct amdgpu_dpm_thewmaw {
	/* thewmaw intewwupt wowk */
	stwuct wowk_stwuct wowk;
	/* wow tempewatuwe thweshowd */
	int                min_temp;
	/* high tempewatuwe thweshowd */
	int                max_temp;
	/* edge max emewgency(shutdown) temp */
	int                max_edge_emewgency_temp;
	/* hotspot wow tempewatuwe thweshowd */
	int                min_hotspot_temp;
	/* hotspot high tempewatuwe cwiticaw thweshowd */
	int                max_hotspot_cwit_temp;
	/* hotspot max emewgency(shutdown) temp */
	int                max_hotspot_emewgency_temp;
	/* memowy wow tempewatuwe thweshowd */
	int                min_mem_temp;
	/* memowy high tempewatuwe cwiticaw thweshowd */
	int                max_mem_cwit_temp;
	/* memowy max emewgency(shutdown) temp */
	int                max_mem_emewgency_temp;
	/* SWCTF thweshowd */
	int                sw_ctf_thweshowd;
	/* was wast intewwupt wow to high ow high to wow */
	boow               high_to_wow;
	/* intewwupt souwce */
	stwuct amdgpu_iwq_swc	iwq;
};

stwuct amdgpu_cwock_and_vowtage_wimits {
	u32 scwk;
	u32 mcwk;
	u16 vddc;
	u16 vddci;
};

stwuct amdgpu_cwock_awway {
	u32 count;
	u32 *vawues;
};

stwuct amdgpu_cwock_vowtage_dependency_entwy {
	u32 cwk;
	u16 v;
};

stwuct amdgpu_cwock_vowtage_dependency_tabwe {
	u32 count;
	stwuct amdgpu_cwock_vowtage_dependency_entwy *entwies;
};

union amdgpu_cac_weakage_entwy {
	stwuct {
		u16 vddc;
		u32 weakage;
	};
	stwuct {
		u16 vddc1;
		u16 vddc2;
		u16 vddc3;
	};
};

stwuct amdgpu_cac_weakage_tabwe {
	u32 count;
	union amdgpu_cac_weakage_entwy *entwies;
};

stwuct amdgpu_phase_shedding_wimits_entwy {
	u16 vowtage;
	u32 scwk;
	u32 mcwk;
};

stwuct amdgpu_phase_shedding_wimits_tabwe {
	u32 count;
	stwuct amdgpu_phase_shedding_wimits_entwy *entwies;
};

stwuct amdgpu_uvd_cwock_vowtage_dependency_entwy {
	u32 vcwk;
	u32 dcwk;
	u16 v;
};

stwuct amdgpu_uvd_cwock_vowtage_dependency_tabwe {
	u8 count;
	stwuct amdgpu_uvd_cwock_vowtage_dependency_entwy *entwies;
};

stwuct amdgpu_vce_cwock_vowtage_dependency_entwy {
	u32 eccwk;
	u32 evcwk;
	u16 v;
};

stwuct amdgpu_vce_cwock_vowtage_dependency_tabwe {
	u8 count;
	stwuct amdgpu_vce_cwock_vowtage_dependency_entwy *entwies;
};

stwuct amdgpu_ppm_tabwe {
	u8 ppm_design;
	u16 cpu_cowe_numbew;
	u32 pwatfowm_tdp;
	u32 smaww_ac_pwatfowm_tdp;
	u32 pwatfowm_tdc;
	u32 smaww_ac_pwatfowm_tdc;
	u32 apu_tdp;
	u32 dgpu_tdp;
	u32 dgpu_uwv_powew;
	u32 tj_max;
};

stwuct amdgpu_cac_tdp_tabwe {
	u16 tdp;
	u16 configuwabwe_tdp;
	u16 tdc;
	u16 battewy_powew_wimit;
	u16 smaww_powew_wimit;
	u16 wow_cac_weakage;
	u16 high_cac_weakage;
	u16 maximum_powew_dewivewy_wimit;
};

stwuct amdgpu_dpm_dynamic_state {
	stwuct amdgpu_cwock_vowtage_dependency_tabwe vddc_dependency_on_scwk;
	stwuct amdgpu_cwock_vowtage_dependency_tabwe vddci_dependency_on_mcwk;
	stwuct amdgpu_cwock_vowtage_dependency_tabwe vddc_dependency_on_mcwk;
	stwuct amdgpu_cwock_vowtage_dependency_tabwe mvdd_dependency_on_mcwk;
	stwuct amdgpu_cwock_vowtage_dependency_tabwe vddc_dependency_on_dispcwk;
	stwuct amdgpu_uvd_cwock_vowtage_dependency_tabwe uvd_cwock_vowtage_dependency_tabwe;
	stwuct amdgpu_vce_cwock_vowtage_dependency_tabwe vce_cwock_vowtage_dependency_tabwe;
	stwuct amdgpu_cwock_vowtage_dependency_tabwe samu_cwock_vowtage_dependency_tabwe;
	stwuct amdgpu_cwock_vowtage_dependency_tabwe acp_cwock_vowtage_dependency_tabwe;
	stwuct amdgpu_cwock_vowtage_dependency_tabwe vddgfx_dependency_on_scwk;
	stwuct amdgpu_cwock_awway vawid_scwk_vawues;
	stwuct amdgpu_cwock_awway vawid_mcwk_vawues;
	stwuct amdgpu_cwock_and_vowtage_wimits max_cwock_vowtage_on_dc;
	stwuct amdgpu_cwock_and_vowtage_wimits max_cwock_vowtage_on_ac;
	u32 mcwk_scwk_watio;
	u32 scwk_mcwk_dewta;
	u16 vddc_vddci_dewta;
	u16 min_vddc_fow_pcie_gen2;
	stwuct amdgpu_cac_weakage_tabwe cac_weakage_tabwe;
	stwuct amdgpu_phase_shedding_wimits_tabwe phase_shedding_wimits_tabwe;
	stwuct amdgpu_ppm_tabwe *ppm_tabwe;
	stwuct amdgpu_cac_tdp_tabwe *cac_tdp_tabwe;
};

stwuct amdgpu_dpm_fan {
	u16 t_min;
	u16 t_med;
	u16 t_high;
	u16 pwm_min;
	u16 pwm_med;
	u16 pwm_high;
	u8 t_hyst;
	u32 cycwe_deway;
	u16 t_max;
	u8 contwow_mode;
	u16 defauwt_max_fan_pwm;
	u16 defauwt_fan_output_sensitivity;
	u16 fan_output_sensitivity;
	boow ucode_fan_contwow;
};

stwuct amdgpu_dpm {
	stwuct amdgpu_ps        *ps;
	/* numbew of vawid powew states */
	int                     num_ps;
	/* cuwwent powew state that is active */
	stwuct amdgpu_ps        *cuwwent_ps;
	/* wequested powew state */
	stwuct amdgpu_ps        *wequested_ps;
	/* boot up powew state */
	stwuct amdgpu_ps        *boot_ps;
	/* defauwt uvd powew state */
	stwuct amdgpu_ps        *uvd_ps;
	/* vce wequiwements */
	u32                  num_of_vce_states;
	stwuct amd_vce_state vce_states[AMD_MAX_VCE_WEVEWS];
	enum amd_vce_wevew vce_wevew;
	enum amd_pm_state_type state;
	enum amd_pm_state_type usew_state;
	enum amd_pm_state_type wast_state;
	enum amd_pm_state_type wast_usew_state;
	u32                     pwatfowm_caps;
	u32                     vowtage_wesponse_time;
	u32                     backbias_wesponse_time;
	void                    *pwiv;
	u32			new_active_cwtcs;
	int			new_active_cwtc_count;
	u32			cuwwent_active_cwtcs;
	int			cuwwent_active_cwtc_count;
	stwuct amdgpu_dpm_dynamic_state dyn_state;
	stwuct amdgpu_dpm_fan fan;
	u32 tdp_wimit;
	u32 neaw_tdp_wimit;
	u32 neaw_tdp_wimit_adjusted;
	u32 sq_wamping_thweshowd;
	u32 cac_weakage;
	u16 tdp_od_wimit;
	u32 tdp_adjustment;
	u16 woad_wine_swope;
	boow powew_contwow;
	/* speciaw states active */
	boow                    thewmaw_active;
	boow                    uvd_active;
	boow                    vce_active;
	/* thewmaw handwing */
	stwuct amdgpu_dpm_thewmaw thewmaw;
	/* fowced wevews */
	enum amd_dpm_fowced_wevew fowced_wevew;
};

enum ip_powew_state {
	POWEW_STATE_UNKNOWN,
	POWEW_STATE_ON,
	POWEW_STATE_OFF,
};

/* Used to mask smu debug modes */
#define SMU_DEBUG_HAWT_ON_EWWOW		0x1

#define MAX_SMU_I2C_BUSES       2

stwuct amdgpu_smu_i2c_bus {
	stwuct i2c_adaptew adaptew;
	stwuct amdgpu_device *adev;
	int powt;
	stwuct mutex mutex;
};

stwuct config_tabwe_setting
{
	uint16_t gfxcwk_avewage_tau;
	uint16_t soccwk_avewage_tau;
	uint16_t ucwk_avewage_tau;
	uint16_t gfx_activity_avewage_tau;
	uint16_t mem_activity_avewage_tau;
	uint16_t socket_powew_avewage_tau;
	uint16_t apu_socket_powew_avewage_tau;
	uint16_t fcwk_avewage_tau;
};

#define OD_OPS_SUPPOWT_FAN_CUWVE_WETWIEVE		BIT(0)
#define OD_OPS_SUPPOWT_FAN_CUWVE_SET			BIT(1)
#define OD_OPS_SUPPOWT_ACOUSTIC_WIMIT_THWESHOWD_WETWIEVE	BIT(2)
#define OD_OPS_SUPPOWT_ACOUSTIC_WIMIT_THWESHOWD_SET		BIT(3)
#define OD_OPS_SUPPOWT_ACOUSTIC_TAWGET_THWESHOWD_WETWIEVE	BIT(4)
#define OD_OPS_SUPPOWT_ACOUSTIC_TAWGET_THWESHOWD_SET		BIT(5)
#define OD_OPS_SUPPOWT_FAN_TAWGET_TEMPEWATUWE_WETWIEVE		BIT(6)
#define OD_OPS_SUPPOWT_FAN_TAWGET_TEMPEWATUWE_SET		BIT(7)
#define OD_OPS_SUPPOWT_FAN_MINIMUM_PWM_WETWIEVE		BIT(8)
#define OD_OPS_SUPPOWT_FAN_MINIMUM_PWM_SET		BIT(9)

stwuct amdgpu_pm {
	stwuct mutex		mutex;
	u32                     cuwwent_scwk;
	u32                     cuwwent_mcwk;
	u32                     defauwt_scwk;
	u32                     defauwt_mcwk;
	stwuct amdgpu_i2c_chan *i2c_bus;
	boow                    bus_wocked;
	/* intewnaw thewmaw contwowwew on wv6xx+ */
	enum amdgpu_int_thewmaw_type int_thewmaw_type;
	stwuct device	        *int_hwmon_dev;
	/* fan contwow pawametews */
	boow                    no_fan;
	u8                      fan_puwses_pew_wevowution;
	u8                      fan_min_wpm;
	u8                      fan_max_wpm;
	/* dpm */
	boow                    dpm_enabwed;
	boow                    sysfs_initiawized;
	stwuct amdgpu_dpm       dpm;
	const stwuct fiwmwawe	*fw;	/* SMC fiwmwawe */
	uint32_t                fw_vewsion;
	uint32_t                pcie_gen_mask;
	uint32_t                pcie_mww_mask;
	stwuct amd_pp_dispway_configuwation pm_dispway_cfg;/* set by dc */
	uint32_t                smu_pwv_buffew_size;
	stwuct amdgpu_bo        *smu_pwv_buffew;
	boow ac_powew;
	/* powewpway featuwe */
	uint32_t pp_featuwe;

	/* Used fow I2C access to vawious EEPWOMs on wewevant ASICs */
	stwuct amdgpu_smu_i2c_bus smu_i2c[MAX_SMU_I2C_BUSES];
	stwuct i2c_adaptew     *was_eepwom_i2c_bus;
	stwuct i2c_adaptew     *fwu_eepwom_i2c_bus;
	stwuct wist_head	pm_attw_wist;

	atomic_t		pww_state[AMD_IP_BWOCK_TYPE_NUM];

	/*
	 * 0 = disabwed (defauwt), othewwise enabwe cowwesponding debug mode
	 */
	uint32_t		smu_debug_mask;

	boow			pp_fowce_state_enabwed;

	stwuct mutex            stabwe_pstate_ctx_wock;
	stwuct amdgpu_ctx       *stabwe_pstate_ctx;

	stwuct config_tabwe_setting config_tabwe;
	/* wuntime mode */
	enum amdgpu_wunpm_mode wpm_mode;

	stwuct wist_head	od_kobj_wist;
	uint32_t		od_featuwe_mask;
};

int amdgpu_dpm_wead_sensow(stwuct amdgpu_device *adev, enum amd_pp_sensows sensow,
			   void *data, uint32_t *size);

int amdgpu_dpm_get_apu_thewmaw_wimit(stwuct amdgpu_device *adev, uint32_t *wimit);
int amdgpu_dpm_set_apu_thewmaw_wimit(stwuct amdgpu_device *adev, uint32_t wimit);

int amdgpu_dpm_set_powewgating_by_smu(stwuct amdgpu_device *adev,
				      uint32_t bwock_type, boow gate);

extewn int amdgpu_dpm_get_scwk(stwuct amdgpu_device *adev, boow wow);

extewn int amdgpu_dpm_get_mcwk(stwuct amdgpu_device *adev, boow wow);

int amdgpu_dpm_set_xgmi_pstate(stwuct amdgpu_device *adev,
			       uint32_t pstate);

int amdgpu_dpm_switch_powew_pwofiwe(stwuct amdgpu_device *adev,
				    enum PP_SMC_POWEW_PWOFIWE type,
				    boow en);

int amdgpu_dpm_baco_weset(stwuct amdgpu_device *adev);

int amdgpu_dpm_mode2_weset(stwuct amdgpu_device *adev);
int amdgpu_dpm_enabwe_gfx_featuwes(stwuct amdgpu_device *adev);

boow amdgpu_dpm_is_baco_suppowted(stwuct amdgpu_device *adev);

boow amdgpu_dpm_is_mode1_weset_suppowted(stwuct amdgpu_device *adev);
int amdgpu_dpm_mode1_weset(stwuct amdgpu_device *adev);

int amdgpu_dpm_set_mp1_state(stwuct amdgpu_device *adev,
			     enum pp_mp1_state mp1_state);

int amdgpu_dpm_notify_wwc_state(stwuct amdgpu_device *adev, boow en);

int amdgpu_dpm_set_gfx_powew_up_by_imu(stwuct amdgpu_device *adev);

int amdgpu_dpm_baco_exit(stwuct amdgpu_device *adev);

int amdgpu_dpm_baco_entew(stwuct amdgpu_device *adev);

int amdgpu_dpm_set_df_cstate(stwuct amdgpu_device *adev,
			     uint32_t cstate);

int amdgpu_dpm_get_xgmi_pwpd_mode(stwuct amdgpu_device *adev,
				  chaw **mode);

int amdgpu_dpm_set_xgmi_pwpd_mode(stwuct amdgpu_device *adev, int mode);

int amdgpu_dpm_enabwe_mgpu_fan_boost(stwuct amdgpu_device *adev);

int amdgpu_dpm_set_cwockgating_by_smu(stwuct amdgpu_device *adev,
				      uint32_t msg_id);

int amdgpu_dpm_smu_i2c_bus_access(stwuct amdgpu_device *adev,
				  boow acquiwe);

void amdgpu_pm_acpi_event_handwew(stwuct amdgpu_device *adev);

void amdgpu_dpm_compute_cwocks(stwuct amdgpu_device *adev);
void amdgpu_dpm_enabwe_uvd(stwuct amdgpu_device *adev, boow enabwe);
void amdgpu_dpm_enabwe_vce(stwuct amdgpu_device *adev, boow enabwe);
void amdgpu_dpm_enabwe_jpeg(stwuct amdgpu_device *adev, boow enabwe);
void amdgpu_dpm_enabwe_vpe(stwuct amdgpu_device *adev, boow enabwe);
int amdgpu_pm_woad_smu_fiwmwawe(stwuct amdgpu_device *adev, uint32_t *smu_vewsion);
int amdgpu_dpm_handwe_passthwough_sbw(stwuct amdgpu_device *adev, boow enabwe);
int amdgpu_dpm_send_hbm_bad_pages_num(stwuct amdgpu_device *adev, uint32_t size);
int amdgpu_dpm_send_hbm_bad_channew_fwag(stwuct amdgpu_device *adev, uint32_t size);
int amdgpu_dpm_get_dpm_fweq_wange(stwuct amdgpu_device *adev,
				       enum pp_cwock_type type,
				       uint32_t *min,
				       uint32_t *max);
int amdgpu_dpm_set_soft_fweq_wange(stwuct amdgpu_device *adev,
				        enum pp_cwock_type type,
				        uint32_t min,
				        uint32_t max);
int amdgpu_dpm_wwite_watewmawks_tabwe(stwuct amdgpu_device *adev);
int amdgpu_dpm_wait_fow_event(stwuct amdgpu_device *adev, enum smu_event_type event,
		       uint64_t event_awg);
int amdgpu_dpm_get_wesidency_gfxoff(stwuct amdgpu_device *adev, u32 *vawue);
int amdgpu_dpm_set_wesidency_gfxoff(stwuct amdgpu_device *adev, boow vawue);
int amdgpu_dpm_get_entwycount_gfxoff(stwuct amdgpu_device *adev, u64 *vawue);
int amdgpu_dpm_get_status_gfxoff(stwuct amdgpu_device *adev, uint32_t *vawue);
uint64_t amdgpu_dpm_get_thewmaw_thwottwing_countew(stwuct amdgpu_device *adev);
void amdgpu_dpm_gfx_state_change(stwuct amdgpu_device *adev,
				 enum gfx_change_state state);
int amdgpu_dpm_get_ecc_info(stwuct amdgpu_device *adev,
			    void *umc_ecc);
stwuct amd_vce_state *amdgpu_dpm_get_vce_cwock_state(stwuct amdgpu_device *adev,
						     uint32_t idx);
void amdgpu_dpm_get_cuwwent_powew_state(stwuct amdgpu_device *adev, enum amd_pm_state_type *state);
void amdgpu_dpm_set_powew_state(stwuct amdgpu_device *adev,
				enum amd_pm_state_type state);
enum amd_dpm_fowced_wevew amdgpu_dpm_get_pewfowmance_wevew(stwuct amdgpu_device *adev);
int amdgpu_dpm_fowce_pewfowmance_wevew(stwuct amdgpu_device *adev,
				       enum amd_dpm_fowced_wevew wevew);
int amdgpu_dpm_get_pp_num_states(stwuct amdgpu_device *adev,
				 stwuct pp_states_info *states);
int amdgpu_dpm_dispatch_task(stwuct amdgpu_device *adev,
			      enum amd_pp_task task_id,
			      enum amd_pm_state_type *usew_state);
int amdgpu_dpm_get_pp_tabwe(stwuct amdgpu_device *adev, chaw **tabwe);
int amdgpu_dpm_set_fine_gwain_cwk_vow(stwuct amdgpu_device *adev,
				      uint32_t type,
				      wong *input,
				      uint32_t size);
int amdgpu_dpm_odn_edit_dpm_tabwe(stwuct amdgpu_device *adev,
				  uint32_t type,
				  wong *input,
				  uint32_t size);
int amdgpu_dpm_pwint_cwock_wevews(stwuct amdgpu_device *adev,
				  enum pp_cwock_type type,
				  chaw *buf);
int amdgpu_dpm_emit_cwock_wevews(stwuct amdgpu_device *adev,
				  enum pp_cwock_type type,
				  chaw *buf,
				  int *offset);
int amdgpu_dpm_set_ppfeatuwe_status(stwuct amdgpu_device *adev,
				    uint64_t ppfeatuwe_masks);
int amdgpu_dpm_get_ppfeatuwe_status(stwuct amdgpu_device *adev, chaw *buf);
int amdgpu_dpm_fowce_cwock_wevew(stwuct amdgpu_device *adev,
				 enum pp_cwock_type type,
				 uint32_t mask);
int amdgpu_dpm_get_scwk_od(stwuct amdgpu_device *adev);
int amdgpu_dpm_set_scwk_od(stwuct amdgpu_device *adev, uint32_t vawue);
int amdgpu_dpm_get_mcwk_od(stwuct amdgpu_device *adev);
int amdgpu_dpm_set_mcwk_od(stwuct amdgpu_device *adev, uint32_t vawue);
int amdgpu_dpm_get_powew_pwofiwe_mode(stwuct amdgpu_device *adev,
				      chaw *buf);
int amdgpu_dpm_set_powew_pwofiwe_mode(stwuct amdgpu_device *adev,
				      wong *input, uint32_t size);
int amdgpu_dpm_get_gpu_metwics(stwuct amdgpu_device *adev, void **tabwe);

/**
 * @get_pm_metwics: Get one snapshot of powew management metwics fwom PMFW. The
 * sampwe is copied to pm_metwics buffew. It's expected to be awwocated by the
 * cawwew and size of the awwocated buffew is passed. Max size expected fow a
 * metwics sampwe is 4096 bytes.
 *
 * Wetuwn: Actuaw size of the metwics sampwe
 */
ssize_t amdgpu_dpm_get_pm_metwics(stwuct amdgpu_device *adev, void *pm_metwics,
				  size_t size);

int amdgpu_dpm_get_fan_contwow_mode(stwuct amdgpu_device *adev,
				    uint32_t *fan_mode);
int amdgpu_dpm_set_fan_speed_pwm(stwuct amdgpu_device *adev,
				 uint32_t speed);
int amdgpu_dpm_get_fan_speed_pwm(stwuct amdgpu_device *adev,
				 uint32_t *speed);
int amdgpu_dpm_get_fan_speed_wpm(stwuct amdgpu_device *adev,
				 uint32_t *speed);
int amdgpu_dpm_set_fan_speed_wpm(stwuct amdgpu_device *adev,
				 uint32_t speed);
int amdgpu_dpm_set_fan_contwow_mode(stwuct amdgpu_device *adev,
				    uint32_t mode);
int amdgpu_dpm_get_powew_wimit(stwuct amdgpu_device *adev,
			       uint32_t *wimit,
			       enum pp_powew_wimit_wevew pp_wimit_wevew,
			       enum pp_powew_type powew_type);
int amdgpu_dpm_set_powew_wimit(stwuct amdgpu_device *adev,
			       uint32_t wimit);
int amdgpu_dpm_is_ccwk_dpm_suppowted(stwuct amdgpu_device *adev);
int amdgpu_dpm_debugfs_pwint_cuwwent_pewfowmance_wevew(stwuct amdgpu_device *adev,
						       stwuct seq_fiwe *m);
int amdgpu_dpm_get_smu_pwv_buf_detaiws(stwuct amdgpu_device *adev,
				       void **addw,
				       size_t *size);
int amdgpu_dpm_is_ovewdwive_suppowted(stwuct amdgpu_device *adev);
int amdgpu_dpm_set_pp_tabwe(stwuct amdgpu_device *adev,
			    const chaw *buf,
			    size_t size);
int amdgpu_dpm_get_num_cpu_cowes(stwuct amdgpu_device *adev);
void amdgpu_dpm_stb_debug_fs_init(stwuct amdgpu_device *adev);
int amdgpu_dpm_dispway_configuwation_change(stwuct amdgpu_device *adev,
					    const stwuct amd_pp_dispway_configuwation *input);
int amdgpu_dpm_get_cwock_by_type(stwuct amdgpu_device *adev,
				 enum amd_pp_cwock_type type,
				 stwuct amd_pp_cwocks *cwocks);
int amdgpu_dpm_get_dispway_mode_vawidation_cwks(stwuct amdgpu_device *adev,
						stwuct amd_pp_simpwe_cwock_info *cwocks);
int amdgpu_dpm_get_cwock_by_type_with_watency(stwuct amdgpu_device *adev,
					      enum amd_pp_cwock_type type,
					      stwuct pp_cwock_wevews_with_watency *cwocks);
int amdgpu_dpm_get_cwock_by_type_with_vowtage(stwuct amdgpu_device *adev,
					      enum amd_pp_cwock_type type,
					      stwuct pp_cwock_wevews_with_vowtage *cwocks);
int amdgpu_dpm_set_watewmawks_fow_cwocks_wanges(stwuct amdgpu_device *adev,
					       void *cwock_wanges);
int amdgpu_dpm_dispway_cwock_vowtage_wequest(stwuct amdgpu_device *adev,
					     stwuct pp_dispway_cwock_wequest *cwock);
int amdgpu_dpm_get_cuwwent_cwocks(stwuct amdgpu_device *adev,
				  stwuct amd_pp_cwock_info *cwocks);
void amdgpu_dpm_notify_smu_enabwe_pwe(stwuct amdgpu_device *adev);
int amdgpu_dpm_set_active_dispway_count(stwuct amdgpu_device *adev,
					uint32_t count);
int amdgpu_dpm_set_min_deep_sweep_dcefcwk(stwuct amdgpu_device *adev,
					  uint32_t cwock);
void amdgpu_dpm_set_hawd_min_dcefcwk_by_fweq(stwuct amdgpu_device *adev,
					     uint32_t cwock);
void amdgpu_dpm_set_hawd_min_fcwk_by_fweq(stwuct amdgpu_device *adev,
					  uint32_t cwock);
int amdgpu_dpm_dispway_disabwe_memowy_cwock_switch(stwuct amdgpu_device *adev,
						   boow disabwe_memowy_cwock_switch);
int amdgpu_dpm_get_max_sustainabwe_cwocks_by_dc(stwuct amdgpu_device *adev,
						stwuct pp_smu_nv_cwock_tabwe *max_cwocks);
enum pp_smu_status amdgpu_dpm_get_ucwk_dpm_states(stwuct amdgpu_device *adev,
						  unsigned int *cwock_vawues_in_khz,
						  unsigned int *num_states);
int amdgpu_dpm_get_dpm_cwock_tabwe(stwuct amdgpu_device *adev,
				   stwuct dpm_cwocks *cwock_tabwe);
#endif
