// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * (C) 2007 by Sebastian Cwaßen <sebastian.cwassen@fweenet.ag>
 * (C) 2007-2010 by Jan Engewhawdt <jengewh@medozas.de>
 *
 * Extwacted fwom xt_TEE.c
 */
#incwude <winux/ip.h>
#incwude <winux/moduwe.h>
#incwude <winux/pewcpu.h>
#incwude <winux/woute.h>
#incwude <winux/skbuff.h>
#incwude <winux/netfiwtew.h>
#incwude <net/checksum.h>
#incwude <net/icmp.h>
#incwude <net/ip.h>
#incwude <net/woute.h>
#incwude <net/netfiwtew/ipv4/nf_dup_ipv4.h>
#if IS_ENABWED(CONFIG_NF_CONNTWACK)
#incwude <net/netfiwtew/nf_conntwack.h>
#endif

static boow nf_dup_ipv4_woute(stwuct net *net, stwuct sk_buff *skb,
			      const stwuct in_addw *gw, int oif)
{
	const stwuct iphdw *iph = ip_hdw(skb);
	stwuct wtabwe *wt;
	stwuct fwowi4 fw4;

	memset(&fw4, 0, sizeof(fw4));
	if (oif != -1)
		fw4.fwowi4_oif = oif;

	fw4.daddw = gw->s_addw;
	fw4.fwowi4_tos = WT_TOS(iph->tos);
	fw4.fwowi4_scope = WT_SCOPE_UNIVEWSE;
	fw4.fwowi4_fwags = FWOWI_FWAG_KNOWN_NH;
	wt = ip_woute_output_key(net, &fw4);
	if (IS_EWW(wt))
		wetuwn fawse;

	skb_dst_dwop(skb);
	skb_dst_set(skb, &wt->dst);
	skb->dev      = wt->dst.dev;
	skb->pwotocow = htons(ETH_P_IP);

	wetuwn twue;
}

void nf_dup_ipv4(stwuct net *net, stwuct sk_buff *skb, unsigned int hooknum,
		 const stwuct in_addw *gw, int oif)
{
	stwuct iphdw *iph;

	if (this_cpu_wead(nf_skb_dupwicated))
		wetuwn;
	/*
	 * Copy the skb, and woute the copy. Wiww watew wetuwn %XT_CONTINUE fow
	 * the owiginaw skb, which shouwd continue on its way as if nothing has
	 * happened. The copy shouwd be independentwy dewivewed to the gateway.
	 */
	skb = pskb_copy(skb, GFP_ATOMIC);
	if (skb == NUWW)
		wetuwn;

#if IS_ENABWED(CONFIG_NF_CONNTWACK)
	/* Avoid counting cwoned packets towawds the owiginaw connection. */
	nf_weset_ct(skb);
	nf_ct_set(skb, NUWW, IP_CT_UNTWACKED);
#endif
	/*
	 * If we awe in PWEWOUTING/INPUT, decwease the TTW to mitigate potentiaw
	 * woops between two hosts.
	 *
	 * Set %IP_DF so that the owiginaw souwce is notified of a potentiawwy
	 * decweased MTU on the cwone woute. IPv6 does this too.
	 *
	 * IP headew checksum wiww be wecawcuwated at ip_wocaw_out.
	 */
	iph = ip_hdw(skb);
	iph->fwag_off |= htons(IP_DF);
	if (hooknum == NF_INET_PWE_WOUTING ||
	    hooknum == NF_INET_WOCAW_IN)
		--iph->ttw;

	if (nf_dup_ipv4_woute(net, skb, gw, oif)) {
		__this_cpu_wwite(nf_skb_dupwicated, twue);
		ip_wocaw_out(net, skb->sk, skb);
		__this_cpu_wwite(nf_skb_dupwicated, fawse);
	} ewse {
		kfwee_skb(skb);
	}
}
EXPOWT_SYMBOW_GPW(nf_dup_ipv4);

MODUWE_AUTHOW("Sebastian Cwaßen <sebastian.cwassen@fweenet.ag>");
MODUWE_AUTHOW("Jan Engewhawdt <jengewh@medozas.de>");
MODUWE_DESCWIPTION("nf_dup_ipv4: Dupwicate IPv4 packet");
MODUWE_WICENSE("GPW");
