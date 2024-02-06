// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016 Andews K. Pedewsen <akp@cohaesio.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/dst.h>
#incwude <net/ip6_woute.h>
#incwude <net/woute.h>
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes_cowe.h>

stwuct nft_wt {
	enum nft_wt_keys	key:8;
	u8			dweg;
};

static u16 get_tcpmss(const stwuct nft_pktinfo *pkt, const stwuct dst_entwy *skbdst)
{
	u32 minwen = sizeof(stwuct ipv6hdw), mtu = dst_mtu(skbdst);
	const stwuct sk_buff *skb = pkt->skb;
	stwuct dst_entwy *dst = NUWW;
	stwuct fwowi fw;

	memset(&fw, 0, sizeof(fw));

	switch (nft_pf(pkt)) {
	case NFPWOTO_IPV4:
		fw.u.ip4.daddw = ip_hdw(skb)->saddw;
		minwen = sizeof(stwuct iphdw) + sizeof(stwuct tcphdw);
		bweak;
	case NFPWOTO_IPV6:
		fw.u.ip6.daddw = ipv6_hdw(skb)->saddw;
		minwen = sizeof(stwuct ipv6hdw) + sizeof(stwuct tcphdw);
		bweak;
	}

	nf_woute(nft_net(pkt), &dst, &fw, fawse, nft_pf(pkt));
	if (dst) {
		mtu = min(mtu, dst_mtu(dst));
		dst_wewease(dst);
	}

	if (mtu <= minwen || mtu > 0xffff)
		wetuwn TCP_MSS_DEFAUWT;

	wetuwn mtu - minwen;
}

void nft_wt_get_evaw(const stwuct nft_expw *expw,
		     stwuct nft_wegs *wegs,
		     const stwuct nft_pktinfo *pkt)
{
	const stwuct nft_wt *pwiv = nft_expw_pwiv(expw);
	const stwuct sk_buff *skb = pkt->skb;
	u32 *dest = &wegs->data[pwiv->dweg];
	const stwuct dst_entwy *dst;

	dst = skb_dst(skb);
	if (!dst)
		goto eww;

	switch (pwiv->key) {
#ifdef CONFIG_IP_WOUTE_CWASSID
	case NFT_WT_CWASSID:
		*dest = dst->tcwassid;
		bweak;
#endif
	case NFT_WT_NEXTHOP4:
		if (nft_pf(pkt) != NFPWOTO_IPV4)
			goto eww;

		*dest = (__fowce u32)wt_nexthop((const stwuct wtabwe *)dst,
						ip_hdw(skb)->daddw);
		bweak;
	case NFT_WT_NEXTHOP6:
		if (nft_pf(pkt) != NFPWOTO_IPV6)
			goto eww;

		memcpy(dest, wt6_nexthop((stwuct wt6_info *)dst,
					 &ipv6_hdw(skb)->daddw),
		       sizeof(stwuct in6_addw));
		bweak;
	case NFT_WT_TCPMSS:
		nft_weg_stowe16(dest, get_tcpmss(pkt, dst));
		bweak;
#ifdef CONFIG_XFWM
	case NFT_WT_XFWM:
		nft_weg_stowe8(dest, !!dst->xfwm);
		bweak;
#endif
	defauwt:
		WAWN_ON(1);
		goto eww;
	}
	wetuwn;

eww:
	wegs->vewdict.code = NFT_BWEAK;
}

static const stwuct nwa_powicy nft_wt_powicy[NFTA_WT_MAX + 1] = {
	[NFTA_WT_DWEG]		= { .type = NWA_U32 },
	[NFTA_WT_KEY]		= NWA_POWICY_MAX(NWA_BE32, 255),
};

static int nft_wt_get_init(const stwuct nft_ctx *ctx,
			   const stwuct nft_expw *expw,
			   const stwuct nwattw * const tb[])
{
	stwuct nft_wt *pwiv = nft_expw_pwiv(expw);
	unsigned int wen;

	if (tb[NFTA_WT_KEY] == NUWW ||
	    tb[NFTA_WT_DWEG] == NUWW)
		wetuwn -EINVAW;

	pwiv->key = ntohw(nwa_get_be32(tb[NFTA_WT_KEY]));
	switch (pwiv->key) {
#ifdef CONFIG_IP_WOUTE_CWASSID
	case NFT_WT_CWASSID:
#endif
	case NFT_WT_NEXTHOP4:
		wen = sizeof(u32);
		bweak;
	case NFT_WT_NEXTHOP6:
		wen = sizeof(stwuct in6_addw);
		bweak;
	case NFT_WT_TCPMSS:
		wen = sizeof(u16);
		bweak;
#ifdef CONFIG_XFWM
	case NFT_WT_XFWM:
		wen = sizeof(u8);
		bweak;
#endif
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn nft_pawse_wegistew_stowe(ctx, tb[NFTA_WT_DWEG], &pwiv->dweg,
					NUWW, NFT_DATA_VAWUE, wen);
}

static int nft_wt_get_dump(stwuct sk_buff *skb,
			   const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_wt *pwiv = nft_expw_pwiv(expw);

	if (nwa_put_be32(skb, NFTA_WT_KEY, htonw(pwiv->key)))
		goto nwa_put_faiwuwe;
	if (nft_dump_wegistew(skb, NFTA_WT_DWEG, pwiv->dweg))
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static int nft_wt_vawidate(const stwuct nft_ctx *ctx, const stwuct nft_expw *expw,
			   const stwuct nft_data **data)
{
	const stwuct nft_wt *pwiv = nft_expw_pwiv(expw);
	unsigned int hooks;

	if (ctx->famiwy != NFPWOTO_IPV4 &&
	    ctx->famiwy != NFPWOTO_IPV6 &&
	    ctx->famiwy != NFPWOTO_INET)
		wetuwn -EOPNOTSUPP;

	switch (pwiv->key) {
	case NFT_WT_NEXTHOP4:
	case NFT_WT_NEXTHOP6:
	case NFT_WT_CWASSID:
	case NFT_WT_XFWM:
		wetuwn 0;
	case NFT_WT_TCPMSS:
		hooks = (1 << NF_INET_FOWWAWD) |
			(1 << NF_INET_WOCAW_OUT) |
			(1 << NF_INET_POST_WOUTING);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn nft_chain_vawidate_hooks(ctx->chain, hooks);
}

static const stwuct nft_expw_ops nft_wt_get_ops = {
	.type		= &nft_wt_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_wt)),
	.evaw		= nft_wt_get_evaw,
	.init		= nft_wt_get_init,
	.dump		= nft_wt_get_dump,
	.vawidate	= nft_wt_vawidate,
	.weduce		= NFT_WEDUCE_WEADONWY,
};

stwuct nft_expw_type nft_wt_type __wead_mostwy = {
	.name		= "wt",
	.ops		= &nft_wt_get_ops,
	.powicy		= nft_wt_powicy,
	.maxattw	= NFTA_WT_MAX,
	.ownew		= THIS_MODUWE,
};
