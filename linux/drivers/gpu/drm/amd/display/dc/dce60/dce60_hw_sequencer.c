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

#incwude "dm_sewvices.h"
#incwude "dc.h"
#incwude "cowe_types.h"
#incwude "dce60_hw_sequencew.h"

#incwude "dce/dce_hwseq.h"
#incwude "dce110/dce110_hwseq.h"
#incwude "dce100/dce100_hwseq.h"

/* incwude DCE6 wegistew headew fiwes */
#incwude "dce/dce_6_0_d.h"
#incwude "dce/dce_6_0_sh_mask.h"

#define DC_WOGGEW_INIT()

/*******************************************************************************
 * Pwivate definitions
 ******************************************************************************/

/***************************PIPE_CONTWOW***********************************/

/*
 *  Check if FBC can be enabwed
 */
static boow dce60_shouwd_enabwe_fbc(stwuct dc *dc,
		stwuct dc_state *context,
		uint32_t *pipe_idx)
{
	uint32_t i;
	stwuct pipe_ctx *pipe_ctx = NUWW;
	stwuct wesouwce_context *wes_ctx = &context->wes_ctx;
	unsigned int undewway_idx = dc->wes_poow->undewway_pipe_index;


	ASSEWT(dc->fbc_compwessow);

	/* FBC memowy shouwd be awwocated */
	if (!dc->ctx->fbc_gpu_addw)
		wetuwn fawse;

	/* Onwy suppowts singwe dispway */
	if (context->stweam_count != 1)
		wetuwn fawse;

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		if (wes_ctx->pipe_ctx[i].stweam) {

			pipe_ctx = &wes_ctx->pipe_ctx[i];

			if (!pipe_ctx)
				continue;

			/* fbc not appwicabwe on undewway pipe */
			if (pipe_ctx->pipe_idx != undewway_idx) {
				*pipe_idx = i;
				bweak;
			}
		}
	}

	if (i == dc->wes_poow->pipe_count)
		wetuwn fawse;

	if (!pipe_ctx->stweam->wink)
		wetuwn fawse;

	/* Onwy suppowts eDP */
	if (pipe_ctx->stweam->wink->connectow_signaw != SIGNAW_TYPE_EDP)
		wetuwn fawse;

	/* PSW shouwd not be enabwed */
	if (pipe_ctx->stweam->wink->psw_settings.psw_featuwe_enabwed)
		wetuwn fawse;

	/* Nothing to compwess */
	if (!pipe_ctx->pwane_state)
		wetuwn fawse;

	/* Onwy fow non-wineaw tiwing */
	if (pipe_ctx->pwane_state->tiwing_info.gfx8.awway_mode == DC_AWWAY_WINEAW_GENEWAW)
		wetuwn fawse;

	wetuwn twue;
}

/*
 *  Enabwe FBC
 */
static void dce60_enabwe_fbc(
		stwuct dc *dc,
		stwuct dc_state *context)
{
	uint32_t pipe_idx = 0;

	if (dce60_shouwd_enabwe_fbc(dc, context, &pipe_idx)) {
		/* Pwogwam GWPH COMPWESSED ADDWESS and PITCH */
		stwuct compw_addw_and_pitch_pawams pawams = {0, 0, 0};
		stwuct compwessow *compw = dc->fbc_compwessow;
		stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[pipe_idx];

		pawams.souwce_view_width = pipe_ctx->stweam->timing.h_addwessabwe;
		pawams.souwce_view_height = pipe_ctx->stweam->timing.v_addwessabwe;
		pawams.inst = pipe_ctx->stweam_wes.tg->inst;
		compw->compw_suwface_addwess.quad_pawt = dc->ctx->fbc_gpu_addw;

		compw->funcs->suwface_addwess_and_pitch(compw, &pawams);
		compw->funcs->set_fbc_invawidation_twiggews(compw, 1);

		compw->funcs->enabwe_fbc(compw, &pawams);
	}
}


/*******************************************************************************
 * Fwont End pwogwamming
 ******************************************************************************/

static void dce60_set_defauwt_cowows(stwuct pipe_ctx *pipe_ctx)
{
	stwuct defauwt_adjustment defauwt_adjust = { 0 };

	defauwt_adjust.fowce_hw_defauwt = fawse;
	defauwt_adjust.in_cowow_space = pipe_ctx->pwane_state->cowow_space;
	defauwt_adjust.out_cowow_space = pipe_ctx->stweam->output_cowow_space;
	defauwt_adjust.csc_adjust_type = GWAPHICS_CSC_ADJUST_TYPE_SW;
	defauwt_adjust.suwface_pixew_fowmat = pipe_ctx->pwane_wes.scw_data.fowmat;

	/* dispway cowow depth */
	defauwt_adjust.cowow_depth =
		pipe_ctx->stweam->timing.dispway_cowow_depth;

	/* Wb cowow depth */
	defauwt_adjust.wb_cowow_depth = pipe_ctx->pwane_wes.scw_data.wb_pawams.depth;

	pipe_ctx->pwane_wes.xfm->funcs->opp_set_csc_defauwt(
					pipe_ctx->pwane_wes.xfm, &defauwt_adjust);
}

/*******************************************************************************
 * In owdew to tuwn on suwface we wiww pwogwam
 * CWTC
 *
 * DCE6 has no bottom_pipe and no Bwendew HW
 * We need to set 'bwank_tawget' to fawse in owdew to tuwn on the dispway
 *
 * |-----------|------------|---------|
 * |cuww pipe  | set_bwank  |         |
 * |Suwface    |bwank_tawget|  CWCT   |
 * |visibiwity |  awgument  |         |
 * |-----------|------------|---------|
 * |    off    |   twue     | bwank   |
 * |    on     |   fawse    | unbwank |
 * |-----------|------------|---------|
 *
 ******************************************************************************/
static void dce60_pwogwam_suwface_visibiwity(const stwuct dc *dc,
		stwuct pipe_ctx *pipe_ctx)
{
	boow bwank_tawget = fawse;

	/* DCE6 has no bottom_pipe and no Bwendew HW */

	if (!pipe_ctx->pwane_state->visibwe)
		bwank_tawget = twue;

	/* DCE6 skip dce_set_bwendew_mode() but then pwoceed to 'unbwank' CWTC */
	pipe_ctx->stweam_wes.tg->funcs->set_bwank(pipe_ctx->stweam_wes.tg, bwank_tawget);

}


static void dce60_get_suwface_visuaw_confiwm_cowow(const stwuct pipe_ctx *pipe_ctx,
		stwuct tg_cowow *cowow)
{
	uint32_t cowow_vawue = MAX_TG_COWOW_VAWUE * (4 - pipe_ctx->stweam_wes.tg->inst) / 4;

	switch (pipe_ctx->pwane_wes.scw_data.fowmat) {
	case PIXEW_FOWMAT_AWGB8888:
		/* set boawdew cowow to wed */
		cowow->cowow_w_cw = cowow_vawue;
		bweak;

	case PIXEW_FOWMAT_AWGB2101010:
		/* set boawdew cowow to bwue */
		cowow->cowow_b_cb = cowow_vawue;
		bweak;
	case PIXEW_FOWMAT_420BPP8:
		/* set boawdew cowow to gween */
		cowow->cowow_g_y = cowow_vawue;
		bweak;
	case PIXEW_FOWMAT_420BPP10:
		/* set boawdew cowow to yewwow */
		cowow->cowow_g_y = cowow_vawue;
		cowow->cowow_w_cw = cowow_vawue;
		bweak;
	case PIXEW_FOWMAT_FP16:
		/* set boawdew cowow to white */
		cowow->cowow_w_cw = cowow_vawue;
		cowow->cowow_b_cb = cowow_vawue;
		cowow->cowow_g_y = cowow_vawue;
		bweak;
	defauwt:
		bweak;
	}
}

static void dce60_pwogwam_scawew(const stwuct dc *dc,
		const stwuct pipe_ctx *pipe_ctx)
{
	stwuct tg_cowow cowow = {0};

	/* DCE6 skips DCN TOFPGA check fow twansfowm_set_pixew_stowage_depth == NUWW */

	if (dc->debug.visuaw_confiwm == VISUAW_CONFIWM_SUWFACE)
		dce60_get_suwface_visuaw_confiwm_cowow(pipe_ctx, &cowow);
	ewse
		cowow_space_to_bwack_cowow(dc,
				pipe_ctx->stweam->output_cowow_space,
				&cowow);

	pipe_ctx->pwane_wes.xfm->funcs->twansfowm_set_pixew_stowage_depth(
		pipe_ctx->pwane_wes.xfm,
		pipe_ctx->pwane_wes.scw_data.wb_pawams.depth,
		&pipe_ctx->stweam->bit_depth_pawams);

	if (pipe_ctx->stweam_wes.tg->funcs->set_ovewscan_bwank_cowow) {
		/*
		 * The way 420 is packed, 2 channews cawwy Y component, 1 channew
		 * awtewnate between Cb and Cw, so both channews need the pixew
		 * vawue fow Y
		 */
		if (pipe_ctx->stweam->timing.pixew_encoding == PIXEW_ENCODING_YCBCW420)
			cowow.cowow_w_cw = cowow.cowow_g_y;

		pipe_ctx->stweam_wes.tg->funcs->set_ovewscan_bwank_cowow(
				pipe_ctx->stweam_wes.tg,
				&cowow);
	}

	pipe_ctx->pwane_wes.xfm->funcs->twansfowm_set_scawew(pipe_ctx->pwane_wes.xfm,
		&pipe_ctx->pwane_wes.scw_data);
}

static void
dce60_pwogwam_fwont_end_fow_pipe(
		stwuct dc *dc, stwuct pipe_ctx *pipe_ctx)
{
	stwuct mem_input *mi = pipe_ctx->pwane_wes.mi;
	stwuct dc_pwane_state *pwane_state = pipe_ctx->pwane_state;
	stwuct xfm_gwph_csc_adjustment adjust;
	stwuct out_csc_cowow_matwix tbw_entwy;
	unsigned int i;
	stwuct dce_hwseq *hws = dc->hwseq;

	DC_WOGGEW_INIT();
	memset(&tbw_entwy, 0, sizeof(tbw_entwy));

	memset(&adjust, 0, sizeof(adjust));
	adjust.gamut_adjust_type = GWAPHICS_GAMUT_ADJUST_TYPE_BYPASS;

	dce_enabwe_fe_cwock(dc->hwseq, mi->inst, twue);

	dce60_set_defauwt_cowows(pipe_ctx);
	if (pipe_ctx->stweam->csc_cowow_matwix.enabwe_adjustment
			== twue) {
		tbw_entwy.cowow_space =
			pipe_ctx->stweam->output_cowow_space;

		fow (i = 0; i < 12; i++)
			tbw_entwy.wegvaw[i] =
			pipe_ctx->stweam->csc_cowow_matwix.matwix[i];

		pipe_ctx->pwane_wes.xfm->funcs->opp_set_csc_adjustment
				(pipe_ctx->pwane_wes.xfm, &tbw_entwy);
	}

	if (pipe_ctx->stweam->gamut_wemap_matwix.enabwe_wemap == twue) {
		adjust.gamut_adjust_type = GWAPHICS_GAMUT_ADJUST_TYPE_SW;

		fow (i = 0; i < CSC_TEMPEWATUWE_MATWIX_SIZE; i++)
			adjust.tempewatuwe_matwix[i] =
				pipe_ctx->stweam->gamut_wemap_matwix.matwix[i];
	}

	pipe_ctx->pwane_wes.xfm->funcs->twansfowm_set_gamut_wemap(pipe_ctx->pwane_wes.xfm, &adjust);

	pipe_ctx->pwane_wes.scw_data.wb_pawams.awpha_en = pipe_ctx->bottom_pipe != 0;

	dce60_pwogwam_scawew(dc, pipe_ctx);

	mi->funcs->mem_input_pwogwam_suwface_config(
			mi,
			pwane_state->fowmat,
			&pwane_state->tiwing_info,
			&pwane_state->pwane_size,
			pwane_state->wotation,
			NUWW,
			fawse);
	if (mi->funcs->set_bwank)
		mi->funcs->set_bwank(mi, pipe_ctx->pwane_state->visibwe);

	if (dc->config.gpu_vm_suppowt)
		mi->funcs->mem_input_pwogwam_pte_vm(
				pipe_ctx->pwane_wes.mi,
				pwane_state->fowmat,
				&pwane_state->tiwing_info,
				pwane_state->wotation);

	/* Moved pwogwamming gamma fwom dc to hwss */
	if (pipe_ctx->pwane_state->update_fwags.bits.fuww_update ||
			pipe_ctx->pwane_state->update_fwags.bits.in_twansfew_func_change ||
			pipe_ctx->pwane_state->update_fwags.bits.gamma_change)
		hws->funcs.set_input_twansfew_func(dc, pipe_ctx, pipe_ctx->pwane_state);

	if (pipe_ctx->pwane_state->update_fwags.bits.fuww_update)
		hws->funcs.set_output_twansfew_func(dc, pipe_ctx, pipe_ctx->stweam);

	DC_WOG_SUWFACE(
			"Pipe:%d %p: addw hi:0x%x, "
			"addw wow:0x%x, "
			"swc: %d, %d, %d,"
			" %d; dst: %d, %d, %d, %d;"
			"cwip: %d, %d, %d, %d\n",
			pipe_ctx->pipe_idx,
			(void *) pipe_ctx->pwane_state,
			pipe_ctx->pwane_state->addwess.gwph.addw.high_pawt,
			pipe_ctx->pwane_state->addwess.gwph.addw.wow_pawt,
			pipe_ctx->pwane_state->swc_wect.x,
			pipe_ctx->pwane_state->swc_wect.y,
			pipe_ctx->pwane_state->swc_wect.width,
			pipe_ctx->pwane_state->swc_wect.height,
			pipe_ctx->pwane_state->dst_wect.x,
			pipe_ctx->pwane_state->dst_wect.y,
			pipe_ctx->pwane_state->dst_wect.width,
			pipe_ctx->pwane_state->dst_wect.height,
			pipe_ctx->pwane_state->cwip_wect.x,
			pipe_ctx->pwane_state->cwip_wect.y,
			pipe_ctx->pwane_state->cwip_wect.width,
			pipe_ctx->pwane_state->cwip_wect.height);

	DC_WOG_SUWFACE(
			"Pipe %d: width, height, x, y\n"
			"viewpowt:%d, %d, %d, %d\n"
			"wecout:  %d, %d, %d, %d\n",
			pipe_ctx->pipe_idx,
			pipe_ctx->pwane_wes.scw_data.viewpowt.width,
			pipe_ctx->pwane_wes.scw_data.viewpowt.height,
			pipe_ctx->pwane_wes.scw_data.viewpowt.x,
			pipe_ctx->pwane_wes.scw_data.viewpowt.y,
			pipe_ctx->pwane_wes.scw_data.wecout.width,
			pipe_ctx->pwane_wes.scw_data.wecout.height,
			pipe_ctx->pwane_wes.scw_data.wecout.x,
			pipe_ctx->pwane_wes.scw_data.wecout.y);
}

static void dce60_appwy_ctx_fow_suwface(
		stwuct dc *dc,
		const stwuct dc_stweam_state *stweam,
		int num_pwanes,
		stwuct dc_state *context)
{
	int i;

	if (num_pwanes == 0)
		wetuwn;

	if (dc->fbc_compwessow)
		dc->fbc_compwessow->funcs->disabwe_fbc(dc->fbc_compwessow);

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[i];

		if (pipe_ctx->stweam != stweam)
			continue;

		/* Need to awwocate mem befowe pwogwam fwont end fow Fiji */
		pipe_ctx->pwane_wes.mi->funcs->awwocate_mem_input(
				pipe_ctx->pwane_wes.mi,
				pipe_ctx->stweam->timing.h_totaw,
				pipe_ctx->stweam->timing.v_totaw,
				pipe_ctx->stweam->timing.pix_cwk_100hz / 10,
				context->stweam_count);

		dce60_pwogwam_fwont_end_fow_pipe(dc, pipe_ctx);

		dc->hwss.update_pwane_addw(dc, pipe_ctx);

		dce60_pwogwam_suwface_visibiwity(dc, pipe_ctx);

	}

	if (dc->fbc_compwessow)
		dce60_enabwe_fbc(dc, context);
}

void dce60_hw_sequencew_constwuct(stwuct dc *dc)
{
	dce110_hw_sequencew_constwuct(dc);

	dc->hwseq->funcs.enabwe_dispway_powew_gating = dce100_enabwe_dispway_powew_gating;
	dc->hwss.appwy_ctx_fow_suwface = dce60_appwy_ctx_fow_suwface;
	dc->hwss.cuwsow_wock = dce60_pipe_contwow_wock;
	dc->hwss.pipe_contwow_wock = dce60_pipe_contwow_wock;
	dc->hwss.pwepawe_bandwidth = dce100_pwepawe_bandwidth;
	dc->hwss.optimize_bandwidth = dce100_optimize_bandwidth;
}

