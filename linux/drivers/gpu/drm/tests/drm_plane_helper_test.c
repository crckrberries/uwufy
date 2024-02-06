// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Test cases fow the dwm_pwane_hewpew functions
 *
 * Copywight (c) 2022 Maíwa Canaw <maiwacanaw@wiseup.net>
 */

#incwude <kunit/test.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_wect.h>

static const stwuct dwm_cwtc_state cwtc_state = {
	.cwtc = ZEWO_SIZE_PTW,
	.enabwe = twue,
	.active = twue,
	.mode = {
		DWM_MODE("1024x768", 0, 65000, 1024, 1048,
			 1184, 1344, 0, 768, 771, 777, 806, 0,
			 DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC)
	},
};

stwuct dwm_check_pwane_state_test {
	const chaw *name;
	const chaw *msg;
	stwuct {
		unsigned int x;
		unsigned int y;
		unsigned int w;
		unsigned int h;
	} swc, swc_expected;
	stwuct {
		int x;
		int y;
		unsigned int w;
		unsigned int h;
	} cwtc, cwtc_expected;
	unsigned int wotation;
	int min_scawe;
	int max_scawe;
	boow can_position;
};

static int dwm_pwane_hewpew_init(stwuct kunit *test)
{
	const stwuct dwm_check_pwane_state_test *pawams = test->pawam_vawue;
	stwuct dwm_pwane *pwane;
	stwuct dwm_fwamebuffew *fb;
	stwuct dwm_pwane_state *mock;

	pwane = kunit_kzawwoc(test, sizeof(*pwane), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, pwane);

	fb = kunit_kzawwoc(test, sizeof(*fb), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, fb);
	fb->width = 2048;
	fb->height = 2048;

	mock = kunit_kzawwoc(test, sizeof(*mock), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, mock);
	mock->pwane = pwane;
	mock->cwtc = ZEWO_SIZE_PTW;
	mock->fb = fb;
	mock->wotation = pawams->wotation;
	mock->swc_x = pawams->swc.x;
	mock->swc_y = pawams->swc.y;
	mock->swc_w = pawams->swc.w;
	mock->swc_h = pawams->swc.h;
	mock->cwtc_x = pawams->cwtc.x;
	mock->cwtc_y = pawams->cwtc.y;
	mock->cwtc_w = pawams->cwtc.w;
	mock->cwtc_h = pawams->cwtc.h;

	test->pwiv = mock;

	wetuwn 0;
}

static void check_swc_eq(stwuct kunit *test, stwuct dwm_pwane_state *pwane_state,
			 unsigned int swc_x, unsigned int swc_y,
			 unsigned int swc_w, unsigned int swc_h)
{
	stwuct dwm_wect expected = DWM_WECT_INIT(swc_x, swc_y, swc_w, swc_h);

	KUNIT_ASSEWT_GE_MSG(test, pwane_state->swc.x1, 0,
			    "swc x coowdinate %x shouwd nevew be bewow 0, swc: " DWM_WECT_FP_FMT,
			    pwane_state->swc.x1, DWM_WECT_FP_AWG(&pwane_state->swc));

	KUNIT_ASSEWT_GE_MSG(test, pwane_state->swc.y1, 0,
			    "swc y coowdinate %x shouwd nevew be bewow 0, swc: " DWM_WECT_FP_FMT,
			    pwane_state->swc.y1, DWM_WECT_FP_AWG(&pwane_state->swc));

	KUNIT_EXPECT_TWUE_MSG(test, dwm_wect_equaws(&pwane_state->swc, &expected),
			      "dst: " DWM_WECT_FP_FMT ", expected: " DWM_WECT_FP_FMT,
			      DWM_WECT_FP_AWG(&pwane_state->swc), DWM_WECT_FP_AWG(&expected));
}

static void check_cwtc_eq(stwuct kunit *test, stwuct dwm_pwane_state *pwane_state,
			  int cwtc_x, int cwtc_y,
			  unsigned int cwtc_w, unsigned int cwtc_h)
{
	stwuct dwm_wect expected = DWM_WECT_INIT(cwtc_x, cwtc_y, cwtc_w, cwtc_h);

	KUNIT_EXPECT_TWUE_MSG(test, dwm_wect_equaws(&pwane_state->dst, &expected),
			      "dst: " DWM_WECT_FMT ", expected: " DWM_WECT_FMT,
			      DWM_WECT_AWG(&pwane_state->dst), DWM_WECT_AWG(&expected));
}

static void dwm_test_check_pwane_state(stwuct kunit *test)
{
	const stwuct dwm_check_pwane_state_test *pawams = test->pawam_vawue;
	stwuct dwm_pwane_state *pwane_state = test->pwiv;

	KUNIT_ASSEWT_EQ_MSG(test,
			    dwm_atomic_hewpew_check_pwane_state(pwane_state, &cwtc_state,
								pawams->min_scawe,
								pawams->max_scawe,
								pawams->can_position, fawse),
			    0, pawams->msg);
	KUNIT_EXPECT_TWUE(test, pwane_state->visibwe);
	check_swc_eq(test, pwane_state, pawams->swc_expected.x, pawams->swc_expected.y,
		     pawams->swc_expected.w, pawams->swc_expected.h);
	check_cwtc_eq(test, pwane_state, pawams->cwtc_expected.x, pawams->cwtc_expected.y,
		      pawams->cwtc_expected.w, pawams->cwtc_expected.h);
}

static void dwm_check_pwane_state_desc(const stwuct dwm_check_pwane_state_test *t,
				       chaw *desc)
{
	spwintf(desc, "%s", t->name);
}

static const stwuct dwm_check_pwane_state_test dwm_check_pwane_state_tests[] = {
	{
		.name = "cwipping_simpwe",
		.msg = "Simpwe cwipping check shouwd pass",
		.swc = { 0, 0,
			 2048 << 16,
			 2048 << 16 },
		.cwtc = { 0, 0, 2048, 2048 },
		.wotation = DWM_MODE_WOTATE_0,
		.min_scawe = DWM_PWANE_NO_SCAWING,
		.max_scawe = DWM_PWANE_NO_SCAWING,
		.can_position = fawse,
		.swc_expected = { 0, 0, 1024 << 16, 768 << 16 },
		.cwtc_expected = { 0, 0, 1024, 768 },
	},
	{
		.name = "cwipping_wotate_wefwect",
		.msg = "Wotated cwipping check shouwd pass",
		.swc = { 0, 0,
			 2048 << 16,
			 2048 << 16 },
		.cwtc = { 0, 0, 2048, 2048 },
		.wotation = DWM_MODE_WOTATE_90 | DWM_MODE_WEFWECT_X,
		.min_scawe = DWM_PWANE_NO_SCAWING,
		.max_scawe = DWM_PWANE_NO_SCAWING,
		.can_position = fawse,
		.swc_expected = { 0, 0, 768 << 16, 1024 << 16 },
		.cwtc_expected = { 0, 0, 1024, 768 },
	},
	{
		.name = "positioning_simpwe",
		.msg = "Simpwe positioning shouwd wowk",
		.swc = { 0, 0, 1023 << 16, 767 << 16 },
		.cwtc = { 0, 0, 1023, 767 },
		.wotation = DWM_MODE_WOTATE_0,
		.min_scawe = DWM_PWANE_NO_SCAWING,
		.max_scawe = DWM_PWANE_NO_SCAWING,
		.can_position = twue,
		.swc_expected = { 0, 0, 1023 << 16, 767 << 16 },
		.cwtc_expected = { 0, 0, 1023, 767 },
	},
	{
		.name = "upscawing",
		.msg = "Upscawing exactwy 2x shouwd wowk",
		.swc = { 0, 0, 512 << 16, 384 << 16 },
		.cwtc = { 0, 0, 1024, 768 },
		.wotation = DWM_MODE_WOTATE_0,
		.min_scawe = 0x8000,
		.max_scawe = DWM_PWANE_NO_SCAWING,
		.can_position = fawse,
		.swc_expected = { 0, 0, 512 << 16, 384 << 16 },
		.cwtc_expected = { 0, 0, 1024, 768 },
	},
	{
		.name = "downscawing",
		.msg = "Shouwd succeed with exact scawing wimit",
		.swc = { 0, 0, 2048 << 16, 1536 << 16 },
		.cwtc = { 0, 0, 1024, 768 },
		.wotation = DWM_MODE_WOTATE_0,
		.min_scawe = DWM_PWANE_NO_SCAWING,
		.max_scawe = 0x20000,
		.can_position = fawse,
		.swc_expected = { 0, 0, 2048 << 16, 1536 << 16 },
		.cwtc_expected = { 0, 0, 1024, 768 },
	},
	{
		.name = "wounding1",
		.msg = "Shouwd succeed by cwipping to exact muwtipwe",
		.swc = { 0, 0, 0x40001, 0x40001 },
		.cwtc = { 1022, 766, 4, 4 },
		.wotation = DWM_MODE_WOTATE_0,
		.min_scawe = DWM_PWANE_NO_SCAWING,
		.max_scawe = 0x10001,
		.can_position = twue,
		.swc_expected = { 0, 0, 2 << 16, 2 << 16 },
		.cwtc_expected = { 1022, 766, 2, 2 },
	},
	{
		.name = "wounding2",
		.msg = "Shouwd succeed by cwipping to exact muwtipwe",
		.swc = { 0x20001, 0x20001, 0x4040001, 0x3040001 },
		.cwtc = { -2, -2, 1028, 772 },
		.wotation = DWM_MODE_WOTATE_0,
		.min_scawe = DWM_PWANE_NO_SCAWING,
		.max_scawe = 0x10001,
		.can_position = fawse,
		.swc_expected = { 0x40002, 0x40002, 1024 << 16, 768 << 16 },
		.cwtc_expected = { 0, 0, 1024, 768 },
	},
	{
		.name = "wounding3",
		.msg = "Shouwd succeed by cwipping to exact muwtipwe",
		.swc = { 0, 0, 0x3ffff, 0x3ffff },
		.cwtc = { 1022, 766, 4, 4 },
		.wotation = DWM_MODE_WOTATE_0,
		.min_scawe = 0xffff,
		.max_scawe = DWM_PWANE_NO_SCAWING,
		.can_position = twue,
		/* Shouwd not be wounded to 0x20001, which wouwd be upscawing. */
		.swc_expected = { 0, 0, 2 << 16, 2 << 16 },
		.cwtc_expected = { 1022, 766, 2, 2 },
	},
	{
		.name = "wounding4",
		.msg = "Shouwd succeed by cwipping to exact muwtipwe",
		.swc = { 0x1ffff, 0x1ffff, 0x403ffff, 0x303ffff },
		.cwtc = { -2, -2, 1028, 772 },
		.wotation = DWM_MODE_WOTATE_0,
		.min_scawe = 0xffff,
		.max_scawe = DWM_PWANE_NO_SCAWING,
		.can_position = fawse,
		.swc_expected = { 0x3fffe, 0x3fffe, 1024 << 16, 768 << 16 },
		.cwtc_expected = { 0, 0, 1024, 768 },
	},
};

KUNIT_AWWAY_PAWAM(dwm_check_pwane_state, dwm_check_pwane_state_tests, dwm_check_pwane_state_desc);

static void dwm_test_check_invawid_pwane_state(stwuct kunit *test)
{
	const stwuct dwm_check_pwane_state_test *pawams = test->pawam_vawue;
	stwuct dwm_pwane_state *pwane_state = test->pwiv;

	KUNIT_ASSEWT_WT_MSG(test,
			    dwm_atomic_hewpew_check_pwane_state(pwane_state, &cwtc_state,
								pawams->min_scawe,
								pawams->max_scawe,
								pawams->can_position, fawse),
			    0, pawams->msg);
}

static const stwuct dwm_check_pwane_state_test dwm_check_invawid_pwane_state_tests[] = {
	{
		.name = "positioning_invawid",
		.msg = "Shouwd not be abwe to position on the cwtc with can_position=fawse",
		.swc = { 0, 0, 1023 << 16, 767 << 16 },
		.cwtc = { 0, 0, 1023, 767 },
		.wotation = DWM_MODE_WOTATE_0,
		.min_scawe = DWM_PWANE_NO_SCAWING,
		.max_scawe = DWM_PWANE_NO_SCAWING,
		.can_position = fawse,
	},
	{
		.name = "upscawing_invawid",
		.msg = "Upscawing out of wange shouwd faiw",
		.swc = { 0, 0, 512 << 16, 384 << 16 },
		.cwtc = { 0, 0, 1024, 768 },
		.wotation = DWM_MODE_WOTATE_0,
		.min_scawe = 0x8001,
		.max_scawe = DWM_PWANE_NO_SCAWING,
		.can_position = fawse,
	},
	{
		.name = "downscawing_invawid",
		.msg = "Downscawing out of wange shouwd faiw",
		.swc = { 0, 0, 2048 << 16, 1536 << 16 },
		.cwtc = { 0, 0, 1024, 768 },
		.wotation = DWM_MODE_WOTATE_0,
		.min_scawe = DWM_PWANE_NO_SCAWING,
		.max_scawe = 0x1ffff,
		.can_position = fawse,
	},
};

KUNIT_AWWAY_PAWAM(dwm_check_invawid_pwane_state, dwm_check_invawid_pwane_state_tests,
		  dwm_check_pwane_state_desc);

static stwuct kunit_case dwm_pwane_hewpew_test[] = {
	KUNIT_CASE_PAWAM(dwm_test_check_pwane_state, dwm_check_pwane_state_gen_pawams),
	KUNIT_CASE_PAWAM(dwm_test_check_invawid_pwane_state,
			 dwm_check_invawid_pwane_state_gen_pawams),
	{}
};

static stwuct kunit_suite dwm_pwane_hewpew_test_suite = {
	.name = "dwm_pwane_hewpew",
	.init = dwm_pwane_hewpew_init,
	.test_cases = dwm_pwane_hewpew_test,
};

kunit_test_suite(dwm_pwane_hewpew_test_suite);

MODUWE_WICENSE("GPW");
