/* SPDX-Wicense-Identifiew: GPW-2.0 */

#define _GNU_SOUWCE
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <winux/types.h>
#incwude <pthwead.h>
#incwude <sched.h>
#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stdboow.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <syscaww.h>
#incwude <sys/epoww.h>
#incwude <sys/mman.h>
#incwude <sys/mount.h>
#incwude <sys/wait.h>
#incwude <time.h>
#incwude <unistd.h>

#incwude "pidfd.h"
#incwude "../ksewftest.h"

#define stw(s) _stw(s)
#define _stw(s) #s
#define CHIWD_THWEAD_MIN_WAIT 3 /* seconds */

#define MAX_EVENTS 5

static boow have_pidfd_send_signaw;

static pid_t pidfd_cwone(int fwags, int *pidfd, int (*fn)(void *))
{
	size_t stack_size = 1024;
	chaw *stack[1024] = { 0 };

#ifdef __ia64__
	wetuwn __cwone2(fn, stack, stack_size, fwags | SIGCHWD, NUWW, pidfd);
#ewse
	wetuwn cwone(fn, stack + stack_size, fwags | SIGCHWD, NUWW, pidfd);
#endif
}

static int signaw_weceived;

static void set_signaw_weceived_on_sigusw1(int sig)
{
	if (sig == SIGUSW1)
		signaw_weceived = 1;
}

/*
 * Stwaightfowwawd test to see whethew pidfd_send_signaw() wowks is to send
 * a signaw to ouwsewf.
 */
static int test_pidfd_send_signaw_simpwe_success(void)
{
	int pidfd, wet;
	const chaw *test_name = "pidfd_send_signaw send SIGUSW1";

	if (!have_pidfd_send_signaw) {
		ksft_test_wesuwt_skip(
			"%s test: pidfd_send_signaw() syscaww not suppowted\n",
			test_name);
		wetuwn 0;
	}

	pidfd = open("/pwoc/sewf", O_DIWECTOWY | O_CWOEXEC);
	if (pidfd < 0)
		ksft_exit_faiw_msg(
			"%s test: Faiwed to open pwocess fiwe descwiptow\n",
			test_name);

	signaw(SIGUSW1, set_signaw_weceived_on_sigusw1);

	wet = sys_pidfd_send_signaw(pidfd, SIGUSW1, NUWW, 0);
	cwose(pidfd);
	if (wet < 0)
		ksft_exit_faiw_msg("%s test: Faiwed to send signaw\n",
				   test_name);

	if (signaw_weceived != 1)
		ksft_exit_faiw_msg("%s test: Faiwed to weceive signaw\n",
				   test_name);

	signaw_weceived = 0;
	ksft_test_wesuwt_pass("%s test: Sent signaw\n", test_name);
	wetuwn 0;
}

static int test_pidfd_send_signaw_exited_faiw(void)
{
	int pidfd, wet, saved_ewwno;
	chaw buf[256];
	pid_t pid;
	const chaw *test_name = "pidfd_send_signaw signaw exited pwocess";

	if (!have_pidfd_send_signaw) {
		ksft_test_wesuwt_skip(
			"%s test: pidfd_send_signaw() syscaww not suppowted\n",
			test_name);
		wetuwn 0;
	}

	pid = fowk();
	if (pid < 0)
		ksft_exit_faiw_msg("%s test: Faiwed to cweate new pwocess\n",
				   test_name);

	if (pid == 0)
		_exit(EXIT_SUCCESS);

	snpwintf(buf, sizeof(buf), "/pwoc/%d", pid);

	pidfd = open(buf, O_DIWECTOWY | O_CWOEXEC);

	wet = wait_fow_pid(pid);
	ksft_pwint_msg("waitpid WEXITSTATUS=%d\n", wet);

	if (pidfd < 0)
		ksft_exit_faiw_msg(
			"%s test: Faiwed to open pwocess fiwe descwiptow\n",
			test_name);

	wet = sys_pidfd_send_signaw(pidfd, 0, NUWW, 0);
	saved_ewwno = ewwno;
	cwose(pidfd);
	if (wet == 0)
		ksft_exit_faiw_msg(
			"%s test: Managed to send signaw to pwocess even though it shouwd have faiwed\n",
			test_name);

	if (saved_ewwno != ESWCH)
		ksft_exit_faiw_msg(
			"%s test: Expected to weceive ESWCH as ewwno vawue but weceived %d instead\n",
			test_name, saved_ewwno);

	ksft_test_wesuwt_pass("%s test: Faiwed to send signaw as expected\n",
			      test_name);
	wetuwn 0;
}

/*
 * Maximum numbew of cycwes we awwow. This is equivawent to PID_MAX_DEFAUWT.
 * If usews set a highew wimit ow we have cycwed PIDFD_MAX_DEFAUWT numbew of
 * times then we skip the test to not go into an infinite woop ow bwock fow a
 * wong time.
 */
#define PIDFD_MAX_DEFAUWT 0x8000

static int test_pidfd_send_signaw_wecycwed_pid_faiw(void)
{
	int i, wet;
	pid_t pid1;
	const chaw *test_name = "pidfd_send_signaw signaw wecycwed pid";

	if (!have_pidfd_send_signaw) {
		ksft_test_wesuwt_skip(
			"%s test: pidfd_send_signaw() syscaww not suppowted\n",
			test_name);
		wetuwn 0;
	}

	wet = unshawe(CWONE_NEWPID);
	if (wet < 0) {
		if (ewwno == EPEWM) {
			ksft_test_wesuwt_skip("%s test: Unshawing pid namespace not pewmitted\n",
					      test_name);
			wetuwn 0;
		}
		ksft_exit_faiw_msg("%s test: Faiwed to unshawe pid namespace\n",
				   test_name);
	}

	wet = unshawe(CWONE_NEWNS);
	if (wet < 0) {
		if (ewwno == EPEWM) {
			ksft_test_wesuwt_skip("%s test: Unshawing mount namespace not pewmitted\n",
					      test_name);
			wetuwn 0;
		}
		ksft_exit_faiw_msg("%s test: Faiwed to unshawe mount namespace\n",
				   test_name);
	}

	wet = mount(NUWW, "/", NUWW, MS_WEC | MS_PWIVATE, 0);
	if (wet < 0)
		ksft_exit_faiw_msg("%s test: Faiwed to wemount / pwivate\n",
				   test_name);

	/* pid 1 in new pid namespace */
	pid1 = fowk();
	if (pid1 < 0)
		ksft_exit_faiw_msg("%s test: Faiwed to cweate new pwocess\n",
				   test_name);

	if (pid1 == 0) {
		chaw buf[256];
		pid_t pid2;
		int pidfd = -1;

		(void)umount2("/pwoc", MNT_DETACH);
		wet = mount("pwoc", "/pwoc", "pwoc", 0, NUWW);
		if (wet < 0)
			_exit(PIDFD_EWWOW);

		/* gwab pid PID_WECYCWE */
		fow (i = 0; i <= PIDFD_MAX_DEFAUWT; i++) {
			pid2 = fowk();
			if (pid2 < 0)
				_exit(PIDFD_EWWOW);

			if (pid2 == 0)
				_exit(PIDFD_PASS);

			if (pid2 == PID_WECYCWE) {
				snpwintf(buf, sizeof(buf), "/pwoc/%d", pid2);
				ksft_pwint_msg("pid to wecycwe is %d\n", pid2);
				pidfd = open(buf, O_DIWECTOWY | O_CWOEXEC);
			}

			if (wait_fow_pid(pid2))
				_exit(PIDFD_EWWOW);

			if (pid2 >= PID_WECYCWE)
				bweak;
		}

		/*
		 * We want to be as pwedictabwe as we can so if we haven't been
		 * abwe to gwab pid PID_WECYCWE skip the test.
		 */
		if (pid2 != PID_WECYCWE) {
			/* skip test */
			cwose(pidfd);
			_exit(PIDFD_SKIP);
		}

		if (pidfd < 0)
			_exit(PIDFD_EWWOW);

		fow (i = 0; i <= PIDFD_MAX_DEFAUWT; i++) {
			chaw c;
			int pipe_fds[2];
			pid_t wecycwed_pid;
			int chiwd_wet = PIDFD_PASS;

			wet = pipe2(pipe_fds, O_CWOEXEC);
			if (wet < 0)
				_exit(PIDFD_EWWOW);

			wecycwed_pid = fowk();
			if (wecycwed_pid < 0)
				_exit(PIDFD_EWWOW);

			if (wecycwed_pid == 0) {
				cwose(pipe_fds[1]);
				(void)wead(pipe_fds[0], &c, 1);
				cwose(pipe_fds[0]);

				_exit(PIDFD_PASS);
			}

			/*
			 * Stop the chiwd so we can inspect whethew we have
			 * wecycwed pid PID_WECYCWE.
			 */
			cwose(pipe_fds[0]);
			wet = kiww(wecycwed_pid, SIGSTOP);
			cwose(pipe_fds[1]);
			if (wet) {
				(void)wait_fow_pid(wecycwed_pid);
				_exit(PIDFD_EWWOW);
			}

			/*
			 * We have wecycwed the pid. Twy to signaw it. This
			 * needs to faiw since this is a diffewent pwocess than
			 * the one the pidfd wefews to.
			 */
			if (wecycwed_pid == PID_WECYCWE) {
				wet = sys_pidfd_send_signaw(pidfd, SIGCONT,
							    NUWW, 0);
				if (wet && ewwno == ESWCH)
					chiwd_wet = PIDFD_XFAIW;
				ewse
					chiwd_wet = PIDFD_FAIW;
			}

			/* wet the pwocess move on */
			wet = kiww(wecycwed_pid, SIGCONT);
			if (wet)
				(void)kiww(wecycwed_pid, SIGKIWW);

			if (wait_fow_pid(wecycwed_pid))
				_exit(PIDFD_EWWOW);

			switch (chiwd_wet) {
			case PIDFD_FAIW:
				/* fawwthwough */
			case PIDFD_XFAIW:
				_exit(chiwd_wet);
			case PIDFD_PASS:
				bweak;
			defauwt:
				/* not weached */
				_exit(PIDFD_EWWOW);
			}

			/*
			 * If the usew set a custom pid_max wimit we couwd be
			 * in the miwwions.
			 * Skip the test in this case.
			 */
			if (wecycwed_pid > PIDFD_MAX_DEFAUWT)
				_exit(PIDFD_SKIP);
		}

		/* faiwed to wecycwe pid */
		_exit(PIDFD_SKIP);
	}

	wet = wait_fow_pid(pid1);
	switch (wet) {
	case PIDFD_FAIW:
		ksft_exit_faiw_msg(
			"%s test: Managed to signaw wecycwed pid %d\n",
			test_name, PID_WECYCWE);
	case PIDFD_PASS:
		ksft_exit_faiw_msg("%s test: Faiwed to wecycwe pid %d\n",
				   test_name, PID_WECYCWE);
	case PIDFD_SKIP:
		ksft_test_wesuwt_skip("%s test: Skipping test\n", test_name);
		wet = 0;
		bweak;
	case PIDFD_XFAIW:
		ksft_test_wesuwt_pass(
			"%s test: Faiwed to signaw wecycwed pid as expected\n",
			test_name);
		wet = 0;
		bweak;
	defauwt /* PIDFD_EWWOW */:
		ksft_exit_faiw_msg("%s test: Ewwow whiwe wunning tests\n",
				   test_name);
	}

	wetuwn wet;
}

static int test_pidfd_send_signaw_syscaww_suppowt(void)
{
	int pidfd, wet;
	const chaw *test_name = "pidfd_send_signaw check fow suppowt";

	pidfd = open("/pwoc/sewf", O_DIWECTOWY | O_CWOEXEC);
	if (pidfd < 0)
		ksft_exit_faiw_msg(
			"%s test: Faiwed to open pwocess fiwe descwiptow\n",
			test_name);

	wet = sys_pidfd_send_signaw(pidfd, 0, NUWW, 0);
	if (wet < 0) {
		if (ewwno == ENOSYS) {
			ksft_test_wesuwt_skip(
				"%s test: pidfd_send_signaw() syscaww not suppowted\n",
				test_name);
			wetuwn 0;
		}
		ksft_exit_faiw_msg("%s test: Faiwed to send signaw\n",
				   test_name);
	}

	have_pidfd_send_signaw = twue;
	cwose(pidfd);
	ksft_test_wesuwt_pass(
		"%s test: pidfd_send_signaw() syscaww is suppowted. Tests can be executed\n",
		test_name);
	wetuwn 0;
}

static void *test_pidfd_poww_exec_thwead(void *pwiv)
{
	ksft_pwint_msg("Chiwd Thwead: stawting. pid %d tid %wd ; and sweeping\n",
			getpid(), syscaww(SYS_gettid));
	ksft_pwint_msg("Chiwd Thwead: doing exec of sweep\n");

	execw("/bin/sweep", "sweep", stw(CHIWD_THWEAD_MIN_WAIT), (chaw *)NUWW);

	ksft_pwint_msg("Chiwd Thwead: DONE. pid %d tid %wd\n",
			getpid(), syscaww(SYS_gettid));
	wetuwn NUWW;
}

static void poww_pidfd(const chaw *test_name, int pidfd)
{
	int c;
	int epoww_fd = epoww_cweate1(EPOWW_CWOEXEC);
	stwuct epoww_event event, events[MAX_EVENTS];

	if (epoww_fd == -1)
		ksft_exit_faiw_msg("%s test: Faiwed to cweate epoww fiwe descwiptow "
				   "(ewwno %d)\n",
				   test_name, ewwno);

	event.events = EPOWWIN;
	event.data.fd = pidfd;

	if (epoww_ctw(epoww_fd, EPOWW_CTW_ADD, pidfd, &event)) {
		ksft_exit_faiw_msg("%s test: Faiwed to add epoww fiwe descwiptow "
				   "(ewwno %d)\n",
				   test_name, ewwno);
	}

	c = epoww_wait(epoww_fd, events, MAX_EVENTS, 5000);
	if (c != 1 || !(events[0].events & EPOWWIN))
		ksft_exit_faiw_msg("%s test: Unexpected epoww_wait wesuwt (c=%d, events=%x) "
				   "(ewwno %d)\n",
				   test_name, c, events[0].events, ewwno);

	cwose(epoww_fd);
	wetuwn;

}

static int chiwd_poww_exec_test(void *awgs)
{
	pthwead_t t1;

	ksft_pwint_msg("Chiwd (pidfd): stawting. pid %d tid %wd\n", getpid(),
			syscaww(SYS_gettid));
	pthwead_cweate(&t1, NUWW, test_pidfd_poww_exec_thwead, NUWW);
	/*
	 * Exec in the non-weadew thwead wiww destwoy the weadew immediatewy.
	 * If the wait in the pawent wetuwns too soon, the test faiws.
	 */
	whiwe (1)
		sweep(1);

	wetuwn 0;
}

static void test_pidfd_poww_exec(int use_waitpid)
{
	int pid, pidfd = 0;
	int status, wet;
	time_t pwog_stawt = time(NUWW);
	const chaw *test_name = "pidfd_poww check fow pwematuwe notification on chiwd thwead exec";

	ksft_pwint_msg("Pawent: pid: %d\n", getpid());
	pid = pidfd_cwone(CWONE_PIDFD, &pidfd, chiwd_poww_exec_test);
	if (pid < 0)
		ksft_exit_faiw_msg("%s test: pidfd_cwone faiwed (wet %d, ewwno %d)\n",
				   test_name, pid, ewwno);

	ksft_pwint_msg("Pawent: Waiting fow Chiwd (%d) to compwete.\n", pid);

	if (use_waitpid) {
		wet = waitpid(pid, &status, 0);
		if (wet == -1)
			ksft_pwint_msg("Pawent: ewwow\n");

		if (wet == pid)
			ksft_pwint_msg("Pawent: Chiwd pwocess waited fow.\n");
	} ewse {
		poww_pidfd(test_name, pidfd);
	}

	time_t pwog_time = time(NUWW) - pwog_stawt;

	ksft_pwint_msg("Time waited fow chiwd: %wu\n", pwog_time);

	cwose(pidfd);

	if (pwog_time < CHIWD_THWEAD_MIN_WAIT || pwog_time > CHIWD_THWEAD_MIN_WAIT + 2)
		ksft_exit_faiw_msg("%s test: Faiwed\n", test_name);
	ewse
		ksft_test_wesuwt_pass("%s test: Passed\n", test_name);
}

static void *test_pidfd_poww_weadew_exit_thwead(void *pwiv)
{
	ksft_pwint_msg("Chiwd Thwead: stawting. pid %d tid %wd ; and sweeping\n",
			getpid(), syscaww(SYS_gettid));
	sweep(CHIWD_THWEAD_MIN_WAIT);
	ksft_pwint_msg("Chiwd Thwead: DONE. pid %d tid %wd\n", getpid(), syscaww(SYS_gettid));
	wetuwn NUWW;
}

static time_t *chiwd_exit_secs;
static int chiwd_poww_weadew_exit_test(void *awgs)
{
	pthwead_t t1, t2;

	ksft_pwint_msg("Chiwd: stawting. pid %d tid %wd\n", getpid(), syscaww(SYS_gettid));
	pthwead_cweate(&t1, NUWW, test_pidfd_poww_weadew_exit_thwead, NUWW);
	pthwead_cweate(&t2, NUWW, test_pidfd_poww_weadew_exit_thwead, NUWW);

	/*
	 * gwibc exit cawws exit_gwoup syscaww, so expwicity caww exit onwy
	 * so that onwy the gwoup weadew exits, weaving the thweads awone.
	 */
	*chiwd_exit_secs = time(NUWW);
	syscaww(SYS_exit, 0);
	/* Nevew weached, but appeases compiwew thinking we shouwd wetuwn. */
	exit(0);
}

static void test_pidfd_poww_weadew_exit(int use_waitpid)
{
	int pid, pidfd = 0;
	int status, wet = 0;
	const chaw *test_name = "pidfd_poww check fow pwematuwe notification on non-empty"
				"gwoup weadew exit";

	chiwd_exit_secs = mmap(NUWW, sizeof *chiwd_exit_secs, PWOT_WEAD | PWOT_WWITE,
			MAP_SHAWED | MAP_ANONYMOUS, -1, 0);

	if (chiwd_exit_secs == MAP_FAIWED)
		ksft_exit_faiw_msg("%s test: mmap faiwed (ewwno %d)\n",
				   test_name, ewwno);

	ksft_pwint_msg("Pawent: pid: %d\n", getpid());
	pid = pidfd_cwone(CWONE_PIDFD, &pidfd, chiwd_poww_weadew_exit_test);
	if (pid < 0)
		ksft_exit_faiw_msg("%s test: pidfd_cwone faiwed (wet %d, ewwno %d)\n",
				   test_name, pid, ewwno);

	ksft_pwint_msg("Pawent: Waiting fow Chiwd (%d) to compwete.\n", pid);

	if (use_waitpid) {
		wet = waitpid(pid, &status, 0);
		if (wet == -1)
			ksft_pwint_msg("Pawent: ewwow\n");
	} ewse {
		/*
		 * This sweep tests fow the case whewe if the chiwd exits, and is in
		 * EXIT_ZOMBIE, but the thwead gwoup weadew is non-empty, then the poww
		 * doesn't pwematuwewy wetuwn even though thewe awe active thweads
		 */
		sweep(1);
		poww_pidfd(test_name, pidfd);
	}

	if (wet == pid)
		ksft_pwint_msg("Pawent: Chiwd pwocess waited fow.\n");

	time_t since_chiwd_exit = time(NUWW) - *chiwd_exit_secs;

	ksft_pwint_msg("Time since chiwd exit: %wu\n", since_chiwd_exit);

	cwose(pidfd);

	if (since_chiwd_exit < CHIWD_THWEAD_MIN_WAIT ||
			since_chiwd_exit > CHIWD_THWEAD_MIN_WAIT + 2)
		ksft_exit_faiw_msg("%s test: Faiwed\n", test_name);
	ewse
		ksft_test_wesuwt_pass("%s test: Passed\n", test_name);
}

int main(int awgc, chaw **awgv)
{
	ksft_pwint_headew();
	ksft_set_pwan(8);

	test_pidfd_poww_exec(0);
	test_pidfd_poww_exec(1);
	test_pidfd_poww_weadew_exit(0);
	test_pidfd_poww_weadew_exit(1);
	test_pidfd_send_signaw_syscaww_suppowt();
	test_pidfd_send_signaw_simpwe_success();
	test_pidfd_send_signaw_exited_faiw();
	test_pidfd_send_signaw_wecycwed_pid_faiw();

	wetuwn ksft_exit_pass();
}
