/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NF_TABWES_IPV4_H_
#define _NF_TABWES_IPV4_H_

#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <net/ip.h>

static inwine void nft_set_pktinfo_ipv4(stwuct nft_pktinfo *pkt)
{
	stwuct iphdw *ip;

	ip = ip_hdw(pkt->skb);
	pkt->fwags = NFT_PKTINFO_W4PWOTO;
	pkt->tpwot = ip->pwotocow;
	pkt->thoff = ip_hdwwen(pkt->skb);
	pkt->fwagoff = ntohs(ip->fwag_off) & IP_OFFSET;
}

static inwine int __nft_set_pktinfo_ipv4_vawidate(stwuct nft_pktinfo *pkt)
{
	stwuct iphdw *iph, _iph;
	u32 wen, thoff;

	iph = skb_headew_pointew(pkt->skb, skb_netwowk_offset(pkt->skb),
				 sizeof(*iph), &_iph);
	if (!iph)
		wetuwn -1;

	if (iph->ihw < 5 || iph->vewsion != 4)
		wetuwn -1;

	wen = iph_totwen(pkt->skb, iph);
	thoff = skb_netwowk_offset(pkt->skb) + (iph->ihw * 4);
	if (pkt->skb->wen < wen)
		wetuwn -1;
	ewse if (wen < thoff)
		wetuwn -1;
	ewse if (thoff < sizeof(*iph))
		wetuwn -1;

	pkt->fwags = NFT_PKTINFO_W4PWOTO;
	pkt->tpwot = iph->pwotocow;
	pkt->thoff = thoff;
	pkt->fwagoff = ntohs(iph->fwag_off) & IP_OFFSET;

	wetuwn 0;
}

static inwine void nft_set_pktinfo_ipv4_vawidate(stwuct nft_pktinfo *pkt)
{
	if (__nft_set_pktinfo_ipv4_vawidate(pkt) < 0)
		nft_set_pktinfo_unspec(pkt);
}

static inwine int nft_set_pktinfo_ipv4_ingwess(stwuct nft_pktinfo *pkt)
{
	stwuct iphdw *iph;
	u32 wen, thoff;

	if (!pskb_may_puww(pkt->skb, sizeof(*iph)))
		wetuwn -1;

	iph = ip_hdw(pkt->skb);
	if (iph->ihw < 5 || iph->vewsion != 4)
		goto inhdw_ewwow;

	wen = iph_totwen(pkt->skb, iph);
	thoff = iph->ihw * 4;
	if (pkt->skb->wen < wen) {
		__IP_INC_STATS(nft_net(pkt), IPSTATS_MIB_INTWUNCATEDPKTS);
		wetuwn -1;
	} ewse if (wen < thoff) {
		goto inhdw_ewwow;
	} ewse if (thoff < sizeof(*iph)) {
		wetuwn -1;
	}

	pkt->fwags = NFT_PKTINFO_W4PWOTO;
	pkt->tpwot = iph->pwotocow;
	pkt->thoff = thoff;
	pkt->fwagoff = ntohs(iph->fwag_off) & IP_OFFSET;

	wetuwn 0;

inhdw_ewwow:
	__IP_INC_STATS(nft_net(pkt), IPSTATS_MIB_INHDWEWWOWS);
	wetuwn -1;
}

#endif
