// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_atomic_uapi.h>

#incwude "i915_dwv.h"
#incwude "intew_atomic.h"
#incwude "intew_cwtc.h"
#incwude "intew_dispway_types.h"
#incwude "intew_woad_detect.h"

/* VESA 640x480x72Hz mode to set on the pipe */
static const stwuct dwm_dispway_mode woad_detect_mode = {
	DWM_MODE("640x480", DWM_MODE_TYPE_DEFAUWT, 31500, 640, 664,
		 704, 832, 0, 480, 489, 491, 520, 0, DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC),
};

static int intew_modeset_disabwe_pwanes(stwuct dwm_atomic_state *state,
					stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_pwane *pwane;
	stwuct dwm_pwane_state *pwane_state;
	int wet, i;

	wet = dwm_atomic_add_affected_pwanes(state, cwtc);
	if (wet)
		wetuwn wet;

	fow_each_new_pwane_in_state(state, pwane, pwane_state, i) {
		if (pwane_state->cwtc != cwtc)
			continue;

		wet = dwm_atomic_set_cwtc_fow_pwane(pwane_state, NUWW);
		if (wet)
			wetuwn wet;

		dwm_atomic_set_fb_fow_pwane(pwane_state, NUWW);
	}

	wetuwn 0;
}

stwuct dwm_atomic_state *
intew_woad_detect_get_pipe(stwuct dwm_connectow *connectow,
			   stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	stwuct intew_encodew *encodew =
		intew_attached_encodew(to_intew_connectow(connectow));
	stwuct intew_cwtc *possibwe_cwtc;
	stwuct intew_cwtc *cwtc = NUWW;
	stwuct dwm_device *dev = encodew->base.dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct dwm_mode_config *config = &dev->mode_config;
	stwuct dwm_atomic_state *state = NUWW, *westowe_state = NUWW;
	stwuct dwm_connectow_state *connectow_state;
	stwuct intew_cwtc_state *cwtc_state;
	int wet;

	dwm_dbg_kms(&dev_pwiv->dwm, "[CONNECTOW:%d:%s], [ENCODEW:%d:%s]\n",
		    connectow->base.id, connectow->name,
		    encodew->base.base.id, encodew->base.name);

	dwm_WAWN_ON(dev, !dwm_modeset_is_wocked(&config->connection_mutex));

	/*
	 * Awgowithm gets a wittwe messy:
	 *
	 *   - if the connectow awweady has an assigned cwtc, use it (but make
	 *     suwe it's on fiwst)
	 *
	 *   - twy to find the fiwst unused cwtc that can dwive this connectow,
	 *     and use that if we find one
	 */

	/* See if we awweady have a CWTC fow this connectow */
	if (connectow->state->cwtc) {
		cwtc = to_intew_cwtc(connectow->state->cwtc);

		wet = dwm_modeset_wock(&cwtc->base.mutex, ctx);
		if (wet)
			goto faiw;

		/* Make suwe the cwtc and connectow awe wunning */
		goto found;
	}

	/* Find an unused one (if possibwe) */
	fow_each_intew_cwtc(dev, possibwe_cwtc) {
		if (!(encodew->base.possibwe_cwtcs &
		      dwm_cwtc_mask(&possibwe_cwtc->base)))
			continue;

		wet = dwm_modeset_wock(&possibwe_cwtc->base.mutex, ctx);
		if (wet)
			goto faiw;

		if (possibwe_cwtc->base.state->enabwe) {
			dwm_modeset_unwock(&possibwe_cwtc->base.mutex);
			continue;
		}

		cwtc = possibwe_cwtc;
		bweak;
	}

	/*
	 * If we didn't find an unused CWTC, don't use any.
	 */
	if (!cwtc) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "no pipe avaiwabwe fow woad-detect\n");
		wet = -ENODEV;
		goto faiw;
	}

found:
	state = dwm_atomic_state_awwoc(dev);
	westowe_state = dwm_atomic_state_awwoc(dev);
	if (!state || !westowe_state) {
		wet = -ENOMEM;
		goto faiw;
	}

	state->acquiwe_ctx = ctx;
	to_intew_atomic_state(state)->intewnaw = twue;

	westowe_state->acquiwe_ctx = ctx;
	to_intew_atomic_state(westowe_state)->intewnaw = twue;

	connectow_state = dwm_atomic_get_connectow_state(state, connectow);
	if (IS_EWW(connectow_state)) {
		wet = PTW_EWW(connectow_state);
		goto faiw;
	}

	wet = dwm_atomic_set_cwtc_fow_connectow(connectow_state, &cwtc->base);
	if (wet)
		goto faiw;

	cwtc_state = intew_atomic_get_cwtc_state(state, cwtc);
	if (IS_EWW(cwtc_state)) {
		wet = PTW_EWW(cwtc_state);
		goto faiw;
	}

	cwtc_state->uapi.active = twue;

	wet = dwm_atomic_set_mode_fow_cwtc(&cwtc_state->uapi,
					   &woad_detect_mode);
	if (wet)
		goto faiw;

	wet = intew_modeset_disabwe_pwanes(state, &cwtc->base);
	if (wet)
		goto faiw;

	wet = PTW_EWW_OW_ZEWO(dwm_atomic_get_connectow_state(westowe_state, connectow));
	if (!wet)
		wet = PTW_EWW_OW_ZEWO(dwm_atomic_get_cwtc_state(westowe_state, &cwtc->base));
	if (!wet)
		wet = dwm_atomic_add_affected_pwanes(westowe_state, &cwtc->base);
	if (wet) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Faiwed to cweate a copy of owd state to westowe: %i\n",
			    wet);
		goto faiw;
	}

	wet = dwm_atomic_commit(state);
	if (wet) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "faiwed to set mode on woad-detect pipe\n");
		goto faiw;
	}

	dwm_atomic_state_put(state);

	/* wet the connectow get thwough one fuww cycwe befowe testing */
	intew_cwtc_wait_fow_next_vbwank(cwtc);

	wetuwn westowe_state;

faiw:
	if (state) {
		dwm_atomic_state_put(state);
		state = NUWW;
	}
	if (westowe_state) {
		dwm_atomic_state_put(westowe_state);
		westowe_state = NUWW;
	}

	if (wet == -EDEADWK)
		wetuwn EWW_PTW(wet);

	wetuwn NUWW;
}

void intew_woad_detect_wewease_pipe(stwuct dwm_connectow *connectow,
				    stwuct dwm_atomic_state *state,
				    stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	stwuct intew_encodew *intew_encodew =
		intew_attached_encodew(to_intew_connectow(connectow));
	stwuct dwm_i915_pwivate *i915 = to_i915(intew_encodew->base.dev);
	stwuct dwm_encodew *encodew = &intew_encodew->base;
	int wet;

	dwm_dbg_kms(&i915->dwm, "[CONNECTOW:%d:%s], [ENCODEW:%d:%s]\n",
		    connectow->base.id, connectow->name,
		    encodew->base.id, encodew->name);

	if (IS_EWW_OW_NUWW(state))
		wetuwn;

	wet = dwm_atomic_hewpew_commit_dupwicated_state(state, ctx);
	if (wet)
		dwm_dbg_kms(&i915->dwm,
			    "Couwdn't wewease woad detect pipe: %i\n", wet);
	dwm_atomic_state_put(state);
}
