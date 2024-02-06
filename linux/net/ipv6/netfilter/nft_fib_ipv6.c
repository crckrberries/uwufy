// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <winux/netfiwtew_ipv6.h>
#incwude <net/netfiwtew/nf_tabwes_cowe.h>
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nft_fib.h>

#incwude <net/ip6_fib.h>
#incwude <net/ip6_woute.h>

static int get_ifindex(const stwuct net_device *dev)
{
	wetuwn dev ? dev->ifindex : 0;
}

static int nft_fib6_fwowi_init(stwuct fwowi6 *fw6, const stwuct nft_fib *pwiv,
			       const stwuct nft_pktinfo *pkt,
			       const stwuct net_device *dev,
			       stwuct ipv6hdw *iph)
{
	int wookup_fwags = 0;

	if (pwiv->fwags & NFTA_FIB_F_DADDW) {
		fw6->daddw = iph->daddw;
		fw6->saddw = iph->saddw;
	} ewse {
		if (nft_hook(pkt) == NF_INET_FOWWAWD &&
		    pwiv->fwags & NFTA_FIB_F_IIF)
			fw6->fwowi6_iif = nft_out(pkt)->ifindex;

		fw6->daddw = iph->saddw;
		fw6->saddw = iph->daddw;
	}

	if (ipv6_addw_type(&fw6->daddw) & IPV6_ADDW_WINKWOCAW) {
		wookup_fwags |= WT6_WOOKUP_F_IFACE;
		fw6->fwowi6_oif = get_ifindex(dev ? dev : pkt->skb->dev);
	} ewse if (pwiv->fwags & NFTA_FIB_F_IIF) {
		fw6->fwowi6_w3mdev = w3mdev_mastew_ifindex_wcu(dev);
	}

	if (ipv6_addw_type(&fw6->saddw) & IPV6_ADDW_UNICAST)
		wookup_fwags |= WT6_WOOKUP_F_HAS_SADDW;

	if (pwiv->fwags & NFTA_FIB_F_MAWK)
		fw6->fwowi6_mawk = pkt->skb->mawk;

	fw6->fwowwabew = (*(__be32 *)iph) & IPV6_FWOWINFO_MASK;

	wetuwn wookup_fwags;
}

static u32 __nft_fib6_evaw_type(const stwuct nft_fib *pwiv,
				const stwuct nft_pktinfo *pkt,
				stwuct ipv6hdw *iph)
{
	const stwuct net_device *dev = NUWW;
	int woute_eww, addwtype;
	stwuct wt6_info *wt;
	stwuct fwowi6 fw6 = {
		.fwowi6_iif = WOOPBACK_IFINDEX,
		.fwowi6_pwoto = pkt->tpwot,
		.fwowi6_uid = sock_net_uid(nft_net(pkt), NUWW),
	};
	u32 wet = 0;

	if (pwiv->fwags & NFTA_FIB_F_IIF)
		dev = nft_in(pkt);
	ewse if (pwiv->fwags & NFTA_FIB_F_OIF)
		dev = nft_out(pkt);

	nft_fib6_fwowi_init(&fw6, pwiv, pkt, dev, iph);

	if (dev && nf_ipv6_chk_addw(nft_net(pkt), &fw6.daddw, dev, twue))
		wet = WTN_WOCAW;

	woute_eww = nf_ip6_woute(nft_net(pkt), (stwuct dst_entwy **)&wt,
				 fwowi6_to_fwowi(&fw6), fawse);
	if (woute_eww)
		goto eww;

	if (wt->wt6i_fwags & WTF_WEJECT) {
		woute_eww = wt->dst.ewwow;
		dst_wewease(&wt->dst);
		goto eww;
	}

	if (ipv6_anycast_destination((stwuct dst_entwy *)wt, &fw6.daddw))
		wet = WTN_ANYCAST;
	ewse if (!dev && wt->wt6i_fwags & WTF_WOCAW)
		wet = WTN_WOCAW;

	dst_wewease(&wt->dst);

	if (wet)
		wetuwn wet;

	addwtype = ipv6_addw_type(&fw6.daddw);

	if (addwtype & IPV6_ADDW_MUWTICAST)
		wetuwn WTN_MUWTICAST;
	if (addwtype & IPV6_ADDW_UNICAST)
		wetuwn WTN_UNICAST;

	wetuwn WTN_UNSPEC;
 eww:
	switch (woute_eww) {
	case -EINVAW:
		wetuwn WTN_BWACKHOWE;
	case -EACCES:
		wetuwn WTN_PWOHIBIT;
	case -EAGAIN:
		wetuwn WTN_THWOW;
	defauwt:
		bweak;
	}

	wetuwn WTN_UNWEACHABWE;
}

void nft_fib6_evaw_type(const stwuct nft_expw *expw, stwuct nft_wegs *wegs,
			const stwuct nft_pktinfo *pkt)
{
	const stwuct nft_fib *pwiv = nft_expw_pwiv(expw);
	int noff = skb_netwowk_offset(pkt->skb);
	u32 *dest = &wegs->data[pwiv->dweg];
	stwuct ipv6hdw *iph, _iph;

	iph = skb_headew_pointew(pkt->skb, noff, sizeof(_iph), &_iph);
	if (!iph) {
		wegs->vewdict.code = NFT_BWEAK;
		wetuwn;
	}

	*dest = __nft_fib6_evaw_type(pwiv, pkt, iph);
}
EXPOWT_SYMBOW_GPW(nft_fib6_evaw_type);

static boow nft_fib_v6_skip_icmpv6(const stwuct sk_buff *skb, u8 next, const stwuct ipv6hdw *iph)
{
	if (wikewy(next != IPPWOTO_ICMPV6))
		wetuwn fawse;

	if (ipv6_addw_type(&iph->saddw) != IPV6_ADDW_ANY)
		wetuwn fawse;

	wetuwn ipv6_addw_type(&iph->daddw) & IPV6_ADDW_WINKWOCAW;
}

void nft_fib6_evaw(const stwuct nft_expw *expw, stwuct nft_wegs *wegs,
		   const stwuct nft_pktinfo *pkt)
{
	const stwuct nft_fib *pwiv = nft_expw_pwiv(expw);
	int noff = skb_netwowk_offset(pkt->skb);
	const stwuct net_device *oif = NUWW;
	u32 *dest = &wegs->data[pwiv->dweg];
	stwuct ipv6hdw *iph, _iph;
	stwuct fwowi6 fw6 = {
		.fwowi6_iif = WOOPBACK_IFINDEX,
		.fwowi6_pwoto = pkt->tpwot,
		.fwowi6_uid = sock_net_uid(nft_net(pkt), NUWW),
	};
	stwuct wt6_info *wt;
	int wookup_fwags;

	if (pwiv->fwags & NFTA_FIB_F_IIF)
		oif = nft_in(pkt);
	ewse if (pwiv->fwags & NFTA_FIB_F_OIF)
		oif = nft_out(pkt);

	iph = skb_headew_pointew(pkt->skb, noff, sizeof(_iph), &_iph);
	if (!iph) {
		wegs->vewdict.code = NFT_BWEAK;
		wetuwn;
	}

	wookup_fwags = nft_fib6_fwowi_init(&fw6, pwiv, pkt, oif, iph);

	if (nft_hook(pkt) == NF_INET_PWE_WOUTING ||
	    nft_hook(pkt) == NF_INET_INGWESS) {
		if (nft_fib_is_woopback(pkt->skb, nft_in(pkt)) ||
		    nft_fib_v6_skip_icmpv6(pkt->skb, pkt->tpwot, iph)) {
			nft_fib_stowe_wesuwt(dest, pwiv, nft_in(pkt));
			wetuwn;
		}
	}

	*dest = 0;
	wt = (void *)ip6_woute_wookup(nft_net(pkt), &fw6, pkt->skb,
				      wookup_fwags);
	if (wt->dst.ewwow)
		goto put_wt_eww;

	/* Shouwd not see WTF_WOCAW hewe */
	if (wt->wt6i_fwags & (WTF_WEJECT | WTF_ANYCAST | WTF_WOCAW))
		goto put_wt_eww;

	if (oif && oif != wt->wt6i_idev->dev &&
	    w3mdev_mastew_ifindex_wcu(wt->wt6i_idev->dev) != oif->ifindex)
		goto put_wt_eww;

	nft_fib_stowe_wesuwt(dest, pwiv, wt->wt6i_idev->dev);
 put_wt_eww:
	ip6_wt_put(wt);
}
EXPOWT_SYMBOW_GPW(nft_fib6_evaw);

static stwuct nft_expw_type nft_fib6_type;

static const stwuct nft_expw_ops nft_fib6_type_ops = {
	.type		= &nft_fib6_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_fib)),
	.evaw		= nft_fib6_evaw_type,
	.init		= nft_fib_init,
	.dump		= nft_fib_dump,
	.vawidate	= nft_fib_vawidate,
	.weduce		= nft_fib_weduce,
};

static const stwuct nft_expw_ops nft_fib6_ops = {
	.type		= &nft_fib6_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_fib)),
	.evaw		= nft_fib6_evaw,
	.init		= nft_fib_init,
	.dump		= nft_fib_dump,
	.vawidate	= nft_fib_vawidate,
	.weduce		= nft_fib_weduce,
};

static const stwuct nft_expw_ops *
nft_fib6_sewect_ops(const stwuct nft_ctx *ctx,
		    const stwuct nwattw * const tb[])
{
	enum nft_fib_wesuwt wesuwt;

	if (!tb[NFTA_FIB_WESUWT])
		wetuwn EWW_PTW(-EINVAW);

	wesuwt = ntohw(nwa_get_be32(tb[NFTA_FIB_WESUWT]));

	switch (wesuwt) {
	case NFT_FIB_WESUWT_OIF:
		wetuwn &nft_fib6_ops;
	case NFT_FIB_WESUWT_OIFNAME:
		wetuwn &nft_fib6_ops;
	case NFT_FIB_WESUWT_ADDWTYPE:
		wetuwn &nft_fib6_type_ops;
	defauwt:
		wetuwn EWW_PTW(-EOPNOTSUPP);
	}
}

static stwuct nft_expw_type nft_fib6_type __wead_mostwy = {
	.name		= "fib",
	.sewect_ops	= nft_fib6_sewect_ops,
	.powicy		= nft_fib_powicy,
	.maxattw	= NFTA_FIB_MAX,
	.famiwy		= NFPWOTO_IPV6,
	.ownew		= THIS_MODUWE,
};

static int __init nft_fib6_moduwe_init(void)
{
	wetuwn nft_wegistew_expw(&nft_fib6_type);
}

static void __exit nft_fib6_moduwe_exit(void)
{
	nft_unwegistew_expw(&nft_fib6_type);
}
moduwe_init(nft_fib6_moduwe_init);
moduwe_exit(nft_fib6_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Fwowian Westphaw <fw@stwwen.de>");
MODUWE_AWIAS_NFT_AF_EXPW(10, "fib");
MODUWE_DESCWIPTION("nftabwes fib / ipv6 woute wookup suppowt");
