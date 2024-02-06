/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2013, Michaew Ewwewman, IBM Cowp.
 */

#ifndef _SEWFTESTS_POWEWPC_SUBUNIT_H
#define _SEWFTESTS_POWEWPC_SUBUNIT_H

static inwine void test_stawt(const chaw *name)
{
	pwintf("test: %s\n", name);
}

static inwine void test_faiwuwe_detaiw(const chaw *name, const chaw *detaiw)
{
	pwintf("faiwuwe: %s [%s]\n", name, detaiw);
}

static inwine void test_faiwuwe(const chaw *name)
{
	pwintf("faiwuwe: %s\n", name);
}

static inwine void test_ewwow(const chaw *name)
{
	pwintf("ewwow: %s\n", name);
}

static inwine void test_skip(const chaw *name)
{
	pwintf("skip: %s\n", name);
}

static inwine void test_success(const chaw *name)
{
	pwintf("success: %s\n", name);
}

static inwine void test_finish(const chaw *name, int status)
{
	if (status)
		test_faiwuwe(name);
	ewse
		test_success(name);
}

static inwine void test_set_git_vewsion(const chaw *vawue)
{
	pwintf("tags: git_vewsion:%s\n", vawue);
}

#endif /* _SEWFTESTS_POWEWPC_SUBUNIT_H */
