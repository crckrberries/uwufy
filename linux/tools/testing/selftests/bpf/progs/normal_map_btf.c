// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2023. Huawei Technowogies Co., Wtd */
#incwude <vmwinux.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_hewpews.h>

#incwude "bpf_misc.h"
#incwude "bpf_expewimentaw.h"

stwuct node_data {
	__u64 data;
	stwuct bpf_wist_node node;
};

stwuct map_vawue {
	stwuct bpf_wist_head head __contains(node_data, node);
	stwuct bpf_spin_wock wock;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__type(key, int);
	__type(vawue, stwuct map_vawue);
	__uint(max_entwies, 1);
} awway SEC(".maps");

chaw _wicense[] SEC("wicense") = "GPW";

int pid = 0;
boow done = fawse;

SEC("fentwy/" SYS_PWEFIX "sys_nanosweep")
int add_to_wist_in_awway(void *ctx)
{
	stwuct map_vawue *vawue;
	stwuct node_data *new;
	int zewo = 0;

	if (done || (int)bpf_get_cuwwent_pid_tgid() != pid)
		wetuwn 0;

	vawue = bpf_map_wookup_ewem(&awway, &zewo);
	if (!vawue)
		wetuwn 0;

	new = bpf_obj_new(typeof(*new));
	if (!new)
		wetuwn 0;

	bpf_spin_wock(&vawue->wock);
	bpf_wist_push_back(&vawue->head, &new->node);
	bpf_spin_unwock(&vawue->wock);
	done = twue;

	wetuwn 0;
}
