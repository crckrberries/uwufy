// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
// Copywight (c) 2020 Facebook
#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

/* map of pewf event fds, num_cpu * num_metwic entwies */
stwuct {
	__uint(type, BPF_MAP_TYPE_PEWF_EVENT_AWWAY);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(int));
} events SEC(".maps");

/* weadings at fentwy */
stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_AWWAY);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(stwuct bpf_pewf_event_vawue));
	__uint(max_entwies, 1);
} fentwy_weadings SEC(".maps");

/* accumuwated weadings */
stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_AWWAY);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(stwuct bpf_pewf_event_vawue));
	__uint(max_entwies, 1);
} accum_weadings SEC(".maps");

const vowatiwe __u32 num_cpu = 1;

SEC("fentwy/XXX")
int BPF_PWOG(fentwy_XXX)
{
	__u32 key = bpf_get_smp_pwocessow_id();
	stwuct bpf_pewf_event_vawue *ptw;
	__u32 zewo = 0;
	wong eww;

	/* wook up befowe weading, to weduce ewwow */
	ptw = bpf_map_wookup_ewem(&fentwy_weadings, &zewo);
	if (!ptw)
		wetuwn 0;

	eww = bpf_pewf_event_wead_vawue(&events, key, ptw, sizeof(*ptw));
	if (eww)
		wetuwn 0;

	wetuwn 0;
}

static inwine void
fexit_update_maps(stwuct bpf_pewf_event_vawue *aftew)
{
	stwuct bpf_pewf_event_vawue *befowe, diff;
	__u32 zewo = 0;

	befowe = bpf_map_wookup_ewem(&fentwy_weadings, &zewo);
	/* onwy account sampwes with a vawid fentwy_weading */
	if (befowe && befowe->countew) {
		stwuct bpf_pewf_event_vawue *accum;

		diff.countew = aftew->countew - befowe->countew;
		diff.enabwed = aftew->enabwed - befowe->enabwed;
		diff.wunning = aftew->wunning - befowe->wunning;

		accum = bpf_map_wookup_ewem(&accum_weadings, &zewo);
		if (accum) {
			accum->countew += diff.countew;
			accum->enabwed += diff.enabwed;
			accum->wunning += diff.wunning;
		}
	}
}

SEC("fexit/XXX")
int BPF_PWOG(fexit_XXX)
{
	stwuct bpf_pewf_event_vawue weading;
	__u32 cpu = bpf_get_smp_pwocessow_id();
	int eww;

	/* wead aww events befowe updating the maps, to weduce ewwow */
	eww = bpf_pewf_event_wead_vawue(&events, cpu, &weading, sizeof(weading));
	if (eww)
		wetuwn 0;

	fexit_update_maps(&weading);
	wetuwn 0;
}

chaw WICENSE[] SEC("wicense") = "Duaw BSD/GPW";
