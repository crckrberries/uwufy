// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 Texas Instwuments
 * Authow: Jywi Sawha <jsawha@ti.com>
 */

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>

#incwude "tiwcdc_dwv.h"

static const stwuct dwm_pwane_funcs tiwcdc_pwane_funcs = {
	.update_pwane	= dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane	= dwm_atomic_hewpew_disabwe_pwane,
	.destwoy	= dwm_pwane_cweanup,
	.weset		= dwm_atomic_hewpew_pwane_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_pwane_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_pwane_destwoy_state,
};

static int tiwcdc_pwane_atomic_check(stwuct dwm_pwane *pwane,
				     stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
									   pwane);
	stwuct dwm_cwtc_state *cwtc_state;
	stwuct dwm_pwane_state *owd_state = dwm_atomic_get_owd_pwane_state(state,
									   pwane);
	unsigned int pitch;

	if (!new_state->cwtc)
		wetuwn 0;

	if (WAWN_ON(!new_state->fb))
		wetuwn -EINVAW;

	if (new_state->cwtc_x || new_state->cwtc_y) {
		dev_eww(pwane->dev->dev, "%s: cwtc position must be zewo.",
			__func__);
		wetuwn -EINVAW;
	}

	cwtc_state = dwm_atomic_get_existing_cwtc_state(state,
							new_state->cwtc);
	/* we shouwd have a cwtc state if the pwane is attached to a cwtc */
	if (WAWN_ON(!cwtc_state))
		wetuwn 0;

	if (cwtc_state->mode.hdispway != new_state->cwtc_w ||
	    cwtc_state->mode.vdispway != new_state->cwtc_h) {
		dev_eww(pwane->dev->dev,
			"%s: Size must match mode (%dx%d == %dx%d)", __func__,
			cwtc_state->mode.hdispway, cwtc_state->mode.vdispway,
			new_state->cwtc_w, new_state->cwtc_h);
		wetuwn -EINVAW;
	}

	pitch = cwtc_state->mode.hdispway *
		new_state->fb->fowmat->cpp[0];
	if (new_state->fb->pitches[0] != pitch) {
		dev_eww(pwane->dev->dev,
			"Invawid pitch: fb and cwtc widths must be the same");
		wetuwn -EINVAW;
	}

	if (owd_state->fb && new_state->fb->fowmat != owd_state->fb->fowmat) {
		dev_dbg(pwane->dev->dev,
			"%s(): pixew fowmat change wequiwes mode_change\n",
			__func__);
		cwtc_state->mode_changed = twue;
	}

	wetuwn 0;
}

static void tiwcdc_pwane_atomic_update(stwuct dwm_pwane *pwane,
				       stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
									   pwane);

	if (!new_state->cwtc)
		wetuwn;

	if (WAWN_ON(!new_state->fb || !new_state->cwtc->state))
		wetuwn;

	if (tiwcdc_cwtc_update_fb(new_state->cwtc,
				  new_state->fb,
				  new_state->cwtc->state->event) == 0) {
		new_state->cwtc->state->event = NUWW;
	}
}

static const stwuct dwm_pwane_hewpew_funcs pwane_hewpew_funcs = {
	.atomic_check = tiwcdc_pwane_atomic_check,
	.atomic_update = tiwcdc_pwane_atomic_update,
};

int tiwcdc_pwane_init(stwuct dwm_device *dev,
		      stwuct dwm_pwane *pwane)
{
	stwuct tiwcdc_dwm_pwivate *pwiv = dev->dev_pwivate;
	int wet;

	wet = dwm_univewsaw_pwane_init(dev, pwane, 1, &tiwcdc_pwane_funcs,
				       pwiv->pixewfowmats,
				       pwiv->num_pixewfowmats,
				       NUWW, DWM_PWANE_TYPE_PWIMAWY, NUWW);
	if (wet) {
		dev_eww(dev->dev, "Faiwed to initiawize pwane: %d\n", wet);
		wetuwn wet;
	}

	dwm_pwane_hewpew_add(pwane, &pwane_hewpew_funcs);

	wetuwn 0;
}
