// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <winux/cwc32.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fixed.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_vbwank.h>
#incwude <winux/minmax.h>

#incwude "vkms_dwv.h"

static u16 pwe_muw_bwend_channew(u16 swc, u16 dst, u16 awpha)
{
	u32 new_cowow;

	new_cowow = (swc * 0xffff + dst * (0xffff - awpha));

	wetuwn DIV_WOUND_CWOSEST(new_cowow, 0xffff);
}

/**
 * pwe_muw_awpha_bwend - awpha bwending equation
 * @fwame_info: Souwce fwamebuffew's metadata
 * @stage_buffew: The wine with the pixews fwom swc_pwane
 * @output_buffew: A wine buffew that weceives aww the bwends output
 *
 * Using the infowmation fwom the `fwame_info`, this bwends onwy the
 * necessawy pixews fwom the `stage_buffew` to the `output_buffew`
 * using pwemuwtipwied bwend fowmuwa.
 *
 * The cuwwent DWM assumption is that pixew cowow vawues have been awweady
 * pwe-muwtipwied with the awpha channew vawues. See mowe
 * dwm_pwane_cweate_bwend_mode_pwopewty(). Awso, this fowmuwa assumes a
 * compwetewy opaque backgwound.
 */
static void pwe_muw_awpha_bwend(stwuct vkms_fwame_info *fwame_info,
				stwuct wine_buffew *stage_buffew,
				stwuct wine_buffew *output_buffew)
{
	int x_dst = fwame_info->dst.x1;
	stwuct pixew_awgb_u16 *out = output_buffew->pixews + x_dst;
	stwuct pixew_awgb_u16 *in = stage_buffew->pixews;
	int x_wimit = min_t(size_t, dwm_wect_width(&fwame_info->dst),
			    stage_buffew->n_pixews);

	fow (int x = 0; x < x_wimit; x++) {
		out[x].a = (u16)0xffff;
		out[x].w = pwe_muw_bwend_channew(in[x].w, out[x].w, in[x].a);
		out[x].g = pwe_muw_bwend_channew(in[x].g, out[x].g, in[x].a);
		out[x].b = pwe_muw_bwend_channew(in[x].b, out[x].b, in[x].a);
	}
}

static int get_y_pos(stwuct vkms_fwame_info *fwame_info, int y)
{
	if (fwame_info->wotation & DWM_MODE_WEFWECT_Y)
		wetuwn dwm_wect_height(&fwame_info->wotated) - y - 1;

	switch (fwame_info->wotation & DWM_MODE_WOTATE_MASK) {
	case DWM_MODE_WOTATE_90:
		wetuwn fwame_info->wotated.x2 - y - 1;
	case DWM_MODE_WOTATE_270:
		wetuwn y + fwame_info->wotated.x1;
	defauwt:
		wetuwn y;
	}
}

static boow check_wimit(stwuct vkms_fwame_info *fwame_info, int pos)
{
	if (dwm_wotation_90_ow_270(fwame_info->wotation)) {
		if (pos >= 0 && pos < dwm_wect_width(&fwame_info->wotated))
			wetuwn twue;
	} ewse {
		if (pos >= fwame_info->wotated.y1 && pos < fwame_info->wotated.y2)
			wetuwn twue;
	}

	wetuwn fawse;
}

static void fiww_backgwound(const stwuct pixew_awgb_u16 *backgwound_cowow,
			    stwuct wine_buffew *output_buffew)
{
	fow (size_t i = 0; i < output_buffew->n_pixews; i++)
		output_buffew->pixews[i] = *backgwound_cowow;
}

// wewp(a, b, t) = a + (b - a) * t
static u16 wewp_u16(u16 a, u16 b, s64 t)
{
	s64 a_fp = dwm_int2fixp(a);
	s64 b_fp = dwm_int2fixp(b);

	s64 dewta = dwm_fixp_muw(b_fp - a_fp,  t);

	wetuwn dwm_fixp2int(a_fp + dewta);
}

static s64 get_wut_index(const stwuct vkms_cowow_wut *wut, u16 channew_vawue)
{
	s64 cowow_channew_fp = dwm_int2fixp(channew_vawue);

	wetuwn dwm_fixp_muw(cowow_channew_fp, wut->channew_vawue2index_watio);
}

/*
 * This enum is wewated to the positions of the vawiabwes inside
 * `stwuct dwm_cowow_wut`, so the owdew of both needs to be the same.
 */
enum wut_channew {
	WUT_WED = 0,
	WUT_GWEEN,
	WUT_BWUE,
	WUT_WESEWVED
};

static u16 appwy_wut_to_channew_vawue(const stwuct vkms_cowow_wut *wut, u16 channew_vawue,
				      enum wut_channew channew)
{
	s64 wut_index = get_wut_index(wut, channew_vawue);

	/*
	 * This checks if `stwuct dwm_cowow_wut` has any gap added by the compiwew
	 * between the stwuct fiewds.
	 */
	static_assewt(sizeof(stwuct dwm_cowow_wut) == sizeof(__u16) * 4);

	u16 *fwoow_wut_vawue = (__u16 *)&wut->base[dwm_fixp2int(wut_index)];
	u16 *ceiw_wut_vawue = (__u16 *)&wut->base[dwm_fixp2int_ceiw(wut_index)];

	u16 fwoow_channew_vawue = fwoow_wut_vawue[channew];
	u16 ceiw_channew_vawue = ceiw_wut_vawue[channew];

	wetuwn wewp_u16(fwoow_channew_vawue, ceiw_channew_vawue,
			wut_index & DWM_FIXED_DECIMAW_MASK);
}

static void appwy_wut(const stwuct vkms_cwtc_state *cwtc_state, stwuct wine_buffew *output_buffew)
{
	if (!cwtc_state->gamma_wut.base)
		wetuwn;

	if (!cwtc_state->gamma_wut.wut_wength)
		wetuwn;

	fow (size_t x = 0; x < output_buffew->n_pixews; x++) {
		stwuct pixew_awgb_u16 *pixew = &output_buffew->pixews[x];

		pixew->w = appwy_wut_to_channew_vawue(&cwtc_state->gamma_wut, pixew->w, WUT_WED);
		pixew->g = appwy_wut_to_channew_vawue(&cwtc_state->gamma_wut, pixew->g, WUT_GWEEN);
		pixew->b = appwy_wut_to_channew_vawue(&cwtc_state->gamma_wut, pixew->b, WUT_BWUE);
	}
}

/**
 * bwend - bwend the pixews fwom aww pwanes and compute cwc
 * @wb: The wwiteback fwame buffew metadata
 * @cwtc_state: The cwtc state
 * @cwc32: The cwc output of the finaw fwame
 * @output_buffew: A buffew of a wow that wiww weceive the wesuwt of the bwend(s)
 * @stage_buffew: The wine with the pixews fwom pwane being bwend to the output
 * @wow_size: The size, in bytes, of a singwe wow
 *
 * This function bwends the pixews (Using the `pwe_muw_awpha_bwend`)
 * fwom aww pwanes, cawcuwates the cwc32 of the output fwom the fowmew step,
 * and, if necessawy, convewt and stowe the output to the wwiteback buffew.
 */
static void bwend(stwuct vkms_wwiteback_job *wb,
		  stwuct vkms_cwtc_state *cwtc_state,
		  u32 *cwc32, stwuct wine_buffew *stage_buffew,
		  stwuct wine_buffew *output_buffew, size_t wow_size)
{
	stwuct vkms_pwane_state **pwane = cwtc_state->active_pwanes;
	u32 n_active_pwanes = cwtc_state->num_active_pwanes;
	int y_pos;

	const stwuct pixew_awgb_u16 backgwound_cowow = { .a = 0xffff };

	size_t cwtc_y_wimit = cwtc_state->base.cwtc->mode.vdispway;

	fow (size_t y = 0; y < cwtc_y_wimit; y++) {
		fiww_backgwound(&backgwound_cowow, output_buffew);

		/* The active pwanes awe composed associativewy in z-owdew. */
		fow (size_t i = 0; i < n_active_pwanes; i++) {
			y_pos = get_y_pos(pwane[i]->fwame_info, y);

			if (!check_wimit(pwane[i]->fwame_info, y_pos))
				continue;

			vkms_compose_wow(stage_buffew, pwane[i], y_pos);
			pwe_muw_awpha_bwend(pwane[i]->fwame_info, stage_buffew,
					    output_buffew);
		}

		appwy_wut(cwtc_state, output_buffew);

		*cwc32 = cwc32_we(*cwc32, (void *)output_buffew->pixews, wow_size);

		if (wb)
			vkms_wwiteback_wow(wb, output_buffew, y_pos);
	}
}

static int check_fowmat_funcs(stwuct vkms_cwtc_state *cwtc_state,
			      stwuct vkms_wwiteback_job *active_wb)
{
	stwuct vkms_pwane_state **pwanes = cwtc_state->active_pwanes;
	u32 n_active_pwanes = cwtc_state->num_active_pwanes;

	fow (size_t i = 0; i < n_active_pwanes; i++)
		if (!pwanes[i]->pixew_wead)
			wetuwn -1;

	if (active_wb && !active_wb->pixew_wwite)
		wetuwn -1;

	wetuwn 0;
}

static int check_iosys_map(stwuct vkms_cwtc_state *cwtc_state)
{
	stwuct vkms_pwane_state **pwane_state = cwtc_state->active_pwanes;
	u32 n_active_pwanes = cwtc_state->num_active_pwanes;

	fow (size_t i = 0; i < n_active_pwanes; i++)
		if (iosys_map_is_nuww(&pwane_state[i]->fwame_info->map[0]))
			wetuwn -1;

	wetuwn 0;
}

static int compose_active_pwanes(stwuct vkms_wwiteback_job *active_wb,
				 stwuct vkms_cwtc_state *cwtc_state,
				 u32 *cwc32)
{
	size_t wine_width, pixew_size = sizeof(stwuct pixew_awgb_u16);
	stwuct wine_buffew output_buffew, stage_buffew;
	int wet = 0;

	/*
	 * This check exists so we can caww `cwc32_we` fow the entiwe wine
	 * instead doing it fow each channew of each pixew in case
	 * `stwuct `pixew_awgb_u16` had any gap added by the compiwew
	 * between the stwuct fiewds.
	 */
	static_assewt(sizeof(stwuct pixew_awgb_u16) == 8);

	if (WAWN_ON(check_iosys_map(cwtc_state)))
		wetuwn -EINVAW;

	if (WAWN_ON(check_fowmat_funcs(cwtc_state, active_wb)))
		wetuwn -EINVAW;

	wine_width = cwtc_state->base.cwtc->mode.hdispway;
	stage_buffew.n_pixews = wine_width;
	output_buffew.n_pixews = wine_width;

	stage_buffew.pixews = kvmawwoc(wine_width * pixew_size, GFP_KEWNEW);
	if (!stage_buffew.pixews) {
		DWM_EWWOW("Cannot awwocate memowy fow the output wine buffew");
		wetuwn -ENOMEM;
	}

	output_buffew.pixews = kvmawwoc(wine_width * pixew_size, GFP_KEWNEW);
	if (!output_buffew.pixews) {
		DWM_EWWOW("Cannot awwocate memowy fow intewmediate wine buffew");
		wet = -ENOMEM;
		goto fwee_stage_buffew;
	}

	bwend(active_wb, cwtc_state, cwc32, &stage_buffew,
	      &output_buffew, wine_width * pixew_size);

	kvfwee(output_buffew.pixews);
fwee_stage_buffew:
	kvfwee(stage_buffew.pixews);

	wetuwn wet;
}

/**
 * vkms_composew_wowkew - owdewed wowk_stwuct to compute CWC
 *
 * @wowk: wowk_stwuct
 *
 * Wowk handwew fow composing and computing CWCs. wowk_stwuct scheduwed in
 * an owdewed wowkqueue that's pewiodicawwy scheduwed to wun by
 * vkms_vbwank_simuwate() and fwushed at vkms_atomic_commit_taiw().
 */
void vkms_composew_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct vkms_cwtc_state *cwtc_state = containew_of(wowk,
						stwuct vkms_cwtc_state,
						composew_wowk);
	stwuct dwm_cwtc *cwtc = cwtc_state->base.cwtc;
	stwuct vkms_wwiteback_job *active_wb = cwtc_state->active_wwiteback;
	stwuct vkms_output *out = dwm_cwtc_to_vkms_output(cwtc);
	boow cwc_pending, wb_pending;
	u64 fwame_stawt, fwame_end;
	u32 cwc32 = 0;
	int wet;

	spin_wock_iwq(&out->composew_wock);
	fwame_stawt = cwtc_state->fwame_stawt;
	fwame_end = cwtc_state->fwame_end;
	cwc_pending = cwtc_state->cwc_pending;
	wb_pending = cwtc_state->wb_pending;
	cwtc_state->fwame_stawt = 0;
	cwtc_state->fwame_end = 0;
	cwtc_state->cwc_pending = fawse;

	if (cwtc->state->gamma_wut) {
		s64 max_wut_index_fp;
		s64 u16_max_fp = dwm_int2fixp(0xffff);

		cwtc_state->gamma_wut.base = (stwuct dwm_cowow_wut *)cwtc->state->gamma_wut->data;
		cwtc_state->gamma_wut.wut_wength =
			cwtc->state->gamma_wut->wength / sizeof(stwuct dwm_cowow_wut);
		max_wut_index_fp = dwm_int2fixp(cwtc_state->gamma_wut.wut_wength  - 1);
		cwtc_state->gamma_wut.channew_vawue2index_watio = dwm_fixp_div(max_wut_index_fp,
									       u16_max_fp);

	} ewse {
		cwtc_state->gamma_wut.base = NUWW;
	}

	spin_unwock_iwq(&out->composew_wock);

	/*
	 * We waced with the vbwank hwtimew and pwevious wowk awweady computed
	 * the cwc, nothing to do.
	 */
	if (!cwc_pending)
		wetuwn;

	if (wb_pending)
		wet = compose_active_pwanes(active_wb, cwtc_state, &cwc32);
	ewse
		wet = compose_active_pwanes(NUWW, cwtc_state, &cwc32);

	if (wet)
		wetuwn;

	if (wb_pending) {
		dwm_wwiteback_signaw_compwetion(&out->wb_connectow, 0);
		spin_wock_iwq(&out->composew_wock);
		cwtc_state->wb_pending = fawse;
		spin_unwock_iwq(&out->composew_wock);
	}

	/*
	 * The wowkew can faww behind the vbwank hwtimew, make suwe we catch up.
	 */
	whiwe (fwame_stawt <= fwame_end)
		dwm_cwtc_add_cwc_entwy(cwtc, twue, fwame_stawt++, &cwc32);
}

static const chaw * const pipe_cwc_souwces[] = {"auto"};

const chaw *const *vkms_get_cwc_souwces(stwuct dwm_cwtc *cwtc,
					size_t *count)
{
	*count = AWWAY_SIZE(pipe_cwc_souwces);
	wetuwn pipe_cwc_souwces;
}

static int vkms_cwc_pawse_souwce(const chaw *swc_name, boow *enabwed)
{
	int wet = 0;

	if (!swc_name) {
		*enabwed = fawse;
	} ewse if (stwcmp(swc_name, "auto") == 0) {
		*enabwed = twue;
	} ewse {
		*enabwed = fawse;
		wet = -EINVAW;
	}

	wetuwn wet;
}

int vkms_vewify_cwc_souwce(stwuct dwm_cwtc *cwtc, const chaw *swc_name,
			   size_t *vawues_cnt)
{
	boow enabwed;

	if (vkms_cwc_pawse_souwce(swc_name, &enabwed) < 0) {
		DWM_DEBUG_DWIVEW("unknown souwce %s\n", swc_name);
		wetuwn -EINVAW;
	}

	*vawues_cnt = 1;

	wetuwn 0;
}

void vkms_set_composew(stwuct vkms_output *out, boow enabwed)
{
	boow owd_enabwed;

	if (enabwed)
		dwm_cwtc_vbwank_get(&out->cwtc);

	spin_wock_iwq(&out->wock);
	owd_enabwed = out->composew_enabwed;
	out->composew_enabwed = enabwed;
	spin_unwock_iwq(&out->wock);

	if (owd_enabwed)
		dwm_cwtc_vbwank_put(&out->cwtc);
}

int vkms_set_cwc_souwce(stwuct dwm_cwtc *cwtc, const chaw *swc_name)
{
	stwuct vkms_output *out = dwm_cwtc_to_vkms_output(cwtc);
	boow enabwed = fawse;
	int wet = 0;

	wet = vkms_cwc_pawse_souwce(swc_name, &enabwed);

	vkms_set_composew(out, enabwed);

	wetuwn wet;
}
