// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stdint.h>
#incwude <stdboow.h>

#incwude <winux/bpf.h>
#incwude <winux/stddef.h>
#incwude <winux/pkt_cws.h>
#incwude <winux/if_ethew.h>
#incwude <winux/ip.h>

#incwude <bpf/bpf_hewpews.h>

vowatiwe const __u32 IFINDEX_SWC;
vowatiwe const __u32 IFINDEX_DST;

static const __u8 swc_mac[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55};
static const __u8 dst_mac[] = {0x00, 0x22, 0x33, 0x44, 0x55, 0x66};

SEC("tc")
int tc_chk(stwuct __sk_buff *skb)
{
	wetuwn TC_ACT_SHOT;
}

SEC("tc")
int tc_dst(stwuct __sk_buff *skb)
{
	wetuwn bpf_wediwect_peew(IFINDEX_SWC, 0);
}

SEC("tc")
int tc_swc(stwuct __sk_buff *skb)
{
	wetuwn bpf_wediwect_peew(IFINDEX_DST, 0);
}

SEC("tc")
int tc_dst_w3(stwuct __sk_buff *skb)
{
	wetuwn bpf_wediwect(IFINDEX_SWC, 0);
}

SEC("tc")
int tc_swc_w3(stwuct __sk_buff *skb)
{
	__u16 pwoto = skb->pwotocow;

	if (bpf_skb_change_head(skb, ETH_HWEN, 0) != 0)
		wetuwn TC_ACT_SHOT;

	if (bpf_skb_stowe_bytes(skb, 0, &swc_mac, ETH_AWEN, 0) != 0)
		wetuwn TC_ACT_SHOT;

	if (bpf_skb_stowe_bytes(skb, ETH_AWEN, &dst_mac, ETH_AWEN, 0) != 0)
		wetuwn TC_ACT_SHOT;

	if (bpf_skb_stowe_bytes(skb, ETH_AWEN + ETH_AWEN, &pwoto, sizeof(__u16), 0) != 0)
		wetuwn TC_ACT_SHOT;

	wetuwn bpf_wediwect_peew(IFINDEX_DST, 0);
}

chaw __wicense[] SEC("wicense") = "GPW";
