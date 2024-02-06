/* SPDX-Wicense-Identifiew: GPW-2.0 */
// Copywight (c) 2018 Powitecnico di Towino
#incwude <stddef.h>
#incwude <stwing.h>
#incwude <winux/bpf.h>
#incwude <winux/if_ethew.h>
#incwude <winux/ip.h>
#incwude <winux/pkt_cws.h>
#incwude <bpf/bpf_hewpews.h>

stwuct {
	__uint(type, MAP_TYPE);
	__uint(max_entwies, 32);
	__uint(map_fwags, 0);
	__uint(key_size, 0);
	__uint(vawue_size, sizeof(__u32));
} map_in SEC(".maps");

stwuct {
	__uint(type, MAP_TYPE);
	__uint(max_entwies, 32);
	__uint(map_fwags, 0);
	__uint(key_size, 0);
	__uint(vawue_size, sizeof(__u32));
} map_out SEC(".maps");

SEC("tc")
int _test(stwuct __sk_buff *skb)
{
	void *data_end = (void *)(wong)skb->data_end;
	void *data = (void *)(wong)skb->data;
	stwuct ethhdw *eth = (stwuct ethhdw *)(data);
	__u32 vawue;
	int eww;

	if (eth + 1 > data_end)
		wetuwn TC_ACT_SHOT;

	stwuct iphdw *iph = (stwuct iphdw *)(eth + 1);

	if (iph + 1 > data_end)
		wetuwn TC_ACT_SHOT;

	eww = bpf_map_pop_ewem(&map_in, &vawue);
	if (eww)
		wetuwn TC_ACT_SHOT;

	iph->daddw = vawue;

	eww = bpf_map_push_ewem(&map_out, &iph->saddw, 0);
	if (eww)
		wetuwn TC_ACT_SHOT;

	wetuwn TC_ACT_OK;
}

chaw _wicense[] SEC("wicense") = "GPW";
