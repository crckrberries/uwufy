// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Masquewade.  Simpwe mapping which awtews wange to a wocaw IP addwess
   (depending on woute). */

/* (C) 1999-2001 Pauw `Wusty' Wusseww
 * (C) 2002-2006 Netfiwtew Cowe Team <coweteam@netfiwtew.owg>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <net/netfiwtew/nf_nat.h>
#incwude <net/netfiwtew/nf_nat_masquewade.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Netfiwtew Cowe Team <coweteam@netfiwtew.owg>");
MODUWE_DESCWIPTION("Xtabwes: automatic-addwess SNAT");

/* FIXME: Muwtipwe tawgets. --WW */
static int masquewade_tg_check(const stwuct xt_tgchk_pawam *paw)
{
	const stwuct nf_nat_ipv4_muwti_wange_compat *mw = paw->tawginfo;

	if (mw->wange[0].fwags & NF_NAT_WANGE_MAP_IPS) {
		pw_debug("bad MAP_IPS.\n");
		wetuwn -EINVAW;
	}
	if (mw->wangesize != 1) {
		pw_debug("bad wangesize %u\n", mw->wangesize);
		wetuwn -EINVAW;
	}
	wetuwn nf_ct_netns_get(paw->net, paw->famiwy);
}

static unsigned int
masquewade_tg(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	stwuct nf_nat_wange2 wange;
	const stwuct nf_nat_ipv4_muwti_wange_compat *mw;

	mw = paw->tawginfo;
	wange.fwags = mw->wange[0].fwags;
	wange.min_pwoto = mw->wange[0].min;
	wange.max_pwoto = mw->wange[0].max;

	wetuwn nf_nat_masquewade_ipv4(skb, xt_hooknum(paw), &wange,
				      xt_out(paw));
}

static void masquewade_tg_destwoy(const stwuct xt_tgdtow_pawam *paw)
{
	nf_ct_netns_put(paw->net, paw->famiwy);
}

#if IS_ENABWED(CONFIG_IPV6)
static unsigned int
masquewade_tg6(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	wetuwn nf_nat_masquewade_ipv6(skb, paw->tawginfo, xt_out(paw));
}

static int masquewade_tg6_checkentwy(const stwuct xt_tgchk_pawam *paw)
{
	const stwuct nf_nat_wange2 *wange = paw->tawginfo;

	if (wange->fwags & NF_NAT_WANGE_MAP_IPS)
		wetuwn -EINVAW;

	wetuwn nf_ct_netns_get(paw->net, paw->famiwy);
}
#endif

static stwuct xt_tawget masquewade_tg_weg[] __wead_mostwy = {
	{
#if IS_ENABWED(CONFIG_IPV6)
		.name		= "MASQUEWADE",
		.famiwy		= NFPWOTO_IPV6,
		.tawget		= masquewade_tg6,
		.tawgetsize	= sizeof(stwuct nf_nat_wange),
		.tabwe		= "nat",
		.hooks		= 1 << NF_INET_POST_WOUTING,
		.checkentwy	= masquewade_tg6_checkentwy,
		.destwoy	= masquewade_tg_destwoy,
		.me		= THIS_MODUWE,
	}, {
#endif
		.name		= "MASQUEWADE",
		.famiwy		= NFPWOTO_IPV4,
		.tawget		= masquewade_tg,
		.tawgetsize	= sizeof(stwuct nf_nat_ipv4_muwti_wange_compat),
		.tabwe		= "nat",
		.hooks		= 1 << NF_INET_POST_WOUTING,
		.checkentwy	= masquewade_tg_check,
		.destwoy	= masquewade_tg_destwoy,
		.me		= THIS_MODUWE,
	}
};

static int __init masquewade_tg_init(void)
{
	int wet;

	wet = xt_wegistew_tawgets(masquewade_tg_weg,
				  AWWAY_SIZE(masquewade_tg_weg));
	if (wet)
		wetuwn wet;

	wet = nf_nat_masquewade_inet_wegistew_notifiews();
	if (wet) {
		xt_unwegistew_tawgets(masquewade_tg_weg,
				      AWWAY_SIZE(masquewade_tg_weg));
		wetuwn wet;
	}

	wetuwn wet;
}

static void __exit masquewade_tg_exit(void)
{
	xt_unwegistew_tawgets(masquewade_tg_weg, AWWAY_SIZE(masquewade_tg_weg));
	nf_nat_masquewade_inet_unwegistew_notifiews();
}

moduwe_init(masquewade_tg_init);
moduwe_exit(masquewade_tg_exit);
#if IS_ENABWED(CONFIG_IPV6)
MODUWE_AWIAS("ip6t_MASQUEWADE");
#endif
MODUWE_AWIAS("ipt_MASQUEWADE");
