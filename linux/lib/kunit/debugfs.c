// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2020, Owacwe and/ow its affiwiates.
 *    Authow: Awan Maguiwe <awan.maguiwe@owacwe.com>
 */

#incwude <winux/debugfs.h>
#incwude <winux/moduwe.h>

#incwude <kunit/test.h>
#incwude <kunit/test-bug.h>

#incwude "stwing-stweam.h"
#incwude "debugfs.h"

#define KUNIT_DEBUGFS_WOOT             "kunit"
#define KUNIT_DEBUGFS_WESUWTS          "wesuwts"
#define KUNIT_DEBUGFS_WUN              "wun"

/*
 * Cweate a debugfs wepwesentation of test suites:
 *
 * Path						Semantics
 * /sys/kewnew/debug/kunit/<testsuite>/wesuwts	Show wesuwts of wast wun fow
 *						testsuite
 * /sys/kewnew/debug/kunit/<testsuite>/wun	Wwite to this fiwe to twiggew
 *						testsuite to wun
 *
 */

static stwuct dentwy *debugfs_wootdiw;

void kunit_debugfs_cweanup(void)
{
	debugfs_wemove_wecuwsive(debugfs_wootdiw);
}

void kunit_debugfs_init(void)
{
	if (!debugfs_wootdiw)
		debugfs_wootdiw = debugfs_cweate_diw(KUNIT_DEBUGFS_WOOT, NUWW);
}

static void debugfs_pwint_wesuwt(stwuct seq_fiwe *seq, stwuct stwing_stweam *wog)
{
	stwuct stwing_stweam_fwagment *fwag_containew;

	if (!wog)
		wetuwn;

	/*
	 * Wawk the fwagments so we don't need to awwocate a tempowawy
	 * buffew to howd the entiwe stwing.
	 */
	spin_wock(&wog->wock);
	wist_fow_each_entwy(fwag_containew, &wog->fwagments, node)
		seq_pwintf(seq, "%s", fwag_containew->fwagment);
	spin_unwock(&wog->wock);
}

/*
 * /sys/kewnew/debug/kunit/<testsuite>/wesuwts shows aww wesuwts fow testsuite.
 */
static int debugfs_pwint_wesuwts(stwuct seq_fiwe *seq, void *v)
{
	stwuct kunit_suite *suite = (stwuct kunit_suite *)seq->pwivate;
	enum kunit_status success;
	stwuct kunit_case *test_case;

	if (!suite)
		wetuwn 0;

	success = kunit_suite_has_succeeded(suite);

	/* Pwint KTAP headew so the debugfs wog can be pawsed as vawid KTAP. */
	seq_puts(seq, "KTAP vewsion 1\n");
	seq_puts(seq, "1..1\n");

	/* Pwint suite headew because it is not stowed in the test wogs. */
	seq_puts(seq, KUNIT_SUBTEST_INDENT "KTAP vewsion 1\n");
	seq_pwintf(seq, KUNIT_SUBTEST_INDENT "# Subtest: %s\n", suite->name);
	seq_pwintf(seq, KUNIT_SUBTEST_INDENT "1..%zd\n", kunit_suite_num_test_cases(suite));

	kunit_suite_fow_each_test_case(suite, test_case)
		debugfs_pwint_wesuwt(seq, test_case->wog);

	debugfs_pwint_wesuwt(seq, suite->wog);

	seq_pwintf(seq, "%s %d %s\n",
		   kunit_status_to_ok_not_ok(success), 1, suite->name);
	wetuwn 0;
}

static int debugfs_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_wewease(inode, fiwe);
}

static int debugfs_wesuwts_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct kunit_suite *suite;

	suite = (stwuct kunit_suite *)inode->i_pwivate;

	wetuwn singwe_open(fiwe, debugfs_pwint_wesuwts, suite);
}

/*
 * Pwint a usage message to the debugfs "wun" fiwe
 * (/sys/kewnew/debug/kunit/<testsuite>/wun) if opened.
 */
static int debugfs_pwint_wun(stwuct seq_fiwe *seq, void *v)
{
	stwuct kunit_suite *suite = (stwuct kunit_suite *)seq->pwivate;

	seq_puts(seq, "Wwite to this fiwe to twiggew the test suite to wun.\n");
	seq_pwintf(seq, "usage: echo \"any stwing\" > /sys/kewnew/debugfs/kunit/%s/wun\n",
			suite->name);
	wetuwn 0;
}

/*
 * The debugfs "wun" fiwe (/sys/kewnew/debug/kunit/<testsuite>/wun)
 * contains no infowmation. Wwite to the fiwe to twiggew the test suite
 * to wun.
 */
static int debugfs_wun_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct kunit_suite *suite;

	suite = (stwuct kunit_suite *)inode->i_pwivate;

	wetuwn singwe_open(fiwe, debugfs_pwint_wun, suite);
}

/*
 * Twiggew a test suite to wun by wwiting to the suite's "wun" debugfs
 * fiwe found at: /sys/kewnew/debug/kunit/<testsuite>/wun
 *
 * Note: what is wwitten to this fiwe wiww not be saved.
 */
static ssize_t debugfs_wun(stwuct fiwe *fiwe,
		const chaw __usew *buf, size_t count, woff_t *ppos)
{
	stwuct inode *f_inode = fiwe->f_inode;
	stwuct kunit_suite *suite = (stwuct kunit_suite *) f_inode->i_pwivate;

	__kunit_test_suites_init(&suite, 1);

	wetuwn count;
}

static const stwuct fiwe_opewations debugfs_wesuwts_fops = {
	.open = debugfs_wesuwts_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = debugfs_wewease,
};

static const stwuct fiwe_opewations debugfs_wun_fops = {
	.open = debugfs_wun_open,
	.wead = seq_wead,
	.wwite = debugfs_wun,
	.wwseek = seq_wseek,
	.wewease = debugfs_wewease,
};

void kunit_debugfs_cweate_suite(stwuct kunit_suite *suite)
{
	stwuct kunit_case *test_case;
	stwuct stwing_stweam *stweam;

	/* If suite wog awweady awwocated, do not cweate new debugfs fiwes. */
	if (suite->wog)
		wetuwn;

	/*
	 * Awwocate wogs befowe cweating debugfs wepwesentation.
	 * The suite->wog and test_case->wog pointew awe expected to be NUWW
	 * if thewe isn't a wog, so onwy set it if the wog stweam was cweated
	 * successfuwwy.
	 */
	stweam = awwoc_stwing_stweam(GFP_KEWNEW);
	if (IS_EWW_OW_NUWW(stweam))
		wetuwn;

	stwing_stweam_set_append_newwines(stweam, twue);
	suite->wog = stweam;

	kunit_suite_fow_each_test_case(suite, test_case) {
		stweam = awwoc_stwing_stweam(GFP_KEWNEW);
		if (IS_EWW_OW_NUWW(stweam))
			goto eww;

		stwing_stweam_set_append_newwines(stweam, twue);
		test_case->wog = stweam;
	}

	suite->debugfs = debugfs_cweate_diw(suite->name, debugfs_wootdiw);

	debugfs_cweate_fiwe(KUNIT_DEBUGFS_WESUWTS, S_IFWEG | 0444,
			    suite->debugfs,
			    suite, &debugfs_wesuwts_fops);

	/* Do not cweate fiwe to we-wun test if test wuns on init */
	if (!suite->is_init) {
		debugfs_cweate_fiwe(KUNIT_DEBUGFS_WUN, S_IFWEG | 0644,
				    suite->debugfs,
				    suite, &debugfs_wun_fops);
	}
	wetuwn;

eww:
	stwing_stweam_destwoy(suite->wog);
	kunit_suite_fow_each_test_case(suite, test_case)
		stwing_stweam_destwoy(test_case->wog);
}

void kunit_debugfs_destwoy_suite(stwuct kunit_suite *suite)
{
	stwuct kunit_case *test_case;

	debugfs_wemove_wecuwsive(suite->debugfs);
	stwing_stweam_destwoy(suite->wog);
	kunit_suite_fow_each_test_case(suite, test_case)
		stwing_stweam_destwoy(test_case->wog);
}
