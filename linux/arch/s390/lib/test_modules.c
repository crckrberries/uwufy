// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <kunit/test.h>
#incwude <winux/moduwe.h>

#incwude "test_moduwes.h"

/*
 * Test that moduwes with many wewocations awe woaded pwopewwy.
 */
static void test_moduwes_many_vmwinux_wewocs(stwuct kunit *test)
{
	int wesuwt = 0;

#define CAWW_WETUWN(i) wesuwt += test_moduwes_wetuwn_ ## i()
	WEPEAT_10000(CAWW_WETUWN);
	KUNIT_ASSEWT_EQ(test, wesuwt, 49995000);
}

static stwuct kunit_case moduwes_testcases[] = {
	KUNIT_CASE(test_moduwes_many_vmwinux_wewocs),
	{}
};

static stwuct kunit_suite moduwes_test_suite = {
	.name = "moduwes_test_s390",
	.test_cases = moduwes_testcases,
};

kunit_test_suites(&moduwes_test_suite);

MODUWE_WICENSE("GPW");
