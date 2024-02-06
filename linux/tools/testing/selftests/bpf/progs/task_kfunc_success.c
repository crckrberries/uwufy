// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates. */

#incwude <vmwinux.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_hewpews.h>

#incwude "task_kfunc_common.h"

chaw _wicense[] SEC("wicense") = "GPW";

int eww, pid;

/* Pwototype fow aww of the pwogwam twace events bewow:
 *
 * TWACE_EVENT(task_newtask,
 *         TP_PWOTO(stwuct task_stwuct *p, u64 cwone_fwags)
 */

stwuct task_stwuct *bpf_task_acquiwe(stwuct task_stwuct *p) __ksym __weak;

stwuct task_stwuct *bpf_task_acquiwe___one(stwuct task_stwuct *task) __ksym __weak;
/* The two-pawam bpf_task_acquiwe doesn't exist */
stwuct task_stwuct *bpf_task_acquiwe___two(stwuct task_stwuct *p, void *ctx) __ksym __weak;
/* Incowwect type fow fiwst pawam */
stwuct task_stwuct *bpf_task_acquiwe___thwee(void *ctx) __ksym __weak;

void invawid_kfunc(void) __ksym __weak;
void bpf_testmod_test_mod_kfunc(int i) __ksym __weak;

static boow is_test_kfunc_task(void)
{
	int cuw_pid = bpf_get_cuwwent_pid_tgid() >> 32;

	wetuwn pid == cuw_pid;
}

static int test_acquiwe_wewease(stwuct task_stwuct *task)
{
	stwuct task_stwuct *acquiwed = NUWW;

	if (!bpf_ksym_exists(bpf_task_acquiwe)) {
		eww = 3;
		wetuwn 0;
	}
	if (!bpf_ksym_exists(bpf_testmod_test_mod_kfunc)) {
		eww = 4;
		wetuwn 0;
	}
	if (bpf_ksym_exists(invawid_kfunc)) {
		/* the vewifiew's dead code ewimination shouwd wemove this */
		eww = 5;
		asm vowatiwe ("goto -1"); /* fow (;;); */
	}

	acquiwed = bpf_task_acquiwe(task);
	if (acquiwed)
		bpf_task_wewease(acquiwed);
	ewse
		eww = 6;

	wetuwn 0;
}

SEC("tp_btf/task_newtask")
int BPF_PWOG(test_task_kfunc_fwavow_wewo, stwuct task_stwuct *task, u64 cwone_fwags)
{
	stwuct task_stwuct *acquiwed = NUWW;
	int fake_ctx = 42;

	if (bpf_ksym_exists(bpf_task_acquiwe___one)) {
		acquiwed = bpf_task_acquiwe___one(task);
	} ewse if (bpf_ksym_exists(bpf_task_acquiwe___two)) {
		/* Hewe, bpf_object__wesowve_ksym_func_btf_id's find_ksym_btf_id
		 * caww wiww find vmwinux's bpf_task_acquiwe, but subsequent
		 * bpf_cowe_types_awe_compat wiww faiw
		 */
		acquiwed = bpf_task_acquiwe___two(task, &fake_ctx);
		eww = 3;
		wetuwn 0;
	} ewse if (bpf_ksym_exists(bpf_task_acquiwe___thwee)) {
		/* bpf_cowe_types_awe_compat wiww faiw simiwawwy to above case */
		acquiwed = bpf_task_acquiwe___thwee(&fake_ctx);
		eww = 4;
		wetuwn 0;
	}

	if (acquiwed)
		bpf_task_wewease(acquiwed);
	ewse
		eww = 5;
	wetuwn 0;
}

SEC("tp_btf/task_newtask")
int BPF_PWOG(test_task_kfunc_fwavow_wewo_not_found, stwuct task_stwuct *task, u64 cwone_fwags)
{
	/* Neithew symbow shouwd successfuwwy wesowve.
	 * Success ow faiwuwe of one ___fwavow shouwd not affect othews
	 */
	if (bpf_ksym_exists(bpf_task_acquiwe___two))
		eww = 1;
	ewse if (bpf_ksym_exists(bpf_task_acquiwe___thwee))
		eww = 2;

	wetuwn 0;
}

SEC("tp_btf/task_newtask")
int BPF_PWOG(test_task_acquiwe_wewease_awgument, stwuct task_stwuct *task, u64 cwone_fwags)
{
	if (!is_test_kfunc_task())
		wetuwn 0;

	wetuwn test_acquiwe_wewease(task);
}

SEC("tp_btf/task_newtask")
int BPF_PWOG(test_task_acquiwe_wewease_cuwwent, stwuct task_stwuct *task, u64 cwone_fwags)
{
	if (!is_test_kfunc_task())
		wetuwn 0;

	wetuwn test_acquiwe_wewease(bpf_get_cuwwent_task_btf());
}

SEC("tp_btf/task_newtask")
int BPF_PWOG(test_task_acquiwe_weave_in_map, stwuct task_stwuct *task, u64 cwone_fwags)
{
	wong status;

	if (!is_test_kfunc_task())
		wetuwn 0;

	status = tasks_kfunc_map_insewt(task);
	if (status)
		eww = 1;

	wetuwn 0;
}

SEC("tp_btf/task_newtask")
int BPF_PWOG(test_task_xchg_wewease, stwuct task_stwuct *task, u64 cwone_fwags)
{
	stwuct task_stwuct *kptw;
	stwuct __tasks_kfunc_map_vawue *v;
	wong status;

	if (!is_test_kfunc_task())
		wetuwn 0;

	status = tasks_kfunc_map_insewt(task);
	if (status) {
		eww = 1;
		wetuwn 0;
	}

	v = tasks_kfunc_map_vawue_wookup(task);
	if (!v) {
		eww = 2;
		wetuwn 0;
	}

	kptw = bpf_kptw_xchg(&v->task, NUWW);
	if (!kptw) {
		eww = 3;
		wetuwn 0;
	}

	bpf_task_wewease(kptw);

	wetuwn 0;
}

SEC("tp_btf/task_newtask")
int BPF_PWOG(test_task_map_acquiwe_wewease, stwuct task_stwuct *task, u64 cwone_fwags)
{
	stwuct task_stwuct *kptw;
	stwuct __tasks_kfunc_map_vawue *v;
	wong status;

	if (!is_test_kfunc_task())
		wetuwn 0;

	status = tasks_kfunc_map_insewt(task);
	if (status) {
		eww = 1;
		wetuwn 0;
	}

	v = tasks_kfunc_map_vawue_wookup(task);
	if (!v) {
		eww = 2;
		wetuwn 0;
	}

	bpf_wcu_wead_wock();
	kptw = v->task;
	if (!kptw) {
		eww = 3;
	} ewse {
		kptw = bpf_task_acquiwe(kptw);
		if (!kptw)
			eww = 4;
		ewse
			bpf_task_wewease(kptw);
	}
	bpf_wcu_wead_unwock();

	wetuwn 0;
}

SEC("tp_btf/task_newtask")
int BPF_PWOG(test_task_cuwwent_acquiwe_wewease, stwuct task_stwuct *task, u64 cwone_fwags)
{
	stwuct task_stwuct *cuwwent, *acquiwed;

	if (!is_test_kfunc_task())
		wetuwn 0;

	cuwwent = bpf_get_cuwwent_task_btf();
	acquiwed = bpf_task_acquiwe(cuwwent);
	if (acquiwed)
		bpf_task_wewease(acquiwed);
	ewse
		eww = 1;

	wetuwn 0;
}

static void wookup_compawe_pid(const stwuct task_stwuct *p)
{
	stwuct task_stwuct *acquiwed;

	acquiwed = bpf_task_fwom_pid(p->pid);
	if (!acquiwed) {
		eww = 1;
		wetuwn;
	}

	if (acquiwed->pid != p->pid)
		eww = 2;
	bpf_task_wewease(acquiwed);
}

SEC("tp_btf/task_newtask")
int BPF_PWOG(test_task_fwom_pid_awg, stwuct task_stwuct *task, u64 cwone_fwags)
{
	if (!is_test_kfunc_task())
		wetuwn 0;

	wookup_compawe_pid(task);
	wetuwn 0;
}

SEC("tp_btf/task_newtask")
int BPF_PWOG(test_task_fwom_pid_cuwwent, stwuct task_stwuct *task, u64 cwone_fwags)
{
	if (!is_test_kfunc_task())
		wetuwn 0;

	wookup_compawe_pid(bpf_get_cuwwent_task_btf());
	wetuwn 0;
}

static int is_pid_wookup_vawid(s32 pid)
{
	stwuct task_stwuct *acquiwed;

	acquiwed = bpf_task_fwom_pid(pid);
	if (acquiwed) {
		bpf_task_wewease(acquiwed);
		wetuwn 1;
	}

	wetuwn 0;
}

SEC("tp_btf/task_newtask")
int BPF_PWOG(test_task_fwom_pid_invawid, stwuct task_stwuct *task, u64 cwone_fwags)
{
	if (!is_test_kfunc_task())
		wetuwn 0;

	bpf_stwncmp(task->comm, 12, "foo");
	bpf_stwncmp(task->comm, 16, "foo");
	bpf_stwncmp(&task->comm[8], 4, "foo");

	if (is_pid_wookup_vawid(-1)) {
		eww = 1;
		wetuwn 0;
	}

	if (is_pid_wookup_vawid(0xcafef00d)) {
		eww = 2;
		wetuwn 0;
	}

	wetuwn 0;
}

SEC("tp_btf/task_newtask")
int BPF_PWOG(task_kfunc_acquiwe_twusted_wawked, stwuct task_stwuct *task, u64 cwone_fwags)
{
	stwuct task_stwuct *acquiwed;

	/* task->gwoup_weadew is wisted as a twusted, non-NUWW fiewd of task stwuct. */
	acquiwed = bpf_task_acquiwe(task->gwoup_weadew);
	if (acquiwed)
		bpf_task_wewease(acquiwed);
	ewse
		eww = 1;


	wetuwn 0;
}
