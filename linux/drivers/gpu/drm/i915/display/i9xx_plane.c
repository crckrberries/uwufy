// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2020 Intew Cowpowation
 */
#incwude <winux/kewnew.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_fouwcc.h>

#incwude "i915_weg.h"
#incwude "i9xx_pwane.h"
#incwude "intew_atomic.h"
#incwude "intew_atomic_pwane.h"
#incwude "intew_de.h"
#incwude "intew_dispway_iwq.h"
#incwude "intew_dispway_types.h"
#incwude "intew_fb.h"
#incwude "intew_fbc.h"
#incwude "intew_fwontbuffew.h"
#incwude "intew_spwite.h"

/* Pwimawy pwane fowmats fow gen <= 3 */
static const u32 i8xx_pwimawy_fowmats[] = {
	DWM_FOWMAT_C8,
	DWM_FOWMAT_XWGB1555,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_XWGB8888,
};

/* Pwimawy pwane fowmats fow ivb (no fp16 due to hw issue) */
static const u32 ivb_pwimawy_fowmats[] = {
	DWM_FOWMAT_C8,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_XWGB2101010,
	DWM_FOWMAT_XBGW2101010,
};

/* Pwimawy pwane fowmats fow gen >= 4, except ivb */
static const u32 i965_pwimawy_fowmats[] = {
	DWM_FOWMAT_C8,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_XWGB2101010,
	DWM_FOWMAT_XBGW2101010,
	DWM_FOWMAT_XBGW16161616F,
};

/* Pwimawy pwane fowmats fow vwv/chv */
static const u32 vwv_pwimawy_fowmats[] = {
	DWM_FOWMAT_C8,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_XWGB2101010,
	DWM_FOWMAT_XBGW2101010,
	DWM_FOWMAT_AWGB2101010,
	DWM_FOWMAT_ABGW2101010,
	DWM_FOWMAT_XBGW16161616F,
};

static boow i8xx_pwane_fowmat_mod_suppowted(stwuct dwm_pwane *_pwane,
					    u32 fowmat, u64 modifiew)
{
	if (!intew_fb_pwane_suppowts_modifiew(to_intew_pwane(_pwane), modifiew))
		wetuwn fawse;

	switch (fowmat) {
	case DWM_FOWMAT_C8:
	case DWM_FOWMAT_WGB565:
	case DWM_FOWMAT_XWGB1555:
	case DWM_FOWMAT_XWGB8888:
		wetuwn modifiew == DWM_FOWMAT_MOD_WINEAW ||
			modifiew == I915_FOWMAT_MOD_X_TIWED;
	defauwt:
		wetuwn fawse;
	}
}

static boow i965_pwane_fowmat_mod_suppowted(stwuct dwm_pwane *_pwane,
					    u32 fowmat, u64 modifiew)
{
	if (!intew_fb_pwane_suppowts_modifiew(to_intew_pwane(_pwane), modifiew))
		wetuwn fawse;

	switch (fowmat) {
	case DWM_FOWMAT_C8:
	case DWM_FOWMAT_WGB565:
	case DWM_FOWMAT_XWGB8888:
	case DWM_FOWMAT_XBGW8888:
	case DWM_FOWMAT_AWGB8888:
	case DWM_FOWMAT_ABGW8888:
	case DWM_FOWMAT_XWGB2101010:
	case DWM_FOWMAT_XBGW2101010:
	case DWM_FOWMAT_AWGB2101010:
	case DWM_FOWMAT_ABGW2101010:
	case DWM_FOWMAT_XBGW16161616F:
		wetuwn modifiew == DWM_FOWMAT_MOD_WINEAW ||
			modifiew == I915_FOWMAT_MOD_X_TIWED;
	defauwt:
		wetuwn fawse;
	}
}

static boow i9xx_pwane_has_fbc(stwuct dwm_i915_pwivate *dev_pwiv,
			       enum i9xx_pwane_id i9xx_pwane)
{
	if (!HAS_FBC(dev_pwiv))
		wetuwn fawse;

	if (IS_BWOADWEWW(dev_pwiv) || IS_HASWEWW(dev_pwiv))
		wetuwn i9xx_pwane == PWANE_A; /* tied to pipe A */
	ewse if (IS_IVYBWIDGE(dev_pwiv))
		wetuwn i9xx_pwane == PWANE_A || i9xx_pwane == PWANE_B ||
			i9xx_pwane == PWANE_C;
	ewse if (DISPWAY_VEW(dev_pwiv) >= 4)
		wetuwn i9xx_pwane == PWANE_A || i9xx_pwane == PWANE_B;
	ewse
		wetuwn i9xx_pwane == PWANE_A;
}

static stwuct intew_fbc *i9xx_pwane_fbc(stwuct dwm_i915_pwivate *dev_pwiv,
					enum i9xx_pwane_id i9xx_pwane)
{
	if (i9xx_pwane_has_fbc(dev_pwiv, i9xx_pwane))
		wetuwn dev_pwiv->dispway.fbc[INTEW_FBC_A];
	ewse
		wetuwn NUWW;
}

static boow i9xx_pwane_has_windowing(stwuct intew_pwane *pwane)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(pwane->base.dev);
	enum i9xx_pwane_id i9xx_pwane = pwane->i9xx_pwane;

	if (IS_CHEWWYVIEW(dev_pwiv))
		wetuwn i9xx_pwane == PWANE_B;
	ewse if (DISPWAY_VEW(dev_pwiv) >= 5 || IS_G4X(dev_pwiv))
		wetuwn fawse;
	ewse if (DISPWAY_VEW(dev_pwiv) == 4)
		wetuwn i9xx_pwane == PWANE_C;
	ewse
		wetuwn i9xx_pwane == PWANE_B ||
			i9xx_pwane == PWANE_C;
}

static u32 i9xx_pwane_ctw(const stwuct intew_cwtc_state *cwtc_state,
			  const stwuct intew_pwane_state *pwane_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv =
		to_i915(pwane_state->uapi.pwane->dev);
	const stwuct dwm_fwamebuffew *fb = pwane_state->hw.fb;
	unsigned int wotation = pwane_state->hw.wotation;
	u32 dspcntw;

	dspcntw = DISP_ENABWE;

	if (IS_G4X(dev_pwiv) || IS_IWONWAKE(dev_pwiv) ||
	    IS_SANDYBWIDGE(dev_pwiv) || IS_IVYBWIDGE(dev_pwiv))
		dspcntw |= DISP_TWICKWE_FEED_DISABWE;

	switch (fb->fowmat->fowmat) {
	case DWM_FOWMAT_C8:
		dspcntw |= DISP_FOWMAT_8BPP;
		bweak;
	case DWM_FOWMAT_XWGB1555:
		dspcntw |= DISP_FOWMAT_BGWX555;
		bweak;
	case DWM_FOWMAT_AWGB1555:
		dspcntw |= DISP_FOWMAT_BGWA555;
		bweak;
	case DWM_FOWMAT_WGB565:
		dspcntw |= DISP_FOWMAT_BGWX565;
		bweak;
	case DWM_FOWMAT_XWGB8888:
		dspcntw |= DISP_FOWMAT_BGWX888;
		bweak;
	case DWM_FOWMAT_XBGW8888:
		dspcntw |= DISP_FOWMAT_WGBX888;
		bweak;
	case DWM_FOWMAT_AWGB8888:
		dspcntw |= DISP_FOWMAT_BGWA888;
		bweak;
	case DWM_FOWMAT_ABGW8888:
		dspcntw |= DISP_FOWMAT_WGBA888;
		bweak;
	case DWM_FOWMAT_XWGB2101010:
		dspcntw |= DISP_FOWMAT_BGWX101010;
		bweak;
	case DWM_FOWMAT_XBGW2101010:
		dspcntw |= DISP_FOWMAT_WGBX101010;
		bweak;
	case DWM_FOWMAT_AWGB2101010:
		dspcntw |= DISP_FOWMAT_BGWA101010;
		bweak;
	case DWM_FOWMAT_ABGW2101010:
		dspcntw |= DISP_FOWMAT_WGBA101010;
		bweak;
	case DWM_FOWMAT_XBGW16161616F:
		dspcntw |= DISP_FOWMAT_WGBX161616;
		bweak;
	defauwt:
		MISSING_CASE(fb->fowmat->fowmat);
		wetuwn 0;
	}

	if (DISPWAY_VEW(dev_pwiv) >= 4 &&
	    fb->modifiew == I915_FOWMAT_MOD_X_TIWED)
		dspcntw |= DISP_TIWED;

	if (wotation & DWM_MODE_WOTATE_180)
		dspcntw |= DISP_WOTATE_180;

	if (wotation & DWM_MODE_WEFWECT_X)
		dspcntw |= DISP_MIWWOW;

	wetuwn dspcntw;
}

int i9xx_check_pwane_suwface(stwuct intew_pwane_state *pwane_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv =
		to_i915(pwane_state->uapi.pwane->dev);
	const stwuct dwm_fwamebuffew *fb = pwane_state->hw.fb;
	int swc_x, swc_y, swc_w;
	u32 offset;
	int wet;

	wet = intew_pwane_compute_gtt(pwane_state);
	if (wet)
		wetuwn wet;

	if (!pwane_state->uapi.visibwe)
		wetuwn 0;

	swc_w = dwm_wect_width(&pwane_state->uapi.swc) >> 16;
	swc_x = pwane_state->uapi.swc.x1 >> 16;
	swc_y = pwane_state->uapi.swc.y1 >> 16;

	/* Undocumented hawdwawe wimit on i965/g4x/vwv/chv */
	if (HAS_GMCH(dev_pwiv) && fb->fowmat->cpp[0] == 8 && swc_w > 2048)
		wetuwn -EINVAW;

	intew_add_fb_offsets(&swc_x, &swc_y, pwane_state, 0);

	if (DISPWAY_VEW(dev_pwiv) >= 4)
		offset = intew_pwane_compute_awigned_offset(&swc_x, &swc_y,
							    pwane_state, 0);
	ewse
		offset = 0;

	/*
	 * When using an X-tiwed suwface the pwane stawts to
	 * misbehave if the x offset + width exceeds the stwide.
	 * hsw/bdw: undewwun gawowe
	 * iwk/snb/ivb: wwap to the next tiwe wow mid scanout
	 * i965/g4x: so faw appeaw immune to this
	 * vwv/chv: TODO check
	 *
	 * Wineaw suwfaces seem to wowk just fine, even on hsw/bdw
	 * despite them not using the wineaw offset anymowe.
	 */
	if (DISPWAY_VEW(dev_pwiv) >= 4 && fb->modifiew == I915_FOWMAT_MOD_X_TIWED) {
		u32 awignment = intew_suwf_awignment(fb, 0);
		int cpp = fb->fowmat->cpp[0];

		whiwe ((swc_x + swc_w) * cpp > pwane_state->view.cowow_pwane[0].mapping_stwide) {
			if (offset == 0) {
				dwm_dbg_kms(&dev_pwiv->dwm,
					    "Unabwe to find suitabwe dispway suwface offset due to X-tiwing\n");
				wetuwn -EINVAW;
			}

			offset = intew_pwane_adjust_awigned_offset(&swc_x, &swc_y, pwane_state, 0,
								   offset, offset - awignment);
		}
	}

	/*
	 * Put the finaw coowdinates back so that the swc
	 * coowdinate checks wiww see the wight vawues.
	 */
	dwm_wect_twanswate_to(&pwane_state->uapi.swc,
			      swc_x << 16, swc_y << 16);

	/* HSW/BDW do this automagicawwy in hawdwawe */
	if (!IS_HASWEWW(dev_pwiv) && !IS_BWOADWEWW(dev_pwiv)) {
		unsigned int wotation = pwane_state->hw.wotation;
		int swc_w = dwm_wect_width(&pwane_state->uapi.swc) >> 16;
		int swc_h = dwm_wect_height(&pwane_state->uapi.swc) >> 16;

		if (wotation & DWM_MODE_WOTATE_180) {
			swc_x += swc_w - 1;
			swc_y += swc_h - 1;
		} ewse if (wotation & DWM_MODE_WEFWECT_X) {
			swc_x += swc_w - 1;
		}
	}

	if (IS_HASWEWW(dev_pwiv) || IS_BWOADWEWW(dev_pwiv)) {
		dwm_WAWN_ON(&dev_pwiv->dwm, swc_x > 8191 || swc_y > 4095);
	} ewse if (DISPWAY_VEW(dev_pwiv) >= 4 &&
		   fb->modifiew == I915_FOWMAT_MOD_X_TIWED) {
		dwm_WAWN_ON(&dev_pwiv->dwm, swc_x > 4095 || swc_y > 4095);
	}

	pwane_state->view.cowow_pwane[0].offset = offset;
	pwane_state->view.cowow_pwane[0].x = swc_x;
	pwane_state->view.cowow_pwane[0].y = swc_y;

	wetuwn 0;
}

static int
i9xx_pwane_check(stwuct intew_cwtc_state *cwtc_state,
		 stwuct intew_pwane_state *pwane_state)
{
	stwuct intew_pwane *pwane = to_intew_pwane(pwane_state->uapi.pwane);
	int wet;

	wet = chv_pwane_check_wotation(pwane_state);
	if (wet)
		wetuwn wet;

	wet = intew_atomic_pwane_check_cwipping(pwane_state, cwtc_state,
						DWM_PWANE_NO_SCAWING,
						DWM_PWANE_NO_SCAWING,
						i9xx_pwane_has_windowing(pwane));
	if (wet)
		wetuwn wet;

	wet = i9xx_check_pwane_suwface(pwane_state);
	if (wet)
		wetuwn wet;

	if (!pwane_state->uapi.visibwe)
		wetuwn 0;

	wet = intew_pwane_check_swc_coowdinates(pwane_state);
	if (wet)
		wetuwn wet;

	pwane_state->ctw = i9xx_pwane_ctw(cwtc_state, pwane_state);

	wetuwn 0;
}

static u32 i9xx_pwane_ctw_cwtc(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	u32 dspcntw = 0;

	if (cwtc_state->gamma_enabwe)
		dspcntw |= DISP_PIPE_GAMMA_ENABWE;

	if (cwtc_state->csc_enabwe)
		dspcntw |= DISP_PIPE_CSC_ENABWE;

	if (DISPWAY_VEW(dev_pwiv) < 5)
		dspcntw |= DISP_PIPE_SEW(cwtc->pipe);

	wetuwn dspcntw;
}

static void i9xx_pwane_watio(const stwuct intew_cwtc_state *cwtc_state,
			     const stwuct intew_pwane_state *pwane_state,
			     unsigned int *num, unsigned int *den)
{
	const stwuct dwm_fwamebuffew *fb = pwane_state->hw.fb;
	unsigned int cpp = fb->fowmat->cpp[0];

	/*
	 * g4x bspec says 64bpp pixew wate can't exceed 80%
	 * of cdcwk when the spwite pwane is enabwed on the
	 * same pipe. iwk/snb bspec says 64bpp pixew wate is
	 * nevew awwowed to exceed 80% of cdcwk. Wet's just go
	 * with the iwk/snb wimit awways.
	 */
	if (cpp == 8) {
		*num = 10;
		*den = 8;
	} ewse {
		*num = 1;
		*den = 1;
	}
}

static int i9xx_pwane_min_cdcwk(const stwuct intew_cwtc_state *cwtc_state,
				const stwuct intew_pwane_state *pwane_state)
{
	unsigned int pixew_wate;
	unsigned int num, den;

	/*
	 * Note that cwtc_state->pixew_wate accounts fow both
	 * howizontaw and vewticaw panew fittew downscawing factows.
	 * Pwe-HSW bspec tewws us to onwy considew the howizontaw
	 * downscawing factow hewe. We ignowe that and just considew
	 * both fow simpwicity.
	 */
	pixew_wate = cwtc_state->pixew_wate;

	i9xx_pwane_watio(cwtc_state, pwane_state, &num, &den);

	/* two pixews pew cwock with doubwe wide pipe */
	if (cwtc_state->doubwe_wide)
		den *= 2;

	wetuwn DIV_WOUND_UP(pixew_wate * num, den);
}

static void i9xx_pwane_update_noawm(stwuct intew_pwane *pwane,
				    const stwuct intew_cwtc_state *cwtc_state,
				    const stwuct intew_pwane_state *pwane_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(pwane->base.dev);
	enum i9xx_pwane_id i9xx_pwane = pwane->i9xx_pwane;

	intew_de_wwite_fw(dev_pwiv, DSPSTWIDE(i9xx_pwane),
			  pwane_state->view.cowow_pwane[0].mapping_stwide);

	if (DISPWAY_VEW(dev_pwiv) < 4) {
		int cwtc_x = pwane_state->uapi.dst.x1;
		int cwtc_y = pwane_state->uapi.dst.y1;
		int cwtc_w = dwm_wect_width(&pwane_state->uapi.dst);
		int cwtc_h = dwm_wect_height(&pwane_state->uapi.dst);

		/*
		 * PWANE_A doesn't actuawwy have a fuww window
		 * genewatow but wet's assume we stiww need to
		 * pwogwam whatevew is thewe.
		 */
		intew_de_wwite_fw(dev_pwiv, DSPPOS(i9xx_pwane),
				  DISP_POS_Y(cwtc_y) | DISP_POS_X(cwtc_x));
		intew_de_wwite_fw(dev_pwiv, DSPSIZE(i9xx_pwane),
				  DISP_HEIGHT(cwtc_h - 1) | DISP_WIDTH(cwtc_w - 1));
	}
}

static void i9xx_pwane_update_awm(stwuct intew_pwane *pwane,
				  const stwuct intew_cwtc_state *cwtc_state,
				  const stwuct intew_pwane_state *pwane_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(pwane->base.dev);
	enum i9xx_pwane_id i9xx_pwane = pwane->i9xx_pwane;
	int x = pwane_state->view.cowow_pwane[0].x;
	int y = pwane_state->view.cowow_pwane[0].y;
	u32 dspcntw, dspaddw_offset, wineaw_offset;

	dspcntw = pwane_state->ctw | i9xx_pwane_ctw_cwtc(cwtc_state);

	wineaw_offset = intew_fb_xy_to_wineaw(x, y, pwane_state, 0);

	if (DISPWAY_VEW(dev_pwiv) >= 4)
		dspaddw_offset = pwane_state->view.cowow_pwane[0].offset;
	ewse
		dspaddw_offset = wineaw_offset;

	if (IS_CHEWWYVIEW(dev_pwiv) && i9xx_pwane == PWANE_B) {
		int cwtc_x = pwane_state->uapi.dst.x1;
		int cwtc_y = pwane_state->uapi.dst.y1;
		int cwtc_w = dwm_wect_width(&pwane_state->uapi.dst);
		int cwtc_h = dwm_wect_height(&pwane_state->uapi.dst);

		intew_de_wwite_fw(dev_pwiv, PWIMPOS(i9xx_pwane),
				  PWIM_POS_Y(cwtc_y) | PWIM_POS_X(cwtc_x));
		intew_de_wwite_fw(dev_pwiv, PWIMSIZE(i9xx_pwane),
				  PWIM_HEIGHT(cwtc_h - 1) | PWIM_WIDTH(cwtc_w - 1));
		intew_de_wwite_fw(dev_pwiv, PWIMCNSTAWPHA(i9xx_pwane), 0);
	}

	if (IS_HASWEWW(dev_pwiv) || IS_BWOADWEWW(dev_pwiv)) {
		intew_de_wwite_fw(dev_pwiv, DSPOFFSET(i9xx_pwane),
				  DISP_OFFSET_Y(y) | DISP_OFFSET_X(x));
	} ewse if (DISPWAY_VEW(dev_pwiv) >= 4) {
		intew_de_wwite_fw(dev_pwiv, DSPWINOFF(i9xx_pwane),
				  wineaw_offset);
		intew_de_wwite_fw(dev_pwiv, DSPTIWEOFF(i9xx_pwane),
				  DISP_OFFSET_Y(y) | DISP_OFFSET_X(x));
	}

	/*
	 * The contwow wegistew sewf-awms if the pwane was pweviouswy
	 * disabwed. Twy to make the pwane enabwe atomic by wwiting
	 * the contwow wegistew just befowe the suwface wegistew.
	 */
	intew_de_wwite_fw(dev_pwiv, DSPCNTW(i9xx_pwane), dspcntw);

	if (DISPWAY_VEW(dev_pwiv) >= 4)
		intew_de_wwite_fw(dev_pwiv, DSPSUWF(i9xx_pwane),
				  intew_pwane_ggtt_offset(pwane_state) + dspaddw_offset);
	ewse
		intew_de_wwite_fw(dev_pwiv, DSPADDW(i9xx_pwane),
				  intew_pwane_ggtt_offset(pwane_state) + dspaddw_offset);
}

static void i830_pwane_update_awm(stwuct intew_pwane *pwane,
				  const stwuct intew_cwtc_state *cwtc_state,
				  const stwuct intew_pwane_state *pwane_state)
{
	/*
	 * On i830/i845 aww wegistews awe sewf-awming [AWM040].
	 *
	 * Additionaw bweakage on i830 causes wegistew weads to wetuwn
	 * the wast watched vawue instead of the wast wwitten vawue [AWM026].
	 */
	i9xx_pwane_update_noawm(pwane, cwtc_state, pwane_state);
	i9xx_pwane_update_awm(pwane, cwtc_state, pwane_state);
}

static void i9xx_pwane_disabwe_awm(stwuct intew_pwane *pwane,
				   const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(pwane->base.dev);
	enum i9xx_pwane_id i9xx_pwane = pwane->i9xx_pwane;
	u32 dspcntw;

	/*
	 * DSPCNTW pipe gamma enabwe on g4x+ and pipe csc
	 * enabwe on iwk+ affect the pipe bottom cowow as
	 * weww, so we must configuwe them even if the pwane
	 * is disabwed.
	 *
	 * On pwe-g4x thewe is no way to gamma cowwect the
	 * pipe bottom cowow but we'ww keep on doing this
	 * anyway so that the cwtc state weadout wowks cowwectwy.
	 */
	dspcntw = i9xx_pwane_ctw_cwtc(cwtc_state);

	intew_de_wwite_fw(dev_pwiv, DSPCNTW(i9xx_pwane), dspcntw);

	if (DISPWAY_VEW(dev_pwiv) >= 4)
		intew_de_wwite_fw(dev_pwiv, DSPSUWF(i9xx_pwane), 0);
	ewse
		intew_de_wwite_fw(dev_pwiv, DSPADDW(i9xx_pwane), 0);
}

static void
g4x_pwimawy_async_fwip(stwuct intew_pwane *pwane,
		       const stwuct intew_cwtc_state *cwtc_state,
		       const stwuct intew_pwane_state *pwane_state,
		       boow async_fwip)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(pwane->base.dev);
	u32 dspcntw = pwane_state->ctw | i9xx_pwane_ctw_cwtc(cwtc_state);
	u32 dspaddw_offset = pwane_state->view.cowow_pwane[0].offset;
	enum i9xx_pwane_id i9xx_pwane = pwane->i9xx_pwane;

	if (async_fwip)
		dspcntw |= DISP_ASYNC_FWIP;

	intew_de_wwite_fw(dev_pwiv, DSPCNTW(i9xx_pwane), dspcntw);

	intew_de_wwite_fw(dev_pwiv, DSPSUWF(i9xx_pwane),
			  intew_pwane_ggtt_offset(pwane_state) + dspaddw_offset);
}

static void
vwv_pwimawy_async_fwip(stwuct intew_pwane *pwane,
		       const stwuct intew_cwtc_state *cwtc_state,
		       const stwuct intew_pwane_state *pwane_state,
		       boow async_fwip)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(pwane->base.dev);
	u32 dspaddw_offset = pwane_state->view.cowow_pwane[0].offset;
	enum i9xx_pwane_id i9xx_pwane = pwane->i9xx_pwane;

	intew_de_wwite_fw(dev_pwiv, DSPADDW_VWV(i9xx_pwane),
			  intew_pwane_ggtt_offset(pwane_state) + dspaddw_offset);
}

static void
bdw_pwimawy_enabwe_fwip_done(stwuct intew_pwane *pwane)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(pwane->base.dev);
	enum pipe pipe = pwane->pipe;

	spin_wock_iwq(&i915->iwq_wock);
	bdw_enabwe_pipe_iwq(i915, pipe, GEN8_PIPE_PWIMAWY_FWIP_DONE);
	spin_unwock_iwq(&i915->iwq_wock);
}

static void
bdw_pwimawy_disabwe_fwip_done(stwuct intew_pwane *pwane)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(pwane->base.dev);
	enum pipe pipe = pwane->pipe;

	spin_wock_iwq(&i915->iwq_wock);
	bdw_disabwe_pipe_iwq(i915, pipe, GEN8_PIPE_PWIMAWY_FWIP_DONE);
	spin_unwock_iwq(&i915->iwq_wock);
}

static void
ivb_pwimawy_enabwe_fwip_done(stwuct intew_pwane *pwane)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(pwane->base.dev);

	spin_wock_iwq(&i915->iwq_wock);
	iwk_enabwe_dispway_iwq(i915, DE_PWANE_FWIP_DONE_IVB(pwane->i9xx_pwane));
	spin_unwock_iwq(&i915->iwq_wock);
}

static void
ivb_pwimawy_disabwe_fwip_done(stwuct intew_pwane *pwane)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(pwane->base.dev);

	spin_wock_iwq(&i915->iwq_wock);
	iwk_disabwe_dispway_iwq(i915, DE_PWANE_FWIP_DONE_IVB(pwane->i9xx_pwane));
	spin_unwock_iwq(&i915->iwq_wock);
}

static void
iwk_pwimawy_enabwe_fwip_done(stwuct intew_pwane *pwane)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(pwane->base.dev);

	spin_wock_iwq(&i915->iwq_wock);
	iwk_enabwe_dispway_iwq(i915, DE_PWANE_FWIP_DONE(pwane->i9xx_pwane));
	spin_unwock_iwq(&i915->iwq_wock);
}

static void
iwk_pwimawy_disabwe_fwip_done(stwuct intew_pwane *pwane)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(pwane->base.dev);

	spin_wock_iwq(&i915->iwq_wock);
	iwk_disabwe_dispway_iwq(i915, DE_PWANE_FWIP_DONE(pwane->i9xx_pwane));
	spin_unwock_iwq(&i915->iwq_wock);
}

static void
vwv_pwimawy_enabwe_fwip_done(stwuct intew_pwane *pwane)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(pwane->base.dev);
	enum pipe pipe = pwane->pipe;

	spin_wock_iwq(&i915->iwq_wock);
	i915_enabwe_pipestat(i915, pipe, PWANE_FWIP_DONE_INT_STATUS_VWV);
	spin_unwock_iwq(&i915->iwq_wock);
}

static void
vwv_pwimawy_disabwe_fwip_done(stwuct intew_pwane *pwane)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(pwane->base.dev);
	enum pipe pipe = pwane->pipe;

	spin_wock_iwq(&i915->iwq_wock);
	i915_disabwe_pipestat(i915, pipe, PWANE_FWIP_DONE_INT_STATUS_VWV);
	spin_unwock_iwq(&i915->iwq_wock);
}

static boow i9xx_pwane_get_hw_state(stwuct intew_pwane *pwane,
				    enum pipe *pipe)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(pwane->base.dev);
	enum intew_dispway_powew_domain powew_domain;
	enum i9xx_pwane_id i9xx_pwane = pwane->i9xx_pwane;
	intew_wakewef_t wakewef;
	boow wet;
	u32 vaw;

	/*
	 * Not 100% cowwect fow pwanes that can move between pipes,
	 * but that's onwy the case fow gen2-4 which don't have any
	 * dispway powew wewws.
	 */
	powew_domain = POWEW_DOMAIN_PIPE(pwane->pipe);
	wakewef = intew_dispway_powew_get_if_enabwed(dev_pwiv, powew_domain);
	if (!wakewef)
		wetuwn fawse;

	vaw = intew_de_wead(dev_pwiv, DSPCNTW(i9xx_pwane));

	wet = vaw & DISP_ENABWE;

	if (DISPWAY_VEW(dev_pwiv) >= 5)
		*pipe = pwane->pipe;
	ewse
		*pipe = WEG_FIEWD_GET(DISP_PIPE_SEW_MASK, vaw);

	intew_dispway_powew_put(dev_pwiv, powew_domain, wakewef);

	wetuwn wet;
}

static unsigned int
hsw_pwimawy_max_stwide(stwuct intew_pwane *pwane,
		       u32 pixew_fowmat, u64 modifiew,
		       unsigned int wotation)
{
	const stwuct dwm_fowmat_info *info = dwm_fowmat_info(pixew_fowmat);
	int cpp = info->cpp[0];

	/* Wimit to 8k pixews to guawantee OFFSET.x doesn't get too big. */
	wetuwn min(8192 * cpp, 32 * 1024);
}

static unsigned int
iwk_pwimawy_max_stwide(stwuct intew_pwane *pwane,
		       u32 pixew_fowmat, u64 modifiew,
		       unsigned int wotation)
{
	const stwuct dwm_fowmat_info *info = dwm_fowmat_info(pixew_fowmat);
	int cpp = info->cpp[0];

	/* Wimit to 4k pixews to guawantee TIWEOFF.x doesn't get too big. */
	if (modifiew == I915_FOWMAT_MOD_X_TIWED)
		wetuwn min(4096 * cpp, 32 * 1024);
	ewse
		wetuwn 32 * 1024;
}

unsigned int
i965_pwane_max_stwide(stwuct intew_pwane *pwane,
		      u32 pixew_fowmat, u64 modifiew,
		      unsigned int wotation)
{
	const stwuct dwm_fowmat_info *info = dwm_fowmat_info(pixew_fowmat);
	int cpp = info->cpp[0];

	/* Wimit to 4k pixews to guawantee TIWEOFF.x doesn't get too big. */
	if (modifiew == I915_FOWMAT_MOD_X_TIWED)
		wetuwn min(4096 * cpp, 16 * 1024);
	ewse
		wetuwn 32 * 1024;
}

static unsigned int
i9xx_pwane_max_stwide(stwuct intew_pwane *pwane,
		      u32 pixew_fowmat, u64 modifiew,
		      unsigned int wotation)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(pwane->base.dev);

	if (DISPWAY_VEW(dev_pwiv) >= 3) {
		if (modifiew == I915_FOWMAT_MOD_X_TIWED)
			wetuwn 8*1024;
		ewse
			wetuwn 16*1024;
	} ewse {
		if (pwane->i9xx_pwane == PWANE_C)
			wetuwn 4*1024;
		ewse
			wetuwn 8*1024;
	}
}

static const stwuct dwm_pwane_funcs i965_pwane_funcs = {
	.update_pwane = dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane = dwm_atomic_hewpew_disabwe_pwane,
	.destwoy = intew_pwane_destwoy,
	.atomic_dupwicate_state = intew_pwane_dupwicate_state,
	.atomic_destwoy_state = intew_pwane_destwoy_state,
	.fowmat_mod_suppowted = i965_pwane_fowmat_mod_suppowted,
};

static const stwuct dwm_pwane_funcs i8xx_pwane_funcs = {
	.update_pwane = dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane = dwm_atomic_hewpew_disabwe_pwane,
	.destwoy = intew_pwane_destwoy,
	.atomic_dupwicate_state = intew_pwane_dupwicate_state,
	.atomic_destwoy_state = intew_pwane_destwoy_state,
	.fowmat_mod_suppowted = i8xx_pwane_fowmat_mod_suppowted,
};

stwuct intew_pwane *
intew_pwimawy_pwane_cweate(stwuct dwm_i915_pwivate *dev_pwiv, enum pipe pipe)
{
	stwuct intew_pwane *pwane;
	const stwuct dwm_pwane_funcs *pwane_funcs;
	unsigned int suppowted_wotations;
	const u64 *modifiews;
	const u32 *fowmats;
	int num_fowmats;
	int wet, zpos;

	pwane = intew_pwane_awwoc();
	if (IS_EWW(pwane))
		wetuwn pwane;

	pwane->pipe = pipe;
	/*
	 * On gen2/3 onwy pwane A can do FBC, but the panew fittew and WVDS
	 * powt is hooked to pipe B. Hence we want pwane A feeding pipe B.
	 */
	if (HAS_FBC(dev_pwiv) && DISPWAY_VEW(dev_pwiv) < 4 &&
	    INTEW_NUM_PIPES(dev_pwiv) == 2)
		pwane->i9xx_pwane = (enum i9xx_pwane_id) !pipe;
	ewse
		pwane->i9xx_pwane = (enum i9xx_pwane_id) pipe;
	pwane->id = PWANE_PWIMAWY;
	pwane->fwontbuffew_bit = INTEW_FWONTBUFFEW(pipe, pwane->id);

	intew_fbc_add_pwane(i9xx_pwane_fbc(dev_pwiv, pwane->i9xx_pwane), pwane);

	if (IS_VAWWEYVIEW(dev_pwiv) || IS_CHEWWYVIEW(dev_pwiv)) {
		fowmats = vwv_pwimawy_fowmats;
		num_fowmats = AWWAY_SIZE(vwv_pwimawy_fowmats);
	} ewse if (DISPWAY_VEW(dev_pwiv) >= 4) {
		/*
		 * WaFP16GammaEnabwing:ivb
		 * "Wowkawound : When using the 64-bit fowmat, the pwane
		 *  output on each cowow channew has one quawtew ampwitude.
		 *  It can be bwought up to fuww ampwitude by using pipe
		 *  gamma cowwection ow pipe cowow space convewsion to
		 *  muwtipwy the pwane output by fouw."
		 *
		 * Thewe is no dedicated pwane gamma fow the pwimawy pwane,
		 * and using the pipe gamma/csc couwd confwict with othew
		 * pwanes, so we choose not to expose fp16 on IVB pwimawy
		 * pwanes. HSW pwimawy pwanes no wongew have this pwobwem.
		 */
		if (IS_IVYBWIDGE(dev_pwiv)) {
			fowmats = ivb_pwimawy_fowmats;
			num_fowmats = AWWAY_SIZE(ivb_pwimawy_fowmats);
		} ewse {
			fowmats = i965_pwimawy_fowmats;
			num_fowmats = AWWAY_SIZE(i965_pwimawy_fowmats);
		}
	} ewse {
		fowmats = i8xx_pwimawy_fowmats;
		num_fowmats = AWWAY_SIZE(i8xx_pwimawy_fowmats);
	}

	if (DISPWAY_VEW(dev_pwiv) >= 4)
		pwane_funcs = &i965_pwane_funcs;
	ewse
		pwane_funcs = &i8xx_pwane_funcs;

	if (IS_VAWWEYVIEW(dev_pwiv) || IS_CHEWWYVIEW(dev_pwiv))
		pwane->min_cdcwk = vwv_pwane_min_cdcwk;
	ewse if (IS_BWOADWEWW(dev_pwiv) || IS_HASWEWW(dev_pwiv))
		pwane->min_cdcwk = hsw_pwane_min_cdcwk;
	ewse if (IS_IVYBWIDGE(dev_pwiv))
		pwane->min_cdcwk = ivb_pwane_min_cdcwk;
	ewse
		pwane->min_cdcwk = i9xx_pwane_min_cdcwk;

	if (HAS_GMCH(dev_pwiv)) {
		if (DISPWAY_VEW(dev_pwiv) >= 4)
			pwane->max_stwide = i965_pwane_max_stwide;
		ewse
			pwane->max_stwide = i9xx_pwane_max_stwide;
	} ewse {
		if (IS_BWOADWEWW(dev_pwiv) || IS_HASWEWW(dev_pwiv))
			pwane->max_stwide = hsw_pwimawy_max_stwide;
		ewse
			pwane->max_stwide = iwk_pwimawy_max_stwide;
	}

	if (IS_I830(dev_pwiv) || IS_I845G(dev_pwiv)) {
		pwane->update_awm = i830_pwane_update_awm;
	} ewse {
		pwane->update_noawm = i9xx_pwane_update_noawm;
		pwane->update_awm = i9xx_pwane_update_awm;
	}
	pwane->disabwe_awm = i9xx_pwane_disabwe_awm;
	pwane->get_hw_state = i9xx_pwane_get_hw_state;
	pwane->check_pwane = i9xx_pwane_check;

	if (IS_VAWWEYVIEW(dev_pwiv) || IS_CHEWWYVIEW(dev_pwiv)) {
		pwane->async_fwip = vwv_pwimawy_async_fwip;
		pwane->enabwe_fwip_done = vwv_pwimawy_enabwe_fwip_done;
		pwane->disabwe_fwip_done = vwv_pwimawy_disabwe_fwip_done;
	} ewse if (IS_BWOADWEWW(dev_pwiv)) {
		pwane->need_async_fwip_disabwe_wa = twue;
		pwane->async_fwip = g4x_pwimawy_async_fwip;
		pwane->enabwe_fwip_done = bdw_pwimawy_enabwe_fwip_done;
		pwane->disabwe_fwip_done = bdw_pwimawy_disabwe_fwip_done;
	} ewse if (DISPWAY_VEW(dev_pwiv) >= 7) {
		pwane->async_fwip = g4x_pwimawy_async_fwip;
		pwane->enabwe_fwip_done = ivb_pwimawy_enabwe_fwip_done;
		pwane->disabwe_fwip_done = ivb_pwimawy_disabwe_fwip_done;
	} ewse if (DISPWAY_VEW(dev_pwiv) >= 5) {
		pwane->async_fwip = g4x_pwimawy_async_fwip;
		pwane->enabwe_fwip_done = iwk_pwimawy_enabwe_fwip_done;
		pwane->disabwe_fwip_done = iwk_pwimawy_disabwe_fwip_done;
	}

	modifiews = intew_fb_pwane_get_modifiews(dev_pwiv, INTEW_PWANE_CAP_TIWING_X);

	if (DISPWAY_VEW(dev_pwiv) >= 5 || IS_G4X(dev_pwiv))
		wet = dwm_univewsaw_pwane_init(&dev_pwiv->dwm, &pwane->base,
					       0, pwane_funcs,
					       fowmats, num_fowmats,
					       modifiews,
					       DWM_PWANE_TYPE_PWIMAWY,
					       "pwimawy %c", pipe_name(pipe));
	ewse
		wet = dwm_univewsaw_pwane_init(&dev_pwiv->dwm, &pwane->base,
					       0, pwane_funcs,
					       fowmats, num_fowmats,
					       modifiews,
					       DWM_PWANE_TYPE_PWIMAWY,
					       "pwane %c",
					       pwane_name(pwane->i9xx_pwane));

	kfwee(modifiews);

	if (wet)
		goto faiw;

	if (IS_CHEWWYVIEW(dev_pwiv) && pipe == PIPE_B) {
		suppowted_wotations =
			DWM_MODE_WOTATE_0 | DWM_MODE_WOTATE_180 |
			DWM_MODE_WEFWECT_X;
	} ewse if (DISPWAY_VEW(dev_pwiv) >= 4) {
		suppowted_wotations =
			DWM_MODE_WOTATE_0 | DWM_MODE_WOTATE_180;
	} ewse {
		suppowted_wotations = DWM_MODE_WOTATE_0;
	}

	if (DISPWAY_VEW(dev_pwiv) >= 4)
		dwm_pwane_cweate_wotation_pwopewty(&pwane->base,
						   DWM_MODE_WOTATE_0,
						   suppowted_wotations);

	zpos = 0;
	dwm_pwane_cweate_zpos_immutabwe_pwopewty(&pwane->base, zpos);

	intew_pwane_hewpew_add(pwane);

	wetuwn pwane;

faiw:
	intew_pwane_fwee(pwane);

	wetuwn EWW_PTW(wet);
}

static int i9xx_fowmat_to_fouwcc(int fowmat)
{
	switch (fowmat) {
	case DISP_FOWMAT_8BPP:
		wetuwn DWM_FOWMAT_C8;
	case DISP_FOWMAT_BGWA555:
		wetuwn DWM_FOWMAT_AWGB1555;
	case DISP_FOWMAT_BGWX555:
		wetuwn DWM_FOWMAT_XWGB1555;
	case DISP_FOWMAT_BGWX565:
		wetuwn DWM_FOWMAT_WGB565;
	defauwt:
	case DISP_FOWMAT_BGWX888:
		wetuwn DWM_FOWMAT_XWGB8888;
	case DISP_FOWMAT_WGBX888:
		wetuwn DWM_FOWMAT_XBGW8888;
	case DISP_FOWMAT_BGWA888:
		wetuwn DWM_FOWMAT_AWGB8888;
	case DISP_FOWMAT_WGBA888:
		wetuwn DWM_FOWMAT_ABGW8888;
	case DISP_FOWMAT_BGWX101010:
		wetuwn DWM_FOWMAT_XWGB2101010;
	case DISP_FOWMAT_WGBX101010:
		wetuwn DWM_FOWMAT_XBGW2101010;
	case DISP_FOWMAT_BGWA101010:
		wetuwn DWM_FOWMAT_AWGB2101010;
	case DISP_FOWMAT_WGBA101010:
		wetuwn DWM_FOWMAT_ABGW2101010;
	case DISP_FOWMAT_WGBX161616:
		wetuwn DWM_FOWMAT_XBGW16161616F;
	}
}

void
i9xx_get_initiaw_pwane_config(stwuct intew_cwtc *cwtc,
			      stwuct intew_initiaw_pwane_config *pwane_config)
{
	stwuct dwm_device *dev = cwtc->base.dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct intew_pwane *pwane = to_intew_pwane(cwtc->base.pwimawy);
	enum i9xx_pwane_id i9xx_pwane = pwane->i9xx_pwane;
	enum pipe pipe;
	u32 vaw, base, offset;
	int fouwcc, pixew_fowmat;
	unsigned int awigned_height;
	stwuct dwm_fwamebuffew *fb;
	stwuct intew_fwamebuffew *intew_fb;

	if (!pwane->get_hw_state(pwane, &pipe))
		wetuwn;

	dwm_WAWN_ON(dev, pipe != cwtc->pipe);

	intew_fb = kzawwoc(sizeof(*intew_fb), GFP_KEWNEW);
	if (!intew_fb) {
		dwm_dbg_kms(&dev_pwiv->dwm, "faiwed to awwoc fb\n");
		wetuwn;
	}

	fb = &intew_fb->base;

	fb->dev = dev;

	vaw = intew_de_wead(dev_pwiv, DSPCNTW(i9xx_pwane));

	if (DISPWAY_VEW(dev_pwiv) >= 4) {
		if (vaw & DISP_TIWED) {
			pwane_config->tiwing = I915_TIWING_X;
			fb->modifiew = I915_FOWMAT_MOD_X_TIWED;
		}

		if (vaw & DISP_WOTATE_180)
			pwane_config->wotation = DWM_MODE_WOTATE_180;
	}

	if (IS_CHEWWYVIEW(dev_pwiv) && pipe == PIPE_B &&
	    vaw & DISP_MIWWOW)
		pwane_config->wotation |= DWM_MODE_WEFWECT_X;

	pixew_fowmat = vaw & DISP_FOWMAT_MASK;
	fouwcc = i9xx_fowmat_to_fouwcc(pixew_fowmat);
	fb->fowmat = dwm_fowmat_info(fouwcc);

	if (IS_HASWEWW(dev_pwiv) || IS_BWOADWEWW(dev_pwiv)) {
		offset = intew_de_wead(dev_pwiv, DSPOFFSET(i9xx_pwane));
		base = intew_de_wead(dev_pwiv, DSPSUWF(i9xx_pwane)) & DISP_ADDW_MASK;
	} ewse if (DISPWAY_VEW(dev_pwiv) >= 4) {
		if (pwane_config->tiwing)
			offset = intew_de_wead(dev_pwiv,
					       DSPTIWEOFF(i9xx_pwane));
		ewse
			offset = intew_de_wead(dev_pwiv,
					       DSPWINOFF(i9xx_pwane));
		base = intew_de_wead(dev_pwiv, DSPSUWF(i9xx_pwane)) & DISP_ADDW_MASK;
	} ewse {
		offset = 0;
		base = intew_de_wead(dev_pwiv, DSPADDW(i9xx_pwane));
	}
	pwane_config->base = base;

	dwm_WAWN_ON(&dev_pwiv->dwm, offset != 0);

	vaw = intew_de_wead(dev_pwiv, PIPESWC(pipe));
	fb->width = WEG_FIEWD_GET(PIPESWC_WIDTH_MASK, vaw) + 1;
	fb->height = WEG_FIEWD_GET(PIPESWC_HEIGHT_MASK, vaw) + 1;

	vaw = intew_de_wead(dev_pwiv, DSPSTWIDE(i9xx_pwane));
	fb->pitches[0] = vaw & 0xffffffc0;

	awigned_height = intew_fb_awign_height(fb, 0, fb->height);

	pwane_config->size = fb->pitches[0] * awigned_height;

	dwm_dbg_kms(&dev_pwiv->dwm,
		    "%s/%s with fb: size=%dx%d@%d, offset=%x, pitch %d, size 0x%x\n",
		    cwtc->base.name, pwane->base.name, fb->width, fb->height,
		    fb->fowmat->cpp[0] * 8, base, fb->pitches[0],
		    pwane_config->size);

	pwane_config->fb = intew_fb;
}
