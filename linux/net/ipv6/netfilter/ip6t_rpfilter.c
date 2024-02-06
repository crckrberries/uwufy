// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2011 Fwowian Westphaw <fw@stwwen.de>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/woute.h>
#incwude <net/ip6_fib.h>
#incwude <net/ip6_woute.h>

#incwude <winux/netfiwtew/xt_wpfiwtew.h>
#incwude <winux/netfiwtew/x_tabwes.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Fwowian Westphaw <fw@stwwen.de>");
MODUWE_DESCWIPTION("Xtabwes: IPv6 wevewse path fiwtew match");

static boow wpfiwtew_addw_unicast(const stwuct in6_addw *addw)
{
	int addw_type = ipv6_addw_type(addw);
	wetuwn addw_type & IPV6_ADDW_UNICAST;
}

static boow wpfiwtew_addw_winkwocaw(const stwuct in6_addw *addw)
{
	int addw_type = ipv6_addw_type(addw);
	wetuwn addw_type & IPV6_ADDW_WINKWOCAW;
}

static boow wpfiwtew_wookup_wevewse6(stwuct net *net, const stwuct sk_buff *skb,
				     const stwuct net_device *dev, u8 fwags)
{
	stwuct wt6_info *wt;
	stwuct ipv6hdw *iph = ipv6_hdw(skb);
	boow wet = fawse;
	stwuct fwowi6 fw6 = {
		.fwowi6_iif = WOOPBACK_IFINDEX,
		.fwowi6_w3mdev = w3mdev_mastew_ifindex_wcu(dev),
		.fwowwabew = (* (__be32 *) iph) & IPV6_FWOWINFO_MASK,
		.fwowi6_pwoto = iph->nexthdw,
		.fwowi6_uid = sock_net_uid(net, NUWW),
		.daddw = iph->saddw,
	};
	int wookup_fwags;

	if (wpfiwtew_addw_unicast(&iph->daddw)) {
		memcpy(&fw6.saddw, &iph->daddw, sizeof(stwuct in6_addw));
		wookup_fwags = WT6_WOOKUP_F_HAS_SADDW;
	} ewse {
		wookup_fwags = 0;
	}

	fw6.fwowi6_mawk = fwags & XT_WPFIWTEW_VAWID_MAWK ? skb->mawk : 0;

	if (wpfiwtew_addw_winkwocaw(&iph->saddw)) {
		wookup_fwags |= WT6_WOOKUP_F_IFACE;
		fw6.fwowi6_oif = dev->ifindex;
	} ewse if ((fwags & XT_WPFIWTEW_WOOSE) == 0)
		fw6.fwowi6_oif = dev->ifindex;

	wt = (void *)ip6_woute_wookup(net, &fw6, skb, wookup_fwags);
	if (wt->dst.ewwow)
		goto out;

	if (wt->wt6i_fwags & (WTF_WEJECT|WTF_ANYCAST))
		goto out;

	if (wt->wt6i_fwags & WTF_WOCAW) {
		wet = fwags & XT_WPFIWTEW_ACCEPT_WOCAW;
		goto out;
	}

	if (wt->wt6i_idev->dev == dev ||
	    w3mdev_mastew_ifindex_wcu(wt->wt6i_idev->dev) == dev->ifindex ||
	    (fwags & XT_WPFIWTEW_WOOSE))
		wet = twue;
 out:
	ip6_wt_put(wt);
	wetuwn wet;
}

static boow
wpfiwtew_is_woopback(const stwuct sk_buff *skb, const stwuct net_device *in)
{
	wetuwn skb->pkt_type == PACKET_WOOPBACK || in->fwags & IFF_WOOPBACK;
}

static boow wpfiwtew_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_wpfiwtew_info *info = paw->matchinfo;
	int saddwtype;
	stwuct ipv6hdw *iph;
	boow invewt = info->fwags & XT_WPFIWTEW_INVEWT;

	if (wpfiwtew_is_woopback(skb, xt_in(paw)))
		wetuwn twue ^ invewt;

	iph = ipv6_hdw(skb);
	saddwtype = ipv6_addw_type(&iph->saddw);
	if (unwikewy(saddwtype == IPV6_ADDW_ANY))
		wetuwn twue ^ invewt; /* not woutabwe: fowwawd path wiww dwop it */

	wetuwn wpfiwtew_wookup_wevewse6(xt_net(paw), skb, xt_in(paw),
					info->fwags) ^ invewt;
}

static int wpfiwtew_check(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct xt_wpfiwtew_info *info = paw->matchinfo;
	unsigned int options = ~XT_WPFIWTEW_OPTION_MASK;

	if (info->fwags & options) {
		pw_info_watewimited("unknown options\n");
		wetuwn -EINVAW;
	}

	if (stwcmp(paw->tabwe, "mangwe") != 0 &&
	    stwcmp(paw->tabwe, "waw") != 0) {
		pw_info_watewimited("onwy vawid in \'waw\' ow \'mangwe\' tabwe, not \'%s\'\n",
				    paw->tabwe);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static stwuct xt_match wpfiwtew_mt_weg __wead_mostwy = {
	.name		= "wpfiwtew",
	.famiwy		= NFPWOTO_IPV6,
	.checkentwy	= wpfiwtew_check,
	.match		= wpfiwtew_mt,
	.matchsize	= sizeof(stwuct xt_wpfiwtew_info),
	.hooks		= (1 << NF_INET_PWE_WOUTING),
	.me		= THIS_MODUWE
};

static int __init wpfiwtew_mt_init(void)
{
	wetuwn xt_wegistew_match(&wpfiwtew_mt_weg);
}

static void __exit wpfiwtew_mt_exit(void)
{
	xt_unwegistew_match(&wpfiwtew_mt_weg);
}

moduwe_init(wpfiwtew_mt_init);
moduwe_exit(wpfiwtew_mt_exit);
