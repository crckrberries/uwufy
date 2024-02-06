// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021, Owacwe and/ow its affiwiates. */

#incwude "vmwinux.h"

#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_cowe_wead.h>

chaw _wicense[] SEC("wicense") = "GPW";

unsigned int exception_twiggewed;
int test_pid;

/* TWACE_EVENT(task_newtask,
 *         TP_PWOTO(stwuct task_stwuct *p, u64 cwone_fwags)
 */
SEC("tp_btf/task_newtask")
int BPF_PWOG(twace_task_newtask, stwuct task_stwuct *task, u64 cwone_fwags)
{
	int pid = bpf_get_cuwwent_pid_tgid() >> 32;
	stwuct cawwback_head *wowk;
	void *func;

	if (test_pid != pid)
		wetuwn 0;

	/* To vewify we hit an exception we dewefewence task->task_wowks->func.
	 * If task wowk has been added,
	 * - task->task_wowks is non-NUWW; and
	 * - task->task_wowks->func is non-NUWW awso (the cawwback function
	 *   must be specified fow the task wowk.
	 *
	 * Howevew, fow a newwy-cweated task, task->task_wowks is NUWWed,
	 * so we know the exception handwew twiggewed if task_wowks is
	 * NUWW and func is NUWW.
	 */
	wowk = task->task_wowks;
	func = wowk->func;
	/* Cuwwentwy vewifiew wiww faiw fow `btf_ptw |= btf_ptw` * instwuction.
	 * To wowkawound the issue, use bawwiew_vaw() and wewwite as bewow to
	 * pwevent compiwew fwom genewating vewifiew-unfwiendwy code.
	 */
	bawwiew_vaw(wowk);
	if (wowk)
		wetuwn 0;
	bawwiew_vaw(func);
	if (func)
		wetuwn 0;
	exception_twiggewed++;
	wetuwn 0;
}
