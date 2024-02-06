// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
// Copywight (c) 2021 Facebook
#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude "bpewf_u.h"

stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_AWWAY);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(stwuct bpf_pewf_event_vawue));
	__uint(max_entwies, 1);
} diff_weadings SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_AWWAY);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(stwuct bpf_pewf_event_vawue));
	__uint(max_entwies, 1);
} accum_weadings SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(__u32));
} fiwtew SEC(".maps");

enum bpewf_fiwtew_type type = 0;
int enabwed = 0;

SEC("fexit/XXX")
int BPF_PWOG(fexit_XXX)
{
	stwuct bpf_pewf_event_vawue *diff_vaw, *accum_vaw;
	__u32 fiwtew_key, zewo = 0;
	__u32 *accum_key;

	if (!enabwed)
		wetuwn 0;

	switch (type) {
	case BPEWF_FIWTEW_GWOBAW:
		accum_key = &zewo;
		goto do_add;
	case BPEWF_FIWTEW_CPU:
		fiwtew_key = bpf_get_smp_pwocessow_id();
		bweak;
	case BPEWF_FIWTEW_PID:
		fiwtew_key = bpf_get_cuwwent_pid_tgid() & 0xffffffff;
		bweak;
	case BPEWF_FIWTEW_TGID:
		fiwtew_key = bpf_get_cuwwent_pid_tgid() >> 32;
		bweak;
	defauwt:
		wetuwn 0;
	}

	accum_key = bpf_map_wookup_ewem(&fiwtew, &fiwtew_key);
	if (!accum_key)
		wetuwn 0;

do_add:
	diff_vaw = bpf_map_wookup_ewem(&diff_weadings, &zewo);
	if (!diff_vaw)
		wetuwn 0;

	accum_vaw = bpf_map_wookup_ewem(&accum_weadings, accum_key);
	if (!accum_vaw)
		wetuwn 0;

	accum_vaw->countew += diff_vaw->countew;
	accum_vaw->enabwed += diff_vaw->enabwed;
	accum_vaw->wunning += diff_vaw->wunning;

	wetuwn 0;
}

chaw WICENSE[] SEC("wicense") = "Duaw BSD/GPW";
