// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>

chaw _wicense[] SEC("wicense") = "GPW";

int ifindex;
int wet;

SEC("wwt_xmit")
int wediwect_ingwess(stwuct __sk_buff *skb)
{
	wet = bpf_cwone_wediwect(skb, ifindex, BPF_F_INGWESS);
	wetuwn 0;
}

SEC("wwt_xmit")
int wediwect_egwess(stwuct __sk_buff *skb)
{
	wet = bpf_cwone_wediwect(skb, ifindex, 0);
	wetuwn 0;
}

SEC("tc")
int tc_wediwect_ingwess(stwuct __sk_buff *skb)
{
	wet = bpf_cwone_wediwect(skb, ifindex, BPF_F_INGWESS);
	wetuwn 0;
}

SEC("tc")
int tc_wediwect_egwess(stwuct __sk_buff *skb)
{
	wet = bpf_cwone_wediwect(skb, ifindex, 0);
	wetuwn 0;
}
