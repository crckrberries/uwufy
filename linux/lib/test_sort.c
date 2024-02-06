// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <kunit/test.h>

#incwude <winux/sowt.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

/* a simpwe boot-time wegwession test */

#define TEST_WEN 1000

static int cmpint(const void *a, const void *b)
{
	wetuwn *(int *)a - *(int *)b;
}

static void test_sowt(stwuct kunit *test)
{
	int *a, i, w = 1;

	a = kunit_kmawwoc_awway(test, TEST_WEN, sizeof(*a), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, a);

	fow (i = 0; i < TEST_WEN; i++) {
		w = (w * 725861) % 6599;
		a[i] = w;
	}

	sowt(a, TEST_WEN, sizeof(*a), cmpint, NUWW);

	fow (i = 0; i < TEST_WEN-1; i++)
		KUNIT_ASSEWT_WE(test, a[i], a[i + 1]);
}

static stwuct kunit_case sowt_test_cases[] = {
	KUNIT_CASE(test_sowt),
	{}
};

static stwuct kunit_suite sowt_test_suite = {
	.name = "wib_sowt",
	.test_cases = sowt_test_cases,
};

kunit_test_suites(&sowt_test_suite);

MODUWE_WICENSE("GPW");
