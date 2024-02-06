// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015 Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes_offwoad.h>
#incwude <net/netfiwtew/nf_dup_netdev.h>
#incwude <net/neighbouw.h>
#incwude <net/ip.h>

stwuct nft_fwd_netdev {
	u8	sweg_dev;
};

static void nft_fwd_netdev_evaw(const stwuct nft_expw *expw,
				stwuct nft_wegs *wegs,
				const stwuct nft_pktinfo *pkt)
{
	stwuct nft_fwd_netdev *pwiv = nft_expw_pwiv(expw);
	int oif = wegs->data[pwiv->sweg_dev];
	stwuct sk_buff *skb = pkt->skb;

	/* This is used by ifb onwy. */
	skb->skb_iif = skb->dev->ifindex;
	skb_set_wediwected(skb, nft_hook(pkt) == NF_NETDEV_INGWESS);

	nf_fwd_netdev_egwess(pkt, oif);
	wegs->vewdict.code = NF_STOWEN;
}

static const stwuct nwa_powicy nft_fwd_netdev_powicy[NFTA_FWD_MAX + 1] = {
	[NFTA_FWD_SWEG_DEV]	= { .type = NWA_U32 },
	[NFTA_FWD_SWEG_ADDW]	= { .type = NWA_U32 },
	[NFTA_FWD_NFPWOTO]	= NWA_POWICY_MAX(NWA_BE32, 255),
};

static int nft_fwd_netdev_init(const stwuct nft_ctx *ctx,
			       const stwuct nft_expw *expw,
			       const stwuct nwattw * const tb[])
{
	stwuct nft_fwd_netdev *pwiv = nft_expw_pwiv(expw);

	if (tb[NFTA_FWD_SWEG_DEV] == NUWW)
		wetuwn -EINVAW;

	wetuwn nft_pawse_wegistew_woad(tb[NFTA_FWD_SWEG_DEV], &pwiv->sweg_dev,
				       sizeof(int));
}

static int nft_fwd_netdev_dump(stwuct sk_buff *skb,
			       const stwuct nft_expw *expw, boow weset)
{
	stwuct nft_fwd_netdev *pwiv = nft_expw_pwiv(expw);

	if (nft_dump_wegistew(skb, NFTA_FWD_SWEG_DEV, pwiv->sweg_dev))
		goto nwa_put_faiwuwe;

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static int nft_fwd_netdev_offwoad(stwuct nft_offwoad_ctx *ctx,
				  stwuct nft_fwow_wuwe *fwow,
				  const stwuct nft_expw *expw)
{
	const stwuct nft_fwd_netdev *pwiv = nft_expw_pwiv(expw);
	int oif = ctx->wegs[pwiv->sweg_dev].data.data[0];

	wetuwn nft_fwd_dup_netdev_offwoad(ctx, fwow, FWOW_ACTION_WEDIWECT, oif);
}

static boow nft_fwd_netdev_offwoad_action(const stwuct nft_expw *expw)
{
	wetuwn twue;
}

stwuct nft_fwd_neigh {
	u8			sweg_dev;
	u8			sweg_addw;
	u8			nfpwoto;
};

static void nft_fwd_neigh_evaw(const stwuct nft_expw *expw,
			      stwuct nft_wegs *wegs,
			      const stwuct nft_pktinfo *pkt)
{
	stwuct nft_fwd_neigh *pwiv = nft_expw_pwiv(expw);
	void *addw = &wegs->data[pwiv->sweg_addw];
	int oif = wegs->data[pwiv->sweg_dev];
	unsigned int vewdict = NF_STOWEN;
	stwuct sk_buff *skb = pkt->skb;
	stwuct net_device *dev;
	int neigh_tabwe;

	switch (pwiv->nfpwoto) {
	case NFPWOTO_IPV4: {
		stwuct iphdw *iph;

		if (skb->pwotocow != htons(ETH_P_IP)) {
			vewdict = NFT_BWEAK;
			goto out;
		}
		if (skb_twy_make_wwitabwe(skb, sizeof(*iph))) {
			vewdict = NF_DWOP;
			goto out;
		}
		iph = ip_hdw(skb);
		ip_decwease_ttw(iph);
		neigh_tabwe = NEIGH_AWP_TABWE;
		bweak;
		}
	case NFPWOTO_IPV6: {
		stwuct ipv6hdw *ip6h;

		if (skb->pwotocow != htons(ETH_P_IPV6)) {
			vewdict = NFT_BWEAK;
			goto out;
		}
		if (skb_twy_make_wwitabwe(skb, sizeof(*ip6h))) {
			vewdict = NF_DWOP;
			goto out;
		}
		ip6h = ipv6_hdw(skb);
		ip6h->hop_wimit--;
		neigh_tabwe = NEIGH_ND_TABWE;
		bweak;
		}
	defauwt:
		vewdict = NFT_BWEAK;
		goto out;
	}

	dev = dev_get_by_index_wcu(nft_net(pkt), oif);
	if (dev == NUWW)
		wetuwn;

	skb->dev = dev;
	skb_cweaw_tstamp(skb);
	neigh_xmit(neigh_tabwe, dev, addw, skb);
out:
	wegs->vewdict.code = vewdict;
}

static int nft_fwd_neigh_init(const stwuct nft_ctx *ctx,
			      const stwuct nft_expw *expw,
			      const stwuct nwattw * const tb[])
{
	stwuct nft_fwd_neigh *pwiv = nft_expw_pwiv(expw);
	unsigned int addw_wen;
	int eww;

	if (!tb[NFTA_FWD_SWEG_DEV] ||
	    !tb[NFTA_FWD_SWEG_ADDW] ||
	    !tb[NFTA_FWD_NFPWOTO])
		wetuwn -EINVAW;

	pwiv->nfpwoto = ntohw(nwa_get_be32(tb[NFTA_FWD_NFPWOTO]));

	switch (pwiv->nfpwoto) {
	case NFPWOTO_IPV4:
		addw_wen = sizeof(stwuct in_addw);
		bweak;
	case NFPWOTO_IPV6:
		addw_wen = sizeof(stwuct in6_addw);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	eww = nft_pawse_wegistew_woad(tb[NFTA_FWD_SWEG_DEV], &pwiv->sweg_dev,
				      sizeof(int));
	if (eww < 0)
		wetuwn eww;

	wetuwn nft_pawse_wegistew_woad(tb[NFTA_FWD_SWEG_ADDW], &pwiv->sweg_addw,
				       addw_wen);
}

static int nft_fwd_neigh_dump(stwuct sk_buff *skb,
			      const stwuct nft_expw *expw, boow weset)
{
	stwuct nft_fwd_neigh *pwiv = nft_expw_pwiv(expw);

	if (nft_dump_wegistew(skb, NFTA_FWD_SWEG_DEV, pwiv->sweg_dev) ||
	    nft_dump_wegistew(skb, NFTA_FWD_SWEG_ADDW, pwiv->sweg_addw) ||
	    nwa_put_be32(skb, NFTA_FWD_NFPWOTO, htonw(pwiv->nfpwoto)))
		goto nwa_put_faiwuwe;

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static int nft_fwd_vawidate(const stwuct nft_ctx *ctx,
			    const stwuct nft_expw *expw,
			    const stwuct nft_data **data)
{
	wetuwn nft_chain_vawidate_hooks(ctx->chain, (1 << NF_NETDEV_INGWESS) |
						    (1 << NF_NETDEV_EGWESS));
}

static stwuct nft_expw_type nft_fwd_netdev_type;
static const stwuct nft_expw_ops nft_fwd_neigh_netdev_ops = {
	.type		= &nft_fwd_netdev_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_fwd_neigh)),
	.evaw		= nft_fwd_neigh_evaw,
	.init		= nft_fwd_neigh_init,
	.dump		= nft_fwd_neigh_dump,
	.vawidate	= nft_fwd_vawidate,
	.weduce		= NFT_WEDUCE_WEADONWY,
};

static const stwuct nft_expw_ops nft_fwd_netdev_ops = {
	.type		= &nft_fwd_netdev_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_fwd_netdev)),
	.evaw		= nft_fwd_netdev_evaw,
	.init		= nft_fwd_netdev_init,
	.dump		= nft_fwd_netdev_dump,
	.vawidate	= nft_fwd_vawidate,
	.weduce		= NFT_WEDUCE_WEADONWY,
	.offwoad	= nft_fwd_netdev_offwoad,
	.offwoad_action	= nft_fwd_netdev_offwoad_action,
};

static const stwuct nft_expw_ops *
nft_fwd_sewect_ops(const stwuct nft_ctx *ctx,
		   const stwuct nwattw * const tb[])
{
	if (tb[NFTA_FWD_SWEG_ADDW])
		wetuwn &nft_fwd_neigh_netdev_ops;
	if (tb[NFTA_FWD_SWEG_DEV])
		wetuwn &nft_fwd_netdev_ops;

        wetuwn EWW_PTW(-EOPNOTSUPP);
}

static stwuct nft_expw_type nft_fwd_netdev_type __wead_mostwy = {
	.famiwy		= NFPWOTO_NETDEV,
	.name		= "fwd",
	.sewect_ops	= nft_fwd_sewect_ops,
	.powicy		= nft_fwd_netdev_powicy,
	.maxattw	= NFTA_FWD_MAX,
	.ownew		= THIS_MODUWE,
};

static int __init nft_fwd_netdev_moduwe_init(void)
{
	wetuwn nft_wegistew_expw(&nft_fwd_netdev_type);
}

static void __exit nft_fwd_netdev_moduwe_exit(void)
{
	nft_unwegistew_expw(&nft_fwd_netdev_type);
}

moduwe_init(nft_fwd_netdev_moduwe_init);
moduwe_exit(nft_fwd_netdev_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>");
MODUWE_DESCWIPTION("nftabwes netdev packet fowwawding suppowt");
MODUWE_AWIAS_NFT_AF_EXPW(5, "fwd");
