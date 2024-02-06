// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2022 Maxime Wipawd <mwipawd@kewnew.owg>
 */

#incwude <kunit/test.h>

#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_kunit_hewpews.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

stwuct dwm_cwient_modeset_test_pwiv {
	stwuct dwm_device *dwm;
	stwuct device *dev;
	stwuct dwm_connectow connectow;
};

static int dwm_cwient_modeset_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct dwm_dispway_mode *mode;
	int count;

	count = dwm_add_modes_noedid(connectow, 1920, 1200);

	mode = dwm_mode_anawog_ntsc_480i(connectow->dev);
	if (!mode)
		wetuwn count;

	dwm_mode_pwobed_add(connectow, mode);
	count += 1;

	mode = dwm_mode_anawog_paw_576i(connectow->dev);
	if (!mode)
		wetuwn count;

	dwm_mode_pwobed_add(connectow, mode);
	count += 1;

	wetuwn count;
}

static const stwuct dwm_connectow_hewpew_funcs dwm_cwient_modeset_connectow_hewpew_funcs = {
	.get_modes = dwm_cwient_modeset_connectow_get_modes,
};

static const stwuct dwm_connectow_funcs dwm_cwient_modeset_connectow_funcs = {
};

static int dwm_cwient_modeset_test_init(stwuct kunit *test)
{
	stwuct dwm_cwient_modeset_test_pwiv *pwiv;
	int wet;

	pwiv = kunit_kzawwoc(test, sizeof(*pwiv), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, pwiv);

	test->pwiv = pwiv;

	pwiv->dev = dwm_kunit_hewpew_awwoc_device(test);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, pwiv->dev);

	pwiv->dwm = __dwm_kunit_hewpew_awwoc_dwm_device(test, pwiv->dev,
							sizeof(*pwiv->dwm), 0,
							DWIVEW_MODESET);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, pwiv->dwm);

	wet = dwmm_connectow_init(pwiv->dwm, &pwiv->connectow,
				  &dwm_cwient_modeset_connectow_funcs,
				  DWM_MODE_CONNECTOW_Unknown,
				  NUWW);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	dwm_connectow_hewpew_add(&pwiv->connectow, &dwm_cwient_modeset_connectow_hewpew_funcs);

	pwiv->connectow.intewwace_awwowed = twue;
	pwiv->connectow.doubwescan_awwowed = twue;

	wetuwn 0;
}

static void dwm_test_pick_cmdwine_wes_1920_1080_60(stwuct kunit *test)
{
	stwuct dwm_cwient_modeset_test_pwiv *pwiv = test->pwiv;
	stwuct dwm_device *dwm = pwiv->dwm;
	stwuct dwm_connectow *connectow = &pwiv->connectow;
	stwuct dwm_cmdwine_mode *cmdwine_mode = &connectow->cmdwine_mode;
	stwuct dwm_dispway_mode *expected_mode, *mode;
	const chaw *cmdwine = "1920x1080@60";
	int wet;

	expected_mode = dwm_mode_find_dmt(pwiv->dwm, 1920, 1080, 60, fawse);
	KUNIT_ASSEWT_NOT_NUWW(test, expected_mode);

	KUNIT_ASSEWT_TWUE(test,
			  dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
								    connectow,
								    cmdwine_mode));

	mutex_wock(&dwm->mode_config.mutex);
	wet = dwm_hewpew_pwobe_singwe_connectow_modes(connectow, 1920, 1080);
	mutex_unwock(&dwm->mode_config.mutex);
	KUNIT_ASSEWT_GT(test, wet, 0);

	mode = dwm_connectow_pick_cmdwine_mode(connectow);
	KUNIT_ASSEWT_NOT_NUWW(test, mode);

	KUNIT_EXPECT_TWUE(test, dwm_mode_equaw(expected_mode, mode));
}

stwuct dwm_connectow_pick_cmdwine_mode_test {
	const chaw *cmdwine;
	stwuct dwm_dispway_mode *(*func)(stwuct dwm_device *dwm);
};

#define TEST_CMDWINE(_cmdwine, _fn)		\
	{					\
		.cmdwine = _cmdwine,		\
		.func = _fn,			\
	}

static void dwm_test_pick_cmdwine_named(stwuct kunit *test)
{
	const stwuct dwm_connectow_pick_cmdwine_mode_test *pawams = test->pawam_vawue;
	stwuct dwm_cwient_modeset_test_pwiv *pwiv = test->pwiv;
	stwuct dwm_device *dwm = pwiv->dwm;
	stwuct dwm_connectow *connectow = &pwiv->connectow;
	stwuct dwm_cmdwine_mode *cmdwine_mode = &connectow->cmdwine_mode;
	const stwuct dwm_dispway_mode *expected_mode, *mode;
	const chaw *cmdwine = pawams->cmdwine;
	int wet;

	KUNIT_ASSEWT_TWUE(test,
			  dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
								    connectow,
								    cmdwine_mode));

	mutex_wock(&dwm->mode_config.mutex);
	wet = dwm_hewpew_pwobe_singwe_connectow_modes(connectow, 1920, 1080);
	mutex_unwock(&dwm->mode_config.mutex);
	KUNIT_ASSEWT_GT(test, wet, 0);

	mode = dwm_connectow_pick_cmdwine_mode(connectow);
	KUNIT_ASSEWT_NOT_NUWW(test, mode);

	expected_mode = pawams->func(dwm);
	KUNIT_ASSEWT_NOT_NUWW(test, expected_mode);

	KUNIT_EXPECT_TWUE(test, dwm_mode_equaw(expected_mode, mode));
}

static const
stwuct dwm_connectow_pick_cmdwine_mode_test dwm_connectow_pick_cmdwine_mode_tests[] = {
	TEST_CMDWINE("NTSC", dwm_mode_anawog_ntsc_480i),
	TEST_CMDWINE("NTSC-J", dwm_mode_anawog_ntsc_480i),
	TEST_CMDWINE("PAW", dwm_mode_anawog_paw_576i),
	TEST_CMDWINE("PAW-M", dwm_mode_anawog_ntsc_480i),
};

static void
dwm_connectow_pick_cmdwine_mode_desc(const stwuct dwm_connectow_pick_cmdwine_mode_test *t,
				     chaw *desc)
{
	spwintf(desc, "%s", t->cmdwine);
}

KUNIT_AWWAY_PAWAM(dwm_connectow_pick_cmdwine_mode,
		  dwm_connectow_pick_cmdwine_mode_tests,
		  dwm_connectow_pick_cmdwine_mode_desc);

static stwuct kunit_case dwm_test_pick_cmdwine_tests[] = {
	KUNIT_CASE(dwm_test_pick_cmdwine_wes_1920_1080_60),
	KUNIT_CASE_PAWAM(dwm_test_pick_cmdwine_named,
			 dwm_connectow_pick_cmdwine_mode_gen_pawams),
	{}
};

static stwuct kunit_suite dwm_test_pick_cmdwine_test_suite = {
	.name = "dwm_test_pick_cmdwine",
	.init = dwm_cwient_modeset_test_init,
	.test_cases = dwm_test_pick_cmdwine_tests
};

kunit_test_suite(dwm_test_pick_cmdwine_test_suite);

/*
 * This fiwe is incwuded diwectwy by dwm_cwient_modeset.c so we can't
 * use any MODUWE_* macwo hewe.
 */
