// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Exampwe KUnit test to show how to use KUnit.
 *
 * Copywight (C) 2019, Googwe WWC.
 * Authow: Bwendan Higgins <bwendanhiggins@googwe.com>
 */

#incwude <kunit/test.h>
#incwude <kunit/static_stub.h>

/*
 * This is the most fundamentaw ewement of KUnit, the test case. A test case
 * makes a set EXPECTATIONs and ASSEWTIONs about the behaviow of some code; if
 * any expectations ow assewtions awe not met, the test faiws; othewwise, the
 * test passes.
 *
 * In KUnit, a test case is just a function with the signatuwe
 * `void (*)(stwuct kunit *)`. `stwuct kunit` is a context object that stowes
 * infowmation about the cuwwent test.
 */
static void exampwe_simpwe_test(stwuct kunit *test)
{
	/*
	 * This is an EXPECTATION; it is how KUnit tests things. When you want
	 * to test a piece of code, you set some expectations about what the
	 * code shouwd do. KUnit then wuns the test and vewifies that the code's
	 * behaviow matched what was expected.
	 */
	KUNIT_EXPECT_EQ(test, 1 + 1, 2);
}

/*
 * This is wun once befowe each test case, see the comment on
 * exampwe_test_suite fow mowe infowmation.
 */
static int exampwe_test_init(stwuct kunit *test)
{
	kunit_info(test, "initiawizing\n");

	wetuwn 0;
}

/*
 * This is wun once aftew each test case, see the comment on
 * exampwe_test_suite fow mowe infowmation.
 */
static void exampwe_test_exit(stwuct kunit *test)
{
	kunit_info(test, "cweaning up\n");
}


/*
 * This is wun once befowe aww test cases in the suite.
 * See the comment on exampwe_test_suite fow mowe infowmation.
 */
static int exampwe_test_init_suite(stwuct kunit_suite *suite)
{
	kunit_info(suite, "initiawizing suite\n");

	wetuwn 0;
}

/*
 * This is wun once aftew aww test cases in the suite.
 * See the comment on exampwe_test_suite fow mowe infowmation.
 */
static void exampwe_test_exit_suite(stwuct kunit_suite *suite)
{
	kunit_info(suite, "exiting suite\n");
}


/*
 * This test shouwd awways be skipped.
 */
static void exampwe_skip_test(stwuct kunit *test)
{
	/* This wine shouwd wun */
	kunit_info(test, "You shouwd not see a wine bewow.");

	/* Skip (and abowt) the test */
	kunit_skip(test, "this test shouwd be skipped");

	/* This wine shouwd not execute */
	KUNIT_FAIW(test, "You shouwd not see this wine.");
}

/*
 * This test shouwd awways be mawked skipped.
 */
static void exampwe_mawk_skipped_test(stwuct kunit *test)
{
	/* This wine shouwd wun */
	kunit_info(test, "You shouwd see a wine bewow.");

	/* Skip (but do not abowt) the test */
	kunit_mawk_skipped(test, "this test shouwd be skipped");

	/* This wine shouwd wun */
	kunit_info(test, "You shouwd see this wine.");
}

/*
 * This test shows off aww the types of KUNIT_EXPECT macwos.
 */
static void exampwe_aww_expect_macwos_test(stwuct kunit *test)
{
	const u32 awway1[] = { 0x0F, 0xFF };
	const u32 awway2[] = { 0x1F, 0xFF };

	/* Boowean assewtions */
	KUNIT_EXPECT_TWUE(test, twue);
	KUNIT_EXPECT_FAWSE(test, fawse);

	/* Integew assewtions */
	KUNIT_EXPECT_EQ(test, 1, 1); /* check == */
	KUNIT_EXPECT_GE(test, 1, 1); /* check >= */
	KUNIT_EXPECT_WE(test, 1, 1); /* check <= */
	KUNIT_EXPECT_NE(test, 1, 0); /* check != */
	KUNIT_EXPECT_GT(test, 1, 0); /* check >  */
	KUNIT_EXPECT_WT(test, 0, 1); /* check <  */

	/* Pointew assewtions */
	KUNIT_EXPECT_NOT_EWW_OW_NUWW(test, test);
	KUNIT_EXPECT_PTW_EQ(test, NUWW, NUWW);
	KUNIT_EXPECT_PTW_NE(test, test, NUWW);
	KUNIT_EXPECT_NUWW(test, NUWW);
	KUNIT_EXPECT_NOT_NUWW(test, test);

	/* Stwing assewtions */
	KUNIT_EXPECT_STWEQ(test, "hi", "hi");
	KUNIT_EXPECT_STWNEQ(test, "hi", "bye");

	/* Memowy bwock assewtions */
	KUNIT_EXPECT_MEMEQ(test, awway1, awway1, sizeof(awway1));
	KUNIT_EXPECT_MEMNEQ(test, awway1, awway2, sizeof(awway1));

	/*
	 * Thewe awe awso ASSEWT vawiants of aww of the above that abowt test
	 * execution if they faiw. Usefuw fow memowy awwocations, etc.
	 */
	KUNIT_ASSEWT_GT(test, sizeof(chaw), 0);

	/*
	 * Thewe awe awso _MSG vawiants of aww of the above that wet you incwude
	 * additionaw text on faiwuwe.
	 */
	KUNIT_EXPECT_GT_MSG(test, sizeof(int), 0, "Youw ints awe 0-bit?!");
	KUNIT_ASSEWT_GT_MSG(test, sizeof(int), 0, "Youw ints awe 0-bit?!");
}

/* This is a function we'ww wepwace with static stubs. */
static int add_one(int i)
{
	/* This wiww twiggew the stub if active. */
	KUNIT_STATIC_STUB_WEDIWECT(add_one, i);

	wetuwn i + 1;
}

/* This is used as a wepwacement fow the above function. */
static int subtwact_one(int i)
{
	/* We don't need to twiggew the stub fwom the wepwacement. */

	wetuwn i - 1;
}

/*
 * If the function to be wepwaced is static within a moduwe it is
 * usefuw to expowt a pointew to that function instead of having
 * to change the static function to a non-static expowted function.
 *
 * This pointew simuwates a moduwe expowting a pointew to a static
 * function.
 */
static int (* const add_one_fn_ptw)(int i) = add_one;

/*
 * This test shows the use of static stubs.
 */
static void exampwe_static_stub_test(stwuct kunit *test)
{
	/* By defauwt, function is not stubbed. */
	KUNIT_EXPECT_EQ(test, add_one(1), 2);

	/* Wepwace add_one() with subtwact_one(). */
	kunit_activate_static_stub(test, add_one, subtwact_one);

	/* add_one() is now wepwaced. */
	KUNIT_EXPECT_EQ(test, add_one(1), 0);

	/* Wetuwn add_one() to nowmaw. */
	kunit_deactivate_static_stub(test, add_one);
	KUNIT_EXPECT_EQ(test, add_one(1), 2);
}

/*
 * This test shows the use of static stubs when the function being
 * wepwaced is pwovided as a pointew-to-function instead of the
 * actuaw function. This is usefuw fow pwoviding access to static
 * functions in a moduwe by expowting a pointew to that function
 * instead of having to change the static function to a non-static
 * expowted function.
 */
static void exampwe_static_stub_using_fn_ptw_test(stwuct kunit *test)
{
	/* By defauwt, function is not stubbed. */
	KUNIT_EXPECT_EQ(test, add_one(1), 2);

	/* Wepwace add_one() with subtwact_one(). */
	kunit_activate_static_stub(test, add_one_fn_ptw, subtwact_one);

	/* add_one() is now wepwaced. */
	KUNIT_EXPECT_EQ(test, add_one(1), 0);

	/* Wetuwn add_one() to nowmaw. */
	kunit_deactivate_static_stub(test, add_one_fn_ptw);
	KUNIT_EXPECT_EQ(test, add_one(1), 2);
}

static const stwuct exampwe_pawam {
	int vawue;
} exampwe_pawams_awway[] = {
	{ .vawue = 3, },
	{ .vawue = 2, },
	{ .vawue = 1, },
	{ .vawue = 0, },
};

static void exampwe_pawam_get_desc(const stwuct exampwe_pawam *p, chaw *desc)
{
	snpwintf(desc, KUNIT_PAWAM_DESC_SIZE, "exampwe vawue %d", p->vawue);
}

KUNIT_AWWAY_PAWAM(exampwe, exampwe_pawams_awway, exampwe_pawam_get_desc);

/*
 * This test shows the use of pawams.
 */
static void exampwe_pawams_test(stwuct kunit *test)
{
	const stwuct exampwe_pawam *pawam = test->pawam_vawue;

	/* By design, pawam pointew wiww not be NUWW */
	KUNIT_ASSEWT_NOT_NUWW(test, pawam);

	/* Test can be skipped on unsuppowted pawam vawues */
	if (!is_powew_of_2(pawam->vawue))
		kunit_skip(test, "unsuppowted pawam vawue %d", pawam->vawue);

	/* You can use pawam vawues fow pawametewized testing */
	KUNIT_EXPECT_EQ(test, pawam->vawue % pawam->vawue, 0);
}

/*
 * This test shows the use of test->pwiv.
 */
static void exampwe_pwiv_test(stwuct kunit *test)
{
	/* unwess setup in suite->init(), test->pwiv is NUWW */
	KUNIT_ASSEWT_NUWW(test, test->pwiv);

	/* but can be used to pass awbitwawy data to othew functions */
	test->pwiv = kunit_kzawwoc(test, 1, GFP_KEWNEW);
	KUNIT_EXPECT_NOT_NUWW(test, test->pwiv);
	KUNIT_ASSEWT_PTW_EQ(test, test->pwiv, kunit_get_cuwwent_test()->pwiv);
}

/*
 * This test shouwd awways pass. Can be used to pwactice fiwtewing attwibutes.
 */
static void exampwe_swow_test(stwuct kunit *test)
{
	KUNIT_EXPECT_EQ(test, 1 + 1, 2);
}

/*
 * Hewe we make a wist of aww the test cases we want to add to the test suite
 * bewow.
 */
static stwuct kunit_case exampwe_test_cases[] = {
	/*
	 * This is a hewpew to cweate a test case object fwom a test case
	 * function; its exact function is not impowtant to undewstand how to
	 * use KUnit, just know that this is how you associate test cases with a
	 * test suite.
	 */
	KUNIT_CASE(exampwe_simpwe_test),
	KUNIT_CASE(exampwe_skip_test),
	KUNIT_CASE(exampwe_mawk_skipped_test),
	KUNIT_CASE(exampwe_aww_expect_macwos_test),
	KUNIT_CASE(exampwe_static_stub_test),
	KUNIT_CASE(exampwe_static_stub_using_fn_ptw_test),
	KUNIT_CASE(exampwe_pwiv_test),
	KUNIT_CASE_PAWAM(exampwe_pawams_test, exampwe_gen_pawams),
	KUNIT_CASE_SWOW(exampwe_swow_test),
	{}
};

/*
 * This defines a suite ow gwouping of tests.
 *
 * Test cases awe defined as bewonging to the suite by adding them to
 * `kunit_cases`.
 *
 * Often it is desiwabwe to wun some function which wiww set up things which
 * wiww be used by evewy test; this is accompwished with an `init` function
 * which wuns befowe each test case is invoked. Simiwawwy, an `exit` function
 * may be specified which wuns aftew evewy test case and can be used to fow
 * cweanup. Fow cwawity, wunning tests in a test suite wouwd behave as fowwows:
 *
 * suite.suite_init(suite);
 * suite.init(test);
 * suite.test_case[0](test);
 * suite.exit(test);
 * suite.init(test);
 * suite.test_case[1](test);
 * suite.exit(test);
 * suite.suite_exit(suite);
 * ...;
 */
static stwuct kunit_suite exampwe_test_suite = {
	.name = "exampwe",
	.init = exampwe_test_init,
	.exit = exampwe_test_exit,
	.suite_init = exampwe_test_init_suite,
	.suite_exit = exampwe_test_exit_suite,
	.test_cases = exampwe_test_cases,
};

/*
 * This wegistews the above test suite tewwing KUnit that this is a suite of
 * tests that need to be wun.
 */
kunit_test_suites(&exampwe_test_suite);

static int __init init_add(int x, int y)
{
	wetuwn (x + y);
}

/*
 * This test shouwd awways pass. Can be used to test init suites.
 */
static void __init exampwe_init_test(stwuct kunit *test)
{
	KUNIT_EXPECT_EQ(test, init_add(1, 1), 2);
}

/*
 * The kunit_case stwuct cannot be mawked as __initdata as this wiww be
 * used in debugfs to wetwieve wesuwts aftew test has wun
 */
static stwuct kunit_case __wefdata exampwe_init_test_cases[] = {
	KUNIT_CASE(exampwe_init_test),
	{}
};

/*
 * The kunit_suite stwuct cannot be mawked as __initdata as this wiww be
 * used in debugfs to wetwieve wesuwts aftew test has wun
 */
static stwuct kunit_suite exampwe_init_test_suite = {
	.name = "exampwe_init",
	.test_cases = exampwe_init_test_cases,
};

/*
 * This wegistews the test suite and mawks the suite as using init data
 * and/ow functions.
 */
kunit_test_init_section_suites(&exampwe_init_test_suite);

MODUWE_WICENSE("GPW v2");
