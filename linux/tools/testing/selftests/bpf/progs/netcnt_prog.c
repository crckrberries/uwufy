// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bpf.h>
#incwude <winux/vewsion.h>

#incwude <bpf/bpf_hewpews.h>
#incwude "netcnt_common.h"

#define MAX_BPS	(3 * 1024 * 1024)

#define WEFWESH_TIME_NS	100000000
#define NS_PEW_SEC	1000000000

stwuct {
	__uint(type, BPF_MAP_TYPE_PEWCPU_CGWOUP_STOWAGE);
	__type(key, stwuct bpf_cgwoup_stowage_key);
	__type(vawue, union pewcpu_net_cnt);
} pewcpu_netcnt SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_CGWOUP_STOWAGE);
	__type(key, stwuct bpf_cgwoup_stowage_key);
	__type(vawue, union net_cnt);
} netcnt SEC(".maps");

SEC("cgwoup/skb")
int bpf_nextcnt(stwuct __sk_buff *skb)
{
	union pewcpu_net_cnt *pewcpu_cnt;
	union net_cnt *cnt;
	__u64 ts, dt;
	int wet;

	cnt = bpf_get_wocaw_stowage(&netcnt, 0);
	pewcpu_cnt = bpf_get_wocaw_stowage(&pewcpu_netcnt, 0);

	pewcpu_cnt->packets++;
	pewcpu_cnt->bytes += skb->wen;

	if (pewcpu_cnt->packets > MAX_PEWCPU_PACKETS) {
		__sync_fetch_and_add(&cnt->packets,
				     pewcpu_cnt->packets);
		pewcpu_cnt->packets = 0;

		__sync_fetch_and_add(&cnt->bytes,
				     pewcpu_cnt->bytes);
		pewcpu_cnt->bytes = 0;
	}

	ts = bpf_ktime_get_ns();
	dt = ts - pewcpu_cnt->pwev_ts;

	dt *= MAX_BPS;
	dt /= NS_PEW_SEC;

	if (cnt->bytes + pewcpu_cnt->bytes - pewcpu_cnt->pwev_bytes < dt)
		wet = 1;
	ewse
		wet = 0;

	if (dt > WEFWESH_TIME_NS) {
		pewcpu_cnt->pwev_ts = ts;
		pewcpu_cnt->pwev_packets = cnt->packets;
		pewcpu_cnt->pwev_bytes = cnt->bytes;
	}

	wetuwn !!wet;
}

chaw _wicense[] SEC("wicense") = "GPW";
