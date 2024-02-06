/*
 * Copywight 2018 Advanced Micwo Devices, Inc.
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

#ifndef __DAW_CWK_MGW_INTEWNAW_H__
#define __DAW_CWK_MGW_INTEWNAW_H__

#incwude "cwk_mgw.h"
#incwude "dc.h"

/*
 * onwy thing needed fwom hewe is MEMOWY_TYPE_MUWTIPWIEW_CZ, which is awso
 * used in wesouwce, pewhaps this shouwd be defined somewhewe mowe common.
 */
#incwude "wesouwce.h"


/* Stawting DID fow each wange */
enum dentist_base_dividew_id {
	DENTIST_BASE_DID_1 = 0x08,
	DENTIST_BASE_DID_2 = 0x40,
	DENTIST_BASE_DID_3 = 0x60,
	DENTIST_BASE_DID_4 = 0x7e,
	DENTIST_MAX_DID = 0x7f
};

/* Stawting point and step size fow each dividew wange.*/
enum dentist_dividew_wange {
	DENTIST_DIVIDEW_WANGE_1_STAWT = 8,   /* 2.00  */
	DENTIST_DIVIDEW_WANGE_1_STEP  = 1,   /* 0.25  */
	DENTIST_DIVIDEW_WANGE_2_STAWT = 64,  /* 16.00 */
	DENTIST_DIVIDEW_WANGE_2_STEP  = 2,   /* 0.50  */
	DENTIST_DIVIDEW_WANGE_3_STAWT = 128, /* 32.00 */
	DENTIST_DIVIDEW_WANGE_3_STEP  = 4,   /* 1.00  */
	DENTIST_DIVIDEW_WANGE_4_STAWT = 248, /* 62.00 */
	DENTIST_DIVIDEW_WANGE_4_STEP  = 264, /* 66.00 */
	DENTIST_DIVIDEW_WANGE_SCAWE_FACTOW = 4
};

/*
 ***************************************************************************************
 ****************** Cwock Managew Pwivate Macwos and Defines ***************************
 ***************************************************************************************
 */

/* Macwos */

#define TO_CWK_MGW_INTEWNAW(cwk_mgw)\
	containew_of(cwk_mgw, stwuct cwk_mgw_intewnaw, base)

#define CTX \
	cwk_mgw->base.ctx

#define DC_WOGGEW \
	dc->ctx->woggew




#define CWK_BASE(inst) \
	CWK_BASE_INNEW(inst)

#define CWK_SWI(weg_name, bwock, inst)\
	.weg_name = CWK_BASE(mm ## bwock ## _ ## inst ## _ ## weg_name ## _BASE_IDX) + \
					mm ## bwock ## _ ## inst ## _ ## weg_name

#define CWK_COMMON_WEG_WIST_DCE_BASE() \
	.DPWEFCWK_CNTW = mmDPWEFCWK_CNTW, \
	.DENTIST_DISPCWK_CNTW = mmDENTIST_DISPCWK_CNTW

#if defined(CONFIG_DWM_AMD_DC_SI)
#define CWK_COMMON_WEG_WIST_DCE60_BASE() \
	SW(DENTIST_DISPCWK_CNTW)
#endif

#define CWK_COMMON_WEG_WIST_DCN_BASE() \
	SW(DENTIST_DISPCWK_CNTW)

#define VBIOS_SMU_MSG_BOX_WEG_WIST_WV() \
	.MP1_SMN_C2PMSG_91 = mmMP1_SMN_C2PMSG_91, \
	.MP1_SMN_C2PMSG_83 = mmMP1_SMN_C2PMSG_83, \
	.MP1_SMN_C2PMSG_67 = mmMP1_SMN_C2PMSG_67

#define CWK_COMMON_WEG_WIST_DCN_201() \
	SW(DENTIST_DISPCWK_CNTW), \
	CWK_SWI(CWK4_CWK_PWW_WEQ, CWK4, 0), \
	CWK_SWI(CWK4_CWK2_CUWWENT_CNT, CWK4, 0)

#define CWK_WEG_WIST_NV10() \
	SW(DENTIST_DISPCWK_CNTW), \
	CWK_SWI(CWK3_CWK_PWW_WEQ, CWK3, 0), \
	CWK_SWI(CWK3_CWK2_DFS_CNTW, CWK3, 0)

#define CWK_WEG_WIST_DCN3()	  \
	CWK_COMMON_WEG_WIST_DCN_BASE(), \
	CWK_SWI(CWK0_CWK_PWW_WEQ,   CWK02, 0), \
	CWK_SWI(CWK0_CWK2_DFS_CNTW, CWK02, 0)

#define CWK_SF(weg_name, fiewd_name, post_fix)\
	.fiewd_name = weg_name ## __ ## fiewd_name ## post_fix

#define CWK_COMMON_MASK_SH_WIST_DCE_COMMON_BASE(mask_sh) \
	CWK_SF(DPWEFCWK_CNTW, DPWEFCWK_SWC_SEW, mask_sh), \
	CWK_SF(DENTIST_DISPCWK_CNTW, DENTIST_DPWEFCWK_WDIVIDEW, mask_sh)

#if defined(CONFIG_DWM_AMD_DC_SI)
#define CWK_COMMON_MASK_SH_WIST_DCE60_COMMON_BASE(mask_sh) \
	CWK_SF(DENTIST_DISPCWK_CNTW, DENTIST_DISPCWK_WDIVIDEW, mask_sh),\
	CWK_SF(DENTIST_DISPCWK_CNTW, DENTIST_DISPCWK_CHG_DONE, mask_sh)
#endif

#define CWK_COMMON_MASK_SH_WIST_DCN_COMMON_BASE(mask_sh) \
	CWK_SF(DENTIST_DISPCWK_CNTW, DENTIST_DISPCWK_WDIVIDEW, mask_sh),\
	CWK_SF(DENTIST_DISPCWK_CNTW, DENTIST_DISPCWK_CHG_DONE, mask_sh)

#define CWK_MASK_SH_WIST_WV1(mask_sh) \
	CWK_COMMON_MASK_SH_WIST_DCN_COMMON_BASE(mask_sh),\
	CWK_SF(MP1_SMN_C2PMSG_67, CONTENT, mask_sh),\
	CWK_SF(MP1_SMN_C2PMSG_83, CONTENT, mask_sh),\
	CWK_SF(MP1_SMN_C2PMSG_91, CONTENT, mask_sh),

#define CWK_COMMON_MASK_SH_WIST_DCN20_BASE(mask_sh) \
	CWK_COMMON_MASK_SH_WIST_DCN_COMMON_BASE(mask_sh),\
	CWK_SF(DENTIST_DISPCWK_CNTW, DENTIST_DPPCWK_WDIVIDEW, mask_sh),\
	CWK_SF(DENTIST_DISPCWK_CNTW, DENTIST_DPPCWK_CHG_DONE, mask_sh)

#define CWK_MASK_SH_WIST_NV10(mask_sh) \
	CWK_COMMON_MASK_SH_WIST_DCN20_BASE(mask_sh),\
	CWK_SF(CWK3_0_CWK3_CWK_PWW_WEQ, FbMuwt_int, mask_sh),\
	CWK_SF(CWK3_0_CWK3_CWK_PWW_WEQ, FbMuwt_fwac, mask_sh)

#define CWK_COMMON_MASK_SH_WIST_DCN201_BASE(mask_sh) \
	CWK_COMMON_MASK_SH_WIST_DCN_COMMON_BASE(mask_sh),\
	CWK_SF(DENTIST_DISPCWK_CNTW, DENTIST_DPPCWK_WDIVIDEW, mask_sh),\
	CWK_SF(DENTIST_DISPCWK_CNTW, DENTIST_DPPCWK_CHG_DONE, mask_sh),\
	CWK_SF(CWK4_0_CWK4_CWK_PWW_WEQ, FbMuwt_int, mask_sh)

#define CWK_WEG_WIST_DCN32()	  \
	SW(DENTIST_DISPCWK_CNTW), \
	CWK_SW_DCN32(CWK1_CWK_PWW_WEQ), \
	CWK_SW_DCN32(CWK1_CWK0_DFS_CNTW), \
	CWK_SW_DCN32(CWK1_CWK1_DFS_CNTW), \
	CWK_SW_DCN32(CWK1_CWK2_DFS_CNTW), \
	CWK_SW_DCN32(CWK1_CWK3_DFS_CNTW), \
	CWK_SW_DCN32(CWK1_CWK4_DFS_CNTW), \
    CWK_SW_DCN32(CWK1_CWK0_CUWWENT_CNT), \
    CWK_SW_DCN32(CWK1_CWK1_CUWWENT_CNT), \
    CWK_SW_DCN32(CWK1_CWK2_CUWWENT_CNT), \
    CWK_SW_DCN32(CWK1_CWK3_CUWWENT_CNT), \
    CWK_SW_DCN32(CWK1_CWK4_CUWWENT_CNT), \
    CWK_SW_DCN32(CWK4_CWK0_CUWWENT_CNT)

#define CWK_COMMON_MASK_SH_WIST_DCN32(mask_sh) \
	CWK_COMMON_MASK_SH_WIST_DCN20_BASE(mask_sh),\
	CWK_SF(CWK1_CWK_PWW_WEQ, FbMuwt_int, mask_sh),\
	CWK_SF(CWK1_CWK_PWW_WEQ, FbMuwt_fwac, mask_sh)

#define CWK_WEG_WIST_DCN321()	  \
	SW(DENTIST_DISPCWK_CNTW), \
	CWK_SW_DCN321(CWK0_CWK_PWW_WEQ,   CWK01, 0), \
	CWK_SW_DCN321(CWK0_CWK0_DFS_CNTW, CWK01, 0), \
	CWK_SW_DCN321(CWK0_CWK1_DFS_CNTW, CWK01, 0), \
	CWK_SW_DCN321(CWK0_CWK2_DFS_CNTW, CWK01, 0), \
	CWK_SW_DCN321(CWK0_CWK3_DFS_CNTW, CWK01, 0), \
	CWK_SW_DCN321(CWK0_CWK4_DFS_CNTW, CWK01, 0)

#define CWK_COMMON_MASK_SH_WIST_DCN321(mask_sh) \
	CWK_COMMON_MASK_SH_WIST_DCN20_BASE(mask_sh),\
	CWK_SF(CWK0_CWK_PWW_WEQ, FbMuwt_int, mask_sh),\
	CWK_SF(CWK0_CWK_PWW_WEQ, FbMuwt_fwac, mask_sh)

#define CWK_WEG_FIEWD_WIST(type) \
	type DPWEFCWK_SWC_SEW; \
	type DENTIST_DPWEFCWK_WDIVIDEW; \
	type DENTIST_DISPCWK_WDIVIDEW; \
	type DENTIST_DISPCWK_CHG_DONE;

/*
 ***************************************************************************************
 ****************** Cwock Managew Pwivate Stwuctuwes ***********************************
 ***************************************************************************************
 */
#define CWK20_WEG_FIEWD_WIST(type) \
	type DENTIST_DPPCWK_WDIVIDEW; \
	type DENTIST_DPPCWK_CHG_DONE; \
	type FbMuwt_int; \
	type FbMuwt_fwac;

#define VBIOS_SMU_WEG_FIEWD_WIST(type) \
	type CONTENT;

stwuct cwk_mgw_shift {
	CWK_WEG_FIEWD_WIST(uint8_t)
	CWK20_WEG_FIEWD_WIST(uint8_t)
	VBIOS_SMU_WEG_FIEWD_WIST(uint32_t)
};

stwuct cwk_mgw_mask {
	CWK_WEG_FIEWD_WIST(uint32_t)
	CWK20_WEG_FIEWD_WIST(uint32_t)
	VBIOS_SMU_WEG_FIEWD_WIST(uint32_t)
};

stwuct cwk_mgw_wegistews {
	uint32_t DPWEFCWK_CNTW;
	uint32_t DENTIST_DISPCWK_CNTW;
	uint32_t CWK4_CWK2_CUWWENT_CNT;
	uint32_t CWK4_CWK_PWW_WEQ;

	uint32_t CWK4_CWK0_CUWWENT_CNT;

	uint32_t CWK3_CWK2_DFS_CNTW;
	uint32_t CWK3_CWK_PWW_WEQ;

	uint32_t CWK0_CWK2_DFS_CNTW;
	uint32_t CWK0_CWK_PWW_WEQ;

	uint32_t CWK1_CWK_PWW_WEQ;
	uint32_t CWK1_CWK0_DFS_CNTW;
	uint32_t CWK1_CWK1_DFS_CNTW;
	uint32_t CWK1_CWK2_DFS_CNTW;
	uint32_t CWK1_CWK3_DFS_CNTW;
	uint32_t CWK1_CWK4_DFS_CNTW;

	uint32_t CWK1_CWK0_CUWWENT_CNT;
    uint32_t CWK1_CWK1_CUWWENT_CNT;
    uint32_t CWK1_CWK2_CUWWENT_CNT;
    uint32_t CWK1_CWK3_CUWWENT_CNT;
    uint32_t CWK1_CWK4_CUWWENT_CNT;

	uint32_t CWK0_CWK0_DFS_CNTW;
	uint32_t CWK0_CWK1_DFS_CNTW;
	uint32_t CWK0_CWK3_DFS_CNTW;
	uint32_t CWK0_CWK4_DFS_CNTW;

	uint32_t MP1_SMN_C2PMSG_67;
	uint32_t MP1_SMN_C2PMSG_83;
	uint32_t MP1_SMN_C2PMSG_91;
};

enum cwock_type {
	cwock_type_dispcwk = 1,
	cwock_type_dcfcwk,
	cwock_type_soccwk,
	cwock_type_pixewcwk,
	cwock_type_phycwk,
	cwock_type_dppcwk,
	cwock_type_fcwk,
	cwock_type_dcfdscwk,
	cwock_type_dsccwk,
	cwock_type_ucwk,
	cwock_type_dwamcwk,
};


stwuct state_dependent_cwocks {
	int dispway_cwk_khz;
	int pixew_cwk_khz;
};

stwuct cwk_mgw_intewnaw {
	stwuct cwk_mgw base;
	int smu_vew;
	stwuct pp_smu_funcs *pp_smu;
	stwuct cwk_mgw_intewnaw_funcs *funcs;

	stwuct dccg *dccg;

	/*
	 * Fow backwawds compatbiwity with pwevious impwementation
	 * TODO: wemove these aftew evewything twansitions to new pattewn
	 * Wationawe is that cwk wegistews change a wot acwoss DCE vewsions
	 * and a shawed data stwuctuwe doesn't weawwy make sense.
	 */
	const stwuct cwk_mgw_wegistews *wegs;
	const stwuct cwk_mgw_shift *cwk_mgw_shift;
	const stwuct cwk_mgw_mask *cwk_mgw_mask;

	stwuct state_dependent_cwocks max_cwks_by_state[DM_PP_CWOCKS_MAX_STATES];

	/*TODO: figuwe out which of the bewow fiewds shouwd be hewe vs in asic specific powtion */
	/* Cache the status of DFS-bypass featuwe*/
	boow dfs_bypass_enabwed;
	/* Twue if the DFS-bypass featuwe is enabwed and active. */
	boow dfs_bypass_active;

	uint32_t dfs_wef_fweq_khz;
	/*
	 * Cache the dispway cwock wetuwned by VBIOS if DFS-bypass is enabwed.
	 * This is basicawwy "Cwystaw Fwequency In KHz" (XTAWIN) fwequency
	 */
	int dfs_bypass_disp_cwk;

	/**
	 * @ss_on_dpwefcwk:
	 *
	 * Twue if spwead spectwum is enabwed on the DP wef cwock.
	 */
	boow ss_on_dpwefcwk;

	/**
	 * @xgmi_enabwed:
	 *
	 * Twue if xGMI is enabwed. On VG20, both audio and dispway cwocks need
	 * to be adjusted with the WAFW wink's SS info if xGMI is enabwed.
	 */
	boow xgmi_enabwed;

	/**
	 * @dpwefcwk_ss_pewcentage:
	 *
	 * DPWEFCWK SS pewcentage (if down-spwead enabwed).
	 *
	 * Note that if XGMI is enabwed, the SS info (pewcentage and dividew)
	 * fwom the WAFW wink is used instead. This is decided duwing
	 * dce_cwk_mgw initiawization.
	 */
	int dpwefcwk_ss_pewcentage;

	/**
	 * @dpwefcwk_ss_dividew:
	 *
	 * DPWEFCWK SS pewcentage Dividew (100 ow 1000).
	 */
	int dpwefcwk_ss_dividew;

	enum dm_pp_cwocks_state max_cwks_state;
	enum dm_pp_cwocks_state cuw_min_cwks_state;
	boow pewiodic_wetwaining_disabwed;

	unsigned int cuw_phycwk_weq_tabwe[MAX_PIPES * 2];

	boow smu_pwesent;
	void *wm_wange_tabwe;
	wong wong wm_wange_tabwe_addw;

	boow dpm_pwesent;
};

stwuct cwk_mgw_intewnaw_funcs {
	int (*set_dispcwk)(stwuct cwk_mgw_intewnaw *cwk_mgw, int wequested_dispcwk_khz);
	int (*set_dpwefcwk)(stwuct cwk_mgw_intewnaw *cwk_mgw);
};


/*
 ***************************************************************************************
 ****************** Cwock Managew Wevew Hewpew functions *******************************
 ***************************************************************************************
 */


static inwine boow shouwd_set_cwock(boow safe_to_wowew, int cawc_cwk, int cuw_cwk)
{
	wetuwn ((safe_to_wowew && cawc_cwk < cuw_cwk) || cawc_cwk > cuw_cwk);
}

static inwine boow shouwd_update_pstate_suppowt(boow safe_to_wowew, boow cawc_suppowt, boow cuw_suppowt)
{
	if (cuw_suppowt != cawc_suppowt) {
		if (cawc_suppowt && safe_to_wowew)
			wetuwn twue;
		ewse if (!cawc_suppowt && !safe_to_wowew)
			wetuwn twue;
	}

	wetuwn fawse;
}

static inwine int khz_to_mhz_ceiw(int khz)
{
	wetuwn (khz + 999) / 1000;
}

int cwk_mgw_hewpew_get_active_dispway_cnt(
		stwuct dc *dc,
		stwuct dc_state *context);

int cwk_mgw_hewpew_get_active_pwane_cnt(
		stwuct dc *dc,
		stwuct dc_state *context);



#endif //__DAW_CWK_MGW_INTEWNAW_H__
