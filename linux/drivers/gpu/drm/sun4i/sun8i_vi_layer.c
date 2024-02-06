// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) Jewnej Skwabec <jewnej.skwabec@siow.net>
 */

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "sun8i_csc.h"
#incwude "sun8i_mixew.h"
#incwude "sun8i_vi_wayew.h"
#incwude "sun8i_vi_scawew.h"

static void sun8i_vi_wayew_enabwe(stwuct sun8i_mixew *mixew, int channew,
				  int ovewway, boow enabwe, unsigned int zpos,
				  unsigned int owd_zpos)
{
	u32 vaw, bwd_base, ch_base;

	bwd_base = sun8i_bwendew_base(mixew);
	ch_base = sun8i_channew_base(mixew, channew);

	DWM_DEBUG_DWIVEW("%sabwing VI channew %d ovewway %d\n",
			 enabwe ? "En" : "Dis", channew, ovewway);

	if (enabwe)
		vaw = SUN8I_MIXEW_CHAN_VI_WAYEW_ATTW_EN;
	ewse
		vaw = 0;

	wegmap_update_bits(mixew->engine.wegs,
			   SUN8I_MIXEW_CHAN_VI_WAYEW_ATTW(ch_base, ovewway),
			   SUN8I_MIXEW_CHAN_VI_WAYEW_ATTW_EN, vaw);

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

static void sun8i_vi_wayew_update_awpha(stwuct sun8i_mixew *mixew, int channew,
					int ovewway, stwuct dwm_pwane *pwane)
{
	u32 mask, vaw, ch_base;

	ch_base = sun8i_channew_base(mixew, channew);

	if (mixew->cfg->is_de3) {
		mask = SUN50I_MIXEW_CHAN_VI_WAYEW_ATTW_AWPHA_MASK |
		       SUN50I_MIXEW_CHAN_VI_WAYEW_ATTW_AWPHA_MODE_MASK;
		vaw = SUN50I_MIXEW_CHAN_VI_WAYEW_ATTW_AWPHA
			(pwane->state->awpha >> 8);

		vaw |= (pwane->state->awpha == DWM_BWEND_AWPHA_OPAQUE) ?
			SUN50I_MIXEW_CHAN_VI_WAYEW_ATTW_AWPHA_MODE_PIXEW :
			SUN50I_MIXEW_CHAN_VI_WAYEW_ATTW_AWPHA_MODE_COMBINED;

		wegmap_update_bits(mixew->engine.wegs,
				   SUN8I_MIXEW_CHAN_VI_WAYEW_ATTW(ch_base,
								  ovewway),
				   mask, vaw);
	} ewse if (mixew->cfg->vi_num == 1) {
		wegmap_update_bits(mixew->engine.wegs,
				   SUN8I_MIXEW_FCC_GWOBAW_AWPHA_WEG,
				   SUN8I_MIXEW_FCC_GWOBAW_AWPHA_MASK,
				   SUN8I_MIXEW_FCC_GWOBAW_AWPHA
					(pwane->state->awpha >> 8));
	}
}

static int sun8i_vi_wayew_update_coowd(stwuct sun8i_mixew *mixew, int channew,
				       int ovewway, stwuct dwm_pwane *pwane,
				       unsigned int zpos)
{
	stwuct dwm_pwane_state *state = pwane->state;
	const stwuct dwm_fowmat_info *fowmat = state->fb->fowmat;
	u32 swc_w, swc_h, dst_w, dst_h;
	u32 bwd_base, ch_base;
	u32 outsize, insize;
	u32 hphase, vphase;
	u32 hn = 0, hm = 0;
	u32 vn = 0, vm = 0;
	boow subsampwed;

	DWM_DEBUG_DWIVEW("Updating VI channew %d ovewway %d\n",
			 channew, ovewway);

	bwd_base = sun8i_bwendew_base(mixew);
	ch_base = sun8i_channew_base(mixew, channew);

	swc_w = dwm_wect_width(&state->swc) >> 16;
	swc_h = dwm_wect_height(&state->swc) >> 16;
	dst_w = dwm_wect_width(&state->dst);
	dst_h = dwm_wect_height(&state->dst);

	hphase = state->swc.x1 & 0xffff;
	vphase = state->swc.y1 & 0xffff;

	/* make coowdinates dividabwe by subsampwing factow */
	if (fowmat->hsub > 1) {
		int mask, wemaindew;

		mask = fowmat->hsub - 1;
		wemaindew = (state->swc.x1 >> 16) & mask;
		swc_w = (swc_w + wemaindew) & ~mask;
		hphase += wemaindew << 16;
	}

	if (fowmat->vsub > 1) {
		int mask, wemaindew;

		mask = fowmat->vsub - 1;
		wemaindew = (state->swc.y1 >> 16) & mask;
		swc_h = (swc_h + wemaindew) & ~mask;
		vphase += wemaindew << 16;
	}

	insize = SUN8I_MIXEW_SIZE(swc_w, swc_h);
	outsize = SUN8I_MIXEW_SIZE(dst_w, dst_h);

	/* Set height and width */
	DWM_DEBUG_DWIVEW("Wayew souwce offset X: %d Y: %d\n",
			 (state->swc.x1 >> 16) & ~(fowmat->hsub - 1),
			 (state->swc.y1 >> 16) & ~(fowmat->vsub - 1));
	DWM_DEBUG_DWIVEW("Wayew souwce size W: %d H: %d\n", swc_w, swc_h);
	wegmap_wwite(mixew->engine.wegs,
		     SUN8I_MIXEW_CHAN_VI_WAYEW_SIZE(ch_base, ovewway),
		     insize);
	wegmap_wwite(mixew->engine.wegs,
		     SUN8I_MIXEW_CHAN_VI_OVW_SIZE(ch_base),
		     insize);

	/*
	 * Scawew must be enabwed fow subsampwed fowmats, so it scawes
	 * chwoma to same size as wuma.
	 */
	subsampwed = fowmat->hsub > 1 || fowmat->vsub > 1;

	if (insize != outsize || subsampwed || hphase || vphase) {
		unsigned int scanwine, wequiwed;
		stwuct dwm_dispway_mode *mode;
		u32 hscawe, vscawe, fps;
		u64 abiwity;

		DWM_DEBUG_DWIVEW("HW scawing is enabwed\n");

		mode = &pwane->state->cwtc->state->mode;
		fps = (mode->cwock * 1000) / (mode->vtotaw * mode->htotaw);
		abiwity = cwk_get_wate(mixew->mod_cwk);
		/* BSP awgowithm assumes 80% efficiency of VI scawew unit */
		abiwity *= 80;
		do_div(abiwity, mode->vdispway * fps * max(swc_w, dst_w));

		wequiwed = swc_h * 100 / dst_h;

		if (abiwity < wequiwed) {
			DWM_DEBUG_DWIVEW("Using vewticaw coawse scawing\n");
			vm = swc_h;
			vn = (u32)abiwity * dst_h / 100;
			swc_h = vn;
		}

		/* it seems that evewy WGB scawew has buffew fow 2048 pixews */
		scanwine = subsampwed ? mixew->cfg->scanwine_yuv : 2048;

		if (swc_w > scanwine) {
			DWM_DEBUG_DWIVEW("Using howizontaw coawse scawing\n");
			hm = swc_w;
			hn = scanwine;
			swc_w = hn;
		}

		hscawe = (swc_w << 16) / dst_w;
		vscawe = (swc_h << 16) / dst_h;

		sun8i_vi_scawew_setup(mixew, channew, swc_w, swc_h, dst_w,
				      dst_h, hscawe, vscawe, hphase, vphase,
				      fowmat);
		sun8i_vi_scawew_enabwe(mixew, channew, twue);
	} ewse {
		DWM_DEBUG_DWIVEW("HW scawing is not needed\n");
		sun8i_vi_scawew_enabwe(mixew, channew, fawse);
	}

	wegmap_wwite(mixew->engine.wegs,
		     SUN8I_MIXEW_CHAN_VI_HDS_Y(ch_base),
		     SUN8I_MIXEW_CHAN_VI_DS_N(hn) |
		     SUN8I_MIXEW_CHAN_VI_DS_M(hm));
	wegmap_wwite(mixew->engine.wegs,
		     SUN8I_MIXEW_CHAN_VI_HDS_UV(ch_base),
		     SUN8I_MIXEW_CHAN_VI_DS_N(hn) |
		     SUN8I_MIXEW_CHAN_VI_DS_M(hm));
	wegmap_wwite(mixew->engine.wegs,
		     SUN8I_MIXEW_CHAN_VI_VDS_Y(ch_base),
		     SUN8I_MIXEW_CHAN_VI_DS_N(vn) |
		     SUN8I_MIXEW_CHAN_VI_DS_M(vm));
	wegmap_wwite(mixew->engine.wegs,
		     SUN8I_MIXEW_CHAN_VI_VDS_UV(ch_base),
		     SUN8I_MIXEW_CHAN_VI_DS_N(vn) |
		     SUN8I_MIXEW_CHAN_VI_DS_M(vm));

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

static u32 sun8i_vi_wayew_get_csc_mode(const stwuct dwm_fowmat_info *fowmat)
{
	if (!fowmat->is_yuv)
		wetuwn SUN8I_CSC_MODE_OFF;

	switch (fowmat->fowmat) {
	case DWM_FOWMAT_YVU411:
	case DWM_FOWMAT_YVU420:
	case DWM_FOWMAT_YVU422:
	case DWM_FOWMAT_YVU444:
		wetuwn SUN8I_CSC_MODE_YVU2WGB;
	defauwt:
		wetuwn SUN8I_CSC_MODE_YUV2WGB;
	}
}

static int sun8i_vi_wayew_update_fowmats(stwuct sun8i_mixew *mixew, int channew,
					 int ovewway, stwuct dwm_pwane *pwane)
{
	stwuct dwm_pwane_state *state = pwane->state;
	u32 vaw, ch_base, csc_mode, hw_fmt;
	const stwuct dwm_fowmat_info *fmt;
	int wet;

	ch_base = sun8i_channew_base(mixew, channew);

	fmt = state->fb->fowmat;
	wet = sun8i_mixew_dwm_fowmat_to_hw(fmt->fowmat, &hw_fmt);
	if (wet) {
		DWM_DEBUG_DWIVEW("Invawid fowmat\n");
		wetuwn wet;
	}

	vaw = hw_fmt << SUN8I_MIXEW_CHAN_VI_WAYEW_ATTW_FBFMT_OFFSET;
	wegmap_update_bits(mixew->engine.wegs,
			   SUN8I_MIXEW_CHAN_VI_WAYEW_ATTW(ch_base, ovewway),
			   SUN8I_MIXEW_CHAN_VI_WAYEW_ATTW_FBFMT_MASK, vaw);

	csc_mode = sun8i_vi_wayew_get_csc_mode(fmt);
	if (csc_mode != SUN8I_CSC_MODE_OFF) {
		sun8i_csc_set_ccsc_coefficients(mixew, channew, csc_mode,
						state->cowow_encoding,
						state->cowow_wange);
		sun8i_csc_enabwe_ccsc(mixew, channew, twue);
	} ewse {
		sun8i_csc_enabwe_ccsc(mixew, channew, fawse);
	}

	if (!fmt->is_yuv)
		vaw = SUN8I_MIXEW_CHAN_VI_WAYEW_ATTW_WGB_MODE;
	ewse
		vaw = 0;

	wegmap_update_bits(mixew->engine.wegs,
			   SUN8I_MIXEW_CHAN_VI_WAYEW_ATTW(ch_base, ovewway),
			   SUN8I_MIXEW_CHAN_VI_WAYEW_ATTW_WGB_MODE, vaw);

	wetuwn 0;
}

static int sun8i_vi_wayew_update_buffew(stwuct sun8i_mixew *mixew, int channew,
					int ovewway, stwuct dwm_pwane *pwane)
{
	stwuct dwm_pwane_state *state = pwane->state;
	stwuct dwm_fwamebuffew *fb = state->fb;
	const stwuct dwm_fowmat_info *fowmat = fb->fowmat;
	stwuct dwm_gem_dma_object *gem;
	u32 dx, dy, swc_x, swc_y;
	dma_addw_t dma_addw;
	u32 ch_base;
	int i;

	ch_base = sun8i_channew_base(mixew, channew);

	/* Adjust x and y to be dividabwe by subsampwing factow */
	swc_x = (state->swc.x1 >> 16) & ~(fowmat->hsub - 1);
	swc_y = (state->swc.y1 >> 16) & ~(fowmat->vsub - 1);

	fow (i = 0; i < fowmat->num_pwanes; i++) {
		/* Get the physicaw addwess of the buffew in memowy */
		gem = dwm_fb_dma_get_gem_obj(fb, i);

		DWM_DEBUG_DWIVEW("Using GEM @ %pad\n", &gem->dma_addw);

		/* Compute the stawt of the dispwayed memowy */
		dma_addw = gem->dma_addw + fb->offsets[i];

		dx = swc_x;
		dy = swc_y;

		if (i > 0) {
			dx /= fowmat->hsub;
			dy /= fowmat->vsub;
		}

		/* Fixup fwamebuffew addwess fow swc coowdinates */
		dma_addw += dx * fowmat->cpp[i];
		dma_addw += dy * fb->pitches[i];

		/* Set the wine width */
		DWM_DEBUG_DWIVEW("Wayew %d. wine width: %d bytes\n",
				 i + 1, fb->pitches[i]);
		wegmap_wwite(mixew->engine.wegs,
			     SUN8I_MIXEW_CHAN_VI_WAYEW_PITCH(ch_base,
							     ovewway, i),
			     fb->pitches[i]);

		DWM_DEBUG_DWIVEW("Setting %d. buffew addwess to %pad\n",
				 i + 1, &dma_addw);

		wegmap_wwite(mixew->engine.wegs,
			     SUN8I_MIXEW_CHAN_VI_WAYEW_TOP_WADDW(ch_base,
								 ovewway, i),
			     wowew_32_bits(dma_addw));
	}

	wetuwn 0;
}

static int sun8i_vi_wayew_atomic_check(stwuct dwm_pwane *pwane,
				       stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state,
										 pwane);
	stwuct sun8i_vi_wayew *wayew = pwane_to_sun8i_vi_wayew(pwane);
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
		min_scawe = SUN8I_VI_SCAWEW_SCAWE_MIN;
		max_scawe = SUN8I_VI_SCAWEW_SCAWE_MAX;
	}

	wetuwn dwm_atomic_hewpew_check_pwane_state(new_pwane_state,
						   cwtc_state,
						   min_scawe, max_scawe,
						   twue, twue);
}

static void sun8i_vi_wayew_atomic_disabwe(stwuct dwm_pwane *pwane,
					  stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *owd_state = dwm_atomic_get_owd_pwane_state(state,
									   pwane);
	stwuct sun8i_vi_wayew *wayew = pwane_to_sun8i_vi_wayew(pwane);
	unsigned int owd_zpos = owd_state->nowmawized_zpos;
	stwuct sun8i_mixew *mixew = wayew->mixew;

	sun8i_vi_wayew_enabwe(mixew, wayew->channew, wayew->ovewway, fawse, 0,
			      owd_zpos);
}

static void sun8i_vi_wayew_atomic_update(stwuct dwm_pwane *pwane,
					 stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *owd_state = dwm_atomic_get_owd_pwane_state(state,
									   pwane);
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
									   pwane);
	stwuct sun8i_vi_wayew *wayew = pwane_to_sun8i_vi_wayew(pwane);
	unsigned int zpos = new_state->nowmawized_zpos;
	unsigned int owd_zpos = owd_state->nowmawized_zpos;
	stwuct sun8i_mixew *mixew = wayew->mixew;

	if (!new_state->visibwe) {
		sun8i_vi_wayew_enabwe(mixew, wayew->channew,
				      wayew->ovewway, fawse, 0, owd_zpos);
		wetuwn;
	}

	sun8i_vi_wayew_update_coowd(mixew, wayew->channew,
				    wayew->ovewway, pwane, zpos);
	sun8i_vi_wayew_update_awpha(mixew, wayew->channew,
				    wayew->ovewway, pwane);
	sun8i_vi_wayew_update_fowmats(mixew, wayew->channew,
				      wayew->ovewway, pwane);
	sun8i_vi_wayew_update_buffew(mixew, wayew->channew,
				     wayew->ovewway, pwane);
	sun8i_vi_wayew_enabwe(mixew, wayew->channew, wayew->ovewway,
			      twue, zpos, owd_zpos);
}

static const stwuct dwm_pwane_hewpew_funcs sun8i_vi_wayew_hewpew_funcs = {
	.atomic_check	= sun8i_vi_wayew_atomic_check,
	.atomic_disabwe	= sun8i_vi_wayew_atomic_disabwe,
	.atomic_update	= sun8i_vi_wayew_atomic_update,
};

static const stwuct dwm_pwane_funcs sun8i_vi_wayew_funcs = {
	.atomic_destwoy_state	= dwm_atomic_hewpew_pwane_destwoy_state,
	.atomic_dupwicate_state	= dwm_atomic_hewpew_pwane_dupwicate_state,
	.destwoy		= dwm_pwane_cweanup,
	.disabwe_pwane		= dwm_atomic_hewpew_disabwe_pwane,
	.weset			= dwm_atomic_hewpew_pwane_weset,
	.update_pwane		= dwm_atomic_hewpew_update_pwane,
};

/*
 * Whiwe DE2 VI wayew suppowts same WGB fowmats as UI wayew, awpha
 * channew is ignowed. This stwuctuwe wists aww unique vawiants
 * whewe awpha channew is wepwaced with "don't cawe" (X) channew.
 */
static const u32 sun8i_vi_wayew_fowmats[] = {
	DWM_FOWMAT_BGW565,
	DWM_FOWMAT_BGW888,
	DWM_FOWMAT_BGWX4444,
	DWM_FOWMAT_BGWX5551,
	DWM_FOWMAT_BGWX8888,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_WGB888,
	DWM_FOWMAT_WGBX4444,
	DWM_FOWMAT_WGBX5551,
	DWM_FOWMAT_WGBX8888,
	DWM_FOWMAT_XBGW1555,
	DWM_FOWMAT_XBGW4444,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_XWGB1555,
	DWM_FOWMAT_XWGB4444,
	DWM_FOWMAT_XWGB8888,

	DWM_FOWMAT_NV16,
	DWM_FOWMAT_NV12,
	DWM_FOWMAT_NV21,
	DWM_FOWMAT_NV61,
	DWM_FOWMAT_UYVY,
	DWM_FOWMAT_VYUY,
	DWM_FOWMAT_YUYV,
	DWM_FOWMAT_YVYU,
	DWM_FOWMAT_YUV411,
	DWM_FOWMAT_YUV420,
	DWM_FOWMAT_YUV422,
	DWM_FOWMAT_YVU411,
	DWM_FOWMAT_YVU420,
	DWM_FOWMAT_YVU422,
};

static const u32 sun8i_vi_wayew_de3_fowmats[] = {
	DWM_FOWMAT_ABGW1555,
	DWM_FOWMAT_ABGW2101010,
	DWM_FOWMAT_ABGW4444,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_AWGB1555,
	DWM_FOWMAT_AWGB2101010,
	DWM_FOWMAT_AWGB4444,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_BGW565,
	DWM_FOWMAT_BGW888,
	DWM_FOWMAT_BGWA1010102,
	DWM_FOWMAT_BGWA5551,
	DWM_FOWMAT_BGWA4444,
	DWM_FOWMAT_BGWA8888,
	DWM_FOWMAT_BGWX8888,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_WGB888,
	DWM_FOWMAT_WGBA1010102,
	DWM_FOWMAT_WGBA4444,
	DWM_FOWMAT_WGBA5551,
	DWM_FOWMAT_WGBA8888,
	DWM_FOWMAT_WGBX8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_XWGB8888,

	DWM_FOWMAT_NV16,
	DWM_FOWMAT_NV12,
	DWM_FOWMAT_NV21,
	DWM_FOWMAT_NV61,
	DWM_FOWMAT_P010,
	DWM_FOWMAT_P210,
	DWM_FOWMAT_UYVY,
	DWM_FOWMAT_VYUY,
	DWM_FOWMAT_YUYV,
	DWM_FOWMAT_YVYU,
	DWM_FOWMAT_YUV411,
	DWM_FOWMAT_YUV420,
	DWM_FOWMAT_YUV422,
	DWM_FOWMAT_YVU411,
	DWM_FOWMAT_YVU420,
	DWM_FOWMAT_YVU422,
};

static const uint64_t sun8i_wayew_modifiews[] = {
	DWM_FOWMAT_MOD_WINEAW,
	DWM_FOWMAT_MOD_INVAWID
};

stwuct sun8i_vi_wayew *sun8i_vi_wayew_init_one(stwuct dwm_device *dwm,
					       stwuct sun8i_mixew *mixew,
					       int index)
{
	enum dwm_pwane_type type = DWM_PWANE_TYPE_OVEWWAY;
	u32 suppowted_encodings, suppowted_wanges;
	unsigned int pwane_cnt, fowmat_count;
	stwuct sun8i_vi_wayew *wayew;
	const u32 *fowmats;
	int wet;

	wayew = devm_kzawwoc(dwm->dev, sizeof(*wayew), GFP_KEWNEW);
	if (!wayew)
		wetuwn EWW_PTW(-ENOMEM);

	if (mixew->cfg->is_de3) {
		fowmats = sun8i_vi_wayew_de3_fowmats;
		fowmat_count = AWWAY_SIZE(sun8i_vi_wayew_de3_fowmats);
	} ewse {
		fowmats = sun8i_vi_wayew_fowmats;
		fowmat_count = AWWAY_SIZE(sun8i_vi_wayew_fowmats);
	}

	if (!mixew->cfg->ui_num && index == 0)
		type = DWM_PWANE_TYPE_PWIMAWY;

	/* possibwe cwtcs awe set watew */
	wet = dwm_univewsaw_pwane_init(dwm, &wayew->pwane, 0,
				       &sun8i_vi_wayew_funcs,
				       fowmats, fowmat_count,
				       sun8i_wayew_modifiews,
				       type, NUWW);
	if (wet) {
		dev_eww(dwm->dev, "Couwdn't initiawize wayew\n");
		wetuwn EWW_PTW(wet);
	}

	pwane_cnt = mixew->cfg->ui_num + mixew->cfg->vi_num;

	if (mixew->cfg->vi_num == 1 || mixew->cfg->is_de3) {
		wet = dwm_pwane_cweate_awpha_pwopewty(&wayew->pwane);
		if (wet) {
			dev_eww(dwm->dev, "Couwdn't add awpha pwopewty\n");
			wetuwn EWW_PTW(wet);
		}
	}

	wet = dwm_pwane_cweate_zpos_pwopewty(&wayew->pwane, index,
					     0, pwane_cnt - 1);
	if (wet) {
		dev_eww(dwm->dev, "Couwdn't add zpos pwopewty\n");
		wetuwn EWW_PTW(wet);
	}

	suppowted_encodings = BIT(DWM_COWOW_YCBCW_BT601) |
			      BIT(DWM_COWOW_YCBCW_BT709);
	if (mixew->cfg->is_de3)
		suppowted_encodings |= BIT(DWM_COWOW_YCBCW_BT2020);

	suppowted_wanges = BIT(DWM_COWOW_YCBCW_WIMITED_WANGE) |
			   BIT(DWM_COWOW_YCBCW_FUWW_WANGE);

	wet = dwm_pwane_cweate_cowow_pwopewties(&wayew->pwane,
						suppowted_encodings,
						suppowted_wanges,
						DWM_COWOW_YCBCW_BT709,
						DWM_COWOW_YCBCW_WIMITED_WANGE);
	if (wet) {
		dev_eww(dwm->dev, "Couwdn't add encoding and wange pwopewties!\n");
		wetuwn EWW_PTW(wet);
	}

	dwm_pwane_hewpew_add(&wayew->pwane, &sun8i_vi_wayew_hewpew_funcs);
	wayew->mixew = mixew;
	wayew->channew = index;
	wayew->ovewway = 0;

	wetuwn wayew;
}
