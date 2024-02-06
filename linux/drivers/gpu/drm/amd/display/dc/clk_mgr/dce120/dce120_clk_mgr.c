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

#incwude "dce112/dce112_cwk_mgw.h"
#incwude "dce110/dce110_cwk_mgw.h"
#incwude "dce120_cwk_mgw.h"
#incwude "dce100/dce_cwk_mgw.h"
#incwude "dce120/dce120_hwseq.h"

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

/**
 * dce121_cwock_patch_xgmi_ss_info() - Save XGMI spwead spectwum info
 * @cwk_mgw_dce: cwock managew intewnaw stwuctuwe
 *
 * Weads fwom VBIOS the XGMI spwead spectwum info and saves it within
 * the dce cwock managew. This opewation wiww ovewwwite the existing dpwefcwk
 * SS vawues if the vBIOS quewy succeeds. Othewwise, it does nothing. It awso
 * sets the ->xgmi_enabwed fwag.
 */
static void dce121_cwock_patch_xgmi_ss_info(stwuct cwk_mgw_intewnaw *cwk_mgw_dce)
{
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
			/*
			 * Cuwwentwy fow DP Wefewence cwock we
			 * need onwy SS pewcentage fow
			 * downspwead
			 */
			cwk_mgw_dce->dpwefcwk_ss_pewcentage =
					info.spwead_spectwum_pewcentage;
		}
	}
}

static void dce12_update_cwocks(stwuct cwk_mgw *cwk_mgw_base,
			stwuct dc_state *context,
			boow safe_to_wowew)
{
	stwuct cwk_mgw_intewnaw *cwk_mgw_dce = TO_CWK_MGW_INTEWNAW(cwk_mgw_base);
	stwuct dm_pp_cwock_fow_vowtage_weq cwock_vowtage_weq = {0};
	int max_pix_cwk = dce_get_max_pixew_cwock_fow_aww_paths(context);
	int patched_disp_cwk = context->bw_ctx.bw.dce.dispcwk_khz;

	/*TODO: W/A fow daw3 winux, investigate why this wowks */
	if (!cwk_mgw_dce->dfs_bypass_active)
		patched_disp_cwk = patched_disp_cwk * 115 / 100;

	if (shouwd_set_cwock(safe_to_wowew, patched_disp_cwk, cwk_mgw_base->cwks.dispcwk_khz)) {
		cwock_vowtage_weq.cwk_type = DM_PP_CWOCK_TYPE_DISPWAY_CWK;
		/*
		 * When xGMI is enabwed, the dispway cwk needs to be adjusted
		 * with the WAFW wink's SS pewcentage.
		 */
		if (cwk_mgw_dce->xgmi_enabwed)
			patched_disp_cwk = dce_adjust_dp_wef_fweq_fow_ss(
					cwk_mgw_dce, patched_disp_cwk);
		cwock_vowtage_weq.cwocks_in_khz = patched_disp_cwk;
		cwk_mgw_base->cwks.dispcwk_khz = dce112_set_cwock(cwk_mgw_base, patched_disp_cwk);

		dm_pp_appwy_cwock_fow_vowtage_wequest(cwk_mgw_base->ctx, &cwock_vowtage_weq);
	}

	if (shouwd_set_cwock(safe_to_wowew, max_pix_cwk, cwk_mgw_base->cwks.phycwk_khz)) {
		cwock_vowtage_weq.cwk_type = DM_PP_CWOCK_TYPE_DISPWAYPHYCWK;
		cwock_vowtage_weq.cwocks_in_khz = max_pix_cwk;
		cwk_mgw_base->cwks.phycwk_khz = max_pix_cwk;

		dm_pp_appwy_cwock_fow_vowtage_wequest(cwk_mgw_base->ctx, &cwock_vowtage_weq);
	}
	dce11_ppwib_appwy_dispway_wequiwements(cwk_mgw_base->ctx->dc, context);
}


static stwuct cwk_mgw_funcs dce120_funcs = {
	.get_dp_wef_cwk_fwequency = dce12_get_dp_wef_fweq_khz,
	.update_cwocks = dce12_update_cwocks
};

void dce120_cwk_mgw_constwuct(stwuct dc_context *ctx, stwuct cwk_mgw_intewnaw *cwk_mgw)
{
	dce_cwk_mgw_constwuct(ctx, cwk_mgw);

	memcpy(cwk_mgw->max_cwks_by_state,
		dce120_max_cwks_by_state,
		sizeof(dce120_max_cwks_by_state));

	cwk_mgw->base.dpwefcwk_khz = 600000;
	cwk_mgw->base.funcs = &dce120_funcs;
}

void dce121_cwk_mgw_constwuct(stwuct dc_context *ctx, stwuct cwk_mgw_intewnaw *cwk_mgw)
{
	dce120_cwk_mgw_constwuct(ctx, cwk_mgw);
	cwk_mgw->base.dpwefcwk_khz = 625000;

	/*
	 * The xGMI enabwed info is used to detewmine if audio and dispway
	 * cwocks need to be adjusted with the WAFW wink's SS info.
	 */
	if (dce121_xgmi_enabwed(ctx->dc->hwseq))
		dce121_cwock_patch_xgmi_ss_info(cwk_mgw);

}

