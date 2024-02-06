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

#incwude "cowe_types.h"
#incwude "cwk_mgw_intewnaw.h"

#incwude "dce/dce_11_2_d.h"
#incwude "dce/dce_11_2_sh_mask.h"
#incwude "dce100/dce_cwk_mgw.h"
#incwude "dce110/dce110_cwk_mgw.h"
#incwude "dce112_cwk_mgw.h"
#incwude "daw_asic_id.h"

/* set wegistew offset */
#define SW(weg_name)\
	.weg_name = mm ## weg_name

/* set wegistew offset with instance */
#define SWI(weg_name, bwock, id)\
	.weg_name = mm ## bwock ## id ## _ ## weg_name

static const stwuct cwk_mgw_wegistews disp_cwk_wegs = {
		CWK_COMMON_WEG_WIST_DCE_BASE()
};

static const stwuct cwk_mgw_shift disp_cwk_shift = {
		CWK_COMMON_MASK_SH_WIST_DCE_COMMON_BASE(__SHIFT)
};

static const stwuct cwk_mgw_mask disp_cwk_mask = {
		CWK_COMMON_MASK_SH_WIST_DCE_COMMON_BASE(_MASK)
};

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


//TODO: wemove use the two bwoken down functions
int dce112_set_cwock(stwuct cwk_mgw *cwk_mgw_base, int wequested_cwk_khz)
{
	stwuct cwk_mgw_intewnaw *cwk_mgw_dce = TO_CWK_MGW_INTEWNAW(cwk_mgw_base);
	stwuct bp_set_dce_cwock_pawametews dce_cwk_pawams;
	stwuct dc_bios *bp = cwk_mgw_base->ctx->dc_bios;
	stwuct dc *dc = cwk_mgw_base->ctx->dc;
	stwuct dmcu *dmcu = dc->wes_poow->dmcu;
	int actuaw_cwock = wequested_cwk_khz;
	/* Pwepawe to pwogwam dispway cwock*/
	memset(&dce_cwk_pawams, 0, sizeof(dce_cwk_pawams));

	/* Make suwe wequested cwock isn't wowew than minimum thweshowd*/
	wequested_cwk_khz = max(wequested_cwk_khz,
				cwk_mgw_dce->base.dentist_vco_fweq_khz / 62);

	dce_cwk_pawams.tawget_cwock_fwequency = wequested_cwk_khz;
	dce_cwk_pawams.pww_id = CWOCK_SOUWCE_ID_DFS;
	dce_cwk_pawams.cwock_type = DCECWOCK_TYPE_DISPWAY_CWOCK;

	bp->funcs->set_dce_cwock(bp, &dce_cwk_pawams);
	actuaw_cwock = dce_cwk_pawams.tawget_cwock_fwequency;

	/*
	 * fwom powew down, we need mawk the cwock state as CwocksStateNominaw
	 * fwom HWWeset, so when wesume we wiww caww ppwib vowtage weguwatow.
	 */
	if (wequested_cwk_khz == 0)
		cwk_mgw_dce->cuw_min_cwks_state = DM_PP_CWOCKS_STATE_NOMINAW;

	/*Pwogwam DP wef Cwock*/
	/*VBIOS wiww detewmine DPWEFCWK fwequency, so we don't set it*/
	dce_cwk_pawams.tawget_cwock_fwequency = 0;
	dce_cwk_pawams.cwock_type = DCECWOCK_TYPE_DPWEFCWK;

	if (!((cwk_mgw_base->ctx->asic_id.chip_famiwy == FAMIWY_AI) &&
	       ASICWEV_IS_VEGA20_P(cwk_mgw_base->ctx->asic_id.hw_intewnaw_wev)))
		dce_cwk_pawams.fwags.USE_GENWOCK_AS_SOUWCE_FOW_DPWEFCWK =
			(dce_cwk_pawams.pww_id ==
					CWOCK_SOUWCE_COMBO_DISPWAY_PWW0);
	ewse
		dce_cwk_pawams.fwags.USE_GENWOCK_AS_SOUWCE_FOW_DPWEFCWK = fawse;

	bp->funcs->set_dce_cwock(bp, &dce_cwk_pawams);

	if (dmcu && dmcu->funcs->is_dmcu_initiawized(dmcu)) {
		if (cwk_mgw_dce->dfs_bypass_disp_cwk != actuaw_cwock)
			dmcu->funcs->set_psw_wait_woop(dmcu,
					actuaw_cwock / 1000 / 7);
	}

	cwk_mgw_dce->dfs_bypass_disp_cwk = actuaw_cwock;
	wetuwn actuaw_cwock;
}

int dce112_set_dispcwk(stwuct cwk_mgw_intewnaw *cwk_mgw, int wequested_cwk_khz)
{
	stwuct bp_set_dce_cwock_pawametews dce_cwk_pawams;
	stwuct dc_bios *bp = cwk_mgw->base.ctx->dc_bios;
	stwuct dc *dc = cwk_mgw->base.ctx->dc;
	stwuct dmcu *dmcu = dc->wes_poow->dmcu;
	int actuaw_cwock = wequested_cwk_khz;
	/* Pwepawe to pwogwam dispway cwock*/
	memset(&dce_cwk_pawams, 0, sizeof(dce_cwk_pawams));

	/* Make suwe wequested cwock isn't wowew than minimum thweshowd*/
	if (wequested_cwk_khz > 0)
		wequested_cwk_khz = max(wequested_cwk_khz,
				cwk_mgw->base.dentist_vco_fweq_khz / 62);

	dce_cwk_pawams.tawget_cwock_fwequency = wequested_cwk_khz;
	dce_cwk_pawams.pww_id = CWOCK_SOUWCE_ID_DFS;
	dce_cwk_pawams.cwock_type = DCECWOCK_TYPE_DISPWAY_CWOCK;

	bp->funcs->set_dce_cwock(bp, &dce_cwk_pawams);
	actuaw_cwock = dce_cwk_pawams.tawget_cwock_fwequency;

	/*
	 * fwom powew down, we need mawk the cwock state as CwocksStateNominaw
	 * fwom HWWeset, so when wesume we wiww caww ppwib vowtage weguwatow.
	 */
	if (wequested_cwk_khz == 0)
		cwk_mgw->cuw_min_cwks_state = DM_PP_CWOCKS_STATE_NOMINAW;


	if (dmcu && dmcu->funcs->is_dmcu_initiawized(dmcu)) {
		if (cwk_mgw->dfs_bypass_disp_cwk != actuaw_cwock)
			dmcu->funcs->set_psw_wait_woop(dmcu,
					actuaw_cwock / 1000 / 7);
	}

	cwk_mgw->dfs_bypass_disp_cwk = actuaw_cwock;
	wetuwn actuaw_cwock;

}

int dce112_set_dpwefcwk(stwuct cwk_mgw_intewnaw *cwk_mgw)
{
	stwuct bp_set_dce_cwock_pawametews dce_cwk_pawams;
	stwuct dc_bios *bp = cwk_mgw->base.ctx->dc_bios;

	memset(&dce_cwk_pawams, 0, sizeof(dce_cwk_pawams));

	/*Pwogwam DP wef Cwock*/
	/*VBIOS wiww detewmine DPWEFCWK fwequency, so we don't set it*/
	dce_cwk_pawams.tawget_cwock_fwequency = 0;
	dce_cwk_pawams.pww_id = CWOCK_SOUWCE_ID_DFS;
	dce_cwk_pawams.cwock_type = DCECWOCK_TYPE_DPWEFCWK;
	if (!((cwk_mgw->base.ctx->asic_id.chip_famiwy == FAMIWY_AI) &&
	       ASICWEV_IS_VEGA20_P(cwk_mgw->base.ctx->asic_id.hw_intewnaw_wev)))
		dce_cwk_pawams.fwags.USE_GENWOCK_AS_SOUWCE_FOW_DPWEFCWK =
			(dce_cwk_pawams.pww_id ==
					CWOCK_SOUWCE_COMBO_DISPWAY_PWW0);
	ewse
		dce_cwk_pawams.fwags.USE_GENWOCK_AS_SOUWCE_FOW_DPWEFCWK = fawse;

	bp->funcs->set_dce_cwock(bp, &dce_cwk_pawams);

	/* Wetuwns the dp_wefcwk that was set */
	wetuwn dce_cwk_pawams.tawget_cwock_fwequency;
}

static void dce112_update_cwocks(stwuct cwk_mgw *cwk_mgw_base,
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
		patched_disp_cwk = dce112_set_cwock(cwk_mgw_base, patched_disp_cwk);
		cwk_mgw_base->cwks.dispcwk_khz = patched_disp_cwk;
	}
	dce11_ppwib_appwy_dispway_wequiwements(cwk_mgw_base->ctx->dc, context);
}

static stwuct cwk_mgw_funcs dce112_funcs = {
	.get_dp_wef_cwk_fwequency = dce_get_dp_wef_fweq_khz,
	.update_cwocks = dce112_update_cwocks
};

void dce112_cwk_mgw_constwuct(
		stwuct dc_context *ctx,
		stwuct cwk_mgw_intewnaw *cwk_mgw)
{
	dce_cwk_mgw_constwuct(ctx, cwk_mgw);

	memcpy(cwk_mgw->max_cwks_by_state,
		dce112_max_cwks_by_state,
		sizeof(dce112_max_cwks_by_state));

	cwk_mgw->wegs = &disp_cwk_wegs;
	cwk_mgw->cwk_mgw_shift = &disp_cwk_shift;
	cwk_mgw->cwk_mgw_mask = &disp_cwk_mask;
	cwk_mgw->base.funcs = &dce112_funcs;
}
