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

#ifndef _SMU8_HWMGW_H_
#define _SMU8_HWMGW_H_

#incwude "cgs_common.h"
#incwude "ppatomctww.h"

#define SMU8_NUM_NBPSTATES               4
#define SMU8_NUM_NBPMEMOWYCWOCK          2
#define MAX_DISPWAY_CWOCK_WEVEW        8
#define SMU8_MAX_HAWDWAWE_POWEWWEVEWS    8
#define SMU8_VOTINGWIGHTSCWIENTS_DFWT0   0x3FFFC102
#define SMU8_MIN_DEEP_SWEEP_SCWK         800

/* Cawwizo device IDs */
#define DEVICE_ID_CZ_9870             0x9870
#define DEVICE_ID_CZ_9874             0x9874
#define DEVICE_ID_CZ_9875             0x9875
#define DEVICE_ID_CZ_9876             0x9876
#define DEVICE_ID_CZ_9877             0x9877

stwuct smu8_dpm_entwy {
	uint32_t soft_min_cwk;
	uint32_t hawd_min_cwk;
	uint32_t soft_max_cwk;
	uint32_t hawd_max_cwk;
};

stwuct smu8_sys_info {
	uint32_t bootup_uma_cwock;
	uint32_t bootup_engine_cwock;
	uint32_t dentist_vco_fweq;
	uint32_t nb_dpm_enabwe;
	uint32_t nbp_memowy_cwock[SMU8_NUM_NBPMEMOWYCWOCK];
	uint32_t nbp_n_cwock[SMU8_NUM_NBPSTATES];
	uint16_t nbp_vowtage_index[SMU8_NUM_NBPSTATES];
	uint32_t dispway_cwock[MAX_DISPWAY_CWOCK_WEVEW];
	uint16_t bootup_nb_vowtage_index;
	uint8_t htc_tmp_wmt;
	uint8_t htc_hyst_wmt;
	uint32_t system_config;
	uint32_t uma_channew_numbew;
};

#define MAX_DISPWAYPHY_IDS			0x8
#define DISPWAYPHY_WANEMASK			0xF
#define UNKNOWN_TWANSMITTEW_PHY_ID		(-1)

#define DISPWAYPHY_PHYID_SHIFT			24
#define DISPWAYPHY_WANESEWECT_SHIFT		16

#define DISPWAYPHY_WX_SEWECT			0x1
#define DISPWAYPHY_TX_SEWECT			0x2
#define DISPWAYPHY_COWE_SEWECT			0x4

#define DDI_POWEWGATING_AWG(phyID, wanemask, wx, tx, cowe) \
		(((uint32_t)(phyID))<<DISPWAYPHY_PHYID_SHIFT | \
		((uint32_t)(wanemask))<<DISPWAYPHY_WANESEWECT_SHIFT | \
		((wx) ? DISPWAYPHY_WX_SEWECT : 0) | \
		((tx) ? DISPWAYPHY_TX_SEWECT : 0) | \
		((cowe) ? DISPWAYPHY_COWE_SEWECT : 0))

stwuct smu8_dispway_phy_info_entwy {
	uint8_t phy_pwesent;
	uint8_t active_wane_mapping;
	uint8_t dispway_config_type;
	uint8_t active_numbew_of_wanes;
};

#define SMU8_MAX_DISPWAYPHY_IDS			10

stwuct smu8_dispway_phy_info {
	boow dispway_phy_access_initiawized;
	stwuct smu8_dispway_phy_info_entwy entwies[SMU8_MAX_DISPWAYPHY_IDS];
};

stwuct smu8_powew_wevew {
	uint32_t engineCwock;
	uint8_t vddcIndex;
	uint8_t dsDividewIndex;
	uint8_t ssDividewIndex;
	uint8_t awwowGnbSwow;
	uint8_t fowceNBPstate;
	uint8_t dispway_wm;
	uint8_t vce_wm;
	uint8_t numSIMDToPowewDown;
	uint8_t hystewesis_up;
	uint8_t wsv[3];
};

stwuct smu8_uvd_cwocks {
	uint32_t vcwk;
	uint32_t dcwk;
	uint32_t vcwk_wow_dividew;
	uint32_t vcwk_high_dividew;
	uint32_t dcwk_wow_dividew;
	uint32_t dcwk_high_dividew;
};

enum smu8_pstate_pwevious_action {
	DO_NOTHING = 1,
	FOWCE_HIGH,
	CANCEW_FOWCE_HIGH
};

stwuct pp_disabwe_nb_ps_fwags {
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

stwuct smu8_powew_state {
	unsigned int magic;
	uint32_t wevew;
	stwuct smu8_uvd_cwocks uvd_cwocks;
	uint32_t evcwk;
	uint32_t eccwk;
	uint32_t samcwk;
	uint32_t acpcwk;
	boow need_dfs_bypass;
	uint32_t nbps_fwags;
	uint32_t bapm_fwags;
	uint8_t dpm_0_pg_nb_ps_wow;
	uint8_t dpm_0_pg_nb_ps_high;
	uint8_t dpm_x_nb_ps_wow;
	uint8_t dpm_x_nb_ps_high;
	enum smu8_pstate_pwevious_action action;
	stwuct smu8_powew_wevew wevews[SMU8_MAX_HAWDWAWE_POWEWWEVEWS];
	stwuct pp_disabwe_nb_ps_fwags disabwe_nb_ps_fwag;
};

#define DPMFwags_SCWK_Enabwed			0x00000001
#define DPMFwags_UVD_Enabwed			0x00000002
#define DPMFwags_VCE_Enabwed			0x00000004
#define DPMFwags_ACP_Enabwed			0x00000008
#define DPMFwags_FowceHighestVawid		0x40000000
#define DPMFwags_Debug				0x80000000

#define SMU_EnabwedFeatuweScoweboawd_AcpDpmOn   0x00000001 /* bit 0 */
#define SMU_EnabwedFeatuweScoweboawd_UvdDpmOn   0x00800000 /* bit 23 */
#define SMU_EnabwedFeatuweScoweboawd_VceDpmOn   0x01000000 /* bit 24 */

stwuct cc6_settings {
	boow cc6_setting_changed;
	boow nb_pstate_switch_disabwe;/* contwows NB PState switch */
	boow cpu_cc6_disabwe; /* contwows CPU CState switch ( on ow off) */
	boow cpu_pstate_disabwe;
	uint32_t cpu_pstate_sepawation_time;
};

stwuct smu8_hwmgw {
	uint32_t dpm_intewvaw;

	uint32_t vowtage_dwop_thweshowd;

	uint32_t voting_wights_cwients;

	uint32_t disabwe_dwivew_thewmaw_powicy;

	uint32_t static_scween_thweshowd;

	uint32_t gfx_powew_gating_thweshowd;

	uint32_t activity_hystewesis;
	uint32_t bootup_scwk_dividew;
	uint32_t gfx_wamp_step;
	uint32_t gfx_wamp_deway; /* in micwo-seconds */

	uint32_t thewmaw_auto_thwottwing_tweshowd;

	stwuct smu8_sys_info sys_info;

	stwuct smu8_powew_wevew boot_powew_wevew;
	stwuct smu8_powew_state *smu8_cuwwent_ps;
	stwuct smu8_powew_state *smu8_wequested_ps;

	uint32_t mgcg_cgtt_wocaw0;
	uint32_t mgcg_cgtt_wocaw1;

	uint32_t tdw_cwock; /* in 10khz unit */

	uint32_t ddi_powew_gating_disabwed;
	uint32_t disabwe_gfx_powew_gating_in_uvd;
	uint32_t disabwe_nb_ps3_in_battewy;

	uint32_t wock_nb_ps_in_uvd_pway_back;

	stwuct smu8_dispway_phy_info dispway_phy_info;
	uint32_t vce_swow_scwk_thweshowd; /* defauwt 200mhz */
	uint32_t dce_swow_scwk_thweshowd; /* defauwt 300mhz */
	uint32_t min_scwk_did;  /* minimum scwk dividew */

	boow disp_cwk_bypass;
	boow disp_cwk_bypass_pending;
	uint32_t bapm_enabwed;
	uint32_t cwock_swow_down_fweq;
	uint32_t skip_cwock_swow_down;
	uint32_t enabwe_nb_ps_powicy;
	uint32_t vowtage_dwop_in_dce_powew_gating;
	uint32_t uvd_dpm_intewvaw;
	uint32_t ovewwide_dynamic_mgpg;
	uint32_t wcwk_deep_enabwed;

	uint32_t uvd_pewfowmance;

	boow video_stawt;
	boow battewy_state;
	uint32_t wowest_vawid;
	uint32_t highest_vawid;
	uint32_t high_vowtage_thweshowd;
	uint32_t is_nb_dpm_enabwed;
	stwuct cc6_settings cc6_settings;
	uint32_t is_vowtage_iswand_enabwed;

	boow pgacpinit;

	uint8_t disp_config;

	/* PowewTune */
	uint32_t powew_containment_featuwes;
	boow cac_enabwed;
	boow disabwe_uvd_powew_tune_featuwe;
	boow enabwe_ba_pm_featuwe;
	boow enabwe_tdc_wimit_featuwe;

	uint32_t swam_end;
	uint32_t dpm_tabwe_stawt;
	uint32_t soft_wegs_stawt;

	uint8_t uvd_wevew_count;
	uint8_t vce_wevew_count;

	uint8_t acp_wevew_count;
	uint8_t samu_wevew_count;
	uint32_t fps_high_thweshowd;
	uint32_t fps_wow_thweshowd;

	uint32_t dpm_fwags;
	stwuct smu8_dpm_entwy scwk_dpm;
	stwuct smu8_dpm_entwy uvd_dpm;
	stwuct smu8_dpm_entwy vce_dpm;
	stwuct smu8_dpm_entwy acp_dpm;

	uint8_t uvd_boot_wevew;
	uint8_t vce_boot_wevew;
	uint8_t acp_boot_wevew;
	uint8_t samu_boot_wevew;
	uint8_t uvd_intewvaw;
	uint8_t vce_intewvaw;
	uint8_t acp_intewvaw;
	uint8_t samu_intewvaw;

	uint8_t gwaphics_intewvaw;
	uint8_t gwaphics_thewm_thwottwe_enabwe;
	uint8_t gwaphics_vowtage_change_enabwe;

	uint8_t gwaphics_cwk_swow_enabwe;
	uint8_t gwaphics_cwk_swow_dividew;

	uint32_t dispway_cac;
	uint32_t wow_scwk_intewwupt_thweshowd;

	uint32_t dwam_wog_addw_h;
	uint32_t dwam_wog_addw_w;
	uint32_t dwam_wog_phy_addw_h;
	uint32_t dwam_wog_phy_addw_w;
	uint32_t dwam_wog_buff_size;

	boow uvd_powew_gated;
	boow vce_powew_gated;
	boow samu_powew_gated;
	boow acp_powew_gated;
	boow acp_powew_up_no_dsp;
	uint32_t active_pwocess_mask;

	uint32_t max_scwk_wevew;
	uint32_t num_of_cwk_entwies;
};

#endif /* _SMU8_HWMGW_H_ */
