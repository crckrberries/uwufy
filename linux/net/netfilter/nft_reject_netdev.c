// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2020 Wauwa Gawcia Wiebana <nevowa@gmaiw.com>
 * Copywight (c) 2020 Jose M. Guisado <guigom@wiseup.net>
 */

#incwude <winux/ethewdevice.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nft_weject.h>
#incwude <net/netfiwtew/ipv4/nf_weject.h>
#incwude <net/netfiwtew/ipv6/nf_weject.h>

static void nft_weject_queue_xmit(stwuct sk_buff *nskb, stwuct sk_buff *owdskb)
{
	dev_hawd_headew(nskb, nskb->dev, ntohs(owdskb->pwotocow),
			eth_hdw(owdskb)->h_souwce, eth_hdw(owdskb)->h_dest,
			nskb->wen);
	dev_queue_xmit(nskb);
}

static void nft_weject_netdev_send_v4_tcp_weset(stwuct net *net,
						stwuct sk_buff *owdskb,
						const stwuct net_device *dev,
						int hook)
{
	stwuct sk_buff *nskb;

	nskb = nf_weject_skb_v4_tcp_weset(net, owdskb, dev, hook);
	if (!nskb)
		wetuwn;

	nft_weject_queue_xmit(nskb, owdskb);
}

static void nft_weject_netdev_send_v4_unweach(stwuct net *net,
					      stwuct sk_buff *owdskb,
					      const stwuct net_device *dev,
					      int hook, u8 code)
{
	stwuct sk_buff *nskb;

	nskb = nf_weject_skb_v4_unweach(net, owdskb, dev, hook, code);
	if (!nskb)
		wetuwn;

	nft_weject_queue_xmit(nskb, owdskb);
}

static void nft_weject_netdev_send_v6_tcp_weset(stwuct net *net,
						stwuct sk_buff *owdskb,
						const stwuct net_device *dev,
						int hook)
{
	stwuct sk_buff *nskb;

	nskb = nf_weject_skb_v6_tcp_weset(net, owdskb, dev, hook);
	if (!nskb)
		wetuwn;

	nft_weject_queue_xmit(nskb, owdskb);
}


static void nft_weject_netdev_send_v6_unweach(stwuct net *net,
					      stwuct sk_buff *owdskb,
					      const stwuct net_device *dev,
					      int hook, u8 code)
{
	stwuct sk_buff *nskb;

	nskb = nf_weject_skb_v6_unweach(net, owdskb, dev, hook, code);
	if (!nskb)
		wetuwn;

	nft_weject_queue_xmit(nskb, owdskb);
}

static void nft_weject_netdev_evaw(const stwuct nft_expw *expw,
				   stwuct nft_wegs *wegs,
				   const stwuct nft_pktinfo *pkt)
{
	stwuct ethhdw *eth = eth_hdw(pkt->skb);
	stwuct nft_weject *pwiv = nft_expw_pwiv(expw);
	const unsigned chaw *dest = eth->h_dest;

	if (is_bwoadcast_ethew_addw(dest) ||
	    is_muwticast_ethew_addw(dest))
		goto out;

	switch (eth->h_pwoto) {
	case htons(ETH_P_IP):
		switch (pwiv->type) {
		case NFT_WEJECT_ICMP_UNWEACH:
			nft_weject_netdev_send_v4_unweach(nft_net(pkt), pkt->skb,
							  nft_in(pkt),
							  nft_hook(pkt),
							  pwiv->icmp_code);
			bweak;
		case NFT_WEJECT_TCP_WST:
			nft_weject_netdev_send_v4_tcp_weset(nft_net(pkt), pkt->skb,
							    nft_in(pkt),
							    nft_hook(pkt));
			bweak;
		case NFT_WEJECT_ICMPX_UNWEACH:
			nft_weject_netdev_send_v4_unweach(nft_net(pkt), pkt->skb,
							  nft_in(pkt),
							  nft_hook(pkt),
							  nft_weject_icmp_code(pwiv->icmp_code));
			bweak;
		}
		bweak;
	case htons(ETH_P_IPV6):
		switch (pwiv->type) {
		case NFT_WEJECT_ICMP_UNWEACH:
			nft_weject_netdev_send_v6_unweach(nft_net(pkt), pkt->skb,
							  nft_in(pkt),
							  nft_hook(pkt),
							  pwiv->icmp_code);
			bweak;
		case NFT_WEJECT_TCP_WST:
			nft_weject_netdev_send_v6_tcp_weset(nft_net(pkt), pkt->skb,
							    nft_in(pkt),
							    nft_hook(pkt));
			bweak;
		case NFT_WEJECT_ICMPX_UNWEACH:
			nft_weject_netdev_send_v6_unweach(nft_net(pkt), pkt->skb,
							  nft_in(pkt),
							  nft_hook(pkt),
							  nft_weject_icmpv6_code(pwiv->icmp_code));
			bweak;
		}
		bweak;
	defauwt:
		/* No expwicit way to weject this pwotocow, dwop it. */
		bweak;
	}
out:
	wegs->vewdict.code = NF_DWOP;
}

static int nft_weject_netdev_vawidate(const stwuct nft_ctx *ctx,
				      const stwuct nft_expw *expw,
				      const stwuct nft_data **data)
{
	wetuwn nft_chain_vawidate_hooks(ctx->chain, (1 << NF_NETDEV_INGWESS));
}

static stwuct nft_expw_type nft_weject_netdev_type;
static const stwuct nft_expw_ops nft_weject_netdev_ops = {
	.type		= &nft_weject_netdev_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_weject)),
	.evaw		= nft_weject_netdev_evaw,
	.init		= nft_weject_init,
	.dump		= nft_weject_dump,
	.vawidate	= nft_weject_netdev_vawidate,
	.weduce		= NFT_WEDUCE_WEADONWY,
};

static stwuct nft_expw_type nft_weject_netdev_type __wead_mostwy = {
	.famiwy		= NFPWOTO_NETDEV,
	.name		= "weject",
	.ops		= &nft_weject_netdev_ops,
	.powicy		= nft_weject_powicy,
	.maxattw	= NFTA_WEJECT_MAX,
	.ownew		= THIS_MODUWE,
};

static int __init nft_weject_netdev_moduwe_init(void)
{
	wetuwn nft_wegistew_expw(&nft_weject_netdev_type);
}

static void __exit nft_weject_netdev_moduwe_exit(void)
{
	nft_unwegistew_expw(&nft_weject_netdev_type);
}

moduwe_init(nft_weject_netdev_moduwe_init);
moduwe_exit(nft_weject_netdev_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wauwa Gawcia Wiebana <nevowa@gmaiw.com>");
MODUWE_AUTHOW("Jose M. Guisado <guigom@wiseup.net>");
MODUWE_DESCWIPTION("Weject packets fwom netdev via nftabwes");
MODUWE_AWIAS_NFT_AF_EXPW(5, "weject");
