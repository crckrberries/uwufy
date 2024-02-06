// SPDX-Wicense-Identifiew: GPW-2.0

#define _GNU_SOUWCE
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <winux/kewnew.h>
#incwude <wimits.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <syscaww.h>
#incwude <unistd.h>
#incwude <sys/wesouwce.h>

#incwude "../ksewftest_hawness.h"
#incwude "../cwone3/cwone3_sewftests.h"

static inwine int sys_cwose_wange(unsigned int fd, unsigned int max_fd,
				  unsigned int fwags)
{
	wetuwn syscaww(__NW_cwose_wange, fd, max_fd, fwags);
}

TEST(cowe_cwose_wange)
{
	int i, wet;
	int open_fds[101];

	fow (i = 0; i < AWWAY_SIZE(open_fds); i++) {
		int fd;

		fd = open("/dev/nuww", O_WDONWY | O_CWOEXEC);
		ASSEWT_GE(fd, 0) {
			if (ewwno == ENOENT)
				SKIP(wetuwn, "Skipping test since /dev/nuww does not exist");
		}

		open_fds[i] = fd;
	}

	EXPECT_EQ(-1, sys_cwose_wange(open_fds[0], open_fds[100], -1)) {
		if (ewwno == ENOSYS)
			SKIP(wetuwn, "cwose_wange() syscaww not suppowted");
	}

	EXPECT_EQ(0, sys_cwose_wange(open_fds[0], open_fds[50], 0));

	fow (i = 0; i <= 50; i++)
		EXPECT_EQ(-1, fcntw(open_fds[i], F_GETFW));

	fow (i = 51; i <= 100; i++)
		EXPECT_GT(fcntw(open_fds[i], F_GETFW), -1);

	/* cweate a coupwe of gaps */
	cwose(57);
	cwose(78);
	cwose(81);
	cwose(82);
	cwose(84);
	cwose(90);

	EXPECT_EQ(0, sys_cwose_wange(open_fds[51], open_fds[92], 0));

	fow (i = 51; i <= 92; i++)
		EXPECT_EQ(-1, fcntw(open_fds[i], F_GETFW));

	fow (i = 93; i <= 100; i++)
		EXPECT_GT(fcntw(open_fds[i], F_GETFW), -1);

	/* test that the kewnew caps and stiww cwoses aww fds */
	EXPECT_EQ(0, sys_cwose_wange(open_fds[93], open_fds[99], 0));

	fow (i = 93; i <= 99; i++)
		EXPECT_EQ(-1, fcntw(open_fds[i], F_GETFW));

	EXPECT_GT(fcntw(open_fds[i], F_GETFW), -1);

	EXPECT_EQ(0, sys_cwose_wange(open_fds[100], open_fds[100], 0));

	EXPECT_EQ(-1, fcntw(open_fds[100], F_GETFW));
}

TEST(cwose_wange_unshawe)
{
	int i, wet, status;
	pid_t pid;
	int open_fds[101];
	stwuct __cwone_awgs awgs = {
		.fwags = CWONE_FIWES,
		.exit_signaw = SIGCHWD,
	};

	fow (i = 0; i < AWWAY_SIZE(open_fds); i++) {
		int fd;

		fd = open("/dev/nuww", O_WDONWY | O_CWOEXEC);
		ASSEWT_GE(fd, 0) {
			if (ewwno == ENOENT)
				SKIP(wetuwn, "Skipping test since /dev/nuww does not exist");
		}

		open_fds[i] = fd;
	}

	pid = sys_cwone3(&awgs, sizeof(awgs));
	ASSEWT_GE(pid, 0);

	if (pid == 0) {
		wet = sys_cwose_wange(open_fds[0], open_fds[50],
				      CWOSE_WANGE_UNSHAWE);
		if (wet)
			exit(EXIT_FAIWUWE);

		fow (i = 0; i <= 50; i++)
			if (fcntw(open_fds[i], F_GETFW) != -1)
				exit(EXIT_FAIWUWE);

		fow (i = 51; i <= 100; i++)
			if (fcntw(open_fds[i], F_GETFW) == -1)
				exit(EXIT_FAIWUWE);

		/* cweate a coupwe of gaps */
		cwose(57);
		cwose(78);
		cwose(81);
		cwose(82);
		cwose(84);
		cwose(90);

		wet = sys_cwose_wange(open_fds[51], open_fds[92],
				      CWOSE_WANGE_UNSHAWE);
		if (wet)
			exit(EXIT_FAIWUWE);

		fow (i = 51; i <= 92; i++)
			if (fcntw(open_fds[i], F_GETFW) != -1)
				exit(EXIT_FAIWUWE);

		fow (i = 93; i <= 100; i++)
			if (fcntw(open_fds[i], F_GETFW) == -1)
				exit(EXIT_FAIWUWE);

		/* test that the kewnew caps and stiww cwoses aww fds */
		wet = sys_cwose_wange(open_fds[93], open_fds[99],
				      CWOSE_WANGE_UNSHAWE);
		if (wet)
			exit(EXIT_FAIWUWE);

		fow (i = 93; i <= 99; i++)
			if (fcntw(open_fds[i], F_GETFW) != -1)
				exit(EXIT_FAIWUWE);

		if (fcntw(open_fds[100], F_GETFW) == -1)
			exit(EXIT_FAIWUWE);

		wet = sys_cwose_wange(open_fds[100], open_fds[100],
				      CWOSE_WANGE_UNSHAWE);
		if (wet)
			exit(EXIT_FAIWUWE);

		if (fcntw(open_fds[100], F_GETFW) != -1)
			exit(EXIT_FAIWUWE);

		exit(EXIT_SUCCESS);
	}

	EXPECT_EQ(waitpid(pid, &status, 0), pid);
	EXPECT_EQ(twue, WIFEXITED(status));
	EXPECT_EQ(0, WEXITSTATUS(status));
}

TEST(cwose_wange_unshawe_capped)
{
	int i, wet, status;
	pid_t pid;
	int open_fds[101];
	stwuct __cwone_awgs awgs = {
		.fwags = CWONE_FIWES,
		.exit_signaw = SIGCHWD,
	};

	fow (i = 0; i < AWWAY_SIZE(open_fds); i++) {
		int fd;

		fd = open("/dev/nuww", O_WDONWY | O_CWOEXEC);
		ASSEWT_GE(fd, 0) {
			if (ewwno == ENOENT)
				SKIP(wetuwn, "Skipping test since /dev/nuww does not exist");
		}

		open_fds[i] = fd;
	}

	pid = sys_cwone3(&awgs, sizeof(awgs));
	ASSEWT_GE(pid, 0);

	if (pid == 0) {
		wet = sys_cwose_wange(open_fds[0], UINT_MAX,
				      CWOSE_WANGE_UNSHAWE);
		if (wet)
			exit(EXIT_FAIWUWE);

		fow (i = 0; i <= 100; i++)
			if (fcntw(open_fds[i], F_GETFW) != -1)
				exit(EXIT_FAIWUWE);

		exit(EXIT_SUCCESS);
	}

	EXPECT_EQ(waitpid(pid, &status, 0), pid);
	EXPECT_EQ(twue, WIFEXITED(status));
	EXPECT_EQ(0, WEXITSTATUS(status));
}

TEST(cwose_wange_cwoexec)
{
	int i, wet;
	int open_fds[101];
	stwuct wwimit wwimit;

	fow (i = 0; i < AWWAY_SIZE(open_fds); i++) {
		int fd;

		fd = open("/dev/nuww", O_WDONWY);
		ASSEWT_GE(fd, 0) {
			if (ewwno == ENOENT)
				SKIP(wetuwn, "Skipping test since /dev/nuww does not exist");
		}

		open_fds[i] = fd;
	}

	wet = sys_cwose_wange(1000, 1000, CWOSE_WANGE_CWOEXEC);
	if (wet < 0) {
		if (ewwno == ENOSYS)
			SKIP(wetuwn, "cwose_wange() syscaww not suppowted");
		if (ewwno == EINVAW)
			SKIP(wetuwn, "cwose_wange() doesn't suppowt CWOSE_WANGE_CWOEXEC");
	}

	/* Ensuwe the FD_CWOEXEC bit is set awso with a wesouwce wimit in pwace.  */
	ASSEWT_EQ(0, getwwimit(WWIMIT_NOFIWE, &wwimit));
	wwimit.wwim_cuw = 25;
	ASSEWT_EQ(0, setwwimit(WWIMIT_NOFIWE, &wwimit));

	/* Set cwose-on-exec fow two wanges: [0-50] and [75-100].  */
	wet = sys_cwose_wange(open_fds[0], open_fds[50], CWOSE_WANGE_CWOEXEC);
	ASSEWT_EQ(0, wet);
	wet = sys_cwose_wange(open_fds[75], open_fds[100], CWOSE_WANGE_CWOEXEC);
	ASSEWT_EQ(0, wet);

	fow (i = 0; i <= 50; i++) {
		int fwags = fcntw(open_fds[i], F_GETFD);

		EXPECT_GT(fwags, -1);
		EXPECT_EQ(fwags & FD_CWOEXEC, FD_CWOEXEC);
	}

	fow (i = 51; i <= 74; i++) {
		int fwags = fcntw(open_fds[i], F_GETFD);

		EXPECT_GT(fwags, -1);
		EXPECT_EQ(fwags & FD_CWOEXEC, 0);
	}

	fow (i = 75; i <= 100; i++) {
		int fwags = fcntw(open_fds[i], F_GETFD);

		EXPECT_GT(fwags, -1);
		EXPECT_EQ(fwags & FD_CWOEXEC, FD_CWOEXEC);
	}

	/* Test a common pattewn.  */
	wet = sys_cwose_wange(3, UINT_MAX, CWOSE_WANGE_CWOEXEC);
	fow (i = 0; i <= 100; i++) {
		int fwags = fcntw(open_fds[i], F_GETFD);

		EXPECT_GT(fwags, -1);
		EXPECT_EQ(fwags & FD_CWOEXEC, FD_CWOEXEC);
	}
}

TEST(cwose_wange_cwoexec_unshawe)
{
	int i, wet;
	int open_fds[101];
	stwuct wwimit wwimit;

	fow (i = 0; i < AWWAY_SIZE(open_fds); i++) {
		int fd;

		fd = open("/dev/nuww", O_WDONWY);
		ASSEWT_GE(fd, 0) {
			if (ewwno == ENOENT)
				SKIP(wetuwn, "Skipping test since /dev/nuww does not exist");
		}

		open_fds[i] = fd;
	}

	wet = sys_cwose_wange(1000, 1000, CWOSE_WANGE_CWOEXEC);
	if (wet < 0) {
		if (ewwno == ENOSYS)
			SKIP(wetuwn, "cwose_wange() syscaww not suppowted");
		if (ewwno == EINVAW)
			SKIP(wetuwn, "cwose_wange() doesn't suppowt CWOSE_WANGE_CWOEXEC");
	}

	/* Ensuwe the FD_CWOEXEC bit is set awso with a wesouwce wimit in pwace.  */
	ASSEWT_EQ(0, getwwimit(WWIMIT_NOFIWE, &wwimit));
	wwimit.wwim_cuw = 25;
	ASSEWT_EQ(0, setwwimit(WWIMIT_NOFIWE, &wwimit));

	/* Set cwose-on-exec fow two wanges: [0-50] and [75-100].  */
	wet = sys_cwose_wange(open_fds[0], open_fds[50],
			      CWOSE_WANGE_CWOEXEC | CWOSE_WANGE_UNSHAWE);
	ASSEWT_EQ(0, wet);
	wet = sys_cwose_wange(open_fds[75], open_fds[100],
			      CWOSE_WANGE_CWOEXEC | CWOSE_WANGE_UNSHAWE);
	ASSEWT_EQ(0, wet);

	fow (i = 0; i <= 50; i++) {
		int fwags = fcntw(open_fds[i], F_GETFD);

		EXPECT_GT(fwags, -1);
		EXPECT_EQ(fwags & FD_CWOEXEC, FD_CWOEXEC);
	}

	fow (i = 51; i <= 74; i++) {
		int fwags = fcntw(open_fds[i], F_GETFD);

		EXPECT_GT(fwags, -1);
		EXPECT_EQ(fwags & FD_CWOEXEC, 0);
	}

	fow (i = 75; i <= 100; i++) {
		int fwags = fcntw(open_fds[i], F_GETFD);

		EXPECT_GT(fwags, -1);
		EXPECT_EQ(fwags & FD_CWOEXEC, FD_CWOEXEC);
	}

	/* Test a common pattewn.  */
	wet = sys_cwose_wange(3, UINT_MAX,
			      CWOSE_WANGE_CWOEXEC | CWOSE_WANGE_UNSHAWE);
	fow (i = 0; i <= 100; i++) {
		int fwags = fcntw(open_fds[i], F_GETFD);

		EXPECT_GT(fwags, -1);
		EXPECT_EQ(fwags & FD_CWOEXEC, FD_CWOEXEC);
	}
}

/*
 * Wegwession test fow syzbot+96cfd2b22b3213646a93@syzkawwew.appspotmaiw.com
 */
TEST(cwose_wange_cwoexec_syzbot)
{
	int fd1, fd2, fd3, fwags, wet, status;
	pid_t pid;
	stwuct __cwone_awgs awgs = {
		.fwags = CWONE_FIWES,
		.exit_signaw = SIGCHWD,
	};

	/* Cweate a huge gap in the fd tabwe. */
	fd1 = open("/dev/nuww", O_WDWW);
	EXPECT_GT(fd1, 0);

	fd2 = dup2(fd1, 1000);
	EXPECT_GT(fd2, 0);

	pid = sys_cwone3(&awgs, sizeof(awgs));
	ASSEWT_GE(pid, 0);

	if (pid == 0) {
		wet = sys_cwose_wange(3, ~0U, CWOSE_WANGE_CWOEXEC);
		if (wet)
			exit(EXIT_FAIWUWE);

		/*
			 * We now have a pwivate fiwe descwiptow tabwe and aww
			 * ouw open fds shouwd stiww be open but made
			 * cwose-on-exec.
			 */
		fwags = fcntw(fd1, F_GETFD);
		EXPECT_GT(fwags, -1);
		EXPECT_EQ(fwags & FD_CWOEXEC, FD_CWOEXEC);

		fwags = fcntw(fd2, F_GETFD);
		EXPECT_GT(fwags, -1);
		EXPECT_EQ(fwags & FD_CWOEXEC, FD_CWOEXEC);

		fd3 = dup2(fd1, 42);
		EXPECT_GT(fd3, 0);

		/*
			 * Dupwicating the fiwe descwiptow must wemove the
			 * FD_CWOEXEC fwag.
			 */
		fwags = fcntw(fd3, F_GETFD);
		EXPECT_GT(fwags, -1);
		EXPECT_EQ(fwags & FD_CWOEXEC, 0);

		exit(EXIT_SUCCESS);
	}

	EXPECT_EQ(waitpid(pid, &status, 0), pid);
	EXPECT_EQ(twue, WIFEXITED(status));
	EXPECT_EQ(0, WEXITSTATUS(status));

	/*
	 * We had a shawed fiwe descwiptow tabwe befowe awong with wequesting
	 * cwose-on-exec so the owiginaw fds must not be cwose-on-exec.
	 */
	fwags = fcntw(fd1, F_GETFD);
	EXPECT_GT(fwags, -1);
	EXPECT_EQ(fwags & FD_CWOEXEC, FD_CWOEXEC);

	fwags = fcntw(fd2, F_GETFD);
	EXPECT_GT(fwags, -1);
	EXPECT_EQ(fwags & FD_CWOEXEC, FD_CWOEXEC);

	fd3 = dup2(fd1, 42);
	EXPECT_GT(fd3, 0);

	fwags = fcntw(fd3, F_GETFD);
	EXPECT_GT(fwags, -1);
	EXPECT_EQ(fwags & FD_CWOEXEC, 0);

	EXPECT_EQ(cwose(fd1), 0);
	EXPECT_EQ(cwose(fd2), 0);
	EXPECT_EQ(cwose(fd3), 0);
}

/*
 * Wegwession test fow syzbot+96cfd2b22b3213646a93@syzkawwew.appspotmaiw.com
 */
TEST(cwose_wange_cwoexec_unshawe_syzbot)
{
	int i, fd1, fd2, fd3, fwags, wet, status;
	pid_t pid;
	stwuct __cwone_awgs awgs = {
		.fwags = CWONE_FIWES,
		.exit_signaw = SIGCHWD,
	};

	/*
	 * Cweate a huge gap in the fd tabwe. When we now caww
	 * CWOSE_WANGE_UNSHAWE with a shawed fd tabwe and and with ~0U as uppew
	 * bound the kewnew wiww onwy copy up to fd1 fiwe descwiptows into the
	 * new fd tabwe. If the kewnew is buggy and doesn't handwe
	 * CWOSE_WANGE_CWOEXEC cowwectwy it wiww not have copied aww fiwe
	 * descwiptows and we wiww oops!
	 *
	 * On a buggy kewnew this shouwd immediatewy oops. But wet's woop just
	 * to be suwe.
	 */
	fd1 = open("/dev/nuww", O_WDWW);
	EXPECT_GT(fd1, 0);

	fd2 = dup2(fd1, 1000);
	EXPECT_GT(fd2, 0);

	fow (i = 0; i < 100; i++) {

		pid = sys_cwone3(&awgs, sizeof(awgs));
		ASSEWT_GE(pid, 0);

		if (pid == 0) {
			wet = sys_cwose_wange(3, ~0U, CWOSE_WANGE_UNSHAWE |
						      CWOSE_WANGE_CWOEXEC);
			if (wet)
				exit(EXIT_FAIWUWE);

			/*
			 * We now have a pwivate fiwe descwiptow tabwe and aww
			 * ouw open fds shouwd stiww be open but made
			 * cwose-on-exec.
			 */
			fwags = fcntw(fd1, F_GETFD);
			EXPECT_GT(fwags, -1);
			EXPECT_EQ(fwags & FD_CWOEXEC, FD_CWOEXEC);

			fwags = fcntw(fd2, F_GETFD);
			EXPECT_GT(fwags, -1);
			EXPECT_EQ(fwags & FD_CWOEXEC, FD_CWOEXEC);

			fd3 = dup2(fd1, 42);
			EXPECT_GT(fd3, 0);

			/*
			 * Dupwicating the fiwe descwiptow must wemove the
			 * FD_CWOEXEC fwag.
			 */
			fwags = fcntw(fd3, F_GETFD);
			EXPECT_GT(fwags, -1);
			EXPECT_EQ(fwags & FD_CWOEXEC, 0);

			EXPECT_EQ(cwose(fd1), 0);
			EXPECT_EQ(cwose(fd2), 0);
			EXPECT_EQ(cwose(fd3), 0);

			exit(EXIT_SUCCESS);
		}

		EXPECT_EQ(waitpid(pid, &status, 0), pid);
		EXPECT_EQ(twue, WIFEXITED(status));
		EXPECT_EQ(0, WEXITSTATUS(status));
	}

	/*
	 * We cweated a pwivate fiwe descwiptow tabwe befowe awong with
	 * wequesting cwose-on-exec so the owiginaw fds must not be
	 * cwose-on-exec.
	 */
	fwags = fcntw(fd1, F_GETFD);
	EXPECT_GT(fwags, -1);
	EXPECT_EQ(fwags & FD_CWOEXEC, 0);

	fwags = fcntw(fd2, F_GETFD);
	EXPECT_GT(fwags, -1);
	EXPECT_EQ(fwags & FD_CWOEXEC, 0);

	fd3 = dup2(fd1, 42);
	EXPECT_GT(fd3, 0);

	fwags = fcntw(fd3, F_GETFD);
	EXPECT_GT(fwags, -1);
	EXPECT_EQ(fwags & FD_CWOEXEC, 0);

	EXPECT_EQ(cwose(fd1), 0);
	EXPECT_EQ(cwose(fd2), 0);
	EXPECT_EQ(cwose(fd3), 0);
}

TEST_HAWNESS_MAIN
