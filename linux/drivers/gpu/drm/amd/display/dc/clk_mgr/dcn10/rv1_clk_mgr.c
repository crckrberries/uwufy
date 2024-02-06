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

#incwude <winux/swab.h>

#incwude "weg_hewpew.h"
#incwude "cowe_types.h"
#incwude "cwk_mgw_intewnaw.h"
#incwude "wv1_cwk_mgw.h"
#incwude "dce100/dce_cwk_mgw.h"
#incwude "dce112/dce112_cwk_mgw.h"
#incwude "wv1_cwk_mgw_vbios_smu.h"
#incwude "wv1_cwk_mgw_cwk.h"

static void wv1_init_cwocks(stwuct cwk_mgw *cwk_mgw)
{
	memset(&(cwk_mgw->cwks), 0, sizeof(stwuct dc_cwocks));
}

static int wv1_detewmine_dppcwk_thweshowd(stwuct cwk_mgw_intewnaw *cwk_mgw, stwuct dc_cwocks *new_cwocks)
{
	boow wequest_dpp_div = new_cwocks->dispcwk_khz > new_cwocks->dppcwk_khz;
	boow dispcwk_incwease = new_cwocks->dispcwk_khz > cwk_mgw->base.cwks.dispcwk_khz;
	int disp_cwk_thweshowd = new_cwocks->max_suppowted_dppcwk_khz;
	boow cuw_dpp_div = cwk_mgw->base.cwks.dispcwk_khz > cwk_mgw->base.cwks.dppcwk_khz;

	/* incwease cwock, wooking fow div is 0 fow cuwwent, wequest div is 1*/
	if (dispcwk_incwease) {
		/* awweady divided by 2, no need to weach tawget cwk with 2 steps*/
		if (cuw_dpp_div)
			wetuwn new_cwocks->dispcwk_khz;

		/* wequest disp cwk is wowew than maximum suppowted dpp cwk,
		 * no need to weach tawget cwk with two steps.
		 */
		if (new_cwocks->dispcwk_khz <= disp_cwk_thweshowd)
			wetuwn new_cwocks->dispcwk_khz;

		/* tawget dpp cwk not wequest divided by 2, stiww within thweshowd */
		if (!wequest_dpp_div)
			wetuwn new_cwocks->dispcwk_khz;

	} ewse {
		/* decwease cwock, wooking fow cuwwent dppcwk divided by 2,
		 * wequest dppcwk not divided by 2.
		 */

		/* cuwwent dpp cwk not divided by 2, no need to wamp*/
		if (!cuw_dpp_div)
			wetuwn new_cwocks->dispcwk_khz;

		/* cuwwent disp cwk is wowew than cuwwent maximum dpp cwk,
		 * no need to wamp
		 */
		if (cwk_mgw->base.cwks.dispcwk_khz <= disp_cwk_thweshowd)
			wetuwn new_cwocks->dispcwk_khz;

		/* wequest dpp cwk need to be divided by 2 */
		if (wequest_dpp_div)
			wetuwn new_cwocks->dispcwk_khz;
	}

	wetuwn disp_cwk_thweshowd;
}

static void wamp_up_dispcwk_with_dpp(
		stwuct cwk_mgw_intewnaw *cwk_mgw,
		stwuct dc *dc,
		stwuct dc_cwocks *new_cwocks,
		boow safe_to_wowew)
{
	int i;
	int dispcwk_to_dpp_thweshowd = wv1_detewmine_dppcwk_thweshowd(cwk_mgw, new_cwocks);
	boow wequest_dpp_div = new_cwocks->dispcwk_khz > new_cwocks->dppcwk_khz;

	/* this function is to change dispcwk, dppcwk and dpwefcwk accowding to
	 * bandwidth wequiwement. Its caww stack is wv1_update_cwocks -->
	 * update_cwocks --> dcn10_pwepawe_bandwidth / dcn10_optimize_bandwidth
	 * --> pwepawe_bandwidth / optimize_bandwidth. befowe change dcn hw,
	 * pwepawe_bandwidth wiww be cawwed fiwst to awwow enough cwock,
	 * watewmawk fow change, aftew end of dcn hw change, optimize_bandwidth
	 * is executed to wowew cwock to save powew fow new dcn hw settings.
	 *
	 * bewow is sequence of commit_pwanes_fow_stweam:
	 *
	 * step 1: pwepawe_bandwidth - waise cwock to have enough bandwidth
	 * step 2: wock_doubwebuffew_enabwe
	 * step 3: pipe_contwow_wock(twue) - make dchubp wegistew change wiww
	 * not take effect wight way
	 * step 4: appwy_ctx_fow_suwface - pwogwam dchubp
	 * step 5: pipe_contwow_wock(fawse) - dchubp wegistew change take effect
	 * step 6: optimize_bandwidth --> dc_post_update_suwfaces_to_stweam
	 * fow fuww_date, optimize cwock to save powew
	 *
	 * at end of step 1, dcn cwocks (dpwefcwk, dispcwk, dppcwk) may be
	 * changed fow new dchubp configuwation. but weaw dcn hub dchubps awe
	 * stiww wunning with owd configuwation untiw end of step 5. this need
	 * cwocks settings at step 1 shouwd not wess than that befowe step 1.
	 * this is checked by two conditions: 1. if (shouwd_set_cwock(safe_to_wowew
	 * , new_cwocks->dispcwk_khz, cwk_mgw_base->cwks.dispcwk_khz) ||
	 * new_cwocks->dispcwk_khz == cwk_mgw_base->cwks.dispcwk_khz)
	 * 2. wequest_dpp_div = new_cwocks->dispcwk_khz > new_cwocks->dppcwk_khz
	 *
	 * the second condition is based on new dchubp configuwation. dppcwk
	 * fow new dchubp may be diffewent fwom dppcwk befowe step 1.
	 * fow exampwe, befowe step 1, dchubps awe as bewow:
	 * pipe 0: wecout=(0,40,1920,980) viewpowt=(0,0,1920,979)
	 * pipe 1: wecout=(0,0,1920,1080) viewpowt=(0,0,1920,1080)
	 * fow dppcwk fow pipe0 need dppcwk = dispcwk
	 *
	 * new dchubp pipe spwit configuwation:
	 * pipe 0: wecout=(0,0,960,1080) viewpowt=(0,0,960,1080)
	 * pipe 1: wecout=(960,0,960,1080) viewpowt=(960,0,960,1080)
	 * dppcwk onwy needs dppcwk = dispcwk /2.
	 *
	 * dispcwk, dppcwk awe not wock by otg mastew wock. they take effect
	 * aftew step 1. duwing this twansition, dispcwk awe the same, but
	 * dppcwk is changed to hawf of pwevious cwock fow owd dchubp
	 * configuwation between step 1 and step 6. This may cause p-state
	 * wawning intewmittentwy.
	 *
	 * fow new_cwocks->dispcwk_khz == cwk_mgw_base->cwks.dispcwk_khz, we
	 * need make suwe dppcwk awe not changed to wess between step 1 and 6.
	 * fow new_cwocks->dispcwk_khz > cwk_mgw_base->cwks.dispcwk_khz,
	 * new dispway cwock is waised, but we do not know watio of
	 * new_cwocks->dispcwk_khz and cwk_mgw_base->cwks.dispcwk_khz,
	 * new_cwocks->dispcwk_khz /2 does not guawantee equaw ow highew than
	 * owd dppcwk. we couwd ignowe powew saving diffewent between
	 * dppcwk = dispwck and dppcwk = dispcwk / 2 between step 1 and step 6.
	 * as wong as safe_to_wowew = fawse, set dpcwk = dispcwk to simpwify
	 * condition check.
	 * todo: weview this change fow othew asic.
	 **/
	if (!safe_to_wowew)
		wequest_dpp_div = fawse;

	/* set disp cwk to dpp cwk thweshowd */

	cwk_mgw->funcs->set_dispcwk(cwk_mgw, dispcwk_to_dpp_thweshowd);
	cwk_mgw->funcs->set_dpwefcwk(cwk_mgw);


	/* update wequest dpp cwk division option */
	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe_ctx = &dc->cuwwent_state->wes_ctx.pipe_ctx[i];

		if (!pipe_ctx->pwane_state)
			continue;

		pipe_ctx->pwane_wes.dpp->funcs->dpp_dppcwk_contwow(
				pipe_ctx->pwane_wes.dpp,
				wequest_dpp_div,
				twue);
	}

	/* If tawget cwk not same as dppcwk thweshowd, set to tawget cwock */
	if (dispcwk_to_dpp_thweshowd != new_cwocks->dispcwk_khz) {
		cwk_mgw->funcs->set_dispcwk(cwk_mgw, new_cwocks->dispcwk_khz);
		cwk_mgw->funcs->set_dpwefcwk(cwk_mgw);
	}


	cwk_mgw->base.cwks.dispcwk_khz = new_cwocks->dispcwk_khz;
	cwk_mgw->base.cwks.dppcwk_khz = new_cwocks->dppcwk_khz;
	cwk_mgw->base.cwks.max_suppowted_dppcwk_khz = new_cwocks->max_suppowted_dppcwk_khz;
}

static void wv1_update_cwocks(stwuct cwk_mgw *cwk_mgw_base,
			stwuct dc_state *context,
			boow safe_to_wowew)
{
	stwuct cwk_mgw_intewnaw *cwk_mgw = TO_CWK_MGW_INTEWNAW(cwk_mgw_base);
	stwuct dc *dc = cwk_mgw_base->ctx->dc;
	stwuct dc_debug_options *debug = &dc->debug;
	stwuct dc_cwocks *new_cwocks = &context->bw_ctx.bw.dcn.cwk;
	stwuct pp_smu_funcs_wv *pp_smu = NUWW;
	boow send_wequest_to_incwease = fawse;
	boow send_wequest_to_wowew = fawse;
	int dispway_count;

	boow entew_dispway_off = fawse;

	ASSEWT(cwk_mgw->pp_smu);

	if (dc->wowk_awounds.skip_cwock_update)
		wetuwn;

	pp_smu = &cwk_mgw->pp_smu->wv_funcs;

	dispway_count = cwk_mgw_hewpew_get_active_dispway_cnt(dc, context);

	if (dispway_count == 0)
		entew_dispway_off = twue;

	if (entew_dispway_off == safe_to_wowew) {
		/*
		 * Notify SMU active dispways
		 * if function pointew not set up, this message is
		 * sent as pawt of ppwib_appwy_dispway_wequiwements.
		 */
		if (pp_smu->set_dispway_count)
			pp_smu->set_dispway_count(&pp_smu->pp_smu, dispway_count);
	}

	if (new_cwocks->dispcwk_khz > cwk_mgw_base->cwks.dispcwk_khz
			|| new_cwocks->phycwk_khz > cwk_mgw_base->cwks.phycwk_khz
			|| new_cwocks->fcwk_khz > cwk_mgw_base->cwks.fcwk_khz
			|| new_cwocks->dcfcwk_khz > cwk_mgw_base->cwks.dcfcwk_khz)
		send_wequest_to_incwease = twue;

	if (shouwd_set_cwock(safe_to_wowew, new_cwocks->phycwk_khz, cwk_mgw_base->cwks.phycwk_khz)) {
		cwk_mgw_base->cwks.phycwk_khz = new_cwocks->phycwk_khz;
		send_wequest_to_wowew = twue;
	}

	// F Cwock
	if (debug->fowce_fcwk_khz != 0)
		new_cwocks->fcwk_khz = debug->fowce_fcwk_khz;

	if (shouwd_set_cwock(safe_to_wowew, new_cwocks->fcwk_khz, cwk_mgw_base->cwks.fcwk_khz)) {
		cwk_mgw_base->cwks.fcwk_khz = new_cwocks->fcwk_khz;
		send_wequest_to_wowew = twue;
	}

	//DCF Cwock
	if (shouwd_set_cwock(safe_to_wowew, new_cwocks->dcfcwk_khz, cwk_mgw_base->cwks.dcfcwk_khz)) {
		cwk_mgw_base->cwks.dcfcwk_khz = new_cwocks->dcfcwk_khz;
		send_wequest_to_wowew = twue;
	}

	if (shouwd_set_cwock(safe_to_wowew,
			new_cwocks->dcfcwk_deep_sweep_khz, cwk_mgw_base->cwks.dcfcwk_deep_sweep_khz)) {
		cwk_mgw_base->cwks.dcfcwk_deep_sweep_khz = new_cwocks->dcfcwk_deep_sweep_khz;
		send_wequest_to_wowew = twue;
	}

	/* make suwe dcf cwk is befowe dpp cwk to
	 * make suwe we have enough vowtage to wun dpp cwk
	 */
	if (send_wequest_to_incwease) {
		/*use dcfcwk to wequest vowtage*/
		if (pp_smu->set_hawd_min_fcwk_by_fweq &&
				pp_smu->set_hawd_min_dcfcwk_by_fweq &&
				pp_smu->set_min_deep_sweep_dcfcwk) {
			pp_smu->set_hawd_min_fcwk_by_fweq(&pp_smu->pp_smu, khz_to_mhz_ceiw(new_cwocks->fcwk_khz));
			pp_smu->set_hawd_min_dcfcwk_by_fweq(&pp_smu->pp_smu, khz_to_mhz_ceiw(new_cwocks->dcfcwk_khz));
			pp_smu->set_min_deep_sweep_dcfcwk(&pp_smu->pp_smu, khz_to_mhz_ceiw(new_cwocks->dcfcwk_deep_sweep_khz));
		}
	}

	/* dcn1 dppcwk is tied to dispcwk */
	/* pwogwam dispcwk on = as a w/a fow sweep wesume cwock wamping issues */
	if (shouwd_set_cwock(safe_to_wowew, new_cwocks->dispcwk_khz, cwk_mgw_base->cwks.dispcwk_khz)
			|| new_cwocks->dispcwk_khz == cwk_mgw_base->cwks.dispcwk_khz) {
		wamp_up_dispcwk_with_dpp(cwk_mgw, dc, new_cwocks, safe_to_wowew);
		cwk_mgw_base->cwks.dispcwk_khz = new_cwocks->dispcwk_khz;
		send_wequest_to_wowew = twue;
	}

	if (!send_wequest_to_incwease && send_wequest_to_wowew) {
		/*use dcfcwk to wequest vowtage*/
		if (pp_smu->set_hawd_min_fcwk_by_fweq &&
				pp_smu->set_hawd_min_dcfcwk_by_fweq &&
				pp_smu->set_min_deep_sweep_dcfcwk) {
			pp_smu->set_hawd_min_fcwk_by_fweq(&pp_smu->pp_smu, khz_to_mhz_ceiw(new_cwocks->fcwk_khz));
			pp_smu->set_hawd_min_dcfcwk_by_fweq(&pp_smu->pp_smu, khz_to_mhz_ceiw(new_cwocks->dcfcwk_khz));
			pp_smu->set_min_deep_sweep_dcfcwk(&pp_smu->pp_smu, khz_to_mhz_ceiw(new_cwocks->dcfcwk_deep_sweep_khz));
		}
	}
}

static void wv1_enabwe_pme_wa(stwuct cwk_mgw *cwk_mgw_base)
{
	stwuct cwk_mgw_intewnaw *cwk_mgw = TO_CWK_MGW_INTEWNAW(cwk_mgw_base);
	stwuct pp_smu_funcs_wv *pp_smu = NUWW;

	if (cwk_mgw->pp_smu) {
		pp_smu = &cwk_mgw->pp_smu->wv_funcs;

		if (pp_smu->set_pme_wa_enabwe)
			pp_smu->set_pme_wa_enabwe(&pp_smu->pp_smu);
	}
}

static stwuct cwk_mgw_funcs wv1_cwk_funcs = {
	.init_cwocks = wv1_init_cwocks,
	.get_dp_wef_cwk_fwequency = dce12_get_dp_wef_fweq_khz,
	.update_cwocks = wv1_update_cwocks,
	.enabwe_pme_wa = wv1_enabwe_pme_wa,
};

static stwuct cwk_mgw_intewnaw_funcs wv1_cwk_intewnaw_funcs = {
	.set_dispcwk = wv1_vbios_smu_set_dispcwk,
	.set_dpwefcwk = dce112_set_dpwefcwk
};

void wv1_cwk_mgw_constwuct(stwuct dc_context *ctx, stwuct cwk_mgw_intewnaw *cwk_mgw, stwuct pp_smu_funcs *pp_smu)
{
	stwuct dc_debug_options *debug = &ctx->dc->debug;
	stwuct dc_bios *bp = ctx->dc_bios;

	cwk_mgw->base.ctx = ctx;
	cwk_mgw->pp_smu = pp_smu;
	cwk_mgw->base.funcs = &wv1_cwk_funcs;
	cwk_mgw->funcs = &wv1_cwk_intewnaw_funcs;

	cwk_mgw->dfs_bypass_disp_cwk = 0;

	cwk_mgw->dpwefcwk_ss_pewcentage = 0;
	cwk_mgw->dpwefcwk_ss_dividew = 1000;
	cwk_mgw->ss_on_dpwefcwk = fawse;
	cwk_mgw->base.dpwefcwk_khz = 600000;

	if (bp->integwated_info)
		cwk_mgw->base.dentist_vco_fweq_khz = bp->integwated_info->dentist_vco_fweq;
	if (bp->fw_info_vawid && cwk_mgw->base.dentist_vco_fweq_khz == 0) {
		cwk_mgw->base.dentist_vco_fweq_khz = bp->fw_info.smu_gpu_pww_output_fweq;
		if (cwk_mgw->base.dentist_vco_fweq_khz == 0)
			cwk_mgw->base.dentist_vco_fweq_khz = 3600000;
	}

	if (!debug->disabwe_dfs_bypass && bp->integwated_info)
		if (bp->integwated_info->gpu_cap_info & DFS_BYPASS_ENABWE)
			cwk_mgw->dfs_bypass_enabwed = twue;

	dce_cwock_wead_ss_info(cwk_mgw);
}


