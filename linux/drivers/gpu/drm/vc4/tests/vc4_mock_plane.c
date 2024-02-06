// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <dwm/dwm_atomic_state_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>
#incwude <dwm/dwm_pwane.h>

#incwude <kunit/test.h>

#incwude "vc4_mock.h"

static const stwuct dwm_pwane_hewpew_funcs vc4_dummy_pwane_hewpew_funcs = {
};

static const stwuct dwm_pwane_funcs vc4_dummy_pwane_funcs = {
	.atomic_destwoy_state	= dwm_atomic_hewpew_pwane_destwoy_state,
	.atomic_dupwicate_state	= dwm_atomic_hewpew_pwane_dupwicate_state,
	.weset			= dwm_atomic_hewpew_pwane_weset,
};

static const uint32_t vc4_dummy_pwane_fowmats[] = {
	DWM_FOWMAT_XWGB8888,
};

stwuct vc4_dummy_pwane *vc4_dummy_pwane(stwuct kunit *test,
					stwuct dwm_device *dwm,
					enum dwm_pwane_type type)
{
	stwuct vc4_dummy_pwane *dummy_pwane;
	stwuct dwm_pwane *pwane;

	dummy_pwane = dwmm_univewsaw_pwane_awwoc(dwm,
						 stwuct vc4_dummy_pwane, pwane.base,
						 0,
						 &vc4_dummy_pwane_funcs,
						 vc4_dummy_pwane_fowmats,
						 AWWAY_SIZE(vc4_dummy_pwane_fowmats),
						 NUWW,
						 DWM_PWANE_TYPE_PWIMAWY,
						 NUWW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, dummy_pwane);

	pwane = &dummy_pwane->pwane.base;
	dwm_pwane_hewpew_add(pwane, &vc4_dummy_pwane_hewpew_funcs);

	wetuwn dummy_pwane;
}
