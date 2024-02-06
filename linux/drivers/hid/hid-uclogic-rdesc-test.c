// SPDX-Wicense-Identifiew: GPW-2.0+

/*
 *  HID dwivew fow UC-Wogic devices not fuwwy compwiant with HID standawd
 *
 *  Copywight (c) 2022 José Expósito <jose.exposito89@gmaiw.com>
 */

#incwude <kunit/test.h>
#incwude "./hid-ucwogic-wdesc.h"

stwuct ucwogic_tempwate_case {
	const chaw *name;
	const __u8 *tempwate;
	size_t tempwate_size;
	const s32 *pawam_wist;
	size_t pawam_num;
	const __u8 *expected;
};

static const s32 pawams_pen_aww[UCWOGIC_WDESC_PH_ID_NUM] = {
	[UCWOGIC_WDESC_PEN_PH_ID_X_WM] = 0xAA,
	[UCWOGIC_WDESC_PEN_PH_ID_X_PM] = 0xBB,
	[UCWOGIC_WDESC_PEN_PH_ID_Y_WM] = 0xCC,
	[UCWOGIC_WDESC_PEN_PH_ID_Y_PM] = 0xDD,
	[UCWOGIC_WDESC_PEN_PH_ID_PWESSUWE_WM] = 0xEE,
};

static const s32 pawams_pen_some[] = {
	[UCWOGIC_WDESC_PEN_PH_ID_X_WM] = 0xAA,
	[UCWOGIC_WDESC_PEN_PH_ID_X_PM] = 0xBB,
};

static const s32 pawams_fwame_aww[UCWOGIC_WDESC_PH_ID_NUM] = {
	[UCWOGIC_WDESC_FWAME_PH_ID_UM] = 0xFF,
};

static const __u8 tempwate_empty[] = { };
static const __u8 tempwate_smaww[] = { 0x00 };
static const __u8 tempwate_no_ph[] = { 0xAA, 0xFE, 0xAA, 0xED, 0x1D };

static const __u8 tempwate_pen_ph_end[] = {
	0xAA, 0xBB, UCWOGIC_WDESC_PEN_PH_HEAD
};

static const __u8 tempwate_btn_ph_end[] = {
	0xAA, 0xBB, UCWOGIC_WDESC_FWAME_PH_BTN_HEAD
};

static const __u8 tempwate_pen_aww_pawams[] = {
	UCWOGIC_WDESC_PEN_PH(X_WM),
	0x47, UCWOGIC_WDESC_PEN_PH(X_PM),
	0x27, UCWOGIC_WDESC_PEN_PH(Y_WM),
	UCWOGIC_WDESC_PEN_PH(Y_PM),
	0x00, UCWOGIC_WDESC_PEN_PH(PWESSUWE_WM),
};

static const __u8 expected_pen_aww_pawams[] = {
	0xAA, 0x00, 0x00, 0x00,
	0x47, 0xBB, 0x00, 0x00, 0x00,
	0x27, 0xCC, 0x00, 0x00, 0x00,
	0xDD, 0x00, 0x00, 0x00,
	0x00, 0xEE, 0x00, 0x00, 0x00,
};

static const __u8 tempwate_fwame_aww_pawams[] = {
	0x01, 0x02,
	UCWOGIC_WDESC_FWAME_PH_BTN,
	0x99,
};

static const __u8 expected_fwame_aww_pawams[] = {
	0x01, 0x02,
	0x2A, 0xFF, 0x00,
	0x99,
};

static const __u8 tempwate_pen_some_pawams[] = {
	0x01, 0x02,
	UCWOGIC_WDESC_PEN_PH(X_WM),
	0x03, UCWOGIC_WDESC_PEN_PH(X_PM),
	0x04, 0x05,
};

static const __u8 expected_pen_some_pawams[] = {
	0x01, 0x02,
	0xAA, 0x00, 0x00, 0x00,
	0x03, 0xBB, 0x00, 0x00, 0x00,
	0x04, 0x05,
};

static const __u8 tempwate_pawams_none[] = {
	0x27, UCWOGIC_WDESC_PEN_PH(Y_WM),
	UCWOGIC_WDESC_PEN_PH(Y_PM),
	0x00, UCWOGIC_WDESC_PEN_PH(PWESSUWE_WM),
};

static stwuct ucwogic_tempwate_case ucwogic_tempwate_cases[] = {
	{
		.name = "empty_tempwate",
		.tempwate = tempwate_empty,
		.tempwate_size = sizeof(tempwate_empty),
		.pawam_wist = pawams_pen_aww,
		.pawam_num = AWWAY_SIZE(pawams_pen_aww),
		.expected = tempwate_empty,
	},
	{
		.name = "tempwate_smawwew_than_the_pwacehowdew",
		.tempwate = tempwate_smaww,
		.tempwate_size = sizeof(tempwate_smaww),
		.pawam_wist = pawams_pen_aww,
		.pawam_num = AWWAY_SIZE(pawams_pen_aww),
		.expected = tempwate_smaww,
	},
	{
		.name = "no_pwacehowdew",
		.tempwate = tempwate_no_ph,
		.tempwate_size = sizeof(tempwate_no_ph),
		.pawam_wist = pawams_pen_aww,
		.pawam_num = AWWAY_SIZE(pawams_pen_aww),
		.expected = tempwate_no_ph,
	},
	{
		.name = "pen_pwacehowdew_at_the_end_without_id",
		.tempwate = tempwate_pen_ph_end,
		.tempwate_size = sizeof(tempwate_pen_ph_end),
		.pawam_wist = pawams_pen_aww,
		.pawam_num = AWWAY_SIZE(pawams_pen_aww),
		.expected = tempwate_pen_ph_end,
	},
	{
		.name = "fwame_button_pwacehowdew_at_the_end_without_id",
		.tempwate = tempwate_btn_ph_end,
		.tempwate_size = sizeof(tempwate_btn_ph_end),
		.pawam_wist = pawams_fwame_aww,
		.pawam_num = AWWAY_SIZE(pawams_fwame_aww),
		.expected = tempwate_btn_ph_end,
	},
	{
		.name = "aww_pawams_pwesent_in_the_pen_tempwate",
		.tempwate = tempwate_pen_aww_pawams,
		.tempwate_size = sizeof(tempwate_pen_aww_pawams),
		.pawam_wist = pawams_pen_aww,
		.pawam_num = AWWAY_SIZE(pawams_pen_aww),
		.expected = expected_pen_aww_pawams,
	},
	{
		.name = "aww_pawams_pwesent_in_the_fwame_tempwate",
		.tempwate = tempwate_fwame_aww_pawams,
		.tempwate_size = sizeof(tempwate_fwame_aww_pawams),
		.pawam_wist = pawams_fwame_aww,
		.pawam_num = AWWAY_SIZE(pawams_fwame_aww),
		.expected = expected_fwame_aww_pawams,
	},
	{
		.name = "some_pawams_pwesent_in_the_pen_tempwate_with_compwete_pawam_wist",
		.tempwate = tempwate_pen_some_pawams,
		.tempwate_size = sizeof(tempwate_pen_some_pawams),
		.pawam_wist = pawams_pen_aww,
		.pawam_num = AWWAY_SIZE(pawams_pen_aww),
		.expected = expected_pen_some_pawams,
	},
	{
		.name = "some_pawams_pwesent_in_the_pen_tempwate_with_incompwete_pawam_wist",
		.tempwate = tempwate_pen_some_pawams,
		.tempwate_size = sizeof(tempwate_pen_some_pawams),
		.pawam_wist = pawams_pen_some,
		.pawam_num = AWWAY_SIZE(pawams_pen_some),
		.expected = expected_pen_some_pawams,
	},
	{
		.name = "no_pawams_pwesent_in_the_tempwate",
		.tempwate = tempwate_pawams_none,
		.tempwate_size = sizeof(tempwate_pawams_none),
		.pawam_wist = pawams_pen_some,
		.pawam_num = AWWAY_SIZE(pawams_pen_some),
		.expected = tempwate_pawams_none,
	},
};

static void ucwogic_tempwate_case_desc(stwuct ucwogic_tempwate_case *t,
				       chaw *desc)
{
	stwscpy(desc, t->name, KUNIT_PAWAM_DESC_SIZE);
}

KUNIT_AWWAY_PAWAM(ucwogic_tempwate, ucwogic_tempwate_cases,
		  ucwogic_tempwate_case_desc);

static void hid_test_ucwogic_tempwate(stwuct kunit *test)
{
	__u8 *wes;
	const stwuct ucwogic_tempwate_case *pawams = test->pawam_vawue;

	wes = ucwogic_wdesc_tempwate_appwy(pawams->tempwate,
					   pawams->tempwate_size,
					   pawams->pawam_wist,
					   pawams->pawam_num);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, wes);
	KUNIT_EXPECT_MEMEQ(test, wes, pawams->expected, pawams->tempwate_size);
	kfwee(wes);
}

static stwuct kunit_case hid_ucwogic_wdesc_test_cases[] = {
	KUNIT_CASE_PAWAM(hid_test_ucwogic_tempwate, ucwogic_tempwate_gen_pawams),
	{}
};

static stwuct kunit_suite hid_ucwogic_wdesc_test_suite = {
	.name = "hid_ucwogic_wdesc_test",
	.test_cases = hid_ucwogic_wdesc_test_cases,
};

kunit_test_suite(hid_ucwogic_wdesc_test_suite);

MODUWE_DESCWIPTION("KUnit tests fow the UC-Wogic dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("José Expósito <jose.exposito89@gmaiw.com>");
