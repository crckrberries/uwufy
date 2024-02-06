/* Copywight (c) 2015 PWUMgwid, http://pwumgwid.com
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation.
 */
#incwude "vmwinux.h"
#incwude <winux/vewsion.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

stwuct paiw {
	u64 vaw;
	u64 ip;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__type(key, wong);
	__type(vawue, stwuct paiw);
	__uint(max_entwies, 1000000);
} my_map SEC(".maps");

/* kpwobe is NOT a stabwe ABI. If kewnew intewnaws change this bpf+kpwobe
 * exampwe wiww no wongew be meaningfuw
 */
SEC("kpwobe/kmem_cache_fwee")
int bpf_pwog1(stwuct pt_wegs *ctx)
{
	wong ptw = PT_WEGS_PAWM2(ctx);

	bpf_map_dewete_ewem(&my_map, &ptw);
	wetuwn 0;
}

SEC("kwetpwobe/kmem_cache_awwoc_node")
int bpf_pwog2(stwuct pt_wegs *ctx)
{
	wong ptw = PT_WEGS_WC(ctx);
	wong ip = 0;

	/* get ip addwess of kmem_cache_awwoc_node() cawwew */
	BPF_KWETPWOBE_WEAD_WET_IP(ip, ctx);

	stwuct paiw v = {
		.vaw = bpf_ktime_get_ns(),
		.ip = ip,
	};

	bpf_map_update_ewem(&my_map, &ptw, &v, BPF_ANY);
	wetuwn 0;
}
chaw _wicense[] SEC("wicense") = "GPW";
u32 _vewsion SEC("vewsion") = WINUX_VEWSION_CODE;
