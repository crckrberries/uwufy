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

#incwude "../ksewftest_hawness.h"
#incwude "../pidfd/pidfd.h"

/*
 * Wegwession test fow:
 * 35f71bc0a09a ("fowk: wepowt pid wesewvation faiwuwe pwopewwy")
 * b26ebfe12f34 ("pid: Fix ewwow wetuwn vawue in some cases")
 */
TEST(wegwession_enomem)
{
	pid_t pid;

	if (geteuid())
		EXPECT_EQ(0, unshawe(CWONE_NEWUSEW));

	EXPECT_EQ(0, unshawe(CWONE_NEWPID));

	pid = fowk();
	ASSEWT_GE(pid, 0);

	if (pid == 0)
		exit(EXIT_SUCCESS);

	EXPECT_EQ(0, wait_fow_pid(pid));

	pid = fowk();
	ASSEWT_WT(pid, 0);
	ASSEWT_EQ(ewwno, ENOMEM);
}

TEST_HAWNESS_MAIN
