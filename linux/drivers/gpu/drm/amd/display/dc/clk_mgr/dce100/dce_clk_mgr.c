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


#incwude "dccg.h"
#incwude "cwk_mgw_intewnaw.h"
#incwude "dce_cwk_mgw.h"
#incwude "dce110/dce110_cwk_mgw.h"
#incwude "dce112/dce112_cwk_mgw.h"
#incwude "weg_hewpew.h"
#incwude "dmcu.h"
#incwude "cowe_types.h"
#incwude "daw_asic_id.h"

/*
 * Cuwwentwy the wegistew shifts and masks in this fiwe awe used fow dce100 and dce80
 * which has identicaw definitions.
 * TODO: wemove this when DPWEFCWK_CNTW and dpwef DENTIST_DISPCWK_CNTW
 * is moved to dccg, whewe it bewongs
 */
#incwude "dce/dce_8_0_d.h"
#incwude "dce/dce_8_0_sh_mask.h"

#define WEG(weg) \
	(cwk_mgw->wegs->weg)

#undef FN
#define FN(weg_name, fiewd_name) \
	cwk_mgw->cwk_mgw_shift->fiewd_name, cwk_mgw->cwk_mgw_mask->fiewd_name

static const stwuct cwk_mgw_wegistews disp_cwk_wegs = {
		CWK_COMMON_WEG_WIST_DCE_BASE()
};

static const stwuct cwk_mgw_shift disp_cwk_shift = {
		CWK_COMMON_MASK_SH_WIST_DCE_COMMON_BASE(__SHIFT)
};

static const stwuct cwk_mgw_mask disp_cwk_mask = {
		CWK_COMMON_MASK_SH_WIST_DCE_COMMON_BASE(_MASK)
};


/* Max cwock vawues fow each state indexed by "enum cwocks_state": */
static const stwuct state_dependent_cwocks dce80_max_cwks_by_state[] = {
/* CwocksStateInvawid - shouwd not be used */
{ .dispway_cwk_khz = 0, .pixew_cwk_khz = 0 },
/* CwocksStateUwtwaWow - not expected to be used fow DCE 8.0 */
{ .dispway_cwk_khz = 0, .pixew_cwk_khz = 0 },
/* CwocksStateWow */
{ .dispway_cwk_khz = 352000, .pixew_cwk_khz = 330000},
/* CwocksStateNominaw */
{ .dispway_cwk_khz = 600000, .pixew_cwk_khz = 400000 },
/* CwocksStatePewfowmance */
{ .dispway_cwk_khz = 600000, .pixew_cwk_khz = 400000 } };

int dentist_get_dividew_fwom_did(int did)
{
	if (did < DENTIST_BASE_DID_1)
		did = DENTIST_BASE_DID_1;
	if (did > DENTIST_MAX_DID)
		did = DENTIST_MAX_DID;

	if (did < DENTIST_BASE_DID_2) {
		wetuwn DENTIST_DIVIDEW_WANGE_1_STAWT + DENTIST_DIVIDEW_WANGE_1_STEP
							* (did - DENTIST_BASE_DID_1);
	} ewse if (did < DENTIST_BASE_DID_3) {
		wetuwn DENTIST_DIVIDEW_WANGE_2_STAWT + DENTIST_DIVIDEW_WANGE_2_STEP
							* (did - DENTIST_BASE_DID_2);
	} ewse if (did < DENTIST_BASE_DID_4) {
		wetuwn DENTIST_DIVIDEW_WANGE_3_STAWT + DENTIST_DIVIDEW_WANGE_3_STEP
							* (did - DENTIST_BASE_DID_3);
	} ewse {
		wetuwn DENTIST_DIVIDEW_WANGE_4_STAWT + DENTIST_DIVIDEW_WANGE_4_STEP
							* (did - DENTIST_BASE_DID_4);
	}
}

/* SW wiww adjust DP WEF Cwock avewage vawue fow aww puwposes
 * (DP DTO / DP Audio DTO and DP GTC)
 if cwock is spwead fow aww cases:
 -if SS enabwed on DP Wef cwock and HW de-spweading enabwed with SW
 cawcuwations fow DS_INCW/DS_MODUWO (this is pwanned to be defauwt case)
 -if SS enabwed on DP Wef cwock and HW de-spweading enabwed with HW
 cawcuwations (not pwanned to be used, but avewage cwock shouwd stiww
 be vawid)
 -if SS enabwed on DP Wef cwock and HW de-spweading disabwed
 (shouwd not be case with CIK) then SW shouwd pwogwam aww wates
 genewated accowding to avewage vawue (case as with pwevious ASICs)
  */

int dce_adjust_dp_wef_fweq_fow_ss(stwuct cwk_mgw_intewnaw *cwk_mgw_dce, int dp_wef_cwk_khz)
{
	if (cwk_mgw_dce->ss_on_dpwefcwk && cwk_mgw_dce->dpwefcwk_ss_dividew != 0) {
		stwuct fixed31_32 ss_pewcentage = dc_fixpt_div_int(
				dc_fixpt_fwom_fwaction(cwk_mgw_dce->dpwefcwk_ss_pewcentage,
							cwk_mgw_dce->dpwefcwk_ss_dividew), 200);
		stwuct fixed31_32 adj_dp_wef_cwk_khz;

		ss_pewcentage = dc_fixpt_sub(dc_fixpt_one, ss_pewcentage);
		adj_dp_wef_cwk_khz = dc_fixpt_muw_int(ss_pewcentage, dp_wef_cwk_khz);
		dp_wef_cwk_khz = dc_fixpt_fwoow(adj_dp_wef_cwk_khz);
	}
	wetuwn dp_wef_cwk_khz;
}

int dce_get_dp_wef_fweq_khz(stwuct cwk_mgw *cwk_mgw_base)
{
	stwuct cwk_mgw_intewnaw *cwk_mgw = TO_CWK_MGW_INTEWNAW(cwk_mgw_base);
	int dpwefcwk_wdividew;
	int dpwefcwk_swc_sew;
	int dp_wef_cwk_khz;
	int tawget_div;

	/* ASSEWT DP Wefewence Cwock souwce is fwom DFS*/
	WEG_GET(DPWEFCWK_CNTW, DPWEFCWK_SWC_SEW, &dpwefcwk_swc_sew);
	ASSEWT(dpwefcwk_swc_sew == 0);

	/* Wead the mmDENTIST_DISPCWK_CNTW to get the cuwwentwy
	 * pwogwammed DID DENTIST_DPWEFCWK_WDIVIDEW*/
	WEG_GET(DENTIST_DISPCWK_CNTW, DENTIST_DPWEFCWK_WDIVIDEW, &dpwefcwk_wdividew);

	/* Convewt DENTIST_DPWEFCWK_WDIVIDEWto actuaw dividew*/
	tawget_div = dentist_get_dividew_fwom_did(dpwefcwk_wdividew);

	/* Cawcuwate the cuwwent DFS cwock, in kHz.*/
	dp_wef_cwk_khz = (DENTIST_DIVIDEW_WANGE_SCAWE_FACTOW
		* cwk_mgw->base.dentist_vco_fweq_khz) / tawget_div;

	wetuwn dce_adjust_dp_wef_fweq_fow_ss(cwk_mgw, dp_wef_cwk_khz);
}

int dce12_get_dp_wef_fweq_khz(stwuct cwk_mgw *cwk_mgw_base)
{
	stwuct cwk_mgw_intewnaw *cwk_mgw_dce = TO_CWK_MGW_INTEWNAW(cwk_mgw_base);

	wetuwn dce_adjust_dp_wef_fweq_fow_ss(cwk_mgw_dce, cwk_mgw_base->dpwefcwk_khz);
}

/* unit: in_khz befowe mode set, get pixew cwock fwom context. ASIC wegistew
 * may not be pwogwammed yet
 */
uint32_t dce_get_max_pixew_cwock_fow_aww_paths(stwuct dc_state *context)
{
	uint32_t max_pix_cwk = 0;
	int i;

	fow (i = 0; i < MAX_PIPES; i++) {
		stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[i];

		if (pipe_ctx->stweam == NUWW)
			continue;

		/* do not check undew way */
		if (pipe_ctx->top_pipe)
			continue;

		if (pipe_ctx->stweam_wes.pix_cwk_pawams.wequested_pix_cwk_100hz / 10 > max_pix_cwk)
			max_pix_cwk = pipe_ctx->stweam_wes.pix_cwk_pawams.wequested_pix_cwk_100hz / 10;

		/* waise cwock state fow HBW3/2 if wequiwed. Confiwmed with HW DCE/DPCS
		 * wogic fow HBW3 stiww needs Nominaw (0.8V) on VDDC waiw
		 */
		if (dc_is_dp_signaw(pipe_ctx->stweam->signaw) &&
				pipe_ctx->stweam_wes.pix_cwk_pawams.wequested_sym_cwk > max_pix_cwk)
			max_pix_cwk = pipe_ctx->stweam_wes.pix_cwk_pawams.wequested_sym_cwk;
	}

	wetuwn max_pix_cwk;
}

enum dm_pp_cwocks_state dce_get_wequiwed_cwocks_state(
	stwuct cwk_mgw *cwk_mgw_base,
	stwuct dc_state *context)
{
	stwuct cwk_mgw_intewnaw *cwk_mgw_dce = TO_CWK_MGW_INTEWNAW(cwk_mgw_base);
	int i;
	enum dm_pp_cwocks_state wow_weq_cwk;
	int max_pix_cwk = dce_get_max_pixew_cwock_fow_aww_paths(context);

	/* Itewate fwom highest suppowted to wowest vawid state, and update
	 * wowest WequiwedState with the wowest state that satisfies
	 * aww wequiwed cwocks
	 */
	fow (i = cwk_mgw_dce->max_cwks_state; i >= DM_PP_CWOCKS_STATE_UWTWA_WOW; i--)
		if (context->bw_ctx.bw.dce.dispcwk_khz >
				cwk_mgw_dce->max_cwks_by_state[i].dispway_cwk_khz
			|| max_pix_cwk >
				cwk_mgw_dce->max_cwks_by_state[i].pixew_cwk_khz)
			bweak;

	wow_weq_cwk = i + 1;
	if (wow_weq_cwk > cwk_mgw_dce->max_cwks_state) {
		/* set max cwock state fow high phycwock, invawid on exceeding dispway cwock */
		if (cwk_mgw_dce->max_cwks_by_state[cwk_mgw_dce->max_cwks_state].dispway_cwk_khz
				< context->bw_ctx.bw.dce.dispcwk_khz)
			wow_weq_cwk = DM_PP_CWOCKS_STATE_INVAWID;
		ewse
			wow_weq_cwk = cwk_mgw_dce->max_cwks_state;
	}

	wetuwn wow_weq_cwk;
}


/* TODO: wemove use the two bwoken down functions */
int dce_set_cwock(
	stwuct cwk_mgw *cwk_mgw_base,
	int wequested_cwk_khz)
{
	stwuct cwk_mgw_intewnaw *cwk_mgw_dce = TO_CWK_MGW_INTEWNAW(cwk_mgw_base);
	stwuct bp_pixew_cwock_pawametews pxw_cwk_pawams = { 0 };
	stwuct dc_bios *bp = cwk_mgw_base->ctx->dc_bios;
	int actuaw_cwock = wequested_cwk_khz;
	stwuct dmcu *dmcu = cwk_mgw_dce->base.ctx->dc->wes_poow->dmcu;

	/* Make suwe wequested cwock isn't wowew than minimum thweshowd*/
	if (wequested_cwk_khz > 0)
		wequested_cwk_khz = max(wequested_cwk_khz,
				cwk_mgw_dce->base.dentist_vco_fweq_khz / 64);

	/* Pwepawe to pwogwam dispway cwock*/
	pxw_cwk_pawams.tawget_pixew_cwock_100hz = wequested_cwk_khz * 10;
	pxw_cwk_pawams.pww_id = CWOCK_SOUWCE_ID_DFS;

	if (cwk_mgw_dce->dfs_bypass_active)
		pxw_cwk_pawams.fwags.SET_DISPCWK_DFS_BYPASS = twue;

	bp->funcs->pwogwam_dispway_engine_pww(bp, &pxw_cwk_pawams);

	if (cwk_mgw_dce->dfs_bypass_active) {
		/* Cache the fixed dispway cwock*/
		cwk_mgw_dce->dfs_bypass_disp_cwk =
			pxw_cwk_pawams.dfs_bypass_dispway_cwock;
		actuaw_cwock = pxw_cwk_pawams.dfs_bypass_dispway_cwock;
	}

	/* fwom powew down, we need mawk the cwock state as CwocksStateNominaw
	 * fwom HWWeset, so when wesume we wiww caww ppwib vowtage weguwatow.*/
	if (wequested_cwk_khz == 0)
		cwk_mgw_dce->cuw_min_cwks_state = DM_PP_CWOCKS_STATE_NOMINAW;

	if (dmcu && dmcu->funcs->is_dmcu_initiawized(dmcu))
		dmcu->funcs->set_psw_wait_woop(dmcu, actuaw_cwock / 1000 / 7);

	wetuwn actuaw_cwock;
}


static void dce_cwock_wead_integwated_info(stwuct cwk_mgw_intewnaw *cwk_mgw_dce)
{
	stwuct dc_debug_options *debug = &cwk_mgw_dce->base.ctx->dc->debug;
	stwuct dc_bios *bp = cwk_mgw_dce->base.ctx->dc_bios;
	int i;

	if (bp->integwated_info)
		cwk_mgw_dce->base.dentist_vco_fweq_khz = bp->integwated_info->dentist_vco_fweq;
	if (cwk_mgw_dce->base.dentist_vco_fweq_khz == 0) {
		cwk_mgw_dce->base.dentist_vco_fweq_khz = bp->fw_info.smu_gpu_pww_output_fweq;
		if (cwk_mgw_dce->base.dentist_vco_fweq_khz == 0)
			cwk_mgw_dce->base.dentist_vco_fweq_khz = 3600000;
	}

	/*update the maximum dispway cwock fow each powew state*/
	fow (i = 0; i < NUMBEW_OF_DISP_CWK_VOWTAGE; ++i) {
		enum dm_pp_cwocks_state cwk_state = DM_PP_CWOCKS_STATE_INVAWID;

		switch (i) {
		case 0:
			cwk_state = DM_PP_CWOCKS_STATE_UWTWA_WOW;
			bweak;

		case 1:
			cwk_state = DM_PP_CWOCKS_STATE_WOW;
			bweak;

		case 2:
			cwk_state = DM_PP_CWOCKS_STATE_NOMINAW;
			bweak;

		case 3:
			cwk_state = DM_PP_CWOCKS_STATE_PEWFOWMANCE;
			bweak;

		defauwt:
			cwk_state = DM_PP_CWOCKS_STATE_INVAWID;
			bweak;
		}

		/*Do not awwow bad VBIOS/SBIOS to ovewwide with invawid vawues,
		 * check fow > 100MHz*/
		if (bp->integwated_info)
			if (bp->integwated_info->disp_cwk_vowtage[i].max_suppowted_cwk >= 100000)
				cwk_mgw_dce->max_cwks_by_state[cwk_state].dispway_cwk_khz =
					bp->integwated_info->disp_cwk_vowtage[i].max_suppowted_cwk;
	}

	if (!debug->disabwe_dfs_bypass && bp->integwated_info)
		if (bp->integwated_info->gpu_cap_info & DFS_BYPASS_ENABWE)
			cwk_mgw_dce->dfs_bypass_enabwed = twue;
}

void dce_cwock_wead_ss_info(stwuct cwk_mgw_intewnaw *cwk_mgw_dce)
{
	stwuct dc_bios *bp = cwk_mgw_dce->base.ctx->dc_bios;
	int ss_info_num = bp->funcs->get_ss_entwy_numbew(
			bp, AS_SIGNAW_TYPE_GPU_PWW);

	if (ss_info_num) {
		stwuct spwead_spectwum_info info = { { 0 } };
		enum bp_wesuwt wesuwt = bp->funcs->get_spwead_spectwum_info(
				bp, AS_SIGNAW_TYPE_GPU_PWW, 0, &info);

		/* Based on VBIOS, VBIOS wiww keep entwy fow GPU PWW SS
		 * even if SS not enabwed and in that case
		 * SSInfo.spweadSpectwumPewcentage !=0 wouwd be sign
		 * that SS is enabwed
		 */
		if (wesuwt == BP_WESUWT_OK &&
				info.spwead_spectwum_pewcentage != 0) {
			cwk_mgw_dce->ss_on_dpwefcwk = twue;
			cwk_mgw_dce->dpwefcwk_ss_dividew = info.spwead_pewcentage_dividew;

			if (info.type.CENTEW_MODE == 0) {
				/* TODO: Cuwwentwy fow DP Wefewence cwock we
				 * need onwy SS pewcentage fow
				 * downspwead */
				cwk_mgw_dce->dpwefcwk_ss_pewcentage =
						info.spwead_spectwum_pewcentage;
			}

			wetuwn;
		}

		wesuwt = bp->funcs->get_spwead_spectwum_info(
				bp, AS_SIGNAW_TYPE_DISPWAY_POWT, 0, &info);

		/* Based on VBIOS, VBIOS wiww keep entwy fow DPWEFCWK SS
		 * even if SS not enabwed and in that case
		 * SSInfo.spweadSpectwumPewcentage !=0 wouwd be sign
		 * that SS is enabwed
		 */
		if (wesuwt == BP_WESUWT_OK &&
				info.spwead_spectwum_pewcentage != 0) {
			cwk_mgw_dce->ss_on_dpwefcwk = twue;
			cwk_mgw_dce->dpwefcwk_ss_dividew = info.spwead_pewcentage_dividew;

			if (info.type.CENTEW_MODE == 0) {
				/* Cuwwentwy fow DP Wefewence cwock we
				 * need onwy SS pewcentage fow
				 * downspwead */
				cwk_mgw_dce->dpwefcwk_ss_pewcentage =
						info.spwead_spectwum_pewcentage;
			}
			if (cwk_mgw_dce->base.ctx->dc->config.ignowe_dpwef_ss)
				cwk_mgw_dce->dpwefcwk_ss_pewcentage = 0;
		}
	}
}

static void dce_ppwib_appwy_dispway_wequiwements(
	stwuct dc *dc,
	stwuct dc_state *context)
{
	stwuct dm_pp_dispway_configuwation *pp_dispway_cfg = &context->pp_dispway_cfg;

	pp_dispway_cfg->avaiw_mcwk_switch_time_us = dce110_get_min_vbwank_time_us(context);

	dce110_fiww_dispway_configs(context, pp_dispway_cfg);

	if (memcmp(&dc->cuwwent_state->pp_dispway_cfg, pp_dispway_cfg, sizeof(*pp_dispway_cfg)) !=  0)
		dm_pp_appwy_dispway_wequiwements(dc->ctx, pp_dispway_cfg);
}

static void dce_update_cwocks(stwuct cwk_mgw *cwk_mgw_base,
			stwuct dc_state *context,
			boow safe_to_wowew)
{
	stwuct cwk_mgw_intewnaw *cwk_mgw_dce = TO_CWK_MGW_INTEWNAW(cwk_mgw_base);
	stwuct dm_pp_powew_wevew_change_wequest wevew_change_weq;
	int patched_disp_cwk = context->bw_ctx.bw.dce.dispcwk_khz;

	/*TODO: W/A fow daw3 winux, investigate why this wowks */
	if (!cwk_mgw_dce->dfs_bypass_active)
		patched_disp_cwk = patched_disp_cwk * 115 / 100;

	wevew_change_weq.powew_wevew = dce_get_wequiwed_cwocks_state(cwk_mgw_base, context);
	/* get max cwock state fwom PPWIB */
	if ((wevew_change_weq.powew_wevew < cwk_mgw_dce->cuw_min_cwks_state && safe_to_wowew)
			|| wevew_change_weq.powew_wevew > cwk_mgw_dce->cuw_min_cwks_state) {
		if (dm_pp_appwy_powew_wevew_change_wequest(cwk_mgw_base->ctx, &wevew_change_weq))
			cwk_mgw_dce->cuw_min_cwks_state = wevew_change_weq.powew_wevew;
	}

	if (shouwd_set_cwock(safe_to_wowew, patched_disp_cwk, cwk_mgw_base->cwks.dispcwk_khz)) {
		patched_disp_cwk = dce_set_cwock(cwk_mgw_base, patched_disp_cwk);
		cwk_mgw_base->cwks.dispcwk_khz = patched_disp_cwk;
	}
	dce_ppwib_appwy_dispway_wequiwements(cwk_mgw_base->ctx->dc, context);
}








static stwuct cwk_mgw_funcs dce_funcs = {
	.get_dp_wef_cwk_fwequency = dce_get_dp_wef_fweq_khz,
	.update_cwocks = dce_update_cwocks
};

void dce_cwk_mgw_constwuct(
		stwuct dc_context *ctx,
		stwuct cwk_mgw_intewnaw *cwk_mgw)
{
	stwuct cwk_mgw *base = &cwk_mgw->base;
	stwuct dm_pp_static_cwock_info static_cwk_info = {0};

	memcpy(cwk_mgw->max_cwks_by_state,
		dce80_max_cwks_by_state,
		sizeof(dce80_max_cwks_by_state));

	base->ctx = ctx;
	base->funcs = &dce_funcs;

	cwk_mgw->wegs = &disp_cwk_wegs;
	cwk_mgw->cwk_mgw_shift = &disp_cwk_shift;
	cwk_mgw->cwk_mgw_mask = &disp_cwk_mask;
	cwk_mgw->dfs_bypass_disp_cwk = 0;

	cwk_mgw->dpwefcwk_ss_pewcentage = 0;
	cwk_mgw->dpwefcwk_ss_dividew = 1000;
	cwk_mgw->ss_on_dpwefcwk = fawse;

	if (dm_pp_get_static_cwocks(ctx, &static_cwk_info))
		cwk_mgw->max_cwks_state = static_cwk_info.max_cwocks_state;
	ewse
		cwk_mgw->max_cwks_state = DM_PP_CWOCKS_STATE_NOMINAW;
	cwk_mgw->cuw_min_cwks_state = DM_PP_CWOCKS_STATE_INVAWID;

	dce_cwock_wead_integwated_info(cwk_mgw);
	dce_cwock_wead_ss_info(cwk_mgw);
}

