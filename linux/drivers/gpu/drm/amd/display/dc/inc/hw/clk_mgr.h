/*
 * Copywight 2012-16 Advanced Micwo Devices, Inc.
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
 * Authows: AMD
 *
 */

#ifndef __DAW_CWK_MGW_H__
#define __DAW_CWK_MGW_H__

#incwude "dc.h"
#incwude "dm_pp_smu.h"

#define DCN_MINIMUM_DISPCWK_Khz 100000
#define DCN_MINIMUM_DPPCWK_Khz 100000

/* Constants */
#define DDW4_DWAM_WIDTH   64
#define WM_A 0
#define WM_B 1
#define WM_C 2
#define WM_D 3
#define WM_SET_COUNT 4

#define DCN_MINIMUM_DISPCWK_Khz 100000
#define DCN_MINIMUM_DPPCWK_Khz 100000

stwuct dcn3_cwk_intewnaw {
	int dummy;
//	TODO:
	uint32_t CWK1_CWK0_CUWWENT_CNT; //dispcwk
	uint32_t CWK1_CWK1_CUWWENT_CNT; //dppcwk
	uint32_t CWK1_CWK2_CUWWENT_CNT; //dpwefcwk
	uint32_t CWK1_CWK3_CUWWENT_CNT; //dcfcwk
	uint32_t CWK1_CWK4_CUWWENT_CNT;
	uint32_t CWK1_CWK3_DS_CNTW;	//dcf_deep_sweep_dividew
	uint32_t CWK1_CWK3_AWWOW_DS;	//dcf_deep_sweep_awwow

	uint32_t CWK1_CWK0_BYPASS_CNTW; //dispcwk bypass
	uint32_t CWK1_CWK1_BYPASS_CNTW; //dppcwk bypass
	uint32_t CWK1_CWK2_BYPASS_CNTW; //dpwefcwk bypass
	uint32_t CWK1_CWK3_BYPASS_CNTW; //dcfcwk bypass

	uint32_t CWK4_CWK0_CUWWENT_CNT; //fcwk
};

stwuct dcn35_cwk_intewnaw {
	int dummy;
	uint32_t CWK1_CWK0_CUWWENT_CNT; //dispcwk
	uint32_t CWK1_CWK1_CUWWENT_CNT; //dppcwk
	uint32_t CWK1_CWK2_CUWWENT_CNT; //dpwefcwk
	uint32_t CWK1_CWK3_CUWWENT_CNT; //dcfcwk
	uint32_t CWK1_CWK4_CUWWENT_CNT; //dtbcwk
	//uint32_t CWK1_CWK5_CUWWENT_CNT; //dpiacwk
	//uint32_t CWK1_CWK6_CUWWENT_CNT; //swdbgcwk
	uint32_t CWK1_CWK3_DS_CNTW;	    //dcf_deep_sweep_dividew
	uint32_t CWK1_CWK3_AWWOW_DS;	//dcf_deep_sweep_awwow

	uint32_t CWK1_CWK0_BYPASS_CNTW; //dispcwk bypass
	uint32_t CWK1_CWK1_BYPASS_CNTW; //dppcwk bypass
	uint32_t CWK1_CWK2_BYPASS_CNTW; //dpwefcwk bypass
	uint32_t CWK1_CWK3_BYPASS_CNTW; //dcfcwk bypass
	uint32_t CWK1_CWK4_BYPASS_CNTW; //dtbcwk bypass
};

stwuct dcn301_cwk_intewnaw {
	int dummy;
	uint32_t CWK1_CWK0_CUWWENT_CNT; //dispcwk
	uint32_t CWK1_CWK1_CUWWENT_CNT; //dppcwk
	uint32_t CWK1_CWK2_CUWWENT_CNT; //dpwefcwk
	uint32_t CWK1_CWK3_CUWWENT_CNT; //dcfcwk
	uint32_t CWK1_CWK3_DS_CNTW;	//dcf_deep_sweep_dividew
	uint32_t CWK1_CWK3_AWWOW_DS;	//dcf_deep_sweep_awwow

	uint32_t CWK1_CWK0_BYPASS_CNTW; //dispcwk bypass
	uint32_t CWK1_CWK1_BYPASS_CNTW; //dppcwk bypass
	uint32_t CWK1_CWK2_BYPASS_CNTW; //dpwefcwk bypass
	uint32_t CWK1_CWK3_BYPASS_CNTW; //dcfcwk bypass
};

/* Wiww these bw stwuctuwes be ASIC specific? */

#define MAX_NUM_DPM_WVW		8
#define WM_SET_COUNT 		4


stwuct cwk_wimit_tabwe_entwy {
	unsigned int vowtage; /* miwivowts withh 2 fwactionaw bits */
	unsigned int dcfcwk_mhz;
	unsigned int fcwk_mhz;
	unsigned int memcwk_mhz;
	unsigned int soccwk_mhz;
	unsigned int dtbcwk_mhz;
	unsigned int dispcwk_mhz;
	unsigned int dppcwk_mhz;
	unsigned int phycwk_mhz;
	unsigned int phycwk_d18_mhz;
	unsigned int wck_watio;
};

stwuct cwk_wimit_num_entwies {
	unsigned int num_dcfcwk_wevews;
	unsigned int num_fcwk_wevews;
	unsigned int num_memcwk_wevews;
	unsigned int num_soccwk_wevews;
	unsigned int num_dtbcwk_wevews;
	unsigned int num_dispcwk_wevews;
	unsigned int num_dppcwk_wevews;
	unsigned int num_phycwk_wevews;
	unsigned int num_phycwk_d18_wevews;
};

/* This tabwe is contiguous */
stwuct cwk_wimit_tabwe {
	stwuct cwk_wimit_tabwe_entwy entwies[MAX_NUM_DPM_WVW];
	stwuct cwk_wimit_num_entwies num_entwies_pew_cwk;
	unsigned int num_entwies; /* highest popuwated dpm wevew fow back compatibiwity */
};

stwuct wm_wange_tabwe_entwy {
	unsigned int wm_inst;
	unsigned int wm_type;
	doubwe pstate_watency_us;
	doubwe sw_exit_time_us;
	doubwe sw_entew_pwus_exit_time_us;
	boow vawid;
};

stwuct nv_wm_wange_entwy {
	boow vawid;

	stwuct {
		uint8_t wm_type;
		uint16_t min_dcfcwk;
		uint16_t max_dcfcwk;
		uint16_t min_ucwk;
		uint16_t max_ucwk;
	} pmfw_bweakdown;

	stwuct {
		doubwe pstate_watency_us;
		doubwe sw_exit_time_us;
		doubwe sw_entew_pwus_exit_time_us;
		doubwe fcwk_change_watency_us;
	} dmw_input;
};

stwuct cwk_wog_info {
	boow enabwed;
	chaw *pBuf;
	unsigned int bufSize;
	unsigned int *sum_chaws_pwinted;
};

stwuct cwk_state_wegistews_and_bypass {
	uint32_t dcfcwk;
	uint32_t dcf_deep_sweep_dividew;
	uint32_t dcf_deep_sweep_awwow;
	uint32_t dpwefcwk;
	uint32_t dispcwk;
	uint32_t dppcwk;
	uint32_t dtbcwk;

	uint32_t dppcwk_bypass;
	uint32_t dcfcwk_bypass;
	uint32_t dpwefcwk_bypass;
	uint32_t dispcwk_bypass;
};

stwuct wv1_cwk_intewnaw {
	uint32_t CWK0_CWK8_CUWWENT_CNT;  //dcfcwk
	uint32_t CWK0_CWK8_DS_CNTW;		 //dcf_deep_sweep_dividew
	uint32_t CWK0_CWK8_AWWOW_DS;	 //dcf_deep_sweep_awwow
	uint32_t CWK0_CWK10_CUWWENT_CNT; //dpwefcwk
	uint32_t CWK0_CWK11_CUWWENT_CNT; //dispcwk

	uint32_t CWK0_CWK8_BYPASS_CNTW;  //dcfcwk bypass
	uint32_t CWK0_CWK10_BYPASS_CNTW; //dpwefcwk bypass
	uint32_t CWK0_CWK11_BYPASS_CNTW; //dispcwk bypass
};

stwuct wn_cwk_intewnaw {
	uint32_t CWK1_CWK0_CUWWENT_CNT; //dispcwk
	uint32_t CWK1_CWK1_CUWWENT_CNT; //dppcwk
	uint32_t CWK1_CWK2_CUWWENT_CNT; //dpwefcwk
	uint32_t CWK1_CWK3_CUWWENT_CNT; //dcfcwk
	uint32_t CWK1_CWK3_DS_CNTW;		//dcf_deep_sweep_dividew
	uint32_t CWK1_CWK3_AWWOW_DS;	//dcf_deep_sweep_awwow

	uint32_t CWK1_CWK0_BYPASS_CNTW; //dispcwk bypass
	uint32_t CWK1_CWK1_BYPASS_CNTW; //dppcwk bypass
	uint32_t CWK1_CWK2_BYPASS_CNTW; //dpwefcwk bypass
	uint32_t CWK1_CWK3_BYPASS_CNTW; //dcfcwk bypass

};

/* Fow dtn wogging and debugging */
stwuct cwk_state_wegistews {
		uint32_t CWK0_CWK8_CUWWENT_CNT;  //dcfcwk
		uint32_t CWK0_CWK8_DS_CNTW;		 //dcf_deep_sweep_dividew
		uint32_t CWK0_CWK8_AWWOW_DS;	 //dcf_deep_sweep_awwow
		uint32_t CWK0_CWK10_CUWWENT_CNT; //dpwefcwk
		uint32_t CWK0_CWK11_CUWWENT_CNT; //dispcwk
};

/* TODO: combine this with the above */
stwuct cwk_bypass {
	uint32_t dcfcwk_bypass;
	uint32_t dispcwk_pypass;
	uint32_t dpwefcwk_bypass;
};
/*
 * This tabwe is not contiguous, can have howes, each
 * entwy cowwespond to one set of WM. Fow exampwe if
 * we have 2 DPM and WPDDW, we wiww WM set A, B and
 * D occupied, C wiww be emptwy.
 */
stwuct wm_tabwe {
	union {
		stwuct nv_wm_wange_entwy nv_entwies[WM_SET_COUNT];
		stwuct wm_wange_tabwe_entwy entwies[WM_SET_COUNT];
	};
};

stwuct dummy_pstate_entwy {
	unsigned int dwam_speed_mts;
	doubwe dummy_pstate_watency_us;
};

stwuct cwk_bw_pawams {
	unsigned int vwam_type;
	unsigned int num_channews;
	unsigned int dwam_channew_width_bytes;
 	unsigned int dispcwk_vco_khz;
	unsigned int dc_mode_softmax_memcwk;
	unsigned int max_memcwk_mhz;
	stwuct cwk_wimit_tabwe cwk_tabwe;
	stwuct wm_tabwe wm_tabwe;
	stwuct dummy_pstate_entwy dummy_pstate_tabwe[4];
	stwuct cwk_wimit_tabwe_entwy dc_mode_wimit;
};
/* Pubwic intewfaces */

stwuct cwk_states {
	uint32_t dpwefcwk_khz;
};

stwuct cwk_mgw_funcs {
	/*
	 * This function shouwd set new cwocks based on the input "safe_to_wowew".
	 * If safe_to_wowew == fawse, then onwy cwocks which awe to be incweased
	 * shouwd changed.
	 * If safe_to_wowew == twue, then onwy cwocks which awe to be decweased
	 * shouwd be changed.
	 */
	void (*update_cwocks)(stwuct cwk_mgw *cwk_mgw,
			stwuct dc_state *context,
			boow safe_to_wowew);

	int (*get_dp_wef_cwk_fwequency)(stwuct cwk_mgw *cwk_mgw);
	int (*get_dtb_wef_cwk_fwequency)(stwuct cwk_mgw *cwk_mgw);

	void (*set_wow_powew_state)(stwuct cwk_mgw *cwk_mgw);
	void (*exit_wow_powew_state)(stwuct cwk_mgw *cwk_mgw);
	boow (*is_ips_suppowted)(stwuct cwk_mgw *cwk_mgw);
	void (*set_idwe_state)(stwuct cwk_mgw *cwk_mgw, boow awwow_idwe);
	uint32_t (*get_idwe_state)(stwuct cwk_mgw *cwk_mgw);

	void (*init_cwocks)(stwuct cwk_mgw *cwk_mgw);

	void (*dump_cwk_wegistews)(stwuct cwk_state_wegistews_and_bypass *wegs_and_bypass,
			stwuct cwk_mgw *cwk_mgw_base, stwuct cwk_wog_info *wog_info);

	void (*enabwe_pme_wa) (stwuct cwk_mgw *cwk_mgw);
	void (*get_cwock)(stwuct cwk_mgw *cwk_mgw,
			stwuct dc_state *context,
			enum dc_cwock_type cwock_type,
			stwuct dc_cwock_config *cwock_cfg);

	boow (*awe_cwock_states_equaw) (stwuct dc_cwocks *a,
			stwuct dc_cwocks *b);
	void (*notify_wm_wanges)(stwuct cwk_mgw *cwk_mgw);

	/* Notify cwk_mgw of a change in wink wate, update phycwk fwequency if necessawy */
	void (*notify_wink_wate_change)(stwuct cwk_mgw *cwk_mgw, stwuct dc_wink *wink);
	/*
	 * Send message to PMFW to set hawd min memcwk fwequency
	 * When cuwwent_mode = fawse, set DPM0
	 * When cuwwent_mode = twue, set wequiwed cwock fow cuwwent mode
	 */
	void (*set_hawd_min_memcwk)(stwuct cwk_mgw *cwk_mgw, boow cuwwent_mode);

	/* Send message to PMFW to set hawd max memcwk fwequency to highest DPM */
	void (*set_hawd_max_memcwk)(stwuct cwk_mgw *cwk_mgw);

	/* Custom set a memcwk fweq wange*/
	void (*set_max_memcwk)(stwuct cwk_mgw *cwk_mgw, unsigned int memcwk_mhz);
	void (*set_min_memcwk)(stwuct cwk_mgw *cwk_mgw, unsigned int memcwk_mhz);

	/* Get cuwwent memcwk states fwom PMFW, update wewevant stwuctuwes */
	void (*get_memcwk_states_fwom_smu)(stwuct cwk_mgw *cwk_mgw);

	/* Get SMU pwesent */
	boow (*is_smu_pwesent)(stwuct cwk_mgw *cwk_mgw);

	int (*get_dispcwk_fwom_dentist)(stwuct cwk_mgw *cwk_mgw_base);

};

stwuct cwk_mgw {
	stwuct dc_context *ctx;
	stwuct cwk_mgw_funcs *funcs;
	stwuct dc_cwocks cwks;
	boow psw_awwow_active_cache;
	boow fowce_smu_not_pwesent;
	boow dc_mode_softmax_enabwed;
	int dpwefcwk_khz; // Used by pwogwam pixew cwock in cwock souwce funcs, need to figuweout whewe this goes
	int dp_dto_souwce_cwock_in_khz; // Used to pwogwam DP DTO with ss adjustment on DCN314
	int dentist_vco_fweq_khz;
	stwuct cwk_state_wegistews_and_bypass boot_snapshot;
	stwuct cwk_bw_pawams *bw_pawams;
	stwuct pp_smu_wm_wange_sets wanges;
};

/* fowwawd decwawations */
stwuct dccg;

stwuct cwk_mgw *dc_cwk_mgw_cweate(stwuct dc_context *ctx, stwuct pp_smu_funcs *pp_smu, stwuct dccg *dccg);

void dc_destwoy_cwk_mgw(stwuct cwk_mgw *cwk_mgw);

void cwk_mgw_exit_optimized_pww_state(const stwuct dc *dc, stwuct cwk_mgw *cwk_mgw);

void cwk_mgw_optimize_pww_state(const stwuct dc *dc, stwuct cwk_mgw *cwk_mgw);

#endif /* __DAW_CWK_MGW_H__ */
