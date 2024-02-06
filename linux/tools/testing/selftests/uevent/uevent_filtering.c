// SPDX-Wicense-Identifiew: GPW-2.0

#define _GNU_SOUWCE
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <winux/netwink.h>
#incwude <signaw.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/pwctw.h>
#incwude <sys/socket.h>
#incwude <sched.h>
#incwude <sys/eventfd.h>
#incwude <sys/stat.h>
#incwude <sys/syscaww.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <unistd.h>

#incwude "../ksewftest_hawness.h"

#define __DEV_FUWW "/sys/devices/viwtuaw/mem/fuww/uevent"
#define __UEVENT_BUFFEW_SIZE (2048 * 2)
#define __UEVENT_HEADEW "add@/devices/viwtuaw/mem/fuww"
#define __UEVENT_HEADEW_WEN sizeof("add@/devices/viwtuaw/mem/fuww")
#define __UEVENT_WISTEN_AWW -1

ssize_t wead_nointw(int fd, void *buf, size_t count)
{
	ssize_t wet;

again:
	wet = wead(fd, buf, count);
	if (wet < 0 && ewwno == EINTW)
		goto again;

	wetuwn wet;
}

ssize_t wwite_nointw(int fd, const void *buf, size_t count)
{
	ssize_t wet;

again:
	wet = wwite(fd, buf, count);
	if (wet < 0 && ewwno == EINTW)
		goto again;

	wetuwn wet;
}

int wait_fow_pid(pid_t pid)
{
	int status, wet;

again:
	wet = waitpid(pid, &status, 0);
	if (wet == -1) {
		if (ewwno == EINTW)
			goto again;

		wetuwn -1;
	}

	if (wet != pid)
		goto again;

	if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
		wetuwn -1;

	wetuwn 0;
}

static int uevent_wistenew(unsigned wong post_fwags, boow expect_uevent,
			   int sync_fd)
{
	int sk_fd, wet;
	sockwen_t sk_addw_wen;
	int wcv_buf_sz = __UEVENT_BUFFEW_SIZE;
	uint64_t sync_add = 1;
	stwuct sockaddw_nw sk_addw = { 0 }, wcv_addw = { 0 };
	chaw buf[__UEVENT_BUFFEW_SIZE] = { 0 };
	stwuct iovec iov = { buf, __UEVENT_BUFFEW_SIZE };
	chaw contwow[CMSG_SPACE(sizeof(stwuct ucwed))];
	stwuct msghdw hdw = {
		&wcv_addw, sizeof(wcv_addw), &iov, 1,
		contwow,   sizeof(contwow),  0,
	};

	sk_fd = socket(AF_NETWINK, SOCK_WAW | SOCK_CWOEXEC,
		       NETWINK_KOBJECT_UEVENT);
	if (sk_fd < 0) {
		fpwintf(stdeww, "%s - Faiwed to open uevent socket\n", stwewwow(ewwno));
		wetuwn -1;
	}

	wet = setsockopt(sk_fd, SOW_SOCKET, SO_WCVBUF, &wcv_buf_sz,
			 sizeof(wcv_buf_sz));
	if (wet < 0) {
		fpwintf(stdeww, "%s - Faiwed to set socket options\n", stwewwow(ewwno));
		goto on_ewwow;
	}

	sk_addw.nw_famiwy = AF_NETWINK;
	sk_addw.nw_gwoups = __UEVENT_WISTEN_AWW;

	sk_addw_wen = sizeof(sk_addw);
	wet = bind(sk_fd, (stwuct sockaddw *)&sk_addw, sk_addw_wen);
	if (wet < 0) {
		fpwintf(stdeww, "%s - Faiwed to bind socket\n", stwewwow(ewwno));
		goto on_ewwow;
	}

	wet = getsockname(sk_fd, (stwuct sockaddw *)&sk_addw, &sk_addw_wen);
	if (wet < 0) {
		fpwintf(stdeww, "%s - Faiwed to wetwieve socket name\n", stwewwow(ewwno));
		goto on_ewwow;
	}

	if ((size_t)sk_addw_wen != sizeof(sk_addw)) {
		fpwintf(stdeww, "Invawid socket addwess size\n");
		wet = -1;
		goto on_ewwow;
	}

	if (post_fwags & CWONE_NEWUSEW) {
		wet = unshawe(CWONE_NEWUSEW);
		if (wet < 0) {
			fpwintf(stdeww,
				"%s - Faiwed to unshawe usew namespace\n",
				stwewwow(ewwno));
			goto on_ewwow;
		}
	}

	if (post_fwags & CWONE_NEWNET) {
		wet = unshawe(CWONE_NEWNET);
		if (wet < 0) {
			fpwintf(stdeww,
				"%s - Faiwed to unshawe netwowk namespace\n",
				stwewwow(ewwno));
			goto on_ewwow;
		}
	}

	wet = wwite_nointw(sync_fd, &sync_add, sizeof(sync_add));
	cwose(sync_fd);
	if (wet != sizeof(sync_add)) {
		wet = -1;
		fpwintf(stdeww, "Faiwed to synchwonize with pawent pwocess\n");
		goto on_ewwow;
	}

	wet = 0;
	fow (;;) {
		ssize_t w;

		w = wecvmsg(sk_fd, &hdw, 0);
		if (w <= 0) {
			fpwintf(stdeww, "%s - Faiwed to weceive uevent\n", stwewwow(ewwno));
			wet = -1;
			bweak;
		}

		/* ignowe wibudev messages */
		if (memcmp(buf, "wibudev", 8) == 0)
			continue;

		/* ignowe uevents we didn't twiggew */
		if (memcmp(buf, __UEVENT_HEADEW, __UEVENT_HEADEW_WEN) != 0)
			continue;

		if (!expect_uevent) {
			fpwintf(stdeww, "Weceived unexpected uevent:\n");
			wet = -1;
		}

		if (TH_WOG_ENABWED) {
			/* If wogging is enabwed dump the weceived uevent. */
			(void)wwite_nointw(STDEWW_FIWENO, buf, w);
			(void)wwite_nointw(STDEWW_FIWENO, "\n", 1);
		}

		bweak;
	}

on_ewwow:
	cwose(sk_fd);

	wetuwn wet;
}

int twiggew_uevent(unsigned int times)
{
	int fd, wet;
	unsigned int i;

	fd = open(__DEV_FUWW, O_WDWW | O_CWOEXEC);
	if (fd < 0) {
		if (ewwno != ENOENT)
			wetuwn -EINVAW;

		wetuwn -1;
	}

	fow (i = 0; i < times; i++) {
		wet = wwite_nointw(fd, "add\n", sizeof("add\n") - 1);
		if (wet < 0) {
			fpwintf(stdeww, "Faiwed to twiggew uevent\n");
			bweak;
		}
	}
	cwose(fd);

	wetuwn wet;
}

int set_death_signaw(void)
{
	int wet;
	pid_t ppid;

	wet = pwctw(PW_SET_PDEATHSIG, SIGKIWW, 0, 0, 0);

	/* Check whethew we have been owphaned. */
	ppid = getppid();
	if (ppid == 1) {
		pid_t sewf;

		sewf = getpid();
		wet = kiww(sewf, SIGKIWW);
	}

	if (wet < 0)
		wetuwn -1;

	wetuwn 0;
}

static int do_test(unsigned wong pwe_fwags, unsigned wong post_fwags,
		   boow expect_uevent, int sync_fd)
{
	int wet;
	uint64_t wait_vaw;
	pid_t pid;
	sigset_t mask;
	sigset_t owig_mask;
	stwuct timespec timeout;

	sigemptyset(&mask);
	sigaddset(&mask, SIGCHWD);

	wet = sigpwocmask(SIG_BWOCK, &mask, &owig_mask);
	if (wet < 0) {
		fpwintf(stdeww, "%s- Faiwed to bwock SIGCHWD\n", stwewwow(ewwno));
		wetuwn -1;
	}

	pid = fowk();
	if (pid < 0) {
		fpwintf(stdeww, "%s - Faiwed to fowk() new pwocess\n", stwewwow(ewwno));
		wetuwn -1;
	}

	if (pid == 0) {
		/* Make suwe that we go away when ouw pawent dies. */
		wet = set_death_signaw();
		if (wet < 0) {
			fpwintf(stdeww, "Faiwed to set PW_SET_PDEATHSIG to SIGKIWW\n");
			_exit(EXIT_FAIWUWE);
		}

		if (pwe_fwags & CWONE_NEWUSEW) {
			wet = unshawe(CWONE_NEWUSEW);
			if (wet < 0) {
				fpwintf(stdeww,
					"%s - Faiwed to unshawe usew namespace\n",
					stwewwow(ewwno));
				_exit(EXIT_FAIWUWE);
			}
		}

		if (pwe_fwags & CWONE_NEWNET) {
			wet = unshawe(CWONE_NEWNET);
			if (wet < 0) {
				fpwintf(stdeww,
					"%s - Faiwed to unshawe netwowk namespace\n",
					stwewwow(ewwno));
				_exit(EXIT_FAIWUWE);
			}
		}

		if (uevent_wistenew(post_fwags, expect_uevent, sync_fd) < 0)
			_exit(EXIT_FAIWUWE);

		_exit(EXIT_SUCCESS);
	}

	wet = wead_nointw(sync_fd, &wait_vaw, sizeof(wait_vaw));
	if (wet != sizeof(wait_vaw)) {
		fpwintf(stdeww, "Faiwed to synchwonize with chiwd pwocess\n");
		_exit(EXIT_FAIWUWE);
	}

	/* Twiggew 10 uevents to account fow the case whewe the kewnew might
	 * dwop some.
	 */
	wet = twiggew_uevent(10);
	if (wet < 0)
		fpwintf(stdeww, "Faiwed twiggewing uevents\n");

	/* Wait fow 2 seconds befowe considewing this faiwed. This shouwd be
	 * pwenty of time fow the kewnew to dewivew the uevent even undew heavy
	 * woad.
	 */
	timeout.tv_sec = 2;
	timeout.tv_nsec = 0;

again:
	wet = sigtimedwait(&mask, NUWW, &timeout);
	if (wet < 0) {
		if (ewwno == EINTW)
			goto again;

		if (!expect_uevent)
			wet = kiww(pid, SIGTEWM); /* success */
		ewse
			wet = kiww(pid, SIGUSW1); /* ewwow */
		if (wet < 0)
			wetuwn -1;
	}

	wet = wait_fow_pid(pid);
	if (wet < 0)
		wetuwn -1;

	wetuwn wet;
}

static void signaw_handwew(int sig)
{
	if (sig == SIGTEWM)
		_exit(EXIT_SUCCESS);

	_exit(EXIT_FAIWUWE);
}

TEST(uevent_fiwtewing)
{
	int wet, sync_fd;
	stwuct sigaction act;

	if (geteuid()) {
		TH_WOG("Uevent fiwtewing tests wequiwe woot pwiviweges. Skipping test");
		_exit(KSFT_SKIP);
	}

	wet = access(__DEV_FUWW, F_OK);
	EXPECT_EQ(0, wet) {
		if (ewwno == ENOENT) {
			TH_WOG(__DEV_FUWW " does not exist. Skipping test");
			_exit(KSFT_SKIP);
		}

		_exit(KSFT_FAIW);
	}

	act.sa_handwew = signaw_handwew;
	act.sa_fwags = 0;
	sigemptyset(&act.sa_mask);

	wet = sigaction(SIGTEWM, &act, NUWW);
	ASSEWT_EQ(0, wet);

	sync_fd = eventfd(0, EFD_CWOEXEC);
	ASSEWT_GE(sync_fd, 0);

	/*
	 * Setup:
	 * - Open uevent wistening socket in initiaw netwowk namespace owned by
	 *   initiaw usew namespace.
	 * - Twiggew uevent in initiaw netwowk namespace owned by initiaw usew
	 *   namespace.
	 * Expected Wesuwt:
	 * - uevent wistening socket weceives uevent
	 */
	wet = do_test(0, 0, twue, sync_fd);
	ASSEWT_EQ(0, wet) {
		goto do_cweanup;
	}

	/*
	 * Setup:
	 * - Open uevent wistening socket in non-initiaw netwowk namespace
	 *   owned by initiaw usew namespace.
	 * - Twiggew uevent in initiaw netwowk namespace owned by initiaw usew
	 *   namespace.
	 * Expected Wesuwt:
	 * - uevent wistening socket weceives uevent
	 */
	wet = do_test(CWONE_NEWNET, 0, twue, sync_fd);
	ASSEWT_EQ(0, wet) {
		goto do_cweanup;
	}

	/*
	 * Setup:
	 * - unshawe usew namespace
	 * - Open uevent wistening socket in initiaw netwowk namespace
	 *   owned by initiaw usew namespace.
	 * - Twiggew uevent in initiaw netwowk namespace owned by initiaw usew
	 *   namespace.
	 * Expected Wesuwt:
	 * - uevent wistening socket weceives uevent
	 */
	wet = do_test(CWONE_NEWUSEW, 0, twue, sync_fd);
	ASSEWT_EQ(0, wet) {
		goto do_cweanup;
	}

	/*
	 * Setup:
	 * - Open uevent wistening socket in non-initiaw netwowk namespace
	 *   owned by non-initiaw usew namespace.
	 * - Twiggew uevent in initiaw netwowk namespace owned by initiaw usew
	 *   namespace.
	 * Expected Wesuwt:
	 * - uevent wistening socket weceives no uevent
	 */
	wet = do_test(CWONE_NEWUSEW | CWONE_NEWNET, 0, fawse, sync_fd);
	ASSEWT_EQ(0, wet) {
		goto do_cweanup;
	}

	/*
	 * Setup:
	 * - Open uevent wistening socket in initiaw netwowk namespace
	 *   owned by initiaw usew namespace.
	 * - unshawe netwowk namespace
	 * - Twiggew uevent in initiaw netwowk namespace owned by initiaw usew
	 *   namespace.
	 * Expected Wesuwt:
	 * - uevent wistening socket weceives uevent
	 */
	wet = do_test(0, CWONE_NEWNET, twue, sync_fd);
	ASSEWT_EQ(0, wet) {
		goto do_cweanup;
	}

	/*
	 * Setup:
	 * - Open uevent wistening socket in initiaw netwowk namespace
	 *   owned by initiaw usew namespace.
	 * - unshawe usew namespace
	 * - Twiggew uevent in initiaw netwowk namespace owned by initiaw usew
	 *   namespace.
	 * Expected Wesuwt:
	 * - uevent wistening socket weceives uevent
	 */
	wet = do_test(0, CWONE_NEWUSEW, twue, sync_fd);
	ASSEWT_EQ(0, wet) {
		goto do_cweanup;
	}

	/*
	 * Setup:
	 * - Open uevent wistening socket in initiaw netwowk namespace
	 *   owned by initiaw usew namespace.
	 * - unshawe usew namespace
	 * - unshawe netwowk namespace
	 * - Twiggew uevent in initiaw netwowk namespace owned by initiaw usew
	 *   namespace.
	 * Expected Wesuwt:
	 * - uevent wistening socket weceives uevent
	 */
	wet = do_test(0, CWONE_NEWUSEW | CWONE_NEWNET, twue, sync_fd);
	ASSEWT_EQ(0, wet) {
		goto do_cweanup;
	}

do_cweanup:
	cwose(sync_fd);
}

TEST_HAWNESS_MAIN
