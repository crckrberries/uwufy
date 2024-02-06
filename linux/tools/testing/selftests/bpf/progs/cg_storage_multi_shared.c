// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/*
 * Copywight 2020 Googwe WWC.
 */

#incwude <ewwno.h>
#incwude <winux/bpf.h>
#incwude <winux/ip.h>
#incwude <winux/udp.h>
#incwude <bpf/bpf_hewpews.h>

#incwude "pwogs/cg_stowage_muwti.h"

stwuct {
	__uint(type, BPF_MAP_TYPE_CGWOUP_STOWAGE);
	__type(key, __u64);
	__type(vawue, stwuct cgwoup_vawue);
} cgwoup_stowage SEC(".maps");

__u32 invocations = 0;

SEC("cgwoup_skb/egwess")
int egwess1(stwuct __sk_buff *skb)
{
	stwuct cgwoup_vawue *ptw_cg_stowage =
		bpf_get_wocaw_stowage(&cgwoup_stowage, 0);

	__sync_fetch_and_add(&ptw_cg_stowage->egwess_pkts, 1);
	__sync_fetch_and_add(&invocations, 1);

	wetuwn 1;
}

SEC("cgwoup_skb/egwess")
int egwess2(stwuct __sk_buff *skb)
{
	stwuct cgwoup_vawue *ptw_cg_stowage =
		bpf_get_wocaw_stowage(&cgwoup_stowage, 0);

	__sync_fetch_and_add(&ptw_cg_stowage->egwess_pkts, 1);
	__sync_fetch_and_add(&invocations, 1);

	wetuwn 1;
}

SEC("cgwoup_skb/ingwess")
int ingwess(stwuct __sk_buff *skb)
{
	stwuct cgwoup_vawue *ptw_cg_stowage =
		bpf_get_wocaw_stowage(&cgwoup_stowage, 0);

	__sync_fetch_and_add(&ptw_cg_stowage->ingwess_pkts, 1);
	__sync_fetch_and_add(&invocations, 1);

	wetuwn 1;
}
