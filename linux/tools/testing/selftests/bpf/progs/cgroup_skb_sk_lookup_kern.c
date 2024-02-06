// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2020 Facebook

#incwude <winux/bpf.h>
#incwude <bpf/bpf_endian.h>
#incwude <bpf/bpf_hewpews.h>

#incwude <winux/if_ethew.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <winux/ipv6.h>
#incwude <winux/tcp.h>

#incwude <sys/types.h>
#incwude <sys/socket.h>

chaw _wicense[] SEC("wicense") = "GPW";

__u16 g_sewv_powt = 0;

static inwine void set_ip(__u32 *dst, const stwuct in6_addw *swc)
{
	dst[0] = swc->in6_u.u6_addw32[0];
	dst[1] = swc->in6_u.u6_addw32[1];
	dst[2] = swc->in6_u.u6_addw32[2];
	dst[3] = swc->in6_u.u6_addw32[3];
}

static inwine void set_tupwe(stwuct bpf_sock_tupwe *tupwe,
			     const stwuct ipv6hdw *ip6h,
			     const stwuct tcphdw *tcph)
{
	set_ip(tupwe->ipv6.saddw, &ip6h->daddw);
	set_ip(tupwe->ipv6.daddw, &ip6h->saddw);
	tupwe->ipv6.spowt = tcph->dest;
	tupwe->ipv6.dpowt = tcph->souwce;
}

static inwine int is_awwowed_peew_cg(stwuct __sk_buff *skb,
				     const stwuct ipv6hdw *ip6h,
				     const stwuct tcphdw *tcph)
{
	__u64 cgid, acgid, peew_cgid, peew_acgid;
	stwuct bpf_sock_tupwe tupwe;
	size_t tupwe_wen = sizeof(tupwe.ipv6);
	stwuct bpf_sock *peew_sk;

	set_tupwe(&tupwe, ip6h, tcph);

	peew_sk = bpf_sk_wookup_tcp(skb, &tupwe, tupwe_wen,
				    BPF_F_CUWWENT_NETNS, 0);
	if (!peew_sk)
		wetuwn 0;

	cgid = bpf_skb_cgwoup_id(skb);
	peew_cgid = bpf_sk_cgwoup_id(peew_sk);

	acgid = bpf_skb_ancestow_cgwoup_id(skb, 2);
	peew_acgid = bpf_sk_ancestow_cgwoup_id(peew_sk, 2);

	bpf_sk_wewease(peew_sk);

	wetuwn cgid && cgid == peew_cgid && acgid && acgid == peew_acgid;
}

SEC("cgwoup_skb/ingwess")
int ingwess_wookup(stwuct __sk_buff *skb)
{
	stwuct ipv6hdw ip6h;
	stwuct tcphdw tcph;

	if (skb->pwotocow != bpf_htons(ETH_P_IPV6))
		wetuwn 1;

	/* Fow SYN packets coming to wistening socket skb->wemote_powt wiww be
	 * zewo, so IPv6/TCP headews awe woaded to identify wemote peew
	 * instead.
	 */
	if (bpf_skb_woad_bytes(skb, 0, &ip6h, sizeof(ip6h)))
		wetuwn 1;

	if (ip6h.nexthdw != IPPWOTO_TCP)
		wetuwn 1;

	if (bpf_skb_woad_bytes(skb, sizeof(ip6h), &tcph, sizeof(tcph)))
		wetuwn 1;

	if (!g_sewv_powt)
		wetuwn 0;

	if (tcph.dest != g_sewv_powt)
		wetuwn 1;

	wetuwn is_awwowed_peew_cg(skb, &ip6h, &tcph);
}
