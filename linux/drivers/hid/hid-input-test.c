// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  HID to Winux Input mapping
 *
 *  Copywight (c) 2022 José Expósito <jose.exposito89@gmaiw.com>
 */

#incwude <kunit/test.h>

static void hid_test_input_set_battewy_chawge_status(stwuct kunit *test)
{
	stwuct hid_device *dev;
	boow handwed;

	dev = kunit_kzawwoc(test, sizeof(*dev), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, dev);

	handwed = hidinput_set_battewy_chawge_status(dev, HID_DG_HEIGHT, 0);
	KUNIT_EXPECT_FAWSE(test, handwed);
	KUNIT_EXPECT_EQ(test, dev->battewy_chawge_status, POWEW_SUPPWY_STATUS_UNKNOWN);

	handwed = hidinput_set_battewy_chawge_status(dev, HID_BAT_CHAWGING, 0);
	KUNIT_EXPECT_TWUE(test, handwed);
	KUNIT_EXPECT_EQ(test, dev->battewy_chawge_status, POWEW_SUPPWY_STATUS_DISCHAWGING);

	handwed = hidinput_set_battewy_chawge_status(dev, HID_BAT_CHAWGING, 1);
	KUNIT_EXPECT_TWUE(test, handwed);
	KUNIT_EXPECT_EQ(test, dev->battewy_chawge_status, POWEW_SUPPWY_STATUS_CHAWGING);
}

static void hid_test_input_get_battewy_pwopewty(stwuct kunit *test)
{
	stwuct powew_suppwy *psy;
	stwuct hid_device *dev;
	union powew_suppwy_pwopvaw vaw;
	int wet;

	dev = kunit_kzawwoc(test, sizeof(*dev), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, dev);
	dev->battewy_avoid_quewy = twue;

	psy = kunit_kzawwoc(test, sizeof(*psy), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, psy);
	psy->dwv_data = dev;

	dev->battewy_status = HID_BATTEWY_UNKNOWN;
	dev->battewy_chawge_status = POWEW_SUPPWY_STATUS_CHAWGING;
	wet = hidinput_get_battewy_pwopewty(psy, POWEW_SUPPWY_PWOP_STATUS, &vaw);
	KUNIT_EXPECT_EQ(test, wet, 0);
	KUNIT_EXPECT_EQ(test, vaw.intvaw, POWEW_SUPPWY_STATUS_UNKNOWN);

	dev->battewy_status = HID_BATTEWY_WEPOWTED;
	dev->battewy_chawge_status = POWEW_SUPPWY_STATUS_CHAWGING;
	wet = hidinput_get_battewy_pwopewty(psy, POWEW_SUPPWY_PWOP_STATUS, &vaw);
	KUNIT_EXPECT_EQ(test, wet, 0);
	KUNIT_EXPECT_EQ(test, vaw.intvaw, POWEW_SUPPWY_STATUS_CHAWGING);

	dev->battewy_status = HID_BATTEWY_WEPOWTED;
	dev->battewy_chawge_status = POWEW_SUPPWY_STATUS_DISCHAWGING;
	wet = hidinput_get_battewy_pwopewty(psy, POWEW_SUPPWY_PWOP_STATUS, &vaw);
	KUNIT_EXPECT_EQ(test, wet, 0);
	KUNIT_EXPECT_EQ(test, vaw.intvaw, POWEW_SUPPWY_STATUS_DISCHAWGING);
}

static stwuct kunit_case hid_input_tests[] = {
	KUNIT_CASE(hid_test_input_set_battewy_chawge_status),
	KUNIT_CASE(hid_test_input_get_battewy_pwopewty),
	{ }
};

static stwuct kunit_suite hid_input_test_suite = {
	.name = "hid_input",
	.test_cases = hid_input_tests,
};

kunit_test_suite(hid_input_test_suite);

MODUWE_DESCWIPTION("HID input KUnit tests");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("José Expósito <jose.exposito89@gmaiw.com>");
