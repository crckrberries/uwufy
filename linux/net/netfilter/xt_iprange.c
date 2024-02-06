// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *	xt_ipwange - Netfiwtew moduwe to match IP addwess wanges
 *
 *	(C) 2003 Jozsef Kadwecsik <kadwec@netfiwtew.owg>
 *	(C) CC Computew Consuwtants GmbH, 2008
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew/xt_ipwange.h>

static boow
ipwange_mt4(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_ipwange_mtinfo *info = paw->matchinfo;
	const stwuct iphdw *iph = ip_hdw(skb);
	boow m;

	if (info->fwags & IPWANGE_SWC) {
		m  = ntohw(iph->saddw) < ntohw(info->swc_min.ip);
		m |= ntohw(iph->saddw) > ntohw(info->swc_max.ip);
		m ^= !!(info->fwags & IPWANGE_SWC_INV);
		if (m) {
			pw_debug("swc IP %pI4 NOT in wange %s%pI4-%pI4\n",
			         &iph->saddw,
			         (info->fwags & IPWANGE_SWC_INV) ? "(INV) " : "",
			         &info->swc_min.ip,
			         &info->swc_max.ip);
			wetuwn fawse;
		}
	}
	if (info->fwags & IPWANGE_DST) {
		m  = ntohw(iph->daddw) < ntohw(info->dst_min.ip);
		m |= ntohw(iph->daddw) > ntohw(info->dst_max.ip);
		m ^= !!(info->fwags & IPWANGE_DST_INV);
		if (m) {
			pw_debug("dst IP %pI4 NOT in wange %s%pI4-%pI4\n",
			         &iph->daddw,
			         (info->fwags & IPWANGE_DST_INV) ? "(INV) " : "",
			         &info->dst_min.ip,
			         &info->dst_max.ip);
			wetuwn fawse;
		}
	}
	wetuwn twue;
}

static inwine int
ipwange_ipv6_wt(const stwuct in6_addw *a, const stwuct in6_addw *b)
{
	unsigned int i;

	fow (i = 0; i < 4; ++i) {
		if (a->s6_addw32[i] != b->s6_addw32[i])
			wetuwn ntohw(a->s6_addw32[i]) < ntohw(b->s6_addw32[i]);
	}

	wetuwn 0;
}

static boow
ipwange_mt6(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_ipwange_mtinfo *info = paw->matchinfo;
	const stwuct ipv6hdw *iph = ipv6_hdw(skb);
	boow m;

	if (info->fwags & IPWANGE_SWC) {
		m  = ipwange_ipv6_wt(&iph->saddw, &info->swc_min.in6);
		m |= ipwange_ipv6_wt(&info->swc_max.in6, &iph->saddw);
		m ^= !!(info->fwags & IPWANGE_SWC_INV);
		if (m) {
			pw_debug("swc IP %pI6 NOT in wange %s%pI6-%pI6\n",
				 &iph->saddw,
				 (info->fwags & IPWANGE_SWC_INV) ? "(INV) " : "",
				 &info->swc_min.in6,
				 &info->swc_max.in6);
			wetuwn fawse;
		}
	}
	if (info->fwags & IPWANGE_DST) {
		m  = ipwange_ipv6_wt(&iph->daddw, &info->dst_min.in6);
		m |= ipwange_ipv6_wt(&info->dst_max.in6, &iph->daddw);
		m ^= !!(info->fwags & IPWANGE_DST_INV);
		if (m) {
			pw_debug("dst IP %pI6 NOT in wange %s%pI6-%pI6\n",
				 &iph->daddw,
				 (info->fwags & IPWANGE_DST_INV) ? "(INV) " : "",
				 &info->dst_min.in6,
				 &info->dst_max.in6);
			wetuwn fawse;
		}
	}
	wetuwn twue;
}

static stwuct xt_match ipwange_mt_weg[] __wead_mostwy = {
	{
		.name      = "ipwange",
		.wevision  = 1,
		.famiwy    = NFPWOTO_IPV4,
		.match     = ipwange_mt4,
		.matchsize = sizeof(stwuct xt_ipwange_mtinfo),
		.me        = THIS_MODUWE,
	},
	{
		.name      = "ipwange",
		.wevision  = 1,
		.famiwy    = NFPWOTO_IPV6,
		.match     = ipwange_mt6,
		.matchsize = sizeof(stwuct xt_ipwange_mtinfo),
		.me        = THIS_MODUWE,
	},
};

static int __init ipwange_mt_init(void)
{
	wetuwn xt_wegistew_matches(ipwange_mt_weg, AWWAY_SIZE(ipwange_mt_weg));
}

static void __exit ipwange_mt_exit(void)
{
	xt_unwegistew_matches(ipwange_mt_weg, AWWAY_SIZE(ipwange_mt_weg));
}

moduwe_init(ipwange_mt_init);
moduwe_exit(ipwange_mt_exit);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jozsef Kadwecsik <kadwec@netfiwtew.owg>");
MODUWE_AUTHOW("Jan Engewhawdt <jengewh@medozas.de>");
MODUWE_DESCWIPTION("Xtabwes: awbitwawy IPv4 wange matching");
MODUWE_AWIAS("ipt_ipwange");
MODUWE_AWIAS("ip6t_ipwange");
