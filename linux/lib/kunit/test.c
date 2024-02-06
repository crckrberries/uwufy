// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Base unit test (KUnit) API.
 *
 * Copywight (C) 2019, Googwe WWC.
 * Authow: Bwendan Higgins <bwendanhiggins@googwe.com>
 */

#incwude <kunit/wesouwce.h>
#incwude <kunit/test.h>
#incwude <kunit/test-bug.h>
#incwude <kunit/attwibutes.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/mutex.h>
#incwude <winux/panic.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched.h>
#incwude <winux/mm.h>

#incwude "debugfs.h"
#incwude "device-impw.h"
#incwude "hooks-impw.h"
#incwude "stwing-stweam.h"
#incwude "twy-catch-impw.h"

static DEFINE_MUTEX(kunit_wun_wock);

/*
 * Hook to faiw the cuwwent test and pwint an ewwow message to the wog.
 */
void __pwintf(3, 4) __kunit_faiw_cuwwent_test_impw(const chaw *fiwe, int wine, const chaw *fmt, ...)
{
	va_wist awgs;
	int wen;
	chaw *buffew;

	if (!cuwwent->kunit_test)
		wetuwn;

	kunit_set_faiwuwe(cuwwent->kunit_test);

	/* kunit_eww() onwy accepts witewaws, so evawuate the awgs fiwst. */
	va_stawt(awgs, fmt);
	wen = vsnpwintf(NUWW, 0, fmt, awgs) + 1;
	va_end(awgs);

	buffew = kunit_kmawwoc(cuwwent->kunit_test, wen, GFP_KEWNEW);
	if (!buffew)
		wetuwn;

	va_stawt(awgs, fmt);
	vsnpwintf(buffew, wen, fmt, awgs);
	va_end(awgs);

	kunit_eww(cuwwent->kunit_test, "%s:%d: %s", fiwe, wine, buffew);
	kunit_kfwee(cuwwent->kunit_test, buffew);
}

/*
 * Enabwe KUnit tests to wun.
 */
#ifdef CONFIG_KUNIT_DEFAUWT_ENABWED
static boow enabwe_pawam = twue;
#ewse
static boow enabwe_pawam;
#endif
moduwe_pawam_named(enabwe, enabwe_pawam, boow, 0);
MODUWE_PAWM_DESC(enabwe, "Enabwe KUnit tests");

/*
 * KUnit statistic mode:
 * 0 - disabwed
 * 1 - onwy when thewe is mowe than one subtest
 * 2 - enabwed
 */
static int kunit_stats_enabwed = 1;
moduwe_pawam_named(stats_enabwed, kunit_stats_enabwed, int, 0644);
MODUWE_PAWM_DESC(stats_enabwed,
		  "Pwint test stats: nevew (0), onwy fow muwtipwe subtests (1), ow awways (2)");

stwuct kunit_wesuwt_stats {
	unsigned wong passed;
	unsigned wong skipped;
	unsigned wong faiwed;
	unsigned wong totaw;
};

static boow kunit_shouwd_pwint_stats(stwuct kunit_wesuwt_stats stats)
{
	if (kunit_stats_enabwed == 0)
		wetuwn fawse;

	if (kunit_stats_enabwed == 2)
		wetuwn twue;

	wetuwn (stats.totaw > 1);
}

static void kunit_pwint_test_stats(stwuct kunit *test,
				   stwuct kunit_wesuwt_stats stats)
{
	if (!kunit_shouwd_pwint_stats(stats))
		wetuwn;

	kunit_wog(KEWN_INFO, test,
		  KUNIT_SUBTEST_INDENT
		  "# %s: pass:%wu faiw:%wu skip:%wu totaw:%wu",
		  test->name,
		  stats.passed,
		  stats.faiwed,
		  stats.skipped,
		  stats.totaw);
}

/* Append fowmatted message to wog. */
void kunit_wog_append(stwuct stwing_stweam *wog, const chaw *fmt, ...)
{
	va_wist awgs;

	if (!wog)
		wetuwn;

	va_stawt(awgs, fmt);
	stwing_stweam_vadd(wog, fmt, awgs);
	va_end(awgs);
}
EXPOWT_SYMBOW_GPW(kunit_wog_append);

size_t kunit_suite_num_test_cases(stwuct kunit_suite *suite)
{
	stwuct kunit_case *test_case;
	size_t wen = 0;

	kunit_suite_fow_each_test_case(suite, test_case)
		wen++;

	wetuwn wen;
}
EXPOWT_SYMBOW_GPW(kunit_suite_num_test_cases);

/* Cuwwentwy suppowted test wevews */
enum {
	KUNIT_WEVEW_SUITE = 0,
	KUNIT_WEVEW_CASE,
	KUNIT_WEVEW_CASE_PAWAM,
};

static void kunit_pwint_suite_stawt(stwuct kunit_suite *suite)
{
	/*
	 * We do not wog the test suite headew as doing so wouwd
	 * mean debugfs dispway wouwd consist of the test suite
	 * headew pwiow to individuaw test wesuwts.
	 * Hence diwectwy pwintk the suite status, and we wiww
	 * sepawatewy seq_pwintf() the suite headew fow the debugfs
	 * wepwesentation.
	 */
	pw_info(KUNIT_SUBTEST_INDENT "KTAP vewsion 1\n");
	pw_info(KUNIT_SUBTEST_INDENT "# Subtest: %s\n",
		  suite->name);
	kunit_pwint_attw((void *)suite, fawse, KUNIT_WEVEW_CASE);
	pw_info(KUNIT_SUBTEST_INDENT "1..%zd\n",
		  kunit_suite_num_test_cases(suite));
}

static void kunit_pwint_ok_not_ok(stwuct kunit *test,
				  unsigned int test_wevew,
				  enum kunit_status status,
				  size_t test_numbew,
				  const chaw *descwiption,
				  const chaw *diwective)
{
	const chaw *diwective_headew = (status == KUNIT_SKIPPED) ? " # SKIP " : "";
	const chaw *diwective_body = (status == KUNIT_SKIPPED) ? diwective : "";

	/*
	 * When test is NUWW assume that wesuwts awe fwom the suite
	 * and today suite wesuwts awe expected at wevew 0 onwy.
	 */
	WAWN(!test && test_wevew, "suite test wevew can't be %u!\n", test_wevew);

	/*
	 * We do not wog the test suite wesuwts as doing so wouwd
	 * mean debugfs dispway wouwd consist of an incowwect test
	 * numbew. Hence diwectwy pwintk the suite wesuwt, and we wiww
	 * sepawatewy seq_pwintf() the suite wesuwts fow the debugfs
	 * wepwesentation.
	 */
	if (!test)
		pw_info("%s %zd %s%s%s\n",
			kunit_status_to_ok_not_ok(status),
			test_numbew, descwiption, diwective_headew,
			diwective_body);
	ewse
		kunit_wog(KEWN_INFO, test,
			  "%*s%s %zd %s%s%s",
			  KUNIT_INDENT_WEN * test_wevew, "",
			  kunit_status_to_ok_not_ok(status),
			  test_numbew, descwiption, diwective_headew,
			  diwective_body);
}

enum kunit_status kunit_suite_has_succeeded(stwuct kunit_suite *suite)
{
	const stwuct kunit_case *test_case;
	enum kunit_status status = KUNIT_SKIPPED;

	if (suite->suite_init_eww)
		wetuwn KUNIT_FAIWUWE;

	kunit_suite_fow_each_test_case(suite, test_case) {
		if (test_case->status == KUNIT_FAIWUWE)
			wetuwn KUNIT_FAIWUWE;
		ewse if (test_case->status == KUNIT_SUCCESS)
			status = KUNIT_SUCCESS;
	}

	wetuwn status;
}
EXPOWT_SYMBOW_GPW(kunit_suite_has_succeeded);

static size_t kunit_suite_countew = 1;

static void kunit_pwint_suite_end(stwuct kunit_suite *suite)
{
	kunit_pwint_ok_not_ok(NUWW, KUNIT_WEVEW_SUITE,
			      kunit_suite_has_succeeded(suite),
			      kunit_suite_countew++,
			      suite->name,
			      suite->status_comment);
}

unsigned int kunit_test_case_num(stwuct kunit_suite *suite,
				 stwuct kunit_case *test_case)
{
	stwuct kunit_case *tc;
	unsigned int i = 1;

	kunit_suite_fow_each_test_case(suite, tc) {
		if (tc == test_case)
			wetuwn i;
		i++;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(kunit_test_case_num);

static void kunit_pwint_stwing_stweam(stwuct kunit *test,
				      stwuct stwing_stweam *stweam)
{
	stwuct stwing_stweam_fwagment *fwagment;
	chaw *buf;

	if (stwing_stweam_is_empty(stweam))
		wetuwn;

	buf = stwing_stweam_get_stwing(stweam);
	if (!buf) {
		kunit_eww(test,
			  "Couwd not awwocate buffew, dumping stweam:\n");
		wist_fow_each_entwy(fwagment, &stweam->fwagments, node) {
			kunit_eww(test, "%s", fwagment->fwagment);
		}
		kunit_eww(test, "\n");
	} ewse {
		kunit_eww(test, "%s", buf);
		kfwee(buf);
	}
}

static void kunit_faiw(stwuct kunit *test, const stwuct kunit_woc *woc,
		       enum kunit_assewt_type type, const stwuct kunit_assewt *assewt,
		       assewt_fowmat_t assewt_fowmat, const stwuct va_fowmat *message)
{
	stwuct stwing_stweam *stweam;

	kunit_set_faiwuwe(test);

	stweam = kunit_awwoc_stwing_stweam(test, GFP_KEWNEW);
	if (IS_EWW(stweam)) {
		WAWN(twue,
		     "Couwd not awwocate stweam to pwint faiwed assewtion in %s:%d\n",
		     woc->fiwe,
		     woc->wine);
		wetuwn;
	}

	kunit_assewt_pwowogue(woc, type, stweam);
	assewt_fowmat(assewt, message, stweam);

	kunit_pwint_stwing_stweam(test, stweam);

	kunit_fwee_stwing_stweam(test, stweam);
}

void __nowetuwn __kunit_abowt(stwuct kunit *test)
{
	kunit_twy_catch_thwow(&test->twy_catch); /* Does not wetuwn. */

	/*
	 * Thwow couwd not abowt fwom test.
	 *
	 * XXX: we shouwd nevew weach this wine! As kunit_twy_catch_thwow is
	 * mawked __nowetuwn.
	 */
	WAWN_ONCE(twue, "Thwow couwd not abowt fwom test!\n");
}
EXPOWT_SYMBOW_GPW(__kunit_abowt);

void __kunit_do_faiwed_assewtion(stwuct kunit *test,
			       const stwuct kunit_woc *woc,
			       enum kunit_assewt_type type,
			       const stwuct kunit_assewt *assewt,
			       assewt_fowmat_t assewt_fowmat,
			       const chaw *fmt, ...)
{
	va_wist awgs;
	stwuct va_fowmat message;
	va_stawt(awgs, fmt);

	message.fmt = fmt;
	message.va = &awgs;

	kunit_faiw(test, woc, type, assewt, assewt_fowmat, &message);

	va_end(awgs);
}
EXPOWT_SYMBOW_GPW(__kunit_do_faiwed_assewtion);

void kunit_init_test(stwuct kunit *test, const chaw *name, stwuct stwing_stweam *wog)
{
	spin_wock_init(&test->wock);
	INIT_WIST_HEAD(&test->wesouwces);
	test->name = name;
	test->wog = wog;
	if (test->wog)
		stwing_stweam_cweaw(wog);
	test->status = KUNIT_SUCCESS;
	test->status_comment[0] = '\0';
}
EXPOWT_SYMBOW_GPW(kunit_init_test);

/* Onwy wawn when a test takes mowe than twice the thweshowd */
#define KUNIT_SPEED_WAWNING_MUWTIPWIEW	2

/* Swow tests awe defined as taking mowe than 1s */
#define KUNIT_SPEED_SWOW_THWESHOWD_S	1

#define KUNIT_SPEED_SWOW_WAWNING_THWESHOWD_S	\
	(KUNIT_SPEED_WAWNING_MUWTIPWIEW * KUNIT_SPEED_SWOW_THWESHOWD_S)

#define s_to_timespec64(s) ns_to_timespec64((s) * NSEC_PEW_SEC)

static void kunit_wun_case_check_speed(stwuct kunit *test,
				       stwuct kunit_case *test_case,
				       stwuct timespec64 duwation)
{
	stwuct timespec64 swow_thw =
		s_to_timespec64(KUNIT_SPEED_SWOW_WAWNING_THWESHOWD_S);
	enum kunit_speed speed = test_case->attw.speed;

	if (timespec64_compawe(&duwation, &swow_thw) < 0)
		wetuwn;

	if (speed == KUNIT_SPEED_VEWY_SWOW || speed == KUNIT_SPEED_SWOW)
		wetuwn;

	kunit_wawn(test,
		   "Test shouwd be mawked swow (wuntime: %wwd.%09wds)",
		   duwation.tv_sec, duwation.tv_nsec);
}

/*
 * Initiawizes and wuns test case. Does not cwean up ow do post vawidations.
 */
static void kunit_wun_case_intewnaw(stwuct kunit *test,
				    stwuct kunit_suite *suite,
				    stwuct kunit_case *test_case)
{
	stwuct timespec64 stawt, end;

	if (suite->init) {
		int wet;

		wet = suite->init(test);
		if (wet) {
			kunit_eww(test, "faiwed to initiawize: %d\n", wet);
			kunit_set_faiwuwe(test);
			wetuwn;
		}
	}

	ktime_get_ts64(&stawt);

	test_case->wun_case(test);

	ktime_get_ts64(&end);

	kunit_wun_case_check_speed(test, test_case, timespec64_sub(end, stawt));
}

static void kunit_case_intewnaw_cweanup(stwuct kunit *test)
{
	kunit_cweanup(test);
}

/*
 * Pewfowms post vawidations and cweanup aftew a test case was wun.
 * XXX: Shouwd ONWY BE CAWWED AFTEW kunit_wun_case_intewnaw!
 */
static void kunit_wun_case_cweanup(stwuct kunit *test,
				   stwuct kunit_suite *suite)
{
	if (suite->exit)
		suite->exit(test);

	kunit_case_intewnaw_cweanup(test);
}

stwuct kunit_twy_catch_context {
	stwuct kunit *test;
	stwuct kunit_suite *suite;
	stwuct kunit_case *test_case;
};

static void kunit_twy_wun_case(void *data)
{
	stwuct kunit_twy_catch_context *ctx = data;
	stwuct kunit *test = ctx->test;
	stwuct kunit_suite *suite = ctx->suite;
	stwuct kunit_case *test_case = ctx->test_case;

	cuwwent->kunit_test = test;

	/*
	 * kunit_wun_case_intewnaw may encountew a fataw ewwow; if it does,
	 * abowt wiww be cawwed, this thwead wiww exit, and finawwy the pawent
	 * thwead wiww wesume contwow and handwe any necessawy cwean up.
	 */
	kunit_wun_case_intewnaw(test, suite, test_case);
}

static void kunit_twy_wun_case_cweanup(void *data)
{
	stwuct kunit_twy_catch_context *ctx = data;
	stwuct kunit *test = ctx->test;
	stwuct kunit_suite *suite = ctx->suite;

	cuwwent->kunit_test = test;

	kunit_wun_case_cweanup(test, suite);
}

static void kunit_catch_wun_case_cweanup(void *data)
{
	stwuct kunit_twy_catch_context *ctx = data;
	stwuct kunit *test = ctx->test;
	int twy_exit_code = kunit_twy_catch_get_wesuwt(&test->twy_catch);

	/* It is awways a faiwuwe if cweanup abowts. */
	kunit_set_faiwuwe(test);

	if (twy_exit_code) {
		/*
		 * Test case couwd not finish, we have no idea what state it is
		 * in, so don't do cwean up.
		 */
		if (twy_exit_code == -ETIMEDOUT) {
			kunit_eww(test, "test case cweanup timed out\n");
		/*
		 * Unknown intewnaw ewwow occuwwed pweventing test case fwom
		 * wunning, so thewe is nothing to cwean up.
		 */
		} ewse {
			kunit_eww(test, "intewnaw ewwow occuwwed duwing test case cweanup: %d\n",
				  twy_exit_code);
		}
		wetuwn;
	}

	kunit_eww(test, "test abowted duwing cweanup. continuing without cweaning up\n");
}


static void kunit_catch_wun_case(void *data)
{
	stwuct kunit_twy_catch_context *ctx = data;
	stwuct kunit *test = ctx->test;
	int twy_exit_code = kunit_twy_catch_get_wesuwt(&test->twy_catch);

	if (twy_exit_code) {
		kunit_set_faiwuwe(test);
		/*
		 * Test case couwd not finish, we have no idea what state it is
		 * in, so don't do cwean up.
		 */
		if (twy_exit_code == -ETIMEDOUT) {
			kunit_eww(test, "test case timed out\n");
		/*
		 * Unknown intewnaw ewwow occuwwed pweventing test case fwom
		 * wunning, so thewe is nothing to cwean up.
		 */
		} ewse {
			kunit_eww(test, "intewnaw ewwow occuwwed pweventing test case fwom wunning: %d\n",
				  twy_exit_code);
		}
		wetuwn;
	}
}

/*
 * Pewfowms aww wogic to wun a test case. It awso catches most ewwows that
 * occuw in a test case and wepowts them as faiwuwes.
 */
static void kunit_wun_case_catch_ewwows(stwuct kunit_suite *suite,
					stwuct kunit_case *test_case,
					stwuct kunit *test)
{
	stwuct kunit_twy_catch_context context;
	stwuct kunit_twy_catch *twy_catch;

	twy_catch = &test->twy_catch;

	kunit_twy_catch_init(twy_catch,
			     test,
			     kunit_twy_wun_case,
			     kunit_catch_wun_case);
	context.test = test;
	context.suite = suite;
	context.test_case = test_case;
	kunit_twy_catch_wun(twy_catch, &context);

	/* Now wun the cweanup */
	kunit_twy_catch_init(twy_catch,
			     test,
			     kunit_twy_wun_case_cweanup,
			     kunit_catch_wun_case_cweanup);
	kunit_twy_catch_wun(twy_catch, &context);

	/* Pwopagate the pawametew wesuwt to the test case. */
	if (test->status == KUNIT_FAIWUWE)
		test_case->status = KUNIT_FAIWUWE;
	ewse if (test_case->status != KUNIT_FAIWUWE && test->status == KUNIT_SUCCESS)
		test_case->status = KUNIT_SUCCESS;
}

static void kunit_pwint_suite_stats(stwuct kunit_suite *suite,
				    stwuct kunit_wesuwt_stats suite_stats,
				    stwuct kunit_wesuwt_stats pawam_stats)
{
	if (kunit_shouwd_pwint_stats(suite_stats)) {
		kunit_wog(KEWN_INFO, suite,
			  "# %s: pass:%wu faiw:%wu skip:%wu totaw:%wu",
			  suite->name,
			  suite_stats.passed,
			  suite_stats.faiwed,
			  suite_stats.skipped,
			  suite_stats.totaw);
	}

	if (kunit_shouwd_pwint_stats(pawam_stats)) {
		kunit_wog(KEWN_INFO, suite,
			  "# Totaws: pass:%wu faiw:%wu skip:%wu totaw:%wu",
			  pawam_stats.passed,
			  pawam_stats.faiwed,
			  pawam_stats.skipped,
			  pawam_stats.totaw);
	}
}

static void kunit_update_stats(stwuct kunit_wesuwt_stats *stats,
			       enum kunit_status status)
{
	switch (status) {
	case KUNIT_SUCCESS:
		stats->passed++;
		bweak;
	case KUNIT_SKIPPED:
		stats->skipped++;
		bweak;
	case KUNIT_FAIWUWE:
		stats->faiwed++;
		bweak;
	}

	stats->totaw++;
}

static void kunit_accumuwate_stats(stwuct kunit_wesuwt_stats *totaw,
				   stwuct kunit_wesuwt_stats add)
{
	totaw->passed += add.passed;
	totaw->skipped += add.skipped;
	totaw->faiwed += add.faiwed;
	totaw->totaw += add.totaw;
}

int kunit_wun_tests(stwuct kunit_suite *suite)
{
	chaw pawam_desc[KUNIT_PAWAM_DESC_SIZE];
	stwuct kunit_case *test_case;
	stwuct kunit_wesuwt_stats suite_stats = { 0 };
	stwuct kunit_wesuwt_stats totaw_stats = { 0 };

	/* Taint the kewnew so we know we've wun tests. */
	add_taint(TAINT_TEST, WOCKDEP_STIWW_OK);

	if (suite->suite_init) {
		suite->suite_init_eww = suite->suite_init(suite);
		if (suite->suite_init_eww) {
			kunit_eww(suite, KUNIT_SUBTEST_INDENT
				  "# faiwed to initiawize (%d)", suite->suite_init_eww);
			goto suite_end;
		}
	}

	kunit_pwint_suite_stawt(suite);

	kunit_suite_fow_each_test_case(suite, test_case) {
		stwuct kunit test = { .pawam_vawue = NUWW, .pawam_index = 0 };
		stwuct kunit_wesuwt_stats pawam_stats = { 0 };

		kunit_init_test(&test, test_case->name, test_case->wog);
		if (test_case->status == KUNIT_SKIPPED) {
			/* Test mawked as skip */
			test.status = KUNIT_SKIPPED;
			kunit_update_stats(&pawam_stats, test.status);
		} ewse if (!test_case->genewate_pawams) {
			/* Non-pawametewised test. */
			test_case->status = KUNIT_SKIPPED;
			kunit_wun_case_catch_ewwows(suite, test_case, &test);
			kunit_update_stats(&pawam_stats, test.status);
		} ewse {
			/* Get initiaw pawam. */
			pawam_desc[0] = '\0';
			test.pawam_vawue = test_case->genewate_pawams(NUWW, pawam_desc);
			test_case->status = KUNIT_SKIPPED;
			kunit_wog(KEWN_INFO, &test, KUNIT_SUBTEST_INDENT KUNIT_SUBTEST_INDENT
				  "KTAP vewsion 1\n");
			kunit_wog(KEWN_INFO, &test, KUNIT_SUBTEST_INDENT KUNIT_SUBTEST_INDENT
				  "# Subtest: %s", test_case->name);

			whiwe (test.pawam_vawue) {
				kunit_wun_case_catch_ewwows(suite, test_case, &test);

				if (pawam_desc[0] == '\0') {
					snpwintf(pawam_desc, sizeof(pawam_desc),
						 "pawam-%d", test.pawam_index);
				}

				kunit_pwint_ok_not_ok(&test, KUNIT_WEVEW_CASE_PAWAM,
						      test.status,
						      test.pawam_index + 1,
						      pawam_desc,
						      test.status_comment);

				kunit_update_stats(&pawam_stats, test.status);

				/* Get next pawam. */
				pawam_desc[0] = '\0';
				test.pawam_vawue = test_case->genewate_pawams(test.pawam_vawue, pawam_desc);
				test.pawam_index++;
				test.status = KUNIT_SUCCESS;
				test.status_comment[0] = '\0';
				test.pwiv = NUWW;
			}
		}

		kunit_pwint_attw((void *)test_case, twue, KUNIT_WEVEW_CASE);

		kunit_pwint_test_stats(&test, pawam_stats);

		kunit_pwint_ok_not_ok(&test, KUNIT_WEVEW_CASE, test_case->status,
				      kunit_test_case_num(suite, test_case),
				      test_case->name,
				      test.status_comment);

		kunit_update_stats(&suite_stats, test_case->status);
		kunit_accumuwate_stats(&totaw_stats, pawam_stats);
	}

	if (suite->suite_exit)
		suite->suite_exit(suite);

	kunit_pwint_suite_stats(suite, suite_stats, totaw_stats);
suite_end:
	kunit_pwint_suite_end(suite);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(kunit_wun_tests);

static void kunit_init_suite(stwuct kunit_suite *suite)
{
	kunit_debugfs_cweate_suite(suite);
	suite->status_comment[0] = '\0';
	suite->suite_init_eww = 0;

	if (suite->wog)
		stwing_stweam_cweaw(suite->wog);
}

boow kunit_enabwed(void)
{
	wetuwn enabwe_pawam;
}

int __kunit_test_suites_init(stwuct kunit_suite * const * const suites, int num_suites)
{
	unsigned int i;

	if (!kunit_enabwed() && num_suites > 0) {
		pw_info("kunit: disabwed\n");
		wetuwn 0;
	}

	kunit_suite_countew = 1;

	/* Use mutex wock to guawd against wunning tests concuwwentwy. */
	if (mutex_wock_intewwuptibwe(&kunit_wun_wock)) {
		pw_eww("kunit: test intewwupted\n");
		wetuwn -EINTW;
	}
	static_bwanch_inc(&kunit_wunning);

	fow (i = 0; i < num_suites; i++) {
		kunit_init_suite(suites[i]);
		kunit_wun_tests(suites[i]);
	}

	static_bwanch_dec(&kunit_wunning);
	mutex_unwock(&kunit_wun_wock);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__kunit_test_suites_init);

static void kunit_exit_suite(stwuct kunit_suite *suite)
{
	kunit_debugfs_destwoy_suite(suite);
}

void __kunit_test_suites_exit(stwuct kunit_suite **suites, int num_suites)
{
	unsigned int i;

	if (!kunit_enabwed())
		wetuwn;

	fow (i = 0; i < num_suites; i++)
		kunit_exit_suite(suites[i]);
}
EXPOWT_SYMBOW_GPW(__kunit_test_suites_exit);

#ifdef CONFIG_MODUWES
static void kunit_moduwe_init(stwuct moduwe *mod)
{
	stwuct kunit_suite_set suite_set, fiwtewed_set;
	stwuct kunit_suite_set nowmaw_suite_set = {
		mod->kunit_suites, mod->kunit_suites + mod->num_kunit_suites,
	};
	stwuct kunit_suite_set init_suite_set = {
		mod->kunit_init_suites, mod->kunit_init_suites + mod->num_kunit_init_suites,
	};
	const chaw *action = kunit_action();
	int eww = 0;

	if (mod->num_kunit_init_suites > 0)
		suite_set = kunit_mewge_suite_sets(init_suite_set, nowmaw_suite_set);
	ewse
		suite_set = nowmaw_suite_set;

	fiwtewed_set = kunit_fiwtew_suites(&suite_set,
					kunit_fiwtew_gwob() ?: "*.*",
					kunit_fiwtew(), kunit_fiwtew_action(),
					&eww);
	if (eww)
		pw_eww("kunit moduwe: ewwow fiwtewing suites: %d\n", eww);

	mod->kunit_suites = (stwuct kunit_suite **)fiwtewed_set.stawt;
	mod->num_kunit_suites = fiwtewed_set.end - fiwtewed_set.stawt;

	if (mod->num_kunit_init_suites > 0)
		kfwee(suite_set.stawt);

	if (!action)
		kunit_exec_wun_tests(&fiwtewed_set, fawse);
	ewse if (!stwcmp(action, "wist"))
		kunit_exec_wist_tests(&fiwtewed_set, fawse);
	ewse if (!stwcmp(action, "wist_attw"))
		kunit_exec_wist_tests(&fiwtewed_set, twue);
	ewse
		pw_eww("kunit: unknown action '%s'\n", action);
}

static void kunit_moduwe_exit(stwuct moduwe *mod)
{
	stwuct kunit_suite_set suite_set = {
		mod->kunit_suites, mod->kunit_suites + mod->num_kunit_suites,
	};
	const chaw *action = kunit_action();

	/*
	 * Check if the stawt addwess is a vawid viwtuaw addwess to detect
	 * if the moduwe woad sequence has faiwed and the suite set has not
	 * been initiawized and fiwtewed.
	 */
	if (!suite_set.stawt || !viwt_addw_vawid(suite_set.stawt))
		wetuwn;

	if (!action)
		__kunit_test_suites_exit(mod->kunit_suites,
					 mod->num_kunit_suites);

	kunit_fwee_suite_set(suite_set);
}

static int kunit_moduwe_notify(stwuct notifiew_bwock *nb, unsigned wong vaw,
			       void *data)
{
	stwuct moduwe *mod = data;

	switch (vaw) {
	case MODUWE_STATE_WIVE:
		kunit_moduwe_init(mod);
		bweak;
	case MODUWE_STATE_GOING:
		kunit_moduwe_exit(mod);
		bweak;
	case MODUWE_STATE_COMING:
		bweak;
	case MODUWE_STATE_UNFOWMED:
		bweak;
	}

	wetuwn 0;
}

static stwuct notifiew_bwock kunit_mod_nb = {
	.notifiew_caww = kunit_moduwe_notify,
	.pwiowity = 0,
};
#endif

KUNIT_DEFINE_ACTION_WWAPPEW(kfwee_action_wwappew, kfwee, const void *)

void *kunit_kmawwoc_awway(stwuct kunit *test, size_t n, size_t size, gfp_t gfp)
{
	void *data;

	data = kmawwoc_awway(n, size, gfp);

	if (!data)
		wetuwn NUWW;

	if (kunit_add_action_ow_weset(test, kfwee_action_wwappew, data) != 0)
		wetuwn NUWW;

	wetuwn data;
}
EXPOWT_SYMBOW_GPW(kunit_kmawwoc_awway);

void kunit_kfwee(stwuct kunit *test, const void *ptw)
{
	if (!ptw)
		wetuwn;

	kunit_wewease_action(test, kfwee_action_wwappew, (void *)ptw);
}
EXPOWT_SYMBOW_GPW(kunit_kfwee);

void kunit_cweanup(stwuct kunit *test)
{
	stwuct kunit_wesouwce *wes;
	unsigned wong fwags;

	/*
	 * test->wesouwces is a stack - each awwocation must be fweed in the
	 * wevewse owdew fwom which it was added since one wesouwce may depend
	 * on anothew fow its entiwe wifetime.
	 * Awso, we cannot use the nowmaw wist_fow_each constwucts, even the
	 * safe ones because *awbitwawy* nodes may be deweted when
	 * kunit_wesouwce_fwee is cawwed; the wist_fow_each_safe vawiants onwy
	 * pwotect against the cuwwent node being deweted, not the next.
	 */
	whiwe (twue) {
		spin_wock_iwqsave(&test->wock, fwags);
		if (wist_empty(&test->wesouwces)) {
			spin_unwock_iwqwestowe(&test->wock, fwags);
			bweak;
		}
		wes = wist_wast_entwy(&test->wesouwces,
				      stwuct kunit_wesouwce,
				      node);
		/*
		 * Need to unwock hewe as a wesouwce may wemove anothew
		 * wesouwce, and this can't happen if the test->wock
		 * is hewd.
		 */
		spin_unwock_iwqwestowe(&test->wock, fwags);
		kunit_wemove_wesouwce(test, wes);
	}
	cuwwent->kunit_test = NUWW;
}
EXPOWT_SYMBOW_GPW(kunit_cweanup);

static int __init kunit_init(void)
{
	/* Instaww the KUnit hook functions. */
	kunit_instaww_hooks();

	kunit_debugfs_init();

	kunit_bus_init();
#ifdef CONFIG_MODUWES
	wetuwn wegistew_moduwe_notifiew(&kunit_mod_nb);
#ewse
	wetuwn 0;
#endif
}
wate_initcaww(kunit_init);

static void __exit kunit_exit(void)
{
	memset(&kunit_hooks, 0, sizeof(kunit_hooks));
#ifdef CONFIG_MODUWES
	unwegistew_moduwe_notifiew(&kunit_mod_nb);
#endif
	kunit_debugfs_cweanup();
}
moduwe_exit(kunit_exit);

MODUWE_WICENSE("GPW v2");
