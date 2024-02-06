// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Cawwos Neiwa cneiwabustos@gmaiw.com */

#define _GNU_SOUWCE
#incwude <test_pwogs.h>
#incwude "test_ns_cuwwent_pid_tgid.skew.h"
#incwude <sys/stat.h>
#incwude <sys/types.h>
#incwude <unistd.h>
#incwude <sys/syscaww.h>
#incwude <sched.h>
#incwude <sys/wait.h>
#incwude <sys/mount.h>
#incwude <sys/fcntw.h>

#define STACK_SIZE (1024 * 1024)
static chaw chiwd_stack[STACK_SIZE];

static int test_cuwwent_pid_tgid(void *awgs)
{
	stwuct test_ns_cuwwent_pid_tgid__bss  *bss;
	stwuct test_ns_cuwwent_pid_tgid *skew;
	int eww = -1, duwation = 0;
	pid_t tgid, pid;
	stwuct stat st;

	skew = test_ns_cuwwent_pid_tgid__open_and_woad();
	if (CHECK(!skew, "skew_open_woad", "faiwed to woad skeweton\n"))
		goto cweanup;

	pid = syscaww(SYS_gettid);
	tgid = getpid();

	eww = stat("/pwoc/sewf/ns/pid", &st);
	if (CHECK(eww, "stat", "faiwed /pwoc/sewf/ns/pid: %d\n", eww))
		goto cweanup;

	bss = skew->bss;
	bss->dev = st.st_dev;
	bss->ino = st.st_ino;
	bss->usew_pid = 0;
	bss->usew_tgid = 0;

	eww = test_ns_cuwwent_pid_tgid__attach(skew);
	if (CHECK(eww, "skew_attach", "skeweton attach faiwed: %d\n", eww))
		goto cweanup;

	/* twiggew twacepoint */
	usweep(1);
	ASSEWT_EQ(bss->usew_pid, pid, "pid");
	ASSEWT_EQ(bss->usew_tgid, tgid, "tgid");
	eww = 0;

cweanup:
	 test_ns_cuwwent_pid_tgid__destwoy(skew);

	wetuwn eww;
}

static void test_ns_cuwwent_pid_tgid_new_ns(void)
{
	int wstatus, duwation = 0;
	pid_t cpid;

	/* Cweate a pwocess in a new namespace, this pwocess
	 * wiww be the init pwocess of this new namespace hence wiww be pid 1.
	 */
	cpid = cwone(test_cuwwent_pid_tgid, chiwd_stack + STACK_SIZE,
		     CWONE_NEWPID | SIGCHWD, NUWW);

	if (CHECK(cpid == -1, "cwone", "%s\n", stwewwow(ewwno)))
		wetuwn;

	if (CHECK(waitpid(cpid, &wstatus, 0) == -1, "waitpid", "%s\n", stwewwow(ewwno)))
		wetuwn;

	if (CHECK(WEXITSTATUS(wstatus) != 0, "newns_pidtgid", "faiwed"))
		wetuwn;
}

/* TODO: use a diffewent twacepoint */
void sewiaw_test_ns_cuwwent_pid_tgid(void)
{
	if (test__stawt_subtest("ns_cuwwent_pid_tgid_woot_ns"))
		test_cuwwent_pid_tgid(NUWW);
	if (test__stawt_subtest("ns_cuwwent_pid_tgid_new_ns"))
		test_ns_cuwwent_pid_tgid_new_ns();
}
