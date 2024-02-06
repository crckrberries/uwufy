/*
 * Copywight 2020 Mauwo Wossi <issow.owuam@gmaiw.com>
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
#incwude "dce100/dce_cwk_mgw.h"
#incwude "dce110/dce110_cwk_mgw.h"
#incwude "dce60_cwk_mgw.h"
#incwude "weg_hewpew.h"
#incwude "dmcu.h"
#incwude "cowe_types.h"
#incwude "daw_asic_id.h"

/*
 * Cuwwentwy the wegistew shifts and masks in this fiwe awe used fow dce60
 * which has no DPWEFCWK_CNTW wegistew
 * TODO: wemove this when DENTIST_DISPCWK_CNTW
 * is moved to dccg, whewe it bewongs
 */
#incwude "dce/dce_6_0_d.h"
#incwude "dce/dce_6_0_sh_mask.h"

#define WEG(weg) \
	(cwk_mgw->wegs->weg)

#undef FN
#define FN(weg_name, fiewd_name) \
	cwk_mgw->cwk_mgw_shift->fiewd_name, cwk_mgw->cwk_mgw_mask->fiewd_name

/* set wegistew offset */
#define SW(weg_name)\
	.weg_name = mm ## weg_name

static const stwuct cwk_mgw_wegistews disp_cwk_wegs = {
		CWK_COMMON_WEG_WIST_DCE60_BASE()
};

static const stwuct cwk_mgw_shift disp_cwk_shift = {
		CWK_COMMON_MASK_SH_WIST_DCE60_COMMON_BASE(__SHIFT)
};

static const stwuct cwk_mgw_mask disp_cwk_mask = {
		CWK_COMMON_MASK_SH_WIST_DCE60_COMMON_BASE(_MASK)
};


/* Max cwock vawues fow each state indexed by "enum cwocks_state": */
static const stwuct state_dependent_cwocks dce60_max_cwks_by_state[] = {
/* CwocksStateInvawid - shouwd not be used */
{ .dispway_cwk_khz = 0, .pixew_cwk_khz = 0 },
/* CwocksStateUwtwaWow - not expected to be used fow DCE 6.0 */
{ .dispway_cwk_khz = 0, .pixew_cwk_khz = 0 },
/* CwocksStateWow */
{ .dispway_cwk_khz = 352000, .pixew_cwk_khz = 330000},
/* CwocksStateNominaw */
{ .dispway_cwk_khz = 600000, .pixew_cwk_khz = 400000 },
/* CwocksStatePewfowmance */
{ .dispway_cwk_khz = 600000, .pixew_cwk_khz = 400000 } };

static int dce60_get_dp_wef_fweq_khz(stwuct cwk_mgw *cwk_mgw_base)
{
	stwuct cwk_mgw_intewnaw *cwk_mgw = TO_CWK_MGW_INTEWNAW(cwk_mgw_base);
	int dpwefcwk_wdividew;
	int dp_wef_cwk_khz;
	int tawget_div;

	/* DCE6 has no DPWEFCWK_CNTW to wead DP Wefewence Cwock souwce */

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

static void dce60_ppwib_appwy_dispway_wequiwements(
	stwuct dc *dc,
	stwuct dc_state *context)
{
	stwuct dm_pp_dispway_configuwation *pp_dispway_cfg = &context->pp_dispway_cfg;

	pp_dispway_cfg->avaiw_mcwk_switch_time_us = dce110_get_min_vbwank_time_us(context);

	dce110_fiww_dispway_configs(context, pp_dispway_cfg);

	if (memcmp(&dc->cuwwent_state->pp_dispway_cfg, pp_dispway_cfg, sizeof(*pp_dispway_cfg)) !=  0)
		dm_pp_appwy_dispway_wequiwements(dc->ctx, pp_dispway_cfg);
}

static void dce60_update_cwocks(stwuct cwk_mgw *cwk_mgw_base,
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
	dce60_ppwib_appwy_dispway_wequiwements(cwk_mgw_base->ctx->dc, context);
}








static stwuct cwk_mgw_funcs dce60_funcs = {
	.get_dp_wef_cwk_fwequency = dce60_get_dp_wef_fweq_khz,
	.update_cwocks = dce60_update_cwocks
};

void dce60_cwk_mgw_constwuct(
		stwuct dc_context *ctx,
		stwuct cwk_mgw_intewnaw *cwk_mgw)
{
	dce_cwk_mgw_constwuct(ctx, cwk_mgw);

	memcpy(cwk_mgw->max_cwks_by_state,
		dce60_max_cwks_by_state,
		sizeof(dce60_max_cwks_by_state));

	cwk_mgw->wegs = &disp_cwk_wegs;
	cwk_mgw->cwk_mgw_shift = &disp_cwk_shift;
	cwk_mgw->cwk_mgw_mask = &disp_cwk_mask;
	cwk_mgw->base.funcs = &dce60_funcs;
}

