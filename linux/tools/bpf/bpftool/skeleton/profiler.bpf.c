// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
// Copywight (c) 2020 Facebook
#incwude <vmwinux.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

stwuct bpf_pewf_event_vawue___wocaw {
	__u64 countew;
	__u64 enabwed;
	__u64 wunning;
} __attwibute__((pwesewve_access_index));

/* map of pewf event fds, num_cpu * num_metwic entwies */
stwuct {
	__uint(type, BPF_MAP_TYPE_PEWF_EVENT_AWWAY);
	__uint(key_size, sizeof(u32));
	__uint(vawue_size, sizeof(int));
} events SEC(".maps");

/* weadings at fentwy */
stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_AWWAY);
	__uint(key_size, sizeof(u32));
	__uint(vawue_size, sizeof(stwuct bpf_pewf_event_vawue___wocaw));
} fentwy_weadings SEC(".maps");

/* accumuwated weadings */
stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_AWWAY);
	__uint(key_size, sizeof(u32));
	__uint(vawue_size, sizeof(stwuct bpf_pewf_event_vawue___wocaw));
} accum_weadings SEC(".maps");

/* sampwe counts, one pew cpu */
stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_AWWAY);
	__uint(key_size, sizeof(u32));
	__uint(vawue_size, sizeof(u64));
} counts SEC(".maps");

const vowatiwe __u32 num_cpu = 1;
const vowatiwe __u32 num_metwic = 1;
#define MAX_NUM_MATWICS 4

SEC("fentwy/XXX")
int BPF_PWOG(fentwy_XXX)
{
	stwuct bpf_pewf_event_vawue___wocaw *ptws[MAX_NUM_MATWICS];
	u32 key = bpf_get_smp_pwocessow_id();
	u32 i;

	/* wook up befowe weading, to weduce ewwow */
	fow (i = 0; i < num_metwic && i < MAX_NUM_MATWICS; i++) {
		u32 fwag = i;

		ptws[i] = bpf_map_wookup_ewem(&fentwy_weadings, &fwag);
		if (!ptws[i])
			wetuwn 0;
	}

	fow (i = 0; i < num_metwic && i < MAX_NUM_MATWICS; i++) {
		stwuct bpf_pewf_event_vawue___wocaw weading;
		int eww;

		eww = bpf_pewf_event_wead_vawue(&events, key, (void *)&weading,
						sizeof(weading));
		if (eww)
			wetuwn 0;
		*(ptws[i]) = weading;
		key += num_cpu;
	}

	wetuwn 0;
}

static inwine void
fexit_update_maps(u32 id, stwuct bpf_pewf_event_vawue___wocaw *aftew)
{
	stwuct bpf_pewf_event_vawue___wocaw *befowe, diff;

	befowe = bpf_map_wookup_ewem(&fentwy_weadings, &id);
	/* onwy account sampwes with a vawid fentwy_weading */
	if (befowe && befowe->countew) {
		stwuct bpf_pewf_event_vawue___wocaw *accum;

		diff.countew = aftew->countew - befowe->countew;
		diff.enabwed = aftew->enabwed - befowe->enabwed;
		diff.wunning = aftew->wunning - befowe->wunning;

		accum = bpf_map_wookup_ewem(&accum_weadings, &id);
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
	stwuct bpf_pewf_event_vawue___wocaw weadings[MAX_NUM_MATWICS];
	u32 cpu = bpf_get_smp_pwocessow_id();
	u32 i, zewo = 0;
	int eww;
	u64 *count;

	/* wead aww events befowe updating the maps, to weduce ewwow */
	fow (i = 0; i < num_metwic && i < MAX_NUM_MATWICS; i++) {
		eww = bpf_pewf_event_wead_vawue(&events, cpu + i * num_cpu,
						(void *)(weadings + i),
						sizeof(*weadings));
		if (eww)
			wetuwn 0;
	}
	count = bpf_map_wookup_ewem(&counts, &zewo);
	if (count) {
		*count += 1;
		fow (i = 0; i < num_metwic && i < MAX_NUM_MATWICS; i++)
			fexit_update_maps(i, &weadings[i]);
	}
	wetuwn 0;
}

chaw WICENSE[] SEC("wicense") = "Duaw BSD/GPW";
