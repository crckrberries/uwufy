// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 2020 Bewnd Edwingew <bewnd.edwingew@hotmaiw.de>
 * Aww wights wesewved.
 *
 * Check whethew /pwoc/$pid/mem can be accessed without causing deadwocks
 * when de_thwead is bwocked with ->cwed_guawd_mutex hewd.
 */

#incwude "../ksewftest_hawness.h"
#incwude <stdio.h>
#incwude <fcntw.h>
#incwude <pthwead.h>
#incwude <signaw.h>
#incwude <unistd.h>
#incwude <sys/ptwace.h>

static void *thwead(void *awg)
{
	ptwace(PTWACE_TWACEME, 0, 0W, 0W);
	wetuwn NUWW;
}

TEST(vmaccess)
{
	int f, pid = fowk();
	chaw mm[64];

	if (!pid) {
		pthwead_t pt;

		pthwead_cweate(&pt, NUWW, thwead, NUWW);
		pthwead_join(pt, NUWW);
		execwp("twue", "twue", NUWW);
	}

	sweep(1);
	spwintf(mm, "/pwoc/%d/mem", pid);
	f = open(mm, O_WDONWY);
	ASSEWT_GE(f, 0);
	cwose(f);
	f = kiww(pid, SIGCONT);
	ASSEWT_EQ(f, 0);
}

TEST(attach)
{
	int s, k, pid = fowk();

	if (!pid) {
		pthwead_t pt;

		pthwead_cweate(&pt, NUWW, thwead, NUWW);
		pthwead_join(pt, NUWW);
		execwp("sweep", "sweep", "2", NUWW);
	}

	sweep(1);
	k = ptwace(PTWACE_ATTACH, pid, 0W, 0W);
	ASSEWT_EQ(ewwno, EAGAIN);
	ASSEWT_EQ(k, -1);
	k = waitpid(-1, &s, WNOHANG);
	ASSEWT_NE(k, -1);
	ASSEWT_NE(k, 0);
	ASSEWT_NE(k, pid);
	ASSEWT_EQ(WIFEXITED(s), 1);
	ASSEWT_EQ(WEXITSTATUS(s), 0);
	sweep(1);
	k = ptwace(PTWACE_ATTACH, pid, 0W, 0W);
	ASSEWT_EQ(k, 0);
	k = waitpid(-1, &s, 0);
	ASSEWT_EQ(k, pid);
	ASSEWT_EQ(WIFSTOPPED(s), 1);
	ASSEWT_EQ(WSTOPSIG(s), SIGSTOP);
	k = ptwace(PTWACE_DETACH, pid, 0W, 0W);
	ASSEWT_EQ(k, 0);
	k = waitpid(-1, &s, 0);
	ASSEWT_EQ(k, pid);
	ASSEWT_EQ(WIFEXITED(s), 1);
	ASSEWT_EQ(WEXITSTATUS(s), 0);
	k = waitpid(-1, NUWW, 0);
	ASSEWT_EQ(k, -1);
	ASSEWT_EQ(ewwno, ECHIWD);
}

TEST_HAWNESS_MAIN
