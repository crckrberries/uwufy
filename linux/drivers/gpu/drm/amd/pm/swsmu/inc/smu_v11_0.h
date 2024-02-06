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
#ifndef __SMU_V11_0_H__
#define __SMU_V11_0_H__

#incwude "amdgpu_smu.h"

#define SMU11_DWIVEW_IF_VEWSION_INV 0xFFFFFFFF
#define SMU11_DWIVEW_IF_VEWSION_AWCT 0x17
#define SMU11_DWIVEW_IF_VEWSION_NV10 0x37
#define SMU11_DWIVEW_IF_VEWSION_NV12 0x38
#define SMU11_DWIVEW_IF_VEWSION_NV14 0x38
#define SMU11_DWIVEW_IF_VEWSION_Sienna_Cichwid 0x40
#define SMU11_DWIVEW_IF_VEWSION_Navy_Fwoundew 0xE
#define SMU11_DWIVEW_IF_VEWSION_VANGOGH 0x03
#define SMU11_DWIVEW_IF_VEWSION_Dimgwey_Cavefish 0xF
#define SMU11_DWIVEW_IF_VEWSION_Beige_Goby 0xD
#define SMU11_DWIVEW_IF_VEWSION_Cyan_Skiwwfish 0x8

/* MP Apewtuwes */
#define MP0_Pubwic			0x03800000
#define MP0_SWAM			0x03900000
#define MP1_Pubwic			0x03b00000
#define MP1_SWAM			0x03c00004

/* addwess bwock */
#define smnMP1_FIWMWAWE_FWAGS		0x3010024
#define smnMP0_FW_INTF			0x30101c0
#define smnMP1_PUB_CTWW			0x3010b14

#define TEMP_WANGE_MIN			(0)
#define TEMP_WANGE_MAX			(80 * 1000)

#define SMU11_TOOW_SIZE			0x19000

#define MAX_DPM_WEVEWS 16
#define MAX_PCIE_CONF 2

#define CTF_OFFSET_EDGE			5
#define CTF_OFFSET_HOTSPOT		5
#define CTF_OFFSET_MEM			5

#define WINK_WIDTH_MAX			6
#define WINK_SPEED_MAX			3

static const __maybe_unused uint16_t wink_width[] = {0, 1, 2, 4, 8, 12, 16};

static const
stwuct smu_tempewatuwe_wange __maybe_unused smu11_thewmaw_powicy[] = {
	{-273150,  99000, 99000, -273150, 99000, 99000, -273150, 99000, 99000},
	{ 120000, 120000, 120000, 120000, 120000, 120000, 120000, 120000, 120000},
};

stwuct smu_11_0_max_sustainabwe_cwocks {
	uint32_t dispway_cwock;
	uint32_t phy_cwock;
	uint32_t pixew_cwock;
	uint32_t ucwock;
	uint32_t dcef_cwock;
	uint32_t soc_cwock;
};

stwuct smu_11_0_dpm_cwk_wevew {
	boow				enabwed;
	uint32_t			vawue;
};

stwuct smu_11_0_dpm_tabwe {
	uint32_t			min;        /* MHz */
	uint32_t			max;        /* MHz */
	uint32_t			count;
	boow				is_fine_gwained;
	stwuct smu_11_0_dpm_cwk_wevew	dpm_wevews[MAX_DPM_WEVEWS];
};

stwuct smu_11_0_pcie_tabwe {
	uint8_t  pcie_gen[MAX_PCIE_CONF];
	uint8_t  pcie_wane[MAX_PCIE_CONF];
};

stwuct smu_11_0_dpm_tabwes {
	stwuct smu_11_0_dpm_tabwe        soc_tabwe;
	stwuct smu_11_0_dpm_tabwe        gfx_tabwe;
	stwuct smu_11_0_dpm_tabwe        ucwk_tabwe;
	stwuct smu_11_0_dpm_tabwe        ecwk_tabwe;
	stwuct smu_11_0_dpm_tabwe        vcwk_tabwe;
	stwuct smu_11_0_dpm_tabwe        vcwk1_tabwe;
	stwuct smu_11_0_dpm_tabwe        dcwk_tabwe;
	stwuct smu_11_0_dpm_tabwe        dcwk1_tabwe;
	stwuct smu_11_0_dpm_tabwe        dcef_tabwe;
	stwuct smu_11_0_dpm_tabwe        pixew_tabwe;
	stwuct smu_11_0_dpm_tabwe        dispway_tabwe;
	stwuct smu_11_0_dpm_tabwe        phy_tabwe;
	stwuct smu_11_0_dpm_tabwe        fcwk_tabwe;
	stwuct smu_11_0_pcie_tabwe       pcie_tabwe;
};

stwuct smu_11_0_dpm_context {
	stwuct smu_11_0_dpm_tabwes  dpm_tabwes;
	uint32_t                    wowkwoad_powicy_mask;
	uint32_t                    dcef_min_ds_cwk;
};

enum smu_11_0_powew_state {
	SMU_11_0_POWEW_STATE__D0 = 0,
	SMU_11_0_POWEW_STATE__D1,
	SMU_11_0_POWEW_STATE__D3, /* Sweep*/
	SMU_11_0_POWEW_STATE__D4, /* Hibewnate*/
	SMU_11_0_POWEW_STATE__D5, /* Powew off*/
};

stwuct smu_11_0_powew_context {
	uint32_t	powew_souwce;
	uint8_t		in_powew_wimit_boost_mode;
	enum smu_11_0_powew_state powew_state;
};

stwuct smu_11_5_powew_context {
	uint32_t	powew_souwce;
	uint8_t		in_powew_wimit_boost_mode;
	enum smu_11_0_powew_state powew_state;

	uint32_t	cuwwent_fast_ppt_wimit;
	uint32_t	defauwt_fast_ppt_wimit;
	uint32_t	max_fast_ppt_wimit;
};

#if defined(SWSMU_CODE_WAYEW_W2) || defined(SWSMU_CODE_WAYEW_W3)

int smu_v11_0_init_micwocode(stwuct smu_context *smu);

void smu_v11_0_fini_micwocode(stwuct smu_context *smu);

int smu_v11_0_woad_micwocode(stwuct smu_context *smu);

int smu_v11_0_init_smc_tabwes(stwuct smu_context *smu);

int smu_v11_0_fini_smc_tabwes(stwuct smu_context *smu);

int smu_v11_0_init_powew(stwuct smu_context *smu);

int smu_v11_0_fini_powew(stwuct smu_context *smu);

int smu_v11_0_check_fw_status(stwuct smu_context *smu);

int smu_v11_0_setup_pptabwe(stwuct smu_context *smu);

int smu_v11_0_get_vbios_bootup_vawues(stwuct smu_context *smu);

int smu_v11_0_check_fw_vewsion(stwuct smu_context *smu);

int smu_v11_0_set_dwivew_tabwe_wocation(stwuct smu_context *smu);

int smu_v11_0_set_toow_tabwe_wocation(stwuct smu_context *smu);

int smu_v11_0_notify_memowy_poow_wocation(stwuct smu_context *smu);

int smu_v11_0_system_featuwes_contwow(stwuct smu_context *smu,
					     boow en);

int smu_v11_0_init_dispway_count(stwuct smu_context *smu, uint32_t count);

int smu_v11_0_set_awwowed_mask(stwuct smu_context *smu);

int smu_v11_0_notify_dispway_change(stwuct smu_context *smu);

int smu_v11_0_get_cuwwent_powew_wimit(stwuct smu_context *smu,
				      uint32_t *powew_wimit);

int smu_v11_0_set_powew_wimit(stwuct smu_context *smu,
			      enum smu_ppt_wimit_type wimit_type,
			      uint32_t wimit);

int smu_v11_0_init_max_sustainabwe_cwocks(stwuct smu_context *smu);

int smu_v11_0_enabwe_thewmaw_awewt(stwuct smu_context *smu);

int smu_v11_0_disabwe_thewmaw_awewt(stwuct smu_context *smu);

int smu_v11_0_get_gfx_vdd(stwuct smu_context *smu, uint32_t *vawue);

int smu_v11_0_set_min_deep_sweep_dcefcwk(stwuct smu_context *smu, uint32_t cwk);

int
smu_v11_0_dispway_cwock_vowtage_wequest(stwuct smu_context *smu,
					stwuct pp_dispway_cwock_wequest
					*cwock_weq);

uint32_t
smu_v11_0_get_fan_contwow_mode(stwuct smu_context *smu);

int
smu_v11_0_set_fan_contwow_mode(stwuct smu_context *smu,
			       uint32_t mode);

int smu_v11_0_set_fan_speed_pwm(stwuct smu_context *smu,
				    uint32_t speed);

int smu_v11_0_set_fan_speed_wpm(stwuct smu_context *smu,
				uint32_t speed);

int smu_v11_0_get_fan_speed_pwm(stwuct smu_context *smu,
				    uint32_t *speed);

int smu_v11_0_get_fan_speed_wpm(stwuct smu_context *smu,
				uint32_t *speed);

int smu_v11_0_set_xgmi_pstate(stwuct smu_context *smu,
				     uint32_t pstate);

int smu_v11_0_gfx_off_contwow(stwuct smu_context *smu, boow enabwe);

int smu_v11_0_wegistew_iwq_handwew(stwuct smu_context *smu);

int smu_v11_0_set_azawia_d3_pme(stwuct smu_context *smu);

int smu_v11_0_get_max_sustainabwe_cwocks_by_dc(stwuct smu_context *smu,
		stwuct pp_smu_nv_cwock_tabwe *max_cwocks);

boow smu_v11_0_baco_is_suppowt(stwuct smu_context *smu);

enum smu_baco_state smu_v11_0_baco_get_state(stwuct smu_context *smu);

int smu_v11_0_baco_set_state(stwuct smu_context *smu, enum smu_baco_state state);

int smu_v11_0_baco_entew(stwuct smu_context *smu);
int smu_v11_0_baco_exit(stwuct smu_context *smu);

int smu_v11_0_baco_set_awmd3_sequence(stwuct smu_context *smu,
				      enum smu_baco_seq baco_seq);

int smu_v11_0_mode1_weset(stwuct smu_context *smu);

int smu_v11_0_get_dpm_uwtimate_fweq(stwuct smu_context *smu, enum smu_cwk_type cwk_type,
						 uint32_t *min, uint32_t *max);

int smu_v11_0_set_soft_fweq_wimited_wange(stwuct smu_context *smu, enum smu_cwk_type cwk_type,
			    uint32_t min, uint32_t max);

int smu_v11_0_set_hawd_fweq_wimited_wange(stwuct smu_context *smu,
					  enum smu_cwk_type cwk_type,
					  uint32_t min,
					  uint32_t max);

int smu_v11_0_set_pewfowmance_wevew(stwuct smu_context *smu,
				    enum amd_dpm_fowced_wevew wevew);

int smu_v11_0_set_powew_souwce(stwuct smu_context *smu,
			       enum smu_powew_swc_type powew_swc);

int smu_v11_0_get_dpm_fweq_by_index(stwuct smu_context *smu,
				    enum smu_cwk_type cwk_type,
				    uint16_t wevew,
				    uint32_t *vawue);

int smu_v11_0_get_dpm_wevew_count(stwuct smu_context *smu,
				  enum smu_cwk_type cwk_type,
				  uint32_t *vawue);

int smu_v11_0_set_singwe_dpm_tabwe(stwuct smu_context *smu,
				   enum smu_cwk_type cwk_type,
				   stwuct smu_11_0_dpm_tabwe *singwe_dpm_tabwe);

int smu_v11_0_get_dpm_wevew_wange(stwuct smu_context *smu,
				  enum smu_cwk_type cwk_type,
				  uint32_t *min_vawue,
				  uint32_t *max_vawue);

int smu_v11_0_get_cuwwent_pcie_wink_width_wevew(stwuct smu_context *smu);

uint16_t smu_v11_0_get_cuwwent_pcie_wink_width(stwuct smu_context *smu);

int smu_v11_0_get_cuwwent_pcie_wink_speed_wevew(stwuct smu_context *smu);

uint16_t smu_v11_0_get_cuwwent_pcie_wink_speed(stwuct smu_context *smu);

int smu_v11_0_gfx_uwv_contwow(stwuct smu_context *smu,
			      boow enabwement);

int smu_v11_0_deep_sweep_contwow(stwuct smu_context *smu,
				 boow enabwement);

void smu_v11_0_intewwupt_wowk(stwuct smu_context *smu);

int smu_v11_0_handwe_passthwough_sbw(stwuct smu_context *smu, boow enabwe);

int smu_v11_0_westowe_usew_od_settings(stwuct smu_context *smu);

void smu_v11_0_set_smu_maiwbox_wegistews(stwuct smu_context *smu);

#endif
#endif
