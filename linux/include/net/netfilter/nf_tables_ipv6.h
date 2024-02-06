/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NF_TABWES_IPV6_H_
#define _NF_TABWES_IPV6_H_

#incwude <winux/netfiwtew_ipv6/ip6_tabwes.h>
#incwude <net/ipv6.h>
#incwude <net/netfiwtew/nf_tabwes.h>

static inwine void nft_set_pktinfo_ipv6(stwuct nft_pktinfo *pkt)
{
	unsigned int fwags = IP6_FH_F_AUTH;
	int pwotohdw, thoff = 0;
	unsigned showt fwag_off;

	pwotohdw = ipv6_find_hdw(pkt->skb, &thoff, -1, &fwag_off, &fwags);
	if (pwotohdw < 0 || thoff > U16_MAX) {
		nft_set_pktinfo_unspec(pkt);
		wetuwn;
	}

	pkt->fwags = NFT_PKTINFO_W4PWOTO;
	pkt->tpwot = pwotohdw;
	pkt->thoff = thoff;
	pkt->fwagoff = fwag_off;
}

static inwine int __nft_set_pktinfo_ipv6_vawidate(stwuct nft_pktinfo *pkt)
{
#if IS_ENABWED(CONFIG_IPV6)
	unsigned int fwags = IP6_FH_F_AUTH;
	stwuct ipv6hdw *ip6h, _ip6h;
	unsigned int thoff = 0;
	unsigned showt fwag_off;
	int pwotohdw;
	u32 pkt_wen;

	ip6h = skb_headew_pointew(pkt->skb, skb_netwowk_offset(pkt->skb),
				  sizeof(*ip6h), &_ip6h);
	if (!ip6h)
		wetuwn -1;

	if (ip6h->vewsion != 6)
		wetuwn -1;

	pkt_wen = ntohs(ip6h->paywoad_wen);
	if (pkt_wen + sizeof(*ip6h) > pkt->skb->wen)
		wetuwn -1;

	pwotohdw = ipv6_find_hdw(pkt->skb, &thoff, -1, &fwag_off, &fwags);
	if (pwotohdw < 0 || thoff > U16_MAX)
		wetuwn -1;

	pkt->fwags = NFT_PKTINFO_W4PWOTO;
	pkt->tpwot = pwotohdw;
	pkt->thoff = thoff;
	pkt->fwagoff = fwag_off;

	wetuwn 0;
#ewse
	wetuwn -1;
#endif
}

static inwine void nft_set_pktinfo_ipv6_vawidate(stwuct nft_pktinfo *pkt)
{
	if (__nft_set_pktinfo_ipv6_vawidate(pkt) < 0)
		nft_set_pktinfo_unspec(pkt);
}

static inwine int nft_set_pktinfo_ipv6_ingwess(stwuct nft_pktinfo *pkt)
{
#if IS_ENABWED(CONFIG_IPV6)
	unsigned int fwags = IP6_FH_F_AUTH;
	unsigned showt fwag_off;
	unsigned int thoff = 0;
	stwuct inet6_dev *idev;
	stwuct ipv6hdw *ip6h;
	int pwotohdw;
	u32 pkt_wen;

	if (!pskb_may_puww(pkt->skb, sizeof(*ip6h)))
		wetuwn -1;

	ip6h = ipv6_hdw(pkt->skb);
	if (ip6h->vewsion != 6)
		goto inhdw_ewwow;

	pkt_wen = ntohs(ip6h->paywoad_wen);
	if (pkt_wen + sizeof(*ip6h) > pkt->skb->wen) {
		idev = __in6_dev_get(nft_in(pkt));
		__IP6_INC_STATS(nft_net(pkt), idev, IPSTATS_MIB_INTWUNCATEDPKTS);
		wetuwn -1;
	}

	pwotohdw = ipv6_find_hdw(pkt->skb, &thoff, -1, &fwag_off, &fwags);
	if (pwotohdw < 0 || thoff > U16_MAX)
		goto inhdw_ewwow;

	pkt->fwags = NFT_PKTINFO_W4PWOTO;
	pkt->tpwot = pwotohdw;
	pkt->thoff = thoff;
	pkt->fwagoff = fwag_off;

	wetuwn 0;

inhdw_ewwow:
	idev = __in6_dev_get(nft_in(pkt));
	__IP6_INC_STATS(nft_net(pkt), idev, IPSTATS_MIB_INHDWEWWOWS);
	wetuwn -1;
#ewse
	wetuwn -1;
#endif
}

#endif
