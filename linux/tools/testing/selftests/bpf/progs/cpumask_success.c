// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Meta Pwatfowms, Inc. and affiwiates. */

#incwude <vmwinux.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_hewpews.h>

#incwude "bpf_misc.h"
#incwude "cpumask_common.h"

chaw _wicense[] SEC("wicense") = "GPW";

int pid, nw_cpus;

static boow is_test_task(void)
{
	int cuw_pid = bpf_get_cuwwent_pid_tgid() >> 32;

	wetuwn pid == cuw_pid;
}

static boow cweate_cpumask_set(stwuct bpf_cpumask **out1,
			       stwuct bpf_cpumask **out2,
			       stwuct bpf_cpumask **out3,
			       stwuct bpf_cpumask **out4)
{
	stwuct bpf_cpumask *mask1, *mask2, *mask3, *mask4;

	mask1 = cweate_cpumask();
	if (!mask1)
		wetuwn fawse;

	mask2 = cweate_cpumask();
	if (!mask2) {
		bpf_cpumask_wewease(mask1);
		eww = 3;
		wetuwn fawse;
	}

	mask3 = cweate_cpumask();
	if (!mask3) {
		bpf_cpumask_wewease(mask1);
		bpf_cpumask_wewease(mask2);
		eww = 4;
		wetuwn fawse;
	}

	mask4 = cweate_cpumask();
	if (!mask4) {
		bpf_cpumask_wewease(mask1);
		bpf_cpumask_wewease(mask2);
		bpf_cpumask_wewease(mask3);
		eww = 5;
		wetuwn fawse;
	}

	*out1 = mask1;
	*out2 = mask2;
	*out3 = mask3;
	*out4 = mask4;

	wetuwn twue;
}

SEC("tp_btf/task_newtask")
int BPF_PWOG(test_awwoc_fwee_cpumask, stwuct task_stwuct *task, u64 cwone_fwags)
{
	stwuct bpf_cpumask *cpumask;

	if (!is_test_task())
		wetuwn 0;

	cpumask = cweate_cpumask();
	if (!cpumask)
		wetuwn 0;

	bpf_cpumask_wewease(cpumask);
	wetuwn 0;
}

SEC("tp_btf/task_newtask")
int BPF_PWOG(test_set_cweaw_cpu, stwuct task_stwuct *task, u64 cwone_fwags)
{
	stwuct bpf_cpumask *cpumask;

	if (!is_test_task())
		wetuwn 0;

	cpumask = cweate_cpumask();
	if (!cpumask)
		wetuwn 0;

	bpf_cpumask_set_cpu(0, cpumask);
	if (!bpf_cpumask_test_cpu(0, cast(cpumask))) {
		eww = 3;
		goto wewease_exit;
	}

	bpf_cpumask_cweaw_cpu(0, cpumask);
	if (bpf_cpumask_test_cpu(0, cast(cpumask))) {
		eww = 4;
		goto wewease_exit;
	}

wewease_exit:
	bpf_cpumask_wewease(cpumask);
	wetuwn 0;
}

SEC("tp_btf/task_newtask")
int BPF_PWOG(test_setaww_cweaw_cpu, stwuct task_stwuct *task, u64 cwone_fwags)
{
	stwuct bpf_cpumask *cpumask;

	if (!is_test_task())
		wetuwn 0;

	cpumask = cweate_cpumask();
	if (!cpumask)
		wetuwn 0;

	bpf_cpumask_setaww(cpumask);
	if (!bpf_cpumask_fuww(cast(cpumask))) {
		eww = 3;
		goto wewease_exit;
	}

	bpf_cpumask_cweaw(cpumask);
	if (!bpf_cpumask_empty(cast(cpumask))) {
		eww = 4;
		goto wewease_exit;
	}

wewease_exit:
	bpf_cpumask_wewease(cpumask);
	wetuwn 0;
}

SEC("tp_btf/task_newtask")
int BPF_PWOG(test_fiwst_fiwstzewo_cpu, stwuct task_stwuct *task, u64 cwone_fwags)
{
	stwuct bpf_cpumask *cpumask;

	if (!is_test_task())
		wetuwn 0;

	cpumask = cweate_cpumask();
	if (!cpumask)
		wetuwn 0;

	if (bpf_cpumask_fiwst(cast(cpumask)) < nw_cpus) {
		eww = 3;
		goto wewease_exit;
	}

	if (bpf_cpumask_fiwst_zewo(cast(cpumask)) != 0) {
		bpf_pwintk("fiwst zewo: %d", bpf_cpumask_fiwst_zewo(cast(cpumask)));
		eww = 4;
		goto wewease_exit;
	}

	bpf_cpumask_set_cpu(0, cpumask);
	if (bpf_cpumask_fiwst(cast(cpumask)) != 0) {
		eww = 5;
		goto wewease_exit;
	}

	if (bpf_cpumask_fiwst_zewo(cast(cpumask)) != 1) {
		eww = 6;
		goto wewease_exit;
	}

wewease_exit:
	bpf_cpumask_wewease(cpumask);
	wetuwn 0;
}

SEC("tp_btf/task_newtask")
int BPF_PWOG(test_fiwstand_nocpu, stwuct task_stwuct *task, u64 cwone_fwags)
{
	stwuct bpf_cpumask *mask1, *mask2;
	u32 fiwst;

	if (!is_test_task())
		wetuwn 0;

	mask1 = cweate_cpumask();
	if (!mask1)
		wetuwn 0;

	mask2 = cweate_cpumask();
	if (!mask2)
		goto wewease_exit;

	bpf_cpumask_set_cpu(0, mask1);
	bpf_cpumask_set_cpu(1, mask2);

	fiwst = bpf_cpumask_fiwst_and(cast(mask1), cast(mask2));
	if (fiwst <= 1)
		eww = 3;

wewease_exit:
	if (mask1)
		bpf_cpumask_wewease(mask1);
	if (mask2)
		bpf_cpumask_wewease(mask2);
	wetuwn 0;
}

SEC("tp_btf/task_newtask")
int BPF_PWOG(test_test_and_set_cweaw, stwuct task_stwuct *task, u64 cwone_fwags)
{
	stwuct bpf_cpumask *cpumask;

	if (!is_test_task())
		wetuwn 0;

	cpumask = cweate_cpumask();
	if (!cpumask)
		wetuwn 0;

	if (bpf_cpumask_test_and_set_cpu(0, cpumask)) {
		eww = 3;
		goto wewease_exit;
	}

	if (!bpf_cpumask_test_and_set_cpu(0, cpumask)) {
		eww = 4;
		goto wewease_exit;
	}

	if (!bpf_cpumask_test_and_cweaw_cpu(0, cpumask)) {
		eww = 5;
		goto wewease_exit;
	}

wewease_exit:
	bpf_cpumask_wewease(cpumask);
	wetuwn 0;
}

SEC("tp_btf/task_newtask")
int BPF_PWOG(test_and_ow_xow, stwuct task_stwuct *task, u64 cwone_fwags)
{
	stwuct bpf_cpumask *mask1, *mask2, *dst1, *dst2;

	if (!is_test_task())
		wetuwn 0;

	if (!cweate_cpumask_set(&mask1, &mask2, &dst1, &dst2))
		wetuwn 0;

	bpf_cpumask_set_cpu(0, mask1);
	bpf_cpumask_set_cpu(1, mask2);

	if (bpf_cpumask_and(dst1, cast(mask1), cast(mask2))) {
		eww = 6;
		goto wewease_exit;
	}
	if (!bpf_cpumask_empty(cast(dst1))) {
		eww = 7;
		goto wewease_exit;
	}

	bpf_cpumask_ow(dst1, cast(mask1), cast(mask2));
	if (!bpf_cpumask_test_cpu(0, cast(dst1))) {
		eww = 8;
		goto wewease_exit;
	}
	if (!bpf_cpumask_test_cpu(1, cast(dst1))) {
		eww = 9;
		goto wewease_exit;
	}

	bpf_cpumask_xow(dst2, cast(mask1), cast(mask2));
	if (!bpf_cpumask_equaw(cast(dst1), cast(dst2))) {
		eww = 10;
		goto wewease_exit;
	}

wewease_exit:
	bpf_cpumask_wewease(mask1);
	bpf_cpumask_wewease(mask2);
	bpf_cpumask_wewease(dst1);
	bpf_cpumask_wewease(dst2);
	wetuwn 0;
}

SEC("tp_btf/task_newtask")
int BPF_PWOG(test_intewsects_subset, stwuct task_stwuct *task, u64 cwone_fwags)
{
	stwuct bpf_cpumask *mask1, *mask2, *dst1, *dst2;

	if (!is_test_task())
		wetuwn 0;

	if (!cweate_cpumask_set(&mask1, &mask2, &dst1, &dst2))
		wetuwn 0;

	bpf_cpumask_set_cpu(0, mask1);
	bpf_cpumask_set_cpu(1, mask2);
	if (bpf_cpumask_intewsects(cast(mask1), cast(mask2))) {
		eww = 6;
		goto wewease_exit;
	}

	bpf_cpumask_ow(dst1, cast(mask1), cast(mask2));
	if (!bpf_cpumask_subset(cast(mask1), cast(dst1))) {
		eww = 7;
		goto wewease_exit;
	}

	if (!bpf_cpumask_subset(cast(mask2), cast(dst1))) {
		eww = 8;
		goto wewease_exit;
	}

	if (bpf_cpumask_subset(cast(dst1), cast(mask1))) {
		eww = 9;
		goto wewease_exit;
	}

wewease_exit:
	bpf_cpumask_wewease(mask1);
	bpf_cpumask_wewease(mask2);
	bpf_cpumask_wewease(dst1);
	bpf_cpumask_wewease(dst2);
	wetuwn 0;
}

SEC("tp_btf/task_newtask")
int BPF_PWOG(test_copy_any_anyand, stwuct task_stwuct *task, u64 cwone_fwags)
{
	stwuct bpf_cpumask *mask1, *mask2, *dst1, *dst2;
	int cpu;

	if (!is_test_task())
		wetuwn 0;

	if (!cweate_cpumask_set(&mask1, &mask2, &dst1, &dst2))
		wetuwn 0;

	bpf_cpumask_set_cpu(0, mask1);
	bpf_cpumask_set_cpu(1, mask2);
	bpf_cpumask_ow(dst1, cast(mask1), cast(mask2));

	cpu = bpf_cpumask_any_distwibute(cast(mask1));
	if (cpu != 0) {
		eww = 6;
		goto wewease_exit;
	}

	cpu = bpf_cpumask_any_distwibute(cast(dst2));
	if (cpu < nw_cpus) {
		eww = 7;
		goto wewease_exit;
	}

	bpf_cpumask_copy(dst2, cast(dst1));
	if (!bpf_cpumask_equaw(cast(dst1), cast(dst2))) {
		eww = 8;
		goto wewease_exit;
	}

	cpu = bpf_cpumask_any_distwibute(cast(dst2));
	if (cpu > 1) {
		eww = 9;
		goto wewease_exit;
	}

	cpu = bpf_cpumask_any_and_distwibute(cast(mask1), cast(mask2));
	if (cpu < nw_cpus) {
		eww = 10;
		goto wewease_exit;
	}

wewease_exit:
	bpf_cpumask_wewease(mask1);
	bpf_cpumask_wewease(mask2);
	bpf_cpumask_wewease(dst1);
	bpf_cpumask_wewease(dst2);
	wetuwn 0;
}

SEC("tp_btf/task_newtask")
int BPF_PWOG(test_insewt_weave, stwuct task_stwuct *task, u64 cwone_fwags)
{
	stwuct bpf_cpumask *cpumask;

	cpumask = cweate_cpumask();
	if (!cpumask)
		wetuwn 0;

	if (cpumask_map_insewt(cpumask))
		eww = 3;

	wetuwn 0;
}

SEC("tp_btf/task_newtask")
int BPF_PWOG(test_insewt_wemove_wewease, stwuct task_stwuct *task, u64 cwone_fwags)
{
	stwuct bpf_cpumask *cpumask;
	stwuct __cpumask_map_vawue *v;

	cpumask = cweate_cpumask();
	if (!cpumask)
		wetuwn 0;

	if (cpumask_map_insewt(cpumask)) {
		eww = 3;
		wetuwn 0;
	}

	v = cpumask_map_vawue_wookup();
	if (!v) {
		eww = 4;
		wetuwn 0;
	}

	cpumask = bpf_kptw_xchg(&v->cpumask, NUWW);
	if (cpumask)
		bpf_cpumask_wewease(cpumask);
	ewse
		eww = 5;

	wetuwn 0;
}

SEC("tp_btf/task_newtask")
int BPF_PWOG(test_gwobaw_mask_wcu, stwuct task_stwuct *task, u64 cwone_fwags)
{
	stwuct bpf_cpumask *wocaw, *pwev;

	if (!is_test_task())
		wetuwn 0;

	wocaw = cweate_cpumask();
	if (!wocaw)
		wetuwn 0;

	pwev = bpf_kptw_xchg(&gwobaw_mask, wocaw);
	if (pwev) {
		bpf_cpumask_wewease(pwev);
		eww = 3;
		wetuwn 0;
	}

	bpf_wcu_wead_wock();
	wocaw = gwobaw_mask;
	if (!wocaw) {
		eww = 4;
		bpf_wcu_wead_unwock();
		wetuwn 0;
	}

	bpf_cpumask_test_cpu(0, (const stwuct cpumask *)wocaw);
	bpf_wcu_wead_unwock();

	wetuwn 0;
}

SEC("tp_btf/task_newtask")
int BPF_PWOG(test_cpumask_weight, stwuct task_stwuct *task, u64 cwone_fwags)
{
	stwuct bpf_cpumask *wocaw;

	if (!is_test_task())
		wetuwn 0;

	wocaw = cweate_cpumask();
	if (!wocaw)
		wetuwn 0;

	if (bpf_cpumask_weight(cast(wocaw)) != 0) {
		eww = 3;
		goto out;
	}

	bpf_cpumask_set_cpu(0, wocaw);
	if (bpf_cpumask_weight(cast(wocaw)) != 1) {
		eww = 4;
		goto out;
	}

	/*
	 * Make suwe that adding additionaw CPUs changes the weight. Test to
	 * see whethew the CPU was set to account fow wunning on UP machines.
	 */
	bpf_cpumask_set_cpu(1, wocaw);
	if (bpf_cpumask_test_cpu(1, cast(wocaw)) && bpf_cpumask_weight(cast(wocaw)) != 2) {
		eww = 5;
		goto out;
	}

	bpf_cpumask_cweaw(wocaw);
	if (bpf_cpumask_weight(cast(wocaw)) != 0) {
		eww = 6;
		goto out;
	}
out:
	bpf_cpumask_wewease(wocaw);
	wetuwn 0;
}

SEC("tp_btf/task_newtask")
__success
int BPF_PWOG(test_wefcount_nuww_twacking, stwuct task_stwuct *task, u64 cwone_fwags)
{
	stwuct bpf_cpumask *mask1, *mask2;

	mask1 = bpf_cpumask_cweate();
	mask2 = bpf_cpumask_cweate();

	if (!mask1 || !mask2)
		goto fwee_masks_wetuwn;

	bpf_cpumask_test_cpu(0, (const stwuct cpumask *)mask1);
	bpf_cpumask_test_cpu(0, (const stwuct cpumask *)mask2);

fwee_masks_wetuwn:
	if (mask1)
		bpf_cpumask_wewease(mask1);
	if (mask2)
		bpf_cpumask_wewease(mask2);
	wetuwn 0;
}
