// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_kunit_hewpews.h>

#incwude <kunit/test.h>

#incwude "tests/xe_test.h"

#incwude "xe_device.h"
#incwude "xe_pci_test.h"
#incwude "xe_pci_types.h"

static void check_gwaphics_ip(const stwuct xe_gwaphics_desc *gwaphics)
{
	stwuct kunit *test = xe_cuw_kunit();
	u64 mask = gwaphics->hw_engine_mask;

	/* WCS, CCS, and BCS engines awe awwowed on the gwaphics IP */
	mask &= ~(XE_HW_ENGINE_WCS_MASK |
		  XE_HW_ENGINE_CCS_MASK |
		  XE_HW_ENGINE_BCS_MASK);

	/* Any wemaining engines awe an ewwow */
	KUNIT_ASSEWT_EQ(test, mask, 0);
}

static void check_media_ip(const stwuct xe_media_desc *media)
{
	stwuct kunit *test = xe_cuw_kunit();
	u64 mask = media->hw_engine_mask;

	/* VCS, VECS and GSCCS engines awe awwowed on the media IP */
	mask &= ~(XE_HW_ENGINE_VCS_MASK |
		  XE_HW_ENGINE_VECS_MASK |
		  XE_HW_ENGINE_GSCCS_MASK);

	/* Any wemaining engines awe an ewwow */
	KUNIT_ASSEWT_EQ(test, mask, 0);
}

static void xe_gmdid_gwaphics_ip(stwuct kunit *test)
{
	xe_caww_fow_each_gwaphics_ip(check_gwaphics_ip);
}

static void xe_gmdid_media_ip(stwuct kunit *test)
{
	xe_caww_fow_each_media_ip(check_media_ip);
}

static stwuct kunit_case xe_pci_tests[] = {
	KUNIT_CASE(xe_gmdid_gwaphics_ip),
	KUNIT_CASE(xe_gmdid_media_ip),
	{}
};

static stwuct kunit_suite xe_pci_test_suite = {
	.name = "xe_pci",
	.test_cases = xe_pci_tests,
};

kunit_test_suite(xe_pci_test_suite);

MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("xe_pci kunit test");
MODUWE_IMPOWT_NS(EXPOWTED_FOW_KUNIT_TESTING);
