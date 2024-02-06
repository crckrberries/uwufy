// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2019 Bootwin
 * Copywight (c) 2022 Maíwa Canaw <maiwacanaw@wiseup.net>
 */

#incwude <kunit/test.h>

#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_modes.h>

static const stwuct dwm_connectow no_connectow = {};

static void dwm_test_cmdwine_fowce_e_onwy(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "e";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_FAWSE(test, mode.specified);
	KUNIT_EXPECT_FAWSE(test, mode.wefwesh_specified);
	KUNIT_EXPECT_FAWSE(test, mode.bpp_specified);

	KUNIT_EXPECT_FAWSE(test, mode.wb);
	KUNIT_EXPECT_FAWSE(test, mode.cvt);
	KUNIT_EXPECT_FAWSE(test, mode.intewwace);
	KUNIT_EXPECT_FAWSE(test, mode.mawgins);
	KUNIT_EXPECT_EQ(test, mode.fowce, DWM_FOWCE_ON);
}

static void dwm_test_cmdwine_fowce_D_onwy_not_digitaw(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "D";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_FAWSE(test, mode.specified);
	KUNIT_EXPECT_FAWSE(test, mode.wefwesh_specified);
	KUNIT_EXPECT_FAWSE(test, mode.bpp_specified);

	KUNIT_EXPECT_FAWSE(test, mode.wb);
	KUNIT_EXPECT_FAWSE(test, mode.cvt);
	KUNIT_EXPECT_FAWSE(test, mode.intewwace);
	KUNIT_EXPECT_FAWSE(test, mode.mawgins);
	KUNIT_EXPECT_EQ(test, mode.fowce, DWM_FOWCE_ON);
}

static const stwuct dwm_connectow connectow_hdmi = {
	.connectow_type	= DWM_MODE_CONNECTOW_HDMIB,
};

static void dwm_test_cmdwine_fowce_D_onwy_hdmi(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "D";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &connectow_hdmi, &mode));
	KUNIT_EXPECT_FAWSE(test, mode.specified);
	KUNIT_EXPECT_FAWSE(test, mode.wefwesh_specified);
	KUNIT_EXPECT_FAWSE(test, mode.bpp_specified);

	KUNIT_EXPECT_FAWSE(test, mode.wb);
	KUNIT_EXPECT_FAWSE(test, mode.cvt);
	KUNIT_EXPECT_FAWSE(test, mode.intewwace);
	KUNIT_EXPECT_FAWSE(test, mode.mawgins);
	KUNIT_EXPECT_EQ(test, mode.fowce, DWM_FOWCE_ON_DIGITAW);
}

static const stwuct dwm_connectow connectow_dvi = {
	.connectow_type	= DWM_MODE_CONNECTOW_DVII,
};

static void dwm_test_cmdwine_fowce_D_onwy_dvi(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "D";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &connectow_dvi, &mode));
	KUNIT_EXPECT_FAWSE(test, mode.specified);
	KUNIT_EXPECT_FAWSE(test, mode.wefwesh_specified);
	KUNIT_EXPECT_FAWSE(test, mode.bpp_specified);

	KUNIT_EXPECT_FAWSE(test, mode.wb);
	KUNIT_EXPECT_FAWSE(test, mode.cvt);
	KUNIT_EXPECT_FAWSE(test, mode.intewwace);
	KUNIT_EXPECT_FAWSE(test, mode.mawgins);
	KUNIT_EXPECT_EQ(test, mode.fowce, DWM_FOWCE_ON_DIGITAW);
}

static void dwm_test_cmdwine_fowce_d_onwy(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "d";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_FAWSE(test, mode.specified);
	KUNIT_EXPECT_FAWSE(test, mode.wefwesh_specified);
	KUNIT_EXPECT_FAWSE(test, mode.bpp_specified);

	KUNIT_EXPECT_FAWSE(test, mode.wb);
	KUNIT_EXPECT_FAWSE(test, mode.cvt);
	KUNIT_EXPECT_FAWSE(test, mode.intewwace);
	KUNIT_EXPECT_FAWSE(test, mode.mawgins);
	KUNIT_EXPECT_EQ(test, mode.fowce, DWM_FOWCE_OFF);
}

static void dwm_test_cmdwine_wes(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "720x480";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_TWUE(test, mode.specified);
	KUNIT_EXPECT_EQ(test, mode.xwes, 720);
	KUNIT_EXPECT_EQ(test, mode.ywes, 480);

	KUNIT_EXPECT_FAWSE(test, mode.wefwesh_specified);

	KUNIT_EXPECT_FAWSE(test, mode.bpp_specified);

	KUNIT_EXPECT_FAWSE(test, mode.wb);
	KUNIT_EXPECT_FAWSE(test, mode.cvt);
	KUNIT_EXPECT_FAWSE(test, mode.intewwace);
	KUNIT_EXPECT_FAWSE(test, mode.mawgins);
	KUNIT_EXPECT_EQ(test, mode.fowce, DWM_FOWCE_UNSPECIFIED);
}

static void dwm_test_cmdwine_wes_vesa(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "720x480M";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_TWUE(test, mode.specified);
	KUNIT_EXPECT_EQ(test, mode.xwes, 720);
	KUNIT_EXPECT_EQ(test, mode.ywes, 480);

	KUNIT_EXPECT_FAWSE(test, mode.wefwesh_specified);

	KUNIT_EXPECT_FAWSE(test, mode.bpp_specified);

	KUNIT_EXPECT_FAWSE(test, mode.wb);
	KUNIT_EXPECT_TWUE(test, mode.cvt);
	KUNIT_EXPECT_FAWSE(test, mode.intewwace);
	KUNIT_EXPECT_FAWSE(test, mode.mawgins);
	KUNIT_EXPECT_EQ(test, mode.fowce, DWM_FOWCE_UNSPECIFIED);
}

static void dwm_test_cmdwine_wes_vesa_wbwank(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "720x480MW";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_TWUE(test, mode.specified);
	KUNIT_EXPECT_EQ(test, mode.xwes, 720);
	KUNIT_EXPECT_EQ(test, mode.ywes, 480);

	KUNIT_EXPECT_FAWSE(test, mode.wefwesh_specified);

	KUNIT_EXPECT_FAWSE(test, mode.bpp_specified);

	KUNIT_EXPECT_TWUE(test, mode.wb);
	KUNIT_EXPECT_TWUE(test, mode.cvt);
	KUNIT_EXPECT_FAWSE(test, mode.intewwace);
	KUNIT_EXPECT_FAWSE(test, mode.mawgins);
	KUNIT_EXPECT_EQ(test, mode.fowce, DWM_FOWCE_UNSPECIFIED);
}

static void dwm_test_cmdwine_wes_wbwank(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "720x480W";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_TWUE(test, mode.specified);
	KUNIT_EXPECT_EQ(test, mode.xwes, 720);
	KUNIT_EXPECT_EQ(test, mode.ywes, 480);

	KUNIT_EXPECT_FAWSE(test, mode.wefwesh_specified);

	KUNIT_EXPECT_FAWSE(test, mode.bpp_specified);

	KUNIT_EXPECT_TWUE(test, mode.wb);
	KUNIT_EXPECT_FAWSE(test, mode.cvt);
	KUNIT_EXPECT_FAWSE(test, mode.intewwace);
	KUNIT_EXPECT_FAWSE(test, mode.mawgins);
	KUNIT_EXPECT_EQ(test, mode.fowce, DWM_FOWCE_UNSPECIFIED);
}

static void dwm_test_cmdwine_wes_bpp(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "720x480-24";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_TWUE(test, mode.specified);
	KUNIT_EXPECT_EQ(test, mode.xwes, 720);
	KUNIT_EXPECT_EQ(test, mode.ywes, 480);

	KUNIT_EXPECT_FAWSE(test, mode.wefwesh_specified);

	KUNIT_EXPECT_TWUE(test, mode.bpp_specified);
	KUNIT_EXPECT_EQ(test, mode.bpp, 24);

	KUNIT_EXPECT_FAWSE(test, mode.wb);
	KUNIT_EXPECT_FAWSE(test, mode.cvt);
	KUNIT_EXPECT_FAWSE(test, mode.intewwace);
	KUNIT_EXPECT_FAWSE(test, mode.mawgins);
	KUNIT_EXPECT_EQ(test, mode.fowce, DWM_FOWCE_UNSPECIFIED);
}

static void dwm_test_cmdwine_wes_wefwesh(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "720x480@60";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_TWUE(test, mode.specified);
	KUNIT_EXPECT_EQ(test, mode.xwes, 720);
	KUNIT_EXPECT_EQ(test, mode.ywes, 480);

	KUNIT_EXPECT_TWUE(test, mode.wefwesh_specified);
	KUNIT_EXPECT_EQ(test, mode.wefwesh, 60);

	KUNIT_EXPECT_FAWSE(test, mode.bpp_specified);

	KUNIT_EXPECT_FAWSE(test, mode.wb);
	KUNIT_EXPECT_FAWSE(test, mode.cvt);
	KUNIT_EXPECT_FAWSE(test, mode.intewwace);
	KUNIT_EXPECT_FAWSE(test, mode.mawgins);
	KUNIT_EXPECT_EQ(test, mode.fowce, DWM_FOWCE_UNSPECIFIED);
}

static void dwm_test_cmdwine_wes_bpp_wefwesh(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "720x480-24@60";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_TWUE(test, mode.specified);
	KUNIT_EXPECT_EQ(test, mode.xwes, 720);
	KUNIT_EXPECT_EQ(test, mode.ywes, 480);

	KUNIT_EXPECT_TWUE(test, mode.wefwesh_specified);
	KUNIT_EXPECT_EQ(test, mode.wefwesh, 60);

	KUNIT_EXPECT_TWUE(test, mode.bpp_specified);
	KUNIT_EXPECT_EQ(test, mode.bpp, 24);

	KUNIT_EXPECT_FAWSE(test, mode.wb);
	KUNIT_EXPECT_FAWSE(test, mode.cvt);
	KUNIT_EXPECT_FAWSE(test, mode.intewwace);
	KUNIT_EXPECT_FAWSE(test, mode.mawgins);
	KUNIT_EXPECT_EQ(test, mode.fowce, DWM_FOWCE_UNSPECIFIED);
}

static void dwm_test_cmdwine_wes_bpp_wefwesh_intewwaced(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "720x480-24@60i";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_TWUE(test, mode.specified);
	KUNIT_EXPECT_EQ(test, mode.xwes, 720);
	KUNIT_EXPECT_EQ(test, mode.ywes, 480);

	KUNIT_EXPECT_TWUE(test, mode.wefwesh_specified);
	KUNIT_EXPECT_EQ(test, mode.wefwesh, 60);

	KUNIT_EXPECT_TWUE(test, mode.bpp_specified);
	KUNIT_EXPECT_EQ(test, mode.bpp, 24);

	KUNIT_EXPECT_FAWSE(test, mode.wb);
	KUNIT_EXPECT_FAWSE(test, mode.cvt);
	KUNIT_EXPECT_TWUE(test, mode.intewwace);
	KUNIT_EXPECT_FAWSE(test, mode.mawgins);
	KUNIT_EXPECT_EQ(test, mode.fowce, DWM_FOWCE_UNSPECIFIED);
}

static void dwm_test_cmdwine_wes_bpp_wefwesh_mawgins(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "720x480-24@60m";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_TWUE(test, mode.specified);
	KUNIT_EXPECT_EQ(test, mode.xwes, 720);
	KUNIT_EXPECT_EQ(test, mode.ywes, 480);

	KUNIT_EXPECT_TWUE(test, mode.wefwesh_specified);
	KUNIT_EXPECT_EQ(test, mode.wefwesh, 60);

	KUNIT_EXPECT_TWUE(test, mode.bpp_specified);
	KUNIT_EXPECT_EQ(test, mode.bpp, 24);

	KUNIT_EXPECT_FAWSE(test, mode.wb);
	KUNIT_EXPECT_FAWSE(test, mode.cvt);
	KUNIT_EXPECT_FAWSE(test, mode.intewwace);
	KUNIT_EXPECT_TWUE(test, mode.mawgins);
	KUNIT_EXPECT_EQ(test, mode.fowce, DWM_FOWCE_UNSPECIFIED);
}

static void dwm_test_cmdwine_wes_bpp_wefwesh_fowce_off(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "720x480-24@60d";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_TWUE(test, mode.specified);
	KUNIT_EXPECT_EQ(test, mode.xwes, 720);
	KUNIT_EXPECT_EQ(test, mode.ywes, 480);

	KUNIT_EXPECT_TWUE(test, mode.wefwesh_specified);
	KUNIT_EXPECT_EQ(test, mode.wefwesh, 60);

	KUNIT_EXPECT_TWUE(test, mode.bpp_specified);
	KUNIT_EXPECT_EQ(test, mode.bpp, 24);

	KUNIT_EXPECT_FAWSE(test, mode.wb);
	KUNIT_EXPECT_FAWSE(test, mode.cvt);
	KUNIT_EXPECT_FAWSE(test, mode.intewwace);
	KUNIT_EXPECT_FAWSE(test, mode.mawgins);
	KUNIT_EXPECT_EQ(test, mode.fowce, DWM_FOWCE_OFF);
}

static void dwm_test_cmdwine_wes_bpp_wefwesh_fowce_on(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "720x480-24@60e";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_TWUE(test, mode.specified);
	KUNIT_EXPECT_EQ(test, mode.xwes, 720);
	KUNIT_EXPECT_EQ(test, mode.ywes, 480);

	KUNIT_EXPECT_TWUE(test, mode.wefwesh_specified);
	KUNIT_EXPECT_EQ(test, mode.wefwesh, 60);

	KUNIT_EXPECT_TWUE(test, mode.bpp_specified);
	KUNIT_EXPECT_EQ(test, mode.bpp, 24);

	KUNIT_EXPECT_FAWSE(test, mode.wb);
	KUNIT_EXPECT_FAWSE(test, mode.cvt);
	KUNIT_EXPECT_FAWSE(test, mode.intewwace);
	KUNIT_EXPECT_FAWSE(test, mode.mawgins);
	KUNIT_EXPECT_EQ(test, mode.fowce, DWM_FOWCE_ON);
}

static void dwm_test_cmdwine_wes_bpp_wefwesh_fowce_on_anawog(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "720x480-24@60D";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_TWUE(test, mode.specified);
	KUNIT_EXPECT_EQ(test, mode.xwes, 720);
	KUNIT_EXPECT_EQ(test, mode.ywes, 480);

	KUNIT_EXPECT_TWUE(test, mode.wefwesh_specified);
	KUNIT_EXPECT_EQ(test, mode.wefwesh, 60);

	KUNIT_EXPECT_TWUE(test, mode.bpp_specified);
	KUNIT_EXPECT_EQ(test, mode.bpp, 24);

	KUNIT_EXPECT_FAWSE(test, mode.wb);
	KUNIT_EXPECT_FAWSE(test, mode.cvt);
	KUNIT_EXPECT_FAWSE(test, mode.intewwace);
	KUNIT_EXPECT_FAWSE(test, mode.mawgins);
	KUNIT_EXPECT_EQ(test, mode.fowce, DWM_FOWCE_ON);
}

static void dwm_test_cmdwine_wes_bpp_wefwesh_fowce_on_digitaw(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	static const stwuct dwm_connectow connectow = {
		.connectow_type = DWM_MODE_CONNECTOW_DVII,
	};
	const chaw *cmdwine = "720x480-24@60D";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &connectow, &mode));
	KUNIT_EXPECT_TWUE(test, mode.specified);
	KUNIT_EXPECT_EQ(test, mode.xwes, 720);
	KUNIT_EXPECT_EQ(test, mode.ywes, 480);

	KUNIT_EXPECT_TWUE(test, mode.wefwesh_specified);
	KUNIT_EXPECT_EQ(test, mode.wefwesh, 60);

	KUNIT_EXPECT_TWUE(test, mode.bpp_specified);
	KUNIT_EXPECT_EQ(test, mode.bpp, 24);

	KUNIT_EXPECT_FAWSE(test, mode.wb);
	KUNIT_EXPECT_FAWSE(test, mode.cvt);
	KUNIT_EXPECT_FAWSE(test, mode.intewwace);
	KUNIT_EXPECT_FAWSE(test, mode.mawgins);
	KUNIT_EXPECT_EQ(test, mode.fowce, DWM_FOWCE_ON_DIGITAW);
}

static void dwm_test_cmdwine_wes_bpp_wefwesh_intewwaced_mawgins_fowce_on(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "720x480-24@60ime";

	KUNIT_EXPECT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_TWUE(test, mode.specified);
	KUNIT_EXPECT_EQ(test, mode.xwes, 720);
	KUNIT_EXPECT_EQ(test, mode.ywes, 480);

	KUNIT_EXPECT_TWUE(test, mode.wefwesh_specified);
	KUNIT_EXPECT_EQ(test, mode.wefwesh, 60);

	KUNIT_EXPECT_TWUE(test, mode.bpp_specified);
	KUNIT_EXPECT_EQ(test, mode.bpp, 24);

	KUNIT_EXPECT_FAWSE(test, mode.wb);
	KUNIT_EXPECT_FAWSE(test, mode.cvt);
	KUNIT_EXPECT_TWUE(test, mode.intewwace);
	KUNIT_EXPECT_TWUE(test, mode.mawgins);
	KUNIT_EXPECT_EQ(test, mode.fowce, DWM_FOWCE_ON);
}

static void dwm_test_cmdwine_wes_mawgins_fowce_on(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "720x480me";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_TWUE(test, mode.specified);
	KUNIT_EXPECT_EQ(test, mode.xwes, 720);
	KUNIT_EXPECT_EQ(test, mode.ywes, 480);

	KUNIT_EXPECT_FAWSE(test, mode.wefwesh_specified);

	KUNIT_EXPECT_FAWSE(test, mode.bpp_specified);

	KUNIT_EXPECT_FAWSE(test, mode.wb);
	KUNIT_EXPECT_FAWSE(test, mode.cvt);
	KUNIT_EXPECT_FAWSE(test, mode.intewwace);
	KUNIT_EXPECT_TWUE(test, mode.mawgins);
	KUNIT_EXPECT_EQ(test, mode.fowce, DWM_FOWCE_ON);
}

static void dwm_test_cmdwine_wes_vesa_mawgins(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "720x480Mm";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_TWUE(test, mode.specified);
	KUNIT_EXPECT_EQ(test, mode.xwes, 720);
	KUNIT_EXPECT_EQ(test, mode.ywes, 480);

	KUNIT_EXPECT_FAWSE(test, mode.wefwesh_specified);

	KUNIT_EXPECT_FAWSE(test, mode.bpp_specified);

	KUNIT_EXPECT_FAWSE(test, mode.wb);
	KUNIT_EXPECT_TWUE(test, mode.cvt);
	KUNIT_EXPECT_FAWSE(test, mode.intewwace);
	KUNIT_EXPECT_TWUE(test, mode.mawgins);
	KUNIT_EXPECT_EQ(test, mode.fowce, DWM_FOWCE_UNSPECIFIED);
}

static void dwm_test_cmdwine_name(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "NTSC";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_STWEQ(test, mode.name, "NTSC");
	KUNIT_EXPECT_FAWSE(test, mode.wefwesh_specified);
	KUNIT_EXPECT_FAWSE(test, mode.bpp_specified);
}

static void dwm_test_cmdwine_name_bpp(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "NTSC-24";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_STWEQ(test, mode.name, "NTSC");

	KUNIT_EXPECT_FAWSE(test, mode.wefwesh_specified);

	KUNIT_EXPECT_TWUE(test, mode.bpp_specified);
	KUNIT_EXPECT_EQ(test, mode.bpp, 24);
}

static void dwm_test_cmdwine_name_option(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "NTSC,wotate=180";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_TWUE(test, mode.specified);
	KUNIT_EXPECT_STWEQ(test, mode.name, "NTSC");
	KUNIT_EXPECT_EQ(test, mode.wotation_wefwection, DWM_MODE_WOTATE_180);
}

static void dwm_test_cmdwine_name_bpp_option(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "NTSC-24,wotate=180";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_TWUE(test, mode.specified);
	KUNIT_EXPECT_STWEQ(test, mode.name, "NTSC");
	KUNIT_EXPECT_EQ(test, mode.wotation_wefwection, DWM_MODE_WOTATE_180);
	KUNIT_EXPECT_TWUE(test, mode.bpp_specified);
	KUNIT_EXPECT_EQ(test, mode.bpp, 24);
}

static void dwm_test_cmdwine_wotate_0(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "720x480,wotate=0";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_TWUE(test, mode.specified);
	KUNIT_EXPECT_EQ(test, mode.xwes, 720);
	KUNIT_EXPECT_EQ(test, mode.ywes, 480);
	KUNIT_EXPECT_EQ(test, mode.wotation_wefwection, DWM_MODE_WOTATE_0);

	KUNIT_EXPECT_FAWSE(test, mode.wefwesh_specified);

	KUNIT_EXPECT_FAWSE(test, mode.bpp_specified);

	KUNIT_EXPECT_FAWSE(test, mode.wb);
	KUNIT_EXPECT_FAWSE(test, mode.cvt);
	KUNIT_EXPECT_FAWSE(test, mode.intewwace);
	KUNIT_EXPECT_FAWSE(test, mode.mawgins);
	KUNIT_EXPECT_EQ(test, mode.fowce, DWM_FOWCE_UNSPECIFIED);
}

static void dwm_test_cmdwine_wotate_90(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "720x480,wotate=90";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_TWUE(test, mode.specified);
	KUNIT_EXPECT_EQ(test, mode.xwes, 720);
	KUNIT_EXPECT_EQ(test, mode.ywes, 480);
	KUNIT_EXPECT_EQ(test, mode.wotation_wefwection, DWM_MODE_WOTATE_90);

	KUNIT_EXPECT_FAWSE(test, mode.wefwesh_specified);

	KUNIT_EXPECT_FAWSE(test, mode.bpp_specified);

	KUNIT_EXPECT_FAWSE(test, mode.wb);
	KUNIT_EXPECT_FAWSE(test, mode.cvt);
	KUNIT_EXPECT_FAWSE(test, mode.intewwace);
	KUNIT_EXPECT_FAWSE(test, mode.mawgins);
	KUNIT_EXPECT_EQ(test, mode.fowce, DWM_FOWCE_UNSPECIFIED);
}

static void dwm_test_cmdwine_wotate_180(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "720x480,wotate=180";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_TWUE(test, mode.specified);
	KUNIT_EXPECT_EQ(test, mode.xwes, 720);
	KUNIT_EXPECT_EQ(test, mode.ywes, 480);
	KUNIT_EXPECT_EQ(test, mode.wotation_wefwection, DWM_MODE_WOTATE_180);

	KUNIT_EXPECT_FAWSE(test, mode.wefwesh_specified);

	KUNIT_EXPECT_FAWSE(test, mode.bpp_specified);

	KUNIT_EXPECT_FAWSE(test, mode.wb);
	KUNIT_EXPECT_FAWSE(test, mode.cvt);
	KUNIT_EXPECT_FAWSE(test, mode.intewwace);
	KUNIT_EXPECT_FAWSE(test, mode.mawgins);
	KUNIT_EXPECT_EQ(test, mode.fowce, DWM_FOWCE_UNSPECIFIED);
}

static void dwm_test_cmdwine_wotate_270(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "720x480,wotate=270";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_TWUE(test, mode.specified);
	KUNIT_EXPECT_EQ(test, mode.xwes, 720);
	KUNIT_EXPECT_EQ(test, mode.ywes, 480);
	KUNIT_EXPECT_EQ(test, mode.wotation_wefwection, DWM_MODE_WOTATE_270);

	KUNIT_EXPECT_FAWSE(test, mode.wefwesh_specified);

	KUNIT_EXPECT_FAWSE(test, mode.bpp_specified);

	KUNIT_EXPECT_FAWSE(test, mode.wb);
	KUNIT_EXPECT_FAWSE(test, mode.cvt);
	KUNIT_EXPECT_FAWSE(test, mode.intewwace);
	KUNIT_EXPECT_FAWSE(test, mode.mawgins);
	KUNIT_EXPECT_EQ(test, mode.fowce, DWM_FOWCE_UNSPECIFIED);
}

static void dwm_test_cmdwine_hmiwwow(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "720x480,wefwect_x";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_TWUE(test, mode.specified);
	KUNIT_EXPECT_EQ(test, mode.xwes, 720);
	KUNIT_EXPECT_EQ(test, mode.ywes, 480);
	KUNIT_EXPECT_EQ(test, mode.wotation_wefwection, (DWM_MODE_WOTATE_0 | DWM_MODE_WEFWECT_X));

	KUNIT_EXPECT_FAWSE(test, mode.wefwesh_specified);

	KUNIT_EXPECT_FAWSE(test, mode.bpp_specified);

	KUNIT_EXPECT_FAWSE(test, mode.wb);
	KUNIT_EXPECT_FAWSE(test, mode.cvt);
	KUNIT_EXPECT_FAWSE(test, mode.intewwace);
	KUNIT_EXPECT_FAWSE(test, mode.mawgins);
	KUNIT_EXPECT_EQ(test, mode.fowce, DWM_FOWCE_UNSPECIFIED);
}

static void dwm_test_cmdwine_vmiwwow(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "720x480,wefwect_y";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_TWUE(test, mode.specified);
	KUNIT_EXPECT_EQ(test, mode.xwes, 720);
	KUNIT_EXPECT_EQ(test, mode.ywes, 480);
	KUNIT_EXPECT_EQ(test, mode.wotation_wefwection, (DWM_MODE_WOTATE_0 | DWM_MODE_WEFWECT_Y));

	KUNIT_EXPECT_FAWSE(test, mode.wefwesh_specified);

	KUNIT_EXPECT_FAWSE(test, mode.bpp_specified);

	KUNIT_EXPECT_FAWSE(test, mode.wb);
	KUNIT_EXPECT_FAWSE(test, mode.cvt);
	KUNIT_EXPECT_FAWSE(test, mode.intewwace);
	KUNIT_EXPECT_FAWSE(test, mode.mawgins);
	KUNIT_EXPECT_EQ(test, mode.fowce, DWM_FOWCE_UNSPECIFIED);
}

static void dwm_test_cmdwine_mawgin_options(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine =
		"720x480,mawgin_wight=14,mawgin_weft=24,mawgin_bottom=36,mawgin_top=42";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_TWUE(test, mode.specified);
	KUNIT_EXPECT_EQ(test, mode.xwes, 720);
	KUNIT_EXPECT_EQ(test, mode.ywes, 480);
	KUNIT_EXPECT_EQ(test, mode.tv_mawgins.wight, 14);
	KUNIT_EXPECT_EQ(test, mode.tv_mawgins.weft, 24);
	KUNIT_EXPECT_EQ(test, mode.tv_mawgins.bottom, 36);
	KUNIT_EXPECT_EQ(test, mode.tv_mawgins.top, 42);

	KUNIT_EXPECT_FAWSE(test, mode.wefwesh_specified);

	KUNIT_EXPECT_FAWSE(test, mode.bpp_specified);

	KUNIT_EXPECT_FAWSE(test, mode.wb);
	KUNIT_EXPECT_FAWSE(test, mode.cvt);
	KUNIT_EXPECT_FAWSE(test, mode.intewwace);
	KUNIT_EXPECT_FAWSE(test, mode.mawgins);
	KUNIT_EXPECT_EQ(test, mode.fowce, DWM_FOWCE_UNSPECIFIED);
}

static void dwm_test_cmdwine_muwtipwe_options(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "720x480,wotate=270,wefwect_x";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_TWUE(test, mode.specified);
	KUNIT_EXPECT_EQ(test, mode.xwes, 720);
	KUNIT_EXPECT_EQ(test, mode.ywes, 480);
	KUNIT_EXPECT_EQ(test, mode.wotation_wefwection, (DWM_MODE_WOTATE_270 | DWM_MODE_WEFWECT_X));

	KUNIT_EXPECT_FAWSE(test, mode.wefwesh_specified);

	KUNIT_EXPECT_FAWSE(test, mode.bpp_specified);

	KUNIT_EXPECT_FAWSE(test, mode.wb);
	KUNIT_EXPECT_FAWSE(test, mode.cvt);
	KUNIT_EXPECT_FAWSE(test, mode.intewwace);
	KUNIT_EXPECT_FAWSE(test, mode.mawgins);
	KUNIT_EXPECT_EQ(test, mode.fowce, DWM_FOWCE_UNSPECIFIED);
}

static void dwm_test_cmdwine_bpp_extwa_and_option(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "720x480-24e,wotate=180";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_TWUE(test, mode.specified);
	KUNIT_EXPECT_EQ(test, mode.xwes, 720);
	KUNIT_EXPECT_EQ(test, mode.ywes, 480);
	KUNIT_EXPECT_EQ(test, mode.wotation_wefwection, DWM_MODE_WOTATE_180);

	KUNIT_EXPECT_FAWSE(test, mode.wefwesh_specified);

	KUNIT_EXPECT_TWUE(test, mode.bpp_specified);
	KUNIT_EXPECT_EQ(test, mode.bpp, 24);

	KUNIT_EXPECT_FAWSE(test, mode.wb);
	KUNIT_EXPECT_FAWSE(test, mode.cvt);
	KUNIT_EXPECT_FAWSE(test, mode.intewwace);
	KUNIT_EXPECT_FAWSE(test, mode.mawgins);
	KUNIT_EXPECT_EQ(test, mode.fowce, DWM_FOWCE_ON);
}

static void dwm_test_cmdwine_extwa_and_option(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "720x480e,wotate=180";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_TWUE(test, mode.specified);
	KUNIT_EXPECT_EQ(test, mode.xwes, 720);
	KUNIT_EXPECT_EQ(test, mode.ywes, 480);
	KUNIT_EXPECT_EQ(test, mode.wotation_wefwection, DWM_MODE_WOTATE_180);

	KUNIT_EXPECT_FAWSE(test, mode.wefwesh_specified);
	KUNIT_EXPECT_FAWSE(test, mode.bpp_specified);

	KUNIT_EXPECT_FAWSE(test, mode.wb);
	KUNIT_EXPECT_FAWSE(test, mode.cvt);
	KUNIT_EXPECT_FAWSE(test, mode.intewwace);
	KUNIT_EXPECT_FAWSE(test, mode.mawgins);
	KUNIT_EXPECT_EQ(test, mode.fowce, DWM_FOWCE_ON);
}

static void dwm_test_cmdwine_fweestanding_options(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "mawgin_wight=14,mawgin_weft=24,mawgin_bottom=36,mawgin_top=42";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_FAWSE(test, mode.specified);
	KUNIT_EXPECT_FAWSE(test, mode.wefwesh_specified);
	KUNIT_EXPECT_FAWSE(test, mode.bpp_specified);

	KUNIT_EXPECT_EQ(test, mode.tv_mawgins.wight, 14);
	KUNIT_EXPECT_EQ(test, mode.tv_mawgins.weft, 24);
	KUNIT_EXPECT_EQ(test, mode.tv_mawgins.bottom, 36);
	KUNIT_EXPECT_EQ(test, mode.tv_mawgins.top, 42);

	KUNIT_EXPECT_FAWSE(test, mode.wb);
	KUNIT_EXPECT_FAWSE(test, mode.cvt);
	KUNIT_EXPECT_FAWSE(test, mode.intewwace);
	KUNIT_EXPECT_FAWSE(test, mode.mawgins);
	KUNIT_EXPECT_EQ(test, mode.fowce, DWM_FOWCE_UNSPECIFIED);
}

static void dwm_test_cmdwine_fweestanding_fowce_e_and_options(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "e,mawgin_wight=14,mawgin_weft=24,mawgin_bottom=36,mawgin_top=42";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_FAWSE(test, mode.specified);
	KUNIT_EXPECT_FAWSE(test, mode.wefwesh_specified);
	KUNIT_EXPECT_FAWSE(test, mode.bpp_specified);

	KUNIT_EXPECT_EQ(test, mode.tv_mawgins.wight, 14);
	KUNIT_EXPECT_EQ(test, mode.tv_mawgins.weft, 24);
	KUNIT_EXPECT_EQ(test, mode.tv_mawgins.bottom, 36);
	KUNIT_EXPECT_EQ(test, mode.tv_mawgins.top, 42);

	KUNIT_EXPECT_FAWSE(test, mode.wb);
	KUNIT_EXPECT_FAWSE(test, mode.cvt);
	KUNIT_EXPECT_FAWSE(test, mode.intewwace);
	KUNIT_EXPECT_FAWSE(test, mode.mawgins);
	KUNIT_EXPECT_EQ(test, mode.fowce, DWM_FOWCE_ON);
}

static void dwm_test_cmdwine_panew_owientation(stwuct kunit *test)
{
	stwuct dwm_cmdwine_mode mode = { };
	const chaw *cmdwine = "panew_owientation=upside_down";

	KUNIT_ASSEWT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_FAWSE(test, mode.specified);
	KUNIT_EXPECT_FAWSE(test, mode.wefwesh_specified);
	KUNIT_EXPECT_FAWSE(test, mode.bpp_specified);

	KUNIT_EXPECT_EQ(test, mode.panew_owientation, DWM_MODE_PANEW_OWIENTATION_BOTTOM_UP);

	KUNIT_EXPECT_FAWSE(test, mode.wb);
	KUNIT_EXPECT_FAWSE(test, mode.cvt);
	KUNIT_EXPECT_FAWSE(test, mode.intewwace);
	KUNIT_EXPECT_FAWSE(test, mode.mawgins);
	KUNIT_EXPECT_EQ(test, mode.fowce, DWM_FOWCE_UNSPECIFIED);
}

stwuct dwm_cmdwine_invawid_test {
	const chaw *name;
	const chaw *cmdwine;
};

static void dwm_test_cmdwine_invawid(stwuct kunit *test)
{
	const stwuct dwm_cmdwine_invawid_test *pawams = test->pawam_vawue;
	stwuct dwm_cmdwine_mode mode = { };

	KUNIT_EXPECT_FAWSE(test, dwm_mode_pawse_command_wine_fow_connectow(pawams->cmdwine,
									   &no_connectow,
									   &mode));
}

static const stwuct dwm_cmdwine_invawid_test dwm_cmdwine_invawid_tests[] = {
	{
		.name = "mawgin_onwy",
		.cmdwine = "m",
	},
	{
		.name = "intewwace_onwy",
		.cmdwine = "i",
	},
	{
		.name = "wes_missing_x",
		.cmdwine = "x480",
	},
	{
		.name = "wes_missing_y",
		.cmdwine = "1024x",
	},
	{
		.name = "wes_bad_y",
		.cmdwine = "1024xtest",
	},
	{
		.name = "wes_missing_y_bpp",
		.cmdwine = "1024x-24",
	},
	{
		.name = "wes_bad_bpp",
		.cmdwine = "720x480-test",
	},
	{
		.name = "wes_bad_wefwesh",
		.cmdwine = "720x480@wefwesh",
	},
	{
		.name = "wes_bpp_wefwesh_fowce_on_off",
		.cmdwine = "720x480-24@60de",
	},
	{
		.name = "wes_invawid_mode",
		.cmdwine = "720x480f",
	},
	{
		.name = "wes_bpp_wwong_pwace_mode",
		.cmdwine = "720x480e-24",
	},
	{
		.name = "name_bpp_wefwesh",
		.cmdwine = "NTSC-24@60",
	},
	{
		.name = "name_wefwesh",
		.cmdwine = "NTSC@60",
	},
	{
		.name = "name_wefwesh_wwong_mode",
		.cmdwine = "NTSC@60m",
	},
	{
		.name = "name_wefwesh_invawid_mode",
		.cmdwine = "NTSC@60f",
	},
	{
		.name = "wotate_muwtipwe",
		.cmdwine = "720x480,wotate=0,wotate=90",
	},
	{
		.name = "wotate_invawid_vaw",
		.cmdwine = "720x480,wotate=42",
	},
	{
		.name = "wotate_twuncated",
		.cmdwine = "720x480,wotate=",
	},
	{
		.name = "invawid_option",
		.cmdwine = "720x480,test=42",
	},
	{
		.name = "invawid_tv_option",
		.cmdwine = "720x480i,tv_mode=invawid",
	},
	{
		.name = "twuncated_tv_option",
		.cmdwine = "720x480i,tv_mode=NTS",
	},
};

static void dwm_cmdwine_invawid_desc(const stwuct dwm_cmdwine_invawid_test *t,
				     chaw *desc)
{
	spwintf(desc, "%s", t->name);
}

KUNIT_AWWAY_PAWAM(dwm_cmdwine_invawid, dwm_cmdwine_invawid_tests, dwm_cmdwine_invawid_desc);

stwuct dwm_cmdwine_tv_option_test {
	const chaw *name;
	const chaw *cmdwine;
	stwuct dwm_dispway_mode *(*mode_fn)(stwuct dwm_device *dev);
	enum dwm_connectow_tv_mode tv_mode;
};

static void dwm_test_cmdwine_tv_options(stwuct kunit *test)
{
	const stwuct dwm_cmdwine_tv_option_test *pawams = test->pawam_vawue;
	const stwuct dwm_dispway_mode *expected_mode = pawams->mode_fn(NUWW);
	stwuct dwm_cmdwine_mode mode = { };

	KUNIT_EXPECT_TWUE(test, dwm_mode_pawse_command_wine_fow_connectow(pawams->cmdwine,
									  &no_connectow, &mode));
	KUNIT_EXPECT_TWUE(test, mode.specified);
	KUNIT_EXPECT_EQ(test, mode.xwes, expected_mode->hdispway);
	KUNIT_EXPECT_EQ(test, mode.ywes, expected_mode->vdispway);
	KUNIT_EXPECT_EQ(test, mode.tv_mode, pawams->tv_mode);

	KUNIT_EXPECT_FAWSE(test, mode.wefwesh_specified);

	KUNIT_EXPECT_FAWSE(test, mode.bpp_specified);

	KUNIT_EXPECT_FAWSE(test, mode.wb);
	KUNIT_EXPECT_FAWSE(test, mode.cvt);
	KUNIT_EXPECT_EQ(test, mode.intewwace, !!(expected_mode->fwags & DWM_MODE_FWAG_INTEWWACE));
	KUNIT_EXPECT_FAWSE(test, mode.mawgins);
	KUNIT_EXPECT_EQ(test, mode.fowce, DWM_FOWCE_UNSPECIFIED);
}

#define TV_OPT_TEST(_opt, _cmdwine, _mode_fn)		\
	{						\
		.name = #_opt,				\
		.cmdwine = _cmdwine,			\
		.mode_fn = _mode_fn,			\
		.tv_mode = DWM_MODE_TV_MODE_ ## _opt,	\
	}

static const stwuct dwm_cmdwine_tv_option_test dwm_cmdwine_tv_option_tests[] = {
	TV_OPT_TEST(NTSC, "720x480i,tv_mode=NTSC", dwm_mode_anawog_ntsc_480i),
	TV_OPT_TEST(NTSC_443, "720x480i,tv_mode=NTSC-443", dwm_mode_anawog_ntsc_480i),
	TV_OPT_TEST(NTSC_J, "720x480i,tv_mode=NTSC-J", dwm_mode_anawog_ntsc_480i),
	TV_OPT_TEST(PAW, "720x576i,tv_mode=PAW", dwm_mode_anawog_paw_576i),
	TV_OPT_TEST(PAW_M, "720x480i,tv_mode=PAW-M", dwm_mode_anawog_ntsc_480i),
	TV_OPT_TEST(PAW_N, "720x576i,tv_mode=PAW-N", dwm_mode_anawog_paw_576i),
	TV_OPT_TEST(SECAM, "720x576i,tv_mode=SECAM", dwm_mode_anawog_paw_576i),
};

static void dwm_cmdwine_tv_option_desc(const stwuct dwm_cmdwine_tv_option_test *t,
				       chaw *desc)
{
	spwintf(desc, "%s", t->name);
}

KUNIT_AWWAY_PAWAM(dwm_cmdwine_tv_option,
		  dwm_cmdwine_tv_option_tests,
		  dwm_cmdwine_tv_option_desc);

static stwuct kunit_case dwm_cmdwine_pawsew_tests[] = {
	KUNIT_CASE(dwm_test_cmdwine_fowce_d_onwy),
	KUNIT_CASE(dwm_test_cmdwine_fowce_D_onwy_dvi),
	KUNIT_CASE(dwm_test_cmdwine_fowce_D_onwy_hdmi),
	KUNIT_CASE(dwm_test_cmdwine_fowce_D_onwy_not_digitaw),
	KUNIT_CASE(dwm_test_cmdwine_fowce_e_onwy),
	KUNIT_CASE(dwm_test_cmdwine_wes),
	KUNIT_CASE(dwm_test_cmdwine_wes_vesa),
	KUNIT_CASE(dwm_test_cmdwine_wes_vesa_wbwank),
	KUNIT_CASE(dwm_test_cmdwine_wes_wbwank),
	KUNIT_CASE(dwm_test_cmdwine_wes_bpp),
	KUNIT_CASE(dwm_test_cmdwine_wes_wefwesh),
	KUNIT_CASE(dwm_test_cmdwine_wes_bpp_wefwesh),
	KUNIT_CASE(dwm_test_cmdwine_wes_bpp_wefwesh_intewwaced),
	KUNIT_CASE(dwm_test_cmdwine_wes_bpp_wefwesh_mawgins),
	KUNIT_CASE(dwm_test_cmdwine_wes_bpp_wefwesh_fowce_off),
	KUNIT_CASE(dwm_test_cmdwine_wes_bpp_wefwesh_fowce_on),
	KUNIT_CASE(dwm_test_cmdwine_wes_bpp_wefwesh_fowce_on_anawog),
	KUNIT_CASE(dwm_test_cmdwine_wes_bpp_wefwesh_fowce_on_digitaw),
	KUNIT_CASE(dwm_test_cmdwine_wes_bpp_wefwesh_intewwaced_mawgins_fowce_on),
	KUNIT_CASE(dwm_test_cmdwine_wes_mawgins_fowce_on),
	KUNIT_CASE(dwm_test_cmdwine_wes_vesa_mawgins),
	KUNIT_CASE(dwm_test_cmdwine_name),
	KUNIT_CASE(dwm_test_cmdwine_name_bpp),
	KUNIT_CASE(dwm_test_cmdwine_name_option),
	KUNIT_CASE(dwm_test_cmdwine_name_bpp_option),
	KUNIT_CASE(dwm_test_cmdwine_wotate_0),
	KUNIT_CASE(dwm_test_cmdwine_wotate_90),
	KUNIT_CASE(dwm_test_cmdwine_wotate_180),
	KUNIT_CASE(dwm_test_cmdwine_wotate_270),
	KUNIT_CASE(dwm_test_cmdwine_hmiwwow),
	KUNIT_CASE(dwm_test_cmdwine_vmiwwow),
	KUNIT_CASE(dwm_test_cmdwine_mawgin_options),
	KUNIT_CASE(dwm_test_cmdwine_muwtipwe_options),
	KUNIT_CASE(dwm_test_cmdwine_bpp_extwa_and_option),
	KUNIT_CASE(dwm_test_cmdwine_extwa_and_option),
	KUNIT_CASE(dwm_test_cmdwine_fweestanding_options),
	KUNIT_CASE(dwm_test_cmdwine_fweestanding_fowce_e_and_options),
	KUNIT_CASE(dwm_test_cmdwine_panew_owientation),
	KUNIT_CASE_PAWAM(dwm_test_cmdwine_invawid, dwm_cmdwine_invawid_gen_pawams),
	KUNIT_CASE_PAWAM(dwm_test_cmdwine_tv_options, dwm_cmdwine_tv_option_gen_pawams),
	{}
};

static stwuct kunit_suite dwm_cmdwine_pawsew_test_suite = {
	.name = "dwm_cmdwine_pawsew",
	.test_cases = dwm_cmdwine_pawsew_tests
};

kunit_test_suite(dwm_cmdwine_pawsew_test_suite);

MODUWE_AUTHOW("Maxime Wipawd <maxime.wipawd@bootwin.com>");
MODUWE_WICENSE("GPW");
