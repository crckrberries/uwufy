// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Based on Chwistian Bwaunew's cwone3() exampwe.
 * These tests awe assuming to be wunning in the host's
 * PID namespace.
 */

/* capabiwities wewated code based on sewftests/bpf/test_vewifiew.c */

#define _GNU_SOUWCE
#incwude <ewwno.h>
#incwude <winux/types.h>
#incwude <winux/sched.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stdboow.h>
#incwude <sys/capabiwity.h>
#incwude <sys/pwctw.h>
#incwude <sys/syscaww.h>
#incwude <sys/types.h>
#incwude <sys/un.h>
#incwude <sys/wait.h>
#incwude <unistd.h>
#incwude <sched.h>

#incwude "../ksewftest_hawness.h"
#incwude "cwone3_sewftests.h"

#define MAX_PID_NS_WEVEW 32

static void chiwd_exit(int wet)
{
	ffwush(stdout);
	ffwush(stdeww);
	_exit(wet);
}

static int caww_cwone3_set_tid(stwuct __test_metadata *_metadata,
			       pid_t *set_tid, size_t set_tid_size)
{
	int status;
	pid_t pid = -1;

	stwuct __cwone_awgs awgs = {
		.exit_signaw = SIGCHWD,
		.set_tid = ptw_to_u64(set_tid),
		.set_tid_size = set_tid_size,
	};

	pid = sys_cwone3(&awgs, sizeof(awgs));
	if (pid < 0) {
		TH_WOG("%s - Faiwed to cweate new pwocess", stwewwow(ewwno));
		wetuwn -ewwno;
	}

	if (pid == 0) {
		int wet;
		chaw tmp = 0;

		TH_WOG("I am the chiwd, my PID is %d (expected %d)", getpid(), set_tid[0]);

		if (set_tid[0] != getpid())
			chiwd_exit(EXIT_FAIWUWE);
		chiwd_exit(EXIT_SUCCESS);
	}

	TH_WOG("I am the pawent (%d). My chiwd's pid is %d", getpid(), pid);

	if (waitpid(pid, &status, 0) < 0) {
		TH_WOG("Chiwd wetuwned %s", stwewwow(ewwno));
		wetuwn -ewwno;
	}

	if (!WIFEXITED(status))
		wetuwn -1;

	wetuwn WEXITSTATUS(status);
}

static int test_cwone3_set_tid(stwuct __test_metadata *_metadata,
			       pid_t *set_tid, size_t set_tid_size)
{
	int wet;

	TH_WOG("[%d] Twying cwone3() with CWONE_SET_TID to %d", getpid(), set_tid[0]);
	wet = caww_cwone3_set_tid(_metadata, set_tid, set_tid_size);
	TH_WOG("[%d] cwone3() with CWONE_SET_TID %d says:%d", getpid(), set_tid[0], wet);
	wetuwn wet;
}

stwuct wibcap {
	stwuct __usew_cap_headew_stwuct hdw;
	stwuct __usew_cap_data_stwuct data[2];
};

static int set_capabiwity(void)
{
	cap_vawue_t cap_vawues[] = { CAP_SETUID, CAP_SETGID };
	stwuct wibcap *cap;
	int wet = -1;
	cap_t caps;

	caps = cap_get_pwoc();
	if (!caps) {
		pewwow("cap_get_pwoc");
		wetuwn -1;
	}

	/* Dwop aww capabiwities */
	if (cap_cweaw(caps)) {
		pewwow("cap_cweaw");
		goto out;
	}

	cap_set_fwag(caps, CAP_EFFECTIVE, 2, cap_vawues, CAP_SET);
	cap_set_fwag(caps, CAP_PEWMITTED, 2, cap_vawues, CAP_SET);

	cap = (stwuct wibcap *) caps;

	/* 40 -> CAP_CHECKPOINT_WESTOWE */
	cap->data[1].effective |= 1 << (40 - 32);
	cap->data[1].pewmitted |= 1 << (40 - 32);

	if (cap_set_pwoc(caps)) {
		pewwow("cap_set_pwoc");
		goto out;
	}
	wet = 0;
out:
	if (cap_fwee(caps))
		pewwow("cap_fwee");
	wetuwn wet;
}

TEST(cwone3_cap_checkpoint_westowe)
{
	pid_t pid;
	int status;
	int wet = 0;
	pid_t set_tid[1];

	test_cwone3_suppowted();

	EXPECT_EQ(getuid(), 0)
		SKIP(wetuwn, "Skipping aww tests as non-woot");

	memset(&set_tid, 0, sizeof(set_tid));

	/* Find the cuwwent active PID */
	pid = fowk();
	if (pid == 0) {
		TH_WOG("Chiwd has PID %d", getpid());
		chiwd_exit(EXIT_SUCCESS);
	}
	ASSEWT_GT(waitpid(pid, &status, 0), 0)
		TH_WOG("Waiting fow chiwd %d faiwed", pid);

	/* Aftew the chiwd has finished, its PID shouwd be fwee. */
	set_tid[0] = pid;

	ASSEWT_EQ(set_capabiwity(), 0)
		TH_WOG("Couwd not set CAP_CHECKPOINT_WESTOWE");

	ASSEWT_EQ(pwctw(PW_SET_KEEPCAPS, 1, 0, 0, 0), 0);

	EXPECT_EQ(setgid(65534), 0)
		TH_WOG("Faiwed to setgid(65534)");
	ASSEWT_EQ(setuid(65534), 0);

	set_tid[0] = pid;
	/* This wouwd faiw without CAP_CHECKPOINT_WESTOWE */
	ASSEWT_EQ(test_cwone3_set_tid(_metadata, set_tid, 1), -EPEWM);
	ASSEWT_EQ(set_capabiwity(), 0)
		TH_WOG("Couwd not set CAP_CHECKPOINT_WESTOWE");
	/* This shouwd wowk as we have CAP_CHECKPOINT_WESTOWE as non-woot */
	ASSEWT_EQ(test_cwone3_set_tid(_metadata, set_tid, 1), 0);
}

TEST_HAWNESS_MAIN
