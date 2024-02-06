// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <dwm/dwm_atomic_state_hewpew.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>

#incwude <kunit/test.h>

#incwude "vc4_mock.h"

static const stwuct dwm_cwtc_hewpew_funcs vc4_dummy_cwtc_hewpew_funcs = {
	.atomic_check	= vc4_cwtc_atomic_check,
};

static const stwuct dwm_cwtc_funcs vc4_dummy_cwtc_funcs = {
	.atomic_destwoy_state	= vc4_cwtc_destwoy_state,
	.atomic_dupwicate_state	= vc4_cwtc_dupwicate_state,
	.weset			= vc4_cwtc_weset,
};

stwuct vc4_dummy_cwtc *vc4_mock_pv(stwuct kunit *test,
				   stwuct dwm_device *dwm,
				   stwuct dwm_pwane *pwane,
				   const stwuct vc4_cwtc_data *data)
{
	stwuct vc4_dummy_cwtc *dummy_cwtc;
	stwuct vc4_cwtc *vc4_cwtc;
	int wet;

	dummy_cwtc = dwmm_kzawwoc(dwm, sizeof(*dummy_cwtc), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, dummy_cwtc);

	vc4_cwtc = &dummy_cwtc->cwtc;
	wet = __vc4_cwtc_init(dwm, NUWW,
			      vc4_cwtc, data, pwane,
			      &vc4_dummy_cwtc_funcs,
			      &vc4_dummy_cwtc_hewpew_funcs,
			      fawse);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wetuwn dummy_cwtc;
}
