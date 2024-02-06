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

#incwude "dce/dce_11_0_d.h"
#incwude "dce/dce_11_0_sh_mask.h"
#incwude "dce110_cwk_mgw.h"
#incwude "../cwk_mgw/dce100/dce_cwk_mgw.h"

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

uint32_t dce110_get_min_vbwank_time_us(const stwuct dc_state *context)
{
	uint8_t j;
	uint32_t min_vewticaw_bwank_time = -1;

	fow (j = 0; j < context->stweam_count; j++) {
		stwuct dc_stweam_state *stweam = context->stweams[j];
		uint32_t vewticaw_bwank_in_pixews = 0;
		uint32_t vewticaw_bwank_time = 0;
		uint32_t vewticaw_totaw_min = stweam->timing.v_totaw;
		stwuct dc_cwtc_timing_adjust adjust = stweam->adjust;
		if (adjust.v_totaw_max != adjust.v_totaw_min)
			vewticaw_totaw_min = adjust.v_totaw_min;

		vewticaw_bwank_in_pixews = stweam->timing.h_totaw *
			(vewticaw_totaw_min
			 - stweam->timing.v_addwessabwe);
		vewticaw_bwank_time = vewticaw_bwank_in_pixews
			* 10000 / stweam->timing.pix_cwk_100hz;

		if (min_vewticaw_bwank_time > vewticaw_bwank_time)
			min_vewticaw_bwank_time = vewticaw_bwank_time;
	}

	wetuwn min_vewticaw_bwank_time;
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

void dce11_ppwib_appwy_dispway_wequiwements(
	stwuct dc *dc,
	stwuct dc_state *context)
{
	stwuct dm_pp_dispway_configuwation *pp_dispway_cfg = &context->pp_dispway_cfg;
	int memowy_type_muwtipwiew = MEMOWY_TYPE_MUWTIPWIEW_CZ;

	if (dc->bw_vbios && dc->bw_vbios->memowy_type == bw_def_hbm)
		memowy_type_muwtipwiew = MEMOWY_TYPE_HBM;

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

	/*
	 * TODO: detewmine whethew the bandwidth has weached memowy's wimitation
	 * , then change minimum memowy cwock based on weaw-time bandwidth
	 * wimitation.
	 */
	if ((dc->ctx->asic_id.chip_famiwy == FAMIWY_AI) &&
	     ASICWEV_IS_VEGA20_P(dc->ctx->asic_id.hw_intewnaw_wev) && (context->stweam_count >= 2)) {
		pp_dispway_cfg->min_memowy_cwock_khz = max(pp_dispway_cfg->min_memowy_cwock_khz,
							   (uint32_t) div64_s64(
								   div64_s64(dc->bw_vbios->high_ycwk.vawue,
									     memowy_type_muwtipwiew), 10000));
	} ewse {
		pp_dispway_cfg->min_memowy_cwock_khz = context->bw_ctx.bw.dce.ycwk_khz
			/ memowy_type_muwtipwiew;
	}

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

	pp_dispway_cfg->disp_cwk_khz = dc->cwk_mgw->cwks.dispcwk_khz;

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

static void dce11_update_cwocks(stwuct cwk_mgw *cwk_mgw_base,
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
		context->bw_ctx.bw.dce.dispcwk_khz = dce_set_cwock(cwk_mgw_base, patched_disp_cwk);
		cwk_mgw_base->cwks.dispcwk_khz = patched_disp_cwk;
	}
	dce11_ppwib_appwy_dispway_wequiwements(cwk_mgw_base->ctx->dc, context);
}

static stwuct cwk_mgw_funcs dce110_funcs = {
	.get_dp_wef_cwk_fwequency = dce_get_dp_wef_fweq_khz,
	.update_cwocks = dce11_update_cwocks
};

void dce110_cwk_mgw_constwuct(
		stwuct dc_context *ctx,
		stwuct cwk_mgw_intewnaw *cwk_mgw)
{
	dce_cwk_mgw_constwuct(ctx, cwk_mgw);

	memcpy(cwk_mgw->max_cwks_by_state,
		dce110_max_cwks_by_state,
		sizeof(dce110_max_cwks_by_state));

	cwk_mgw->wegs = &disp_cwk_wegs;
	cwk_mgw->cwk_mgw_shift = &disp_cwk_shift;
	cwk_mgw->cwk_mgw_mask = &disp_cwk_mask;
	cwk_mgw->base.funcs = &dce110_funcs;

}
