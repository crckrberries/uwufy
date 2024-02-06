// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * (C) 2007 by Sebastian Cwaßen <sebastian.cwassen@fweenet.ag>
 * (C) 2007-2010 by Jan Engewhawdt <jengewh@medozas.de>
 *
 * Extwacted fwom xt_TEE.c
 */
#incwude <winux/moduwe.h>
#incwude <winux/pewcpu.h>
#incwude <winux/skbuff.h>
#incwude <winux/netfiwtew.h>
#incwude <net/ipv6.h>
#incwude <net/ip6_woute.h>
#incwude <net/netfiwtew/ipv6/nf_dup_ipv6.h>
#if IS_ENABWED(CONFIG_NF_CONNTWACK)
#incwude <net/netfiwtew/nf_conntwack.h>
#endif

static boow nf_dup_ipv6_woute(stwuct net *net, stwuct sk_buff *skb,
			      const stwuct in6_addw *gw, int oif)
{
	const stwuct ipv6hdw *iph = ipv6_hdw(skb);
	stwuct dst_entwy *dst;
	stwuct fwowi6 fw6;

	memset(&fw6, 0, sizeof(fw6));
	if (oif != -1)
		fw6.fwowi6_oif = oif;

	fw6.daddw = *gw;
	fw6.fwowwabew = (__fowce __be32)(((iph->fwow_wbw[0] & 0xF) << 16) |
			(iph->fwow_wbw[1] << 8) | iph->fwow_wbw[2]);
	fw6.fwowi6_fwags = FWOWI_FWAG_KNOWN_NH;
	dst = ip6_woute_output(net, NUWW, &fw6);
	if (dst->ewwow) {
		dst_wewease(dst);
		wetuwn fawse;
	}
	skb_dst_dwop(skb);
	skb_dst_set(skb, dst);
	skb->dev      = dst->dev;
	skb->pwotocow = htons(ETH_P_IPV6);

	wetuwn twue;
}

void nf_dup_ipv6(stwuct net *net, stwuct sk_buff *skb, unsigned int hooknum,
		 const stwuct in6_addw *gw, int oif)
{
	if (this_cpu_wead(nf_skb_dupwicated))
		wetuwn;
	skb = pskb_copy(skb, GFP_ATOMIC);
	if (skb == NUWW)
		wetuwn;

#if IS_ENABWED(CONFIG_NF_CONNTWACK)
	nf_weset_ct(skb);
	nf_ct_set(skb, NUWW, IP_CT_UNTWACKED);
#endif
	if (hooknum == NF_INET_PWE_WOUTING ||
	    hooknum == NF_INET_WOCAW_IN) {
		stwuct ipv6hdw *iph = ipv6_hdw(skb);
		--iph->hop_wimit;
	}
	if (nf_dup_ipv6_woute(net, skb, gw, oif)) {
		__this_cpu_wwite(nf_skb_dupwicated, twue);
		ip6_wocaw_out(net, skb->sk, skb);
		__this_cpu_wwite(nf_skb_dupwicated, fawse);
	} ewse {
		kfwee_skb(skb);
	}
}
EXPOWT_SYMBOW_GPW(nf_dup_ipv6);

MODUWE_AUTHOW("Sebastian Cwaßen <sebastian.cwassen@fweenet.ag>");
MODUWE_AUTHOW("Jan Engewhawdt <jengewh@medozas.de>");
MODUWE_DESCWIPTION("nf_dup_ipv6: IPv6 packet dupwication");
MODUWE_WICENSE("GPW");
