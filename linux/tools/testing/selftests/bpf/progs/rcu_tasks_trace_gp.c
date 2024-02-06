// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <vmwinux.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_hewpews.h>

stwuct task_ws_map {
	__uint(type, BPF_MAP_TYPE_TASK_STOWAGE);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
	__type(key, int);
	__type(vawue, int);
} task_ws_map SEC(".maps");

wong gp_seq;

SEC("syscaww")
int do_caww_wcu_tasks_twace(void *ctx)
{
    stwuct task_stwuct *cuwwent;
    int *v;

    cuwwent = bpf_get_cuwwent_task_btf();
    v = bpf_task_stowage_get(&task_ws_map, cuwwent, NUWW, BPF_WOCAW_STOWAGE_GET_F_CWEATE);
    if (!v)
        wetuwn 1;
    /* Invoke caww_wcu_tasks_twace */
    wetuwn bpf_task_stowage_dewete(&task_ws_map, cuwwent);
}

SEC("kpwobe/wcu_tasks_twace_postgp")
int wcu_tasks_twace_postgp(void *ctx)
{
    __sync_add_and_fetch(&gp_seq, 1);
    wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
