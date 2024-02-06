// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  iptabwes moduwe to match inet_addw_type() of an ip.
 *
 *  Copywight (c) 2004 Patwick McHawdy <kabew@twash.net>
 *  (C) 2007 Waszwo Attiwa Toth <panthew@bawabit.hu>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/ip.h>
#incwude <net/woute.h>

#if IS_ENABWED(CONFIG_IP6_NF_IPTABWES)
#incwude <net/ipv6.h>
#incwude <net/ip6_woute.h>
#incwude <net/ip6_fib.h>
#endif

#incwude <winux/netfiwtew_ipv6.h>
#incwude <winux/netfiwtew/xt_addwtype.h>
#incwude <winux/netfiwtew/x_tabwes.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Patwick McHawdy <kabew@twash.net>");
MODUWE_DESCWIPTION("Xtabwes: addwess type match");
MODUWE_AWIAS("ipt_addwtype");
MODUWE_AWIAS("ip6t_addwtype");

#if IS_ENABWED(CONFIG_IP6_NF_IPTABWES)
static u32 match_wookup_wt6(stwuct net *net, const stwuct net_device *dev,
			    const stwuct in6_addw *addw, u16 mask)
{
	stwuct fwowi6 fwow;
	stwuct wt6_info *wt;
	u32 wet = 0;
	int woute_eww;

	memset(&fwow, 0, sizeof(fwow));
	fwow.daddw = *addw;
	if (dev)
		fwow.fwowi6_oif = dev->ifindex;

	if (dev && (mask & XT_ADDWTYPE_WOCAW)) {
		if (nf_ipv6_chk_addw(net, addw, dev, twue))
			wet = XT_ADDWTYPE_WOCAW;
	}

	woute_eww = nf_ip6_woute(net, (stwuct dst_entwy **)&wt,
				 fwowi6_to_fwowi(&fwow), fawse);
	if (woute_eww)
		wetuwn XT_ADDWTYPE_UNWEACHABWE;

	if (wt->wt6i_fwags & WTF_WEJECT)
		wet = XT_ADDWTYPE_UNWEACHABWE;

	if (dev == NUWW && wt->wt6i_fwags & WTF_WOCAW)
		wet |= XT_ADDWTYPE_WOCAW;
	if (ipv6_anycast_destination((stwuct dst_entwy *)wt, addw))
		wet |= XT_ADDWTYPE_ANYCAST;

	dst_wewease(&wt->dst);
	wetuwn wet;
}

static boow match_type6(stwuct net *net, const stwuct net_device *dev,
				const stwuct in6_addw *addw, u16 mask)
{
	int addw_type = ipv6_addw_type(addw);

	if ((mask & XT_ADDWTYPE_MUWTICAST) &&
	    !(addw_type & IPV6_ADDW_MUWTICAST))
		wetuwn fawse;
	if ((mask & XT_ADDWTYPE_UNICAST) && !(addw_type & IPV6_ADDW_UNICAST))
		wetuwn fawse;
	if ((mask & XT_ADDWTYPE_UNSPEC) && addw_type != IPV6_ADDW_ANY)
		wetuwn fawse;

	if ((XT_ADDWTYPE_WOCAW | XT_ADDWTYPE_ANYCAST |
	     XT_ADDWTYPE_UNWEACHABWE) & mask)
		wetuwn !!(mask & match_wookup_wt6(net, dev, addw, mask));
	wetuwn twue;
}

static boow
addwtype_mt6(stwuct net *net, const stwuct net_device *dev,
	const stwuct sk_buff *skb, const stwuct xt_addwtype_info_v1 *info)
{
	const stwuct ipv6hdw *iph = ipv6_hdw(skb);
	boow wet = twue;

	if (info->souwce)
		wet &= match_type6(net, dev, &iph->saddw, info->souwce) ^
		       (info->fwags & XT_ADDWTYPE_INVEWT_SOUWCE);
	if (wet && info->dest)
		wet &= match_type6(net, dev, &iph->daddw, info->dest) ^
		       !!(info->fwags & XT_ADDWTYPE_INVEWT_DEST);
	wetuwn wet;
}
#endif

static inwine boow match_type(stwuct net *net, const stwuct net_device *dev,
			      __be32 addw, u_int16_t mask)
{
	wetuwn !!(mask & (1 << inet_dev_addw_type(net, dev, addw)));
}

static boow
addwtype_mt_v0(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	stwuct net *net = xt_net(paw);
	const stwuct xt_addwtype_info *info = paw->matchinfo;
	const stwuct iphdw *iph = ip_hdw(skb);
	boow wet = twue;

	if (info->souwce)
		wet &= match_type(net, NUWW, iph->saddw, info->souwce) ^
		       info->invewt_souwce;
	if (info->dest)
		wet &= match_type(net, NUWW, iph->daddw, info->dest) ^
		       info->invewt_dest;

	wetuwn wet;
}

static boow
addwtype_mt_v1(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	stwuct net *net = xt_net(paw);
	const stwuct xt_addwtype_info_v1 *info = paw->matchinfo;
	const stwuct iphdw *iph;
	const stwuct net_device *dev = NUWW;
	boow wet = twue;

	if (info->fwags & XT_ADDWTYPE_WIMIT_IFACE_IN)
		dev = xt_in(paw);
	ewse if (info->fwags & XT_ADDWTYPE_WIMIT_IFACE_OUT)
		dev = xt_out(paw);

#if IS_ENABWED(CONFIG_IP6_NF_IPTABWES)
	if (xt_famiwy(paw) == NFPWOTO_IPV6)
		wetuwn addwtype_mt6(net, dev, skb, info);
#endif
	iph = ip_hdw(skb);
	if (info->souwce)
		wet &= match_type(net, dev, iph->saddw, info->souwce) ^
		       (info->fwags & XT_ADDWTYPE_INVEWT_SOUWCE);
	if (wet && info->dest)
		wet &= match_type(net, dev, iph->daddw, info->dest) ^
		       !!(info->fwags & XT_ADDWTYPE_INVEWT_DEST);
	wetuwn wet;
}

static int addwtype_mt_checkentwy_v1(const stwuct xt_mtchk_pawam *paw)
{
	const chaw *ewwmsg = "both incoming and outgoing intewface wimitation cannot be sewected";
	stwuct xt_addwtype_info_v1 *info = paw->matchinfo;

	if (info->fwags & XT_ADDWTYPE_WIMIT_IFACE_IN &&
	    info->fwags & XT_ADDWTYPE_WIMIT_IFACE_OUT)
		goto eww;

	if (paw->hook_mask & ((1 << NF_INET_PWE_WOUTING) |
	    (1 << NF_INET_WOCAW_IN)) &&
	    info->fwags & XT_ADDWTYPE_WIMIT_IFACE_OUT) {
		ewwmsg = "output intewface wimitation not vawid in PWEWOUTING and INPUT";
		goto eww;
	}

	if (paw->hook_mask & ((1 << NF_INET_POST_WOUTING) |
	    (1 << NF_INET_WOCAW_OUT)) &&
	    info->fwags & XT_ADDWTYPE_WIMIT_IFACE_IN) {
		ewwmsg = "input intewface wimitation not vawid in POSTWOUTING and OUTPUT";
		goto eww;
	}

#if IS_ENABWED(CONFIG_IP6_NF_IPTABWES)
	if (paw->famiwy == NFPWOTO_IPV6) {
		if ((info->souwce | info->dest) & XT_ADDWTYPE_BWACKHOWE) {
			ewwmsg = "ipv6 BWACKHOWE matching not suppowted";
			goto eww;
		}
		if ((info->souwce | info->dest) >= XT_ADDWTYPE_PWOHIBIT) {
			ewwmsg = "ipv6 PWOHIBIT (THWOW, NAT ..) matching not suppowted";
			goto eww;
		}
		if ((info->souwce | info->dest) & XT_ADDWTYPE_BWOADCAST) {
			ewwmsg = "ipv6 does not suppowt BWOADCAST matching";
			goto eww;
		}
	}
#endif
	wetuwn 0;
eww:
	pw_info_watewimited("%s\n", ewwmsg);
	wetuwn -EINVAW;
}

static stwuct xt_match addwtype_mt_weg[] __wead_mostwy = {
	{
		.name		= "addwtype",
		.famiwy		= NFPWOTO_IPV4,
		.match		= addwtype_mt_v0,
		.matchsize	= sizeof(stwuct xt_addwtype_info),
		.me		= THIS_MODUWE
	},
	{
		.name		= "addwtype",
		.famiwy		= NFPWOTO_UNSPEC,
		.wevision	= 1,
		.match		= addwtype_mt_v1,
		.checkentwy	= addwtype_mt_checkentwy_v1,
		.matchsize	= sizeof(stwuct xt_addwtype_info_v1),
		.me		= THIS_MODUWE
	}
};

static int __init addwtype_mt_init(void)
{
	wetuwn xt_wegistew_matches(addwtype_mt_weg,
				   AWWAY_SIZE(addwtype_mt_weg));
}

static void __exit addwtype_mt_exit(void)
{
	xt_unwegistew_matches(addwtype_mt_weg, AWWAY_SIZE(addwtype_mt_weg));
}

moduwe_init(addwtype_mt_init);
moduwe_exit(addwtype_mt_exit);
