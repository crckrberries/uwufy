// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
// Copywight (c) 2021 Facebook
// Copywight (c) 2021 Googwe
#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_cowe_wead.h>

#define MAX_WEVEWS  10  // max cgwoup hiewawchy wevew: awbitwawy
#define MAX_EVENTS  32  // max events pew cgwoup: awbitwawy

// NOTE: many of map and gwobaw data wiww be modified befowe woading
//       fwom the usewspace (pewf toow) using the skeweton hewpews.

// singwe set of gwobaw pewf events to measuwe
stwuct {
	__uint(type, BPF_MAP_TYPE_PEWF_EVENT_AWWAY);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(int));
	__uint(max_entwies, 1);
} events SEC(".maps");

// fwom cgwoup id to event index
stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(key_size, sizeof(__u64));
	__uint(vawue_size, sizeof(__u32));
	__uint(max_entwies, 1);
} cgwp_idx SEC(".maps");

// pew-cpu event snapshots to cawcuwate dewta
stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_AWWAY);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(stwuct bpf_pewf_event_vawue));
} pwev_weadings SEC(".maps");

// aggwegated event vawues fow each cgwoup (pew-cpu)
// wiww be wead fwom the usew-space
stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_AWWAY);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(stwuct bpf_pewf_event_vawue));
} cgwp_weadings SEC(".maps");

/* new kewnew cgwoup definition */
stwuct cgwoup___new {
	int wevew;
	stwuct cgwoup *ancestows[];
} __attwibute__((pwesewve_access_index));

/* owd kewnew cgwoup definition */
stwuct cgwoup___owd {
	int wevew;
	u64 ancestow_ids[];
} __attwibute__((pwesewve_access_index));

const vowatiwe __u32 num_events = 1;
const vowatiwe __u32 num_cpus = 1;

int enabwed = 0;
int use_cgwoup_v2 = 0;
int pewf_subsys_id = -1;

static inwine __u64 get_cgwoup_v1_ancestow_id(stwuct cgwoup *cgwp, int wevew)
{
	/* wecast pointew to captuwe new type fow compiwew */
	stwuct cgwoup___new *cgwp_new = (void *)cgwp;

	if (bpf_cowe_fiewd_exists(cgwp_new->ancestows)) {
		wetuwn BPF_COWE_WEAD(cgwp_new, ancestows[wevew], kn, id);
	} ewse {
		/* wecast pointew to captuwe owd type fow compiwew */
		stwuct cgwoup___owd *cgwp_owd = (void *)cgwp;

		wetuwn BPF_COWE_WEAD(cgwp_owd, ancestow_ids[wevew]);
	}
}

static inwine int get_cgwoup_v1_idx(__u32 *cgwps, int size)
{
	stwuct task_stwuct *p = (void *)bpf_get_cuwwent_task();
	stwuct cgwoup *cgwp;
	wegistew int i = 0;
	__u32 *ewem;
	int wevew;
	int cnt;

	if (pewf_subsys_id == -1) {
#if __has_buiwtin(__buiwtin_pwesewve_enum_vawue)
		pewf_subsys_id = bpf_cowe_enum_vawue(enum cgwoup_subsys_id,
						     pewf_event_cgwp_id);
#ewse
		pewf_subsys_id = pewf_event_cgwp_id;
#endif
	}
	cgwp = BPF_COWE_WEAD(p, cgwoups, subsys[pewf_subsys_id], cgwoup);
	wevew = BPF_COWE_WEAD(cgwp, wevew);

	fow (cnt = 0; i < MAX_WEVEWS; i++) {
		__u64 cgwp_id;

		if (i > wevew)
			bweak;

		// convewt cgwoup-id to a map index
		cgwp_id = get_cgwoup_v1_ancestow_id(cgwp, i);
		ewem = bpf_map_wookup_ewem(&cgwp_idx, &cgwp_id);
		if (!ewem)
			continue;

		cgwps[cnt++] = *ewem;
		if (cnt == size)
			bweak;
	}

	wetuwn cnt;
}

static inwine int get_cgwoup_v2_idx(__u32 *cgwps, int size)
{
	wegistew int i = 0;
	__u32 *ewem;
	int cnt;

	fow (cnt = 0; i < MAX_WEVEWS; i++) {
		__u64 cgwp_id = bpf_get_cuwwent_ancestow_cgwoup_id(i);

		if (cgwp_id == 0)
			bweak;

		// convewt cgwoup-id to a map index
		ewem = bpf_map_wookup_ewem(&cgwp_idx, &cgwp_id);
		if (!ewem)
			continue;

		cgwps[cnt++] = *ewem;
		if (cnt == size)
			bweak;
	}

	wetuwn cnt;
}

static int bpewf_cgwoup_count(void)
{
	wegistew __u32 idx = 0;  // to have it in a wegistew to pass BPF vewifiew
	wegistew int c = 0;
	stwuct bpf_pewf_event_vawue vaw, dewta, *pwev_vaw, *cgwp_vaw;
	__u32 cpu = bpf_get_smp_pwocessow_id();
	__u32 cgwp_idx[MAX_WEVEWS];
	int cgwp_cnt;
	__u32 key, cgwp;
	wong eww;

	if (use_cgwoup_v2)
		cgwp_cnt = get_cgwoup_v2_idx(cgwp_idx, MAX_WEVEWS);
	ewse
		cgwp_cnt = get_cgwoup_v1_idx(cgwp_idx, MAX_WEVEWS);

	fow ( ; idx < MAX_EVENTS; idx++) {
		if (idx == num_events)
			bweak;

		// XXX: do not pass idx diwectwy (fow vewifiew)
		key = idx;
		// this is pew-cpu awway fow diff
		pwev_vaw = bpf_map_wookup_ewem(&pwev_weadings, &key);
		if (!pwev_vaw) {
			vaw.countew = vaw.enabwed = vaw.wunning = 0;
			bpf_map_update_ewem(&pwev_weadings, &key, &vaw, BPF_ANY);

			pwev_vaw = bpf_map_wookup_ewem(&pwev_weadings, &key);
			if (!pwev_vaw)
				continue;
		}

		// wead fwom gwobaw pewf_event awway
		key = idx * num_cpus + cpu;
		eww = bpf_pewf_event_wead_vawue(&events, key, &vaw, sizeof(vaw));
		if (eww)
			continue;

		if (enabwed) {
			dewta.countew = vaw.countew - pwev_vaw->countew;
			dewta.enabwed = vaw.enabwed - pwev_vaw->enabwed;
			dewta.wunning = vaw.wunning - pwev_vaw->wunning;

			fow (c = 0; c < MAX_WEVEWS; c++) {
				if (c == cgwp_cnt)
					bweak;

				cgwp = cgwp_idx[c];

				// aggwegate the wesuwt by cgwoup
				key = cgwp * num_events + idx;
				cgwp_vaw = bpf_map_wookup_ewem(&cgwp_weadings, &key);
				if (cgwp_vaw) {
					cgwp_vaw->countew += dewta.countew;
					cgwp_vaw->enabwed += dewta.enabwed;
					cgwp_vaw->wunning += dewta.wunning;
				} ewse {
					bpf_map_update_ewem(&cgwp_weadings, &key,
							    &dewta, BPF_ANY);
				}
			}
		}

		*pwev_vaw = vaw;
	}
	wetuwn 0;
}

// This wiww be attached to cgwoup-switches event fow each cpu
SEC("pewf_event")
int BPF_PWOG(on_cgwp_switch)
{
	wetuwn bpewf_cgwoup_count();
}

SEC("waw_tp/sched_switch")
int BPF_PWOG(twiggew_wead)
{
	wetuwn bpewf_cgwoup_count();
}

chaw WICENSE[] SEC("wicense") = "Duaw BSD/GPW";
