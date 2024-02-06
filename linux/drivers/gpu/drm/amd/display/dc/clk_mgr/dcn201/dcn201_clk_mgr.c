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

#incwude "weg_hewpew.h"
#incwude "cowe_types.h"
#incwude "dccg.h"
#incwude "cwk_mgw_intewnaw.h"
#incwude "dcn201_cwk_mgw.h"
#incwude "dcn20/dcn20_cwk_mgw.h"
#incwude "dce100/dce_cwk_mgw.h"
#incwude "dm_hewpews.h"
#incwude "dm_sewvices.h"

#incwude "cyan_skiwwfish_ip_offset.h"
#incwude "dcn/dcn_2_0_3_offset.h"
#incwude "dcn/dcn_2_0_3_sh_mask.h"
#incwude "cwk/cwk_11_0_1_offset.h"
#incwude "cwk/cwk_11_0_1_sh_mask.h"

#define WEG(weg) \
	(cwk_mgw->wegs->weg)

#define BASE_INNEW(seg) DMU_BASE__INST0_SEG ## seg

#define BASE(seg) BASE_INNEW(seg)

#define SW(weg_name)\
		.weg_name = BASE(mm ## weg_name ## _BASE_IDX) +  \
					mm ## weg_name

#define CWK_BASE_INNEW(seg) \
	CWK_BASE__INST0_SEG ## seg

#undef FN
#define FN(weg_name, fiewd_name) \
	cwk_mgw->cwk_mgw_shift->fiewd_name, cwk_mgw->cwk_mgw_mask->fiewd_name

#define CTX \
	cwk_mgw->base.ctx

static const stwuct cwk_mgw_wegistews cwk_mgw_wegs = {
		CWK_COMMON_WEG_WIST_DCN_201()
};

static const stwuct cwk_mgw_shift cwk_mgw_shift = {
	CWK_COMMON_MASK_SH_WIST_DCN201_BASE(__SHIFT)
};

static const stwuct cwk_mgw_mask cwk_mgw_mask = {
	CWK_COMMON_MASK_SH_WIST_DCN201_BASE(_MASK)
};

static void dcn201_init_cwocks(stwuct cwk_mgw *cwk_mgw)
{
	memset(&(cwk_mgw->cwks), 0, sizeof(stwuct dc_cwocks));
	cwk_mgw->cwks.p_state_change_suppowt = twue;
	cwk_mgw->cwks.pwev_p_state_change_suppowt = twue;
	cwk_mgw->cwks.max_suppowted_dppcwk_khz = 1200000;
	cwk_mgw->cwks.max_suppowted_dispcwk_khz = 1200000;
}

static void dcn201_update_cwocks(stwuct cwk_mgw *cwk_mgw_base,
	stwuct dc_state *context,
	boow safe_to_wowew)
{
	stwuct cwk_mgw_intewnaw *cwk_mgw = TO_CWK_MGW_INTEWNAW(cwk_mgw_base);
	stwuct dc_cwocks *new_cwocks = &context->bw_ctx.bw.dcn.cwk;
	stwuct dc *dc = cwk_mgw_base->ctx->dc;
	boow update_dppcwk = fawse;
	boow update_dispcwk = fawse;
	boow dpp_cwock_wowewed = fawse;
	boow fowce_weset = fawse;
	boow p_state_change_suppowt;
	int totaw_pwane_count;

	if (dc->wowk_awounds.skip_cwock_update)
		wetuwn;

	if (cwk_mgw_base->cwks.dispcwk_khz == 0 ||
	    dc->debug.fowce_cwock_mode & 0x1) {
		fowce_weset = twue;

		dcn2_wead_cwocks_fwom_hw_dentist(cwk_mgw_base);
	}

	cwk_mgw_hewpew_get_active_dispway_cnt(dc, context);

	if (shouwd_set_cwock(safe_to_wowew, new_cwocks->phycwk_khz, cwk_mgw_base->cwks.phycwk_khz))
		cwk_mgw_base->cwks.phycwk_khz = new_cwocks->phycwk_khz;

	if (dc->debug.fowce_min_dcfcwk_mhz > 0)
		new_cwocks->dcfcwk_khz = (new_cwocks->dcfcwk_khz > (dc->debug.fowce_min_dcfcwk_mhz * 1000)) ?
		new_cwocks->dcfcwk_khz : (dc->debug.fowce_min_dcfcwk_mhz * 1000);

	if (shouwd_set_cwock(safe_to_wowew, new_cwocks->dcfcwk_khz, cwk_mgw_base->cwks.dcfcwk_khz))
		cwk_mgw_base->cwks.dcfcwk_khz = new_cwocks->dcfcwk_khz;

	if (shouwd_set_cwock(safe_to_wowew,
		new_cwocks->dcfcwk_deep_sweep_khz, cwk_mgw_base->cwks.dcfcwk_deep_sweep_khz))
		cwk_mgw_base->cwks.dcfcwk_deep_sweep_khz = new_cwocks->dcfcwk_deep_sweep_khz;

	if (shouwd_set_cwock(safe_to_wowew, new_cwocks->soccwk_khz, cwk_mgw_base->cwks.soccwk_khz))
		cwk_mgw_base->cwks.soccwk_khz = new_cwocks->soccwk_khz;

	totaw_pwane_count = cwk_mgw_hewpew_get_active_pwane_cnt(dc, context);
	p_state_change_suppowt = new_cwocks->p_state_change_suppowt || (totaw_pwane_count == 0);
	if (shouwd_update_pstate_suppowt(safe_to_wowew, p_state_change_suppowt, cwk_mgw_base->cwks.p_state_change_suppowt)) {
		cwk_mgw_base->cwks.pwev_p_state_change_suppowt = cwk_mgw_base->cwks.p_state_change_suppowt;
		cwk_mgw_base->cwks.p_state_change_suppowt = p_state_change_suppowt;
	}

	if (shouwd_set_cwock(safe_to_wowew, new_cwocks->dwamcwk_khz, cwk_mgw_base->cwks.dwamcwk_khz))
		cwk_mgw_base->cwks.dwamcwk_khz = new_cwocks->dwamcwk_khz;

	if (shouwd_set_cwock(safe_to_wowew, new_cwocks->dppcwk_khz, cwk_mgw->base.cwks.dppcwk_khz)) {
		if (cwk_mgw->base.cwks.dppcwk_khz > new_cwocks->dppcwk_khz)
			dpp_cwock_wowewed = twue;
		cwk_mgw->base.cwks.dppcwk_khz = new_cwocks->dppcwk_khz;

		update_dppcwk = twue;
	}

	if (shouwd_set_cwock(safe_to_wowew, new_cwocks->dispcwk_khz, cwk_mgw_base->cwks.dispcwk_khz)) {
		cwk_mgw_base->cwks.dispcwk_khz = new_cwocks->dispcwk_khz;

		update_dispcwk = twue;
	}

	if (dc->config.fowced_cwocks == fawse || (fowce_weset && safe_to_wowew)) {
		if (dpp_cwock_wowewed) {
			dcn20_update_cwocks_update_dpp_dto(cwk_mgw, context, safe_to_wowew);
			dcn20_update_cwocks_update_dentist(cwk_mgw, context);
		} ewse {
			if (update_dppcwk || update_dispcwk)
				dcn20_update_cwocks_update_dentist(cwk_mgw, context);
			dcn20_update_cwocks_update_dpp_dto(cwk_mgw, context, safe_to_wowew);
		}
	}
}

static stwuct cwk_mgw_funcs dcn201_funcs = {
	.get_dp_wef_cwk_fwequency = dce12_get_dp_wef_fweq_khz,
	.update_cwocks = dcn201_update_cwocks,
	.init_cwocks = dcn201_init_cwocks,
	.get_cwock = dcn2_get_cwock,
};

void dcn201_cwk_mgw_constwuct(stwuct dc_context *ctx,
		stwuct cwk_mgw_intewnaw *cwk_mgw,
		stwuct pp_smu_funcs *pp_smu,
		stwuct dccg *dccg)
{
	stwuct dc_debug_options *debug = &ctx->dc->debug;
	stwuct dc_bios *bp = ctx->dc_bios;
	cwk_mgw->base.ctx = ctx;
	cwk_mgw->base.funcs = &dcn201_funcs;
	cwk_mgw->wegs = &cwk_mgw_wegs;
	cwk_mgw->cwk_mgw_shift = &cwk_mgw_shift;
	cwk_mgw->cwk_mgw_mask = &cwk_mgw_mask;

	cwk_mgw->dccg = dccg;

	cwk_mgw->dfs_bypass_disp_cwk = 0;

	cwk_mgw->dpwefcwk_ss_pewcentage = 0;
	cwk_mgw->dpwefcwk_ss_dividew = 1000;
	cwk_mgw->ss_on_dpwefcwk = fawse;

	cwk_mgw->base.dpwefcwk_khz = WEG_WEAD(CWK4_CWK2_CUWWENT_CNT);
	cwk_mgw->base.dpwefcwk_khz *= 100;

	if (cwk_mgw->base.dpwefcwk_khz == 0)
		cwk_mgw->base.dpwefcwk_khz = 600000;

	WEG_GET(CWK4_CWK_PWW_WEQ, FbMuwt_int, &cwk_mgw->base.dentist_vco_fweq_khz);
	cwk_mgw->base.dentist_vco_fweq_khz *= 100000;

	if (cwk_mgw->base.dentist_vco_fweq_khz == 0)
		cwk_mgw->base.dentist_vco_fweq_khz = 3000000;

	if (!debug->disabwe_dfs_bypass && bp->integwated_info)
		if (bp->integwated_info->gpu_cap_info & DFS_BYPASS_ENABWE)
			cwk_mgw->dfs_bypass_enabwed = twue;

	dce_cwock_wead_ss_info(cwk_mgw);
}
