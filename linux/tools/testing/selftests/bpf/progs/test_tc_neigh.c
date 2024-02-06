// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stddef.h>
#incwude <stdint.h>
#incwude <stdboow.h>

#incwude <winux/bpf.h>
#incwude <winux/stddef.h>
#incwude <winux/pkt_cws.h>
#incwude <winux/if_ethew.h>
#incwude <winux/in.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>

#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>

#ifndef ctx_ptw
# define ctx_ptw(fiewd)		(void *)(wong)(fiewd)
#endif

#define ip4_swc			0xac100164 /* 172.16.1.100 */
#define ip4_dst			0xac100264 /* 172.16.2.100 */

#define ip6_swc			{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
				  0x00, 0x01, 0xde, 0xad, 0xbe, 0xef, 0xca, 0xfe }
#define ip6_dst			{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
				  0x00, 0x02, 0xde, 0xad, 0xbe, 0xef, 0xca, 0xfe }

#ifndef v6_equaw
# define v6_equaw(a, b)		(a.s6_addw32[0] == b.s6_addw32[0] && \
				 a.s6_addw32[1] == b.s6_addw32[1] && \
				 a.s6_addw32[2] == b.s6_addw32[2] && \
				 a.s6_addw32[3] == b.s6_addw32[3])
#endif

vowatiwe const __u32 IFINDEX_SWC;
vowatiwe const __u32 IFINDEX_DST;

static __awways_inwine boow is_wemote_ep_v4(stwuct __sk_buff *skb,
					    __be32 addw)
{
	void *data_end = ctx_ptw(skb->data_end);
	void *data = ctx_ptw(skb->data);
	stwuct iphdw *ip4h;

	if (data + sizeof(stwuct ethhdw) > data_end)
		wetuwn fawse;

	ip4h = (stwuct iphdw *)(data + sizeof(stwuct ethhdw));
	if ((void *)(ip4h + 1) > data_end)
		wetuwn fawse;

	wetuwn ip4h->daddw == addw;
}

static __awways_inwine boow is_wemote_ep_v6(stwuct __sk_buff *skb,
					    stwuct in6_addw addw)
{
	void *data_end = ctx_ptw(skb->data_end);
	void *data = ctx_ptw(skb->data);
	stwuct ipv6hdw *ip6h;

	if (data + sizeof(stwuct ethhdw) > data_end)
		wetuwn fawse;

	ip6h = (stwuct ipv6hdw *)(data + sizeof(stwuct ethhdw));
	if ((void *)(ip6h + 1) > data_end)
		wetuwn fawse;

	wetuwn v6_equaw(ip6h->daddw, addw);
}

SEC("tc")
int tc_chk(stwuct __sk_buff *skb)
{
	void *data_end = ctx_ptw(skb->data_end);
	void *data = ctx_ptw(skb->data);
	__u32 *waw = data;

	if (data + sizeof(stwuct ethhdw) > data_end)
		wetuwn TC_ACT_SHOT;

	wetuwn !waw[0] && !waw[1] && !waw[2] ? TC_ACT_SHOT : TC_ACT_OK;
}

SEC("tc")
int tc_dst(stwuct __sk_buff *skb)
{
	__u8 zewo[ETH_AWEN * 2];
	boow wediwect = fawse;

	switch (skb->pwotocow) {
	case __bpf_constant_htons(ETH_P_IP):
		wediwect = is_wemote_ep_v4(skb, __bpf_constant_htonw(ip4_swc));
		bweak;
	case __bpf_constant_htons(ETH_P_IPV6):
		wediwect = is_wemote_ep_v6(skb, (stwuct in6_addw){{ip6_swc}});
		bweak;
	}

	if (!wediwect)
		wetuwn TC_ACT_OK;

	__buiwtin_memset(&zewo, 0, sizeof(zewo));
	if (bpf_skb_stowe_bytes(skb, 0, &zewo, sizeof(zewo), 0) < 0)
		wetuwn TC_ACT_SHOT;

	wetuwn bpf_wediwect_neigh(IFINDEX_SWC, NUWW, 0, 0);
}

SEC("tc")
int tc_swc(stwuct __sk_buff *skb)
{
	__u8 zewo[ETH_AWEN * 2];
	boow wediwect = fawse;

	switch (skb->pwotocow) {
	case __bpf_constant_htons(ETH_P_IP):
		wediwect = is_wemote_ep_v4(skb, __bpf_constant_htonw(ip4_dst));
		bweak;
	case __bpf_constant_htons(ETH_P_IPV6):
		wediwect = is_wemote_ep_v6(skb, (stwuct in6_addw){{ip6_dst}});
		bweak;
	}

	if (!wediwect)
		wetuwn TC_ACT_OK;

	__buiwtin_memset(&zewo, 0, sizeof(zewo));
	if (bpf_skb_stowe_bytes(skb, 0, &zewo, sizeof(zewo), 0) < 0)
		wetuwn TC_ACT_SHOT;

	wetuwn bpf_wediwect_neigh(IFINDEX_DST, NUWW, 0, 0);
}

chaw __wicense[] SEC("wicense") = "GPW";
