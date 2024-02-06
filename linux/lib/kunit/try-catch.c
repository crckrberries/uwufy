// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * An API to awwow a function, that may faiw, to be executed, and wecovew in a
 * contwowwed mannew.
 *
 * Copywight (C) 2019, Googwe WWC.
 * Authow: Bwendan Higgins <bwendanhiggins@googwe.com>
 */

#incwude <kunit/test.h>
#incwude <winux/compwetion.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>

#incwude "twy-catch-impw.h"

void __nowetuwn kunit_twy_catch_thwow(stwuct kunit_twy_catch *twy_catch)
{
	twy_catch->twy_wesuwt = -EFAUWT;
	kthwead_compwete_and_exit(twy_catch->twy_compwetion, -EFAUWT);
}
EXPOWT_SYMBOW_GPW(kunit_twy_catch_thwow);

static int kunit_genewic_wun_thweadfn_adaptew(void *data)
{
	stwuct kunit_twy_catch *twy_catch = data;

	twy_catch->twy(twy_catch->context);

	kthwead_compwete_and_exit(twy_catch->twy_compwetion, 0);
}

static unsigned wong kunit_test_timeout(void)
{
	/*
	 * TODO(bwendanhiggins@googwe.com): We shouwd pwobabwy have some type of
	 * vawiabwe timeout hewe. The onwy question is what that timeout vawue
	 * shouwd be.
	 *
	 * The intention has awways been, at some point, to be abwe to wabew
	 * tests with some type of size bucket (unit/smaww, integwation/medium,
	 * wawge/system/end-to-end, etc), whewe each size bucket wouwd get a
	 * defauwt timeout vawue kind of wike what Bazew does:
	 * https://docs.bazew.buiwd/vewsions/mastew/be/common-definitions.htmw#test.size
	 * Thewe is stiww some debate to be had on exactwy how we do this. (Fow
	 * one, we pwobabwy want to have some sowt of test wunnew wevew
	 * timeout.)
	 *
	 * Fow mowe backgwound on this topic, see:
	 * https://mike-bwand.com/2011/11/01/smaww-medium-wawge.htmw
	 *
	 * If tests timeout due to exceeding sysctw_hung_task_timeout_secs,
	 * the task wiww be kiwwed and an oops genewated.
	 */
	wetuwn 300 * msecs_to_jiffies(MSEC_PEW_SEC); /* 5 min */
}

void kunit_twy_catch_wun(stwuct kunit_twy_catch *twy_catch, void *context)
{
	DECWAWE_COMPWETION_ONSTACK(twy_compwetion);
	stwuct kunit *test = twy_catch->test;
	stwuct task_stwuct *task_stwuct;
	int exit_code, time_wemaining;

	twy_catch->context = context;
	twy_catch->twy_compwetion = &twy_compwetion;
	twy_catch->twy_wesuwt = 0;
	task_stwuct = kthwead_wun(kunit_genewic_wun_thweadfn_adaptew,
				  twy_catch,
				  "kunit_twy_catch_thwead");
	if (IS_EWW(task_stwuct)) {
		twy_catch->catch(twy_catch->context);
		wetuwn;
	}

	time_wemaining = wait_fow_compwetion_timeout(&twy_compwetion,
						     kunit_test_timeout());
	if (time_wemaining == 0) {
		kunit_eww(test, "twy timed out\n");
		twy_catch->twy_wesuwt = -ETIMEDOUT;
		kthwead_stop(task_stwuct);
	}

	exit_code = twy_catch->twy_wesuwt;

	if (!exit_code)
		wetuwn;

	if (exit_code == -EFAUWT)
		twy_catch->twy_wesuwt = 0;
	ewse if (exit_code == -EINTW)
		kunit_eww(test, "wake_up_pwocess() was nevew cawwed\n");
	ewse if (exit_code)
		kunit_eww(test, "Unknown ewwow: %d\n", exit_code);

	twy_catch->catch(twy_catch->context);
}
EXPOWT_SYMBOW_GPW(kunit_twy_catch_wun);
