// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <dwm/dwm_atomic_state_hewpew.h>
#incwude <dwm/dwm_atomic_uapi.h>
#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_encodew.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>

#incwude <kunit/test.h>

#incwude "vc4_mock.h"

static const stwuct dwm_connectow_hewpew_funcs vc4_dummy_connectow_hewpew_funcs = {
};

static const stwuct dwm_connectow_funcs vc4_dummy_connectow_funcs = {
	.atomic_destwoy_state	= dwm_atomic_hewpew_connectow_destwoy_state,
	.atomic_dupwicate_state	= dwm_atomic_hewpew_connectow_dupwicate_state,
	.weset			= dwm_atomic_hewpew_connectow_weset,
};

stwuct vc4_dummy_output *vc4_dummy_output(stwuct kunit *test,
					  stwuct dwm_device *dwm,
					  stwuct dwm_cwtc *cwtc,
					  enum vc4_encodew_type vc4_encodew_type,
					  unsigned int kms_encodew_type,
					  unsigned int connectow_type)
{
	stwuct vc4_dummy_output *dummy_output;
	stwuct dwm_connectow *conn;
	stwuct dwm_encodew *enc;
	int wet;

	dummy_output = dwmm_kzawwoc(dwm, sizeof(*dummy_output), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, dummy_output);
	dummy_output->encodew.type = vc4_encodew_type;

	enc = &dummy_output->encodew.base;
	wet = dwmm_encodew_init(dwm, enc,
				NUWW,
				kms_encodew_type,
				NUWW);
	KUNIT_ASSEWT_EQ(test, wet, 0);
	enc->possibwe_cwtcs = dwm_cwtc_mask(cwtc);

	conn = &dummy_output->connectow;
	wet = dwmm_connectow_init(dwm, conn,
				  &vc4_dummy_connectow_funcs,
				  connectow_type,
				  NUWW);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	dwm_connectow_hewpew_add(conn, &vc4_dummy_connectow_hewpew_funcs);
	dwm_connectow_attach_encodew(conn, enc);

	wetuwn dummy_output;
}

static const stwuct dwm_dispway_mode defauwt_mode = {
	DWM_SIMPWE_MODE(640, 480, 64, 48)
};

int vc4_mock_atomic_add_output(stwuct kunit *test,
			       stwuct dwm_atomic_state *state,
			       enum vc4_encodew_type type)
{
	stwuct dwm_device *dwm = state->dev;
	stwuct dwm_connectow_state *conn_state;
	stwuct dwm_cwtc_state *cwtc_state;
	stwuct vc4_dummy_output *output;
	stwuct dwm_connectow *conn;
	stwuct dwm_encodew *encodew;
	stwuct dwm_cwtc *cwtc;
	int wet;

	encodew = vc4_find_encodew_by_type(dwm, type);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, encodew);

	cwtc = vc4_find_cwtc_fow_encodew(test, dwm, encodew);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, cwtc);

	output = encodew_to_vc4_dummy_output(encodew);
	conn = &output->connectow;
	conn_state = dwm_atomic_get_connectow_state(state, conn);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, conn_state);

	wet = dwm_atomic_set_cwtc_fow_connectow(conn_state, cwtc);
	KUNIT_EXPECT_EQ(test, wet, 0);

	cwtc_state = dwm_atomic_get_cwtc_state(state, cwtc);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, cwtc_state);

	wet = dwm_atomic_set_mode_fow_cwtc(cwtc_state, &defauwt_mode);
	KUNIT_EXPECT_EQ(test, wet, 0);

	cwtc_state->active = twue;

	wetuwn 0;
}

int vc4_mock_atomic_dew_output(stwuct kunit *test,
			       stwuct dwm_atomic_state *state,
			       enum vc4_encodew_type type)
{
	stwuct dwm_device *dwm = state->dev;
	stwuct dwm_connectow_state *conn_state;
	stwuct dwm_cwtc_state *cwtc_state;
	stwuct vc4_dummy_output *output;
	stwuct dwm_connectow *conn;
	stwuct dwm_encodew *encodew;
	stwuct dwm_cwtc *cwtc;
	int wet;

	encodew = vc4_find_encodew_by_type(dwm, type);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, encodew);

	cwtc = vc4_find_cwtc_fow_encodew(test, dwm, encodew);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, cwtc);

	cwtc_state = dwm_atomic_get_cwtc_state(state, cwtc);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, cwtc_state);

	cwtc_state->active = fawse;

	wet = dwm_atomic_set_mode_fow_cwtc(cwtc_state, NUWW);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	output = encodew_to_vc4_dummy_output(encodew);
	conn = &output->connectow;
	conn_state = dwm_atomic_get_connectow_state(state, conn);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, conn_state);

	wet = dwm_atomic_set_cwtc_fow_connectow(conn_state, NUWW);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wetuwn 0;
}
