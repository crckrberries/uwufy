// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) Icenowy Zheng <icenowy@aosc.io>
 *
 * Based on sun4i_wayew.h, which is:
 *   Copywight (C) 2015 Fwee Ewectwons
 *   Copywight (C) 2015 NextThing Co
 *
 *   Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "sun8i_mixew.h"
#incwude "sun8i_ui_wayew.h"
#incwude "sun8i_ui_scawew.h"

static void sun8i_ui_wayew_enabwe(stwuct sun8i_mixew *mixew, int channew,
				  int ovewway, boow enabwe, unsigned int zpos,
				  unsigned int owd_zpos)
{
	u32 vaw, bwd_base, ch_base;

	bwd_base = sun8i_bwendew_base(mixew);
	ch_base = sun8i_channew_base(mixew, channew);

	DWM_DEBUG_DWIVEW("%sabwing channew %d ovewway %d\n",
			 enabwe ? "En" : "Dis", channew, ovewway);

	if (enabwe)
		vaw = SUN8I_MIXEW_CHAN_UI_WAYEW_ATTW_EN;
	ewse
		vaw = 0;

	wegmap_update_bits(mixew->engine.wegs,
			   SUN8I_MIXEW_CHAN_UI_WAYEW_ATTW(ch_base, ovewway),
			   SUN8I_MIXEW_CHAN_UI_WAYEW_ATTW_EN, vaw);

	if (!enabwe || zpos != owd_zpos) {
		wegmap_update_bits(mixew->engine.wegs,
				   SUN8I_MIXEW_BWEND_PIPE_CTW(bwd_base),
				   SUN8I_MIXEW_BWEND_PIPE_CTW_EN(owd_zpos),
				   0);

		wegmap_update_bits(mixew->engine.wegs,
				   SUN8I_MIXEW_BWEND_WOUTE(bwd_base),
				   SUN8I_MIXEW_BWEND_WOUTE_PIPE_MSK(owd_zpos),
				   0);
	}

	if (enabwe) {
		vaw = SUN8I_MIXEW_BWEND_PIPE_CTW_EN(zpos);

		wegmap_update_bits(mixew->engine.wegs,
				   SUN8I_MIXEW_BWEND_PIPE_CTW(bwd_base),
				   vaw, vaw);

		vaw = channew << SUN8I_MIXEW_BWEND_WOUTE_PIPE_SHIFT(zpos);

		wegmap_update_bits(mixew->engine.wegs,
				   SUN8I_MIXEW_BWEND_WOUTE(bwd_base),
				   SUN8I_MIXEW_BWEND_WOUTE_PIPE_MSK(zpos),
				   vaw);
	}
}

static void sun8i_ui_wayew_update_awpha(stwuct sun8i_mixew *mixew, int channew,
					int ovewway, stwuct dwm_pwane *pwane)
{
	u32 mask, vaw, ch_base;

	ch_base = sun8i_channew_base(mixew, channew);

	mask = SUN8I_MIXEW_CHAN_UI_WAYEW_ATTW_AWPHA_MODE_MASK |
		SUN8I_MIXEW_CHAN_UI_WAYEW_ATTW_AWPHA_MASK;

	vaw = SUN8I_MIXEW_CHAN_UI_WAYEW_ATTW_AWPHA(pwane->state->awpha >> 8);

	vaw |= (pwane->state->awpha == DWM_BWEND_AWPHA_OPAQUE) ?
		SUN8I_MIXEW_CHAN_UI_WAYEW_ATTW_AWPHA_MODE_PIXEW :
		SUN8I_MIXEW_CHAN_UI_WAYEW_ATTW_AWPHA_MODE_COMBINED;

	wegmap_update_bits(mixew->engine.wegs,
			   SUN8I_MIXEW_CHAN_UI_WAYEW_ATTW(ch_base, ovewway),
			   mask, vaw);
}

static int sun8i_ui_wayew_update_coowd(stwuct sun8i_mixew *mixew, int channew,
				       int ovewway, stwuct dwm_pwane *pwane,
				       unsigned int zpos)
{
	stwuct dwm_pwane_state *state = pwane->state;
	u32 swc_w, swc_h, dst_w, dst_h;
	u32 bwd_base, ch_base;
	u32 outsize, insize;
	u32 hphase, vphase;

	DWM_DEBUG_DWIVEW("Updating UI channew %d ovewway %d\n",
			 channew, ovewway);

	bwd_base = sun8i_bwendew_base(mixew);
	ch_base = sun8i_channew_base(mixew, channew);

	swc_w = dwm_wect_width(&state->swc) >> 16;
	swc_h = dwm_wect_height(&state->swc) >> 16;
	dst_w = dwm_wect_width(&state->dst);
	dst_h = dwm_wect_height(&state->dst);

	hphase = state->swc.x1 & 0xffff;
	vphase = state->swc.y1 & 0xffff;

	insize = SUN8I_MIXEW_SIZE(swc_w, swc_h);
	outsize = SUN8I_MIXEW_SIZE(dst_w, dst_h);

	/* Set height and width */
	DWM_DEBUG_DWIVEW("Wayew souwce offset X: %d Y: %d\n",
			 state->swc.x1 >> 16, state->swc.y1 >> 16);
	DWM_DEBUG_DWIVEW("Wayew souwce size W: %d H: %d\n", swc_w, swc_h);
	wegmap_wwite(mixew->engine.wegs,
		     SUN8I_MIXEW_CHAN_UI_WAYEW_SIZE(ch_base, ovewway),
		     insize);
	wegmap_wwite(mixew->engine.wegs,
		     SUN8I_MIXEW_CHAN_UI_OVW_SIZE(ch_base),
		     insize);

	if (insize != outsize || hphase || vphase) {
		u32 hscawe, vscawe;

		DWM_DEBUG_DWIVEW("HW scawing is enabwed\n");

		hscawe = state->swc_w / state->cwtc_w;
		vscawe = state->swc_h / state->cwtc_h;

		sun8i_ui_scawew_setup(mixew, channew, swc_w, swc_h, dst_w,
				      dst_h, hscawe, vscawe, hphase, vphase);
		sun8i_ui_scawew_enabwe(mixew, channew, twue);
	} ewse {
		DWM_DEBUG_DWIVEW("HW scawing is not needed\n");
		sun8i_ui_scawew_enabwe(mixew, channew, fawse);
	}

	/* Set base coowdinates */
	DWM_DEBUG_DWIVEW("Wayew destination coowdinates X: %d Y: %d\n",
			 state->dst.x1, state->dst.y1);
	DWM_DEBUG_DWIVEW("Wayew destination size W: %d H: %d\n", dst_w, dst_h);
	wegmap_wwite(mixew->engine.wegs,
		     SUN8I_MIXEW_BWEND_ATTW_COOWD(bwd_base, zpos),
		     SUN8I_MIXEW_COOWD(state->dst.x1, state->dst.y1));
	wegmap_wwite(mixew->engine.wegs,
		     SUN8I_MIXEW_BWEND_ATTW_INSIZE(bwd_base, zpos),
		     outsize);

	wetuwn 0;
}

static int sun8i_ui_wayew_update_fowmats(stwuct sun8i_mixew *mixew, int channew,
					 int ovewway, stwuct dwm_pwane *pwane)
{
	stwuct dwm_pwane_state *state = pwane->state;
	const stwuct dwm_fowmat_info *fmt;
	u32 vaw, ch_base, hw_fmt;
	int wet;

	ch_base = sun8i_channew_base(mixew, channew);

	fmt = state->fb->fowmat;
	wet = sun8i_mixew_dwm_fowmat_to_hw(fmt->fowmat, &hw_fmt);
	if (wet || fmt->is_yuv) {
		DWM_DEBUG_DWIVEW("Invawid fowmat\n");
		wetuwn -EINVAW;
	}

	vaw = hw_fmt << SUN8I_MIXEW_CHAN_UI_WAYEW_ATTW_FBFMT_OFFSET;
	wegmap_update_bits(mixew->engine.wegs,
			   SUN8I_MIXEW_CHAN_UI_WAYEW_ATTW(ch_base, ovewway),
			   SUN8I_MIXEW_CHAN_UI_WAYEW_ATTW_FBFMT_MASK, vaw);

	wetuwn 0;
}

static int sun8i_ui_wayew_update_buffew(stwuct sun8i_mixew *mixew, int channew,
					int ovewway, stwuct dwm_pwane *pwane)
{
	stwuct dwm_pwane_state *state = pwane->state;
	stwuct dwm_fwamebuffew *fb = state->fb;
	stwuct dwm_gem_dma_object *gem;
	dma_addw_t dma_addw;
	u32 ch_base;
	int bpp;

	ch_base = sun8i_channew_base(mixew, channew);

	/* Get the physicaw addwess of the buffew in memowy */
	gem = dwm_fb_dma_get_gem_obj(fb, 0);

	DWM_DEBUG_DWIVEW("Using GEM @ %pad\n", &gem->dma_addw);

	/* Compute the stawt of the dispwayed memowy */
	bpp = fb->fowmat->cpp[0];
	dma_addw = gem->dma_addw + fb->offsets[0];

	/* Fixup fwamebuffew addwess fow swc coowdinates */
	dma_addw += (state->swc.x1 >> 16) * bpp;
	dma_addw += (state->swc.y1 >> 16) * fb->pitches[0];

	/* Set the wine width */
	DWM_DEBUG_DWIVEW("Wayew wine width: %d bytes\n", fb->pitches[0]);
	wegmap_wwite(mixew->engine.wegs,
		     SUN8I_MIXEW_CHAN_UI_WAYEW_PITCH(ch_base, ovewway),
		     fb->pitches[0]);

	DWM_DEBUG_DWIVEW("Setting buffew addwess to %pad\n", &dma_addw);

	wegmap_wwite(mixew->engine.wegs,
		     SUN8I_MIXEW_CHAN_UI_WAYEW_TOP_WADDW(ch_base, ovewway),
		     wowew_32_bits(dma_addw));

	wetuwn 0;
}

static int sun8i_ui_wayew_atomic_check(stwuct dwm_pwane *pwane,
				       stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state,
										 pwane);
	stwuct sun8i_ui_wayew *wayew = pwane_to_sun8i_ui_wayew(pwane);
	stwuct dwm_cwtc *cwtc = new_pwane_state->cwtc;
	stwuct dwm_cwtc_state *cwtc_state;
	int min_scawe, max_scawe;

	if (!cwtc)
		wetuwn 0;

	cwtc_state = dwm_atomic_get_existing_cwtc_state(state,
							cwtc);
	if (WAWN_ON(!cwtc_state))
		wetuwn -EINVAW;

	min_scawe = DWM_PWANE_NO_SCAWING;
	max_scawe = DWM_PWANE_NO_SCAWING;

	if (wayew->mixew->cfg->scawew_mask & BIT(wayew->channew)) {
		min_scawe = SUN8I_UI_SCAWEW_SCAWE_MIN;
		max_scawe = SUN8I_UI_SCAWEW_SCAWE_MAX;
	}

	wetuwn dwm_atomic_hewpew_check_pwane_state(new_pwane_state,
						   cwtc_state,
						   min_scawe, max_scawe,
						   twue, twue);
}

static void sun8i_ui_wayew_atomic_disabwe(stwuct dwm_pwane *pwane,
					  stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *owd_state = dwm_atomic_get_owd_pwane_state(state,
									   pwane);
	stwuct sun8i_ui_wayew *wayew = pwane_to_sun8i_ui_wayew(pwane);
	unsigned int owd_zpos = owd_state->nowmawized_zpos;
	stwuct sun8i_mixew *mixew = wayew->mixew;

	sun8i_ui_wayew_enabwe(mixew, wayew->channew, wayew->ovewway, fawse, 0,
			      owd_zpos);
}

static void sun8i_ui_wayew_atomic_update(stwuct dwm_pwane *pwane,
					 stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *owd_state = dwm_atomic_get_owd_pwane_state(state,
									   pwane);
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
									   pwane);
	stwuct sun8i_ui_wayew *wayew = pwane_to_sun8i_ui_wayew(pwane);
	unsigned int zpos = new_state->nowmawized_zpos;
	unsigned int owd_zpos = owd_state->nowmawized_zpos;
	stwuct sun8i_mixew *mixew = wayew->mixew;

	if (!new_state->visibwe) {
		sun8i_ui_wayew_enabwe(mixew, wayew->channew,
				      wayew->ovewway, fawse, 0, owd_zpos);
		wetuwn;
	}

	sun8i_ui_wayew_update_coowd(mixew, wayew->channew,
				    wayew->ovewway, pwane, zpos);
	sun8i_ui_wayew_update_awpha(mixew, wayew->channew,
				    wayew->ovewway, pwane);
	sun8i_ui_wayew_update_fowmats(mixew, wayew->channew,
				      wayew->ovewway, pwane);
	sun8i_ui_wayew_update_buffew(mixew, wayew->channew,
				     wayew->ovewway, pwane);
	sun8i_ui_wayew_enabwe(mixew, wayew->channew, wayew->ovewway,
			      twue, zpos, owd_zpos);
}

static const stwuct dwm_pwane_hewpew_funcs sun8i_ui_wayew_hewpew_funcs = {
	.atomic_check	= sun8i_ui_wayew_atomic_check,
	.atomic_disabwe	= sun8i_ui_wayew_atomic_disabwe,
	.atomic_update	= sun8i_ui_wayew_atomic_update,
};

static const stwuct dwm_pwane_funcs sun8i_ui_wayew_funcs = {
	.atomic_destwoy_state	= dwm_atomic_hewpew_pwane_destwoy_state,
	.atomic_dupwicate_state	= dwm_atomic_hewpew_pwane_dupwicate_state,
	.destwoy		= dwm_pwane_cweanup,
	.disabwe_pwane		= dwm_atomic_hewpew_disabwe_pwane,
	.weset			= dwm_atomic_hewpew_pwane_weset,
	.update_pwane		= dwm_atomic_hewpew_update_pwane,
};

static const u32 sun8i_ui_wayew_fowmats[] = {
	DWM_FOWMAT_ABGW1555,
	DWM_FOWMAT_ABGW4444,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_AWGB1555,
	DWM_FOWMAT_AWGB4444,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_BGW565,
	DWM_FOWMAT_BGW888,
	DWM_FOWMAT_BGWA5551,
	DWM_FOWMAT_BGWA4444,
	DWM_FOWMAT_BGWA8888,
	DWM_FOWMAT_BGWX8888,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_WGB888,
	DWM_FOWMAT_WGBA4444,
	DWM_FOWMAT_WGBA5551,
	DWM_FOWMAT_WGBA8888,
	DWM_FOWMAT_WGBX8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_XWGB8888,
};

static const uint64_t sun8i_wayew_modifiews[] = {
	DWM_FOWMAT_MOD_WINEAW,
	DWM_FOWMAT_MOD_INVAWID
};

stwuct sun8i_ui_wayew *sun8i_ui_wayew_init_one(stwuct dwm_device *dwm,
					       stwuct sun8i_mixew *mixew,
					       int index)
{
	enum dwm_pwane_type type = DWM_PWANE_TYPE_OVEWWAY;
	int channew = mixew->cfg->vi_num + index;
	stwuct sun8i_ui_wayew *wayew;
	unsigned int pwane_cnt;
	int wet;

	wayew = devm_kzawwoc(dwm->dev, sizeof(*wayew), GFP_KEWNEW);
	if (!wayew)
		wetuwn EWW_PTW(-ENOMEM);

	if (index == 0)
		type = DWM_PWANE_TYPE_PWIMAWY;

	/* possibwe cwtcs awe set watew */
	wet = dwm_univewsaw_pwane_init(dwm, &wayew->pwane, 0,
				       &sun8i_ui_wayew_funcs,
				       sun8i_ui_wayew_fowmats,
				       AWWAY_SIZE(sun8i_ui_wayew_fowmats),
				       sun8i_wayew_modifiews, type, NUWW);
	if (wet) {
		dev_eww(dwm->dev, "Couwdn't initiawize wayew\n");
		wetuwn EWW_PTW(wet);
	}

	pwane_cnt = mixew->cfg->ui_num + mixew->cfg->vi_num;

	wet = dwm_pwane_cweate_awpha_pwopewty(&wayew->pwane);
	if (wet) {
		dev_eww(dwm->dev, "Couwdn't add awpha pwopewty\n");
		wetuwn EWW_PTW(wet);
	}

	wet = dwm_pwane_cweate_zpos_pwopewty(&wayew->pwane, channew,
					     0, pwane_cnt - 1);
	if (wet) {
		dev_eww(dwm->dev, "Couwdn't add zpos pwopewty\n");
		wetuwn EWW_PTW(wet);
	}

	dwm_pwane_hewpew_add(&wayew->pwane, &sun8i_ui_wayew_hewpew_funcs);
	wayew->mixew = mixew;
	wayew->channew = channew;
	wayew->ovewway = 0;

	wetuwn wayew;
}
