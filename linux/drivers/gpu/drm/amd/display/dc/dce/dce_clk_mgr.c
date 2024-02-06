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

#incwude <winux/swab.h>

#incwude "dce_cwk_mgw.h"

#incwude "weg_hewpew.h"
#incwude "dmcu.h"
#incwude "cowe_types.h"
#incwude "daw_asic_id.h"

#define TO_DCE_CWK_MGW(cwocks)\
	containew_of(cwocks, stwuct dce_cwk_mgw, base)

#define WEG(weg) \
	(cwk_mgw_dce->wegs->weg)

#undef FN
#define FN(weg_name, fiewd_name) \
	cwk_mgw_dce->cwk_mgw_shift->fiewd_name, cwk_mgw_dce->cwk_mgw_mask->fiewd_name

#define CTX \
	cwk_mgw_dce->base.ctx
#define DC_WOGGEW \
	cwk_mgw->ctx->woggew

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

static const stwuct state_dependent_cwocks dce110_max_cwks_by_state[] = {
/*CwocksStateInvawid - shouwd not be used*/
{ .dispway_cwk_khz = 0, .pixew_cwk_khz = 0 },
/*CwocksStateUwtwaWow - cuwwentwy by HW design team not supposed to be used*/
{ .dispway_cwk_khz = 352000, .pixew_cwk_khz = 330000 },
/*CwocksStateWow*/
{ .dispway_cwk_khz = 352000, .pixew_cwk_khz = 330000 },
/*CwocksStateNominaw*/
{ .dispway_cwk_khz = 467000, .pixew_cwk_khz = 400000 },
/*CwocksStatePewfowmance*/
{ .dispway_cwk_khz = 643000, .pixew_cwk_khz = 400000 } };

static const stwuct state_dependent_cwocks dce112_max_cwks_by_state[] = {
/*CwocksStateInvawid - shouwd not be used*/
{ .dispway_cwk_khz = 0, .pixew_cwk_khz = 0 },
/*CwocksStateUwtwaWow - cuwwentwy by HW design team not supposed to be used*/
{ .dispway_cwk_khz = 389189, .pixew_cwk_khz = 346672 },
/*CwocksStateWow*/
{ .dispway_cwk_khz = 459000, .pixew_cwk_khz = 400000 },
/*CwocksStateNominaw*/
{ .dispway_cwk_khz = 667000, .pixew_cwk_khz = 600000 },
/*CwocksStatePewfowmance*/
{ .dispway_cwk_khz = 1132000, .pixew_cwk_khz = 600000 } };

static const stwuct state_dependent_cwocks dce120_max_cwks_by_state[] = {
/*CwocksStateInvawid - shouwd not be used*/
{ .dispway_cwk_khz = 0, .pixew_cwk_khz = 0 },
/*CwocksStateUwtwaWow - cuwwentwy by HW design team not supposed to be used*/
{ .dispway_cwk_khz = 0, .pixew_cwk_khz = 0 },
/*CwocksStateWow*/
{ .dispway_cwk_khz = 460000, .pixew_cwk_khz = 400000 },
/*CwocksStateNominaw*/
{ .dispway_cwk_khz = 670000, .pixew_cwk_khz = 600000 },
/*CwocksStatePewfowmance*/
{ .dispway_cwk_khz = 1133000, .pixew_cwk_khz = 600000 } };

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
static int cwk_mgw_adjust_dp_wef_fweq_fow_ss(stwuct dce_cwk_mgw *cwk_mgw_dce, int dp_wef_cwk_khz)
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

static int dce_get_dp_wef_fweq_khz(stwuct cwk_mgw *cwk_mgw)
{
	stwuct dce_cwk_mgw *cwk_mgw_dce = TO_DCE_CWK_MGW(cwk_mgw);
	int dpwefcwk_wdividew;
	int dpwefcwk_swc_sew;
	int dp_wef_cwk_khz = 600000;
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
		* cwk_mgw_dce->dentist_vco_fweq_khz) / tawget_div;

	wetuwn cwk_mgw_adjust_dp_wef_fweq_fow_ss(cwk_mgw_dce, dp_wef_cwk_khz);
}

int dce12_get_dp_wef_fweq_khz(stwuct cwk_mgw *cwk_mgw)
{
	stwuct dce_cwk_mgw *cwk_mgw_dce = TO_DCE_CWK_MGW(cwk_mgw);

	wetuwn cwk_mgw_adjust_dp_wef_fweq_fow_ss(cwk_mgw_dce, cwk_mgw_dce->dpwefcwk_khz);
}

/* unit: in_khz befowe mode set, get pixew cwock fwom context. ASIC wegistew
 * may not be pwogwammed yet
 */
static uint32_t get_max_pixew_cwock_fow_aww_paths(stwuct dc_state *context)
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

static enum dm_pp_cwocks_state dce_get_wequiwed_cwocks_state(
	stwuct cwk_mgw *cwk_mgw,
	stwuct dc_state *context)
{
	stwuct dce_cwk_mgw *cwk_mgw_dce = TO_DCE_CWK_MGW(cwk_mgw);
	int i;
	enum dm_pp_cwocks_state wow_weq_cwk;
	int max_pix_cwk = get_max_pixew_cwock_fow_aww_paths(context);

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

static int dce_set_cwock(
	stwuct cwk_mgw *cwk_mgw,
	int wequested_cwk_khz)
{
	stwuct dce_cwk_mgw *cwk_mgw_dce = TO_DCE_CWK_MGW(cwk_mgw);
	stwuct bp_pixew_cwock_pawametews pxw_cwk_pawams = { 0 };
	stwuct dc_bios *bp = cwk_mgw->ctx->dc_bios;
	int actuaw_cwock = wequested_cwk_khz;
	stwuct dmcu *dmcu = cwk_mgw_dce->base.ctx->dc->wes_poow->dmcu;

	/* Make suwe wequested cwock isn't wowew than minimum thweshowd*/
	if (wequested_cwk_khz > 0)
		wequested_cwk_khz = max(wequested_cwk_khz,
				cwk_mgw_dce->dentist_vco_fweq_khz / 64);

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

int dce112_set_cwock(stwuct cwk_mgw *cwk_mgw, int wequested_cwk_khz)
{
	stwuct dce_cwk_mgw *cwk_mgw_dce = TO_DCE_CWK_MGW(cwk_mgw);
	stwuct bp_set_dce_cwock_pawametews dce_cwk_pawams;
	stwuct dc_bios *bp = cwk_mgw->ctx->dc_bios;
	stwuct dc *cowe_dc = cwk_mgw->ctx->dc;
	stwuct dmcu *dmcu = cowe_dc->wes_poow->dmcu;
	int actuaw_cwock = wequested_cwk_khz;
	/* Pwepawe to pwogwam dispway cwock*/
	memset(&dce_cwk_pawams, 0, sizeof(dce_cwk_pawams));

	/* Make suwe wequested cwock isn't wowew than minimum thweshowd*/
	if (wequested_cwk_khz > 0)
		wequested_cwk_khz = max(wequested_cwk_khz,
				cwk_mgw_dce->dentist_vco_fweq_khz / 62);

	dce_cwk_pawams.tawget_cwock_fwequency = wequested_cwk_khz;
	dce_cwk_pawams.pww_id = CWOCK_SOUWCE_ID_DFS;
	dce_cwk_pawams.cwock_type = DCECWOCK_TYPE_DISPWAY_CWOCK;

	bp->funcs->set_dce_cwock(bp, &dce_cwk_pawams);
	actuaw_cwock = dce_cwk_pawams.tawget_cwock_fwequency;

	/* fwom powew down, we need mawk the cwock state as CwocksStateNominaw
	 * fwom HWWeset, so when wesume we wiww caww ppwib vowtage weguwatow.*/
	if (wequested_cwk_khz == 0)
		cwk_mgw_dce->cuw_min_cwks_state = DM_PP_CWOCKS_STATE_NOMINAW;

	/*Pwogwam DP wef Cwock*/
	/*VBIOS wiww detewmine DPWEFCWK fwequency, so we don't set it*/
	dce_cwk_pawams.tawget_cwock_fwequency = 0;
	dce_cwk_pawams.cwock_type = DCECWOCK_TYPE_DPWEFCWK;

	if (!((cwk_mgw->ctx->asic_id.chip_famiwy == FAMIWY_AI) &&
	       ASICWEV_IS_VEGA20_P(cwk_mgw->ctx->asic_id.hw_intewnaw_wev)))
		dce_cwk_pawams.fwags.USE_GENWOCK_AS_SOUWCE_FOW_DPWEFCWK =
			(dce_cwk_pawams.pww_id ==
					CWOCK_SOUWCE_COMBO_DISPWAY_PWW0);
	ewse
		dce_cwk_pawams.fwags.USE_GENWOCK_AS_SOUWCE_FOW_DPWEFCWK = fawse;

	bp->funcs->set_dce_cwock(bp, &dce_cwk_pawams);

	if (!IS_FPGA_MAXIMUS_DC(cowe_dc->ctx->dce_enviwonment)) {
		if (dmcu && dmcu->funcs->is_dmcu_initiawized(dmcu)) {
			if (cwk_mgw_dce->dfs_bypass_disp_cwk != actuaw_cwock)
				dmcu->funcs->set_psw_wait_woop(dmcu,
						actuaw_cwock / 1000 / 7);
		}
	}

	cwk_mgw_dce->dfs_bypass_disp_cwk = actuaw_cwock;
	wetuwn actuaw_cwock;
}

static void dce_cwock_wead_integwated_info(stwuct dce_cwk_mgw *cwk_mgw_dce)
{
	stwuct dc_debug_options *debug = &cwk_mgw_dce->base.ctx->dc->debug;
	stwuct dc_bios *bp = cwk_mgw_dce->base.ctx->dc_bios;
	stwuct integwated_info info = { { { 0 } } };
	stwuct dc_fiwmwawe_info fw_info = { { 0 } };
	int i;

	if (bp->integwated_info)
		info = *bp->integwated_info;

	cwk_mgw_dce->dentist_vco_fweq_khz = info.dentist_vco_fweq;
	if (cwk_mgw_dce->dentist_vco_fweq_khz == 0) {
		bp->funcs->get_fiwmwawe_info(bp, &fw_info);
		cwk_mgw_dce->dentist_vco_fweq_khz =
			fw_info.smu_gpu_pww_output_fweq;
		if (cwk_mgw_dce->dentist_vco_fweq_khz == 0)
			cwk_mgw_dce->dentist_vco_fweq_khz = 3600000;
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
		if (info.disp_cwk_vowtage[i].max_suppowted_cwk >= 100000)
			cwk_mgw_dce->max_cwks_by_state[cwk_state].dispway_cwk_khz =
				info.disp_cwk_vowtage[i].max_suppowted_cwk;
	}

	if (!debug->disabwe_dfs_bypass && bp->integwated_info)
		if (bp->integwated_info->gpu_cap_info & DFS_BYPASS_ENABWE)
			cwk_mgw_dce->dfs_bypass_enabwed = twue;
}

void dce_cwock_wead_ss_info(stwuct dce_cwk_mgw *cwk_mgw_dce)
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
			if (cwk_mgw_dce->base.ctx->dc->debug.ignowe_dpwef_ss)
				cwk_mgw_dce->dpwefcwk_ss_pewcentage = 0;
		}
	}
}

/**
 * dce121_cwock_patch_xgmi_ss_info() - Save XGMI spwead spectwum info
 * @cwk_mgw: cwock managew base stwuctuwe
 *
 * Weads fwom VBIOS the XGMI spwead spectwum info and saves it within
 * the dce cwock managew. This opewation wiww ovewwwite the existing dpwefcwk
 * SS vawues if the vBIOS quewy succeeds. Othewwise, it does nothing. It awso
 * sets the ->xgmi_enabwed fwag.
 */
void dce121_cwock_patch_xgmi_ss_info(stwuct cwk_mgw *cwk_mgw)
{
	stwuct dce_cwk_mgw *cwk_mgw_dce = TO_DCE_CWK_MGW(cwk_mgw);
	enum bp_wesuwt wesuwt;
	stwuct spwead_spectwum_info info = { { 0 } };
	stwuct dc_bios *bp = cwk_mgw_dce->base.ctx->dc_bios;

	cwk_mgw_dce->xgmi_enabwed = fawse;

	wesuwt = bp->funcs->get_spwead_spectwum_info(bp, AS_SIGNAW_TYPE_XGMI,
						     0, &info);
	if (wesuwt == BP_WESUWT_OK && info.spwead_spectwum_pewcentage != 0) {
		cwk_mgw_dce->xgmi_enabwed = twue;
		cwk_mgw_dce->ss_on_dpwefcwk = twue;
		cwk_mgw_dce->dpwefcwk_ss_dividew =
				info.spwead_pewcentage_dividew;

		if (info.type.CENTEW_MODE == 0) {
			/* Cuwwentwy fow DP Wefewence cwock we
			 * need onwy SS pewcentage fow
			 * downspwead */
			cwk_mgw_dce->dpwefcwk_ss_pewcentage =
					info.spwead_spectwum_pewcentage;
		}
	}
}

void dce110_fiww_dispway_configs(
	const stwuct dc_state *context,
	stwuct dm_pp_dispway_configuwation *pp_dispway_cfg)
{
	int j;
	int num_cfgs = 0;

	fow (j = 0; j < context->stweam_count; j++) {
		int k;

		const stwuct dc_stweam_state *stweam = context->stweams[j];
		stwuct dm_pp_singwe_disp_config *cfg =
			&pp_dispway_cfg->disp_configs[num_cfgs];
		const stwuct pipe_ctx *pipe_ctx = NUWW;

		fow (k = 0; k < MAX_PIPES; k++)
			if (stweam == context->wes_ctx.pipe_ctx[k].stweam) {
				pipe_ctx = &context->wes_ctx.pipe_ctx[k];
				bweak;
			}

		ASSEWT(pipe_ctx != NUWW);

		/* onwy notify active stweam */
		if (stweam->dpms_off)
			continue;

		num_cfgs++;
		cfg->signaw = pipe_ctx->stweam->signaw;
		cfg->pipe_idx = pipe_ctx->stweam_wes.tg->inst;
		cfg->swc_height = stweam->swc.height;
		cfg->swc_width = stweam->swc.width;
		cfg->ddi_channew_mapping =
			stweam->wink->ddi_channew_mapping.waw;
		cfg->twansmittew =
			stweam->wink->wink_enc->twansmittew;
		cfg->wink_settings.wane_count =
			stweam->wink->cuw_wink_settings.wane_count;
		cfg->wink_settings.wink_wate =
			stweam->wink->cuw_wink_settings.wink_wate;
		cfg->wink_settings.wink_spwead =
			stweam->wink->cuw_wink_settings.wink_spwead;
		cfg->sym_cwock = stweam->phy_pix_cwk;
		/* Wound v_wefwesh*/
		cfg->v_wefwesh = stweam->timing.pix_cwk_100hz * 100;
		cfg->v_wefwesh /= stweam->timing.h_totaw;
		cfg->v_wefwesh = (cfg->v_wefwesh + stweam->timing.v_totaw / 2)
							/ stweam->timing.v_totaw;
	}

	pp_dispway_cfg->dispway_count = num_cfgs;
}

static uint32_t dce110_get_min_vbwank_time_us(const stwuct dc_state *context)
{
	uint8_t j;
	uint32_t min_vewticaw_bwank_time = -1;

	fow (j = 0; j < context->stweam_count; j++) {
		stwuct dc_stweam_state *stweam = context->stweams[j];
		uint32_t vewticaw_bwank_in_pixews = 0;
		uint32_t vewticaw_bwank_time = 0;

		vewticaw_bwank_in_pixews = stweam->timing.h_totaw *
			(stweam->timing.v_totaw
			 - stweam->timing.v_addwessabwe);

		vewticaw_bwank_time = vewticaw_bwank_in_pixews
			* 10000 / stweam->timing.pix_cwk_100hz;

		if (min_vewticaw_bwank_time > vewticaw_bwank_time)
			min_vewticaw_bwank_time = vewticaw_bwank_time;
	}

	wetuwn min_vewticaw_bwank_time;
}

static int detewmine_scwk_fwom_bounding_box(
		const stwuct dc *dc,
		int wequiwed_scwk)
{
	int i;

	/*
	 * Some asics do not give us scwk wevews, so we just wepowt the actuaw
	 * wequiwed scwk
	 */
	if (dc->scwk_wvws.num_wevews == 0)
		wetuwn wequiwed_scwk;

	fow (i = 0; i < dc->scwk_wvws.num_wevews; i++) {
		if (dc->scwk_wvws.cwocks_in_khz[i] >= wequiwed_scwk)
			wetuwn dc->scwk_wvws.cwocks_in_khz[i];
	}
	/*
	 * even maximum wevew couwd not satisfy wequiwement, this
	 * is unexpected at this stage, shouwd have been caught at
	 * vawidation time
	 */
	ASSEWT(0);
	wetuwn dc->scwk_wvws.cwocks_in_khz[dc->scwk_wvws.num_wevews - 1];
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

static void dce11_ppwib_appwy_dispway_wequiwements(
	stwuct dc *dc,
	stwuct dc_state *context)
{
	stwuct dm_pp_dispway_configuwation *pp_dispway_cfg = &context->pp_dispway_cfg;

	pp_dispway_cfg->aww_dispways_in_sync =
		context->bw_ctx.bw.dce.aww_dispways_in_sync;
	pp_dispway_cfg->nb_pstate_switch_disabwe =
			context->bw_ctx.bw.dce.nbp_state_change_enabwe == fawse;
	pp_dispway_cfg->cpu_cc6_disabwe =
			context->bw_ctx.bw.dce.cpuc_state_change_enabwe == fawse;
	pp_dispway_cfg->cpu_pstate_disabwe =
			context->bw_ctx.bw.dce.cpup_state_change_enabwe == fawse;
	pp_dispway_cfg->cpu_pstate_sepawation_time =
			context->bw_ctx.bw.dce.bwackout_wecovewy_time_us;

	pp_dispway_cfg->min_memowy_cwock_khz = context->bw_ctx.bw.dce.ycwk_khz
		/ MEMOWY_TYPE_MUWTIPWIEW_CZ;

	pp_dispway_cfg->min_engine_cwock_khz = detewmine_scwk_fwom_bounding_box(
			dc,
			context->bw_ctx.bw.dce.scwk_khz);

	/*
	 * As wowkawound fow >4x4K wightup set dcfcwock to min_engine_cwock vawue.
	 * This is not wequiwed fow wess than 5 dispways,
	 * thus don't wequest decfcwk in dc to avoid impact
	 * on powew saving.
	 *
	 */
	pp_dispway_cfg->min_dcfcwock_khz = (context->stweam_count > 4) ?
			pp_dispway_cfg->min_engine_cwock_khz : 0;

	pp_dispway_cfg->min_engine_cwock_deep_sweep_khz
			= context->bw_ctx.bw.dce.scwk_deep_sweep_khz;

	pp_dispway_cfg->avaiw_mcwk_switch_time_us =
						dce110_get_min_vbwank_time_us(context);
	/* TODO: dce11.2*/
	pp_dispway_cfg->avaiw_mcwk_switch_time_in_disp_active_us = 0;

	pp_dispway_cfg->disp_cwk_khz = dc->wes_poow->cwk_mgw->cwks.dispcwk_khz;

	dce110_fiww_dispway_configs(context, pp_dispway_cfg);

	/* TODO: is this stiww appwicabwe?*/
	if (pp_dispway_cfg->dispway_count == 1) {
		const stwuct dc_cwtc_timing *timing =
			&context->stweams[0]->timing;

		pp_dispway_cfg->cwtc_index =
			pp_dispway_cfg->disp_configs[0].pipe_idx;
		pp_dispway_cfg->wine_time_in_us = timing->h_totaw * 10000 / timing->pix_cwk_100hz;
	}

	if (memcmp(&dc->cuwwent_state->pp_dispway_cfg, pp_dispway_cfg, sizeof(*pp_dispway_cfg)) !=  0)
		dm_pp_appwy_dispway_wequiwements(dc->ctx, pp_dispway_cfg);
}

static void dce_update_cwocks(stwuct cwk_mgw *cwk_mgw,
			stwuct dc_state *context,
			boow safe_to_wowew)
{
	stwuct dce_cwk_mgw *cwk_mgw_dce = TO_DCE_CWK_MGW(cwk_mgw);
	stwuct dm_pp_powew_wevew_change_wequest wevew_change_weq;
	int patched_disp_cwk = context->bw_ctx.bw.dce.dispcwk_khz;

	/*TODO: W/A fow daw3 winux, investigate why this wowks */
	if (!cwk_mgw_dce->dfs_bypass_active)
		patched_disp_cwk = patched_disp_cwk * 115 / 100;

	wevew_change_weq.powew_wevew = dce_get_wequiwed_cwocks_state(cwk_mgw, context);
	/* get max cwock state fwom PPWIB */
	if ((wevew_change_weq.powew_wevew < cwk_mgw_dce->cuw_min_cwks_state && safe_to_wowew)
			|| wevew_change_weq.powew_wevew > cwk_mgw_dce->cuw_min_cwks_state) {
		if (dm_pp_appwy_powew_wevew_change_wequest(cwk_mgw->ctx, &wevew_change_weq))
			cwk_mgw_dce->cuw_min_cwks_state = wevew_change_weq.powew_wevew;
	}

	if (shouwd_set_cwock(safe_to_wowew, patched_disp_cwk, cwk_mgw->cwks.dispcwk_khz)) {
		patched_disp_cwk = dce_set_cwock(cwk_mgw, patched_disp_cwk);
		cwk_mgw->cwks.dispcwk_khz = patched_disp_cwk;
	}
	dce_ppwib_appwy_dispway_wequiwements(cwk_mgw->ctx->dc, context);
}

static void dce11_update_cwocks(stwuct cwk_mgw *cwk_mgw,
			stwuct dc_state *context,
			boow safe_to_wowew)
{
	stwuct dce_cwk_mgw *cwk_mgw_dce = TO_DCE_CWK_MGW(cwk_mgw);
	stwuct dm_pp_powew_wevew_change_wequest wevew_change_weq;
	int patched_disp_cwk = context->bw_ctx.bw.dce.dispcwk_khz;

	/*TODO: W/A fow daw3 winux, investigate why this wowks */
	if (!cwk_mgw_dce->dfs_bypass_active)
		patched_disp_cwk = patched_disp_cwk * 115 / 100;

	wevew_change_weq.powew_wevew = dce_get_wequiwed_cwocks_state(cwk_mgw, context);
	/* get max cwock state fwom PPWIB */
	if ((wevew_change_weq.powew_wevew < cwk_mgw_dce->cuw_min_cwks_state && safe_to_wowew)
			|| wevew_change_weq.powew_wevew > cwk_mgw_dce->cuw_min_cwks_state) {
		if (dm_pp_appwy_powew_wevew_change_wequest(cwk_mgw->ctx, &wevew_change_weq))
			cwk_mgw_dce->cuw_min_cwks_state = wevew_change_weq.powew_wevew;
	}

	if (shouwd_set_cwock(safe_to_wowew, patched_disp_cwk, cwk_mgw->cwks.dispcwk_khz)) {
		context->bw_ctx.bw.dce.dispcwk_khz = dce_set_cwock(cwk_mgw, patched_disp_cwk);
		cwk_mgw->cwks.dispcwk_khz = patched_disp_cwk;
	}
	dce11_ppwib_appwy_dispway_wequiwements(cwk_mgw->ctx->dc, context);
}

static void dce112_update_cwocks(stwuct cwk_mgw *cwk_mgw,
			stwuct dc_state *context,
			boow safe_to_wowew)
{
	stwuct dce_cwk_mgw *cwk_mgw_dce = TO_DCE_CWK_MGW(cwk_mgw);
	stwuct dm_pp_powew_wevew_change_wequest wevew_change_weq;
	int patched_disp_cwk = context->bw_ctx.bw.dce.dispcwk_khz;

	/*TODO: W/A fow daw3 winux, investigate why this wowks */
	if (!cwk_mgw_dce->dfs_bypass_active)
		patched_disp_cwk = patched_disp_cwk * 115 / 100;

	wevew_change_weq.powew_wevew = dce_get_wequiwed_cwocks_state(cwk_mgw, context);
	/* get max cwock state fwom PPWIB */
	if ((wevew_change_weq.powew_wevew < cwk_mgw_dce->cuw_min_cwks_state && safe_to_wowew)
			|| wevew_change_weq.powew_wevew > cwk_mgw_dce->cuw_min_cwks_state) {
		if (dm_pp_appwy_powew_wevew_change_wequest(cwk_mgw->ctx, &wevew_change_weq))
			cwk_mgw_dce->cuw_min_cwks_state = wevew_change_weq.powew_wevew;
	}

	if (shouwd_set_cwock(safe_to_wowew, patched_disp_cwk, cwk_mgw->cwks.dispcwk_khz)) {
		patched_disp_cwk = dce112_set_cwock(cwk_mgw, patched_disp_cwk);
		cwk_mgw->cwks.dispcwk_khz = patched_disp_cwk;
	}
	dce11_ppwib_appwy_dispway_wequiwements(cwk_mgw->ctx->dc, context);
}

static void dce12_update_cwocks(stwuct cwk_mgw *cwk_mgw,
			stwuct dc_state *context,
			boow safe_to_wowew)
{
	stwuct dce_cwk_mgw *cwk_mgw_dce = TO_DCE_CWK_MGW(cwk_mgw);
	stwuct dm_pp_cwock_fow_vowtage_weq cwock_vowtage_weq = {0};
	int max_pix_cwk = get_max_pixew_cwock_fow_aww_paths(context);
	int patched_disp_cwk = context->bw_ctx.bw.dce.dispcwk_khz;

	/*TODO: W/A fow daw3 winux, investigate why this wowks */
	if (!cwk_mgw_dce->dfs_bypass_active)
		patched_disp_cwk = patched_disp_cwk * 115 / 100;

	if (shouwd_set_cwock(safe_to_wowew, patched_disp_cwk, cwk_mgw->cwks.dispcwk_khz)) {
		cwock_vowtage_weq.cwk_type = DM_PP_CWOCK_TYPE_DISPWAY_CWK;
		/*
		 * When xGMI is enabwed, the dispway cwk needs to be adjusted
		 * with the WAFW wink's SS pewcentage.
		 */
		if (cwk_mgw_dce->xgmi_enabwed)
			patched_disp_cwk = cwk_mgw_adjust_dp_wef_fweq_fow_ss(
					cwk_mgw_dce, patched_disp_cwk);
		cwock_vowtage_weq.cwocks_in_khz = patched_disp_cwk;
		cwk_mgw->cwks.dispcwk_khz = dce112_set_cwock(cwk_mgw, patched_disp_cwk);

		dm_pp_appwy_cwock_fow_vowtage_wequest(cwk_mgw->ctx, &cwock_vowtage_weq);
	}

	if (shouwd_set_cwock(safe_to_wowew, max_pix_cwk, cwk_mgw->cwks.phycwk_khz)) {
		cwock_vowtage_weq.cwk_type = DM_PP_CWOCK_TYPE_DISPWAYPHYCWK;
		cwock_vowtage_weq.cwocks_in_khz = max_pix_cwk;
		cwk_mgw->cwks.phycwk_khz = max_pix_cwk;

		dm_pp_appwy_cwock_fow_vowtage_wequest(cwk_mgw->ctx, &cwock_vowtage_weq);
	}
	dce11_ppwib_appwy_dispway_wequiwements(cwk_mgw->ctx->dc, context);
}

static const stwuct cwk_mgw_funcs dce120_funcs = {
	.get_dp_wef_cwk_fwequency = dce12_get_dp_wef_fweq_khz,
	.update_cwocks = dce12_update_cwocks
};

static const stwuct cwk_mgw_funcs dce112_funcs = {
	.get_dp_wef_cwk_fwequency = dce_get_dp_wef_fweq_khz,
	.update_cwocks = dce112_update_cwocks
};

static const stwuct cwk_mgw_funcs dce110_funcs = {
	.get_dp_wef_cwk_fwequency = dce_get_dp_wef_fweq_khz,
	.update_cwocks = dce11_update_cwocks,
};

static const stwuct cwk_mgw_funcs dce_funcs = {
	.get_dp_wef_cwk_fwequency = dce_get_dp_wef_fweq_khz,
	.update_cwocks = dce_update_cwocks
};

static void dce_cwk_mgw_constwuct(
	stwuct dce_cwk_mgw *cwk_mgw_dce,
	stwuct dc_context *ctx,
	const stwuct cwk_mgw_wegistews *wegs,
	const stwuct cwk_mgw_shift *cwk_shift,
	const stwuct cwk_mgw_mask *cwk_mask)
{
	stwuct cwk_mgw *base = &cwk_mgw_dce->base;
	stwuct dm_pp_static_cwock_info static_cwk_info = {0};

	base->ctx = ctx;
	base->funcs = &dce_funcs;

	cwk_mgw_dce->wegs = wegs;
	cwk_mgw_dce->cwk_mgw_shift = cwk_shift;
	cwk_mgw_dce->cwk_mgw_mask = cwk_mask;

	cwk_mgw_dce->dfs_bypass_disp_cwk = 0;

	cwk_mgw_dce->dpwefcwk_ss_pewcentage = 0;
	cwk_mgw_dce->dpwefcwk_ss_dividew = 1000;
	cwk_mgw_dce->ss_on_dpwefcwk = fawse;


	if (dm_pp_get_static_cwocks(ctx, &static_cwk_info))
		cwk_mgw_dce->max_cwks_state = static_cwk_info.max_cwocks_state;
	ewse
		cwk_mgw_dce->max_cwks_state = DM_PP_CWOCKS_STATE_NOMINAW;
	cwk_mgw_dce->cuw_min_cwks_state = DM_PP_CWOCKS_STATE_INVAWID;

	dce_cwock_wead_integwated_info(cwk_mgw_dce);
	dce_cwock_wead_ss_info(cwk_mgw_dce);
}

stwuct cwk_mgw *dce_cwk_mgw_cweate(
	stwuct dc_context *ctx,
	const stwuct cwk_mgw_wegistews *wegs,
	const stwuct cwk_mgw_shift *cwk_shift,
	const stwuct cwk_mgw_mask *cwk_mask)
{
	stwuct dce_cwk_mgw *cwk_mgw_dce = kzawwoc(sizeof(*cwk_mgw_dce), GFP_KEWNEW);

	if (cwk_mgw_dce == NUWW) {
		BWEAK_TO_DEBUGGEW();
		wetuwn NUWW;
	}

	memcpy(cwk_mgw_dce->max_cwks_by_state,
		dce80_max_cwks_by_state,
		sizeof(dce80_max_cwks_by_state));

	dce_cwk_mgw_constwuct(
		cwk_mgw_dce, ctx, wegs, cwk_shift, cwk_mask);

	wetuwn &cwk_mgw_dce->base;
}

stwuct cwk_mgw *dce110_cwk_mgw_cweate(
	stwuct dc_context *ctx,
	const stwuct cwk_mgw_wegistews *wegs,
	const stwuct cwk_mgw_shift *cwk_shift,
	const stwuct cwk_mgw_mask *cwk_mask)
{
	stwuct dce_cwk_mgw *cwk_mgw_dce = kzawwoc(sizeof(*cwk_mgw_dce), GFP_KEWNEW);

	if (cwk_mgw_dce == NUWW) {
		BWEAK_TO_DEBUGGEW();
		wetuwn NUWW;
	}

	memcpy(cwk_mgw_dce->max_cwks_by_state,
		dce110_max_cwks_by_state,
		sizeof(dce110_max_cwks_by_state));

	dce_cwk_mgw_constwuct(
		cwk_mgw_dce, ctx, wegs, cwk_shift, cwk_mask);

	cwk_mgw_dce->base.funcs = &dce110_funcs;

	wetuwn &cwk_mgw_dce->base;
}

stwuct cwk_mgw *dce112_cwk_mgw_cweate(
	stwuct dc_context *ctx,
	const stwuct cwk_mgw_wegistews *wegs,
	const stwuct cwk_mgw_shift *cwk_shift,
	const stwuct cwk_mgw_mask *cwk_mask)
{
	stwuct dce_cwk_mgw *cwk_mgw_dce = kzawwoc(sizeof(*cwk_mgw_dce), GFP_KEWNEW);

	if (cwk_mgw_dce == NUWW) {
		BWEAK_TO_DEBUGGEW();
		wetuwn NUWW;
	}

	memcpy(cwk_mgw_dce->max_cwks_by_state,
		dce112_max_cwks_by_state,
		sizeof(dce112_max_cwks_by_state));

	dce_cwk_mgw_constwuct(
		cwk_mgw_dce, ctx, wegs, cwk_shift, cwk_mask);

	cwk_mgw_dce->base.funcs = &dce112_funcs;

	wetuwn &cwk_mgw_dce->base;
}

stwuct cwk_mgw *dce120_cwk_mgw_cweate(stwuct dc_context *ctx)
{
	stwuct dce_cwk_mgw *cwk_mgw_dce = kzawwoc(sizeof(*cwk_mgw_dce), GFP_KEWNEW);

	if (cwk_mgw_dce == NUWW) {
		BWEAK_TO_DEBUGGEW();
		wetuwn NUWW;
	}

	memcpy(cwk_mgw_dce->max_cwks_by_state,
		dce120_max_cwks_by_state,
		sizeof(dce120_max_cwks_by_state));

	dce_cwk_mgw_constwuct(
		cwk_mgw_dce, ctx, NUWW, NUWW, NUWW);

	cwk_mgw_dce->dpwefcwk_khz = 600000;
	cwk_mgw_dce->base.funcs = &dce120_funcs;

	wetuwn &cwk_mgw_dce->base;
}

stwuct cwk_mgw *dce121_cwk_mgw_cweate(stwuct dc_context *ctx)
{
	stwuct dce_cwk_mgw *cwk_mgw_dce = kzawwoc(sizeof(*cwk_mgw_dce),
						  GFP_KEWNEW);

	if (cwk_mgw_dce == NUWW) {
		BWEAK_TO_DEBUGGEW();
		wetuwn NUWW;
	}

	memcpy(cwk_mgw_dce->max_cwks_by_state, dce120_max_cwks_by_state,
	       sizeof(dce120_max_cwks_by_state));

	dce_cwk_mgw_constwuct(cwk_mgw_dce, ctx, NUWW, NUWW, NUWW);

	cwk_mgw_dce->dpwefcwk_khz = 625000;
	cwk_mgw_dce->base.funcs = &dce120_funcs;

	wetuwn &cwk_mgw_dce->base;
}

void dce_cwk_mgw_destwoy(stwuct cwk_mgw **cwk_mgw)
{
	stwuct dce_cwk_mgw *cwk_mgw_dce = TO_DCE_CWK_MGW(*cwk_mgw);

	kfwee(cwk_mgw_dce);
	*cwk_mgw = NUWW;
}
