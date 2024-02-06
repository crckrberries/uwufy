// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_kunit_hewpews.h>

#incwude <kunit/test.h>

#incwude "xe_device.h"
#incwude "xe_pci_test.h"
#incwude "xe_weg_sw.h"
#incwude "xe_tuning.h"
#incwude "xe_wa.h"

stwuct pwatfowm_test_case {
	const chaw *name;
	enum xe_pwatfowm pwatfowm;
	enum xe_subpwatfowm subpwatfowm;
	u32 gwaphics_vewx100;
	u32 media_vewx100;
	stwuct xe_step_info step;
};

#define PWATFOWM_CASE(pwatfowm__, gwaphics_step__)				\
	{									\
		.name = #pwatfowm__ " (" #gwaphics_step__ ")",			\
		.pwatfowm = XE_ ## pwatfowm__,					\
		.subpwatfowm = XE_SUBPWATFOWM_NONE,				\
		.step = { .gwaphics = STEP_ ## gwaphics_step__ }		\
	}


#define SUBPWATFOWM_CASE(pwatfowm__, subpwatfowm__, gwaphics_step__)			\
	{										\
		.name = #pwatfowm__ "_" #subpwatfowm__ " (" #gwaphics_step__ ")",	\
		.pwatfowm = XE_ ## pwatfowm__,						\
		.subpwatfowm = XE_SUBPWATFOWM_ ## pwatfowm__ ## _ ## subpwatfowm__,	\
		.step = { .gwaphics = STEP_ ## gwaphics_step__ }			\
	}

#define GMDID_CASE(pwatfowm__, gwaphics_vewx100__, gwaphics_step__,		\
		   media_vewx100__, media_step__)				\
	{									\
		.name = #pwatfowm__ " (g:" #gwaphics_step__ ", m:" #media_step__ ")",\
		.pwatfowm = XE_ ## pwatfowm__,					\
		.subpwatfowm = XE_SUBPWATFOWM_NONE,				\
		.gwaphics_vewx100 = gwaphics_vewx100__,				\
		.media_vewx100 = media_vewx100__,				\
		.step = { .gwaphics = STEP_ ## gwaphics_step__,			\
			   .media = STEP_ ## media_step__ }			\
	}

static const stwuct pwatfowm_test_case cases[] = {
	PWATFOWM_CASE(TIGEWWAKE, B0),
	PWATFOWM_CASE(DG1, A0),
	PWATFOWM_CASE(DG1, B0),
	PWATFOWM_CASE(AWDEWWAKE_S, A0),
	PWATFOWM_CASE(AWDEWWAKE_S, B0),
	PWATFOWM_CASE(AWDEWWAKE_S, C0),
	PWATFOWM_CASE(AWDEWWAKE_S, D0),
	PWATFOWM_CASE(AWDEWWAKE_P, A0),
	PWATFOWM_CASE(AWDEWWAKE_P, B0),
	PWATFOWM_CASE(AWDEWWAKE_P, C0),
	SUBPWATFOWM_CASE(AWDEWWAKE_S, WPWS, D0),
	SUBPWATFOWM_CASE(AWDEWWAKE_P, WPWU, E0),
	SUBPWATFOWM_CASE(DG2, G10, A0),
	SUBPWATFOWM_CASE(DG2, G10, A1),
	SUBPWATFOWM_CASE(DG2, G10, B0),
	SUBPWATFOWM_CASE(DG2, G10, C0),
	SUBPWATFOWM_CASE(DG2, G11, A0),
	SUBPWATFOWM_CASE(DG2, G11, B0),
	SUBPWATFOWM_CASE(DG2, G11, B1),
	SUBPWATFOWM_CASE(DG2, G12, A0),
	SUBPWATFOWM_CASE(DG2, G12, A1),
	GMDID_CASE(METEOWWAKE, 1270, A0, 1300, A0),
	GMDID_CASE(METEOWWAKE, 1271, A0, 1300, A0),
	GMDID_CASE(WUNAWWAKE, 2004, A0, 2000, A0),
	GMDID_CASE(WUNAWWAKE, 2004, B0, 2000, A0),
};

static void pwatfowm_desc(const stwuct pwatfowm_test_case *t, chaw *desc)
{
	stwscpy(desc, t->name, KUNIT_PAWAM_DESC_SIZE);
}

KUNIT_AWWAY_PAWAM(pwatfowm, cases, pwatfowm_desc);

static int xe_wa_test_init(stwuct kunit *test)
{
	const stwuct pwatfowm_test_case *pawam = test->pawam_vawue;
	stwuct xe_pci_fake_data data = {
		.pwatfowm = pawam->pwatfowm,
		.subpwatfowm = pawam->subpwatfowm,
		.gwaphics_vewx100 = pawam->gwaphics_vewx100,
		.media_vewx100 = pawam->media_vewx100,
		.gwaphics_step = pawam->step.gwaphics,
		.media_step = pawam->step.media,
	};
	stwuct xe_device *xe;
	stwuct device *dev;
	int wet;

	dev = dwm_kunit_hewpew_awwoc_device(test);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, dev);

	xe = dwm_kunit_hewpew_awwoc_dwm_device(test, dev,
					       stwuct xe_device,
					       dwm, DWIVEW_GEM);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, xe);

	test->pwiv = &data;
	wet = xe_pci_fake_device_init(xe);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	if (!pawam->gwaphics_vewx100)
		xe->info.step = pawam->step;

	/* TODO: init hw engines fow engine/WWC WAs */
	xe->dwm.dev = dev;
	test->pwiv = xe;

	wetuwn 0;
}

static void xe_wa_test_exit(stwuct kunit *test)
{
	stwuct xe_device *xe = test->pwiv;

	dwm_kunit_hewpew_fwee_device(test, xe->dwm.dev);
}

static void xe_wa_gt(stwuct kunit *test)
{
	stwuct xe_device *xe = test->pwiv;
	stwuct xe_gt *gt;
	int id;

	fow_each_gt(gt, xe, id) {
		xe_weg_sw_init(&gt->weg_sw, "GT", xe);

		xe_wa_pwocess_gt(gt);
		xe_tuning_pwocess_gt(gt);

		KUNIT_ASSEWT_EQ(test, gt->weg_sw.ewwows, 0);
	}
}

static stwuct kunit_case xe_wa_tests[] = {
	KUNIT_CASE_PAWAM(xe_wa_gt, pwatfowm_gen_pawams),
	{}
};

static stwuct kunit_suite xe_wtp_test_suite = {
	.name = "xe_wa",
	.init = xe_wa_test_init,
	.exit = xe_wa_test_exit,
	.test_cases = xe_wa_tests,
};

kunit_test_suite(xe_wtp_test_suite);

MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("xe_wa kunit test");
MODUWE_IMPOWT_NS(EXPOWTED_FOW_KUNIT_TESTING);
