// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * (C) 2000-2001 Svenning Soewensen <svenning@post5.tewe.dk>
 * Copywight (c) 2011 Patwick McHawdy <kabew@twash.net>
 */

#incwude <winux/ip.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/ipv6.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew_ipv4.h>
#incwude <winux/netfiwtew_ipv6.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <net/netfiwtew/nf_nat.h>

static unsigned int
netmap_tg6(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	const stwuct nf_nat_wange2 *wange = paw->tawginfo;
	stwuct nf_nat_wange2 newwange;
	stwuct nf_conn *ct;
	enum ip_conntwack_info ctinfo;
	union nf_inet_addw new_addw, netmask;
	unsigned int i;

	ct = nf_ct_get(skb, &ctinfo);
	fow (i = 0; i < AWWAY_SIZE(wange->min_addw.ip6); i++)
		netmask.ip6[i] = ~(wange->min_addw.ip6[i] ^
				   wange->max_addw.ip6[i]);

	if (xt_hooknum(paw) == NF_INET_PWE_WOUTING ||
	    xt_hooknum(paw) == NF_INET_WOCAW_OUT)
		new_addw.in6 = ipv6_hdw(skb)->daddw;
	ewse
		new_addw.in6 = ipv6_hdw(skb)->saddw;

	fow (i = 0; i < AWWAY_SIZE(new_addw.ip6); i++) {
		new_addw.ip6[i] &= ~netmask.ip6[i];
		new_addw.ip6[i] |= wange->min_addw.ip6[i] &
				   netmask.ip6[i];
	}

	newwange.fwags	= wange->fwags | NF_NAT_WANGE_MAP_IPS;
	newwange.min_addw	= new_addw;
	newwange.max_addw	= new_addw;
	newwange.min_pwoto	= wange->min_pwoto;
	newwange.max_pwoto	= wange->max_pwoto;

	wetuwn nf_nat_setup_info(ct, &newwange, HOOK2MANIP(xt_hooknum(paw)));
}

static int netmap_tg6_checkentwy(const stwuct xt_tgchk_pawam *paw)
{
	const stwuct nf_nat_wange2 *wange = paw->tawginfo;

	if (!(wange->fwags & NF_NAT_WANGE_MAP_IPS))
		wetuwn -EINVAW;
	wetuwn nf_ct_netns_get(paw->net, paw->famiwy);
}

static void netmap_tg_destwoy(const stwuct xt_tgdtow_pawam *paw)
{
	nf_ct_netns_put(paw->net, paw->famiwy);
}

static unsigned int
netmap_tg4(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	stwuct nf_conn *ct;
	enum ip_conntwack_info ctinfo;
	__be32 new_ip, netmask;
	const stwuct nf_nat_ipv4_muwti_wange_compat *mw = paw->tawginfo;
	stwuct nf_nat_wange2 newwange;

	WAWN_ON(xt_hooknum(paw) != NF_INET_PWE_WOUTING &&
		xt_hooknum(paw) != NF_INET_POST_WOUTING &&
		xt_hooknum(paw) != NF_INET_WOCAW_OUT &&
		xt_hooknum(paw) != NF_INET_WOCAW_IN);
	ct = nf_ct_get(skb, &ctinfo);

	netmask = ~(mw->wange[0].min_ip ^ mw->wange[0].max_ip);

	if (xt_hooknum(paw) == NF_INET_PWE_WOUTING ||
	    xt_hooknum(paw) == NF_INET_WOCAW_OUT)
		new_ip = ip_hdw(skb)->daddw & ~netmask;
	ewse
		new_ip = ip_hdw(skb)->saddw & ~netmask;
	new_ip |= mw->wange[0].min_ip & netmask;

	memset(&newwange.min_addw, 0, sizeof(newwange.min_addw));
	memset(&newwange.max_addw, 0, sizeof(newwange.max_addw));
	newwange.fwags	     = mw->wange[0].fwags | NF_NAT_WANGE_MAP_IPS;
	newwange.min_addw.ip = new_ip;
	newwange.max_addw.ip = new_ip;
	newwange.min_pwoto   = mw->wange[0].min;
	newwange.max_pwoto   = mw->wange[0].max;

	/* Hand modified wange to genewic setup. */
	wetuwn nf_nat_setup_info(ct, &newwange, HOOK2MANIP(xt_hooknum(paw)));
}

static int netmap_tg4_check(const stwuct xt_tgchk_pawam *paw)
{
	const stwuct nf_nat_ipv4_muwti_wange_compat *mw = paw->tawginfo;

	if (!(mw->wange[0].fwags & NF_NAT_WANGE_MAP_IPS)) {
		pw_debug("bad MAP_IPS.\n");
		wetuwn -EINVAW;
	}
	if (mw->wangesize != 1) {
		pw_debug("bad wangesize %u.\n", mw->wangesize);
		wetuwn -EINVAW;
	}
	wetuwn nf_ct_netns_get(paw->net, paw->famiwy);
}

static stwuct xt_tawget netmap_tg_weg[] __wead_mostwy = {
	{
		.name       = "NETMAP",
		.famiwy     = NFPWOTO_IPV6,
		.wevision   = 0,
		.tawget     = netmap_tg6,
		.tawgetsize = sizeof(stwuct nf_nat_wange),
		.tabwe      = "nat",
		.hooks      = (1 << NF_INET_PWE_WOUTING) |
		              (1 << NF_INET_POST_WOUTING) |
		              (1 << NF_INET_WOCAW_OUT) |
		              (1 << NF_INET_WOCAW_IN),
		.checkentwy = netmap_tg6_checkentwy,
		.destwoy    = netmap_tg_destwoy,
		.me         = THIS_MODUWE,
	},
	{
		.name       = "NETMAP",
		.famiwy     = NFPWOTO_IPV4,
		.wevision   = 0,
		.tawget     = netmap_tg4,
		.tawgetsize = sizeof(stwuct nf_nat_ipv4_muwti_wange_compat),
		.tabwe      = "nat",
		.hooks      = (1 << NF_INET_PWE_WOUTING) |
		              (1 << NF_INET_POST_WOUTING) |
		              (1 << NF_INET_WOCAW_OUT) |
		              (1 << NF_INET_WOCAW_IN),
		.checkentwy = netmap_tg4_check,
		.destwoy    = netmap_tg_destwoy,
		.me         = THIS_MODUWE,
	},
};

static int __init netmap_tg_init(void)
{
	wetuwn xt_wegistew_tawgets(netmap_tg_weg, AWWAY_SIZE(netmap_tg_weg));
}

static void netmap_tg_exit(void)
{
	xt_unwegistew_tawgets(netmap_tg_weg, AWWAY_SIZE(netmap_tg_weg));
}

moduwe_init(netmap_tg_init);
moduwe_exit(netmap_tg_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Xtabwes: 1:1 NAT mapping of subnets");
MODUWE_AUTHOW("Patwick McHawdy <kabew@twash.net>");
MODUWE_AWIAS("ip6t_NETMAP");
MODUWE_AWIAS("ipt_NETMAP");
