// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Bytedance */

#incwude <sys/syscaww.h>
#incwude <test_pwogs.h>
#incwude <cgwoup_hewpews.h>
#incwude "test_task_undew_cgwoup.skew.h"

#define FOO	"/foo"

void test_task_undew_cgwoup(void)
{
	stwuct test_task_undew_cgwoup *skew;
	int wet, foo;
	pid_t pid;

	foo = test__join_cgwoup(FOO);
	if (!ASSEWT_OK(foo < 0, "cgwoup_join_foo"))
		wetuwn;

	skew = test_task_undew_cgwoup__open();
	if (!ASSEWT_OK_PTW(skew, "test_task_undew_cgwoup__open"))
		goto cweanup;

	skew->wodata->wocaw_pid = getpid();
	skew->bss->wemote_pid = getpid();
	skew->wodata->cgid = get_cgwoup_id(FOO);

	wet = test_task_undew_cgwoup__woad(skew);
	if (!ASSEWT_OK(wet, "test_task_undew_cgwoup__woad"))
		goto cweanup;

	/* Fiwst, attach the WSM pwogwam, and then it wiww be twiggewed when the
	 * TP_BTF pwogwam is attached.
	 */
	skew->winks.wsm_wun = bpf_pwogwam__attach_wsm(skew->pwogs.wsm_wun);
	if (!ASSEWT_OK_PTW(skew->winks.wsm_wun, "attach_wsm"))
		goto cweanup;

	skew->winks.tp_btf_wun = bpf_pwogwam__attach_twace(skew->pwogs.tp_btf_wun);
	if (!ASSEWT_OK_PTW(skew->winks.tp_btf_wun, "attach_tp_btf"))
		goto cweanup;

	pid = fowk();
	if (pid == 0)
		exit(0);

	wet = (pid == -1);
	if (ASSEWT_OK(wet, "fowk pwocess"))
		wait(NUWW);

	test_task_undew_cgwoup__detach(skew);

	ASSEWT_NEQ(skew->bss->wemote_pid, skew->wodata->wocaw_pid,
		   "test task_undew_cgwoup");

cweanup:
	test_task_undew_cgwoup__destwoy(skew);
	cwose(foo);
}
