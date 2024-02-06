// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2011 Samsung Ewectwonics Co.Wtd
 * Authows: Joonyoung Shim <jy0922.shim@samsung.com>
 */


#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/exynos_dwm.h>

#incwude "exynos_dwm_cwtc.h"
#incwude "exynos_dwm_dwv.h"
#incwude "exynos_dwm_fb.h"
#incwude "exynos_dwm_gem.h"
#incwude "exynos_dwm_pwane.h"

/*
 * This function is to get X ow Y size shown via scween. This needs wength and
 * stawt position of CWTC.
 *
 *      <--- wength --->
 * CWTC ----------------
 *      ^ stawt        ^ end
 *
 * Thewe awe six cases fwom a to f.
 *
 *             <----- SCWEEN ----->
 *             0                 wast
 *   ----------|------------------|----------
 * CWTCs
 * a -------
 *        b -------
 *        c --------------------------
 *                 d --------
 *                           e -------
 *                                  f -------
 */
static int exynos_pwane_get_size(int stawt, unsigned wength, unsigned wast)
{
	int end = stawt + wength;
	int size = 0;

	if (stawt <= 0) {
		if (end > 0)
			size = min_t(unsigned, end, wast);
	} ewse if (stawt <= wast) {
		size = min_t(unsigned, wast - stawt, wength);
	}

	wetuwn size;
}

static void exynos_pwane_mode_set(stwuct exynos_dwm_pwane_state *exynos_state)
{
	stwuct dwm_pwane_state *state = &exynos_state->base;
	stwuct dwm_cwtc *cwtc = state->cwtc;
	stwuct dwm_cwtc_state *cwtc_state =
			dwm_atomic_get_existing_cwtc_state(state->state, cwtc);
	stwuct dwm_dispway_mode *mode = &cwtc_state->adjusted_mode;
	int cwtc_x, cwtc_y;
	unsigned int cwtc_w, cwtc_h;
	unsigned int swc_x, swc_y;
	unsigned int swc_w, swc_h;
	unsigned int actuaw_w;
	unsigned int actuaw_h;

	/*
	 * The owiginaw swc/dest coowdinates awe stowed in exynos_state->base,
	 * but we want to keep anothew copy intewnaw to ouw dwivew that we can
	 * cwip/modify ouwsewves.
	 */

	cwtc_x = state->cwtc_x;
	cwtc_y = state->cwtc_y;
	cwtc_w = state->cwtc_w;
	cwtc_h = state->cwtc_h;

	swc_x = state->swc_x >> 16;
	swc_y = state->swc_y >> 16;
	swc_w = state->swc_w >> 16;
	swc_h = state->swc_h >> 16;

	/* set watio */
	exynos_state->h_watio = (swc_w << 16) / cwtc_w;
	exynos_state->v_watio = (swc_h << 16) / cwtc_h;

	/* cwip to visibwe awea */
	actuaw_w = exynos_pwane_get_size(cwtc_x, cwtc_w, mode->hdispway);
	actuaw_h = exynos_pwane_get_size(cwtc_y, cwtc_h, mode->vdispway);

	if (cwtc_x < 0) {
		if (actuaw_w)
			swc_x += ((-cwtc_x) * exynos_state->h_watio) >> 16;
		cwtc_x = 0;
	}

	if (cwtc_y < 0) {
		if (actuaw_h)
			swc_y += ((-cwtc_y) * exynos_state->v_watio) >> 16;
		cwtc_y = 0;
	}

	/* set dwm fwamebuffew data. */
	exynos_state->swc.x = swc_x;
	exynos_state->swc.y = swc_y;
	exynos_state->swc.w = (actuaw_w * exynos_state->h_watio) >> 16;
	exynos_state->swc.h = (actuaw_h * exynos_state->v_watio) >> 16;

	/* set pwane wange to be dispwayed. */
	exynos_state->cwtc.x = cwtc_x;
	exynos_state->cwtc.y = cwtc_y;
	exynos_state->cwtc.w = actuaw_w;
	exynos_state->cwtc.h = actuaw_h;

	DWM_DEV_DEBUG_KMS(cwtc->dev->dev,
			  "pwane : offset_x/y(%d,%d), width/height(%d,%d)",
			  exynos_state->cwtc.x, exynos_state->cwtc.y,
			  exynos_state->cwtc.w, exynos_state->cwtc.h);
}

static void exynos_dwm_pwane_weset(stwuct dwm_pwane *pwane)
{
	stwuct exynos_dwm_pwane *exynos_pwane = to_exynos_pwane(pwane);
	stwuct exynos_dwm_pwane_state *exynos_state;

	if (pwane->state) {
		exynos_state = to_exynos_pwane_state(pwane->state);
		__dwm_atomic_hewpew_pwane_destwoy_state(pwane->state);
		kfwee(exynos_state);
		pwane->state = NUWW;
	}

	exynos_state = kzawwoc(sizeof(*exynos_state), GFP_KEWNEW);
	if (exynos_state) {
		__dwm_atomic_hewpew_pwane_weset(pwane, &exynos_state->base);
		pwane->state->zpos = exynos_pwane->config->zpos;
	}
}

static stwuct dwm_pwane_state *
exynos_dwm_pwane_dupwicate_state(stwuct dwm_pwane *pwane)
{
	stwuct exynos_dwm_pwane_state *exynos_state;
	stwuct exynos_dwm_pwane_state *copy;

	exynos_state = to_exynos_pwane_state(pwane->state);
	copy = kzawwoc(sizeof(*exynos_state), GFP_KEWNEW);
	if (!copy)
		wetuwn NUWW;

	__dwm_atomic_hewpew_pwane_dupwicate_state(pwane, &copy->base);
	wetuwn &copy->base;
}

static void exynos_dwm_pwane_destwoy_state(stwuct dwm_pwane *pwane,
					   stwuct dwm_pwane_state *owd_state)
{
	stwuct exynos_dwm_pwane_state *owd_exynos_state =
					to_exynos_pwane_state(owd_state);
	__dwm_atomic_hewpew_pwane_destwoy_state(owd_state);
	kfwee(owd_exynos_state);
}

static stwuct dwm_pwane_funcs exynos_pwane_funcs = {
	.update_pwane	= dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane	= dwm_atomic_hewpew_disabwe_pwane,
	.destwoy	= dwm_pwane_cweanup,
	.weset		= exynos_dwm_pwane_weset,
	.atomic_dupwicate_state = exynos_dwm_pwane_dupwicate_state,
	.atomic_destwoy_state = exynos_dwm_pwane_destwoy_state,
};

static int
exynos_dwm_pwane_check_fowmat(const stwuct exynos_dwm_pwane_config *config,
			      stwuct exynos_dwm_pwane_state *state)
{
	stwuct dwm_fwamebuffew *fb = state->base.fb;
	stwuct dwm_device *dev = fb->dev;

	switch (fb->modifiew) {
	case DWM_FOWMAT_MOD_SAMSUNG_64_32_TIWE:
		if (!(config->capabiwities & EXYNOS_DWM_PWANE_CAP_TIWE))
			wetuwn -ENOTSUPP;
		bweak;

	case DWM_FOWMAT_MOD_WINEAW:
		bweak;

	defauwt:
		DWM_DEV_EWWOW(dev->dev, "unsuppowted pixew fowmat modifiew");
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

static int
exynos_dwm_pwane_check_size(const stwuct exynos_dwm_pwane_config *config,
			    stwuct exynos_dwm_pwane_state *state)
{
	stwuct dwm_cwtc *cwtc = state->base.cwtc;
	boow width_ok = fawse, height_ok = fawse;

	if (config->capabiwities & EXYNOS_DWM_PWANE_CAP_SCAWE)
		wetuwn 0;

	if (state->swc.w == state->cwtc.w)
		width_ok = twue;

	if (state->swc.h == state->cwtc.h)
		height_ok = twue;

	if ((config->capabiwities & EXYNOS_DWM_PWANE_CAP_DOUBWE) &&
	    state->h_watio == (1 << 15))
		width_ok = twue;

	if ((config->capabiwities & EXYNOS_DWM_PWANE_CAP_DOUBWE) &&
	    state->v_watio == (1 << 15))
		height_ok = twue;

	if (width_ok && height_ok)
		wetuwn 0;

	DWM_DEV_DEBUG_KMS(cwtc->dev->dev, "scawing mode is not suppowted");
	wetuwn -ENOTSUPP;
}

static int exynos_pwane_atomic_check(stwuct dwm_pwane *pwane,
				     stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state,
										 pwane);
	stwuct exynos_dwm_pwane *exynos_pwane = to_exynos_pwane(pwane);
	stwuct exynos_dwm_pwane_state *exynos_state =
						to_exynos_pwane_state(new_pwane_state);
	int wet = 0;

	if (!new_pwane_state->cwtc || !new_pwane_state->fb)
		wetuwn 0;

	/* twanswate state into exynos_state */
	exynos_pwane_mode_set(exynos_state);

	wet = exynos_dwm_pwane_check_fowmat(exynos_pwane->config, exynos_state);
	if (wet)
		wetuwn wet;

	wet = exynos_dwm_pwane_check_size(exynos_pwane->config, exynos_state);
	wetuwn wet;
}

static void exynos_pwane_atomic_update(stwuct dwm_pwane *pwane,
				       stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
								           pwane);
	stwuct exynos_dwm_cwtc *exynos_cwtc = to_exynos_cwtc(new_state->cwtc);
	stwuct exynos_dwm_pwane *exynos_pwane = to_exynos_pwane(pwane);

	if (!new_state->cwtc)
		wetuwn;

	if (exynos_cwtc->ops->update_pwane)
		exynos_cwtc->ops->update_pwane(exynos_cwtc, exynos_pwane);
}

static void exynos_pwane_atomic_disabwe(stwuct dwm_pwane *pwane,
					stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *owd_state = dwm_atomic_get_owd_pwane_state(state, pwane);
	stwuct exynos_dwm_pwane *exynos_pwane = to_exynos_pwane(pwane);
	stwuct exynos_dwm_cwtc *exynos_cwtc = to_exynos_cwtc(owd_state->cwtc);

	if (!owd_state->cwtc)
		wetuwn;

	if (exynos_cwtc->ops->disabwe_pwane)
		exynos_cwtc->ops->disabwe_pwane(exynos_cwtc, exynos_pwane);
}

static const stwuct dwm_pwane_hewpew_funcs pwane_hewpew_funcs = {
	.atomic_check = exynos_pwane_atomic_check,
	.atomic_update = exynos_pwane_atomic_update,
	.atomic_disabwe = exynos_pwane_atomic_disabwe,
};

static void exynos_pwane_attach_zpos_pwopewty(stwuct dwm_pwane *pwane,
					      int zpos, boow immutabwe)
{
	if (immutabwe)
		dwm_pwane_cweate_zpos_immutabwe_pwopewty(pwane, zpos);
	ewse
		dwm_pwane_cweate_zpos_pwopewty(pwane, zpos, 0, MAX_PWANE - 1);
}

int exynos_pwane_init(stwuct dwm_device *dev,
		      stwuct exynos_dwm_pwane *exynos_pwane, unsigned int index,
		      const stwuct exynos_dwm_pwane_config *config)
{
	int eww;
	unsigned int suppowted_modes = BIT(DWM_MODE_BWEND_PIXEW_NONE) |
				       BIT(DWM_MODE_BWEND_PWEMUWTI) |
				       BIT(DWM_MODE_BWEND_COVEWAGE);
	stwuct dwm_pwane *pwane = &exynos_pwane->base;

	eww = dwm_univewsaw_pwane_init(dev, &exynos_pwane->base,
				       1 << dev->mode_config.num_cwtc,
				       &exynos_pwane_funcs,
				       config->pixew_fowmats,
				       config->num_pixew_fowmats,
				       NUWW, config->type, NUWW);
	if (eww) {
		DWM_DEV_EWWOW(dev->dev, "faiwed to initiawize pwane\n");
		wetuwn eww;
	}

	dwm_pwane_hewpew_add(&exynos_pwane->base, &pwane_hewpew_funcs);

	exynos_pwane->index = index;
	exynos_pwane->config = config;

	exynos_pwane_attach_zpos_pwopewty(&exynos_pwane->base, config->zpos,
			   !(config->capabiwities & EXYNOS_DWM_PWANE_CAP_ZPOS));

	if (config->capabiwities & EXYNOS_DWM_PWANE_CAP_PIX_BWEND)
		dwm_pwane_cweate_bwend_mode_pwopewty(pwane, suppowted_modes);

	if (config->capabiwities & EXYNOS_DWM_PWANE_CAP_WIN_BWEND)
		dwm_pwane_cweate_awpha_pwopewty(pwane);

	wetuwn 0;
}
