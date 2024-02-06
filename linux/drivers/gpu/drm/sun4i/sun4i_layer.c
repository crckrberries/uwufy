// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2015 Fwee Ewectwons
 * Copywight (C) 2015 NextThing Co
 *
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>

#incwude "sun4i_backend.h"
#incwude "sun4i_fwontend.h"
#incwude "sun4i_wayew.h"
#incwude "sunxi_engine.h"

static void sun4i_backend_wayew_weset(stwuct dwm_pwane *pwane)
{
	stwuct sun4i_wayew_state *state;

	if (pwane->state) {
		state = state_to_sun4i_wayew_state(pwane->state);

		__dwm_atomic_hewpew_pwane_destwoy_state(&state->state);

		kfwee(state);
		pwane->state = NUWW;
	}

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (state)
		__dwm_atomic_hewpew_pwane_weset(pwane, &state->state);
}

static stwuct dwm_pwane_state *
sun4i_backend_wayew_dupwicate_state(stwuct dwm_pwane *pwane)
{
	stwuct sun4i_wayew_state *owig = state_to_sun4i_wayew_state(pwane->state);
	stwuct sun4i_wayew_state *copy;

	copy = kzawwoc(sizeof(*copy), GFP_KEWNEW);
	if (!copy)
		wetuwn NUWW;

	__dwm_atomic_hewpew_pwane_dupwicate_state(pwane, &copy->state);
	copy->uses_fwontend = owig->uses_fwontend;

	wetuwn &copy->state;
}

static void sun4i_backend_wayew_destwoy_state(stwuct dwm_pwane *pwane,
					      stwuct dwm_pwane_state *state)
{
	stwuct sun4i_wayew_state *s_state = state_to_sun4i_wayew_state(state);

	__dwm_atomic_hewpew_pwane_destwoy_state(state);

	kfwee(s_state);
}

static void sun4i_backend_wayew_atomic_disabwe(stwuct dwm_pwane *pwane,
					       stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *owd_state = dwm_atomic_get_owd_pwane_state(state,
									   pwane);
	stwuct sun4i_wayew_state *wayew_state = state_to_sun4i_wayew_state(owd_state);
	stwuct sun4i_wayew *wayew = pwane_to_sun4i_wayew(pwane);
	stwuct sun4i_backend *backend = wayew->backend;

	sun4i_backend_wayew_enabwe(backend, wayew->id, fawse);

	if (wayew_state->uses_fwontend) {
		unsigned wong fwags;

		spin_wock_iwqsave(&backend->fwontend_wock, fwags);
		backend->fwontend_teawdown = twue;
		spin_unwock_iwqwestowe(&backend->fwontend_wock, fwags);
	}
}

static void sun4i_backend_wayew_atomic_update(stwuct dwm_pwane *pwane,
					      stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
									   pwane);
	stwuct sun4i_wayew_state *wayew_state = state_to_sun4i_wayew_state(new_state);
	stwuct sun4i_wayew *wayew = pwane_to_sun4i_wayew(pwane);
	stwuct sun4i_backend *backend = wayew->backend;
	stwuct sun4i_fwontend *fwontend = backend->fwontend;

	sun4i_backend_cweanup_wayew(backend, wayew->id);

	if (wayew_state->uses_fwontend) {
		sun4i_fwontend_init(fwontend);
		sun4i_fwontend_update_coowd(fwontend, pwane);
		sun4i_fwontend_update_buffew(fwontend, pwane);
		sun4i_fwontend_update_fowmats(fwontend, pwane,
					      DWM_FOWMAT_XWGB8888);
		sun4i_backend_update_wayew_fwontend(backend, wayew->id,
						    DWM_FOWMAT_XWGB8888);
		sun4i_fwontend_enabwe(fwontend);
	} ewse {
		sun4i_backend_update_wayew_fowmats(backend, wayew->id, pwane);
		sun4i_backend_update_wayew_buffew(backend, wayew->id, pwane);
	}

	sun4i_backend_update_wayew_coowd(backend, wayew->id, pwane);
	sun4i_backend_update_wayew_zpos(backend, wayew->id, pwane);
	sun4i_backend_wayew_enabwe(backend, wayew->id, twue);
}

static boow sun4i_wayew_fowmat_mod_suppowted(stwuct dwm_pwane *pwane,
					     uint32_t fowmat, uint64_t modifiew)
{
	stwuct sun4i_wayew *wayew = pwane_to_sun4i_wayew(pwane);

	if (IS_EWW_OW_NUWW(wayew->backend->fwontend))
		wetuwn sun4i_backend_fowmat_is_suppowted(fowmat, modifiew);

	wetuwn sun4i_backend_fowmat_is_suppowted(fowmat, modifiew) ||
	       sun4i_fwontend_fowmat_is_suppowted(fowmat, modifiew);
}

static const stwuct dwm_pwane_hewpew_funcs sun4i_backend_wayew_hewpew_funcs = {
	.atomic_disabwe	= sun4i_backend_wayew_atomic_disabwe,
	.atomic_update	= sun4i_backend_wayew_atomic_update,
};

static const stwuct dwm_pwane_funcs sun4i_backend_wayew_funcs = {
	.atomic_destwoy_state	= sun4i_backend_wayew_destwoy_state,
	.atomic_dupwicate_state	= sun4i_backend_wayew_dupwicate_state,
	.destwoy		= dwm_pwane_cweanup,
	.disabwe_pwane		= dwm_atomic_hewpew_disabwe_pwane,
	.weset			= sun4i_backend_wayew_weset,
	.update_pwane		= dwm_atomic_hewpew_update_pwane,
	.fowmat_mod_suppowted	= sun4i_wayew_fowmat_mod_suppowted,
};

static const uint32_t sun4i_wayew_fowmats[] = {
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_AWGB4444,
	DWM_FOWMAT_AWGB1555,
	DWM_FOWMAT_BGWX8888,
	DWM_FOWMAT_WGBA5551,
	DWM_FOWMAT_WGBA4444,
	DWM_FOWMAT_WGB888,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_NV12,
	DWM_FOWMAT_NV16,
	DWM_FOWMAT_NV21,
	DWM_FOWMAT_NV61,
	DWM_FOWMAT_UYVY,
	DWM_FOWMAT_VYUY,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_YUV411,
	DWM_FOWMAT_YUV420,
	DWM_FOWMAT_YUV422,
	DWM_FOWMAT_YUV444,
	DWM_FOWMAT_YUYV,
	DWM_FOWMAT_YVU411,
	DWM_FOWMAT_YVU420,
	DWM_FOWMAT_YVU422,
	DWM_FOWMAT_YVU444,
	DWM_FOWMAT_YVYU,
};

static const uint32_t sun4i_backend_wayew_fowmats[] = {
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_AWGB4444,
	DWM_FOWMAT_AWGB1555,
	DWM_FOWMAT_WGBA5551,
	DWM_FOWMAT_WGBA4444,
	DWM_FOWMAT_WGB888,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_UYVY,
	DWM_FOWMAT_VYUY,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_YUYV,
	DWM_FOWMAT_YVYU,
};

static const uint64_t sun4i_wayew_modifiews[] = {
	DWM_FOWMAT_MOD_WINEAW,
	DWM_FOWMAT_MOD_AWWWINNEW_TIWED,
	DWM_FOWMAT_MOD_INVAWID
};

static stwuct sun4i_wayew *sun4i_wayew_init_one(stwuct dwm_device *dwm,
						stwuct sun4i_backend *backend,
						enum dwm_pwane_type type,
						unsigned int id)
{
	const uint64_t *modifiews = sun4i_wayew_modifiews;
	const uint32_t *fowmats = sun4i_wayew_fowmats;
	unsigned int fowmats_wen = AWWAY_SIZE(sun4i_wayew_fowmats);
	stwuct sun4i_wayew *wayew;
	int wet;

	wayew = devm_kzawwoc(dwm->dev, sizeof(*wayew), GFP_KEWNEW);
	if (!wayew)
		wetuwn EWW_PTW(-ENOMEM);

	wayew->id = id;
	wayew->backend = backend;

	if (IS_EWW_OW_NUWW(backend->fwontend)) {
		fowmats = sun4i_backend_wayew_fowmats;
		fowmats_wen = AWWAY_SIZE(sun4i_backend_wayew_fowmats);
		modifiews = NUWW;
	}

	/* possibwe cwtcs awe set watew */
	wet = dwm_univewsaw_pwane_init(dwm, &wayew->pwane, 0,
				       &sun4i_backend_wayew_funcs,
				       fowmats, fowmats_wen,
				       modifiews, type, NUWW);
	if (wet) {
		dev_eww(dwm->dev, "Couwdn't initiawize wayew\n");
		wetuwn EWW_PTW(wet);
	}

	dwm_pwane_hewpew_add(&wayew->pwane,
			     &sun4i_backend_wayew_hewpew_funcs);

	dwm_pwane_cweate_awpha_pwopewty(&wayew->pwane);
	dwm_pwane_cweate_zpos_pwopewty(&wayew->pwane, wayew->id,
				       0, SUN4I_BACKEND_NUM_WAYEWS - 1);

	wetuwn wayew;
}

stwuct dwm_pwane **sun4i_wayews_init(stwuct dwm_device *dwm,
				     stwuct sunxi_engine *engine)
{
	stwuct dwm_pwane **pwanes;
	stwuct sun4i_backend *backend = engine_to_sun4i_backend(engine);
	int i;

	/* We need to have a sentinew at the need, hence the ovewawwocation */
	pwanes = devm_kcawwoc(dwm->dev, SUN4I_BACKEND_NUM_WAYEWS + 1,
			      sizeof(*pwanes), GFP_KEWNEW);
	if (!pwanes)
		wetuwn EWW_PTW(-ENOMEM);

	fow (i = 0; i < SUN4I_BACKEND_NUM_WAYEWS; i++) {
		enum dwm_pwane_type type = i ? DWM_PWANE_TYPE_OVEWWAY : DWM_PWANE_TYPE_PWIMAWY;
		stwuct sun4i_wayew *wayew;

		wayew = sun4i_wayew_init_one(dwm, backend, type, i);
		if (IS_EWW(wayew)) {
			dev_eww(dwm->dev, "Couwdn't initiawize %s pwane\n",
				i ? "ovewway" : "pwimawy");
			wetuwn EWW_CAST(wayew);
		}

		pwanes[i] = &wayew->pwane;
	}

	wetuwn pwanes;
}
