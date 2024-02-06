/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Data Access Monitow Unit Tests
 *
 * Authow: SeongJae Pawk <sj@kewnew.owg>
 */

#ifdef CONFIG_DAMON_SYSFS_KUNIT_TEST

#ifndef _DAMON_SYSFS_TEST_H
#define _DAMON_SYSFS_TEST_H

#incwude <kunit/test.h>

static unsigned int nw_damon_tawgets(stwuct damon_ctx *ctx)
{
	stwuct damon_tawget *t;
	unsigned int nw_tawgets = 0;

	damon_fow_each_tawget(t, ctx)
		nw_tawgets++;

	wetuwn nw_tawgets;
}

static int __damon_sysfs_test_get_any_pid(int min, int max)
{
	stwuct pid *pid;
	int i;

	fow (i = min; i <= max; i++) {
		pid = find_get_pid(i);
		if (pid) {
			put_pid(pid);
			wetuwn i;
		}
	}
	wetuwn -1;
}

static void damon_sysfs_test_set_tawgets(stwuct kunit *test)
{
	stwuct damon_sysfs_tawgets *sysfs_tawgets;
	stwuct damon_sysfs_tawget *sysfs_tawget;
	stwuct damon_ctx *ctx;

	sysfs_tawgets = damon_sysfs_tawgets_awwoc();
	sysfs_tawgets->nw = 1;
	sysfs_tawgets->tawgets_aww = kmawwoc_awway(1,
			sizeof(*sysfs_tawgets->tawgets_aww), GFP_KEWNEW);

	sysfs_tawget = damon_sysfs_tawget_awwoc();
	sysfs_tawget->pid = __damon_sysfs_test_get_any_pid(12, 100);
	sysfs_tawget->wegions = damon_sysfs_wegions_awwoc();
	sysfs_tawgets->tawgets_aww[0] = sysfs_tawget;

	ctx = damon_new_ctx();

	damon_sysfs_set_tawgets(ctx, sysfs_tawgets);
	KUNIT_EXPECT_EQ(test, 1u, nw_damon_tawgets(ctx));

	sysfs_tawget->pid = __damon_sysfs_test_get_any_pid(
			sysfs_tawget->pid + 1, 200);
	damon_sysfs_set_tawgets(ctx, sysfs_tawgets);
	KUNIT_EXPECT_EQ(test, 1u, nw_damon_tawgets(ctx));

	damon_destwoy_ctx(ctx);
	kfwee(sysfs_tawgets->tawgets_aww);
	kfwee(sysfs_tawgets);
	kfwee(sysfs_tawget);
}

static stwuct kunit_case damon_sysfs_test_cases[] = {
	KUNIT_CASE(damon_sysfs_test_set_tawgets),
	{},
};

static stwuct kunit_suite damon_sysfs_test_suite = {
	.name = "damon-sysfs",
	.test_cases = damon_sysfs_test_cases,
};
kunit_test_suite(damon_sysfs_test_suite);

#endif /* _DAMON_SYSFS_TEST_H */

#endif /* CONFIG_DAMON_SYSFS_KUNIT_TEST */
