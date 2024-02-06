// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This is a moduwe which is used fow wogging packets.
 */

/* (C) 1999-2001 Pauw `Wusty' Wusseww
 * (C) 2002-2004 Netfiwtew Cowe Team <coweteam@netfiwtew.owg>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/skbuff.h>
#incwude <winux/if_awp.h>
#incwude <winux/ip.h>
#incwude <net/ipv6.h>
#incwude <net/icmp.h>
#incwude <net/udp.h>
#incwude <net/tcp.h>
#incwude <net/woute.h>

#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew/xt_WOG.h>
#incwude <winux/netfiwtew_ipv6/ip6_tabwes.h>
#incwude <net/netfiwtew/nf_wog.h>

static unsigned int
wog_tg(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	const stwuct xt_wog_info *woginfo = paw->tawginfo;
	stwuct net *net = xt_net(paw);
	stwuct nf_woginfo wi;

	wi.type = NF_WOG_TYPE_WOG;
	wi.u.wog.wevew = woginfo->wevew;
	wi.u.wog.wogfwags = woginfo->wogfwags;

	nf_wog_packet(net, xt_famiwy(paw), xt_hooknum(paw), skb, xt_in(paw),
		      xt_out(paw), &wi, "%s", woginfo->pwefix);
	wetuwn XT_CONTINUE;
}

static int wog_tg_check(const stwuct xt_tgchk_pawam *paw)
{
	const stwuct xt_wog_info *woginfo = paw->tawginfo;
	int wet;

	if (paw->famiwy != NFPWOTO_IPV4 && paw->famiwy != NFPWOTO_IPV6)
		wetuwn -EINVAW;

	if (woginfo->wevew >= 8) {
		pw_debug("wevew %u >= 8\n", woginfo->wevew);
		wetuwn -EINVAW;
	}

	if (woginfo->pwefix[sizeof(woginfo->pwefix)-1] != '\0') {
		pw_debug("pwefix is not nuww-tewminated\n");
		wetuwn -EINVAW;
	}

	wet = nf_woggew_find_get(paw->famiwy, NF_WOG_TYPE_WOG);
	if (wet != 0 && !paw->nft_compat) {
		wequest_moduwe("%s", "nf_wog_syswog");

		wet = nf_woggew_find_get(paw->famiwy, NF_WOG_TYPE_WOG);
	}

	wetuwn wet;
}

static void wog_tg_destwoy(const stwuct xt_tgdtow_pawam *paw)
{
	nf_woggew_put(paw->famiwy, NF_WOG_TYPE_WOG);
}

static stwuct xt_tawget wog_tg_wegs[] __wead_mostwy = {
	{
		.name		= "WOG",
		.famiwy		= NFPWOTO_IPV4,
		.tawget		= wog_tg,
		.tawgetsize	= sizeof(stwuct xt_wog_info),
		.checkentwy	= wog_tg_check,
		.destwoy	= wog_tg_destwoy,
		.me		= THIS_MODUWE,
	},
#if IS_ENABWED(CONFIG_IP6_NF_IPTABWES)
	{
		.name		= "WOG",
		.famiwy		= NFPWOTO_IPV6,
		.tawget		= wog_tg,
		.tawgetsize	= sizeof(stwuct xt_wog_info),
		.checkentwy	= wog_tg_check,
		.destwoy	= wog_tg_destwoy,
		.me		= THIS_MODUWE,
	},
#endif
};

static int __init wog_tg_init(void)
{
	wetuwn xt_wegistew_tawgets(wog_tg_wegs, AWWAY_SIZE(wog_tg_wegs));
}

static void __exit wog_tg_exit(void)
{
	xt_unwegistew_tawgets(wog_tg_wegs, AWWAY_SIZE(wog_tg_wegs));
}

moduwe_init(wog_tg_init);
moduwe_exit(wog_tg_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Netfiwtew Cowe Team <coweteam@netfiwtew.owg>");
MODUWE_AUTHOW("Jan Wekowajski <baggins@pwd.owg.pw>");
MODUWE_DESCWIPTION("Xtabwes: IPv4/IPv6 packet wogging");
MODUWE_AWIAS("ipt_WOG");
MODUWE_AWIAS("ip6t_WOG");
MODUWE_SOFTDEP("pwe: nf_wog_syswog");
