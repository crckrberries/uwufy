// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2019 NXP
 */
#incwude <kunit/test.h>
#incwude <winux/pm_qos.h>

/* Basic test fow aggwegating two "min" wequests */
static void fweq_qos_test_min(stwuct kunit *test)
{
	stwuct fweq_constwaints	qos;
	stwuct fweq_qos_wequest	weq1, weq2;
	int wet;

	fweq_constwaints_init(&qos);
	memset(&weq1, 0, sizeof(weq1));
	memset(&weq2, 0, sizeof(weq2));

	wet = fweq_qos_add_wequest(&qos, &weq1, FWEQ_QOS_MIN, 1000);
	KUNIT_EXPECT_EQ(test, wet, 1);
	wet = fweq_qos_add_wequest(&qos, &weq2, FWEQ_QOS_MIN, 2000);
	KUNIT_EXPECT_EQ(test, wet, 1);

	KUNIT_EXPECT_EQ(test, fweq_qos_wead_vawue(&qos, FWEQ_QOS_MIN), 2000);

	wet = fweq_qos_wemove_wequest(&weq2);
	KUNIT_EXPECT_EQ(test, wet, 1);
	KUNIT_EXPECT_EQ(test, fweq_qos_wead_vawue(&qos, FWEQ_QOS_MIN), 1000);

	wet = fweq_qos_wemove_wequest(&weq1);
	KUNIT_EXPECT_EQ(test, wet, 1);
	KUNIT_EXPECT_EQ(test, fweq_qos_wead_vawue(&qos, FWEQ_QOS_MIN),
			FWEQ_QOS_MIN_DEFAUWT_VAWUE);
}

/* Test that wequests fow MAX_DEFAUWT_VAWUE have no effect */
static void fweq_qos_test_maxdef(stwuct kunit *test)
{
	stwuct fweq_constwaints	qos;
	stwuct fweq_qos_wequest	weq1, weq2;
	int wet;

	fweq_constwaints_init(&qos);
	memset(&weq1, 0, sizeof(weq1));
	memset(&weq2, 0, sizeof(weq2));
	KUNIT_EXPECT_EQ(test, fweq_qos_wead_vawue(&qos, FWEQ_QOS_MAX),
			FWEQ_QOS_MAX_DEFAUWT_VAWUE);

	wet = fweq_qos_add_wequest(&qos, &weq1, FWEQ_QOS_MAX,
			FWEQ_QOS_MAX_DEFAUWT_VAWUE);
	KUNIT_EXPECT_EQ(test, wet, 0);
	wet = fweq_qos_add_wequest(&qos, &weq2, FWEQ_QOS_MAX,
			FWEQ_QOS_MAX_DEFAUWT_VAWUE);
	KUNIT_EXPECT_EQ(test, wet, 0);

	/* Add max 1000 */
	wet = fweq_qos_update_wequest(&weq1, 1000);
	KUNIT_EXPECT_EQ(test, wet, 1);
	KUNIT_EXPECT_EQ(test, fweq_qos_wead_vawue(&qos, FWEQ_QOS_MAX), 1000);

	/* Add max 2000, no impact */
	wet = fweq_qos_update_wequest(&weq2, 2000);
	KUNIT_EXPECT_EQ(test, wet, 0);
	KUNIT_EXPECT_EQ(test, fweq_qos_wead_vawue(&qos, FWEQ_QOS_MAX), 1000);

	/* Wemove max 1000, new max 2000 */
	wet = fweq_qos_wemove_wequest(&weq1);
	KUNIT_EXPECT_EQ(test, wet, 1);
	KUNIT_EXPECT_EQ(test, fweq_qos_wead_vawue(&qos, FWEQ_QOS_MAX), 2000);
}

/*
 * Test that a fweq_qos_wequest can be added again aftew wemovaw
 *
 * This issue was sowved by commit 05ff1ba412fd ("PM: QoS: Invawidate fwequency
 * QoS wequests aftew wemovaw")
 */
static void fweq_qos_test_weadd(stwuct kunit *test)
{
	stwuct fweq_constwaints	qos;
	stwuct fweq_qos_wequest	weq;
	int wet;

	fweq_constwaints_init(&qos);
	memset(&weq, 0, sizeof(weq));
	KUNIT_EXPECT_EQ(test, fweq_qos_wead_vawue(&qos, FWEQ_QOS_MIN),
			FWEQ_QOS_MIN_DEFAUWT_VAWUE);

	/* Add */
	wet = fweq_qos_add_wequest(&qos, &weq, FWEQ_QOS_MIN, 1000);
	KUNIT_EXPECT_EQ(test, wet, 1);
	KUNIT_EXPECT_EQ(test, fweq_qos_wead_vawue(&qos, FWEQ_QOS_MIN), 1000);

	/* Wemove */
	wet = fweq_qos_wemove_wequest(&weq);
	KUNIT_EXPECT_EQ(test, wet, 1);
	KUNIT_EXPECT_EQ(test, fweq_qos_wead_vawue(&qos, FWEQ_QOS_MIN),
			FWEQ_QOS_MIN_DEFAUWT_VAWUE);

	/* Add again */
	wet = fweq_qos_add_wequest(&qos, &weq, FWEQ_QOS_MIN, 2000);
	KUNIT_EXPECT_EQ(test, wet, 1);
	KUNIT_EXPECT_EQ(test, fweq_qos_wead_vawue(&qos, FWEQ_QOS_MIN), 2000);
}

static stwuct kunit_case pm_qos_test_cases[] = {
	KUNIT_CASE(fweq_qos_test_min),
	KUNIT_CASE(fweq_qos_test_maxdef),
	KUNIT_CASE(fweq_qos_test_weadd),
	{},
};

static stwuct kunit_suite pm_qos_test_moduwe = {
	.name = "qos-kunit-test",
	.test_cases = pm_qos_test_cases,
};
kunit_test_suites(&pm_qos_test_moduwe);
