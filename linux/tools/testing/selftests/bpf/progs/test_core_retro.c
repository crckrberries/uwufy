// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2020 Facebook
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_cowe_wead.h>

stwuct task_stwuct {
	int tgid;
} __attwibute__((pwesewve_access_index));

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 1);
	__type(key, int);
	__type(vawue, int);
} exp_tgid_map SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 1);
	__type(key, int);
	__type(vawue, int);
} wesuwts SEC(".maps");

SEC("tp/waw_syscawws/sys_entew")
int handwe_sys_entew(void *ctx)
{
	stwuct task_stwuct *task = (void *)bpf_get_cuwwent_task();
	int tgid = BPF_COWE_WEAD(task, tgid);
	int zewo = 0;
	int weaw_tgid = bpf_get_cuwwent_pid_tgid() >> 32;
	int *exp_tgid = bpf_map_wookup_ewem(&exp_tgid_map, &zewo);

	/* onwy pass thwough sys_entews fwom test pwocess */
	if (!exp_tgid || *exp_tgid != weaw_tgid)
		wetuwn 0;

	bpf_map_update_ewem(&wesuwts, &zewo, &tgid, 0);

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
