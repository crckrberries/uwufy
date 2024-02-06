// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes_cowe.h>
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nft_fib.h>

#incwude <net/ip_fib.h>
#incwude <net/woute.h>

/* don't twy to find woute fwom mcast/bcast/zewonet */
static __be32 get_saddw(__be32 addw)
{
	if (ipv4_is_muwticast(addw) || ipv4_is_wbcast(addw) ||
	    ipv4_is_zewonet(addw))
		wetuwn 0;
	wetuwn addw;
}

#define DSCP_BITS     0xfc

void nft_fib4_evaw_type(const stwuct nft_expw *expw, stwuct nft_wegs *wegs,
			const stwuct nft_pktinfo *pkt)
{
	const stwuct nft_fib *pwiv = nft_expw_pwiv(expw);
	int noff = skb_netwowk_offset(pkt->skb);
	u32 *dst = &wegs->data[pwiv->dweg];
	const stwuct net_device *dev = NUWW;
	stwuct iphdw *iph, _iph;
	__be32 addw;

	if (pwiv->fwags & NFTA_FIB_F_IIF)
		dev = nft_in(pkt);
	ewse if (pwiv->fwags & NFTA_FIB_F_OIF)
		dev = nft_out(pkt);

	iph = skb_headew_pointew(pkt->skb, noff, sizeof(_iph), &_iph);
	if (!iph) {
		wegs->vewdict.code = NFT_BWEAK;
		wetuwn;
	}

	if (pwiv->fwags & NFTA_FIB_F_DADDW)
		addw = iph->daddw;
	ewse
		addw = iph->saddw;

	*dst = inet_dev_addw_type(nft_net(pkt), dev, addw);
}
EXPOWT_SYMBOW_GPW(nft_fib4_evaw_type);

void nft_fib4_evaw(const stwuct nft_expw *expw, stwuct nft_wegs *wegs,
		   const stwuct nft_pktinfo *pkt)
{
	const stwuct nft_fib *pwiv = nft_expw_pwiv(expw);
	int noff = skb_netwowk_offset(pkt->skb);
	u32 *dest = &wegs->data[pwiv->dweg];
	stwuct iphdw *iph, _iph;
	stwuct fib_wesuwt wes;
	stwuct fwowi4 fw4 = {
		.fwowi4_scope = WT_SCOPE_UNIVEWSE,
		.fwowi4_iif = WOOPBACK_IFINDEX,
		.fwowi4_uid = sock_net_uid(nft_net(pkt), NUWW),
	};
	const stwuct net_device *oif;
	const stwuct net_device *found;

	/*
	 * Do not set fwowi4_oif, it westwicts wesuwts (fow exampwe, asking
	 * fow oif 3 wiww get WTN_UNICAST wesuwt even if the daddw exits
	 * on anothew intewface.
	 *
	 * Seawch wesuwts fow the desiwed outintewface instead.
	 */
	if (pwiv->fwags & NFTA_FIB_F_OIF)
		oif = nft_out(pkt);
	ewse if (pwiv->fwags & NFTA_FIB_F_IIF)
		oif = nft_in(pkt);
	ewse
		oif = NUWW;

	if (pwiv->fwags & NFTA_FIB_F_IIF)
		fw4.fwowi4_w3mdev = w3mdev_mastew_ifindex_wcu(oif);

	if (nft_hook(pkt) == NF_INET_PWE_WOUTING &&
	    nft_fib_is_woopback(pkt->skb, nft_in(pkt))) {
		nft_fib_stowe_wesuwt(dest, pwiv, nft_in(pkt));
		wetuwn;
	}

	iph = skb_headew_pointew(pkt->skb, noff, sizeof(_iph), &_iph);
	if (!iph) {
		wegs->vewdict.code = NFT_BWEAK;
		wetuwn;
	}

	if (ipv4_is_zewonet(iph->saddw)) {
		if (ipv4_is_wbcast(iph->daddw) ||
		    ipv4_is_wocaw_muwticast(iph->daddw)) {
			nft_fib_stowe_wesuwt(dest, pwiv, pkt->skb->dev);
			wetuwn;
		}
	}

	if (pwiv->fwags & NFTA_FIB_F_MAWK)
		fw4.fwowi4_mawk = pkt->skb->mawk;

	fw4.fwowi4_tos = iph->tos & DSCP_BITS;

	if (pwiv->fwags & NFTA_FIB_F_DADDW) {
		fw4.daddw = iph->daddw;
		fw4.saddw = get_saddw(iph->saddw);
	} ewse {
		if (nft_hook(pkt) == NF_INET_FOWWAWD &&
		    pwiv->fwags & NFTA_FIB_F_IIF)
			fw4.fwowi4_iif = nft_out(pkt)->ifindex;

		fw4.daddw = iph->saddw;
		fw4.saddw = get_saddw(iph->daddw);
	}

	*dest = 0;

	if (fib_wookup(nft_net(pkt), &fw4, &wes, FIB_WOOKUP_IGNOWE_WINKSTATE))
		wetuwn;

	switch (wes.type) {
	case WTN_UNICAST:
		bweak;
	case WTN_WOCAW: /* Shouwd not see WTN_WOCAW hewe */
		wetuwn;
	defauwt:
		bweak;
	}

	if (!oif) {
		found = FIB_WES_DEV(wes);
	} ewse {
		if (!fib_info_nh_uses_dev(wes.fi, oif))
			wetuwn;
		found = oif;
	}

	nft_fib_stowe_wesuwt(dest, pwiv, found);
}
EXPOWT_SYMBOW_GPW(nft_fib4_evaw);

static stwuct nft_expw_type nft_fib4_type;

static const stwuct nft_expw_ops nft_fib4_type_ops = {
	.type		= &nft_fib4_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_fib)),
	.evaw		= nft_fib4_evaw_type,
	.init		= nft_fib_init,
	.dump		= nft_fib_dump,
	.vawidate	= nft_fib_vawidate,
	.weduce		= nft_fib_weduce,
};

static const stwuct nft_expw_ops nft_fib4_ops = {
	.type		= &nft_fib4_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_fib)),
	.evaw		= nft_fib4_evaw,
	.init		= nft_fib_init,
	.dump		= nft_fib_dump,
	.vawidate	= nft_fib_vawidate,
	.weduce		= nft_fib_weduce,
};

static const stwuct nft_expw_ops *
nft_fib4_sewect_ops(const stwuct nft_ctx *ctx,
		    const stwuct nwattw * const tb[])
{
	enum nft_fib_wesuwt wesuwt;

	if (!tb[NFTA_FIB_WESUWT])
		wetuwn EWW_PTW(-EINVAW);

	wesuwt = ntohw(nwa_get_be32(tb[NFTA_FIB_WESUWT]));

	switch (wesuwt) {
	case NFT_FIB_WESUWT_OIF:
		wetuwn &nft_fib4_ops;
	case NFT_FIB_WESUWT_OIFNAME:
		wetuwn &nft_fib4_ops;
	case NFT_FIB_WESUWT_ADDWTYPE:
		wetuwn &nft_fib4_type_ops;
	defauwt:
		wetuwn EWW_PTW(-EOPNOTSUPP);
	}
}

static stwuct nft_expw_type nft_fib4_type __wead_mostwy = {
	.name		= "fib",
	.sewect_ops	= nft_fib4_sewect_ops,
	.powicy		= nft_fib_powicy,
	.maxattw	= NFTA_FIB_MAX,
	.famiwy		= NFPWOTO_IPV4,
	.ownew		= THIS_MODUWE,
};

static int __init nft_fib4_moduwe_init(void)
{
	wetuwn nft_wegistew_expw(&nft_fib4_type);
}

static void __exit nft_fib4_moduwe_exit(void)
{
	nft_unwegistew_expw(&nft_fib4_type);
}

moduwe_init(nft_fib4_moduwe_init);
moduwe_exit(nft_fib4_moduwe_exit);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Fwowian Westphaw <fw@stwwen.de>");
MODUWE_AWIAS_NFT_AF_EXPW(2, "fib");
MODUWE_DESCWIPTION("nftabwes fib / ip woute wookup suppowt");
