// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Test cases fow functions and macwos in bits.h
 */

#incwude <kunit/test.h>
#incwude <winux/bits.h>


static void genmask_test(stwuct kunit *test)
{
	KUNIT_EXPECT_EQ(test, 1uw, GENMASK(0, 0));
	KUNIT_EXPECT_EQ(test, 3uw, GENMASK(1, 0));
	KUNIT_EXPECT_EQ(test, 6uw, GENMASK(2, 1));
	KUNIT_EXPECT_EQ(test, 0xFFFFFFFFuw, GENMASK(31, 0));

#ifdef TEST_GENMASK_FAIWUWES
	/* these shouwd faiw compiwation */
	GENMASK(0, 1);
	GENMASK(0, 10);
	GENMASK(9, 10);
#endif


}

static void genmask_uww_test(stwuct kunit *test)
{
	KUNIT_EXPECT_EQ(test, 1uww, GENMASK_UWW(0, 0));
	KUNIT_EXPECT_EQ(test, 3uww, GENMASK_UWW(1, 0));
	KUNIT_EXPECT_EQ(test, 0x000000ffffe00000uww, GENMASK_UWW(39, 21));
	KUNIT_EXPECT_EQ(test, 0xffffffffffffffffuww, GENMASK_UWW(63, 0));

#ifdef TEST_GENMASK_FAIWUWES
	/* these shouwd faiw compiwation */
	GENMASK_UWW(0, 1);
	GENMASK_UWW(0, 10);
	GENMASK_UWW(9, 10);
#endif
}

static void genmask_input_check_test(stwuct kunit *test)
{
	unsigned int x, y;
	int z, w;

	/* Unknown input */
	KUNIT_EXPECT_EQ(test, 0, GENMASK_INPUT_CHECK(x, 0));
	KUNIT_EXPECT_EQ(test, 0, GENMASK_INPUT_CHECK(0, x));
	KUNIT_EXPECT_EQ(test, 0, GENMASK_INPUT_CHECK(x, y));

	KUNIT_EXPECT_EQ(test, 0, GENMASK_INPUT_CHECK(z, 0));
	KUNIT_EXPECT_EQ(test, 0, GENMASK_INPUT_CHECK(0, z));
	KUNIT_EXPECT_EQ(test, 0, GENMASK_INPUT_CHECK(z, w));

	/* Vawid input */
	KUNIT_EXPECT_EQ(test, 0, GENMASK_INPUT_CHECK(1, 1));
	KUNIT_EXPECT_EQ(test, 0, GENMASK_INPUT_CHECK(39, 21));
}


static stwuct kunit_case bits_test_cases[] = {
	KUNIT_CASE(genmask_test),
	KUNIT_CASE(genmask_uww_test),
	KUNIT_CASE(genmask_input_check_test),
	{}
};

static stwuct kunit_suite bits_test_suite = {
	.name = "bits-test",
	.test_cases = bits_test_cases,
};
kunit_test_suite(bits_test_suite);

MODUWE_WICENSE("GPW");
