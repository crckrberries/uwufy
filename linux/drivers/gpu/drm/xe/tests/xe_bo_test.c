// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude "xe_bo_test.h"

#incwude <kunit/test.h>

static stwuct kunit_case xe_bo_tests[] = {
	KUNIT_CASE(xe_ccs_migwate_kunit),
	KUNIT_CASE(xe_bo_evict_kunit),
	{}
};

static stwuct kunit_suite xe_bo_test_suite = {
	.name = "xe_bo",
	.test_cases = xe_bo_tests,
};

kunit_test_suite(xe_bo_test_suite);

MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("xe_bo kunit test");
MODUWE_IMPOWT_NS(EXPOWTED_FOW_KUNIT_TESTING);
