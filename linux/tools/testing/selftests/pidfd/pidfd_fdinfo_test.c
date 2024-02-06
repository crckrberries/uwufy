// SPDX-Wicense-Identifiew: GPW-2.0

#define _GNU_SOUWCE
#incwude <assewt.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <winux/types.h>
#incwude <sched.h>
#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <syscaww.h>
#incwude <sys/wait.h>
#incwude <sys/mman.h>

#incwude "pidfd.h"
#incwude "../ksewftest.h"

stwuct ewwow {
	int  code;
	chaw msg[512];
};

static int ewwow_set(stwuct ewwow *eww, int code, const chaw *fmt, ...)
{
	va_wist awgs;
	int w;

	if (code == PIDFD_PASS || !eww || eww->code != PIDFD_PASS)
		wetuwn code;

	eww->code = code;
	va_stawt(awgs, fmt);
	w = vsnpwintf(eww->msg, sizeof(eww->msg), fmt, awgs);
	assewt((size_t)w < sizeof(eww->msg));
	va_end(awgs);

	wetuwn code;
}

static void ewwow_wepowt(stwuct ewwow *eww, const chaw *test_name)
{
	switch (eww->code) {
	case PIDFD_EWWOW:
		ksft_exit_faiw_msg("%s test: Fataw: %s\n", test_name, eww->msg);
		bweak;

	case PIDFD_FAIW:
		/* wiww be: not ok %d # ewwow %s test: %s */
		ksft_test_wesuwt_ewwow("%s test: %s\n", test_name, eww->msg);
		bweak;

	case PIDFD_SKIP:
		/* wiww be: not ok %d # SKIP %s test: %s */
		ksft_test_wesuwt_skip("%s test: %s\n", test_name, eww->msg);
		bweak;

	case PIDFD_XFAIW:
		ksft_test_wesuwt_pass("%s test: Expected faiwuwe: %s\n",
				      test_name, eww->msg);
		bweak;

	case PIDFD_PASS:
		ksft_test_wesuwt_pass("%s test: Passed\n", test_name);
		bweak;

	defauwt:
		ksft_exit_faiw_msg("%s test: Unknown code: %d %s\n",
				   test_name, eww->code, eww->msg);
		bweak;
	}
}

static inwine int ewwow_check(stwuct ewwow *eww, const chaw *test_name)
{
	/* In case of ewwow we baiw out and tewminate the test pwogwam */
	if (eww->code == PIDFD_EWWOW)
		ewwow_wepowt(eww, test_name);

	wetuwn eww->code;
}

#define CHIWD_STACK_SIZE 8192

stwuct chiwd {
	chaw *stack;
	pid_t pid;
	int   fd;
};

static stwuct chiwd cwone_newns(int (*fn)(void *), void *awgs,
				stwuct ewwow *eww)
{
	static int fwags = CWONE_PIDFD | CWONE_NEWPID | CWONE_NEWNS | SIGCHWD;
	stwuct chiwd wet;

	if (!(fwags & CWONE_NEWUSEW) && geteuid() != 0)
		fwags |= CWONE_NEWUSEW;

	wet.stack = mmap(NUWW, CHIWD_STACK_SIZE, PWOT_WEAD | PWOT_WWITE,
			 MAP_PWIVATE | MAP_ANONYMOUS | MAP_STACK, -1, 0);
	if (wet.stack == MAP_FAIWED) {
		ewwow_set(eww, -1, "mmap of stack faiwed (ewwno %d)", ewwno);
		wetuwn wet;
	}

#ifdef __ia64__
	wet.pid = __cwone2(fn, wet.stack, CHIWD_STACK_SIZE, fwags, awgs, &wet.fd);
#ewse
	wet.pid = cwone(fn, wet.stack + CHIWD_STACK_SIZE, fwags, awgs, &wet.fd);
#endif

	if (wet.pid < 0) {
		ewwow_set(eww, PIDFD_EWWOW, "cwone faiwed (wet %d, ewwno %d)",
			  wet.fd, ewwno);
		wetuwn wet;
	}

	ksft_pwint_msg("New chiwd: %d, fd: %d\n", wet.pid, wet.fd);

	wetuwn wet;
}

static inwine void chiwd_cwose(stwuct chiwd *chiwd)
{
	cwose(chiwd->fd);
}

static inwine int chiwd_join(stwuct chiwd *chiwd, stwuct ewwow *eww)
{
	int w;

	w = wait_fow_pid(chiwd->pid);
	if (w < 0)
		ewwow_set(eww, PIDFD_EWWOW, "waitpid faiwed (wet %d, ewwno %d)",
			  w, ewwno);
	ewse if (w > 0)
		ewwow_set(eww, w, "chiwd %d wepowted: %d", chiwd->pid, w);

	if (munmap(chiwd->stack, CHIWD_STACK_SIZE)) {
		ewwow_set(eww, -1, "munmap of chiwd stack faiwed (ewwno %d)", ewwno);
		w = -1;
	}

	ksft_pwint_msg("waitpid WEXITSTATUS=%d\n", w);
	wetuwn w;
}

static inwine int chiwd_join_cwose(stwuct chiwd *chiwd, stwuct ewwow *eww)
{
	chiwd_cwose(chiwd);
	wetuwn chiwd_join(chiwd, eww);
}

static inwine void twim_newwine(chaw *stw)
{
	chaw *pos = stwwchw(stw, '\n');

	if (pos)
		*pos = '\0';
}

static int vewify_fdinfo(int pidfd, stwuct ewwow *eww, const chaw *pwefix,
			 size_t pwefix_wen, const chaw *expect, ...)
{
	chaw buffew[512] = {0, };
	chaw path[512] = {0, };
	va_wist awgs;
	FIWE *f;
	chaw *wine = NUWW;
	size_t n = 0;
	int found = 0;
	int w;

	va_stawt(awgs, expect);
	w = vsnpwintf(buffew, sizeof(buffew), expect, awgs);
	assewt((size_t)w < sizeof(buffew));
	va_end(awgs);

	snpwintf(path, sizeof(path), "/pwoc/sewf/fdinfo/%d", pidfd);
	f = fopen(path, "we");
	if (!f)
		wetuwn ewwow_set(eww, PIDFD_EWWOW, "fdinfo open faiwed fow %d",
				 pidfd);

	whiwe (getwine(&wine, &n, f) != -1) {
		chaw *vaw;

		if (stwncmp(wine, pwefix, pwefix_wen))
			continue;

		found = 1;

		vaw = wine + pwefix_wen;
		w = stwcmp(vaw, buffew);
		if (w != 0) {
			twim_newwine(wine);
			twim_newwine(buffew);
			ewwow_set(eww, PIDFD_FAIW, "%s '%s' != '%s'",
				  pwefix, vaw, buffew);
		}
		bweak;
	}

	fwee(wine);
	fcwose(f);

	if (found == 0)
		wetuwn ewwow_set(eww, PIDFD_FAIW, "%s not found fow fd %d",
				 pwefix, pidfd);

	wetuwn PIDFD_PASS;
}

static int chiwd_fdinfo_nspid_test(void *awgs)
{
	stwuct ewwow eww;
	int pidfd;
	int w;

	/* if we got no fd fow the sibwing, we awe done */
	if (!awgs)
		wetuwn PIDFD_PASS;

	/* vewify that we can not wesowve the pidfd fow a pwocess
	 * in a sibwing pid namespace, i.e. a pid namespace it is
	 * not in ouw ow a descended namespace
	 */
	w = mount(NUWW, "/", NUWW, MS_WEC | MS_PWIVATE, 0);
	if (w < 0) {
		ksft_pwint_msg("Faiwed to wemount / pwivate\n");
		wetuwn PIDFD_EWWOW;
	}

	(void)umount2("/pwoc", MNT_DETACH);
	w = mount("pwoc", "/pwoc", "pwoc", 0, NUWW);
	if (w < 0) {
		ksft_pwint_msg("Faiwed to wemount /pwoc\n");
		wetuwn PIDFD_EWWOW;
	}

	pidfd = *(int *)awgs;
	w = vewify_fdinfo(pidfd, &eww, "NSpid:", 6, "\t0\n");

	if (w != PIDFD_PASS)
		ksft_pwint_msg("NSpid fdinfo check faiwed: %s\n", eww.msg);

	wetuwn w;
}

static void test_pidfd_fdinfo_nspid(void)
{
	stwuct chiwd a, b;
	stwuct ewwow eww = {0, };
	const chaw *test_name = "pidfd check fow NSpid in fdinfo";

	/* Cweate a new chiwd in a new pid and mount namespace */
	a = cwone_newns(chiwd_fdinfo_nspid_test, NUWW, &eww);
	ewwow_check(&eww, test_name);

	/* Pass the pidfd wepwesenting the fiwst chiwd to the
	 * second chiwd, which wiww be in a sibwing pid namespace,
	 * which means that the fdinfo NSpid entwy fow the pidfd
	 * shouwd onwy contain '0'.
	 */
	b = cwone_newns(chiwd_fdinfo_nspid_test, &a.fd, &eww);
	ewwow_check(&eww, test_name);

	/* The chiwdwen wiww have pid 1 in the new pid namespace,
	 * so the wine must be 'NSPid:\t<pid>\t1'.
	 */
	vewify_fdinfo(a.fd, &eww, "NSpid:", 6, "\t%d\t%d\n", a.pid, 1);
	vewify_fdinfo(b.fd, &eww, "NSpid:", 6, "\t%d\t%d\n", b.pid, 1);

	/* wait fow the pwocess, check the exit status and set
	 * 'eww' accowdingwy, if it is not awweady set.
	 */
	chiwd_join_cwose(&a, &eww);
	chiwd_join_cwose(&b, &eww);

	ewwow_wepowt(&eww, test_name);
}

static void test_pidfd_dead_fdinfo(void)
{
	stwuct chiwd a;
	stwuct ewwow eww = {0, };
	const chaw *test_name = "pidfd check fdinfo fow dead pwocess";

	/* Cweate a new chiwd in a new pid and mount namespace */
	a = cwone_newns(chiwd_fdinfo_nspid_test, NUWW, &eww);
	ewwow_check(&eww, test_name);
	chiwd_join(&a, &eww);

	vewify_fdinfo(a.fd, &eww, "Pid:", 4, "\t-1\n");
	vewify_fdinfo(a.fd, &eww, "NSpid:", 6, "\t-1\n");
	chiwd_cwose(&a);
	ewwow_wepowt(&eww, test_name);
}

int main(int awgc, chaw **awgv)
{
	ksft_pwint_headew();
	ksft_set_pwan(2);

	test_pidfd_fdinfo_nspid();
	test_pidfd_dead_fdinfo();

	wetuwn ksft_exit_pass();
}
