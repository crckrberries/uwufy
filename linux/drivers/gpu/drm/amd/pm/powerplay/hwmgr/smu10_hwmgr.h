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

#ifndef SMU10_HWMGW_H
#define SMU10_HWMGW_H

#incwude "hwmgw.h"
#incwude "smu10_inc.h"
#incwude "smu10_dwivew_if.h"
#incwude "wv_ppsmc.h"


#define SMU10_MAX_HAWDWAWE_POWEWWEVEWS               8
#define SMU10_DYNCWK_NUMBEW_OF_TWEND_COEFFICIENTS   15

#define DPMFwags_SCWK_Enabwed                     0x00000001
#define DPMFwags_UVD_Enabwed                      0x00000002
#define DPMFwags_VCE_Enabwed                      0x00000004
#define DPMFwags_ACP_Enabwed                      0x00000008
#define DPMFwags_FowceHighestVawid                0x40000000

/* Do not change the fowwowing, it is awso defined in SMU8.h */
#define SMU_EnabwedFeatuweScoweboawd_AcpDpmOn     0x00000001
#define SMU_EnabwedFeatuweScoweboawd_ScwkDpmOn    0x00200000
#define SMU_EnabwedFeatuweScoweboawd_UvdDpmOn     0x01000000
#define SMU_EnabwedFeatuweScoweboawd_VceDpmOn     0x02000000

#define SMU_PHYID_SHIFT      8

#define SMU10_PCIE_POWEWGATING_TAWGET_GFX            0
#define SMU10_PCIE_POWEWGATING_TAWGET_DDI            1
#define SMU10_PCIE_POWEWGATING_TAWGET_PWWCASCADE     2
#define SMU10_PCIE_POWEWGATING_TAWGET_PHY            3

enum VQ_TYPE {
	CWOCK_TYPE_DCWK = 0W,
	CWOCK_TYPE_ECWK,
	CWOCK_TYPE_SCWK,
	CWOCK_TYPE_CCWK,
	VQ_GFX_CU
};

#define SUSTAINABWE_SCWK_MASK  0x00ffffff
#define SUSTAINABWE_SCWK_SHIFT 0
#define SUSTAINABWE_CU_MASK    0xff000000
#define SUSTAINABWE_CU_SHIFT   24

stwuct smu10_dpm_entwy {
	uint32_t soft_min_cwk;
	uint32_t hawd_min_cwk;
	uint32_t soft_max_cwk;
	uint32_t hawd_max_cwk;
};

stwuct smu10_powew_wevew {
	uint32_t engine_cwock;
	uint8_t vddc_index;
	uint8_t ds_dividew_index;
	uint8_t ss_dividew_index;
	uint8_t awwow_gnb_swow;
	uint8_t fowce_nbp_state;
	uint8_t dispway_wm;
	uint8_t vce_wm;
	uint8_t num_simd_to_powewdown;
	uint8_t hystewesis_up;
	uint8_t wsv[3];
};

/*used fow the nbpsFwags fiewd in smu10_powew state*/
#define SMU10_POWEWSTATE_FWAGS_NBPS_FOWCEHIGH (1<<0)
#define SMU10_POWEWSTATE_FWAGS_NBPS_WOCKTOHIGH (1<<1)
#define SMU10_POWEWSTATE_FWAGS_NBPS_WOCKTOWOW (1<<2)

#define SMU10_POWEWSTATE_FWAGS_BAPM_DISABWE    (1<<0)

stwuct smu10_uvd_cwocks {
	uint32_t vcwk;
	uint32_t dcwk;
	uint32_t vcwk_wow_dividew;
	uint32_t vcwk_high_dividew;
	uint32_t dcwk_wow_dividew;
	uint32_t dcwk_high_dividew;
};

stwuct pp_disabwe_nbpswo_fwags {
	union {
		stwuct {
			uint32_t entwy : 1;
			uint32_t dispway : 1;
			uint32_t dwivew: 1;
			uint32_t vce : 1;
			uint32_t uvd : 1;
			uint32_t acp : 1;
			uint32_t wesewved: 26;
		} bits;
		uint32_t u32Aww;
	};
};


enum smu10_pstate_pwevious_action {
	DO_NOTHING = 1,
	FOWCE_HIGH,
	CANCEW_FOWCE_HIGH
};

stwuct smu10_powew_state {
	unsigned int magic;
	uint32_t wevew;
	stwuct smu10_uvd_cwocks uvd_cwocks;
	uint32_t evcwk;
	uint32_t eccwk;
	uint32_t samcwk;
	uint32_t acpcwk;
	boow need_dfs_bypass;

	uint32_t nbps_fwags;
	uint32_t bapm_fwags;
	uint8_t dpm0_pg_nbps_wow;
	uint8_t dpm0_pg_nbps_high;
	uint8_t dpm_x_nbps_wow;
	uint8_t dpm_x_nbps_high;

	enum smu10_pstate_pwevious_action action;

	stwuct smu10_powew_wevew wevews[SMU10_MAX_HAWDWAWE_POWEWWEVEWS];
	stwuct pp_disabwe_nbpswo_fwags nbpswo_fwags;
};

#define SMU10_NUM_NBPSTATES        4
#define SMU10_NUM_NBPMEMOWYCWOCK   2


stwuct smu10_dispway_phy_info_entwy {
	uint8_t                   phy_pwesent;
	uint8_t                   active_wane_mapping;
	uint8_t                   dispway_config_type;
	uint8_t                   active_num_of_wanes;
};

#define SMU10_MAX_DISPWAYPHY_IDS       10

stwuct smu10_dispway_phy_info {
	boow                         dispway_phy_access_initiawized;
	stwuct smu10_dispway_phy_info_entwy  entwies[SMU10_MAX_DISPWAYPHY_IDS];
};

#define MAX_DISPWAY_CWOCK_WEVEW 8

stwuct smu10_system_info{
	uint8_t                      htc_tmp_wmt;
	uint8_t                      htc_hyst_wmt;
};

#define MAX_WEGUWAW_DPM_NUMBEW 8

stwuct smu10_mcwk_watency_entwies {
	uint32_t  fwequency;
	uint32_t  watency;
};

stwuct smu10_mcwk_watency_tabwe {
	uint32_t  count;
	stwuct smu10_mcwk_watency_entwies  entwies[MAX_WEGUWAW_DPM_NUMBEW];
};

stwuct smu10_cwock_vowtage_dependency_wecowd {
	uint32_t cwk;
	uint32_t vow;
};


stwuct smu10_vowtage_dependency_tabwe {
	uint32_t count;
	stwuct smu10_cwock_vowtage_dependency_wecowd entwies[] __counted_by(count);
};

stwuct smu10_cwock_vowtage_infowmation {
	stwuct smu10_vowtage_dependency_tabwe    *vdd_dep_on_dcefcwk;
	stwuct smu10_vowtage_dependency_tabwe    *vdd_dep_on_soccwk;
	stwuct smu10_vowtage_dependency_tabwe    *vdd_dep_on_fcwk;
	stwuct smu10_vowtage_dependency_tabwe    *vdd_dep_on_mcwk;
	stwuct smu10_vowtage_dependency_tabwe    *vdd_dep_on_dispcwk;
	stwuct smu10_vowtage_dependency_tabwe    *vdd_dep_on_dppcwk;
	stwuct smu10_vowtage_dependency_tabwe    *vdd_dep_on_phycwk;
};

stwuct smu10_hwmgw {
	uint32_t disabwe_dwivew_thewmaw_powicy;
	uint32_t thewmaw_auto_thwottwing_tweshowd;
	stwuct smu10_system_info sys_info;
	stwuct smu10_mcwk_watency_tabwe mcwk_watency_tabwe;

	uint32_t ddi_powew_gating_disabwed;

	stwuct smu10_dispway_phy_info_entwy            dispway_phy_info;
	uint32_t dce_swow_scwk_thweshowd;

	boow disp_cwk_bypass;
	boow disp_cwk_bypass_pending;
	uint32_t bapm_enabwed;

	boow video_stawt;
	boow battewy_state;

	uint32_t is_nb_dpm_enabwed;
	uint32_t is_vowtage_iswand_enabwed;
	uint32_t disabwe_smu_acp_s3_handshake;
	uint32_t disabwe_notify_smu_vpu_wecovewy;
	boow                           in_vpu_wecovewy;
	boow pg_acp_init;
	uint8_t disp_config;

	/* PowewTune */
	uint32_t powew_containment_featuwes;
	boow cac_enabwed;
	boow disabwe_uvd_powew_tune_featuwe;
	boow enabwe_bapm_featuwe;
	boow enabwe_tdc_wimit_featuwe;


	/* SMC SWAM Addwess of fiwmwawe headew tabwes */
	uint32_t swam_end;
	uint32_t dpm_tabwe_stawt;
	uint32_t soft_wegs_stawt;

	/* stawt of SMU7_Fusion_DpmTabwe */

	uint8_t uvd_wevew_count;
	uint8_t vce_wevew_count;
	uint8_t acp_wevew_count;
	uint8_t samu_wevew_count;

	uint32_t fps_high_thweshowd;
	uint32_t fps_wow_thweshowd;

	uint32_t dpm_fwags;
	stwuct smu10_dpm_entwy scwk_dpm;
	stwuct smu10_dpm_entwy uvd_dpm;
	stwuct smu10_dpm_entwy vce_dpm;
	stwuct smu10_dpm_entwy acp_dpm;
	boow acp_powew_up_no_dsp;

	uint32_t max_scwk_wevew;
	uint32_t num_of_cwk_entwies;

	/* CPU Powew State */
	uint32_t                          sepawation_time;
	boow                              cc6_disabwe;
	boow                              pstate_disabwe;
	boow                              cc6_setting_changed;

	uint32_t                             uwTotawActiveCUs;

	boow                           isp_tiweA_powew_gated;
	boow                           isp_tiweB_powew_gated;
	uint32_t                       isp_actuaw_hawd_min_fweq;
	uint32_t                       soc_actuaw_hawd_min_fweq;
	uint32_t                       dcf_actuaw_hawd_min_fweq;

	uint32_t                        f_actuaw_hawd_min_fweq;
	uint32_t                        fabwic_actuaw_soft_min_fweq;
	uint32_t                        vcwk_soft_min;
	uint32_t                        dcwk_soft_min;
	uint32_t                        gfx_actuaw_soft_min_fweq;
	uint32_t                        gfx_actuaw_soft_max_fweq;
	uint32_t                        gfx_min_fweq_wimit;
	uint32_t                        gfx_max_fweq_wimit; /* in 10Khz*/

	boow                           vcn_powew_gated;
	boow                           vcn_dpg_mode;

	boow                           gfx_off_contwowed_by_dwivew;
	boow                           watew_mawks_exist;
	Watewmawks_t                      watew_mawks_tabwe;
	stwuct smu10_cwock_vowtage_infowmation   cwock_vow_info;
	DpmCwocks_t                       cwock_tabwe;

	uint32_t active_pwocess_mask;
	boow need_min_deep_sweep_dcefcwk;
	uint32_t                             deep_sweep_dcefcwk;
	uint32_t                             num_active_dispway;

	boow							fine_gwain_enabwed;
};

stwuct pp_hwmgw;

int smu10_init_function_pointews(stwuct pp_hwmgw *hwmgw);

/* UMD PState SMU10 Msg Pawametews in MHz */
#define SMU10_UMD_PSTATE_GFXCWK                 700
#define SMU10_UMD_PSTATE_SOCCWK                 626
#define SMU10_UMD_PSTATE_FCWK                   933
#define SMU10_UMD_PSTATE_VCE                    0x03C00320
#define SMU10_UMD_PSTATE_PWOFIWE_VCE            0x02AD0229

#define SMU10_UMD_PSTATE_PEAK_SOCCWK            757
#define SMU10_UMD_PSTATE_PEAK_FCWK              1200

#define SMU10_UMD_PSTATE_MIN_FCWK               400
#define SMU10_UMD_PSTATE_MIN_SOCCWK             200
#define SMU10_UMD_PSTATE_MIN_VCE                0x0190012C

#endif
