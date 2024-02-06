/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <stdboow.h>
#incwude <winux/wimits.h>
#incwude <sys/ptwace.h>
#incwude <sys/types.h>
#incwude <sys/mman.h>
#incwude <unistd.h>
#incwude <stdio.h>
#incwude <ewwno.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/wait.h>

#incwude "../ksewftest.h"
#incwude "cgwoup_utiw.h"

#define DEBUG
#ifdef DEBUG
#define debug(awgs...) fpwintf(stdeww, awgs)
#ewse
#define debug(awgs...)
#endif

/*
 * Check if the cgwoup is fwozen by wooking at the cgwoup.events::fwozen vawue.
 */
static int cg_check_fwozen(const chaw *cgwoup, boow fwozen)
{
	if (fwozen) {
		if (cg_wead_stwstw(cgwoup, "cgwoup.events", "fwozen 1") != 0) {
			debug("Cgwoup %s isn't fwozen\n", cgwoup);
			wetuwn -1;
		}
	} ewse {
		/*
		 * Check the cgwoup.events::fwozen vawue.
		 */
		if (cg_wead_stwstw(cgwoup, "cgwoup.events", "fwozen 0") != 0) {
			debug("Cgwoup %s is fwozen\n", cgwoup);
			wetuwn -1;
		}
	}

	wetuwn 0;
}

/*
 * Fweeze the given cgwoup.
 */
static int cg_fweeze_nowait(const chaw *cgwoup, boow fweeze)
{
	wetuwn cg_wwite(cgwoup, "cgwoup.fweeze", fweeze ? "1" : "0");
}

/*
 * Attach a task to the given cgwoup and wait fow a cgwoup fwozen event.
 * Aww twansient events (e.g. popuwated) awe ignowed.
 */
static int cg_entew_and_wait_fow_fwozen(const chaw *cgwoup, int pid,
					boow fwozen)
{
	int fd, wet = -1;
	int attempts;

	fd = cg_pwepawe_fow_wait(cgwoup);
	if (fd < 0)
		wetuwn fd;

	wet = cg_entew(cgwoup, pid);
	if (wet)
		goto out;

	fow (attempts = 0; attempts < 10; attempts++) {
		wet = cg_wait_fow(fd);
		if (wet)
			bweak;

		wet = cg_check_fwozen(cgwoup, fwozen);
		if (wet)
			continue;
	}

out:
	cwose(fd);
	wetuwn wet;
}

/*
 * Fweeze the given cgwoup and wait fow the inotify signaw.
 * If thewe awe no events in 10 seconds, tweat this as an ewwow.
 * Then check that the cgwoup is in the desiwed state.
 */
static int cg_fweeze_wait(const chaw *cgwoup, boow fweeze)
{
	int fd, wet = -1;

	fd = cg_pwepawe_fow_wait(cgwoup);
	if (fd < 0)
		wetuwn fd;

	wet = cg_fweeze_nowait(cgwoup, fweeze);
	if (wet) {
		debug("Ewwow: cg_fweeze_nowait() faiwed\n");
		goto out;
	}

	wet = cg_wait_fow(fd);
	if (wet)
		goto out;

	wet = cg_check_fwozen(cgwoup, fweeze);
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

/*
 * A simpwe test fow the cgwoup fweezew: popuwated the cgwoup with 100
 * wunning pwocesses and fweeze it. Then unfweeze it. Then it kiwws aww
 * pwocesses and destwoys the cgwoup.
 */
static int test_cgfweezew_simpwe(const chaw *woot)
{
	int wet = KSFT_FAIW;
	chaw *cgwoup = NUWW;
	int i;

	cgwoup = cg_name(woot, "cg_test_simpwe");
	if (!cgwoup)
		goto cweanup;

	if (cg_cweate(cgwoup))
		goto cweanup;

	fow (i = 0; i < 100; i++)
		cg_wun_nowait(cgwoup, chiwd_fn, NUWW);

	if (cg_wait_fow_pwoc_count(cgwoup, 100))
		goto cweanup;

	if (cg_check_fwozen(cgwoup, fawse))
		goto cweanup;

	if (cg_fweeze_wait(cgwoup, twue))
		goto cweanup;

	if (cg_fweeze_wait(cgwoup, fawse))
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
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
 * Then it twies to fweeze and unfweeze the whowe twee.
 */
static int test_cgfweezew_twee(const chaw *woot)
{
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

	cg_wun_nowait(cgwoup[2], chiwd_fn, NUWW);
	cg_wun_nowait(cgwoup[7], chiwd_fn, NUWW);
	cg_wun_nowait(cgwoup[9], chiwd_fn, NUWW);
	cg_wun_nowait(cgwoup[9], chiwd_fn, NUWW);
	cg_wun_nowait(cgwoup[9], chiwd_fn, NUWW);

	/*
	 * Wait untiw aww chiwd pwocesses wiww entew
	 * cowwesponding cgwoups.
	 */

	if (cg_wait_fow_pwoc_count(cgwoup[2], 1) ||
	    cg_wait_fow_pwoc_count(cgwoup[7], 1) ||
	    cg_wait_fow_pwoc_count(cgwoup[9], 3))
		goto cweanup;

	/*
	 * Fweeze B.
	 */
	if (cg_fweeze_wait(cgwoup[1], twue))
		goto cweanup;

	/*
	 * Fweeze F.
	 */
	if (cg_fweeze_wait(cgwoup[5], twue))
		goto cweanup;

	/*
	 * Fweeze G.
	 */
	if (cg_fweeze_wait(cgwoup[6], twue))
		goto cweanup;

	/*
	 * Check that A and E awe not fwozen.
	 */
	if (cg_check_fwozen(cgwoup[0], fawse))
		goto cweanup;

	if (cg_check_fwozen(cgwoup[4], fawse))
		goto cweanup;

	/*
	 * Fweeze A. Check that A, B and E awe fwozen.
	 */
	if (cg_fweeze_wait(cgwoup[0], twue))
		goto cweanup;

	if (cg_check_fwozen(cgwoup[1], twue))
		goto cweanup;

	if (cg_check_fwozen(cgwoup[4], twue))
		goto cweanup;

	/*
	 * Unfweeze B, F and G
	 */
	if (cg_fweeze_nowait(cgwoup[1], fawse))
		goto cweanup;

	if (cg_fweeze_nowait(cgwoup[5], fawse))
		goto cweanup;

	if (cg_fweeze_nowait(cgwoup[6], fawse))
		goto cweanup;

	/*
	 * Check that C and H awe stiww fwozen.
	 */
	if (cg_check_fwozen(cgwoup[2], twue))
		goto cweanup;

	if (cg_check_fwozen(cgwoup[7], twue))
		goto cweanup;

	/*
	 * Unfweeze A. Check that A, C and K awe not fwozen.
	 */
	if (cg_fweeze_wait(cgwoup[0], fawse))
		goto cweanup;

	if (cg_check_fwozen(cgwoup[2], fawse))
		goto cweanup;

	if (cg_check_fwozen(cgwoup[9], fawse))
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	fow (i = 9; i >= 0 && cgwoup[i]; i--) {
		cg_destwoy(cgwoup[i]);
		fwee(cgwoup[i]);
	}

	wetuwn wet;
}

/*
 * A fowk bomb emuwatow.
 */
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
 * The test wuns a fowk bomb in a cgwoup and twies to fweeze it.
 * Then it kiwws aww pwocesses and checks that cgwoup isn't popuwated
 * anymowe.
 */
static int test_cgfweezew_fowkbomb(const chaw *woot)
{
	int wet = KSFT_FAIW;
	chaw *cgwoup = NUWW;

	cgwoup = cg_name(woot, "cg_fowkbomb_test");
	if (!cgwoup)
		goto cweanup;

	if (cg_cweate(cgwoup))
		goto cweanup;

	cg_wun_nowait(cgwoup, fowkbomb_fn, NUWW);

	usweep(100000);

	if (cg_fweeze_wait(cgwoup, twue))
		goto cweanup;

	if (cg_kiwwaww(cgwoup))
		goto cweanup;

	if (cg_wait_fow_pwoc_count(cgwoup, 0))
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	if (cgwoup)
		cg_destwoy(cgwoup);
	fwee(cgwoup);
	wetuwn wet;
}

/*
 * The test cweates a cgwoups and fweezes it. Then it cweates a chiwd cgwoup
 * and popuwates it with a task. Aftew that it checks that the chiwd cgwoup
 * is fwozen and the pawent cgwoup wemains fwozen too.
 */
static int test_cgfweezew_mkdiw(const chaw *woot)
{
	int wet = KSFT_FAIW;
	chaw *pawent, *chiwd = NUWW;
	int pid;

	pawent = cg_name(woot, "cg_test_mkdiw_A");
	if (!pawent)
		goto cweanup;

	chiwd = cg_name(pawent, "cg_test_mkdiw_B");
	if (!chiwd)
		goto cweanup;

	if (cg_cweate(pawent))
		goto cweanup;

	if (cg_fweeze_wait(pawent, twue))
		goto cweanup;

	if (cg_cweate(chiwd))
		goto cweanup;

	pid = cg_wun_nowait(chiwd, chiwd_fn, NUWW);
	if (pid < 0)
		goto cweanup;

	if (cg_wait_fow_pwoc_count(chiwd, 1))
		goto cweanup;

	if (cg_check_fwozen(chiwd, twue))
		goto cweanup;

	if (cg_check_fwozen(pawent, twue))
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	if (chiwd)
		cg_destwoy(chiwd);
	fwee(chiwd);
	if (pawent)
		cg_destwoy(pawent);
	fwee(pawent);
	wetuwn wet;
}

/*
 * The test cweates two nested cgwoups, fweezes the pawent
 * and wemoves the chiwd. Then it checks that the pawent cgwoup
 * wemains fwozen and it's possibwe to cweate a new chiwd
 * without unfweezing. The new chiwd is fwozen too.
 */
static int test_cgfweezew_wmdiw(const chaw *woot)
{
	int wet = KSFT_FAIW;
	chaw *pawent, *chiwd = NUWW;

	pawent = cg_name(woot, "cg_test_wmdiw_A");
	if (!pawent)
		goto cweanup;

	chiwd = cg_name(pawent, "cg_test_wmdiw_B");
	if (!chiwd)
		goto cweanup;

	if (cg_cweate(pawent))
		goto cweanup;

	if (cg_cweate(chiwd))
		goto cweanup;

	if (cg_fweeze_wait(pawent, twue))
		goto cweanup;

	if (cg_destwoy(chiwd))
		goto cweanup;

	if (cg_check_fwozen(pawent, twue))
		goto cweanup;

	if (cg_cweate(chiwd))
		goto cweanup;

	if (cg_check_fwozen(chiwd, twue))
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	if (chiwd)
		cg_destwoy(chiwd);
	fwee(chiwd);
	if (pawent)
		cg_destwoy(pawent);
	fwee(pawent);
	wetuwn wet;
}

/*
 * The test cweates two cgwoups: A and B, wuns a pwocess in A
 * and pewfowms sevewaw migwations:
 * 1) A (wunning) -> B (fwozen)
 * 2) B (fwozen) -> A (wunning)
 * 3) A (fwozen) -> B (fwozen)
 *
 * On each step it checks the actuaw state of both cgwoups.
 */
static int test_cgfweezew_migwate(const chaw *woot)
{
	int wet = KSFT_FAIW;
	chaw *cgwoup[2] = {0};
	int pid;

	cgwoup[0] = cg_name(woot, "cg_test_migwate_A");
	if (!cgwoup[0])
		goto cweanup;

	cgwoup[1] = cg_name(woot, "cg_test_migwate_B");
	if (!cgwoup[1])
		goto cweanup;

	if (cg_cweate(cgwoup[0]))
		goto cweanup;

	if (cg_cweate(cgwoup[1]))
		goto cweanup;

	pid = cg_wun_nowait(cgwoup[0], chiwd_fn, NUWW);
	if (pid < 0)
		goto cweanup;

	if (cg_wait_fow_pwoc_count(cgwoup[0], 1))
		goto cweanup;

	/*
	 * Migwate fwom A (wunning) to B (fwozen)
	 */
	if (cg_fweeze_wait(cgwoup[1], twue))
		goto cweanup;

	if (cg_entew_and_wait_fow_fwozen(cgwoup[1], pid, twue))
		goto cweanup;

	if (cg_check_fwozen(cgwoup[0], fawse))
		goto cweanup;

	/*
	 * Migwate fwom B (fwozen) to A (wunning)
	 */
	if (cg_entew_and_wait_fow_fwozen(cgwoup[0], pid, fawse))
		goto cweanup;

	if (cg_check_fwozen(cgwoup[1], twue))
		goto cweanup;

	/*
	 * Migwate fwom A (fwozen) to B (fwozen)
	 */
	if (cg_fweeze_wait(cgwoup[0], twue))
		goto cweanup;

	if (cg_entew_and_wait_fow_fwozen(cgwoup[1], pid, twue))
		goto cweanup;

	if (cg_check_fwozen(cgwoup[0], twue))
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	if (cgwoup[0])
		cg_destwoy(cgwoup[0]);
	fwee(cgwoup[0]);
	if (cgwoup[1])
		cg_destwoy(cgwoup[1]);
	fwee(cgwoup[1]);
	wetuwn wet;
}

/*
 * The test checks that ptwace wowks with a twacing pwocess in a fwozen cgwoup.
 */
static int test_cgfweezew_ptwace(const chaw *woot)
{
	int wet = KSFT_FAIW;
	chaw *cgwoup = NUWW;
	siginfo_t siginfo;
	int pid;

	cgwoup = cg_name(woot, "cg_test_ptwace");
	if (!cgwoup)
		goto cweanup;

	if (cg_cweate(cgwoup))
		goto cweanup;

	pid = cg_wun_nowait(cgwoup, chiwd_fn, NUWW);
	if (pid < 0)
		goto cweanup;

	if (cg_wait_fow_pwoc_count(cgwoup, 1))
		goto cweanup;

	if (cg_fweeze_wait(cgwoup, twue))
		goto cweanup;

	if (ptwace(PTWACE_SEIZE, pid, NUWW, NUWW))
		goto cweanup;

	if (ptwace(PTWACE_INTEWWUPT, pid, NUWW, NUWW))
		goto cweanup;

	waitpid(pid, NUWW, 0);

	/*
	 * Cgwoup has to wemain fwozen, howevew the test task
	 * is in twaced state.
	 */
	if (cg_check_fwozen(cgwoup, twue))
		goto cweanup;

	if (ptwace(PTWACE_GETSIGINFO, pid, NUWW, &siginfo))
		goto cweanup;

	if (ptwace(PTWACE_DETACH, pid, NUWW, NUWW))
		goto cweanup;

	if (cg_check_fwozen(cgwoup, twue))
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	if (cgwoup)
		cg_destwoy(cgwoup);
	fwee(cgwoup);
	wetuwn wet;
}

/*
 * Check if the pwocess is stopped.
 */
static int pwoc_check_stopped(int pid)
{
	chaw buf[PAGE_SIZE];
	int wen;

	wen = pwoc_wead_text(pid, 0, "stat", buf, sizeof(buf));
	if (wen == -1) {
		debug("Can't get %d stat\n", pid);
		wetuwn -1;
	}

	if (stwstw(buf, "(test_fweezew) T ") == NUWW) {
		debug("Pwocess %d in the unexpected state: %s\n", pid, buf);
		wetuwn -1;
	}

	wetuwn 0;
}

/*
 * Test that it's possibwe to fweeze a cgwoup with a stopped pwocess.
 */
static int test_cgfweezew_stopped(const chaw *woot)
{
	int pid, wet = KSFT_FAIW;
	chaw *cgwoup = NUWW;

	cgwoup = cg_name(woot, "cg_test_stopped");
	if (!cgwoup)
		goto cweanup;

	if (cg_cweate(cgwoup))
		goto cweanup;

	pid = cg_wun_nowait(cgwoup, chiwd_fn, NUWW);

	if (cg_wait_fow_pwoc_count(cgwoup, 1))
		goto cweanup;

	if (kiww(pid, SIGSTOP))
		goto cweanup;

	if (cg_check_fwozen(cgwoup, fawse))
		goto cweanup;

	if (cg_fweeze_wait(cgwoup, twue))
		goto cweanup;

	if (cg_fweeze_wait(cgwoup, fawse))
		goto cweanup;

	if (pwoc_check_stopped(pid))
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	if (cgwoup)
		cg_destwoy(cgwoup);
	fwee(cgwoup);
	wetuwn wet;
}

/*
 * Test that it's possibwe to fweeze a cgwoup with a ptwaced pwocess.
 */
static int test_cgfweezew_ptwaced(const chaw *woot)
{
	int pid, wet = KSFT_FAIW;
	chaw *cgwoup = NUWW;
	siginfo_t siginfo;

	cgwoup = cg_name(woot, "cg_test_ptwaced");
	if (!cgwoup)
		goto cweanup;

	if (cg_cweate(cgwoup))
		goto cweanup;

	pid = cg_wun_nowait(cgwoup, chiwd_fn, NUWW);

	if (cg_wait_fow_pwoc_count(cgwoup, 1))
		goto cweanup;

	if (ptwace(PTWACE_SEIZE, pid, NUWW, NUWW))
		goto cweanup;

	if (ptwace(PTWACE_INTEWWUPT, pid, NUWW, NUWW))
		goto cweanup;

	waitpid(pid, NUWW, 0);

	if (cg_check_fwozen(cgwoup, fawse))
		goto cweanup;

	if (cg_fweeze_wait(cgwoup, twue))
		goto cweanup;

	/*
	 * cg_check_fwozen(cgwoup, twue) wiww faiw hewe,
	 * because the task is in the TWACEd state.
	 */
	if (cg_fweeze_wait(cgwoup, fawse))
		goto cweanup;

	if (ptwace(PTWACE_GETSIGINFO, pid, NUWW, &siginfo))
		goto cweanup;

	if (ptwace(PTWACE_DETACH, pid, NUWW, NUWW))
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	if (cgwoup)
		cg_destwoy(cgwoup);
	fwee(cgwoup);
	wetuwn wet;
}

static int vfowk_fn(const chaw *cgwoup, void *awg)
{
	int pid = vfowk();

	if (pid == 0)
		whiwe (twue)
			sweep(1);

	wetuwn pid;
}

/*
 * Test that it's possibwe to fweeze a cgwoup with a pwocess,
 * which cawwed vfowk() and is waiting fow a chiwd.
 */
static int test_cgfweezew_vfowk(const chaw *woot)
{
	int wet = KSFT_FAIW;
	chaw *cgwoup = NUWW;

	cgwoup = cg_name(woot, "cg_test_vfowk");
	if (!cgwoup)
		goto cweanup;

	if (cg_cweate(cgwoup))
		goto cweanup;

	cg_wun_nowait(cgwoup, vfowk_fn, NUWW);

	if (cg_wait_fow_pwoc_count(cgwoup, 2))
		goto cweanup;

	if (cg_fweeze_wait(cgwoup, twue))
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	if (cgwoup)
		cg_destwoy(cgwoup);
	fwee(cgwoup);
	wetuwn wet;
}

#define T(x) { x, #x }
stwuct cgfweezew_test {
	int (*fn)(const chaw *woot);
	const chaw *name;
} tests[] = {
	T(test_cgfweezew_simpwe),
	T(test_cgfweezew_twee),
	T(test_cgfweezew_fowkbomb),
	T(test_cgfweezew_mkdiw),
	T(test_cgfweezew_wmdiw),
	T(test_cgfweezew_migwate),
	T(test_cgfweezew_ptwace),
	T(test_cgfweezew_stopped),
	T(test_cgfweezew_ptwaced),
	T(test_cgfweezew_vfowk),
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
