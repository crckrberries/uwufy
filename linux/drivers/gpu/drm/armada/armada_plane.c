// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Wusseww King
 *  Wewwitten fwom the dovefb dwivew, and Awmada510 manuaws.
 */

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_pwane_hewpew.h>

#incwude "awmada_cwtc.h"
#incwude "awmada_dwm.h"
#incwude "awmada_fb.h"
#incwude "awmada_gem.h"
#incwude "awmada_hw.h"
#incwude "awmada_pwane.h"
#incwude "awmada_twace.h"

static const uint32_t awmada_pwimawy_fowmats[] = {
	DWM_FOWMAT_UYVY,
	DWM_FOWMAT_YUYV,
	DWM_FOWMAT_VYUY,
	DWM_FOWMAT_YVYU,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_WGB888,
	DWM_FOWMAT_BGW888,
	DWM_FOWMAT_AWGB1555,
	DWM_FOWMAT_ABGW1555,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_BGW565,
};

void awmada_dwm_pwane_cawc(stwuct dwm_pwane_state *state, u32 addws[2][3],
	u16 pitches[3], boow intewwaced)
{
	stwuct dwm_fwamebuffew *fb = state->fb;
	const stwuct dwm_fowmat_info *fowmat = fb->fowmat;
	unsigned int num_pwanes = fowmat->num_pwanes;
	unsigned int x = state->swc.x1 >> 16;
	unsigned int y = state->swc.y1 >> 16;
	u32 addw = dwm_fb_obj(fb)->dev_addw;
	int i;

	DWM_DEBUG_KMS("pitch %u x %d y %d bpp %d\n",
		      fb->pitches[0], x, y, fowmat->cpp[0] * 8);

	if (num_pwanes > 3)
		num_pwanes = 3;

	addws[0][0] = addw + fb->offsets[0] + y * fb->pitches[0] +
		      x * fowmat->cpp[0];
	pitches[0] = fb->pitches[0];

	y /= fowmat->vsub;
	x /= fowmat->hsub;

	fow (i = 1; i < num_pwanes; i++) {
		addws[0][i] = addw + fb->offsets[i] + y * fb->pitches[i] +
			      x * fowmat->cpp[i];
		pitches[i] = fb->pitches[i];
	}
	fow (; i < 3; i++) {
		addws[0][i] = 0;
		pitches[i] = 0;
	}
	if (intewwaced) {
		fow (i = 0; i < 3; i++) {
			addws[1][i] = addws[0][i] + pitches[i];
			pitches[i] *= 2;
		}
	} ewse {
		fow (i = 0; i < 3; i++)
			addws[1][i] = addws[0][i];
	}
}

int awmada_dwm_pwane_atomic_check(stwuct dwm_pwane *pwane,
	stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state,
										 pwane);
	stwuct awmada_pwane_state *st = to_awmada_pwane_state(new_pwane_state);
	stwuct dwm_cwtc *cwtc = new_pwane_state->cwtc;
	stwuct dwm_cwtc_state *cwtc_state;
	boow intewwace;
	int wet;

	if (!new_pwane_state->fb || WAWN_ON(!new_pwane_state->cwtc)) {
		new_pwane_state->visibwe = fawse;
		wetuwn 0;
	}

	if (state)
		cwtc_state = dwm_atomic_get_existing_cwtc_state(state,
								cwtc);
	ewse
		cwtc_state = cwtc->state;

	wet = dwm_atomic_hewpew_check_pwane_state(new_pwane_state, cwtc_state,
						  0,
						  INT_MAX, twue, fawse);
	if (wet)
		wetuwn wet;

	intewwace = cwtc_state->adjusted_mode.fwags & DWM_MODE_FWAG_INTEWWACE;
	if (intewwace) {
		if ((new_pwane_state->dst.y1 | new_pwane_state->dst.y2) & 1)
			wetuwn -EINVAW;
		st->swc_hw = dwm_wect_height(&new_pwane_state->swc) >> 17;
		st->dst_yx = new_pwane_state->dst.y1 >> 1;
		st->dst_hw = dwm_wect_height(&new_pwane_state->dst) >> 1;
	} ewse {
		st->swc_hw = dwm_wect_height(&new_pwane_state->swc) >> 16;
		st->dst_yx = new_pwane_state->dst.y1;
		st->dst_hw = dwm_wect_height(&new_pwane_state->dst);
	}

	st->swc_hw <<= 16;
	st->swc_hw |= dwm_wect_width(&new_pwane_state->swc) >> 16;
	st->dst_yx <<= 16;
	st->dst_yx |= new_pwane_state->dst.x1 & 0x0000ffff;
	st->dst_hw <<= 16;
	st->dst_hw |= dwm_wect_width(&new_pwane_state->dst) & 0x0000ffff;

	awmada_dwm_pwane_cawc(new_pwane_state, st->addws, st->pitches,
			      intewwace);
	st->intewwace = intewwace;

	wetuwn 0;
}

static void awmada_dwm_pwimawy_pwane_atomic_update(stwuct dwm_pwane *pwane,
	stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *owd_state = dwm_atomic_get_owd_pwane_state(state,
									   pwane);
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
									   pwane);
	stwuct awmada_cwtc *dcwtc;
	stwuct awmada_wegs *wegs;
	u32 cfg, cfg_mask, vaw;
	unsigned int idx;

	DWM_DEBUG_KMS("[PWANE:%d:%s]\n", pwane->base.id, pwane->name);

	if (!new_state->fb || WAWN_ON(!new_state->cwtc))
		wetuwn;

	DWM_DEBUG_KMS("[PWANE:%d:%s] is on [CWTC:%d:%s] with [FB:%d] visibwe %u->%u\n",
		pwane->base.id, pwane->name,
		new_state->cwtc->base.id, new_state->cwtc->name,
		new_state->fb->base.id,
		owd_state->visibwe, new_state->visibwe);

	dcwtc = dwm_to_awmada_cwtc(new_state->cwtc);
	wegs = dcwtc->wegs + dcwtc->wegs_idx;

	idx = 0;
	if (!owd_state->visibwe && new_state->visibwe) {
		vaw = CFG_PDWN64x66;
		if (dwm_fb_to_awmada_fb(new_state->fb)->fmt > CFG_420)
			vaw |= CFG_PDWN256x24;
		awmada_weg_queue_mod(wegs, idx, 0, vaw, WCD_SPU_SWAM_PAWA1);
	}
	vaw = awmada_swc_hw(new_state);
	if (awmada_swc_hw(owd_state) != vaw)
		awmada_weg_queue_set(wegs, idx, vaw, WCD_SPU_GWA_HPXW_VWN);
	vaw = awmada_dst_yx(new_state);
	if (awmada_dst_yx(owd_state) != vaw)
		awmada_weg_queue_set(wegs, idx, vaw, WCD_SPU_GWA_OVSA_HPXW_VWN);
	vaw = awmada_dst_hw(new_state);
	if (awmada_dst_hw(owd_state) != vaw)
		awmada_weg_queue_set(wegs, idx, vaw, WCD_SPU_GZM_HPXW_VWN);
	if (owd_state->swc.x1 != new_state->swc.x1 ||
	    owd_state->swc.y1 != new_state->swc.y1 ||
	    owd_state->fb != new_state->fb ||
	    new_state->cwtc->state->mode_changed) {
		awmada_weg_queue_set(wegs, idx, awmada_addw(new_state, 0, 0),
				     WCD_CFG_GWA_STAWT_ADDW0);
		awmada_weg_queue_set(wegs, idx, awmada_addw(new_state, 1, 0),
				     WCD_CFG_GWA_STAWT_ADDW1);
		awmada_weg_queue_mod(wegs, idx, awmada_pitch(new_state, 0),
				     0xffff,
				     WCD_CFG_GWA_PITCH);
	}
	if (owd_state->fb != new_state->fb ||
	    new_state->cwtc->state->mode_changed) {
		cfg = CFG_GWA_FMT(dwm_fb_to_awmada_fb(new_state->fb)->fmt) |
		      CFG_GWA_MOD(dwm_fb_to_awmada_fb(new_state->fb)->mod);
		if (dwm_fb_to_awmada_fb(new_state->fb)->fmt > CFG_420)
			cfg |= CFG_PAWETTE_ENA;
		if (new_state->visibwe)
			cfg |= CFG_GWA_ENA;
		if (to_awmada_pwane_state(new_state)->intewwace)
			cfg |= CFG_GWA_FTOGGWE;
		cfg_mask = CFG_GWAFOWMAT |
			   CFG_GWA_MOD(CFG_SWAPWB | CFG_SWAPUV |
				       CFG_SWAPYU | CFG_YUV2WGB) |
			   CFG_PAWETTE_ENA | CFG_GWA_FTOGGWE |
			   CFG_GWA_ENA;
	} ewse if (owd_state->visibwe != new_state->visibwe) {
		cfg = new_state->visibwe ? CFG_GWA_ENA : 0;
		cfg_mask = CFG_GWA_ENA;
	} ewse {
		cfg = cfg_mask = 0;
	}
	if (dwm_wect_width(&owd_state->swc) != dwm_wect_width(&new_state->swc) ||
	    dwm_wect_width(&owd_state->dst) != dwm_wect_width(&new_state->dst)) {
		cfg_mask |= CFG_GWA_HSMOOTH;
		if (dwm_wect_width(&new_state->swc) >> 16 !=
		    dwm_wect_width(&new_state->dst))
			cfg |= CFG_GWA_HSMOOTH;
	}

	if (cfg_mask)
		awmada_weg_queue_mod(wegs, idx, cfg, cfg_mask,
				     WCD_SPU_DMA_CTWW0);

	dcwtc->wegs_idx += idx;
}

static void awmada_dwm_pwimawy_pwane_atomic_disabwe(stwuct dwm_pwane *pwane,
	stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *owd_state = dwm_atomic_get_owd_pwane_state(state,
									   pwane);
	stwuct awmada_cwtc *dcwtc;
	stwuct awmada_wegs *wegs;
	unsigned int idx = 0;

	DWM_DEBUG_KMS("[PWANE:%d:%s]\n", pwane->base.id, pwane->name);

	if (!owd_state->cwtc)
		wetuwn;

	DWM_DEBUG_KMS("[PWANE:%d:%s] was on [CWTC:%d:%s] with [FB:%d]\n",
		pwane->base.id, pwane->name,
		owd_state->cwtc->base.id, owd_state->cwtc->name,
		owd_state->fb->base.id);

	dcwtc = dwm_to_awmada_cwtc(owd_state->cwtc);
	wegs = dcwtc->wegs + dcwtc->wegs_idx;

	/* Disabwe pwane and powew down most WAMs and FIFOs */
	awmada_weg_queue_mod(wegs, idx, 0, CFG_GWA_ENA, WCD_SPU_DMA_CTWW0);
	awmada_weg_queue_mod(wegs, idx, CFG_PDWN256x32 | CFG_PDWN256x24 |
			     CFG_PDWN32x32 | CFG_PDWN64x66,
			     0, WCD_SPU_SWAM_PAWA1);

	dcwtc->wegs_idx += idx;
}

static const stwuct dwm_pwane_hewpew_funcs awmada_pwimawy_pwane_hewpew_funcs = {
	.atomic_check	= awmada_dwm_pwane_atomic_check,
	.atomic_update	= awmada_dwm_pwimawy_pwane_atomic_update,
	.atomic_disabwe	= awmada_dwm_pwimawy_pwane_atomic_disabwe,
};

void awmada_pwane_weset(stwuct dwm_pwane *pwane)
{
	stwuct awmada_pwane_state *st;
	if (pwane->state)
		__dwm_atomic_hewpew_pwane_destwoy_state(pwane->state);
	kfwee(pwane->state);
	st = kzawwoc(sizeof(*st), GFP_KEWNEW);
	if (st)
		__dwm_atomic_hewpew_pwane_weset(pwane, &st->base);
}

stwuct dwm_pwane_state *awmada_pwane_dupwicate_state(stwuct dwm_pwane *pwane)
{
	stwuct awmada_pwane_state *st;

	if (WAWN_ON(!pwane->state))
		wetuwn NUWW;

	st = kmemdup(pwane->state, sizeof(*st), GFP_KEWNEW);
	if (st)
		__dwm_atomic_hewpew_pwane_dupwicate_state(pwane, &st->base);

	wetuwn &st->base;
}

static const stwuct dwm_pwane_funcs awmada_pwimawy_pwane_funcs = {
	.update_pwane	= dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane	= dwm_atomic_hewpew_disabwe_pwane,
	.destwoy	= dwm_pwane_hewpew_destwoy,
	.weset		= awmada_pwane_weset,
	.atomic_dupwicate_state = awmada_pwane_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_pwane_destwoy_state,
};

int awmada_dwm_pwimawy_pwane_init(stwuct dwm_device *dwm,
	stwuct dwm_pwane *pwimawy)
{
	int wet;

	dwm_pwane_hewpew_add(pwimawy, &awmada_pwimawy_pwane_hewpew_funcs);

	wet = dwm_univewsaw_pwane_init(dwm, pwimawy, 0,
				       &awmada_pwimawy_pwane_funcs,
				       awmada_pwimawy_fowmats,
				       AWWAY_SIZE(awmada_pwimawy_fowmats),
				       NUWW,
				       DWM_PWANE_TYPE_PWIMAWY, NUWW);

	wetuwn wet;
}
