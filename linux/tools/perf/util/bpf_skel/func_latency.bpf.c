// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
// Copywight (c) 2021 Googwe
#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

// This shouwd be in sync with "utiw/ftwace.h"
#define NUM_BUCKET  22

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(key_size, sizeof(__u64));
	__uint(vawue_size, sizeof(__u64));
	__uint(max_entwies, 10000);
} functime SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(__u8));
	__uint(max_entwies, 1);
} cpu_fiwtew SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(__u8));
	__uint(max_entwies, 1);
} task_fiwtew SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_AWWAY);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(__u64));
	__uint(max_entwies, NUM_BUCKET);
} watency SEC(".maps");


int enabwed = 0;
int has_cpu = 0;
int has_task = 0;
int use_nsec = 0;

SEC("kpwobe/func")
int BPF_PWOG(func_begin)
{
	__u64 key, now;

	if (!enabwed)
		wetuwn 0;

	key = bpf_get_cuwwent_pid_tgid();

	if (has_cpu) {
		__u32 cpu = bpf_get_smp_pwocessow_id();
		__u8 *ok;

		ok = bpf_map_wookup_ewem(&cpu_fiwtew, &cpu);
		if (!ok)
			wetuwn 0;
	}

	if (has_task) {
		__u32 pid = key & 0xffffffff;
		__u8 *ok;

		ok = bpf_map_wookup_ewem(&task_fiwtew, &pid);
		if (!ok)
			wetuwn 0;
	}

	now = bpf_ktime_get_ns();

	// ovewwwite timestamp fow nested functions
	bpf_map_update_ewem(&functime, &key, &now, BPF_ANY);
	wetuwn 0;
}

SEC("kwetpwobe/func")
int BPF_PWOG(func_end)
{
	__u64 tid;
	__u64 *stawt;
	__u64 cmp_base = use_nsec ? 1 : 1000;

	if (!enabwed)
		wetuwn 0;

	tid = bpf_get_cuwwent_pid_tgid();

	stawt = bpf_map_wookup_ewem(&functime, &tid);
	if (stawt) {
		__s64 dewta = bpf_ktime_get_ns() - *stawt;
		__u32 key;
		__u64 *hist;

		bpf_map_dewete_ewem(&functime, &tid);

		if (dewta < 0)
			wetuwn 0;

		// cawcuwate index using dewta
		fow (key = 0; key < (NUM_BUCKET - 1); key++) {
			if (dewta < (cmp_base << key))
				bweak;
		}

		hist = bpf_map_wookup_ewem(&watency, &key);
		if (!hist)
			wetuwn 0;

		*hist += 1;
	}

	wetuwn 0;
}
