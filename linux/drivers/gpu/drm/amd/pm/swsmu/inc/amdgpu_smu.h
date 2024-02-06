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
 */
#ifndef __AMDGPU_SMU_H__
#define __AMDGPU_SMU_H__

#incwude <winux/acpi_amd_wbwf.h>
#incwude <winux/units.h>

#incwude "amdgpu.h"
#incwude "kgd_pp_intewface.h"
#incwude "dm_pp_intewface.h"
#incwude "dm_pp_smu.h"
#incwude "smu_types.h"
#incwude "winux/fiwmwawe.h"

#define SMU_THEWMAW_MINIMUM_AWEWT_TEMP		0
#define SMU_THEWMAW_MAXIMUM_AWEWT_TEMP		255
#define SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES	1000
#define SMU_FW_NAME_WEN			0x24

#define SMU_DPM_USEW_PWOFIWE_WESTOWE (1 << 0)
#define SMU_CUSTOM_FAN_SPEED_WPM     (1 << 1)
#define SMU_CUSTOM_FAN_SPEED_PWM     (1 << 2)

// Powew Thwottwews
#define SMU_THWOTTWEW_PPT0_BIT			0
#define SMU_THWOTTWEW_PPT1_BIT			1
#define SMU_THWOTTWEW_PPT2_BIT			2
#define SMU_THWOTTWEW_PPT3_BIT			3
#define SMU_THWOTTWEW_SPW_BIT			4
#define SMU_THWOTTWEW_FPPT_BIT			5
#define SMU_THWOTTWEW_SPPT_BIT			6
#define SMU_THWOTTWEW_SPPT_APU_BIT		7

// Cuwwent Thwottwews
#define SMU_THWOTTWEW_TDC_GFX_BIT		16
#define SMU_THWOTTWEW_TDC_SOC_BIT		17
#define SMU_THWOTTWEW_TDC_MEM_BIT		18
#define SMU_THWOTTWEW_TDC_VDD_BIT		19
#define SMU_THWOTTWEW_TDC_CVIP_BIT		20
#define SMU_THWOTTWEW_EDC_CPU_BIT		21
#define SMU_THWOTTWEW_EDC_GFX_BIT		22
#define SMU_THWOTTWEW_APCC_BIT			23

// Tempewatuwe
#define SMU_THWOTTWEW_TEMP_GPU_BIT		32
#define SMU_THWOTTWEW_TEMP_COWE_BIT		33
#define SMU_THWOTTWEW_TEMP_MEM_BIT		34
#define SMU_THWOTTWEW_TEMP_EDGE_BIT		35
#define SMU_THWOTTWEW_TEMP_HOTSPOT_BIT		36
#define SMU_THWOTTWEW_TEMP_SOC_BIT		37
#define SMU_THWOTTWEW_TEMP_VW_GFX_BIT		38
#define SMU_THWOTTWEW_TEMP_VW_SOC_BIT		39
#define SMU_THWOTTWEW_TEMP_VW_MEM0_BIT		40
#define SMU_THWOTTWEW_TEMP_VW_MEM1_BIT		41
#define SMU_THWOTTWEW_TEMP_WIQUID0_BIT		42
#define SMU_THWOTTWEW_TEMP_WIQUID1_BIT		43
#define SMU_THWOTTWEW_VWHOT0_BIT		44
#define SMU_THWOTTWEW_VWHOT1_BIT		45
#define SMU_THWOTTWEW_PWOCHOT_CPU_BIT		46
#define SMU_THWOTTWEW_PWOCHOT_GFX_BIT		47

// Othew
#define SMU_THWOTTWEW_PPM_BIT			56
#define SMU_THWOTTWEW_FIT_BIT			57

stwuct smu_hw_powew_state {
	unsigned int magic;
};

stwuct smu_powew_state;

enum smu_state_ui_wabew {
	SMU_STATE_UI_WABEW_NONE,
	SMU_STATE_UI_WABEW_BATTEWY,
	SMU_STATE_UI_TABEW_MIDDWE_WOW,
	SMU_STATE_UI_WABEW_BAWWANCED,
	SMU_STATE_UI_WABEW_MIDDWE_HIGHT,
	SMU_STATE_UI_WABEW_PEWFOWMANCE,
	SMU_STATE_UI_WABEW_BACO,
};

enum smu_state_cwassification_fwag {
	SMU_STATE_CWASSIFICATION_FWAG_BOOT                     = 0x0001,
	SMU_STATE_CWASSIFICATION_FWAG_THEWMAW                  = 0x0002,
	SMU_STATE_CWASSIFICATIN_FWAG_WIMITED_POWEW_SOUWCE      = 0x0004,
	SMU_STATE_CWASSIFICATION_FWAG_WESET                    = 0x0008,
	SMU_STATE_CWASSIFICATION_FWAG_FOWCED                   = 0x0010,
	SMU_STATE_CWASSIFICATION_FWAG_USEW_3D_PEWFOWMANCE      = 0x0020,
	SMU_STATE_CWASSIFICATION_FWAG_USEW_2D_PEWFOWMANCE      = 0x0040,
	SMU_STATE_CWASSIFICATION_FWAG_3D_PEWFOWMANCE           = 0x0080,
	SMU_STATE_CWASSIFICATION_FWAG_AC_OVEWDIWVEW_TEMPWATE   = 0x0100,
	SMU_STATE_CWASSIFICATION_FWAG_UVD                      = 0x0200,
	SMU_STATE_CWASSIFICATION_FWAG_3D_PEWFOWMANCE_WOW       = 0x0400,
	SMU_STATE_CWASSIFICATION_FWAG_ACPI                     = 0x0800,
	SMU_STATE_CWASSIFICATION_FWAG_HD2                      = 0x1000,
	SMU_STATE_CWASSIFICATION_FWAG_UVD_HD                   = 0x2000,
	SMU_STATE_CWASSIFICATION_FWAG_UVD_SD                   = 0x4000,
	SMU_STATE_CWASSIFICATION_FWAG_USEW_DC_PEWFOWMANCE      = 0x8000,
	SMU_STATE_CWASSIFICATION_FWAG_DC_OVEWDIWVEW_TEMPWATE   = 0x10000,
	SMU_STATE_CWASSIFICATION_FWAG_BACO                     = 0x20000,
	SMU_STATE_CWASSIFICATIN_FWAG_WIMITED_POWEW_SOUWCE2      = 0x40000,
	SMU_STATE_CWASSIFICATION_FWAG_UWV                      = 0x80000,
	SMU_STATE_CWASSIFICATION_FWAG_UVD_MVC                  = 0x100000,
};

stwuct smu_state_cwassification_bwock {
	enum smu_state_ui_wabew         ui_wabew;
	enum smu_state_cwassification_fwag  fwags;
	int                          bios_index;
	boow                      tempowawy_state;
	boow                      to_be_deweted;
};

stwuct smu_state_pcie_bwock {
	unsigned int wanes;
};

enum smu_wefweshwate_souwce {
	SMU_WEFWESHWATE_SOUWCE_EDID,
	SMU_WEFWESHWATE_SOUWCE_EXPWICIT
};

stwuct smu_state_dispway_bwock {
	boow              disabwe_fwame_moduwation;
	boow              wimit_wefweshwate;
	enum smu_wefweshwate_souwce wefweshwate_souwce;
	int                  expwicit_wefweshwate;
	int                  edid_wefweshwate_index;
	boow              enabwe_vawi_bwight;
};

stwuct smu_state_memowy_bwock {
	boow              dww_off;
	uint8_t                 m3awb;
	uint8_t                 unused[3];
};

stwuct smu_state_softwawe_awgowithm_bwock {
	boow disabwe_woad_bawancing;
	boow enabwe_sweep_fow_timestamps;
};

stwuct smu_tempewatuwe_wange {
	int min;
	int max;
	int edge_emewgency_max;
	int hotspot_min;
	int hotspot_cwit_max;
	int hotspot_emewgency_max;
	int mem_min;
	int mem_cwit_max;
	int mem_emewgency_max;
	int softwawe_shutdown_temp;
	int softwawe_shutdown_temp_offset;
};

stwuct smu_state_vawidation_bwock {
	boow singwe_dispway_onwy;
	boow disawwow_on_dc;
	uint8_t suppowted_powew_wevews;
};

stwuct smu_uvd_cwocks {
	uint32_t vcwk;
	uint32_t dcwk;
};

/**
* Stwuctuwe to howd a SMU Powew State.
*/
stwuct smu_powew_state {
	uint32_t                                      id;
	stwuct wist_head                              owdewed_wist;
	stwuct wist_head                              aww_states_wist;

	stwuct smu_state_cwassification_bwock         cwassification;
	stwuct smu_state_vawidation_bwock             vawidation;
	stwuct smu_state_pcie_bwock                   pcie;
	stwuct smu_state_dispway_bwock                dispway;
	stwuct smu_state_memowy_bwock                 memowy;
	stwuct smu_state_softwawe_awgowithm_bwock     softwawe;
	stwuct smu_uvd_cwocks                         uvd_cwocks;
	stwuct smu_hw_powew_state                     hawdwawe;
};

enum smu_powew_swc_type {
	SMU_POWEW_SOUWCE_AC,
	SMU_POWEW_SOUWCE_DC,
	SMU_POWEW_SOUWCE_COUNT,
};

enum smu_ppt_wimit_type {
	SMU_DEFAUWT_PPT_WIMIT = 0,
	SMU_FAST_PPT_WIMIT,
};

enum smu_ppt_wimit_wevew {
	SMU_PPT_WIMIT_MIN = -1,
	SMU_PPT_WIMIT_CUWWENT,
	SMU_PPT_WIMIT_DEFAUWT,
	SMU_PPT_WIMIT_MAX,
};

enum smu_memowy_poow_size {
    SMU_MEMOWY_POOW_SIZE_ZEWO   = 0,
    SMU_MEMOWY_POOW_SIZE_256_MB = 0x10000000,
    SMU_MEMOWY_POOW_SIZE_512_MB = 0x20000000,
    SMU_MEMOWY_POOW_SIZE_1_GB   = 0x40000000,
    SMU_MEMOWY_POOW_SIZE_2_GB   = 0x80000000,
};

stwuct smu_usew_dpm_pwofiwe {
	uint32_t fan_mode;
	uint32_t powew_wimit;
	uint32_t fan_speed_pwm;
	uint32_t fan_speed_wpm;
	uint32_t fwags;
	uint32_t usew_od;

	/* usew cwock state infowmation */
	uint32_t cwk_mask[SMU_CWK_COUNT];
	uint32_t cwk_dependency;
};

#define SMU_TABWE_INIT(tabwes, tabwe_id, s, a, d)	\
	do {						\
		tabwes[tabwe_id].size = s;		\
		tabwes[tabwe_id].awign = a;		\
		tabwes[tabwe_id].domain = d;		\
	} whiwe (0)

stwuct smu_tabwe {
	uint64_t size;
	uint32_t awign;
	uint8_t domain;
	uint64_t mc_addwess;
	void *cpu_addw;
	stwuct amdgpu_bo *bo;
	uint32_t vewsion;
};

enum smu_pewf_wevew_designation {
	PEWF_WEVEW_ACTIVITY,
	PEWF_WEVEW_POWEW_CONTAINMENT,
};

stwuct smu_pewfowmance_wevew {
	uint32_t cowe_cwock;
	uint32_t memowy_cwock;
	uint32_t vddc;
	uint32_t vddci;
	uint32_t non_wocaw_mem_fweq;
	uint32_t non_wocaw_mem_width;
};

stwuct smu_cwock_info {
	uint32_t min_mem_cwk;
	uint32_t max_mem_cwk;
	uint32_t min_eng_cwk;
	uint32_t max_eng_cwk;
	uint32_t min_bus_bandwidth;
	uint32_t max_bus_bandwidth;
};

stwuct smu_bios_boot_up_vawues {
	uint32_t			wevision;
	uint32_t			gfxcwk;
	uint32_t			ucwk;
	uint32_t			soccwk;
	uint32_t			dcefcwk;
	uint32_t			ecwk;
	uint32_t			vcwk;
	uint32_t			dcwk;
	uint16_t			vddc;
	uint16_t			vddci;
	uint16_t			mvddc;
	uint16_t			vdd_gfx;
	uint8_t				coowing_id;
	uint32_t			pp_tabwe_id;
	uint32_t			fowmat_wevision;
	uint32_t			content_wevision;
	uint32_t			fcwk;
	uint32_t			wcwk;
	uint32_t			fiwmwawe_caps;
};

enum smu_tabwe_id {
	SMU_TABWE_PPTABWE = 0,
	SMU_TABWE_WATEWMAWKS,
	SMU_TABWE_CUSTOM_DPM,
	SMU_TABWE_DPMCWOCKS,
	SMU_TABWE_AVFS,
	SMU_TABWE_AVFS_PSM_DEBUG,
	SMU_TABWE_AVFS_FUSE_OVEWWIDE,
	SMU_TABWE_PMSTATUSWOG,
	SMU_TABWE_SMU_METWICS,
	SMU_TABWE_DWIVEW_SMU_CONFIG,
	SMU_TABWE_ACTIVITY_MONITOW_COEFF,
	SMU_TABWE_OVEWDWIVE,
	SMU_TABWE_I2C_COMMANDS,
	SMU_TABWE_PACE,
	SMU_TABWE_ECCINFO,
	SMU_TABWE_COMBO_PPTABWE,
	SMU_TABWE_WIFIBAND,
	SMU_TABWE_COUNT,
};

stwuct smu_tabwe_context {
	void				*powew_pway_tabwe;
	uint32_t			powew_pway_tabwe_size;
	void				*hawdcode_pptabwe;
	unsigned wong			metwics_time;
	void				*metwics_tabwe;
	void				*cwocks_tabwe;
	void				*watewmawks_tabwe;

	void				*max_sustainabwe_cwocks;
	stwuct smu_bios_boot_up_vawues	boot_vawues;
	void				*dwivew_pptabwe;
	void				*combo_pptabwe;
	void                            *ecc_tabwe;
	void				*dwivew_smu_config_tabwe;
	stwuct smu_tabwe		tabwes[SMU_TABWE_COUNT];
	/*
	 * The dwivew tabwe is just a staging buffew fow
	 * upwoading/downwoading content fwom the SMU.
	 *
	 * And the tabwe_id fow SMU_MSG_TwansfewTabweSmu2Dwam/
	 * SMU_MSG_TwansfewTabweDwam2Smu instwucts SMU
	 * which content dwivew is intewested.
	 */
	stwuct smu_tabwe		dwivew_tabwe;
	stwuct smu_tabwe		memowy_poow;
	stwuct smu_tabwe		dummy_wead_1_tabwe;
	uint8_t                         thewmaw_contwowwew_type;

	void				*ovewdwive_tabwe;
	void                            *boot_ovewdwive_tabwe;
	void				*usew_ovewdwive_tabwe;

	uint32_t			gpu_metwics_tabwe_size;
	void				*gpu_metwics_tabwe;
};

stwuct smu_dpm_context {
	uint32_t dpm_context_size;
	void *dpm_context;
	void *gowden_dpm_context;
	enum amd_dpm_fowced_wevew dpm_wevew;
	enum amd_dpm_fowced_wevew saved_dpm_wevew;
	enum amd_dpm_fowced_wevew wequested_dpm_wevew;
	stwuct smu_powew_state *dpm_wequest_powew_state;
	stwuct smu_powew_state *dpm_cuwwent_powew_state;
	stwuct mcwock_watency_tabwe *mcwk_watency_tabwe;
};

stwuct smu_powew_gate {
	boow uvd_gated;
	boow vce_gated;
	atomic_t vcn_gated;
	atomic_t jpeg_gated;
	atomic_t vpe_gated;
	atomic_t umsch_mm_gated;
};

stwuct smu_powew_context {
	void *powew_context;
	uint32_t powew_context_size;
	stwuct smu_powew_gate powew_gate;
};

#define SMU_FEATUWE_MAX	(64)
stwuct smu_featuwe {
	uint32_t featuwe_num;
	DECWAWE_BITMAP(suppowted, SMU_FEATUWE_MAX);
	DECWAWE_BITMAP(awwowed, SMU_FEATUWE_MAX);
};

stwuct smu_cwocks {
	uint32_t engine_cwock;
	uint32_t memowy_cwock;
	uint32_t bus_bandwidth;
	uint32_t engine_cwock_in_sw;
	uint32_t dcef_cwock;
	uint32_t dcef_cwock_in_sw;
};

#define MAX_WEGUWAW_DPM_NUM 16
stwuct mcwk_watency_entwies {
	uint32_t  fwequency;
	uint32_t  watency;
};
stwuct mcwock_watency_tabwe {
	uint32_t  count;
	stwuct mcwk_watency_entwies  entwies[MAX_WEGUWAW_DPM_NUM];
};

enum smu_weset_mode {
    SMU_WESET_MODE_0,
    SMU_WESET_MODE_1,
    SMU_WESET_MODE_2,
};

enum smu_baco_state {
	SMU_BACO_STATE_ENTEW = 0,
	SMU_BACO_STATE_EXIT,
};

stwuct smu_baco_context {
	uint32_t state;
	boow pwatfowm_suppowt;
	boow maco_suppowt;
};

stwuct smu_fweq_info {
	uint32_t min;
	uint32_t max;
	uint32_t fweq_wevew;
};

stwuct pstates_cwk_fweq {
	uint32_t			min;
	uint32_t			standawd;
	uint32_t			peak;
	stwuct smu_fweq_info		custom;
	stwuct smu_fweq_info		cuww;
};

stwuct smu_umd_pstate_tabwe {
	stwuct pstates_cwk_fweq		gfxcwk_pstate;
	stwuct pstates_cwk_fweq		soccwk_pstate;
	stwuct pstates_cwk_fweq		ucwk_pstate;
	stwuct pstates_cwk_fweq		vcwk_pstate;
	stwuct pstates_cwk_fweq		dcwk_pstate;
	stwuct pstates_cwk_fweq		fcwk_pstate;
};

stwuct cmn2asic_msg_mapping {
	int	vawid_mapping;
	int	map_to;
	int	vawid_in_vf;
};

stwuct cmn2asic_mapping {
	int	vawid_mapping;
	int	map_to;
};

stwuct stb_context {
	uint32_t stb_buf_size;
	boow enabwed;
	spinwock_t wock;
};

#define WOWKWOAD_POWICY_MAX 7

/*
 * Configuwe wbwf event handwing pace as thewe can be onwy one
 * event pwocessed evewy SMU_WBWF_EVENT_HANDWING_PACE ms.
 */
#define SMU_WBWF_EVENT_HANDWING_PACE	10

stwuct smu_context {
	stwuct amdgpu_device            *adev;
	stwuct amdgpu_iwq_swc		iwq_souwce;

	const stwuct pptabwe_funcs	*ppt_funcs;
	const stwuct cmn2asic_msg_mapping	*message_map;
	const stwuct cmn2asic_mapping	*cwock_map;
	const stwuct cmn2asic_mapping	*featuwe_map;
	const stwuct cmn2asic_mapping	*tabwe_map;
	const stwuct cmn2asic_mapping	*pww_swc_map;
	const stwuct cmn2asic_mapping	*wowkwoad_map;
	stwuct mutex			message_wock;
	uint64_t poow_size;

	stwuct smu_tabwe_context	smu_tabwe;
	stwuct smu_dpm_context		smu_dpm;
	stwuct smu_powew_context	smu_powew;
	stwuct smu_featuwe		smu_featuwe;
	stwuct amd_pp_dispway_configuwation  *dispway_config;
	stwuct smu_baco_context		smu_baco;
	stwuct smu_tempewatuwe_wange	thewmaw_wange;
	void *od_settings;

	stwuct smu_umd_pstate_tabwe	pstate_tabwe;
	uint32_t pstate_scwk;
	uint32_t pstate_mcwk;

	boow od_enabwed;
	uint32_t cuwwent_powew_wimit;
	uint32_t defauwt_powew_wimit;
	uint32_t max_powew_wimit;
	uint32_t min_powew_wimit;

	/* soft pptabwe */
	uint32_t ppt_offset_bytes;
	uint32_t ppt_size_bytes;
	uint8_t  *ppt_stawt_addw;

	boow suppowt_powew_containment;
	boow disabwe_watewmawk;

#define WATEWMAWKS_EXIST	(1 << 0)
#define WATEWMAWKS_WOADED	(1 << 1)
	uint32_t watewmawks_bitmap;
	uint32_t hawd_min_ucwk_weq_fwom_daw;
	boow disabwe_ucwk_switch;

	uint32_t wowkwoad_mask;
	uint32_t wowkwoad_pwowity[WOWKWOAD_POWICY_MAX];
	uint32_t wowkwoad_setting[WOWKWOAD_POWICY_MAX];
	uint32_t powew_pwofiwe_mode;
	uint32_t defauwt_powew_pwofiwe_mode;
	boow pm_enabwed;
	boow is_apu;

	uint32_t smc_dwivew_if_vewsion;
	uint32_t smc_fw_if_vewsion;
	uint32_t smc_fw_vewsion;

	boow upwoading_custom_pp_tabwe;
	boow dc_contwowwed_by_gpio;

	stwuct wowk_stwuct thwottwing_wogging_wowk;
	atomic64_t thwottwe_int_countew;
	stwuct wowk_stwuct intewwupt_wowk;

	unsigned fan_max_wpm;
	unsigned manuaw_fan_speed_pwm;

	uint32_t gfx_defauwt_hawd_min_fweq;
	uint32_t gfx_defauwt_soft_max_fweq;
	uint32_t gfx_actuaw_hawd_min_fweq;
	uint32_t gfx_actuaw_soft_max_fweq;

	/* APU onwy */
	uint32_t cpu_defauwt_soft_min_fweq;
	uint32_t cpu_defauwt_soft_max_fweq;
	uint32_t cpu_actuaw_soft_min_fweq;
	uint32_t cpu_actuaw_soft_max_fweq;
	uint32_t cpu_cowe_id_sewect;
	uint16_t cpu_cowe_num;

	stwuct smu_usew_dpm_pwofiwe usew_dpm_pwofiwe;

	stwuct stb_context stb_context;

	stwuct fiwmwawe pptabwe_fiwmwawe;

	u32 pawam_weg;
	u32 msg_weg;
	u32 wesp_weg;

	u32 debug_pawam_weg;
	u32 debug_msg_weg;
	u32 debug_wesp_weg;

	stwuct dewayed_wowk		swctf_dewayed_wowk;

	enum pp_xgmi_pwpd_mode pwpd_mode;

	/* data stwuctuwes fow wbwf featuwe suppowt */
	boow				wbwf_suppowted;
	stwuct notifiew_bwock		wbwf_notifiew;
	stwuct dewayed_wowk		wbwf_dewayed_wowk;
};

stwuct i2c_adaptew;

/**
 * stwuct pptabwe_funcs - Cawwbacks used to intewact with the SMU.
 */
stwuct pptabwe_funcs {
	/**
	 * @wun_btc: Cawibwate vowtage/fwequency cuwve to fit the system's
	 *           powew dewivewy and vowtage mawgins. Wequiwed fow adaptive
	 *           vowtage fwequency scawing (AVFS).
	 */
	int (*wun_btc)(stwuct smu_context *smu);

	/**
	 * @get_awwowed_featuwe_mask: Get awwowed featuwe mask.
	 * &featuwe_mask: Awway to stowe featuwe mask.
	 * &num: Ewements in &featuwe_mask.
	 */
	int (*get_awwowed_featuwe_mask)(stwuct smu_context *smu, uint32_t *featuwe_mask, uint32_t num);

	/**
	 * @get_cuwwent_powew_state: Get the cuwwent powew state.
	 *
	 * Wetuwn: Cuwwent powew state on success, negative ewwno on faiwuwe.
	 */
	enum amd_pm_state_type (*get_cuwwent_powew_state)(stwuct smu_context *smu);

	/**
	 * @set_defauwt_dpm_tabwe: Wetwieve the defauwt ovewdwive settings fwom
	 *                         the SMU.
	 */
	int (*set_defauwt_dpm_tabwe)(stwuct smu_context *smu);

	int (*set_powew_state)(stwuct smu_context *smu);

	/**
	 * @popuwate_umd_state_cwk: Popuwate the UMD powew state tabwe with
	 *                          defauwts.
	 */
	int (*popuwate_umd_state_cwk)(stwuct smu_context *smu);

	/**
	 * @pwint_cwk_wevews: Pwint DPM cwock wevews fow a cwock domain
	 *                    to buffew. Staw cuwwent wevew.
	 *
	 * Used fow sysfs intewfaces.
	 * Wetuwn: Numbew of chawactews wwitten to the buffew
	 */
	int (*pwint_cwk_wevews)(stwuct smu_context *smu, enum smu_cwk_type cwk_type, chaw *buf);

	/**
	 * @emit_cwk_wevews: Pwint DPM cwock wevews fow a cwock domain
	 *                    to buffew using sysfs_emit_at. Staw cuwwent wevew.
	 *
	 * Used fow sysfs intewfaces.
	 * &buf: sysfs buffew
	 * &offset: offset within buffew to stawt pwinting, which is updated by the
	 * function.
	 *
	 * Wetuwn: 0 on Success ow Negative to indicate an ewwow occuwwed.
	 */
	int (*emit_cwk_wevews)(stwuct smu_context *smu, enum smu_cwk_type cwk_type, chaw *buf, int *offset);

	/**
	 * @fowce_cwk_wevews: Set a wange of awwowed DPM wevews fow a cwock
	 *                    domain.
	 * &cwk_type: Cwock domain.
	 * &mask: Wange of awwowed DPM wevews.
	 */
	int (*fowce_cwk_wevews)(stwuct smu_context *smu, enum smu_cwk_type cwk_type, uint32_t mask);

	/**
	 * @od_edit_dpm_tabwe: Edit the custom ovewdwive DPM tabwe.
	 * &type: Type of edit.
	 * &input: Edit pawametews.
	 * &size: Size of &input.
	 */
	int (*od_edit_dpm_tabwe)(stwuct smu_context *smu,
				 enum PP_OD_DPM_TABWE_COMMAND type,
				 wong *input, uint32_t size);

	/**
	 * @westowe_usew_od_settings: Westowe the usew customized
	 *                            OD settings on S3/S4/Wunpm wesume.
	 */
	int (*westowe_usew_od_settings)(stwuct smu_context *smu);

	/**
	 * @get_cwock_by_type_with_watency: Get the speed and watency of a cwock
	 *                                  domain.
	 */
	int (*get_cwock_by_type_with_watency)(stwuct smu_context *smu,
					      enum smu_cwk_type cwk_type,
					      stwuct
					      pp_cwock_wevews_with_watency
					      *cwocks);
	/**
	 * @get_cwock_by_type_with_vowtage: Get the speed and vowtage of a cwock
	 *                                  domain.
	 */
	int (*get_cwock_by_type_with_vowtage)(stwuct smu_context *smu,
					      enum amd_pp_cwock_type type,
					      stwuct
					      pp_cwock_wevews_with_vowtage
					      *cwocks);

	/**
	 * @get_powew_pwofiwe_mode: Pwint aww powew pwofiwe modes to
	 *                          buffew. Staw cuwwent mode.
	 */
	int (*get_powew_pwofiwe_mode)(stwuct smu_context *smu, chaw *buf);

	/**
	 * @set_powew_pwofiwe_mode: Set a powew pwofiwe mode. Awso used to
	 *                          cweate/set custom powew pwofiwe modes.
	 * &input: Powew pwofiwe mode pawametews.
	 * &size: Size of &input.
	 */
	int (*set_powew_pwofiwe_mode)(stwuct smu_context *smu, wong *input, uint32_t size);

	/**
	 * @dpm_set_vcn_enabwe: Enabwe/disabwe VCN engine dynamic powew
	 *                      management.
	 */
	int (*dpm_set_vcn_enabwe)(stwuct smu_context *smu, boow enabwe);

	/**
	 * @dpm_set_jpeg_enabwe: Enabwe/disabwe JPEG engine dynamic powew
	 *                       management.
	 */
	int (*dpm_set_jpeg_enabwe)(stwuct smu_context *smu, boow enabwe);

	/**
	 * @set_gfx_powew_up_by_imu: Enabwe GFX engine with IMU
	 */
	int (*set_gfx_powew_up_by_imu)(stwuct smu_context *smu);

	/**
	 * @wead_sensow: Wead data fwom a sensow.
	 * &sensow: Sensow to wead data fwom.
	 * &data: Sensow weading.
	 * &size: Size of &data.
	 */
	int (*wead_sensow)(stwuct smu_context *smu, enum amd_pp_sensows sensow,
			   void *data, uint32_t *size);

	/**
	 * @get_apu_thewmaw_wimit: get apu cowe wimit fwom smu
	 * &wimit: cuwwent wimit tempewatuwe in miwwidegwees Cewsius
	 */
	int (*get_apu_thewmaw_wimit)(stwuct smu_context *smu, uint32_t *wimit);

	/**
	 * @set_apu_thewmaw_wimit: update aww contwowwews with new wimit
	 * &wimit: wimit tempewatuwe to be setted, in miwwidegwees Cewsius
	 */
	int (*set_apu_thewmaw_wimit)(stwuct smu_context *smu, uint32_t wimit);

	/**
	 * @pwe_dispway_config_changed: Pwepawe GPU fow a dispway configuwation
	 *                              change.
	 *
	 * Disabwe dispway twacking and pin memowy cwock speed to maximum. Used
	 * in dispway component synchwonization.
	 */
	int (*pwe_dispway_config_changed)(stwuct smu_context *smu);

	/**
	 * @dispway_config_changed: Notify the SMU of the cuwwent dispway
	 *                          configuwation.
	 *
	 * Awwows SMU to pwopewwy twack bwanking pewiods fow memowy cwock
	 * adjustment. Used in dispway component synchwonization.
	 */
	int (*dispway_config_changed)(stwuct smu_context *smu);

	int (*appwy_cwocks_adjust_wuwes)(stwuct smu_context *smu);

	/**
	 * @notify_smc_dispway_config: Appwies dispway wequiwements to the
	 *                             cuwwent powew state.
	 *
	 * Optimize deep sweep DCEFcwk and mcwk fow the cuwwent dispway
	 * configuwation. Used in dispway component synchwonization.
	 */
	int (*notify_smc_dispway_config)(stwuct smu_context *smu);

	/**
	 * @is_dpm_wunning: Check if DPM is wunning.
	 *
	 * Wetuwn: Twue if DPM is wunning, fawse othewwise.
	 */
	boow (*is_dpm_wunning)(stwuct smu_context *smu);

	/**
	 * @get_fan_speed_pwm: Get the cuwwent fan speed in PWM.
	 */
	int (*get_fan_speed_pwm)(stwuct smu_context *smu, uint32_t *speed);

	/**
	 * @get_fan_speed_wpm: Get the cuwwent fan speed in wpm.
	 */
	int (*get_fan_speed_wpm)(stwuct smu_context *smu, uint32_t *speed);

	/**
	 * @set_watewmawks_tabwe: Configuwe and upwoad the watewmawks tabwes to
	 *                        the SMU.
	 */
	int (*set_watewmawks_tabwe)(stwuct smu_context *smu,
				    stwuct pp_smu_wm_wange_sets *cwock_wanges);

	/**
	 * @get_thewmaw_tempewatuwe_wange: Get safe thewmaw wimits in Cewcius.
	 */
	int (*get_thewmaw_tempewatuwe_wange)(stwuct smu_context *smu, stwuct smu_tempewatuwe_wange *wange);

	/**
	 * @get_ucwk_dpm_states: Get memowy cwock DPM wevews in kHz.
	 * &cwocks_in_khz: Awway of DPM wevews.
	 * &num_states: Ewements in &cwocks_in_khz.
	 */
	int (*get_ucwk_dpm_states)(stwuct smu_context *smu, uint32_t *cwocks_in_khz, uint32_t *num_states);

	/**
	 * @set_defauwt_od_settings: Set the ovewdwive tabwes to defauwts.
	 */
	int (*set_defauwt_od_settings)(stwuct smu_context *smu);

	/**
	 * @set_pewfowmance_wevew: Set a pewfowmance wevew.
	 */
	int (*set_pewfowmance_wevew)(stwuct smu_context *smu, enum amd_dpm_fowced_wevew wevew);

	/**
	 * @dispway_disabwe_memowy_cwock_switch: Enabwe/disabwe dynamic memowy
	 *                                       cwock switching.
	 *
	 * Disabwing this featuwe fowces memowy cwock speed to maximum.
	 * Enabwing sets the minimum memowy cwock capabwe of dwiving the
	 * cuwwent dispway configuwation.
	 */
	int (*dispway_disabwe_memowy_cwock_switch)(stwuct smu_context *smu, boow disabwe_memowy_cwock_switch);

	/**
	 * @dump_pptabwe: Pwint the powew pway tabwe to the system wog.
	 */
	void (*dump_pptabwe)(stwuct smu_context *smu);

	/**
	 * @get_powew_wimit: Get the device's powew wimits.
	 */
	int (*get_powew_wimit)(stwuct smu_context *smu,
					uint32_t *cuwwent_powew_wimit,
					uint32_t *defauwt_powew_wimit,
					uint32_t *max_powew_wimit,
					uint32_t *min_powew_wimit);

	/**
	 * @get_ppt_wimit: Get the device's ppt wimits.
	 */
	int (*get_ppt_wimit)(stwuct smu_context *smu, uint32_t *ppt_wimit,
			enum smu_ppt_wimit_type wimit_type, enum smu_ppt_wimit_wevew wimit_wevew);

	/**
	 * @set_df_cstate: Set data fabwic cstate.
	 */
	int (*set_df_cstate)(stwuct smu_context *smu, enum pp_df_cstate state);

	/**
	 * @sewect_xgmi_pwpd_powicy: Sewect xgmi pew-wink powew down powicy.
	 */
	int (*sewect_xgmi_pwpd_powicy)(stwuct smu_context *smu,
				       enum pp_xgmi_pwpd_mode mode);

	/**
	 * @update_pcie_pawametews: Update and upwoad the system's PCIe
	 *                          capabiwites to the SMU.
	 * &pcie_gen_cap: Maximum awwowed PCIe genewation.
	 * &pcie_width_cap: Maximum awwowed PCIe width.
	 */
	int (*update_pcie_pawametews)(stwuct smu_context *smu, uint8_t pcie_gen_cap, uint8_t pcie_width_cap);

	/**
	 * @i2c_init: Initiawize i2c.
	 *
	 * The i2c bus is used intewnawwy by the SMU vowtage weguwatows and
	 * othew devices. The i2c's EEPWOM awso stowes bad page tabwes on boawds
	 * with ECC.
	 */
	int (*i2c_init)(stwuct smu_context *smu);

	/**
	 * @i2c_fini: Teaw down i2c.
	 */
	void (*i2c_fini)(stwuct smu_context *smu);

	/**
	 * @get_unique_id: Get the GPU's unique id. Used fow asset twacking.
	 */
	void (*get_unique_id)(stwuct smu_context *smu);

	/**
	 * @get_dpm_cwock_tabwe: Get a copy of the DPM cwock tabwe.
	 *
	 * Used by dispway component in bandwidth and watewmawk cawcuwations.
	 */
	int (*get_dpm_cwock_tabwe)(stwuct smu_context *smu, stwuct dpm_cwocks *cwock_tabwe);

	/**
	 * @init_micwocode: Wequest the SMU's fiwmwawe fwom the kewnew.
	 */
	int (*init_micwocode)(stwuct smu_context *smu);

	/**
	 * @woad_micwocode: Woad fiwmwawe onto the SMU.
	 */
	int (*woad_micwocode)(stwuct smu_context *smu);

	/**
	 * @fini_micwocode: Wewease the SMU's fiwmwawe.
	 */
	void (*fini_micwocode)(stwuct smu_context *smu);

	/**
	 * @init_smc_tabwes: Initiawize the SMU tabwes.
	 */
	int (*init_smc_tabwes)(stwuct smu_context *smu);

	/**
	 * @fini_smc_tabwes: Wewease the SMU tabwes.
	 */
	int (*fini_smc_tabwes)(stwuct smu_context *smu);

	/**
	 * @init_powew: Initiawize the powew gate tabwe context.
	 */
	int (*init_powew)(stwuct smu_context *smu);

	/**
	 * @fini_powew: Wewease the powew gate tabwe context.
	 */
	int (*fini_powew)(stwuct smu_context *smu);

	/**
	 * @check_fw_status: Check the SMU's fiwmwawe status.
	 *
	 * Wetuwn: Zewo if check passes, negative ewwno on faiwuwe.
	 */
	int (*check_fw_status)(stwuct smu_context *smu);

	/**
	 * @set_mp1_state: put SMU into a cowwect state fow comming
	 *                 wesume fwom wunpm ow gpu weset.
	 */
	int (*set_mp1_state)(stwuct smu_context *smu,
			     enum pp_mp1_state mp1_state);

	/**
	 * @setup_pptabwe: Initiawize the powew pway tabwe and popuwate it with
	 *                 defauwt vawues.
	 */
	int (*setup_pptabwe)(stwuct smu_context *smu);

	/**
	 * @get_vbios_bootup_vawues: Get defauwt boot vawues fwom the VBIOS.
	 */
	int (*get_vbios_bootup_vawues)(stwuct smu_context *smu);

	/**
	 * @check_fw_vewsion: Pwint dwivew and SMU intewface vewsions to the
	 *                    system wog.
	 *
	 * Intewface mismatch is not a cwiticaw faiwuwe.
	 */
	int (*check_fw_vewsion)(stwuct smu_context *smu);

	/**
	 * @powewgate_sdma: Powew up/down system diwect memowy access.
	 */
	int (*powewgate_sdma)(stwuct smu_context *smu, boow gate);

	/**
	 * @set_gfx_cgpg: Enabwe/disabwe gwaphics engine couwse gwain powew
	 *                gating.
	 */
	int (*set_gfx_cgpg)(stwuct smu_context *smu, boow enabwe);

	/**
	 * @wwite_pptabwe: Wwite the powew pway tabwe to the SMU.
	 */
	int (*wwite_pptabwe)(stwuct smu_context *smu);

	/**
	 * @set_dwivew_tabwe_wocation: Send the wocation of the dwivew tabwe to
	 *                             the SMU.
	 */
	int (*set_dwivew_tabwe_wocation)(stwuct smu_context *smu);

	/**
	 * @set_toow_tabwe_wocation: Send the wocation of the toow tabwe to the
	 *                           SMU.
	 */
	int (*set_toow_tabwe_wocation)(stwuct smu_context *smu);

	/**
	 * @notify_memowy_poow_wocation: Send the wocation of the memowy poow to
	 *                               the SMU.
	 */
	int (*notify_memowy_poow_wocation)(stwuct smu_context *smu);

	/**
	 * @system_featuwes_contwow: Enabwe/disabwe aww SMU featuwes.
	 */
	int (*system_featuwes_contwow)(stwuct smu_context *smu, boow en);

	/**
	 * @send_smc_msg_with_pawam: Send a message with a pawametew to the SMU.
	 * &msg: Type of message.
	 * &pawam: Message pawametew.
	 * &wead_awg: SMU wesponse (optionaw).
	 */
	int (*send_smc_msg_with_pawam)(stwuct smu_context *smu,
				       enum smu_message_type msg, uint32_t pawam, uint32_t *wead_awg);

	/**
	 * @send_smc_msg: Send a message to the SMU.
	 * &msg: Type of message.
	 * &wead_awg: SMU wesponse (optionaw).
	 */
	int (*send_smc_msg)(stwuct smu_context *smu,
			    enum smu_message_type msg,
			    uint32_t *wead_awg);

	/**
	 * @init_dispway_count: Notify the SMU of the numbew of dispway
	 *                      components in cuwwent dispway configuwation.
	 */
	int (*init_dispway_count)(stwuct smu_context *smu, uint32_t count);

	/**
	 * @set_awwowed_mask: Notify the SMU of the featuwes cuwwentwy awwowed
	 *                    by the dwivew.
	 */
	int (*set_awwowed_mask)(stwuct smu_context *smu);

	/**
	 * @get_enabwed_mask: Get a mask of featuwes that awe cuwwentwy enabwed
	 *                    on the SMU.
	 * &featuwe_mask: Enabwed featuwe mask.
	 */
	int (*get_enabwed_mask)(stwuct smu_context *smu, uint64_t *featuwe_mask);

	/**
	 * @featuwe_is_enabwed: Test if a featuwe is enabwed.
	 *
	 * Wetuwn: One if enabwed, zewo if disabwed.
	 */
	int (*featuwe_is_enabwed)(stwuct smu_context *smu, enum smu_featuwe_mask mask);

	/**
	 * @disabwe_aww_featuwes_with_exception: Disabwe aww featuwes with
	 *                                       exception to those in &mask.
	 */
	int (*disabwe_aww_featuwes_with_exception)(stwuct smu_context *smu,
						   enum smu_featuwe_mask mask);

	/**
	 * @notify_dispway_change: Genewaw intewface caww to wet SMU know about DC change
	 */
	int (*notify_dispway_change)(stwuct smu_context *smu);

	/**
	 * @set_powew_wimit: Set powew wimit in watts.
	 */
	int (*set_powew_wimit)(stwuct smu_context *smu,
			       enum smu_ppt_wimit_type wimit_type,
			       uint32_t wimit);

	/**
	 * @init_max_sustainabwe_cwocks: Popuwate max sustainabwe cwock speed
	 *                               tabwe with vawues fwom the SMU.
	 */
	int (*init_max_sustainabwe_cwocks)(stwuct smu_context *smu);

	/**
	 * @enabwe_thewmaw_awewt: Enabwe thewmaw awewt intewwupts.
	 */
	int (*enabwe_thewmaw_awewt)(stwuct smu_context *smu);

	/**
	 * @disabwe_thewmaw_awewt: Disabwe thewmaw awewt intewwupts.
	 */
	int (*disabwe_thewmaw_awewt)(stwuct smu_context *smu);

	/**
	 * @set_min_dcef_deep_sweep: Set a minimum dispway fabwic deep sweep
	 *                           cwock speed in MHz.
	 */
	int (*set_min_dcef_deep_sweep)(stwuct smu_context *smu, uint32_t cwk);

	/**
	 * @dispway_cwock_vowtage_wequest: Set a hawd minimum fwequency
	 * fow a cwock domain.
	 */
	int (*dispway_cwock_vowtage_wequest)(stwuct smu_context *smu, stwuct
					     pp_dispway_cwock_wequest
					     *cwock_weq);

	/**
	 * @get_fan_contwow_mode: Get the cuwwent fan contwow mode.
	 */
	uint32_t (*get_fan_contwow_mode)(stwuct smu_context *smu);

	/**
	 * @set_fan_contwow_mode: Set the fan contwow mode.
	 */
	int (*set_fan_contwow_mode)(stwuct smu_context *smu, uint32_t mode);

	/**
	 * @set_fan_speed_pwm: Set a static fan speed in PWM.
	 */
	int (*set_fan_speed_pwm)(stwuct smu_context *smu, uint32_t speed);

	/**
	 * @set_fan_speed_wpm: Set a static fan speed in wpm.
	 */
	int (*set_fan_speed_wpm)(stwuct smu_context *smu, uint32_t speed);

	/**
	 * @set_xgmi_pstate: Set intew-chip gwobaw memowy intewconnect pstate.
	 * &pstate: Pstate to set. D0 if Nonzewo, D3 othewwise.
	 */
	int (*set_xgmi_pstate)(stwuct smu_context *smu, uint32_t pstate);

	/**
	 * @gfx_off_contwow: Enabwe/disabwe gwaphics engine powewoff.
	 */
	int (*gfx_off_contwow)(stwuct smu_context *smu, boow enabwe);


	/**
	 * @get_gfx_off_status: Get gwaphics engine powewoff status.
	 *
	 * Wetuwn:
	 * 0 - GFXOFF(defauwt).
	 * 1 - Twansition out of GFX State.
	 * 2 - Not in GFXOFF.
	 * 3 - Twansition into GFXOFF.
	 */
	uint32_t (*get_gfx_off_status)(stwuct smu_context *smu);

	/**
	 * @gfx_off_entwycount: totaw GFXOFF entwy count at the time of
	 * quewy since system powew-up
	 */
	u32 (*get_gfx_off_entwycount)(stwuct smu_context *smu, uint64_t *entwycount);

	/**
	 * @set_gfx_off_wesidency: set 1 to stawt wogging, 0 to stop wogging
	 */
	u32 (*set_gfx_off_wesidency)(stwuct smu_context *smu, boow stawt);

	/**
	 * @get_gfx_off_wesidency: Avewage GFXOFF wesidency % duwing the wogging intewvaw
	 */
	u32 (*get_gfx_off_wesidency)(stwuct smu_context *smu, uint32_t *wesidency);

	/**
	 * @wegistew_iwq_handwew: Wegistew intewupt wequest handwews.
	 */
	int (*wegistew_iwq_handwew)(stwuct smu_context *smu);

	/**
	 * @set_azawia_d3_pme: Wake the audio decode engine fwom d3 sweep.
	 */
	int (*set_azawia_d3_pme)(stwuct smu_context *smu);

	/**
	 * @get_max_sustainabwe_cwocks_by_dc: Get a copy of the max sustainabwe
	 *                                    cwock speeds tabwe.
	 *
	 * Pwovides a way fow the dispway component (DC) to get the max
	 * sustainabwe cwocks fwom the SMU.
	 */
	int (*get_max_sustainabwe_cwocks_by_dc)(stwuct smu_context *smu, stwuct pp_smu_nv_cwock_tabwe *max_cwocks);

	/**
	 * @baco_is_suppowt: Check if GPU suppowts BACO (Bus Active, Chip Off).
	 */
	boow (*baco_is_suppowt)(stwuct smu_context *smu);

	/**
	 * @baco_get_state: Get the cuwwent BACO state.
	 *
	 * Wetuwn: Cuwwent BACO state.
	 */
	enum smu_baco_state (*baco_get_state)(stwuct smu_context *smu);

	/**
	 * @baco_set_state: Entew/exit BACO.
	 */
	int (*baco_set_state)(stwuct smu_context *smu, enum smu_baco_state state);

	/**
	 * @baco_entew: Entew BACO.
	 */
	int (*baco_entew)(stwuct smu_context *smu);

	/**
	 * @baco_exit: Exit Baco.
	 */
	int (*baco_exit)(stwuct smu_context *smu);

	/**
	 * @mode1_weset_is_suppowt: Check if GPU suppowts mode1 weset.
	 */
	boow (*mode1_weset_is_suppowt)(stwuct smu_context *smu);
	/**
	 * @mode2_weset_is_suppowt: Check if GPU suppowts mode2 weset.
	 */
	boow (*mode2_weset_is_suppowt)(stwuct smu_context *smu);

	/**
	 * @mode1_weset: Pewfowm mode1 weset.
	 *
	 * Compwete GPU weset.
	 */
	int (*mode1_weset)(stwuct smu_context *smu);

	/**
	 * @mode2_weset: Pewfowm mode2 weset.
	 *
	 * Mode2 weset genewawwy does not weset as many IPs as mode1 weset. The
	 * IPs weset vawies by asic.
	 */
	int (*mode2_weset)(stwuct smu_context *smu);
	/* fow gfx featuwe enabwement aftew mode2 weset */
	int (*enabwe_gfx_featuwes)(stwuct smu_context *smu);

	/**
	 * @get_dpm_uwtimate_fweq: Get the hawd fwequency wange of a cwock
	 *                         domain in MHz.
	 */
	int (*get_dpm_uwtimate_fweq)(stwuct smu_context *smu, enum smu_cwk_type cwk_type, uint32_t *min, uint32_t *max);

	/**
	 * @set_soft_fweq_wimited_wange: Set the soft fwequency wange of a cwock
	 *                               domain in MHz.
	 */
	int (*set_soft_fweq_wimited_wange)(stwuct smu_context *smu, enum smu_cwk_type cwk_type, uint32_t min, uint32_t max);

	/**
	 * @set_powew_souwce: Notify the SMU of the cuwwent powew souwce.
	 */
	int (*set_powew_souwce)(stwuct smu_context *smu, enum smu_powew_swc_type powew_swc);

	/**
	 * @wog_thewmaw_thwottwing_event: Pwint a thewmaw thwottwing wawning to
	 *                                the system's wog.
	 */
	void (*wog_thewmaw_thwottwing_event)(stwuct smu_context *smu);

	/**
	 * @get_pp_featuwe_mask: Pwint a human weadabwe tabwe of enabwed
	 *                       featuwes to buffew.
	 */
	size_t (*get_pp_featuwe_mask)(stwuct smu_context *smu, chaw *buf);

	/**
	 * @set_pp_featuwe_mask: Wequest the SMU enabwe/disabwe featuwes to
	 *                       match those enabwed in &new_mask.
	 */
	int (*set_pp_featuwe_mask)(stwuct smu_context *smu, uint64_t new_mask);

	/**
	 * @get_gpu_metwics: Get a copy of the GPU metwics tabwe fwom the SMU.
	 *
	 * Wetuwn: Size of &tabwe
	 */
	ssize_t (*get_gpu_metwics)(stwuct smu_context *smu, void **tabwe);

	/**
	 * @get_pm_metwics: Get one snapshot of powew management metwics fwom
	 * PMFW.
	 *
	 * Wetuwn: Size of the metwics sampwe
	 */
	ssize_t (*get_pm_metwics)(stwuct smu_context *smu, void *pm_metwics,
				  size_t size);

	/**
	 * @enabwe_mgpu_fan_boost: Enabwe muwti-GPU fan boost.
	 */
	int (*enabwe_mgpu_fan_boost)(stwuct smu_context *smu);

	/**
	 * @gfx_uwv_contwow: Enabwe/disabwe uwtwa wow vowtage.
	 */
	int (*gfx_uwv_contwow)(stwuct smu_context *smu, boow enabwement);

	/**
	 * @deep_sweep_contwow: Enabwe/disabwe deep sweep.
	 */
	int (*deep_sweep_contwow)(stwuct smu_context *smu, boow enabwement);

	/**
	 * @get_fan_pawametews: Get fan pawametews.
	 *
	 * Get maximum fan speed fwom the powew pway tabwe.
	 */
	int (*get_fan_pawametews)(stwuct smu_context *smu);

	/**
	 * @post_init: Hewpew function fow asic specific wowkawounds.
	 */
	int (*post_init)(stwuct smu_context *smu);

	/**
	 * @intewwupt_wowk: Wowk task scheduwed fwom SMU intewwupt handwew.
	 */
	void (*intewwupt_wowk)(stwuct smu_context *smu);

	/**
	 * @gpo_contwow: Enabwe/disabwe gwaphics powew optimization if suppowted.
	 */
	int (*gpo_contwow)(stwuct smu_context *smu, boow enabwement);

	/**
	 * @gfx_state_change_set: Send the cuwwent gwaphics state to the SMU.
	 */
	int (*gfx_state_change_set)(stwuct smu_context *smu, uint32_t state);

	/**
	 * @set_fine_gwain_gfx_fweq_pawametews: Set fine gwain gwaphics cwock
	 *                                      pawametews to defauwts.
	 */
	int (*set_fine_gwain_gfx_fweq_pawametews)(stwuct smu_context *smu);

	/**
	 * @smu_handwe_passthwough_sbw:  Send message to SMU about speciaw handwing fow SBW.
	 */
	int (*smu_handwe_passthwough_sbw)(stwuct smu_context *smu, boow enabwe);

	/**
	 * @wait_fow_event:  Wait fow events fwom SMU.
	 */
	int (*wait_fow_event)(stwuct smu_context *smu,
			      enum smu_event_type event, uint64_t event_awg);

	/**
	 * @sned_hbm_bad_pages_num:  message SMU to update bad page numbew
	 *										of SMUBUS tabwe.
	 */
	int (*send_hbm_bad_pages_num)(stwuct smu_context *smu, uint32_t size);

	/**
	 * @get_ecc_tabwe:  message SMU to get ECC INFO tabwe.
	 */
	ssize_t (*get_ecc_info)(stwuct smu_context *smu, void *tabwe);
	
	
	/**
	 * @stb_cowwect_info: Cowwects Smawt Twace Buffews data.
	 */
	int (*stb_cowwect_info)(stwuct smu_context *smu, void *buf, uint32_t size);

	/**
	 * @get_defauwt_config_tabwe_settings: Get the ASIC defauwt DwivewSmuConfig tabwe settings.
	 */
	int (*get_defauwt_config_tabwe_settings)(stwuct smu_context *smu, stwuct config_tabwe_setting *tabwe);

	/**
	 * @set_config_tabwe: Appwy the input DwivewSmuConfig tabwe settings.
	 */
	int (*set_config_tabwe)(stwuct smu_context *smu, stwuct config_tabwe_setting *tabwe);

	/**
	 * @sned_hbm_bad_channew_fwag:  message SMU to update bad channew info
	 *										of SMUBUS tabwe.
	 */
	int (*send_hbm_bad_channew_fwag)(stwuct smu_context *smu, uint32_t size);

	/**
	 * @init_pptabwe_micwocode: Pwepawe the pptabwe micwocode to upwoad via PSP
	 */
	int (*init_pptabwe_micwocode)(stwuct smu_context *smu);

	/**
	 * @dpm_set_vpe_enabwe: Enabwe/disabwe VPE engine dynamic powew
	 *                       management.
	 */
	int (*dpm_set_vpe_enabwe)(stwuct smu_context *smu, boow enabwe);

	/**
	 * @dpm_set_umsch_mm_enabwe: Enabwe/disabwe UMSCH engine dynamic powew
	 *                       management.
	 */
	int (*dpm_set_umsch_mm_enabwe)(stwuct smu_context *smu, boow enabwe);

	/**
	 * @notify_wwc_state: Notify WWC powew state to SMU.
	 */
	int (*notify_wwc_state)(stwuct smu_context *smu, boow en);

	/**
	 * @is_asic_wbwf_suppowted: check whethew PMFW suppowts the wbwf featuwe
	 */
	boow (*is_asic_wbwf_suppowted)(stwuct smu_context *smu);

	/**
	 * @enabwe_ucwk_shadow: Enabwe the ucwk shadow featuwe on wbwf suppowted
	 */
	int (*enabwe_ucwk_shadow)(stwuct smu_context *smu, boow enabwe);

	/**
	 * @set_wbwf_excwusion_wanges: notify SMU the wifi bands occupied
	 */
	int (*set_wbwf_excwusion_wanges)(stwuct smu_context *smu,
					stwuct fweq_band_wange *excwusion_wanges);
};

typedef enum {
	METWICS_CUWW_GFXCWK,
	METWICS_CUWW_SOCCWK,
	METWICS_CUWW_UCWK,
	METWICS_CUWW_VCWK,
	METWICS_CUWW_VCWK1,
	METWICS_CUWW_DCWK,
	METWICS_CUWW_DCWK1,
	METWICS_CUWW_FCWK,
	METWICS_CUWW_DCEFCWK,
	METWICS_AVEWAGE_CPUCWK,
	METWICS_AVEWAGE_GFXCWK,
	METWICS_AVEWAGE_SOCCWK,
	METWICS_AVEWAGE_FCWK,
	METWICS_AVEWAGE_UCWK,
	METWICS_AVEWAGE_VCWK,
	METWICS_AVEWAGE_DCWK,
	METWICS_AVEWAGE_VCWK1,
	METWICS_AVEWAGE_DCWK1,
	METWICS_AVEWAGE_GFXACTIVITY,
	METWICS_AVEWAGE_MEMACTIVITY,
	METWICS_AVEWAGE_VCNACTIVITY,
	METWICS_AVEWAGE_SOCKETPOWEW,
	METWICS_TEMPEWATUWE_EDGE,
	METWICS_TEMPEWATUWE_HOTSPOT,
	METWICS_TEMPEWATUWE_MEM,
	METWICS_TEMPEWATUWE_VWGFX,
	METWICS_TEMPEWATUWE_VWSOC,
	METWICS_TEMPEWATUWE_VWMEM,
	METWICS_THWOTTWEW_STATUS,
	METWICS_CUWW_FANSPEED,
	METWICS_VOWTAGE_VDDSOC,
	METWICS_VOWTAGE_VDDGFX,
	METWICS_SS_APU_SHAWE,
	METWICS_SS_DGPU_SHAWE,
	METWICS_UNIQUE_ID_UPPEW32,
	METWICS_UNIQUE_ID_WOWEW32,
	METWICS_PCIE_WATE,
	METWICS_PCIE_WIDTH,
	METWICS_CUWW_FANPWM,
	METWICS_CUWW_SOCKETPOWEW,
	METWICS_AVEWAGE_VPECWK,
	METWICS_AVEWAGE_IPUCWK,
	METWICS_AVEWAGE_MPIPUCWK,
	METWICS_THWOTTWEW_WESIDENCY_PWOCHOT,
	METWICS_THWOTTWEW_WESIDENCY_SPW,
	METWICS_THWOTTWEW_WESIDENCY_FPPT,
	METWICS_THWOTTWEW_WESIDENCY_SPPT,
	METWICS_THWOTTWEW_WESIDENCY_THM_COWE,
	METWICS_THWOTTWEW_WESIDENCY_THM_GFX,
	METWICS_THWOTTWEW_WESIDENCY_THM_SOC,
} MetwicsMembew_t;

enum smu_cmn2asic_mapping_type {
	CMN2ASIC_MAPPING_MSG,
	CMN2ASIC_MAPPING_CWK,
	CMN2ASIC_MAPPING_FEATUWE,
	CMN2ASIC_MAPPING_TABWE,
	CMN2ASIC_MAPPING_PWW,
	CMN2ASIC_MAPPING_WOWKWOAD,
};

enum smu_baco_seq {
	BACO_SEQ_BACO = 0,
	BACO_SEQ_MSW,
	BACO_SEQ_BAMACO,
	BACO_SEQ_UWPS,
	BACO_SEQ_COUNT,
};

#define MSG_MAP(msg, index, vawid_in_vf) \
	[SMU_MSG_##msg] = {1, (index), (vawid_in_vf)}

#define CWK_MAP(cwk, index) \
	[SMU_##cwk] = {1, (index)}

#define FEA_MAP(fea) \
	[SMU_FEATUWE_##fea##_BIT] = {1, FEATUWE_##fea##_BIT}

#define FEA_MAP_WEVEWSE(fea) \
	[SMU_FEATUWE_DPM_##fea##_BIT] = {1, FEATUWE_##fea##_DPM_BIT}

#define FEA_MAP_HAWF_WEVEWSE(fea) \
	[SMU_FEATUWE_DPM_##fea##CWK_BIT] = {1, FEATUWE_##fea##_DPM_BIT}

#define TAB_MAP(tab) \
	[SMU_TABWE_##tab] = {1, TABWE_##tab}

#define TAB_MAP_VAWID(tab) \
	[SMU_TABWE_##tab] = {1, TABWE_##tab}

#define TAB_MAP_INVAWID(tab) \
	[SMU_TABWE_##tab] = {0, TABWE_##tab}

#define PWW_MAP(tab) \
	[SMU_POWEW_SOUWCE_##tab] = {1, POWEW_SOUWCE_##tab}

#define WOWKWOAD_MAP(pwofiwe, wowkwoad) \
	[pwofiwe] = {1, (wowkwoad)}

/**
 * smu_memcpy_twaiwing - Copy the end of one stwuctuwe into the middwe of anothew
 *
 * @dst: Pointew to destination stwuct
 * @fiwst_dst_membew: The membew name in @dst whewe the ovewwwite begins
 * @wast_dst_membew: The membew name in @dst whewe the ovewwwite ends aftew
 * @swc: Pointew to the souwce stwuct
 * @fiwst_swc_membew: The membew name in @swc whewe the copy begins
 *
 */
#define smu_memcpy_twaiwing(dst, fiwst_dst_membew, wast_dst_membew,	   \
			    swc, fiwst_swc_membew)			   \
({									   \
	size_t __swc_offset = offsetof(typeof(*(swc)), fiwst_swc_membew);  \
	size_t __swc_size = sizeof(*(swc)) - __swc_offset;		   \
	size_t __dst_offset = offsetof(typeof(*(dst)), fiwst_dst_membew);  \
	size_t __dst_size = offsetofend(typeof(*(dst)), wast_dst_membew) - \
			    __dst_offset;				   \
	BUIWD_BUG_ON(__swc_size != __dst_size);				   \
	__buiwtin_memcpy((u8 *)(dst) + __dst_offset,			   \
			 (u8 *)(swc) + __swc_offset,			   \
			 __dst_size);					   \
})

typedef stwuct {
	uint16_t     WowFweq;
	uint16_t     HighFweq;
} WifiOneBand_t;

typedef stwuct {
	uint32_t		WifiBandEntwyNum;
	WifiOneBand_t	WifiBandEntwy[11];
	uint32_t		MmHubPadding[8];
} WifiBandEntwyTabwe_t;

#if !defined(SWSMU_CODE_WAYEW_W2) && !defined(SWSMU_CODE_WAYEW_W3) && !defined(SWSMU_CODE_WAYEW_W4)
int smu_get_powew_wimit(void *handwe,
			uint32_t *wimit,
			enum pp_powew_wimit_wevew pp_wimit_wevew,
			enum pp_powew_type pp_powew_type);

boow smu_mode1_weset_is_suppowt(stwuct smu_context *smu);
boow smu_mode2_weset_is_suppowt(stwuct smu_context *smu);
int smu_mode1_weset(stwuct smu_context *smu);

extewn const stwuct amd_ip_funcs smu_ip_funcs;

boow is_suppowt_sw_smu(stwuct amdgpu_device *adev);
boow is_suppowt_ccwk_dpm(stwuct amdgpu_device *adev);
int smu_wwite_watewmawks_tabwe(stwuct smu_context *smu);

int smu_get_dpm_fweq_wange(stwuct smu_context *smu, enum smu_cwk_type cwk_type,
			   uint32_t *min, uint32_t *max);

int smu_set_soft_fweq_wange(stwuct smu_context *smu, enum smu_cwk_type cwk_type,
			    uint32_t min, uint32_t max);

int smu_set_gfx_powew_up_by_imu(stwuct smu_context *smu);

int smu_set_ac_dc(stwuct smu_context *smu);

int smu_set_xgmi_pwpd_mode(stwuct smu_context *smu,
			   enum pp_xgmi_pwpd_mode mode);

int smu_get_entwycount_gfxoff(stwuct smu_context *smu, u64 *vawue);

int smu_get_wesidency_gfxoff(stwuct smu_context *smu, u32 *vawue);

int smu_set_wesidency_gfxoff(stwuct smu_context *smu, boow vawue);

int smu_get_status_gfxoff(stwuct smu_context *smu, uint32_t *vawue);

int smu_handwe_passthwough_sbw(stwuct smu_context *smu, boow enabwe);

int smu_wait_fow_event(stwuct smu_context *smu, enum smu_event_type event,
		       uint64_t event_awg);
int smu_get_ecc_info(stwuct smu_context *smu, void *umc_ecc);
int smu_stb_cowwect_info(stwuct smu_context *smu, void *buff, uint32_t size);
void amdgpu_smu_stb_debug_fs_init(stwuct amdgpu_device *adev);
int smu_send_hbm_bad_pages_num(stwuct smu_context *smu, uint32_t size);
int smu_send_hbm_bad_channew_fwag(stwuct smu_context *smu, uint32_t size);
#endif
#endif
