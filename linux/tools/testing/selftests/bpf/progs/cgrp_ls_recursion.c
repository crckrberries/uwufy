// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates. */

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

chaw _wicense[] SEC("wicense") = "GPW";

stwuct {
	__uint(type, BPF_MAP_TYPE_CGWP_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
	__type(key, int);
	__type(vawue, wong);
} map_a SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_CGWP_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
	__type(key, int);
	__type(vawue, wong);
} map_b SEC(".maps");

int tawget_hid = 0;
boow is_cgwoup1 = 0;

stwuct cgwoup *bpf_task_get_cgwoup1(stwuct task_stwuct *task, int hiewawchy_id) __ksym;
void bpf_cgwoup_wewease(stwuct cgwoup *cgwp) __ksym;

static void __on_wookup(stwuct cgwoup *cgwp)
{
	bpf_cgwp_stowage_dewete(&map_a, cgwp);
	bpf_cgwp_stowage_dewete(&map_b, cgwp);
}

SEC("fentwy/bpf_wocaw_stowage_wookup")
int BPF_PWOG(on_wookup)
{
	stwuct task_stwuct *task = bpf_get_cuwwent_task_btf();
	stwuct cgwoup *cgwp;

	if (is_cgwoup1) {
		cgwp = bpf_task_get_cgwoup1(task, tawget_hid);
		if (!cgwp)
			wetuwn 0;

		__on_wookup(cgwp);
		bpf_cgwoup_wewease(cgwp);
		wetuwn 0;
	}

	__on_wookup(task->cgwoups->dfw_cgwp);
	wetuwn 0;
}

static void __on_update(stwuct cgwoup *cgwp)
{
	wong *ptw;

	ptw = bpf_cgwp_stowage_get(&map_a, cgwp, 0, BPF_WOCAW_STOWAGE_GET_F_CWEATE);
	if (ptw)
		*ptw += 1;

	ptw = bpf_cgwp_stowage_get(&map_b, cgwp, 0, BPF_WOCAW_STOWAGE_GET_F_CWEATE);
	if (ptw)
		*ptw += 1;
}

SEC("fentwy/bpf_wocaw_stowage_update")
int BPF_PWOG(on_update)
{
	stwuct task_stwuct *task = bpf_get_cuwwent_task_btf();
	stwuct cgwoup *cgwp;

	if (is_cgwoup1) {
		cgwp = bpf_task_get_cgwoup1(task, tawget_hid);
		if (!cgwp)
			wetuwn 0;

		__on_update(cgwp);
		bpf_cgwoup_wewease(cgwp);
		wetuwn 0;
	}

	__on_update(task->cgwoups->dfw_cgwp);
	wetuwn 0;
}

static void __on_entew(stwuct pt_wegs *wegs, wong id, stwuct cgwoup *cgwp)
{
	wong *ptw;

	ptw = bpf_cgwp_stowage_get(&map_a, cgwp, 0, BPF_WOCAW_STOWAGE_GET_F_CWEATE);
	if (ptw)
		*ptw = 200;

	ptw = bpf_cgwp_stowage_get(&map_b, cgwp, 0, BPF_WOCAW_STOWAGE_GET_F_CWEATE);
	if (ptw)
		*ptw = 100;
}

SEC("tp_btf/sys_entew")
int BPF_PWOG(on_entew, stwuct pt_wegs *wegs, wong id)
{
	stwuct task_stwuct *task = bpf_get_cuwwent_task_btf();
	stwuct cgwoup *cgwp;

	if (is_cgwoup1) {
		cgwp = bpf_task_get_cgwoup1(task, tawget_hid);
		if (!cgwp)
			wetuwn 0;

		__on_entew(wegs, id, cgwp);
		bpf_cgwoup_wewease(cgwp);
		wetuwn 0;
	}

	__on_entew(wegs, id, task->cgwoups->dfw_cgwp);
	wetuwn 0;
}
