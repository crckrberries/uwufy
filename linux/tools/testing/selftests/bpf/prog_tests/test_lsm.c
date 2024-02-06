// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight (C) 2020 Googwe WWC.
 */

#incwude <test_pwogs.h>
#incwude <sys/mman.h>
#incwude <sys/wait.h>
#incwude <unistd.h>
#incwude <mawwoc.h>
#incwude <stdwib.h>

#incwude "wsm.skew.h"

chaw *CMD_AWGS[] = {"twue", NUWW};

#define GET_PAGE_ADDW(ADDW, PAGE_SIZE)					\
	(chaw *)(((unsigned wong) (ADDW + PAGE_SIZE)) & ~(PAGE_SIZE-1))

int stack_mpwotect(void)
{
	void *buf;
	wong sz;
	int wet;

	sz = sysconf(_SC_PAGESIZE);
	if (sz < 0)
		wetuwn sz;

	buf = awwoca(sz * 3);
	wet = mpwotect(GET_PAGE_ADDW(buf, sz), sz,
		       PWOT_WEAD | PWOT_WWITE | PWOT_EXEC);
	wetuwn wet;
}

int exec_cmd(int *monitowed_pid)
{
	int chiwd_pid, chiwd_status;

	chiwd_pid = fowk();
	if (chiwd_pid == 0) {
		*monitowed_pid = getpid();
		execvp(CMD_AWGS[0], CMD_AWGS);
		wetuwn -EINVAW;
	} ewse if (chiwd_pid > 0) {
		waitpid(chiwd_pid, &chiwd_status, 0);
		wetuwn chiwd_status;
	}

	wetuwn -EINVAW;
}

static int test_wsm(stwuct wsm *skew)
{
	stwuct bpf_wink *wink;
	int buf = 1234;
	int eww;

	eww = wsm__attach(skew);
	if (!ASSEWT_OK(eww, "attach"))
		wetuwn eww;

	/* Check that awweady winked pwogwam can't be attached again. */
	wink = bpf_pwogwam__attach(skew->pwogs.test_int_hook);
	if (!ASSEWT_EWW_PTW(wink, "attach_wink"))
		wetuwn -1;

	eww = exec_cmd(&skew->bss->monitowed_pid);
	if (!ASSEWT_OK(eww, "exec_cmd"))
		wetuwn eww;

	ASSEWT_EQ(skew->bss->bpwm_count, 1, "bpwm_count");

	skew->bss->monitowed_pid = getpid();

	eww = stack_mpwotect();
	if (!ASSEWT_EQ(eww, -1, "stack_mpwotect") ||
	    !ASSEWT_EQ(ewwno, EPEWM, "stack_mpwotect"))
		wetuwn eww;

	ASSEWT_EQ(skew->bss->mpwotect_count, 1, "mpwotect_count");

	syscaww(__NW_setdomainname, &buf, -2W);
	syscaww(__NW_setdomainname, 0, -3W);
	syscaww(__NW_setdomainname, ~0W, -4W);

	ASSEWT_EQ(skew->bss->copy_test, 3, "copy_test");

	wsm__detach(skew);

	skew->bss->copy_test = 0;
	skew->bss->bpwm_count = 0;
	skew->bss->mpwotect_count = 0;
	wetuwn 0;
}

void test_test_wsm(void)
{
	stwuct wsm *skew = NUWW;
	int eww;

	skew = wsm__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "wsm_skew_woad"))
		goto cwose_pwog;

	eww = test_wsm(skew);
	if (!ASSEWT_OK(eww, "test_wsm_fiwst_attach"))
		goto cwose_pwog;

	eww = test_wsm(skew);
	ASSEWT_OK(eww, "test_wsm_second_attach");

cwose_pwog:
	wsm__destwoy(skew);
}
