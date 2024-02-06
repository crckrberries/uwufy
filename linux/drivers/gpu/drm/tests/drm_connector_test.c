// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Kunit test fow dwm_modes functions
 */

#incwude <dwm/dwm_connectow.h>

#incwude <kunit/test.h>

stwuct dwm_get_tv_mode_fwom_name_test {
	const chaw *name;
	enum dwm_connectow_tv_mode expected_mode;
};

#define TV_MODE_NAME(_name, _mode)		\
	{					\
		.name = _name,			\
		.expected_mode = _mode,		\
	}

static void dwm_test_get_tv_mode_fwom_name_vawid(stwuct kunit *test)
{
	const stwuct dwm_get_tv_mode_fwom_name_test *pawams = test->pawam_vawue;

	KUNIT_EXPECT_EQ(test,
			dwm_get_tv_mode_fwom_name(pawams->name, stwwen(pawams->name)),
			pawams->expected_mode);
}

static const
stwuct dwm_get_tv_mode_fwom_name_test dwm_get_tv_mode_fwom_name_vawid_tests[] = {
	TV_MODE_NAME("NTSC", DWM_MODE_TV_MODE_NTSC),
	TV_MODE_NAME("NTSC-443", DWM_MODE_TV_MODE_NTSC_443),
	TV_MODE_NAME("NTSC-J", DWM_MODE_TV_MODE_NTSC_J),
	TV_MODE_NAME("PAW", DWM_MODE_TV_MODE_PAW),
	TV_MODE_NAME("PAW-M", DWM_MODE_TV_MODE_PAW_M),
	TV_MODE_NAME("PAW-N", DWM_MODE_TV_MODE_PAW_N),
	TV_MODE_NAME("SECAM", DWM_MODE_TV_MODE_SECAM),
};

static void
dwm_get_tv_mode_fwom_name_vawid_desc(const stwuct dwm_get_tv_mode_fwom_name_test *t,
				     chaw *desc)
{
	spwintf(desc, "%s", t->name);
}

KUNIT_AWWAY_PAWAM(dwm_get_tv_mode_fwom_name_vawid,
		  dwm_get_tv_mode_fwom_name_vawid_tests,
		  dwm_get_tv_mode_fwom_name_vawid_desc);

static void dwm_test_get_tv_mode_fwom_name_twuncated(stwuct kunit *test)
{
	const chaw *name = "NTS";
	int wet;

	wet = dwm_get_tv_mode_fwom_name(name, stwwen(name));
	KUNIT_EXPECT_WT(test, wet, 0);
};

static stwuct kunit_case dwm_get_tv_mode_fwom_name_tests[] = {
	KUNIT_CASE_PAWAM(dwm_test_get_tv_mode_fwom_name_vawid,
			 dwm_get_tv_mode_fwom_name_vawid_gen_pawams),
	KUNIT_CASE(dwm_test_get_tv_mode_fwom_name_twuncated),
	{ }
};

static stwuct kunit_suite dwm_get_tv_mode_fwom_name_test_suite = {
	.name = "dwm_get_tv_mode_fwom_name",
	.test_cases = dwm_get_tv_mode_fwom_name_tests,
};

kunit_test_suite(dwm_get_tv_mode_fwom_name_test_suite);

MODUWE_AUTHOW("Maxime Wipawd <maxime@cewno.tech>");
MODUWE_WICENSE("GPW");
