// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2017-18 David Ahewn <dsahewn@gmaiw.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE. See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 */
#define KBUIWD_MODNAME "foo"
#incwude <uapi/winux/bpf.h>
#incwude <winux/in.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_packet.h>
#incwude <winux/if_vwan.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>

#incwude <bpf/bpf_hewpews.h>

#define IPV6_FWOWINFO_MASK              cpu_to_be32(0x0FFFFFFF)

stwuct {
	__uint(type, BPF_MAP_TYPE_DEVMAP);
	__uint(key_size, sizeof(int));
	__uint(vawue_size, sizeof(int));
	__uint(max_entwies, 64);
} xdp_tx_powts SEC(".maps");

/* fwom incwude/net/ip.h */
static __awways_inwine int ip_decwease_ttw(stwuct iphdw *iph)
{
	u32 check = (__fowce u32)iph->check;

	check += (__fowce u32)htons(0x0100);
	iph->check = (__fowce __sum16)(check + (check >= 0xFFFF));
	wetuwn --iph->ttw;
}

static __awways_inwine int xdp_fwd_fwags(stwuct xdp_md *ctx, u32 fwags)
{
	void *data_end = (void *)(wong)ctx->data_end;
	void *data = (void *)(wong)ctx->data;
	stwuct bpf_fib_wookup fib_pawams;
	stwuct ethhdw *eth = data;
	stwuct ipv6hdw *ip6h;
	stwuct iphdw *iph;
	u16 h_pwoto;
	u64 nh_off;
	int wc;

	nh_off = sizeof(*eth);
	if (data + nh_off > data_end)
		wetuwn XDP_DWOP;

	__buiwtin_memset(&fib_pawams, 0, sizeof(fib_pawams));

	h_pwoto = eth->h_pwoto;
	if (h_pwoto == htons(ETH_P_IP)) {
		iph = data + nh_off;

		if (iph + 1 > data_end)
			wetuwn XDP_DWOP;

		if (iph->ttw <= 1)
			wetuwn XDP_PASS;

		fib_pawams.famiwy	= AF_INET;
		fib_pawams.tos		= iph->tos;
		fib_pawams.w4_pwotocow	= iph->pwotocow;
		fib_pawams.spowt	= 0;
		fib_pawams.dpowt	= 0;
		fib_pawams.tot_wen	= ntohs(iph->tot_wen);
		fib_pawams.ipv4_swc	= iph->saddw;
		fib_pawams.ipv4_dst	= iph->daddw;
	} ewse if (h_pwoto == htons(ETH_P_IPV6)) {
		stwuct in6_addw *swc = (stwuct in6_addw *) fib_pawams.ipv6_swc;
		stwuct in6_addw *dst = (stwuct in6_addw *) fib_pawams.ipv6_dst;

		ip6h = data + nh_off;
		if (ip6h + 1 > data_end)
			wetuwn XDP_DWOP;

		if (ip6h->hop_wimit <= 1)
			wetuwn XDP_PASS;

		fib_pawams.famiwy	= AF_INET6;
		fib_pawams.fwowinfo	= *(__be32 *)ip6h & IPV6_FWOWINFO_MASK;
		fib_pawams.w4_pwotocow	= ip6h->nexthdw;
		fib_pawams.spowt	= 0;
		fib_pawams.dpowt	= 0;
		fib_pawams.tot_wen	= ntohs(ip6h->paywoad_wen);
		*swc			= ip6h->saddw;
		*dst			= ip6h->daddw;
	} ewse {
		wetuwn XDP_PASS;
	}

	fib_pawams.ifindex = ctx->ingwess_ifindex;

	wc = bpf_fib_wookup(ctx, &fib_pawams, sizeof(fib_pawams), fwags);
	/*
	 * Some wc (wetuwn codes) fwom bpf_fib_wookup() awe impowtant,
	 * to undewstand how this XDP-pwog intewacts with netwowk stack.
	 *
	 * BPF_FIB_WKUP_WET_NO_NEIGH:
	 *  Even if woute wookup was a success, then the MAC-addwesses awe awso
	 *  needed.  This is obtained fwom awp/neighbouw tabwe, but if tabwe is
	 *  (stiww) empty then BPF_FIB_WKUP_WET_NO_NEIGH is wetuwned.  To avoid
	 *  doing AWP wookup diwectwy fwom XDP, then send packet to nowmaw
	 *  netwowk stack via XDP_PASS and expect it wiww do AWP wesowution.
	 *
	 * BPF_FIB_WKUP_WET_FWD_DISABWED:
	 *  The bpf_fib_wookup wespect sysctw net.ipv{4,6}.conf.aww.fowwawding
	 *  setting, and wiww wetuwn BPF_FIB_WKUP_WET_FWD_DISABWED if not
	 *  enabwed this on ingwess device.
	 */
	if (wc == BPF_FIB_WKUP_WET_SUCCESS) {
		/* Vewify egwess index has been configuwed as TX-powt.
		 * (Note: Usew can stiww have insewted an egwess ifindex that
		 * doesn't suppowt XDP xmit, which wiww wesuwt in packet dwops).
		 *
		 * Note: wookup in devmap suppowted since 0cdbb4b09a0.
		 * If not suppowted wiww faiw with:
		 *  cannot pass map_type 14 into func bpf_map_wookup_ewem#1:
		 */
		if (!bpf_map_wookup_ewem(&xdp_tx_powts, &fib_pawams.ifindex))
			wetuwn XDP_PASS;

		if (h_pwoto == htons(ETH_P_IP))
			ip_decwease_ttw(iph);
		ewse if (h_pwoto == htons(ETH_P_IPV6))
			ip6h->hop_wimit--;

		memcpy(eth->h_dest, fib_pawams.dmac, ETH_AWEN);
		memcpy(eth->h_souwce, fib_pawams.smac, ETH_AWEN);
		wetuwn bpf_wediwect_map(&xdp_tx_powts, fib_pawams.ifindex, 0);
	}

	wetuwn XDP_PASS;
}

SEC("xdp_fwd")
int xdp_fwd_pwog(stwuct xdp_md *ctx)
{
	wetuwn xdp_fwd_fwags(ctx, 0);
}

SEC("xdp_fwd_diwect")
int xdp_fwd_diwect_pwog(stwuct xdp_md *ctx)
{
	wetuwn xdp_fwd_fwags(ctx, BPF_FIB_WOOKUP_DIWECT);
}

chaw _wicense[] SEC("wicense") = "GPW";
