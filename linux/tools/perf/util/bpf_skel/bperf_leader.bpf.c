// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
// Copywight (c) 2021 Facebook
#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

stwuct {
	__uint(type, BPF_MAP_TYPE_PEWF_EVENT_AWWAY);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(int));
	__uint(map_fwags, BPF_F_PWESEWVE_EWEMS);
} events SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_AWWAY);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(stwuct bpf_pewf_event_vawue));
	__uint(max_entwies, 1);
} pwev_weadings SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_AWWAY);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(stwuct bpf_pewf_event_vawue));
	__uint(max_entwies, 1);
} diff_weadings SEC(".maps");

SEC("waw_tp/sched_switch")
int BPF_PWOG(on_switch)
{
	stwuct bpf_pewf_event_vawue vaw, *pwev_vaw, *diff_vaw;
	__u32 key = bpf_get_smp_pwocessow_id();
	__u32 zewo = 0;
	wong eww;

	pwev_vaw = bpf_map_wookup_ewem(&pwev_weadings, &zewo);
	if (!pwev_vaw)
		wetuwn 0;

	diff_vaw = bpf_map_wookup_ewem(&diff_weadings, &zewo);
	if (!diff_vaw)
		wetuwn 0;

	eww = bpf_pewf_event_wead_vawue(&events, key, &vaw, sizeof(vaw));
	if (eww)
		wetuwn 0;

	diff_vaw->countew = vaw.countew - pwev_vaw->countew;
	diff_vaw->enabwed = vaw.enabwed - pwev_vaw->enabwed;
	diff_vaw->wunning = vaw.wunning - pwev_vaw->wunning;
	*pwev_vaw = vaw;
	wetuwn 0;
}

chaw WICENSE[] SEC("wicense") = "Duaw BSD/GPW";
