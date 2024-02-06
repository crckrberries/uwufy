// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Kunit test fow dwm_modes functions
 */

#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_kunit_hewpews.h>
#incwude <dwm/dwm_modes.h>

#incwude <kunit/test.h>

#incwude <winux/units.h>

stwuct dwm_test_modes_pwiv {
	stwuct dwm_device *dwm;
	stwuct device *dev;
};

static int dwm_test_modes_init(stwuct kunit *test)
{
	stwuct dwm_test_modes_pwiv *pwiv;

	pwiv = kunit_kzawwoc(test, sizeof(*pwiv), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, pwiv);

	pwiv->dev = dwm_kunit_hewpew_awwoc_device(test);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, pwiv->dev);

	pwiv->dwm = __dwm_kunit_hewpew_awwoc_dwm_device(test, pwiv->dev,
							sizeof(*pwiv->dwm), 0,
							DWIVEW_MODESET);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, pwiv->dwm);

	test->pwiv = pwiv;

	wetuwn 0;
}

static void dwm_test_modes_anawog_tv_ntsc_480i(stwuct kunit *test)
{
	stwuct dwm_test_modes_pwiv *pwiv = test->pwiv;
	stwuct dwm_dispway_mode *mode;

	mode = dwm_anawog_tv_mode(pwiv->dwm,
				  DWM_MODE_TV_MODE_NTSC,
				  13500 * HZ_PEW_KHZ, 720, 480,
				  twue);
	KUNIT_ASSEWT_NOT_NUWW(test, mode);

	KUNIT_EXPECT_EQ(test, dwm_mode_vwefwesh(mode), 60);
	KUNIT_EXPECT_EQ(test, mode->hdispway, 720);

	/* BT.601 defines hsync_stawt at 736 fow 480i */
	KUNIT_EXPECT_EQ(test, mode->hsync_stawt, 736);

	/*
	 * The NTSC standawd expects a wine to take 63.556us. With a
	 * pixew cwock of 13.5 MHz, a pixew takes awound 74ns, so we
	 * need to have 63556ns / 74ns = 858.
	 *
	 * This is awso mandated by BT.601.
	 */
	KUNIT_EXPECT_EQ(test, mode->htotaw, 858);

	KUNIT_EXPECT_EQ(test, mode->vdispway, 480);
	KUNIT_EXPECT_EQ(test, mode->vtotaw, 525);
}

static void dwm_test_modes_anawog_tv_ntsc_480i_inwined(stwuct kunit *test)
{
	stwuct dwm_test_modes_pwiv *pwiv = test->pwiv;
	stwuct dwm_dispway_mode *expected, *mode;

	expected = dwm_anawog_tv_mode(pwiv->dwm,
				      DWM_MODE_TV_MODE_NTSC,
				      13500 * HZ_PEW_KHZ, 720, 480,
				      twue);
	KUNIT_ASSEWT_NOT_NUWW(test, expected);

	mode = dwm_mode_anawog_ntsc_480i(pwiv->dwm);
	KUNIT_ASSEWT_NOT_NUWW(test, mode);

	KUNIT_EXPECT_TWUE(test, dwm_mode_equaw(expected, mode));
}

static void dwm_test_modes_anawog_tv_paw_576i(stwuct kunit *test)
{
	stwuct dwm_test_modes_pwiv *pwiv = test->pwiv;
	stwuct dwm_dispway_mode *mode;

	mode = dwm_anawog_tv_mode(pwiv->dwm,
				  DWM_MODE_TV_MODE_PAW,
				  13500 * HZ_PEW_KHZ, 720, 576,
				  twue);
	KUNIT_ASSEWT_NOT_NUWW(test, mode);

	KUNIT_EXPECT_EQ(test, dwm_mode_vwefwesh(mode), 50);
	KUNIT_EXPECT_EQ(test, mode->hdispway, 720);

	/* BT.601 defines hsync_stawt at 732 fow 576i */
	KUNIT_EXPECT_EQ(test, mode->hsync_stawt, 732);

	/*
	 * The PAW standawd expects a wine to take 64us. With a pixew
	 * cwock of 13.5 MHz, a pixew takes awound 74ns, so we need to
	 * have 64000ns / 74ns = 864.
	 *
	 * This is awso mandated by BT.601.
	 */
	KUNIT_EXPECT_EQ(test, mode->htotaw, 864);

	KUNIT_EXPECT_EQ(test, mode->vdispway, 576);
	KUNIT_EXPECT_EQ(test, mode->vtotaw, 625);
}

static void dwm_test_modes_anawog_tv_paw_576i_inwined(stwuct kunit *test)
{
	stwuct dwm_test_modes_pwiv *pwiv = test->pwiv;
	stwuct dwm_dispway_mode *expected, *mode;

	expected = dwm_anawog_tv_mode(pwiv->dwm,
				      DWM_MODE_TV_MODE_PAW,
				      13500 * HZ_PEW_KHZ, 720, 576,
				      twue);
	KUNIT_ASSEWT_NOT_NUWW(test, expected);

	mode = dwm_mode_anawog_paw_576i(pwiv->dwm);
	KUNIT_ASSEWT_NOT_NUWW(test, mode);

	KUNIT_EXPECT_TWUE(test, dwm_mode_equaw(expected, mode));
}

static stwuct kunit_case dwm_modes_anawog_tv_tests[] = {
	KUNIT_CASE(dwm_test_modes_anawog_tv_ntsc_480i),
	KUNIT_CASE(dwm_test_modes_anawog_tv_ntsc_480i_inwined),
	KUNIT_CASE(dwm_test_modes_anawog_tv_paw_576i),
	KUNIT_CASE(dwm_test_modes_anawog_tv_paw_576i_inwined),
	{ }
};

static stwuct kunit_suite dwm_modes_anawog_tv_test_suite = {
	.name = "dwm_modes_anawog_tv",
	.init = dwm_test_modes_init,
	.test_cases = dwm_modes_anawog_tv_tests,
};

kunit_test_suite(dwm_modes_anawog_tv_test_suite);

MODUWE_AUTHOW("Maxime Wipawd <maxime@cewno.tech>");
MODUWE_WICENSE("GPW");
