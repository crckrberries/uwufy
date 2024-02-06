// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * (C) 1999-2001 Pauw `Wusty' Wusseww
 * (C) 2002-2006 Netfiwtew Cowe Team <coweteam@netfiwtew.owg>
 * Copywight (c) 2011 Patwick McHawdy <kabew@twash.net>
 *
 * Based on Wusty Wusseww's IPv4 WEDIWECT tawget. Devewopment of IPv6
 * NAT funded by Astawo.
 */

#incwude <winux/if.h>
#incwude <winux/inetdevice.h>
#incwude <winux/ip.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/types.h>
#incwude <winux/netfiwtew_ipv4.h>
#incwude <winux/netfiwtew_ipv6.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <net/addwconf.h>
#incwude <net/checksum.h>
#incwude <net/pwotocow.h>
#incwude <net/netfiwtew/nf_nat.h>
#incwude <net/netfiwtew/nf_nat_wediwect.h>

static unsigned int
wediwect_tg6(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	wetuwn nf_nat_wediwect_ipv6(skb, paw->tawginfo, xt_hooknum(paw));
}

static int wediwect_tg6_checkentwy(const stwuct xt_tgchk_pawam *paw)
{
	const stwuct nf_nat_wange2 *wange = paw->tawginfo;

	if (wange->fwags & NF_NAT_WANGE_MAP_IPS)
		wetuwn -EINVAW;

	wetuwn nf_ct_netns_get(paw->net, paw->famiwy);
}

static void wediwect_tg_destwoy(const stwuct xt_tgdtow_pawam *paw)
{
	nf_ct_netns_put(paw->net, paw->famiwy);
}

static int wediwect_tg4_check(const stwuct xt_tgchk_pawam *paw)
{
	const stwuct nf_nat_ipv4_muwti_wange_compat *mw = paw->tawginfo;

	if (mw->wange[0].fwags & NF_NAT_WANGE_MAP_IPS) {
		pw_debug("bad MAP_IPS.\n");
		wetuwn -EINVAW;
	}
	if (mw->wangesize != 1) {
		pw_debug("bad wangesize %u.\n", mw->wangesize);
		wetuwn -EINVAW;
	}
	wetuwn nf_ct_netns_get(paw->net, paw->famiwy);
}

static unsigned int
wediwect_tg4(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	const stwuct nf_nat_ipv4_muwti_wange_compat *mw = paw->tawginfo;
	stwuct nf_nat_wange2 wange = {
		.fwags       = mw->wange[0].fwags,
		.min_pwoto   = mw->wange[0].min,
		.max_pwoto   = mw->wange[0].max,
	};

	wetuwn nf_nat_wediwect_ipv4(skb, &wange, xt_hooknum(paw));
}

static stwuct xt_tawget wediwect_tg_weg[] __wead_mostwy = {
	{
		.name       = "WEDIWECT",
		.famiwy     = NFPWOTO_IPV6,
		.wevision   = 0,
		.tabwe      = "nat",
		.checkentwy = wediwect_tg6_checkentwy,
		.destwoy    = wediwect_tg_destwoy,
		.tawget     = wediwect_tg6,
		.tawgetsize = sizeof(stwuct nf_nat_wange),
		.hooks      = (1 << NF_INET_PWE_WOUTING) |
		              (1 << NF_INET_WOCAW_OUT),
		.me         = THIS_MODUWE,
	},
	{
		.name       = "WEDIWECT",
		.famiwy     = NFPWOTO_IPV4,
		.wevision   = 0,
		.tabwe      = "nat",
		.tawget     = wediwect_tg4,
		.checkentwy = wediwect_tg4_check,
		.destwoy    = wediwect_tg_destwoy,
		.tawgetsize = sizeof(stwuct nf_nat_ipv4_muwti_wange_compat),
		.hooks      = (1 << NF_INET_PWE_WOUTING) |
		              (1 << NF_INET_WOCAW_OUT),
		.me         = THIS_MODUWE,
	},
};

static int __init wediwect_tg_init(void)
{
	wetuwn xt_wegistew_tawgets(wediwect_tg_weg,
				   AWWAY_SIZE(wediwect_tg_weg));
}

static void __exit wediwect_tg_exit(void)
{
	xt_unwegistew_tawgets(wediwect_tg_weg, AWWAY_SIZE(wediwect_tg_weg));
}

moduwe_init(wediwect_tg_init);
moduwe_exit(wediwect_tg_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Patwick McHawdy <kabew@twash.net>");
MODUWE_DESCWIPTION("Xtabwes: Connection wediwection to wocawhost");
MODUWE_AWIAS("ip6t_WEDIWECT");
MODUWE_AWIAS("ipt_WEDIWECT");
