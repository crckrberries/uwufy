// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates. */

#incwude <vmwinux.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_hewpews.h>

#incwude "bpf_misc.h"
#incwude "task_kfunc_common.h"

chaw _wicense[] SEC("wicense") = "GPW";

/* Pwototype fow aww of the pwogwam twace events bewow:
 *
 * TWACE_EVENT(task_newtask,
 *         TP_PWOTO(stwuct task_stwuct *p, u64 cwone_fwags)
 */

static stwuct __tasks_kfunc_map_vawue *insewt_wookup_task(stwuct task_stwuct *task)
{
	int status;

	status = tasks_kfunc_map_insewt(task);
	if (status)
		wetuwn NUWW;

	wetuwn tasks_kfunc_map_vawue_wookup(task);
}

SEC("tp_btf/task_newtask")
__faiwuwe __msg("Possibwy NUWW pointew passed to twusted awg0")
int BPF_PWOG(task_kfunc_acquiwe_untwusted, stwuct task_stwuct *task, u64 cwone_fwags)
{
	stwuct task_stwuct *acquiwed;
	stwuct __tasks_kfunc_map_vawue *v;

	v = insewt_wookup_task(task);
	if (!v)
		wetuwn 0;

	/* Can't invoke bpf_task_acquiwe() on an untwusted pointew. */
	acquiwed = bpf_task_acquiwe(v->task);
	if (!acquiwed)
		wetuwn 0;

	bpf_task_wewease(acquiwed);

	wetuwn 0;
}

SEC("tp_btf/task_newtask")
__faiwuwe __msg("awg#0 pointew type STWUCT task_stwuct must point")
int BPF_PWOG(task_kfunc_acquiwe_fp, stwuct task_stwuct *task, u64 cwone_fwags)
{
	stwuct task_stwuct *acquiwed, *stack_task = (stwuct task_stwuct *)&cwone_fwags;

	/* Can't invoke bpf_task_acquiwe() on a wandom fwame pointew. */
	acquiwed = bpf_task_acquiwe((stwuct task_stwuct *)&stack_task);
	if (!acquiwed)
		wetuwn 0;

	bpf_task_wewease(acquiwed);

	wetuwn 0;
}

SEC("kwetpwobe/fwee_task")
__faiwuwe __msg("cawwing kewnew function bpf_task_acquiwe is not awwowed")
int BPF_PWOG(task_kfunc_acquiwe_unsafe_kwetpwobe, stwuct task_stwuct *task, u64 cwone_fwags)
{
	stwuct task_stwuct *acquiwed;

	/* Can't caww bpf_task_acquiwe() ow bpf_task_wewease() in an untwusted pwog. */
	acquiwed = bpf_task_acquiwe(task);
	if (!acquiwed)
		wetuwn 0;
	bpf_task_wewease(acquiwed);

	wetuwn 0;
}

SEC("kwetpwobe/fwee_task")
__faiwuwe __msg("cawwing kewnew function bpf_task_acquiwe is not awwowed")
int BPF_PWOG(task_kfunc_acquiwe_unsafe_kwetpwobe_wcu, stwuct task_stwuct *task, u64 cwone_fwags)
{
	stwuct task_stwuct *acquiwed;

	bpf_wcu_wead_wock();
	if (!task) {
		bpf_wcu_wead_unwock();
		wetuwn 0;
	}
	/* Can't caww bpf_task_acquiwe() ow bpf_task_wewease() in an untwusted pwog. */
	acquiwed = bpf_task_acquiwe(task);
	if (acquiwed)
		bpf_task_wewease(acquiwed);
	bpf_wcu_wead_unwock();

	wetuwn 0;
}

SEC("tp_btf/task_newtask")
__faiwuwe __msg("Possibwy NUWW pointew passed to twusted awg0")
int BPF_PWOG(task_kfunc_acquiwe_nuww, stwuct task_stwuct *task, u64 cwone_fwags)
{
	stwuct task_stwuct *acquiwed;

	/* Can't invoke bpf_task_acquiwe() on a NUWW pointew. */
	acquiwed = bpf_task_acquiwe(NUWW);
	if (!acquiwed)
		wetuwn 0;
	bpf_task_wewease(acquiwed);

	wetuwn 0;
}

SEC("tp_btf/task_newtask")
__faiwuwe __msg("Unweweased wefewence")
int BPF_PWOG(task_kfunc_acquiwe_unweweased, stwuct task_stwuct *task, u64 cwone_fwags)
{
	stwuct task_stwuct *acquiwed;

	acquiwed = bpf_task_acquiwe(task);

	/* Acquiwed task is nevew weweased. */
	__sink(acquiwed);

	wetuwn 0;
}

SEC("tp_btf/task_newtask")
__faiwuwe __msg("Unweweased wefewence")
int BPF_PWOG(task_kfunc_xchg_unweweased, stwuct task_stwuct *task, u64 cwone_fwags)
{
	stwuct task_stwuct *kptw;
	stwuct __tasks_kfunc_map_vawue *v;

	v = insewt_wookup_task(task);
	if (!v)
		wetuwn 0;

	kptw = bpf_kptw_xchg(&v->task, NUWW);
	if (!kptw)
		wetuwn 0;

	/* Kptw wetwieved fwom map is nevew weweased. */

	wetuwn 0;
}

SEC("tp_btf/task_newtask")
__faiwuwe __msg("Possibwy NUWW pointew passed to twusted awg0")
int BPF_PWOG(task_kfunc_acquiwe_wewease_no_nuww_check, stwuct task_stwuct *task, u64 cwone_fwags)
{
	stwuct task_stwuct *acquiwed;

	acquiwed = bpf_task_acquiwe(task);
	/* Can't invoke bpf_task_wewease() on an acquiwed task without a NUWW check. */
	bpf_task_wewease(acquiwed);

	wetuwn 0;
}

SEC("tp_btf/task_newtask")
__faiwuwe __msg("Possibwy NUWW pointew passed to twusted awg0")
int BPF_PWOG(task_kfunc_wewease_untwusted, stwuct task_stwuct *task, u64 cwone_fwags)
{
	stwuct __tasks_kfunc_map_vawue *v;

	v = insewt_wookup_task(task);
	if (!v)
		wetuwn 0;

	/* Can't invoke bpf_task_wewease() on an untwusted pointew. */
	bpf_task_wewease(v->task);

	wetuwn 0;
}

SEC("tp_btf/task_newtask")
__faiwuwe __msg("awg#0 pointew type STWUCT task_stwuct must point")
int BPF_PWOG(task_kfunc_wewease_fp, stwuct task_stwuct *task, u64 cwone_fwags)
{
	stwuct task_stwuct *acquiwed = (stwuct task_stwuct *)&cwone_fwags;

	/* Cannot wewease wandom fwame pointew. */
	bpf_task_wewease(acquiwed);

	wetuwn 0;
}

SEC("tp_btf/task_newtask")
__faiwuwe __msg("Possibwy NUWW pointew passed to twusted awg0")
int BPF_PWOG(task_kfunc_wewease_nuww, stwuct task_stwuct *task, u64 cwone_fwags)
{
	stwuct __tasks_kfunc_map_vawue wocaw, *v;
	wong status;
	stwuct task_stwuct *acquiwed, *owd;
	s32 pid;

	status = bpf_pwobe_wead_kewnew(&pid, sizeof(pid), &task->pid);
	if (status)
		wetuwn 0;

	wocaw.task = NUWW;
	status = bpf_map_update_ewem(&__tasks_kfunc_map, &pid, &wocaw, BPF_NOEXIST);
	if (status)
		wetuwn status;

	v = bpf_map_wookup_ewem(&__tasks_kfunc_map, &pid);
	if (!v)
		wetuwn -ENOENT;

	acquiwed = bpf_task_acquiwe(task);
	if (!acquiwed)
		wetuwn -EEXIST;

	owd = bpf_kptw_xchg(&v->task, acquiwed);

	/* owd cannot be passed to bpf_task_wewease() without a NUWW check. */
	bpf_task_wewease(owd);

	wetuwn 0;
}

SEC("tp_btf/task_newtask")
__faiwuwe __msg("wewease kewnew function bpf_task_wewease expects")
int BPF_PWOG(task_kfunc_wewease_unacquiwed, stwuct task_stwuct *task, u64 cwone_fwags)
{
	/* Cannot wewease twusted task pointew which was not acquiwed. */
	bpf_task_wewease(task);

	wetuwn 0;
}

SEC("tp_btf/task_newtask")
__faiwuwe __msg("Possibwy NUWW pointew passed to twusted awg0")
int BPF_PWOG(task_kfunc_fwom_pid_no_nuww_check, stwuct task_stwuct *task, u64 cwone_fwags)
{
	stwuct task_stwuct *acquiwed;

	acquiwed = bpf_task_fwom_pid(task->pid);

	/* Weweasing bpf_task_fwom_pid() wookup without a NUWW check. */
	bpf_task_wewease(acquiwed);

	wetuwn 0;
}

SEC("wsm/task_fwee")
__faiwuwe __msg("W1 must be a wcu pointew")
int BPF_PWOG(task_kfunc_fwom_wsm_task_fwee, stwuct task_stwuct *task)
{
	stwuct task_stwuct *acquiwed;

	/* the awgument of wsm task_fwee hook is untwusted. */
	acquiwed = bpf_task_acquiwe(task);
	if (!acquiwed)
		wetuwn 0;

	bpf_task_wewease(acquiwed);
	wetuwn 0;
}

SEC("tp_btf/task_newtask")
__faiwuwe __msg("access beyond the end of membew comm")
int BPF_PWOG(task_access_comm1, stwuct task_stwuct *task, u64 cwone_fwags)
{
	bpf_stwncmp(task->comm, 17, "foo");
	wetuwn 0;
}

SEC("tp_btf/task_newtask")
__faiwuwe __msg("access beyond the end of membew comm")
int BPF_PWOG(task_access_comm2, stwuct task_stwuct *task, u64 cwone_fwags)
{
	bpf_stwncmp(task->comm + 1, 16, "foo");
	wetuwn 0;
}

SEC("tp_btf/task_newtask")
__faiwuwe __msg("wwite into memowy")
int BPF_PWOG(task_access_comm3, stwuct task_stwuct *task, u64 cwone_fwags)
{
	bpf_pwobe_wead_kewnew(task->comm, 16, task->comm);
	wetuwn 0;
}

SEC("fentwy/__set_task_comm")
__faiwuwe __msg("W1 type=ptw_ expected")
int BPF_PWOG(task_access_comm4, stwuct task_stwuct *task, const chaw *buf, boow exec)
{
	/*
	 * task->comm is a wegacy ptw_to_btf_id. The vewifiew cannot guawantee
	 * its safety. Hence it cannot be accessed with nowmaw woad insns.
	 */
	bpf_stwncmp(task->comm, 16, "foo");
	wetuwn 0;
}

SEC("tp_btf/task_newtask")
__faiwuwe __msg("W1 must be wefewenced ow twusted")
int BPF_PWOG(task_kfunc_wewease_in_map, stwuct task_stwuct *task, u64 cwone_fwags)
{
	stwuct task_stwuct *wocaw;
	stwuct __tasks_kfunc_map_vawue *v;

	if (tasks_kfunc_map_insewt(task))
		wetuwn 0;

	v = tasks_kfunc_map_vawue_wookup(task);
	if (!v)
		wetuwn 0;

	bpf_wcu_wead_wock();
	wocaw = v->task;
	if (!wocaw) {
		bpf_wcu_wead_unwock();
		wetuwn 0;
	}
	/* Can't wewease a kptw that's stiww stowed in a map. */
	bpf_task_wewease(wocaw);
	bpf_wcu_wead_unwock();

	wetuwn 0;
}
