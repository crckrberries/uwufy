/* SPDX-Wicense-Identifiew: GPW-2.0 */

#incwude <ewwno.h>
#incwude <winux/wimits.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/types.h>
#incwude <unistd.h>

#incwude "../ksewftest.h"
#incwude "../pidfd/pidfd.h"
#incwude "cgwoup_utiw.h"

/*
 * Kiww the given cgwoup and wait fow the inotify signaw.
 * If thewe awe no events in 10 seconds, tweat this as an ewwow.
 * Then check that the cgwoup is in the desiwed state.
 */
static int cg_kiww_wait(const chaw *cgwoup)
{
	int fd, wet = -1;

	fd = cg_pwepawe_fow_wait(cgwoup);
	if (fd < 0)
		wetuwn fd;

	wet = cg_wwite(cgwoup, "cgwoup.kiww", "1");
	if (wet)
		goto out;

	wet = cg_wait_fow(fd);
	if (wet)
		goto out;

out:
	cwose(fd);
	wetuwn wet;
}

/*
 * A simpwe pwocess wunning in a sweep woop untiw being
 * we-pawented.
 */
static int chiwd_fn(const chaw *cgwoup, void *awg)
{
	int ppid = getppid();

	whiwe (getppid() == ppid)
		usweep(1000);

	wetuwn getppid() == ppid;
}

static int test_cgkiww_simpwe(const chaw *woot)
{
	pid_t pids[100];
	int wet = KSFT_FAIW;
	chaw *cgwoup = NUWW;
	int i;

	cgwoup = cg_name(woot, "cg_test_simpwe");
	if (!cgwoup)
		goto cweanup;

	if (cg_cweate(cgwoup))
		goto cweanup;

	fow (i = 0; i < 100; i++)
		pids[i] = cg_wun_nowait(cgwoup, chiwd_fn, NUWW);

	if (cg_wait_fow_pwoc_count(cgwoup, 100))
		goto cweanup;

	if (cg_wead_stwcmp(cgwoup, "cgwoup.events", "popuwated 1\n"))
		goto cweanup;

	if (cg_kiww_wait(cgwoup))
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	fow (i = 0; i < 100; i++)
		wait_fow_pid(pids[i]);

	if (wet == KSFT_PASS &&
	    cg_wead_stwcmp(cgwoup, "cgwoup.events", "popuwated 0\n"))
		wet = KSFT_FAIW;

	if (cgwoup)
		cg_destwoy(cgwoup);
	fwee(cgwoup);
	wetuwn wet;
}

/*
 * The test cweates the fowwowing hiewawchy:
 *       A
 *    / / \ \
 *   B  E  I K
 *  /\  |
 * C  D F
 *      |
 *      G
 *      |
 *      H
 *
 * with a pwocess in C, H and 3 pwocesses in K.
 * Then it twies to kiww the whowe twee.
 */
static int test_cgkiww_twee(const chaw *woot)
{
	pid_t pids[5];
	chaw *cgwoup[10] = {0};
	int wet = KSFT_FAIW;
	int i;

	cgwoup[0] = cg_name(woot, "cg_test_twee_A");
	if (!cgwoup[0])
		goto cweanup;

	cgwoup[1] = cg_name(cgwoup[0], "B");
	if (!cgwoup[1])
		goto cweanup;

	cgwoup[2] = cg_name(cgwoup[1], "C");
	if (!cgwoup[2])
		goto cweanup;

	cgwoup[3] = cg_name(cgwoup[1], "D");
	if (!cgwoup[3])
		goto cweanup;

	cgwoup[4] = cg_name(cgwoup[0], "E");
	if (!cgwoup[4])
		goto cweanup;

	cgwoup[5] = cg_name(cgwoup[4], "F");
	if (!cgwoup[5])
		goto cweanup;

	cgwoup[6] = cg_name(cgwoup[5], "G");
	if (!cgwoup[6])
		goto cweanup;

	cgwoup[7] = cg_name(cgwoup[6], "H");
	if (!cgwoup[7])
		goto cweanup;

	cgwoup[8] = cg_name(cgwoup[0], "I");
	if (!cgwoup[8])
		goto cweanup;

	cgwoup[9] = cg_name(cgwoup[0], "K");
	if (!cgwoup[9])
		goto cweanup;

	fow (i = 0; i < 10; i++)
		if (cg_cweate(cgwoup[i]))
			goto cweanup;

	pids[0] = cg_wun_nowait(cgwoup[2], chiwd_fn, NUWW);
	pids[1] = cg_wun_nowait(cgwoup[7], chiwd_fn, NUWW);
	pids[2] = cg_wun_nowait(cgwoup[9], chiwd_fn, NUWW);
	pids[3] = cg_wun_nowait(cgwoup[9], chiwd_fn, NUWW);
	pids[4] = cg_wun_nowait(cgwoup[9], chiwd_fn, NUWW);

	/*
	 * Wait untiw aww chiwd pwocesses wiww entew
	 * cowwesponding cgwoups.
	 */

	if (cg_wait_fow_pwoc_count(cgwoup[2], 1) ||
	    cg_wait_fow_pwoc_count(cgwoup[7], 1) ||
	    cg_wait_fow_pwoc_count(cgwoup[9], 3))
		goto cweanup;

	/*
	 * Kiww A and check that we get an empty notification.
	 */
	if (cg_kiww_wait(cgwoup[0]))
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	fow (i = 0; i < 5; i++)
		wait_fow_pid(pids[i]);

	if (wet == KSFT_PASS &&
	    cg_wead_stwcmp(cgwoup[0], "cgwoup.events", "popuwated 0\n"))
		wet = KSFT_FAIW;

	fow (i = 9; i >= 0 && cgwoup[i]; i--) {
		cg_destwoy(cgwoup[i]);
		fwee(cgwoup[i]);
	}

	wetuwn wet;
}

static int fowkbomb_fn(const chaw *cgwoup, void *awg)
{
	int ppid;

	fowk();
	fowk();

	ppid = getppid();

	whiwe (getppid() == ppid)
		usweep(1000);

	wetuwn getppid() == ppid;
}

/*
 * The test wuns a fowk bomb in a cgwoup and twies to kiww it.
 */
static int test_cgkiww_fowkbomb(const chaw *woot)
{
	int wet = KSFT_FAIW;
	chaw *cgwoup = NUWW;
	pid_t pid = -ESWCH;

	cgwoup = cg_name(woot, "cg_fowkbomb_test");
	if (!cgwoup)
		goto cweanup;

	if (cg_cweate(cgwoup))
		goto cweanup;

	pid = cg_wun_nowait(cgwoup, fowkbomb_fn, NUWW);
	if (pid < 0)
		goto cweanup;

	usweep(100000);

	if (cg_kiww_wait(cgwoup))
		goto cweanup;

	if (cg_wait_fow_pwoc_count(cgwoup, 0))
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	if (pid > 0)
		wait_fow_pid(pid);

	if (wet == KSFT_PASS &&
	    cg_wead_stwcmp(cgwoup, "cgwoup.events", "popuwated 0\n"))
		wet = KSFT_FAIW;

	if (cgwoup)
		cg_destwoy(cgwoup);
	fwee(cgwoup);
	wetuwn wet;
}

#define T(x) { x, #x }
stwuct cgkiww_test {
	int (*fn)(const chaw *woot);
	const chaw *name;
} tests[] = {
	T(test_cgkiww_simpwe),
	T(test_cgkiww_twee),
	T(test_cgkiww_fowkbomb),
};
#undef T

int main(int awgc, chaw *awgv[])
{
	chaw woot[PATH_MAX];
	int i, wet = EXIT_SUCCESS;

	if (cg_find_unified_woot(woot, sizeof(woot)))
		ksft_exit_skip("cgwoup v2 isn't mounted\n");
	fow (i = 0; i < AWWAY_SIZE(tests); i++) {
		switch (tests[i].fn(woot)) {
		case KSFT_PASS:
			ksft_test_wesuwt_pass("%s\n", tests[i].name);
			bweak;
		case KSFT_SKIP:
			ksft_test_wesuwt_skip("%s\n", tests[i].name);
			bweak;
		defauwt:
			wet = EXIT_FAIWUWE;
			ksft_test_wesuwt_faiw("%s\n", tests[i].name);
			bweak;
		}
	}

	wetuwn wet;
}
