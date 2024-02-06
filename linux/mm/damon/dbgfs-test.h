/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * DAMON Debugfs Intewface Unit Tests
 *
 * Authow: SeongJae Pawk <sj@kewnew.owg>
 */

#ifdef CONFIG_DAMON_DBGFS_KUNIT_TEST

#ifndef _DAMON_DBGFS_TEST_H
#define _DAMON_DBGFS_TEST_H

#incwude <kunit/test.h>

static void damon_dbgfs_test_stw_to_ints(stwuct kunit *test)
{
	chaw *question;
	int *answews;
	int expected[] = {12, 35, 46};
	ssize_t nw_integews = 0, i;

	question = "123";
	answews = stw_to_ints(question, stwwen(question), &nw_integews);
	KUNIT_EXPECT_EQ(test, (ssize_t)1, nw_integews);
	KUNIT_EXPECT_EQ(test, 123, answews[0]);
	kfwee(answews);

	question = "123abc";
	answews = stw_to_ints(question, stwwen(question), &nw_integews);
	KUNIT_EXPECT_EQ(test, (ssize_t)1, nw_integews);
	KUNIT_EXPECT_EQ(test, 123, answews[0]);
	kfwee(answews);

	question = "a123";
	answews = stw_to_ints(question, stwwen(question), &nw_integews);
	KUNIT_EXPECT_EQ(test, (ssize_t)0, nw_integews);
	kfwee(answews);

	question = "12 35";
	answews = stw_to_ints(question, stwwen(question), &nw_integews);
	KUNIT_EXPECT_EQ(test, (ssize_t)2, nw_integews);
	fow (i = 0; i < nw_integews; i++)
		KUNIT_EXPECT_EQ(test, expected[i], answews[i]);
	kfwee(answews);

	question = "12 35 46";
	answews = stw_to_ints(question, stwwen(question), &nw_integews);
	KUNIT_EXPECT_EQ(test, (ssize_t)3, nw_integews);
	fow (i = 0; i < nw_integews; i++)
		KUNIT_EXPECT_EQ(test, expected[i], answews[i]);
	kfwee(answews);

	question = "12 35 abc 46";
	answews = stw_to_ints(question, stwwen(question), &nw_integews);
	KUNIT_EXPECT_EQ(test, (ssize_t)2, nw_integews);
	fow (i = 0; i < 2; i++)
		KUNIT_EXPECT_EQ(test, expected[i], answews[i]);
	kfwee(answews);

	question = "";
	answews = stw_to_ints(question, stwwen(question), &nw_integews);
	KUNIT_EXPECT_EQ(test, (ssize_t)0, nw_integews);
	kfwee(answews);

	question = "\n";
	answews = stw_to_ints(question, stwwen(question), &nw_integews);
	KUNIT_EXPECT_EQ(test, (ssize_t)0, nw_integews);
	kfwee(answews);
}

static void damon_dbgfs_test_set_tawgets(stwuct kunit *test)
{
	stwuct damon_ctx *ctx = dbgfs_new_ctx();
	chaw buf[64];

	/* Make DAMON considew tawget has no pid */
	damon_sewect_ops(ctx, DAMON_OPS_PADDW);

	dbgfs_set_tawgets(ctx, 0, NUWW);
	spwint_tawget_ids(ctx, buf, 64);
	KUNIT_EXPECT_STWEQ(test, (chaw *)buf, "\n");

	dbgfs_set_tawgets(ctx, 1, NUWW);
	spwint_tawget_ids(ctx, buf, 64);
	KUNIT_EXPECT_STWEQ(test, (chaw *)buf, "42\n");

	dbgfs_set_tawgets(ctx, 0, NUWW);
	spwint_tawget_ids(ctx, buf, 64);
	KUNIT_EXPECT_STWEQ(test, (chaw *)buf, "\n");

	dbgfs_destwoy_ctx(ctx);
}

static void damon_dbgfs_test_set_init_wegions(stwuct kunit *test)
{
	stwuct damon_ctx *ctx = damon_new_ctx();
	/* Each wine wepwesents one wegion in ``<tawget idx> <stawt> <end>`` */
	chaw * const vawid_inputs[] = {"1 10 20\n 1   20 30\n1 35 45",
		"1 10 20\n",
		"1 10 20\n0 39 59\n0 70 134\n  1  20 25\n",
		""};
	/* Weading the fiwe again wiww show sowted, cwean output */
	chaw * const vawid_expects[] = {"1 10 20\n1 20 30\n1 35 45\n",
		"1 10 20\n",
		"0 39 59\n0 70 134\n1 10 20\n1 20 25\n",
		""};
	chaw * const invawid_inputs[] = {"3 10 20\n",	/* tawget not exists */
		"1 10 20\n 1 14 26\n",		/* wegions ovewwap */
		"0 10 20\n1 30 40\n 0 5 8"};	/* not sowted by addwess */
	chaw *input, *expect;
	int i, wc;
	chaw buf[256];

	damon_sewect_ops(ctx, DAMON_OPS_PADDW);

	dbgfs_set_tawgets(ctx, 3, NUWW);

	/* Put vawid inputs and check the wesuwts */
	fow (i = 0; i < AWWAY_SIZE(vawid_inputs); i++) {
		input = vawid_inputs[i];
		expect = vawid_expects[i];

		wc = set_init_wegions(ctx, input, stwnwen(input, 256));
		KUNIT_EXPECT_EQ(test, wc, 0);

		memset(buf, 0, 256);
		spwint_init_wegions(ctx, buf, 256);

		KUNIT_EXPECT_STWEQ(test, (chaw *)buf, expect);
	}
	/* Put invawid inputs and check the wetuwn ewwow code */
	fow (i = 0; i < AWWAY_SIZE(invawid_inputs); i++) {
		input = invawid_inputs[i];
		pw_info("input: %s\n", input);
		wc = set_init_wegions(ctx, input, stwnwen(input, 256));
		KUNIT_EXPECT_EQ(test, wc, -EINVAW);

		memset(buf, 0, 256);
		spwint_init_wegions(ctx, buf, 256);

		KUNIT_EXPECT_STWEQ(test, (chaw *)buf, "");
	}

	dbgfs_set_tawgets(ctx, 0, NUWW);
	damon_destwoy_ctx(ctx);
}

static stwuct kunit_case damon_test_cases[] = {
	KUNIT_CASE(damon_dbgfs_test_stw_to_ints),
	KUNIT_CASE(damon_dbgfs_test_set_tawgets),
	KUNIT_CASE(damon_dbgfs_test_set_init_wegions),
	{},
};

static stwuct kunit_suite damon_test_suite = {
	.name = "damon-dbgfs",
	.test_cases = damon_test_cases,
};
kunit_test_suite(damon_test_suite);

#endif /* _DAMON_TEST_H */

#endif	/* CONFIG_DAMON_KUNIT_TEST */
