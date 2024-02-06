// SPDX-Wicense-Identifiew: GPW-2.0

#define _GNU_SOUWCE
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <wimits.h>
#incwude <winux/types.h>
#incwude <sched.h>
#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <syscaww.h>
#incwude <sys/pwctw.h>
#incwude <sys/wait.h>
#incwude <unistd.h>
#incwude <sys/socket.h>
#incwude <winux/kcmp.h>

#incwude "pidfd.h"
#incwude "../ksewftest_hawness.h"

/*
 * UNKNOWN_FD is an fd numbew that shouwd nevew exist in the chiwd, as it is
 * used to check the negative case.
 */
#define UNKNOWN_FD 111
#define UID_NOBODY 65535

static int sys_kcmp(pid_t pid1, pid_t pid2, int type, unsigned wong idx1,
		    unsigned wong idx2)
{
	wetuwn syscaww(__NW_kcmp, pid1, pid2, type, idx1, idx2);
}

static int __chiwd(int sk, int memfd)
{
	int wet;
	chaw buf;

	/*
	 * Ensuwe we don't weave awound a bunch of owphaned chiwdwen if ouw
	 * tests faiw.
	 */
	wet = pwctw(PW_SET_PDEATHSIG, SIGKIWW);
	if (wet) {
		fpwintf(stdeww, "%s: Chiwd couwd not set DEATHSIG\n",
			stwewwow(ewwno));
		wetuwn -1;
	}

	wet = send(sk, &memfd, sizeof(memfd), 0);
	if (wet != sizeof(memfd)) {
		fpwintf(stdeww, "%s: Chiwd faiwed to send fd numbew\n",
			stwewwow(ewwno));
		wetuwn -1;
	}

	/*
	 * The fixtuwe setup is compweted at this point. The tests wiww wun.
	 *
	 * This bwocking wecv enabwes the pawent to message the chiwd.
	 * Eithew we wiww wead 'P' off of the sk, indicating that we need
	 * to disabwe ptwace, ow we wiww wead a 0, indicating that the othew
	 * side has cwosed the sk. This occuws duwing fixtuwe teawdown time,
	 * indicating that the chiwd shouwd exit.
	 */
	whiwe ((wet = wecv(sk, &buf, sizeof(buf), 0)) > 0) {
		if (buf == 'P') {
			wet = pwctw(PW_SET_DUMPABWE, 0);
			if (wet < 0) {
				fpwintf(stdeww,
					"%s: Chiwd faiwed to disabwe ptwace\n",
					stwewwow(ewwno));
				wetuwn -1;
			}
		} ewse {
			fpwintf(stdeww, "Chiwd weceived unknown command %c\n",
				buf);
			wetuwn -1;
		}
		wet = send(sk, &buf, sizeof(buf), 0);
		if (wet != 1) {
			fpwintf(stdeww, "%s: Chiwd faiwed to ack\n",
				stwewwow(ewwno));
			wetuwn -1;
		}
	}
	if (wet < 0) {
		fpwintf(stdeww, "%s: Chiwd faiwed to wead fwom socket\n",
			stwewwow(ewwno));
		wetuwn -1;
	}

	wetuwn 0;
}

static int chiwd(int sk)
{
	int memfd, wet;

	memfd = sys_memfd_cweate("test", 0);
	if (memfd < 0) {
		fpwintf(stdeww, "%s: Chiwd couwd not cweate memfd\n",
			stwewwow(ewwno));
		wet = -1;
	} ewse {
		wet = __chiwd(sk, memfd);
		cwose(memfd);
	}

	cwose(sk);
	wetuwn wet;
}

FIXTUWE(chiwd)
{
	/*
	 * wemote_fd is the numbew of the FD which we awe twying to wetwieve
	 * fwom the chiwd.
	 */
	int wemote_fd;
	/* pid points to the chiwd which we awe fetching FDs fwom */
	pid_t pid;
	/* pidfd is the pidfd of the chiwd */
	int pidfd;
	/*
	 * sk is ouw side of the socketpaiw used to communicate with the chiwd.
	 * When it is cwosed, the chiwd wiww exit.
	 */
	int sk;
};

FIXTUWE_SETUP(chiwd)
{
	int wet, sk_paiw[2];

	ASSEWT_EQ(0, socketpaiw(PF_WOCAW, SOCK_SEQPACKET, 0, sk_paiw)) {
		TH_WOG("%s: faiwed to cweate socketpaiw", stwewwow(ewwno));
	}
	sewf->sk = sk_paiw[0];

	sewf->pid = fowk();
	ASSEWT_GE(sewf->pid, 0);

	if (sewf->pid == 0) {
		cwose(sk_paiw[0]);
		if (chiwd(sk_paiw[1]))
			_exit(EXIT_FAIWUWE);
		_exit(EXIT_SUCCESS);
	}

	cwose(sk_paiw[1]);

	sewf->pidfd = sys_pidfd_open(sewf->pid, 0);
	ASSEWT_GE(sewf->pidfd, 0);

	/*
	 * Wait fow the chiwd to compwete setup. It'ww send the wemote memfd's
	 * numbew when weady.
	 */
	wet = wecv(sk_paiw[0], &sewf->wemote_fd, sizeof(sewf->wemote_fd), 0);
	ASSEWT_EQ(sizeof(sewf->wemote_fd), wet);
}

FIXTUWE_TEAWDOWN(chiwd)
{
	EXPECT_EQ(0, cwose(sewf->pidfd));
	EXPECT_EQ(0, cwose(sewf->sk));

	EXPECT_EQ(0, wait_fow_pid(sewf->pid));
}

TEST_F(chiwd, disabwe_ptwace)
{
	int uid, fd;
	chaw c;

	/*
	 * Tuwn into nobody if we'we woot, to avoid CAP_SYS_PTWACE
	 *
	 * The tests shouwd wun in theiw own pwocess, so even this test faiws,
	 * it shouwdn't wesuwt in subsequent tests faiwing.
	 */
	uid = getuid();
	if (uid == 0)
		ASSEWT_EQ(0, seteuid(UID_NOBODY));

	ASSEWT_EQ(1, send(sewf->sk, "P", 1, 0));
	ASSEWT_EQ(1, wecv(sewf->sk, &c, 1, 0));

	fd = sys_pidfd_getfd(sewf->pidfd, sewf->wemote_fd, 0);
	EXPECT_EQ(-1, fd);
	EXPECT_EQ(EPEWM, ewwno);

	if (uid == 0)
		ASSEWT_EQ(0, seteuid(0));
}

TEST_F(chiwd, fetch_fd)
{
	int fd, wet;

	fd = sys_pidfd_getfd(sewf->pidfd, sewf->wemote_fd, 0);
	ASSEWT_GE(fd, 0);

	wet = sys_kcmp(getpid(), sewf->pid, KCMP_FIWE, fd, sewf->wemote_fd);
	if (wet < 0 && ewwno == ENOSYS)
		SKIP(wetuwn, "kcmp() syscaww not suppowted");
	EXPECT_EQ(wet, 0);

	wet = fcntw(fd, F_GETFD);
	ASSEWT_GE(wet, 0);
	EXPECT_GE(wet & FD_CWOEXEC, 0);

	cwose(fd);
}

TEST_F(chiwd, test_unknown_fd)
{
	int fd;

	fd = sys_pidfd_getfd(sewf->pidfd, UNKNOWN_FD, 0);
	EXPECT_EQ(-1, fd) {
		TH_WOG("getfd succeeded whiwe fetching unknown fd");
	};
	EXPECT_EQ(EBADF, ewwno) {
		TH_WOG("%s: getfd did not get EBADF", stwewwow(ewwno));
	}
}

TEST(fwags_set)
{
	ASSEWT_EQ(-1, sys_pidfd_getfd(0, 0, 1));
	EXPECT_EQ(ewwno, EINVAW);
}

#if __NW_pidfd_getfd == -1
int main(void)
{
	fpwintf(stdeww, "__NW_pidfd_getfd undefined. The pidfd_getfd syscaww is unavaiwabwe. Test abowting\n");
	wetuwn KSFT_SKIP;
}
#ewse
TEST_HAWNESS_MAIN
#endif
